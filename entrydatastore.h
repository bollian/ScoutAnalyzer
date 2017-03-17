#ifndef ENTRYDATASTORE_H
#define ENTRYDATASTORE_H

#include <qhash.h>
#include <qobject.h>
#include <qlist.h>
#include <entry.h>

class EntryDataStore : public QObject
{
	Q_OBJECT

public:
	enum SortOrder {
		TEAM_NUMBER,
		GEAR_HIGH,
		CLIMB_LOW,
		GEAR_AVG,
		CLIMB_AVG,
		CLIMB_RATE
	};

	EntryDataStore();
	~EntryDataStore();

	int teamCount() const;
	int sortedTeam(int index) const;


	int gearHigh(int team) const;
	Entry::Range climbLow(int team) const;
	float gearAverage(int team) const;
	float climbAverage(int team) const;
	float climbRate(int team) const;

	void addEntry(Entry* entry);
	Entry* getRow(int row);
	QList<Entry*>* getTeam(int team);

	SortOrder sortOrder() const;
	void setSortOrder(SortOrder order);

private:
	QList<Entry*>* getTeamList(int team) const;
	void sortTeam(int team);

	int gearHigh(QList<Entry*>* entries) const;
	Entry::Range climbLow(QList<Entry*>* entries) const;
	float gearAverage(QList<Entry*>* entries) const;
	float climbAverage(QList<Entry*>* entries) const;

	QList<Entry*> all_entries;
	QHash<int, QList<Entry*>*> team_entries;
	QList<int> sorted_teams;

	SortOrder sort_order;

};

#endif // ENTRYDATASTORE_H
