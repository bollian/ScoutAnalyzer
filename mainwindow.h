#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qfiledialog.h>
#include <qfile.h>
#include <qmainwindow.h>
#include <csvfile.h>
#include <entrydatastore.h>
#include <entry.h>
#include <messageview.h>
#include <teamlistdatamodel.h>
#include <teamlistview.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private:
	Ui::MainWindow* ui;
	MessageView message_view;

	QFileDialog fdialog;
	CSVFile* csv;

	EntryDataStore data_store;
	TeamListDataModel team_list_data_model;
	TeamListView team_list_view;

	void showMessage(const QString& message);

private slots:
	void openFilePressed();
	void fileSelected(int status);

	void sortingChanged(EntryDataStore::SortOrder new_order);
};

#endif // MAINWINDOW_H
