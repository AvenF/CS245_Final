#include "mainwindow.h"
#include "adddialog.h"
#include "updatedialog.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include "datamanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create new asset / category models & apply them to the table view
    assetModel = new AssetTableModel(dm.getAssets(), this);
    ui->assetTable->setModel(assetModel);

    categoryModel = new CategoryTableModel(dm.getCategories(), this);
    ui->categoryTable->setModel(categoryModel);

    // Set the table view to allow the columns to expand
    ui->assetTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->categoryTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Stretch the columns' headers to fit the width of the table view
    ui->assetTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->categoryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Resize the columns
    ui->assetTable->resizeColumnsToContents();
    ui->categoryTable->resizeColumnsToContents();

}

MainWindow::~MainWindow()
{
    // Be sure to delete the model
    delete assetModel;
    delete ui;

}


void MainWindow::on_actionExit_triggered()
{
    exit(1);
}



void MainWindow::on_assetTable_pressed(const QModelIndex &index)
{
    ui->removeCategoryButton->setEnabled(false);
    ui->removeAssetButton->setEnabled(true);
}

// Currently removes items from asset table
// VERY VERY IMPORTANT: REQUIRES LOGIC FOR REMOVING FROM CATEGORY LIST AS WELL, I WOULD LIKE THESE TWO FUNCTIONS TO BE IN THE SAME BUTTON
void MainWindow::on_removeAssetButton_clicked()
{
    // what Asset will we delete?  check the assetTable's selection!
    QModelIndex index = ui->assetTable->selectionModel()->currentIndex();
    int row = index.row();

    // verify that the end user wants to delete the selected Asset;
    // displays a standard Yes|No QMessageBox
    StandardButton reply;
    reply = QMessageBox::question(this, "Remove Asset", "Are you sure you want to remove this asset from the database?",
                                  QMessageBox::Yes|QMessageBox::No);

    // if yes, remove the asset
    if (reply == QMessageBox::Yes)
    {
        this->dm.removeAssetFromDB(index.sibling(row,0).data().toInt());

        // tell the AssetTableModel to delete the Asset at index 'row'
        assetModel->removeAsset(row);

        // clear any selections in the assetTable
        ui->assetTable->selectionModel()->clearSelection();

    }
}

// Just a shell awaiting actual code implementation
void MainWindow::on_addButton_clicked()
{
    this->openAddDialog();
}

// Just a shell awaiting actual code implementation
void MainWindow::on_updateButton_pressed()
{
    this->openUpdateDialog();
}


void MainWindow::on_actionAdd_triggered()
{
    this->openAddDialog();
}


void MainWindow::on_actionUpdate_triggered()
{
    this->openUpdateDialog();
}


void MainWindow::on_categoryTable_pressed(const QModelIndex &index)
{
    ui->removeAssetButton->setEnabled(false);
    ui->removeCategoryButton->setEnabled(true);
}


void MainWindow::on_removeCategoryButton_clicked()
{
    // what Category will we delete?  check the categoryTable's selection!
    QModelIndex index = ui->categoryTable->selectionModel()->currentIndex();
    int row = index.row();

    // verify that the end user wants to delete the selected Asset;
    // displays a standard Yes|No QMessageBox
    StandardButton reply;
    reply = QMessageBox::question(this, "Remove Category", "Are you sure you want to remove this category from the database? All assets within the category will be deleted!",
                                  QMessageBox::Yes|QMessageBox::No);

    // if yes, remove the asset
    if (reply == QMessageBox::Yes)
    {
        this->dm.removeCategoryFromDB(index.sibling(row,0).data().toString().toStdString());
        // tell the AssetTableModel to delete the Asset at index 'row'
        categoryModel->removeCategory(row);

        // clear any selections in the assetTable
        ui->categoryTable->selectionModel()->clearSelection();

        this->assetModel->setModelData(this->dm.getAssets());
    }
}

void MainWindow::openAddDialog() {

    AddDialog ad(categoryModel->getCategories(), this);
    ad.setModal(true);


    ad.show();
    if(ad.exec( )== QDialog::Accepted) {
        if (!ad.getCategoryName().empty()) {
            string cName = ad.getCategoryName();
            this->dm.addCategoryToDB(cName);
            categoryModel->setModelData(this->dm.getCategories());
        }
        else {
            string aName = ad.getAssetName();
            double aCost = ad.getAssetCost();
            string aCat = ad.getAssetCategory();
            string aDesc = ad.getAssetDescription();
            unsigned id = ad.getAssetID();
            this->dm.addAssetToDB(aName, aCost, aCat, aDesc, id);
            assetModel->setModelData(this->dm.getAssets());
        }
    }
}

void MainWindow::openUpdateDialog() {

    // what Asset will we update?  check the assetTable's selection!
    QModelIndex index = ui->assetTable->selectionModel()->currentIndex();
    int row = index.row();
    vector<Category> categories = this->dm.getCategories();

    UpdateDialog ud(categories, index, this);
    ud.setModal(true);

    ud.show();
    if(ud.exec( )== QDialog::Accepted) {
        string aName = ud.getAssetName();
        double aCost = ud.getAssetCost();
        string aCat = ud.getAssetCategory();
        string aDesc = ud.getAssetDescription();

        int id = index.sibling(row,0).data().toInt();
        this->dm.updateAssetInDB(aName, aCost, aCat, aDesc, id);
        this->assetModel->setModelData(this->dm.getAssets());
    }

}

void MainWindow::on_searchBar_returnPressed()
{
    this->dm.searchAssets(ui->searchBar->text().toStdString());
    this->assetModel->setModelData(this->dm.getAssets());
}

