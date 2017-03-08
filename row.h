#ifndef ROW_H
#define ROW_H

#include <QList>
#include <QMap>

class Row
{
public:
	Row(const QList<QString>& cols, const QList<QString>& row);

	QString getColumn(const QString& col, bool* ok = NULL);

private:
	QMap<QString, QString> values;

};

#endif // ROW_H