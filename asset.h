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

    void setID(int i);
    void setName(string n);
    void setCost(double c);
    void setCategory(string s);
    void setDescription(string d);

private:
    string name;
    int id;
    double cost;
    string category;
    string description;

};

#endif // ASSET_H
