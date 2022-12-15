#include "datamanager.h"
using namespace std;
using std::cout;

DataManager::DataManager(string file)
{
    this->file = file;
    readDataFile();
}

DataManager::~DataManager()//destructor using the writeData function
{
    writeDataFile();
}

void DataManager::display()//display function meant to format the output
{
    // Print all items on the same line
    cout << left << setw(15) << "Asset Tag" << " ";
    cout << setw(25) << "Name" << " ";
    cout << setw(18) << "Category" << " ";
    cout << right << setw(10) << "Price" << " ";
    cout << endl;

    // Print on a new line
    cout << string(70, '-') << endl;

    for(auto& item : assets) //Displays asset data on a new line
    {
        item.second.display();
        cout << '\n';
    }
}

void DataManager::add(AssetItem asset)//function meant to add assets to the map if not a duplicate
{
        auto it = assets.find(asset.getAssetTag());
            if (it != assets.end())
            {
                return;
            }
        assets.insert(std::pair<int, AssetItem>(asset.getAssetTag(), asset));
}

void DataManager::readDataFile()//This opens and reads the file
{
    ifstream input("Assign4.txt");
    if (!input)
    {
        exit(1);
    }

    string line;

    // while there are still rows of data in the states data file
    while (!input.eof())
    {
        // read a line from the file; separate it into fields on tab characters
        getline(input, line);
        vector<string> fields = splitString(line, '\t');

        // if the row has 6 fields...
        if (fields.size() == 4)
        {
            // assign each token to a variable
            int assetTag = std::stoi(fields[0]);
            string name = fields[1];
            string category = fields[2];
            double price = std::stod(fields[3]);
            // create an asset object
            AssetItem a(assetTag, name, category, price);

            assets.insert(std::pair<int, AssetItem>(assetTag, a));
        }
    }
    input.close();
}

void DataManager::writeDataFile()//sends data back to file
{
    ofstream input("Assign4.txt");
}

vector<string> DataManager::splitString(string text, char sep)//splitstring function meant to seperate data
{
    string field;				// Stores a single field
    vector<string> fields;		// Stores all fields

    // Open an input string stream
    istringstream inputStr(text);	// C++ input string stream class

    // Get a line of text from the string stream; split on the separator character;
    while (getline(inputStr, field, sep))
    {
        // Add ‘field’ to ‘fields’
        fields.push_back(field);
    }

    return fields;
}

AssetItem DataManager::find(int assetTag) //This function finds an asset based on its tag
{
    auto it = assets.find(assetTag);
    if (it == assets.end())
    {
        throw std::out_of_range {"The tag could not be found."};
    }
    return it->second;
}
