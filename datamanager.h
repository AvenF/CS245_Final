#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include "asset.h"
#include "category.h"
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
    vector<Asset> assets;
    vector<Category> categories;
    QString connection;
    vector<string> splitString(string, char);
    void readDataFile(); //loadData
    string file;
    QSqlDatabase db;
    void insertData();
    bool updateData(const string name, double cost, const string category,
                    const string description);
    void removeData();

    void _loadCategoryData();
    void _loadAssetData();

public:
    DataManager(); // should pass connection string to datamanager!!!!!!
    ~DataManager();

    //These are the functions meant to aid in the showing, adding, and finding of assets
    void display(); // all need parameters
    void add(Asset);
    Asset find(int assetTag);

    // Database manipulation functions
    void addCategoryToDB(string c);
    void addAssetToDB(string name, double cost, string cat, string desc, int id);
    void removeCategoryFromDB(string c);
    void removeAssetFromDB(int id);
    void updateAssetInDB(string name, double cost, string cat, string desc, int id);
    void searchAssets(string s);

    vector<Asset> getAssets();
    vector<Category> getCategories();
};

#endif // DATAMANAGER_H
