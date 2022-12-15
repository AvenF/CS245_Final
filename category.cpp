#include "category.h"
using namespace std;

Category::Category()
{
    categoryID = 0;
    categoryName = "";
}

Category::Category(int categoryID, string categoryName) : categoryID(categoryID),
    categoryName(categoryName)
{

}

void Category::setCategoryID(int categoryID)
{
    this->categoryID = categoryID;
}

void Category::setCategoryName(string categoryName)
{
    this->categoryName = categoryName;
}
