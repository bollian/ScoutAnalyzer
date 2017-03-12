#ifndef ENTRY_H
#define ENTRY_H

#include <qstring.h>
#include <matchnumber.h>

class Entry
{
public:
	struct Range {
		int low;
		int high;
	};

	Entry();
	QString submitter();
	MatchNumber match();
	int teamNumber();
	bool attended();

	bool autoBaseline();
	bool autoGear();

	/**
	 * @brief about how fast did they shoot balls during autonomous
	 * @return 0 if they didn't shoot, otherwise a number in units of balls/sec
	 */
	int autoHighGoalSpeed();
	Range autoHighGoalAccuracy();
	QString autoComments();

	int teleopGears();
	bool teleopLoadingStation();
	bool teleopGroundGear();
	int teleopHighGoalSpeed();
	Range teleopHighGoalAccuracy();
	Range climbTime();
	QString foulsDescription();
	QString teleopComments();

private:
	QString submitter_name;
	MatchNumber match_number;
	int team_number;
	bool team_attended;

	bool auto_baseline;
	bool auto_gear;
	int auto_high_goal_speed;
	Range auto_high_goal_accuracy;
	QString auto_comments;

	int teleop_gears;
	bool teleop_loading_station;
	bool teleop_ground_gear;
	int teleop_high_goal_speed;
	Range teleop_high_goal_accuracy;
	Range climb_time;
	QString fouls_description;
	QString teleop_comments;
};

#endif // ENTRY_H
