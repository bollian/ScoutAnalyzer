#include "row.h"

Row::Row(const QList<QString>& columns, const QList<QString>& row) :
	values() {
	for (int i = 0; i < columns.length(); ++i) {
		if (i < row.length()) {
			values.insert(columns[i], row[i]);
		} else {
			values.insert(columns[i], "");
		}
	}
}

QString Row::getColumn(const QString &col, bool *ok) {
	if (ok != NULL) {
		*ok = values.contains(col);
		if (!*ok) {
			return "";
		}
	}
	return *values.find(col);
}
