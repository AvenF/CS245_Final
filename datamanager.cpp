#include "datamanager.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QString>
#include <QVariant>
#include <QMessageBox>
#include <string>
#include <QFile>
#include <QFileDialog>
using namespace std;
using std::string;
using std::cout;

DataManager::DataManager() {

    this->readDataFile();

    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(connection);

    this->_loadCategoryData();
    this->_loadAssetData();

}

void DataManager::_loadCategoryData()
{
    // open the connection
    bool ok = db.open();

        // if we connect successfully...
        if(ok)
        {
            // Create a query that can only be read forward;
            // improves performance *dramatically*
            QSqlQuery query;
            query.setForwardOnly(true);

            query.prepare("SELECT * FROM category");
            if (query.exec()) {
                while (query.next()) {
                    int categoryID = query.value(0).toInt();
                    string categoryName = query.value(1).toString().toStdString();

                    Category myCategory;
                    // store data in category data member
                    myCategory.setCategoryID(categoryID);
                    myCategory.setCategoryName(categoryName);
                    this->categories.push_back(myCategory);
                }
            }
        }
        else {
            std::cout << "Issues" << std::endl;
            exit(1);
        }
}

void DataManager::_loadAssetData() {
    // open the connection
    bool ok = db.open();

        // if we connect successfully...
        if(ok) {
            QSqlQuery query;
            query.setForwardOnly(true);

            // Create a prepared statement;
            // Get all items from assetItem table
            //
            query.prepare("SELECT * FROM assetItems");

            // If your SQL was OK...
            if(query.exec())
            {
                // while there are still more records in the result set...
                while (query.next())
                {

                    /*
                     *  NOTE: toString() returns a QString object, not a std::string
                     *  Use the QString.toStdString() command to convert the QString
                     *  to a std::string.
                     */

                    // Get asset data
                    int assetID = query.value(0).toInt();
                    int assetCategoryID = query.value(1).toInt();
                    double assetCost = query.value(2).toDouble();
                    string assetName = query.value(3).toString().toStdString();
                    string assetDescription = query.value(4).toString().toStdString();

                    Asset myAsset;
                    // Store the data in the Customer data member
                    myAsset.setID(assetID);
                    for (Category c : categories) {
                        if (c.getCategoryID() == assetCategoryID) {
                            myAsset.setCategory(c.getCategoryName());
                        }
                    }
                    myAsset.setCost(assetCost);
                    myAsset.setName(assetName);
                    myAsset.setDescription(assetDescription);
                    this->assets.push_back(myAsset);
                 }
             }
             else {
                std::cout << "Issues" << std::endl;
                exit(1);
             }

        }
}

DataManager::~DataManager()//destructor using the writeData function
{

}

// Reads database connection string from a file and
// assigns it to QString connection
void DataManager::readDataFile()
{
    // Below is a snippet of code I snagged from BadHombre on https://forum.qt.io/topic/76962/problem-with-ifstream-and-qt-creator
    // and modified it a little bit to make it less ugly for the end user. Only displays text files and automatically opens up
    // at the CS245_Final directory. Super convenient.
    QStringList filenames = QFileDialog::getOpenFileNames(
           new QWidget,
           QObject::tr("Please choose a text document to read your database connection string from ! "),
           "...\\CS245_Final",
           "Text files (*.txt*)");

       std::string current_locale_text = filenames[0].toLocal8Bit().constData();

       ifstream input(current_locale_text.c_str());

    if (!input)
    {
        std::cout << "File I/O failure" << std::endl;
        exit(1);
    }

    string line;

    // while there are still rows of data in the states data file
    while (!input.eof())
    {
        // read a line from the file; separate it into fields on tab characters
        getline(input, line);
        vector<string> fields = splitString(line, '\t');

        // if the row has 1 field...
        if (fields.size() == 1)
        {
            // assign token to a variable
            string connect = fields[0];
            this->connection = QString::fromStdString(connect);
        }
    }
    input.close();
}

vector<string> DataManager::splitString(string text, char sep)//splitstring function meant to seperate data
{
    string field;				// Stores a single field
    vector<string> fields;		// Stores all fields

    // Open an input string stream
    istringstream inputStr(text);	// C++ input string stream class

    // Get a line of text from the string stream; split on the separator character;
    while (getline(inputStr, field, sep))
    {
        // Add ‘field’ to ‘fields’
        fields.push_back(field);
    }

    return fields;
}

/*Asset DataManager::find(int assetTag) //This function finds an asset based on its tag
{
    auto it = assets.find(assetTag);
    if (it == assets.end())
    {
        throw std::out_of_range {"The tag could not be found."};
    }
    return it->second;
}*/

vector<Asset> DataManager::getAssets() {
    return this->assets;
}

vector<Category> DataManager::getCategories() {
    return this->categories;
}

void DataManager::addCategoryToDB(string c) {

    bool ok = db.open();

        if(ok) {
            QSqlQuery query;
            query.setForwardOnly(true);
            query.prepare("INSERT INTO category(categoryName)"
                          " VALUES(:name); ");

            query.bindValue(":name", QString::fromStdString(c));

            if(!query.exec()) {
                std::cout << "SQL Execution Failed" << std::endl;
            }
            else {
                qDebug()<<query.lastInsertId().toInt();
                int lastId = query.lastInsertId().toInt();

                Category myCategory;
                myCategory.setCategoryID(lastId);
                myCategory.setCategoryName(c);
                this->categories.push_back(myCategory);
            }


        }
        else {
            std::cout << "Issues" << std::endl;
        }

}

void DataManager::removeCategoryFromDB(string cat) {

    bool ok = db.open();

        if(ok) {
            QSqlQuery query;
            query.setForwardOnly(true);
            query.prepare("DELETE FROM assetItems WHERE categoryID = :id; ");

            for (const Category &c : categories) {
                if (c.getCategoryName() == cat) {
                    query.bindValue(":id", c.getCategoryID());
                    break;
                }
            }
            if(!query.exec()) {
                std::cout << "Something is wrong when you attempt to delete every asset under a category procced for removal" << std::endl;
            }

            query.prepare("DELETE FROM category WHERE categoryName = :name; ");

            query.bindValue(":name", QString::fromStdString(cat));

            if(!query.exec()) {
                std::cout << "Category Deletion Failure" << std::endl;
            }

        }
}

void DataManager::searchAssets(string s) {
    QString name = QString::fromStdString(s);
    QString desc = name;

    bool ok = db.open();

        if(ok) {
            QSqlQuery query;
            query.setForwardOnly(true);
            query.prepare("SELECT * FROM assetItems WHERE name LIKE concat('%', ?, '%') OR description LIKE concat('%', ?, '%'); ");

            query.bindValue(0, name);
            query.bindValue(1, desc);

            if(query.exec()) {
                assets.clear();
                while (query.next())
                {

                    /*
                     *  NOTE: toString() returns a QString object, not a std::string
                     *  Use the QString.toStdString() command to convert the QString
                     *  to a std::string.
                     */

                    // Get asset data
                    int assetID = query.value(0).toInt();
                    int assetCategoryID = query.value(1).toInt();
                    double assetCost = query.value(2).toDouble();
                    string assetName = query.value(3).toString().toStdString();
                    string assetDescription = query.value(4).toString().toStdString();

                    Asset myAsset;
                    // Store the data in the Customer data member
                    myAsset.setID(assetID);
                    for (const Category &c : categories) {
                        if (c.getCategoryID() == assetCategoryID) {
                            myAsset.setCategory(c.getCategoryName());
                        }
                    }
                    myAsset.setCost(assetCost);
                    myAsset.setName(assetName);
                    myAsset.setDescription(assetDescription);
                    this->assets.push_back(myAsset);
                 }
            }
        }
}

void DataManager::addAssetToDB(string name, double cost, string cat, string desc, int id) {

    bool ok = db.open();

        if(ok) {
            QSqlQuery query;
            query.setForwardOnly(true);
            query.prepare("INSERT INTO assetItems(ID, categoryID, Cost, Name, Description)"
                          " VALUES(:id, :catID, :cost, :name, :desc); ");

            query.bindValue(":id", id);
            for (const Category &c : categories) {
                if (c.getCategoryName() == cat) {
                    query.bindValue(":catID", c.getCategoryID());
                    break;
                }
            }
            query.bindValue(":cost", cost);
            query.bindValue(":name", QString::fromStdString(name));
            query.bindValue(":desc", QString::fromStdString(desc));

            Asset a(name, id, cost, cat, desc);
            assets.push_back(a);

           if(!query.exec()) {
               std::cout << "Can't Add Asset To Database" << std::endl;
           }
        }

}

void DataManager::removeAssetFromDB(int id) {
    bool ok = db.open();

        if(ok) {
            QSqlQuery query;
            query.setForwardOnly(true);
            query.prepare("DELETE FROM assetItems WHERE ID = ?; ");

            query.bindValue(0, id);

            if(!query.exec()) {
                std::cout << "Asset was NOT removed from your Database" << std::endl;
            }
        }
}

void DataManager::updateAssetInDB(string name, double cost, string cat, string desc, int id) {
    bool ok = db.open();

        if(ok) {
            QSqlQuery query;
            query.setForwardOnly(true);
            query.prepare("UPDATE assetItems SET categoryID = ?, cost = ?, name = ?, description = ? WHERE id = ? ");

            for (const Category &c : categories) {
                if (c.getCategoryName() == cat) {
                    query.bindValue(0, c.getCategoryID());
                    break;
                }
            }
            query.bindValue(1, cost);
            query.bindValue(2, QString::fromStdString(name));
            query.bindValue(3, QString::fromStdString(desc));
            query.bindValue(4, id);

            if (!query.exec()) {
                std::cout << "Asset failed to update!" << std::endl;
            }
            else {
                for (auto it = assets.begin(); it != assets.end(); it++) {
                    if (it->getID() == id) {
                        assets.erase(it);
                        break;
                    }
                }
                Asset myAsset;
                myAsset.setName(name);
                myAsset.setCost(cost);
                myAsset.setCategory(cat);
                myAsset.setDescription(desc);
                myAsset.setID(id);

                assets.push_back(myAsset);
            }
        }

}
