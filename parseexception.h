#ifndef PARSEEXCEPTION_H
#define PARSEEXCEPTION_H

#include <exception>
#include <qexception.h>
#include <qbytearray.h>

class ParseException : public QException {
public:
	ParseException(const QString& context, int location, const QString& message);
	virtual ~ParseException() throw();

	const QString& context() const;
	int location() const;
	const QString& message() const;

	virtual const char* what() const throw();

private:
	const QString _context;
	int _location;
	const QString _message;

	QByteArray compiled;

};

#endif // PARSEEXCEPTION_H
