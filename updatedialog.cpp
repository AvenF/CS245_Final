#include "updatedialog.h"
#include "ui_updatedialog.h"
#include <QMessageBox>
#include <string>

UpdateDialog::UpdateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateDialog)
{
    ui->setupUi(this);
}

UpdateDialog::~UpdateDialog()
{
    delete ui;
}
