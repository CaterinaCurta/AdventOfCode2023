#include "EngineSchematics.h"


vector<EngineSchematic> parseSchematic()
{
    vector<EngineSchematic> schematics;
    vector<string> data = getDataFromFile("day3.txt");
    int row_index = 0; // row number
    for (int i = 0; i < data.size(); i++)
    {
        stringstream ss(data.at(i));
        string parsed;

        while (getline(ss, parsed))
        {
            for (int column_index = 0; column_index < parsed.length(); column_index++)
            {
                EngineSchematic current_es;
                //cout << parsed.at(k) << " tralala" << endl;
                current_es.symbol = parsed.at(column_index);
                current_es.row_position = row_index;
                current_es.column_position = column_index;
                schematics.push_back(current_es);

            }
            row_index++;
        }
    }

    return schematics;
}

int findMaxRowIndex(vector<EngineSchematic> schematics)
{
    EngineSchematic lastSchematic = schematics.at(schematics.size() - 1);
    return lastSchematic.row_position;
}

vector<char> getSymbolsOnRow(int row_index)
{
    vector<char> symbols;
    vector<EngineSchematic> schematics = parseSchematic();

    for (int i = 0; i < schematics.size(); i++)
    {
        if (schematics.at(i).row_position == row_index)
        {
            symbols.push_back(schematics.at(i).symbol);
        }
    }
    return symbols;
}

void evaluateSchematics()
{
    vector<EngineSchematic> schematics = parseSchematic();
    int highest_row_index = findMaxRowIndex(schematics);
    vector<int> numbers;
    int i = 0;
    while (i < highest_row_index)
    {
        //cout << "Row: " << i << endl;
        int number;

        // I want to take all the symbols on a certain row in order to determine which ones are numbers
        // I also need to somehow get the column index that it is at
        vector<char> symbols = getSymbolsOnRow(i);
        //for (char s : symbols) cout << s << " hahaha" << endl;
        // cout << schematics.at(i).symbol << " " << schematics.at(i).row_position << " " << schematics.at(i).column_position << endl;

        int j = 0;
       // int k = j;
       //int offset;
        while(j < symbols.size())
        {
            cout << "j = " << j << endl;
            if (isdigit(symbols.at(j))) {
                string number_string = "";
                //cout << symbols.at(i) << " hihi";
                number_string += symbols.at(j);
                int k = j + 1;
                while (isdigit(symbols.at(k))) {
                    number_string += symbols.at(k);
                    k++;
                    j++;
                }
                //offset = k;
                numbers.push_back(stoi(number_string));
                cout << "This is k: " << k << endl;

            }
            //cout << "Offset: " << offset << endl;
            j++;
        }
        i++;
    }
    cout << "These are the numbers: " << endl;
    for (int n : numbers) cout << n << endl;
}