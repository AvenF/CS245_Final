#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include "asset.h"
#include<string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <map>
#include <QtSql/QSqlDatabase>
using std::vector;
using std::string;
typedef std::map< int, Asset > AssetMap;

class DataManager
{
private:
    AssetMap assets;
    vector<string> splitString(string, char);
    void readDataFile(); //loadData
    string file;
    QSqlDatabase db;
    void insertData();
    bool updateData(const string name, double cost, const string category,
                    const string description);
    void removeData();

public:
    DataManager(); // should pass connection string to datamanager!!!!!!
    ~DataManager();
    void loadData(); // should be underscored AND PRIVATE!!!!!!!!!!!!!!!!!!!!!


    //These are the functions meant to aid in the showing, adding, and finding of assets
    void display(); // all need parameters
    void add(Asset);
    Asset find(int assetTag);
};

#endif // DATAMANAGER_H
