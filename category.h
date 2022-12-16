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

public:
    Category();
    Category(int, string);

    int getCategoryID() const { return categoryID; }
    string getCategoryName() const { return categoryName; }

    void setCategoryName(string categoryName);
    void setCategoryID(int categoryID);
};

#endif // CATEGORY_H
