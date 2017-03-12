// standard #includes come first, then qt, then local.  #includes should be in alphabetical order.
// all header names should be lowercase
#include <bitset> // standard
#include <iostream> // standard
#include <vector> // standard
#include <qstring.h> // qt (note that qstring.h was used, not QString)
#include <scoutanalyzerheader.h> // local

using namespace std; // feel free to use using statements, just not in headers

// pointer(*) and reference(&) type identifiers go next to the type name, in this case char
int main(int argc, char* argv) { // brackets don't get their own line and have a space before them
	if (true) { // put spaces before and after the parentheses in if, while, for, switch, and catch statements (and any other control statements)
		int six = 5 + 1; // space out operators
	} else { // else, catch, finally, etc. clauses go on the same line as the preceding bracket

	}
}

// type names are camel-cased, first letter upper
class Family {
public: // access modifiers aren't tabbed
	int haveReunion(); // function names are camel-cased, first letter lowercased
	int lastName(); // don't prepend getters with "get" (e.g. this shouldn't be getLastName)

private:
	int last_name; // variable names are underscored and are generally private

};

class BigFamily : public Family {
private:
	// creating a typedef of the parent class called 'super' is a pretty good idea, but make it private
	typedef Family super;

public:
	int lastName() {
		return super::lastName();
	}

};
