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

vector<EngineSchematic> parseSchematic();
int findMaxRowIndex(vector<EngineSchematic> schematics);
vector<char> getSymbolsOnRow(int row_index);
void evaluateSchematics();

#endif //ENGINESCHEMATICS_H
