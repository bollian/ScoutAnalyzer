#include "entrydatastore.h"

EntryDataStore::EntryDataStore() :
	all_entries(),
	team_entries(),
	sorted_teams(),
	sort_order(TEAM_NUMBER) {}

EntryDataStore::~EntryDataStore() {
	for (int i = 0; i < all_entries.length(); ++i) {
		delete all_entries[i];
	}
	for (auto i = team_entries.begin(); i != team_entries.end(); ++i) {
		delete i.value();
	}
}

void EntryDataStore::addEntry(Entry* entry) {
	all_entries.append(entry);

	auto iterator = team_entries.find(entry->teamNumber());
	if (iterator == team_entries.end()) {
		// the team hasn't been added to the qhash
		QList<Entry*>* entry_list = new QList<Entry*>();
		entry_list->append(entry);
		iterator = team_entries.insert(entry->teamNumber(), entry_list);
	} else {
		// there's already a list for the team
		iterator.value()->append(entry);
	}

	sortTeam(entry->teamNumber());
}

int EntryDataStore::teamCount() const {
	return sorted_teams.length();
}

int EntryDataStore::sortedTeam(int index) const {
	return sorted_teams.value(index, -1);
}

int EntryDataStore::gearHigh(int team) const {
	QList<Entry*>* team_list = getTeamList(team);
	if (team_list == nullptr) {
		return -1;
	}

	int high = -1;
	int possibility;
	for (int i = 0; i < team_list->length(); ++i) {
		possibility = team_list->at(i)->teleopGears();
		if (possibility > high) {
			high = possibility;
		}
	}
	return high;
}

Entry::Range EntryDataStore::climbLow(int team) const {
	QList<Entry*>* team_list = getTeamList(team);
	if (team_list == nullptr) {
		return {-1, -1};
	}

	Entry::Range low = {9999, 9999};
	Entry::Range possibility;
	for (int i = 0; i < team_list->length(); ++i) {
		possibility = team_list->at(i)->climbTime();
		if (possibility.high < low.high && possibility.high != 0) {
			low = possibility;
		}
	}
	return low;
}

float EntryDataStore::gearAverage(int team) const {
	QList<Entry*>* team_list = getTeamList(team);
	if (team_list == nullptr) {
		return -1.0;
	}

	int total = 0;
	int entry_count = team_list->length();
	int possibility;
	for (int i = 0; i < team_list->length(); ++i) {
		possibility = team_list->at(i)->teleopGears();
		if (possibility == -1) { // check to see if the entry was valid
			--entry_count;
		} else {
			total += possibility;
		}
	}
	if (entry_count == 0) {
		return 0.0;
	}
	return (float)total / (float)entry_count;
}

float EntryDataStore::climbAverage(int team) const {
	QList<Entry*>* team_list = getTeamList(team);
	if (team_list == nullptr) {
		return -1.0;
	}

	int total = 0;
	int entry_count = team_list->length();
	Entry::Range possibility;
	for (int i = 0; i < team_list->length(); ++i) {
		possibility = team_list->at(i)->climbTime();
		if (possibility.high == -1 || possibility.high == 0) {
			// don't include invalid entries and entries where they didn't climb
			--entry_count;
		} else {
			total += possibility.low + possibility.high;
		}
	}
	if (entry_count == 0) {
		return 99.0; // they've never successfully climbed
	}
	return (float)total / (float)entry_count / 2.0; // halved because there are two values for each entry
}

float EntryDataStore::climbRate(int team) const {
	QList<Entry*>* team_list = getTeamList(team);
	if (team_list == nullptr) {
		return -1.0;
	}

	int climb_count = 0;
	Entry::Range possibility;
	for (int i = 0; i < team_list->length(); ++i) {
		possibility = team_list->at(i)->climbTime();
		if (!(possibility.high == 0 || possibility.high == -1)) {
			++climb_count;
		}
	}
	return (float)climb_count / (float)team_list->length();
}

QList<Entry*>* EntryDataStore::getTeamList(int team) const {
	auto i = team_entries.find(team);
	if (i == team_entries.end()) {
		return nullptr;
	}
	return *i;
}

EntryDataStore::SortOrder EntryDataStore::sortOrder() const {
	return sort_order;
}

void EntryDataStore::setSortOrder(SortOrder order) {
	sort_order = order;
	sorted_teams.clear();
	for (auto i = team_entries.begin(); i != team_entries.end(); ++i) {
		sortTeam(i.key());
	}
}


void EntryDataStore::sortTeam(int team) {
	Entry::Range climb_low;
	float some_average;
	switch (sort_order) {
	case TEAM_NUMBER:
		break;
	case GEAR_HIGH:
		some_average = gearHigh(team);
		break;
	case CLIMB_LOW:
		climb_low = climbLow(team);
		break;
	case GEAR_AVG:
		some_average = gearAverage(team);
		break;
	case CLIMB_AVG:
		some_average = climbAverage(team);
		break;
	case CLIMB_RATE:
		some_average = climbRate(team);
		break;
	}

	int bottom = 0; // inclusive bottom of the binary search
	int top = sorted_teams.length(); // exclusive top of the binary search
	int search_index = 0;
	while (bottom != top) {
		search_index = (bottom + top) / 2;
		switch (sort_order) {
		case TEAM_NUMBER:
			if (team < sorted_teams[search_index]) {
				top = search_index;
			} else {
				bottom = search_index + 1;
			}
			break;
		case GEAR_HIGH:
			if (some_average > gearHigh(sorted_teams[search_index])) {
				top = search_index;
			} else {
				bottom = search_index + 1;
			}
			break;
		case CLIMB_LOW:
			if (climb_low.high < climbLow(sorted_teams[search_index]).high) {
				top = search_index;
			} else {
				bottom = search_index + 1;
			}
			break;
		case GEAR_AVG:
			if (some_average > gearAverage(sorted_teams[search_index])) {
				top = search_index;
			} else {
				bottom = search_index + 1;
			}
			break;
		case CLIMB_AVG:
			if (some_average < climbAverage(sorted_teams[search_index])) {
				top = search_index;
			} else {
				bottom = search_index + 1;
			}
			break;
		case CLIMB_RATE:
			if (some_average > climbRate(sorted_teams[search_index])) {
				top = search_index;
			} else {
				bottom = search_index + 1;
			}
			break;
		}
	}
	int old_index = sorted_teams.indexOf(team);
	if (old_index == -1) {
		sorted_teams.insert(bottom, team);
	} else {
		if (bottom == sorted_teams.length()) {
			sorted_teams.takeAt(old_index);
			sorted_teams.append(team);
		} else {
			sorted_teams.move(old_index, bottom);
		}
	}
}
