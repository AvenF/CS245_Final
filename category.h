#ifndef CATEGORY_H
#define CATEGORY_H
#include<string>
using std::string;

class Category
{
private:
    int categoryID;
    string categoryName;
public:
    Category();
    Category(int, string);

    int getCategoryID() const { return categoryID; }
    string getCategoryName() const { return categoryName; }

    void setCategoryID(int categoryID);
    void setCategoryName(string categoryName);
};

#endif // CATEGORY_H
