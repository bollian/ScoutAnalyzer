#ifndef ENTRY_H
#define ENTRY_H

#include <qlist.h>
#include <qhash.h>
#include <qstring.h>
#include <matchnumber.h>

class Entry
{
public:
	struct Range {
		int low;
		int high;
	};

	Entry(const QHash<QString, int>& index, const QList<QString>& row);

	QString submitter() const;
	MatchNumber match() const;
	int teamNumber() const;
	bool attended() const;

	bool autoBaseline() const;
	bool autoGear() const;

	/**
	 * @brief about how fast did they shoot balls during autonomous
	 * @return 0 if they didn't shoot, otherwise a number in units of balls/sec
	 */
	int autoHighGoalSpeed() const;
	Range autoHighGoalAccuracy() const;
	QString autoComments() const;

	int teleopGears() const;
	bool teleopLoadingStation() const;
	bool teleopGroundGear() const;
	int teleopHighGoalSpeed() const;
	Range teleopHighGoalAccuracy() const;
	Range climbTime() const;
	QString foulsDescription() const;
	QString teleopComments() const;

private:
	static QString getColumn(const QString& name, const QHash<QString, int>& index, const QList<QString>& row);
	static Range parseAccuracy(const QString& text);
	static int parseSpeed(const QString& speed);

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
