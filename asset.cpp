#include "asset.h"

Asset::Asset()
{
    this->id = 0;
    this->category = "";
    this->cost = 0.0;
    this->name = "";
    this->description = "";
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

void Asset::setCategory(string s) {
    category = s;
}

void Asset::setDescription(string d) {
    description = d;
}

void Asset::setID(int i) {
    id = i;
}
