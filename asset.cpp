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

void Asset::setName(string n) {
    name = n;
}

void Asset::setCost(double c) {
    cost = c;
}

void Asset::setCategory(string c) {
    category = c;
}

void Asset::setDescription(string d) {
    description = d;
}
