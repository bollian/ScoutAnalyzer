#include <qabstractitemmodel.h>
#include <qcombobox.h>
#include <QShowEvent>
#include <entrydatastore.h>
#include <teamlistview.h>
#include <ui_teamlistview.h>

TeamListView::TeamListView(TeamListDataModel* model, QWidget *parent) :
    QWidget(parent),
	ui(new Ui::TeamListView),
	model(model)
{
	ui->setupUi(this);

	ui->sort_combo_box->addItem("Team Number", QVariant(EntryDataStore::TEAM_NUMBER));
	ui->sort_combo_box->addItem("Gear High", QVariant(EntryDataStore::GEAR_HIGH));
	ui->sort_combo_box->addItem("Climb Low", QVariant(EntryDataStore::CLIMB_LOW));
	ui->sort_combo_box->addItem("Gear Average", QVariant(EntryDataStore::GEAR_AVG));
	ui->sort_combo_box->addItem("Climb Average", QVariant(EntryDataStore::CLIMB_AVG));
	ui->sort_combo_box->addItem("Climb Rate", QVariant(EntryDataStore::CLIMB_RATE));
	connect(ui->sort_combo_box, (void(QComboBox::*)(int))(&QComboBox::currentIndexChanged), this, &TeamListView::sortingBoxIndexChanged);

	ui->table->setModel(model);
}

TeamListView::~TeamListView()
{
	delete ui;
}

void TeamListView::showEvent(QShowEvent* event) {
	ui->table->setModel(nullptr);
	ui->table->setModel(model);
}

void TeamListView::sortingBoxIndexChanged(int index) {
	model->setSortOrder((EntryDataStore::SortOrder)ui->sort_combo_box->itemData(index).toInt());
	ui->table->setModel(nullptr);
	ui->table->setModel(model);
}
