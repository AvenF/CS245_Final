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
using std::vector;
using std::string;
typedef std::map< int, Asset > AssetMap;

class DataManager
{
private:
    AssetMap assets;
    vector<string> splitString(string, char);
    void writeDataFile();
    void readDataFile(); //loadData
    string file;

public:
    DataManager(string);
    ~DataManager();

    //These are the functions meant to aid in the showing, adding, and finding of assets
    void display(); // all need parameters
    void add(Asset);
    Asset find(int assetTag);
};

#endif // DATAMANAGER_H
