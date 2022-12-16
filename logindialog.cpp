#include "logindialog.h"
#include "ui_logindialog.h"
#include "mainwindow.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_buttonBox_accepted()
{

    if (ui->usernameBox->text() == "jpgrady" && ui->passwordBox->text() == "cs245C++") {
        accept();
    }
    else if (ui->usernameBox->text().isEmpty() || ui->passwordBox->text().isEmpty()){
        // display a warning
        QMessageBox::warning(
                    this,
                    tr("Alert"),
                    tr("Sorry, but all fields are required.") );
        reject();
    }
    else {
        // display a warning
        QMessageBox::warning(
                    this,
                    tr("Alert"),
                    tr("Sorry, but your username and password do not match. Username = jpgrady | Password = cs245") );
        reject();
    }

}

