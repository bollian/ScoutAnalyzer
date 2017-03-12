#include <csvfile.h>
#include <cstdlib>
#include <strings.h>
#include <qiodevice.h>
#include <parseexception.h>

CSVFile::CSVFile(const QString& path) : QFile(path) {}

bool followedBy(char* str, int len, int index, char suf) {
	return index < len - 1 ? str[index + 1] == suf : false;
}

/**
 * @brief grabCell takes the part of a string indicated by start an end an returns it with extra formatting for csv cells
 * @param str the string the cell is contained in
 * @param start the beginning of the cell (inclusive)
 * @param end the end of the cell (exclusive)
 * @return the contents of the cell
 */
QString grabCell(char* str, int start, int end) {
	if (str[start] == '"' && str[end - 1] == '"') {
		++start;
		--end;

		// replace any double quotes with single quotes
		QByteArray copy(str + start, end - start);
		copy.replace("\"\"", "\"");
		return QString(copy);
	}
	return QString(QByteArray(str + start, end - start));
}

bool CSVFile::readRow(QList<QString>& cells) {
	const int expansion_size = 1024;
	int buf_size = 0;
	char* buffer = NULL;
	int read_len;
	int i = 0;
	int cell_start = 0;
	bool quoted = false;
	bool quote_preceded = false;

	do {
		do {
			buf_size += expansion_size;
			buffer = (char*)realloc(buffer, buf_size);
			read_len = readLineData(buffer + buf_size - expansion_size, expansion_size);
			if (read_len == -1) {
				throw ParseException("", -1, "Error reading from file: " + errorString());
			}
		} while (buffer[buf_size - expansion_size + read_len - 1] != '\n' && !atEnd());
		// reset buf_size to the actual length of the string
		buf_size = buf_size - expansion_size + read_len;

		for (; i < buf_size; ++i) {
			switch (buffer[i]) {
			case ',':
				if (!quoted || quote_preceded) {
					cells.append(grabCell(buffer, cell_start, i));
					cell_start = i + 1;
					quoted = false;
					quote_preceded = false;
				} // else this is a comma contained in a cell
				break;
			case '"':
				if (i == cell_start) {
					// this is the beginning of a quoted cell
					quoted = true;
				} else if (quote_preceded) {
					quote_preceded = false; // found a double quote
				} else if (quoted) {
					quote_preceded = true;
				} else {
					throw ParseException(QString(QByteArray(buffer, buf_size)), i, "Unquoted cell contained quotation mark");
				}
				break;
			case '\r':
			case '\n':
				if (!quoted || quote_preceded) {
					cells.append(grabCell(buffer, cell_start, i));
					quoted = false;
					quote_preceded = false;
				}
				break;
			default:
				if (quote_preceded) {
					throw ParseException(QString(QByteArray(buffer, buf_size)), i, "Unpaired quote in cell");
				}
			}
		}

		if (atEnd() && buffer[i - 1] != '\n') {
			// we reached the end of the file but didn't find the newline
			// so the cell was never added to the row

			if (quoted && !quote_preceded) {
				// we never saw the end quote
				throw ParseException(QString(buffer), i, "");
			}

			cells.append(grabCell(buffer, cell_start, i));
			quoted = false;
			quote_preceded = false;
		}
	} while (quoted);

	free(buffer);
	return !atEnd();
}

bool CSVFile::open() {
	return super::open(QIODevice::ReadOnly);
}

void CSVFile::close() {
	super::close();
}
