#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include<string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <map>
using std::vector;
using std::string;
typedef std::map< int, AssetItem > AssetMap;

class DataManager
{
private:
    AssetMap assets; //map
    vector<string> splitString(string, char);
    void writeDataFile();
    void readDataFile();
    string file;

public:
    DataManager(string);
    ~DataManager();

    //These are the functions meant to aid in the showing, adding, and finding of assets
    void display(); // all need parameters
    void add(AssetItem);
    AssetItem find(int assetTag);
};

#endif // DATAMANAGER_H
