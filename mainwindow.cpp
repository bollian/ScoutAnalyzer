#include <iostream>
#include <exception>
#include <qlabel.h>
#include <qhash.h>
#include <mainwindow.h>
#include <parseexception.h>
#include <ui_mainwindow.h>

using namespace std;

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow),
	message_view(this),
	fdialog(),
	csv(NULL),
	data_store(),
	team_list_data_model(data_store, this->font()),
	team_list_view(&team_list_data_model) {
	ui->setupUi(this);
	ui->verticalLayout->addWidget(&message_view);
	showMessage("Please select a spreadsheet.");

	team_list_view.hide();
	ui->verticalLayout->addWidget(&team_list_view);

	fdialog.setFilter(QDir::AllDirs | QDir::Files | QDir::NoDot | QDir::NoDotDot);
	fdialog.setNameFilter("Spreadsheet (*.csv)");

	connect(&fdialog, &QFileDialog::finished, this, &MainWindow::fileSelected);
	connect(&message_view, &MessageView::clicked, this, &MainWindow::openFilePressed);
}

MainWindow::~MainWindow() {
    delete ui;
	if (csv != NULL) {
		csv->close();
		delete csv;
	}
}

void MainWindow::fileSelected(int status) {
	if (status == QDialog::Accepted) {
		QFileInfo info(fdialog.selectedFiles()[0]);
		if (info.isReadable()) {
			if (csv != NULL) {
				csv->close();
				delete csv;
			}
			csv = new CSVFile(info.filePath());
			if (!csv->open()) {
				showMessage("Failed to open file.  Please try again.");
			} else {
				showMessage("opened file");
			}

			QHash<QString, int> header_index;
			QList<QString> row;
			bool more = false;
			try {
				more = csv->readRow(row);
				for (int i = 0; i < row.length(); ++i) {
					header_index.insert(row[i], i);
				}

				while (more) {
					row.clear();
					more = csv->readRow(row);
					data_store.addEntry(new Entry(header_index, row));
				}

				message_view.hide();
				team_list_view.show();
			} catch (ParseException& e) {
				showMessage("There was an issue with the CSV file (" + e.message() + "): " + e.context());
			} catch (exception& e) {
				showMessage("An unexpected error occured: " + QString(e.what()));
			}
		} else {
			showMessage("The file you selected isn't readable.  Please select another file.");
		}
	} else {
		showMessage("Please select a spreadsheet.");
	}
}

void MainWindow::showMessage(const QString& message) {
	message_view.setMessage(message);
	message_view.show();
}

void MainWindow::openFilePressed() {
	fdialog.show();
}

void MainWindow::sortingChanged(EntryDataStore::SortOrder new_order) {
	data_store.setSortOrder(new_order);
}
