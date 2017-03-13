#include <entry.h>

Entry::Entry(const QHash<QString, int>& index, const QList<QString>& row) :
	submitter_name(getColumn("Name", index, row)),
	match_number(getColumn("Match number", index, row)),
	team_number(-1),
	team_attended(getColumn("Attendance", index, row) == "On Field"),
	auto_baseline(getColumn("Cross Baseline", index, row) == "Yes"),
	auto_gear(getColumn("Delivered Gear", index, row) == "Yes"),
	auto_high_goal_speed(-1),
	auto_high_goal_accuracy(Range{-1, -1}),
	auto_comments(getColumn("Auto Comments", index, row)),
	teleop_gears(-1),
	teleop_loading_station(false),
	teleop_ground_gear(false),
	teleop_high_goal_speed(-1),
	teleop_high_goal_accuracy(Range{-1, -1}),
	climb_time(Range{-1, -1}),
	fouls_description(getColumn("Fouls", index, row)),
	teleop_comments(getColumn("General Comments", index, row)) {

	bool ok;
	team_number = getColumn("Team", index, row).toInt(&ok);
	if (!ok) {
		team_number = -1;
	}

	auto_high_goal_speed = parseSpeed(getColumn("Auto High Goal Speed", index, row).toLower());
	auto_high_goal_accuracy = parseAccuracy(getColumn("Auto High Goal Accuracy", index, row).toLower());

	QString tmp = getColumn("Gears", index, row).toLower();
	teleop_gears = tmp.toInt(&ok);
	if (!ok) {
		if (tmp == "13 or more") {
			teleop_gears = 13;
		} else {
			teleop_gears = -1;
		}
	}

	tmp = getColumn("How do they receive gears?", index, row).toLower();
	if (tmp.contains("loading station")) {
		teleop_loading_station = true;
	}
	if (tmp.contains("ground pickup")) {
		teleop_ground_gear = true;
	}

	teleop_high_goal_speed = parseSpeed(getColumn("High Goal Speed", index, row).toLower());
	teleop_high_goal_accuracy = parseAccuracy(getColumn("High Goal Accuracy", index, row).toLower());

	tmp = getColumn("How long did they take to climb?", index, row).toLower();
	if (tmp == "" || tmp == "they didn't climb") {
		climb_time = Range{0, 0};
	} else if (tmp == "0-5 seconds") {
		climb_time = Range{0, 5};
	} else if (tmp == "5-10 seconds") {
		climb_time = Range{5, 10};
	} else if (tmp == "10-15 seconds") {
		climb_time = Range{10, 15};
	} else if (tmp == "15-25 seconds") {
		climb_time = Range{15, 25};
	} else if (tmp == "more than 25 seconds") {
		climb_time = Range{25, 30};
	} else {
		// tmp == something we don't recognize
		climb_time = Range{-1, -1};
	}
}

QString Entry::submitter() const {
	return submitter_name;
}

MatchNumber Entry::match() const {
	return match_number;
}

int Entry::teamNumber() const {
	return team_number;
}

bool Entry::attended() const {
	return team_attended;
}

bool Entry::autoBaseline() const {
	return auto_baseline;
}

bool Entry::autoGear() const {
	return auto_gear;
}

int Entry::autoHighGoalSpeed() const {
	return auto_high_goal_speed;
}

Entry::Range Entry::autoHighGoalAccuracy() const {
	return auto_high_goal_accuracy;
}

QString Entry::autoComments() const {
	return auto_comments;
}

int Entry::teleopGears() const {
	return teleop_gears;
}

bool Entry::teleopLoadingStation() const {
	return teleop_loading_station;
}

bool Entry::teleopGroundGear() const {
	return teleop_ground_gear;
}

int Entry::teleopHighGoalSpeed() const {
	return teleop_high_goal_speed;
}

Entry::Range Entry::teleopHighGoalAccuracy() const {
	return teleop_high_goal_accuracy;
}

Entry::Range Entry::climbTime() const {
	return climb_time;
}

QString Entry::foulsDescription() const {
	return fouls_description;
}

QString Entry::teleopComments() const {
	return teleop_comments;
}

QString Entry::getColumn(const QString& name, const QHash<QString, int>& index, const QList<QString>& row) {
	return row.value(index.value(name, -1));
}

int Entry::parseSpeed(const QString& speed) {
	if (speed == "" || speed == "none attempted") {
		return 0;
	} else if (speed == "slow (up to 1 ball per second)") {
		return 1;
	} else if (speed == "moderate (around 2 balls per second)") {
		return 2;
	} else if (speed == "high (3 or more balls per second)") {
		return 3;
	}
	// else speed == something unrecognized
	return -1;
}

Entry::Range Entry::parseAccuracy(const QString &text) {
	if (text == "" || text == "none attempted") {
		return Range{0, 0};
	} else if (text == "0% - 25%") {
		return Range{0, 25};
	} else if (text == "25% - 50%") {
		return Range{25, 50};
	} else if (text == "50% - 75%") {
		return Range{50, 75};
	} else if (text == "75% - 100%") {
		return Range{75, 100};
	}
	// else tmp == something unrecognized
	return Range{-1, -1};
}
