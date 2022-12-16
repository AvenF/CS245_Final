#include "updatedialog.h"
#include "ui_updatedialog.h"
#include <QMessageBox>
#include <string>

UpdateDialog::UpdateDialog(vector<Category> categories, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateDialog)
{
    ui->setupUi(this);

    for ( Category c : categories ) {
        ui->assetCategoryCombo->addItem(QString::fromStdString(c.getCategoryName()));
    }
}

UpdateDialog::~UpdateDialog()
{
    delete ui;
}
