#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include "category.h"
#include <QDialog>
#include <string>
#include <vector>
using std::vector;

namespace Ui {
class UpdateDialog;
}

class UpdateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateDialog(vector<Category> categories, QModelIndex &index, QWidget *parent = nullptr);
    ~UpdateDialog();

    string getAssetName();
    double getAssetCost();
    string getAssetCategory();
    string getAssetDescription();
private slots:
    QDialog::DialogCode on_updateAsset_clicked();

private:
    Ui::UpdateDialog *ui;
    double cost;
};

#endif // UPDATEDIALOG_H
