#include <QTextStream>
#include "parseexception.h"

ParseException::ParseException(const QString& context, int location, const QString& message) :
	_context(context),
	_location(location),
	_message(message) {
	QTextStream(&compiled) << message << " at " << location;
}

ParseException::~ParseException() throw() {}

const QString& ParseException::context() const {
	return _context;
}

int ParseException::location() const {
	return _location;
}

const QString& ParseException::message() const {
	return _message;
}

const char* ParseException::what() const throw() {
	return compiled.data();
}
