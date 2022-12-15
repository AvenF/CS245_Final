#include "mainwindow.h"
#include "adddialog.h"
#include "updatedialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create new user model & apply it to the table view
    assetModel = new AssetTableModel(this);
    ui->assetTable->setModel(assetModel);

    // Set the table view to allow the columns to expand
    ui->assetTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Stretch the columns' headers to fit the width of the table view
    ui->assetTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Resize the columns
    ui->assetTable->resizeColumnsToContents();

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
    ui->removeButton->setEnabled(true);
    ui->actionRemove->setEnabled(true);
}

// Currently removes items from asset table
// VERY VERY IMPORTANT: REQUIRES LOGIC FOR REMOVING FROM CATEGORY LIST AS WELL, I WOULD LIKE THESE TWO FUNCTIONS TO BE IN THE SAME BUTTON
void MainWindow::on_removeButton_clicked()
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
        // tell the AssetTableModel to delete the Asset at index 'row'
        assetModel->removeAsset(row);

        // clear any selections in the assetTable
        ui->assetTable->selectionModel()->clearSelection();
    }
}


void MainWindow::on_actionRemove_triggered()
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
        // tell the AssetTableModel to delete the Asset at index 'row'
        assetModel->removeAsset(row);

        // clear any selections in the assetTable
        ui->assetTable->selectionModel()->clearSelection();
    }
}

// Just a shell awaiting actual code implementation
void MainWindow::on_addButton_clicked()
{
    AddDialog ad(this);
    ad.setModal(true);

    ad.show();
    if(ad.exec( )== QDialog::Accepted) {

    }
}

// Just a shell awaiting actual code implementation
void MainWindow::on_updateButton_pressed()
{
    UpdateDialog ud(this);
    ud.setModal(true);

    ud.show();
    if(ud.exec( )== QDialog::Accepted) {

    }
}


void MainWindow::on_actionAdd_triggered()
{
    AddDialog ad(this);
    ad.setModal(true);

    ad.show();
    if(ad.exec( )== QDialog::Accepted) {

    }
}


void MainWindow::on_actionUpdate_triggered()
{
    UpdateDialog ud(this);
    ud.setModal(true);

    ud.show();
    if(ud.exec( )== QDialog::Accepted) {

    }
}

