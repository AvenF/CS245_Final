#include "updatedialog.h"
#include "ui_updatedialog.h"
#include <QMessageBox>
#include <string>

UpdateDialog::UpdateDialog(vector<Category> categories, QModelIndex &index, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateDialog)
{
    ui->setupUi(this);

    for ( Category c : categories ) {
        ui->assetCategoryCombo->addItem(QString::fromStdString(c.getCategoryName()));
    }

    int row = index.row();

    ui->assetNameBox->setText(index.sibling(row,1).data().toString());
    ui->assetCostBox->setText(index.sibling(row,2).data().toString());
    ui->assetCategoryCombo->setCurrentText(index.sibling(row,3).data().toString());
    ui->assetDescriptionText->setPlainText(index.sibling(row,4).data().toString());
}

UpdateDialog::~UpdateDialog()
{
    delete ui;
}

string UpdateDialog::getAssetName() {
    return ui->assetNameBox->text().toStdString();
}

double UpdateDialog::getAssetCost() {
    return cost;
}

string UpdateDialog::getAssetCategory() {
    return ui->assetCategoryCombo->currentText().toStdString();
}

string UpdateDialog::getAssetDescription() {
    return ui->assetDescriptionText->toPlainText().toStdString();
}

QDialog::DialogCode UpdateDialog::on_updateAsset_clicked()
{
    // Get data entered by the user
    QString name = ui->assetNameBox->text();
    QString category = ui->assetCategoryCombo->currentText();
    QString description = ui->assetDescriptionText->toPlainText();
    double cost;

    ui->assetCostBox->setValidator(new QDoubleValidator(this));
    if (ui->assetCostBox->text().isEmpty())
        cost = std::numeric_limits<double>::signaling_NaN();
    else {
        cost = ui->assetCostBox->text().toDouble();
    }

    this->cost = cost;

    // return QDialog::Accepted
    accept();
}
