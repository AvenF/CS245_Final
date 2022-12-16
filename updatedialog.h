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
    explicit UpdateDialog(vector<Category> categories, QWidget *parent = nullptr);
    ~UpdateDialog();

private:
    Ui::UpdateDialog *ui;
};

#endif // UPDATEDIALOG_H
