#ifndef TEAMLISTDATAMODEL_H
#define TEAMLISTDATAMODEL_H

#include <QAbstractTableModel>
#include <qflags.h>
#include <qfontmetrics.h>
#include <qhash.h>
#include <qlist.h>
#include <entrydatastore.h>

class TeamListDataModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	enum ColumnType {
		INVALID,
		TEAM_NUMBER,
		GEAR_HIGH,
		CLIMB_LOW,
		GEAR_AVG,
		CLIMB_AVG,
		CLIMB_RATE,
		SELECTABLE
	};

	TeamListDataModel(EntryDataStore& store, const QFont& font, QObject* parent = nullptr);
	~TeamListDataModel();

	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	int rowCount(const QModelIndex& parent = QModelIndex()) const;

	QVariant data(const QModelIndex& index, int role) const;
	bool setData(const QModelIndex& index, const QVariant& value, int role);
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;

	Qt::ItemFlags flags(const QModelIndex& index) const;

	void setSortOrder(EntryDataStore::SortOrder order);

private:
	ColumnType columnType(int col) const;
	static QFlags<Qt::AlignmentFlag> columnAlignment(int col);

	QHash<int, bool> team_selections;
	EntryDataStore& data_store;

	QFontMetrics font_metrics;

};

#endif // TEAMLISTDATAMODEL_H
