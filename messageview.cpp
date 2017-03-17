#include <qpushbutton.h>
#include <messageview.h>
#include <ui_messageview.h>

MessageView::MessageView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageView)
{
	ui->setupUi(this);

	connect(ui->open_file_button, &QPushButton::clicked, this, &MessageView::clicked);
}

MessageView::~MessageView()
{
	delete ui;
}

void MessageView::setMessage(const QString& msg) {
	ui->message_label->setText(msg);
}

QString MessageView::message() const {
	return ui->message_label->text();
}
