#ifndef CATEGORYTABLEMODEL_H
#define CATEGORYTABLEMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include <string>
#include "category.h"

using std::string;
using std::vector;

class CategoryTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit CategoryTableModel(vector<Category> categories, QObject *parent = 0);

    // Overrides methods inherited from QAbstractTableModel
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    void setModelData(vector<Category> updatedCategories);


    void removeCategory(int index);
    vector<Category> getCategories();
    void addCategory(int i, string s);    

private:
    vector<Category> categories;   // stores the category objects

signals:

public slots:

};

#endif // CATEGORYTABLEMODEL_H
