#include "Data.h"
#include <fstream>

vector<string> getDataFromFile(string filepath)
{
    ifstream file;
    string line;
    vector<string> data;

    try
    {
        file.open(filepath);
        if(!file.is_open()) {
            throw "File not found";
        }

        while(getline(file, line))
        {
            data.push_back(line);
        }
    }
    catch(runtime_error& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return data;
}
