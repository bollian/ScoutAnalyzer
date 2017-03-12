#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QList>
#include <QMainWindow>
#include <csvfile.h>
#include <row.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

	QFileDialog fdialog;
	CSVFile* csv;
	QList<Row*> rows;

	void showMessage(const QString& message);

private slots:
	void openFilePressed();
	void fileSelected(int status);
};

#endif // MAINWINDOW_H
