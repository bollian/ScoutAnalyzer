#include <entry.h>

Entry::Entry() :
	match_number(0)
{

}

QString Entry::submitter() {
	return submitter_name;
}

MatchNumber Entry::match() {
	return match_number;
}

int Entry::teamNumber() {
	return team_number;
}

bool Entry::attended() {
	return team_attended;
}

bool Entry::autoBaseline() {
	return auto_baseline;
}

bool Entry::autoGear() {
	return auto_gear;
}

int Entry::autoHighGoalSpeed() {
	return auto_high_goal_speed;
}

Entry::Range Entry::autoHighGoalAccuracy() {
	return auto_high_goal_accuracy;
}

QString Entry::autoComments() {
	return auto_comments;
}

int Entry::teleopGears() {
	return teleop_gears;
}

bool Entry::teleopLoadingStation() {
	return teleop_loading_station;
}

bool Entry::teleopGroundGear() {
	return teleop_ground_gear;
}

int Entry::teleopHighGoalSpeed() {
	return teleop_high_goal_speed;
}

Entry::Range Entry::teleopHighGoalAccuracy() {
	return teleop_high_goal_accuracy;
}

Entry::Range Entry::climbTime() {
	return climb_time;
}

QString Entry::foulsDescription() {
	return fouls_description;
}

QString Entry::teleopComments() {
	return teleop_comments;
}
