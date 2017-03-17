#ifndef TEAMLISTVIEW_H
#define TEAMLISTVIEW_H

#include <qwidget.h>
#include <entrydatastore.h>
#include <teamlistdatamodel.h>

namespace Ui {
class TeamListView;
}

class TeamListView : public QWidget
{
	Q_OBJECT

public:
	explicit TeamListView(TeamListDataModel* model, QWidget *parent = 0);
	~TeamListView();

private:
	void showEvent(QShowEvent* event);

	Ui::TeamListView *ui;
	TeamListDataModel* model;

private slots:
	void sortingBoxIndexChanged(int index);

};

#endif // TEAMLISTVIEW_H
