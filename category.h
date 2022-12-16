#ifndef CATEGORY_H
#define CATEGORY_H
#include<string>
using std::string;

class Category
{
private:
    int categoryID;
    string categoryName;
    int lastSetID;          // Will help keep track of SQL's auto increment id field

    void setCategoryName(string categoryName);
    void setCategoryID(int categoryID);

public:
    Category();
    Category(int, string);

    int getCategoryID() const { return categoryID; }
    string getCategoryName() const { return categoryName; }
};

#endif // CATEGORY_H
