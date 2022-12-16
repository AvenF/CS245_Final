#include "assettablemodel.h"
#include <QColor>
#include <QFont>
#include "asset.h"
#include "qbrush.h"

using std::vector;

AssetTableModel::AssetTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    this->createAssets();
}

void AssetTableModel::createAssets() {
    // Create 3 asset objects
    Asset asset1("11th gen intel processor", 1, 209.99, "CPU", "");
    Asset asset2("500 watt samsung power supply", 2, 79.99, "PSU", "Gold-rated, refurbished");
    Asset asset3("Hyperx Quadcast S", 3, 129.99, "Mic", "");

    // Add them to the assets vector
    assets.push_back(asset1);
    assets.push_back(asset2);
    assets.push_back(asset3);
}

QVariant AssetTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        // Set the column (Qt::Horizontal) headers
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return QString("Asset ID");
            case 1:
                return QString("Name");
            case 2:
                return QString("Cost");
            case 3:
                return QString("Category");
            case 4:
                return QString("Description");
            }
        }
    }
    return QVariant();
}

int AssetTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return static_cast<int>(assets.size()); // # of rows in table?
}

int AssetTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return 5; // Number of data members to display to user in table
}

QVariant AssetTableModel::data(const QModelIndex &index, int role) const
{
    // Get the row and column numbers from the given index (QModelIndex)
    int row = index.row();
    int col = index.column();

    // Qt::DisplayRole -> what data do we display and in what columns?
    if (role == Qt::DisplayRole) {
        switch (col) {
        case 0: // id column
            return QString::fromStdString(std::to_string(assets[row].getID()));
        case 1: // name column
            return QString::fromStdString(assets[row].getName());
        case 2: // cost column
            return QString::fromStdString(std::to_string(assets[row].getCost()));
        case 3: // category column
            return QString::fromStdString(assets[row].getCategory());
        case 4: // description column
            return QString::fromStdString(assets[row].getDescription());
        }
    }

    // Qt::FontRole -> manages the fonts and font styles used in the View
    else if (role == Qt::FontRole)
    {
        // Bold the text in the first column
        if (col == 0) {
            QFont boldFont;
            boldFont.setBold(true);
            return boldFont;
        }
    }

    // Qt::ForegroundRole -> paints the foreground (text) colors
    else if (role == Qt::ForegroundRole)
    {
        // Paint the text red in the Password column
        if (col == 1) {
           return QBrush(QColor(255,0,0));
        }
    }

    // Qt::TextAlignRole -> controls how data is aligned inside cells
    else if(role == Qt::TextAlignmentRole)
    {
        // All columns after the Username column should be right-aligned
        // horizontally, and centered vertically.
        if (col > 0)
        {
            return int(Qt::AlignRight | Qt::AlignVCenter);
        }
    }
    return QVariant();
}

bool AssetTableModel::setData(QModelIndex const& idx, QVariant const & /*value*/, int role) {

    // Qt::EditRole: manages changes in the model
    if (Qt::EditRole == role) {
        // Get the top left and bottom right indices of the cells in our update range
        QModelIndex topLeft = idx;
        QModelIndex bottomRight = index(this->rowCount() - 1, this->columnCount() - 1);

        // VERY IMPORTANT - emit events telling all listening event handlers
        // that both the data (from cell 0,0 to the end) AND the layout have changed
        emit dataChanged(topLeft, bottomRight);
        emit layoutChanged();

        return true;
    }

    return false;
}

/*
 * deletes the Asset at the given 0index from the user data
 */
void AssetTableModel::removeAsset(int index)
{
    // erases the Asset at position 'index' in the vector.
    assets.erase(assets.begin() + index);

    /*
     * NOTE: vector::erase() uses an iterator as an argument.
     * We grab the begin() iterator of 'users', then advance by
     * 'index' number of elements to get to the User object
     * we want to remove.
     */

    // VERY IMPORTANT - call setData to trigger the update of the model and view
    this->setData(this->index(0,0), 0);
}

void AssetTableModel::addAsset(string name, double cost, string cat, string desc) {
    Asset a(name, 4, cost, cat, desc);
    assets.push_back(a);

    // VERY IMPORTANT - call setData to trigger the update of the model and view
    this->setData(this->index(0,0), 0);
}

void AssetTableModel::updateAsset(string &name, double &cost, string &cat, string &desc, const int &id) {
    for (Asset &a : assets) {
        if (a.getID() == id) {
            a.setName(name);
            a.setCost(cost);
            a.setCategory(cat);

            if (!desc.empty()) {
                a.setDescription(desc);
            }
        }
    }

    // VERY IMPORTANT - call setData to trigger the update of the model and view
    this->setData(this->index(0,0), 0);
}

void AssetTableModel::searchAsset(string s) {
    vector<Asset> tempAssets;

    for (Asset a : assets) {
        if (a.getName().find(s) != string::npos || a.getDescription().find(s) != string::npos) {
            tempAssets.push_back(a);
        }
    }

    setModelData(tempAssets);

}

void AssetTableModel::setModelData(vector<Asset> updatedAssets) {

    // clear out old vector items
    this->assets.clear();

    // if vector is not empty, copy new vector to 'assets'
    this->assets = updatedAssets;

    // refresh all the view's data
    this->setData(this->index(0,0), 0);
}
