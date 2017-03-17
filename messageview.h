#ifndef MESSAGEVIEW_H
#define MESSAGEVIEW_H

#include <qstring.h>
#include <qwidget.h>

namespace Ui {
class MessageView;
}

class MessageView : public QWidget
{
	Q_OBJECT

public:
	explicit MessageView(QWidget *parent = 0);
	~MessageView();

	void setMessage(const QString& msg);
	QString message() const;

signals:
	void clicked(bool clicked = false);

private:
	Ui::MessageView *ui;
};

#endif // MESSAGEVIEW_H
