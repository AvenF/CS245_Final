#include "mainwindow.h"
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

