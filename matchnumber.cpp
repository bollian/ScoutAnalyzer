#include <exception>
#include <matchnumber.h>

MatchNumber::MatchNumber(const QString& text) :
	number(0),
	rematch(0),
	type(MatchNumber::QUALIFIER) {
	int parse_start = 1;
	if (text.startsWith("P")) {
		type = MatchNumber::PRACTICE;
	} else if (text.startsWith("Q")) {
		type = MatchNumber::QUARTER_FINAL;
	} else if (text.startsWith("S")) {
		type = MatchNumber::SEMI_FINAL;
	} else if (text.startsWith("F")) {
		type = MatchNumber::FINAL;
	} else {
		type = MatchNumber::QUALIFIER;
		parse_start = 0;
	}

	// count the number of 'R's at the end of the string.  that's the rematch number
	if (text.length() > 0) {
		for (int i = text.length() - 1; text[i] == 'R'; --i, ++rematch);
	}

	bool ok = false;
	number = text.mid(parse_start, text.length() - parse_start - rematch).toInt(&ok);
	if (!ok) {
		number = -1;
	}
}

MatchNumber::MatchNumber(int num) :
	number(num),
	rematch(0),
	type(MatchNumber::QUALIFIER) {}

int MatchNumber::matchNum() {
	return number;
}

int MatchNumber::rematchCount() {
	return rematch;
}

MatchNumber::MatchType MatchNumber::matchType() {
	return type;
}
