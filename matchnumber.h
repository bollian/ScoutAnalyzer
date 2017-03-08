#ifndef MATCHNUMBER_H
#define MATCHNUMBER_H

#include <QString>

class MatchNumber
{
public:
	enum MatchType {
		PRACTICE,
		QUALIFIER,
		QUARTER_FINAL,
		SEMI_FINAL,
		FINAL
	};

	MatchNumber(QString text);
	MatchNumber(int num);

	/**
	 * @brief which match this is
	 * @return an integer greater than 0. 1 for the first match, 77 for the seventy-seventh.
	 */
	int matchNum();

	/**
	 * @brief Indicates which rematch this is.
	 * @return If this isn't a rematch, returns 0.  If it is, returns 1 for the first rematch, 2 for the second, etc.
	 */
	int rematchCount();

	/**
	 * @brief indicates whether the match took place during practice rounds, quarter-finals, semi-finals, or finals
	 * @return an enum value indicating which phase of the competition the match took part in
	 */
	MatchType matchType();

private:
	int number;
	int rematch;
	MatchType type;
};

#endif // MATCHNUMBER_H
