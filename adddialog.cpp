#include "adddialog.h"
#include "ui_adddialog.h"
#include <QMessageBox>
#include <string>

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
}

AddDialog::~AddDialog()
{
    delete ui;
}
