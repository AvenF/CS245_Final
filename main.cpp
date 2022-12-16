#include "logindialog.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    LoginDialog ld;
    ld.show();

    if (ld.exec() == QDialog::Accepted) {
        w.show();
        return a.exec();
    }
}
