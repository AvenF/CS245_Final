#include "categorytablemodel.h"
#include <QColor>
#include <QFont>
#include "category.h"
#include "qbrush.h"

using std::vector;

CategoryTableModel::CategoryTableModel(vector<Category> categories, QObject *parent)
    : QAbstractTableModel(parent), categories(categories)
{
}

QVariant CategoryTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        // Set the column (Qt::Horizontal) headers
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return QString("Name");
            }
        }
    }
    return QVariant();
}

int CategoryTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return static_cast<int>(categories.size()); // # of rows in table?
}

int CategoryTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return 1; // Number of data members to display to user in table
}

QVariant CategoryTableModel::data(const QModelIndex &index, int role) const
{
    // Get the row and column numbers from the given index (QModelIndex)
    int row = index.row();
    int col = index.column();

    // Qt::DisplayRole -> what data do we display and in what columns?
    if (role == Qt::DisplayRole) {
        switch (col) {
        case 0: // name column
            return QString::fromStdString(categories[row].getCategoryName());
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

bool CategoryTableModel::setData(QModelIndex const& idx, QVariant const & /*value*/, int role) {
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
 * deletes the Category at the given 0index from the user data
 */
void CategoryTableModel::removeCategory(int index)
{
    // erases the Category at position 'index' in the vector.
    categories.erase(categories.begin() + index);

    /*
     * NOTE: vector::erase() uses an iterator as an argument.
     * We grab the begin() iterator of 'users', then advance by
     * 'index' number of elements to get to the User object
     * we want to remove.
     */

    // VERY IMPORTANT - call setData to trigger the update of the model and view
    this->setData(this->index(0,0), 0);
}

vector<Category> CategoryTableModel::getCategories() {
    return categories;
}

void CategoryTableModel::addCategory(int i, string s) {
    Category c(i, s);

    categories.push_back(c);

    // VERY IMPORTANT - call setData to trigger the update of the model and view
    this->setData(this->index(0,0), 0);
}

void CategoryTableModel::setModelData(vector<Category> updatedCategories) {

    // clear out old vector items
    this->categories.clear();

    // if vector is not empty, copy new vector to 'assets'
    this->categories = updatedCategories;

    // refresh all the view's data
    this->setData(this->index(0,0), 0);
}
