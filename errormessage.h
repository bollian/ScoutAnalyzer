#ifndef ERRORMESSAGE_H
#define ERRORMESSAGE_H

#include <QWidget>

namespace Ui {
class ErrorMessage;
}

class MessageView : public QWidget
{
	Q_OBJECT

public:
	explicit MessageView(const QString& m, QWidget *parent = 0);
	~MessageView();

	const QString& message();
	void setMessage(const QString& m);

private:
	Ui::ErrorMessage *ui;

	QString msg;
};

#endif // ERRORMESSAGE_H
