#ifndef ENGINESCHEMATICS_H
#define ENGINESCHEMATICS_H
#include "Data.h"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
struct EngineSchematic{
    char symbol;
    int row_position;
    int column_position;
};

struct PartNumber
{
    int partNumber;
    int start_column;
    int end_column;
    int row_number;
};

vector<EngineSchematic> parseSchematic();
int findMaxRowIndex();
vector<char> getSymbolsOnRow(int row_index);
vector<PartNumber> getPotentialPartNumbers();
vector<EngineSchematic> getSymbols();
char getSymbolBasedOnPosition(int row_index, int column_index);
vector<PartNumber> getActualPartNumbers();
int getPartNumberSum();
#endif //ENGINESCHEMATICS_H
