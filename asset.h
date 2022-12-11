#ifndef ASSET_H
#define ASSET_H
#include <string>
using std::string;


class Asset
{
public:
    Asset();
    Asset(string, int, double, string, string);
    string getName() const;
    int getID() const;
    double getCost() const;
    string getCategory() const;
    string getDescription() const;

private:
    string name;
    int id;
    double cost;
    string category;
    string description;
};

#endif // ASSET_H
