#ifndef CSVFILE_H
#define CSVFILE_H

#include <QList>
#include <QString>
#include <QFile>
#include <row.h>

/**
 * @brief The CSVFile class.  Opens and interprets a Comma Separated Values file following the rules set out in RFC4180.
 */
class CSVFile : protected QFile
{
private:
	typedef QFile super;

public:
	CSVFile(const QString& path);

	/**
	 * @brief interprets a single row from the file as a list of QStrings, where each QString is a cell in the row
	 * @return a dynamically allocated QList of cells.  User must delete the QList when finished.
	 */
	bool readRow(QList<QString>& cells);

	bool open();
	void close();

};

#endif // CSVFILE_H
