#include "adddialog.h"
#include "ui_adddialog.h"
#include <QMessageBox>
#include <cstdlib>

AddDialog::AddDialog(vector<Category> categories, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);

    for ( Category c : categories ) {
        ui->assetCategoryCombo->addItem(QString::fromStdString(c.getCategoryName()));
    }
}

AddDialog::~AddDialog()
{
    delete ui;
}


QDialog::DialogCode AddDialog::on_addCategory_clicked()
{
    // Get data entered by the user
    QString name = ui->categoryNameBox->text();

    // if the one field has a value, we are good...
    if(!name.isEmpty()) {
        // add category to list of categories and close
        accept();
    }

    // otherwise, if the field does NOT have a value...
    else {
        // display a warning
        QMessageBox::warning(
                    this,
                    tr("Alert"),
                    tr("Sorry, but all fields are required.") );
    }

}

string AddDialog::getAssetName() {
    return ui->assetNameBox->text().toStdString();
}

double AddDialog::getAssetCost() {
    return cost;
}

string AddDialog::getAssetCategory() {
    return ui->assetCategoryCombo->currentText().toStdString();
}

string AddDialog::getAssetDescription() {
    return ui->assetDescriptionText->toPlainText().toStdString();
}

string AddDialog::getCategoryName() {
    return ui->categoryNameBox->text().toStdString();
}

void AddDialog::on_addAsset_clicked()
{
    // Get data entered by the user
    QString name = ui->assetNameBox->text();
    QString category = ui->assetCategoryCombo->currentText();
    QString description = ui->assetDescriptionText->toPlainText();
    double cost;

    ui->assetCostBox->setValidator(new QDoubleValidator(this));
    if (ui->assetCostBox->text().isEmpty())
        cost = std::numeric_limits<double>::signaling_NaN();
    else
        cost = ui->assetCostBox->text().toDouble();

    this->cost = cost;

    /*QString qStr = ui->assetCostBox->text();
    bool doub = true;
    for (char c : qStr.toStdString()) {

    }
    else {
        QMessageBox::warning(
                    this,
                    tr("Alert"),
                    tr("Sorry, but the 'cost' field input must be numeric.")    );
    }*/

    // exception the description, if all fields have values, we are good...
    if(!name.isEmpty() && !category.isEmpty()) {
        // add category to list of categories and close
        accept();
    }

    // otherwise, if the fields do NOT have a value...
    else {
        // display a warning
        QMessageBox::warning(
                    this,
                    tr("Alert"),
                    tr("Sorry, but all fields are required.") );
    }
}
