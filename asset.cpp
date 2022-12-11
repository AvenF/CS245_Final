#include "asset.h"

Asset::Asset()
{
}

Asset::Asset(string name, int id, double cost, string cat, string desc) {
    this->name = name;
    this->id = id;
    this->cost = cost;
    category = cat;
    description = desc;
}

string Asset::getName() const {
    return name;
}

int Asset::getID() const {
    return id;
}

double Asset::getCost() const {
    return cost;
}

string Asset::getCategory() const {
    return category;
}

string Asset::getDescription() const {
    return description;
}
