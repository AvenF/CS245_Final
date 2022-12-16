#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <string>
#include <vector>
using std::vector;
#include "categorytablemodel.h"

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(vector<Category> categories, QWidget *parent = nullptr);
    ~AddDialog();

    string getAssetName();
    double getAssetCost();
    string getAssetCategory();
    string getAssetDescription();
    string getCategoryName();

private slots:
    QDialog::DialogCode on_addCategory_clicked();

    void on_addAsset_clicked();

private:
    Ui::AddDialog *ui;
    double cost;
};

#endif // ADDDIALOG_H
