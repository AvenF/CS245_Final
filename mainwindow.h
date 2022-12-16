#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
using StandardButton = QMessageBox::StandardButton;
#include <QItemSelection>
#include "assettablemodel.h"
#include "categorytablemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_assetTable_pressed(const QModelIndex &index);

    void on_removeAssetButton_clicked();

    void on_addButton_clicked();

    void on_updateButton_pressed();

    void on_actionAdd_triggered();

    void on_actionUpdate_triggered();

    void on_categoryTable_pressed(const QModelIndex &index);

    void on_removeCategoryButton_clicked();

private:
    Ui::MainWindow *ui;
    AssetTableModel *assetModel;
    CategoryTableModel *categoryModel;
    void openAddDialog();
    void openUpdateDialog();
};
#endif // MAINWINDOW_H
