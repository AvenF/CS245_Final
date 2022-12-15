#ifndef ASSETTABLEMODEL_H
#define ASSETTABLEMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include <string>
#include "asset.h"

using std::string;
using std::vector;

class AssetTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit AssetTableModel(QObject *parent = 0);

    // Overrides methods inherited from QAbstractTableModel
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    void removeAsset(int index);

private:
    vector<Asset> assets;   // stores the asset objects
    void createAssets();    // helper function to create a few defualt assets

signals:

public slots:

};

#endif // ASSETTABLEMODEL_H
