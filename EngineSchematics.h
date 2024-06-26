#ifndef ENGINESCHEMATICS_H
#define ENGINESCHEMATICS_H
#include "Data.h"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include<tuple>

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
    int adjacent_stars = 0;
};

void parseSchematic();
char getSymbolBasedOnPosition(int row_index, int column_index);

#endif //ENGINESCHEMATICS_H
