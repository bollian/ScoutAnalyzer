#include <algorithm>
#include <teamlistdatamodel.h>

TeamListDataModel::TeamListDataModel(EntryDataStore& store, const QFont& font, QObject* parent) : QAbstractTableModel(parent),
	team_selections(),
	data_store(store),
	font_metrics(font) {
}

TeamListDataModel::~TeamListDataModel() {}

int TeamListDataModel::columnCount(const QModelIndex& parent) const {
	return 5;
}

int TeamListDataModel::rowCount(const QModelIndex& parent) const {
	return data_store.teamCount();
}

QVariant TeamListDataModel::data(const QModelIndex& index, int role) const {
	int team = data_store.sortedTeam(index.row());
	if (team == -1) {
		return QVariant(QVariant::Invalid);
	}
	if (index.column() < 0 || index.column() >= columnCount()) {
		return QVariant(QVariant::Invalid);
	}

	if (role == Qt::TextAlignmentRole) {
		return QVariant(columnAlignment(index.column()));
	}

	Entry::Range low;
	QString text;
	switch (columnType(index.column())) {
	case INVALID:
		return QVariant(QVariant::Invalid);
	case TEAM_NUMBER:
		text = QString::number(team);
		break;
	case GEAR_HIGH:
		text = QString::number(data_store.gearHigh(team));
		break;
	case CLIMB_LOW:
		low = data_store.climbLow(team);
		text = QString::number(low.low) + " - " + QString::number(low.high);
		break;
	case GEAR_AVG:
		text = QString::number(data_store.gearAverage(team));
		break;
	case CLIMB_AVG:
		text = QString::number(data_store.climbAverage(team));
		break;
	case CLIMB_RATE:
		text = QString::number(data_store.climbRate(team));
		break;
	case SELECTABLE:
		if (role == Qt::CheckStateRole) {
			return QVariant(team_selections.value(team, true) ? Qt::Checked : Qt::Unchecked);
		} else {
			return QVariant(QVariant::Invalid);
		}
	}

	switch (role) {
	case Qt::DisplayRole:
		return QVariant(text);
	case Qt::SizeHintRole:
		return QVariant(font_metrics.boundingRect(text).size());
	default:
		return QVariant(QVariant::Invalid);
	}
}

bool TeamListDataModel::setData(const QModelIndex& index, const QVariant& value, int role) {
	if (index.row() < 0 || index.row() >= data_store.teamCount()) {
		return false;
	}

	if (columnType(index.column()) == SELECTABLE && role == Qt::CheckStateRole) {
		if (value.type() == QVariant::Int) {
			int team = data_store.sortedTeam(index.row());
			if (value.toInt() == Qt::Checked) {
				team_selections[team] = true;
			} else if (value.toInt() == Qt::Unchecked) {
				team_selections[team] = false;
			} else {
				return false;
			}
		}
		return true;
	}
	return false;
}

QVariant TeamListDataModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (orientation == Qt::Vertical || role == Qt::DecorationRole || role == Qt::EditRole) {
		return QVariant(QVariant::Invalid);
	}

	if (role == Qt::TextAlignmentRole) {
		return QVariant(columnAlignment(section));
	}

	QString col_name;
	switch (columnType(section)) {
	case TeamListDataModel::TEAM_NUMBER:
		col_name = "Team";
		break;
	case TeamListDataModel::GEAR_HIGH:
		col_name = "Gear High";
		break;
	case TeamListDataModel::CLIMB_LOW:
		col_name = "Climb Low";
		break;
	case TeamListDataModel::GEAR_AVG:
		col_name = "Gear Average";
		break;
	case TeamListDataModel::CLIMB_AVG:
		col_name = "Climb Average";
		break;
	case TeamListDataModel::CLIMB_RATE:
		col_name = "Climb Rate";
		break;
	case TeamListDataModel::SELECTABLE:
		col_name = "Selectable";
		break;
	case TeamListDataModel::INVALID:
		return QVariant(QVariant::Invalid);
	}

	if (role == Qt::SizeHintRole) {
		return QVariant(font_metrics.boundingRect(col_name).size());
	}
	return QVariant(col_name);
}

Qt::ItemFlags TeamListDataModel::flags(const QModelIndex& index) const {
	if (index.row() < 0 || index.row() >= data_store.teamCount() ||
			index.column() < 0 || index.column() >= columnCount()) {
		return Qt::NoItemFlags;
	}

	Qt::ItemFlags f = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
	if (columnType(index.column()) == TeamListDataModel::SELECTABLE) {
		f |= Qt::ItemIsUserCheckable;
	}
	return f;
}

TeamListDataModel::ColumnType TeamListDataModel::columnType(int col) const {
	switch (col) {
	case 0:
		return TEAM_NUMBER;
	case 1:
		switch (data_store.sortOrder()) {
		case EntryDataStore::TEAM_NUMBER:
		case EntryDataStore::GEAR_AVG:
		case EntryDataStore::CLIMB_AVG:
		case EntryDataStore::CLIMB_RATE:
			return GEAR_AVG;
		case EntryDataStore::GEAR_HIGH:
		case EntryDataStore::CLIMB_LOW:
			return GEAR_HIGH;
		}
	case 2:
		switch (data_store.sortOrder()) {
		case EntryDataStore::TEAM_NUMBER:
		case EntryDataStore::GEAR_AVG:
		case EntryDataStore::CLIMB_AVG:
		case EntryDataStore::CLIMB_RATE:
			return CLIMB_AVG;
		case EntryDataStore::GEAR_HIGH:
		case EntryDataStore::CLIMB_LOW:
			return CLIMB_LOW;
		}
	case 3:
		return CLIMB_RATE;
	case 4:
		return SELECTABLE;
	}
	return INVALID;
}

QFlags<Qt::AlignmentFlag> TeamListDataModel::columnAlignment(int col) {
	return col == 0 ? Qt::AlignLeft | Qt::AlignVCenter : Qt::AlignCenter;
}

void TeamListDataModel::setSortOrder(EntryDataStore::SortOrder order) {
	data_store.setSortOrder(order);
}
