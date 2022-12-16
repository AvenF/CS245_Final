#include "datamanager.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QString>
#include <QVariant>
#include <QMessageBox>
#include <string>
using namespace std;
using std::string;
using std::cout;

DataManager::DataManager() {

}
void DataManager::loadData() // DONT FORGET TO CHANGE DONOVAN
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Driver={ODBC Driver 13 for SQL Server};Server=tcp:assetitem-dw.database.windows.net,1433;Database=assetitem;Uid=jpgrady;Pwd=cs245C++;Encrypt=yes;TrustServerCertificate=no;Connection Timeout=30;");
    bool ok = db.open();
           // if we connect successfully...
           if(ok)
           {

           }
           else
           {
                 exit(1);
           }
}

void DataManager::insertData()
{
   QString sql;
   sql += "INSERT INTO assetItems (categoryID, Cost, Name, Description)";
}

bool DataManager::updateData(const string name, double cost, const string category,
                             const string description)
{
    /**
    AssetMap assets = assets;
    assets;
    theCust.setHomeTown(city);
    theCust.setHomeState(state);
    **/

    bool ok = db.open();
    if(ok)
    {
    QString sql;
    sql += "UPDATE asset ";
    sql += "SET name = ?, cost = ?, category = ?, description = ? ";
    sql += "WHERE ID = ?";

    QSqlQuery query;
    query.setForwardOnly(true);
    query.prepare(sql);

    query.bindValue(0, QString::fromStdString(name));
    query.bindValue(1, QString::number(cost));
    query.bindValue(2, QString::fromStdString(category));
    query.bindValue(3, QString::fromStdString(description));
    if(query.exec())
    {
      return true;
    }
    else
    {
    return false;
    }
    return false;
    }
}

/**
void removeData()
{
    QSqlQuery query;
    query.prepare("DELETE FROM asset WHERE ID = ?");
    query.exec();

}
**/

DataManager::~DataManager()//destructor using the writeData function
{

}


void DataManager::add(Asset asset)//function meant to add assets to the map if not a duplicate
{
        auto it = assets.find(asset.getID());
            if (it != assets.end())
            {
                return;
            }
        assets.insert(std::pair<int, Asset>(asset.getID(), asset));
}

void DataManager::readDataFile()//This loads data
{
    ifstream input("Assign4.txt");
    if (!input)
    {
        exit(1);
    }

    string line;

    // while there are still rows of data in the states data file
    while (!input.eof())
    {
        // read a line from the file; separate it into fields on tab characters
        getline(input, line);
        vector<string> fields = splitString(line, '\t');

        // if the row has 6 fields...
        if (fields.size() == 5)
        {
            //add item
            //remove
            // assign each token to a variable
            int assetTag = std::stoi(fields[0]);
            string name = fields[1];
            string category = fields[2];
            double price = std::stod(fields[3]);
            string description = fields[4];
            // create an asset object
            Asset a(name, assetTag, price, category, description);

            assets.insert(std::pair<int, Asset>(assetTag, a));
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

Asset DataManager::find(int assetTag) //This function finds an asset based on its tag
{
    auto it = assets.find(assetTag);
    if (it == assets.end())
    {
        throw std::out_of_range {"The tag could not be found."};
    }
    return it->second;
}
