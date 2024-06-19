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

vector<PartNumber> getPotentialPartNumbers()
{
    vector<EngineSchematic> schematics = parseSchematic();
    vector<PartNumber> potential_part_numbers;

    for (int i = 0; i < schematics.size(); i++)
    {
        if(isdigit(schematics.at(i).symbol))
        {
            PartNumber current_part_number;
            current_part_number.partNumber = 0;
            current_part_number.start_column = schematics.at(i).column_position;
            current_part_number.row_number = schematics.at(i).row_position;
            current_part_number.end_column = current_part_number.start_column;
            while(isdigit(schematics.at(i).symbol))
            {
                current_part_number.end_column++;
                current_part_number.partNumber = current_part_number.partNumber * 10 + (schematics.at(i).symbol - '0');
                i++;
            }
            current_part_number.end_column--;
            potential_part_numbers.push_back(current_part_number);
        }
    }

//    for (int i = 0; i < potential_part_numbers.size(); i++)
//    {
//        cout << potential_part_numbers.at(i).partNumber << " Start column position: "
//             << potential_part_numbers.at(i).start_column << " End column position: "
//             << potential_part_numbers.at(i).end_column << " Row column position: "
//             << potential_part_numbers.at(i).row_number << endl;
//    }
    return potential_part_numbers;
}

vector<EngineSchematic> getSymbols()
{
    vector<EngineSchematic> symbols;
    vector<EngineSchematic> schematics = parseSchematic();

    for (int i = 0; i < schematics.size(); i++)
    {
        if(schematics.at(i).symbol != '.' && !isdigit(schematics.at(i).symbol))
        {
            EngineSchematic new_symbol;
            new_symbol.symbol = schematics.at(i).symbol;
            new_symbol.column_position = schematics.at(i).column_position;
            new_symbol.row_position = schematics.at(i).row_position;
            symbols.push_back(new_symbol);
        }
    }
    return symbols;
}

char getSymbolBasedOnPosition(int row_index, int column_index)
{
    vector<EngineSchematic> symbols = getSymbols();
    for (int i = 0; i < symbols.size(); i++)
    {
        if(symbols.at(i).row_position == row_index && symbols.at(i).column_position == column_index)
        {
            return symbols.at(i).symbol;
        }
    }
    return ' ';
}

bool checkSymbolsAbovePN(PartNumber pn)
{
    for (int i = pn.start_column; i <= pn.end_column; i++)
    {
        char symbol = getSymbolBasedOnPosition(pn.row_number - 1, i);

        if (symbol != ' ')
        {
            return true;
        }
    }
    return false;
}

bool checkSymbolsBelowPN(PartNumber pn)
{
    for (int i = pn.start_column; i <= pn.end_column; i++)
    {
        char symbol = getSymbolBasedOnPosition(pn.row_number + 1, i);

        if (symbol != ' ')
        {
            return true;
        }
    }
    return false;
}

bool checkLeftOrRightSymbols(PartNumber pn)
{
    char left_symbol = getSymbolBasedOnPosition(pn.row_number,
                                                pn.start_column - 1);
    char right_symbol = getSymbolBasedOnPosition(pn.row_number,
                                                 pn.end_column + 1);

    if (left_symbol != ' ' || right_symbol != ' ')
    {
        return true;
    }
    return false;
}

bool checkDiagonalAdjacency(PartNumber pn)
{
    // Left-side below
    if(getSymbolBasedOnPosition(pn.row_number + 1,
                                pn.start_column - 1) != ' ')
    {
        return true;
    }
    // Right-side below
    if(getSymbolBasedOnPosition(pn.row_number + 1,
                                pn.end_column + 1) != ' ')
    {
        return true;
    }
    // Left-side above
    if(getSymbolBasedOnPosition(pn.row_number - 1,
                                pn.start_column - 1) != ' ')
    {
        return true;
    }
    // Right-side above
    if(getSymbolBasedOnPosition(pn.row_number - 1,
                                pn.end_column + 1) != ' ')
    {
        return true;
    }
    return false;
}
bool isAdjacentPartNumber(PartNumber pn)
{
    // Check adjacency upper left and upper right
    // or adjacency lower left or lower right
    // or left or right on the same row
    // or row below or row above
    if (checkSymbolsBelowPN(pn) || checkSymbolsAbovePN(pn) || checkLeftOrRightSymbols(pn)
        || checkDiagonalAdjacency(pn))
    {
        cout << "Number " << pn.partNumber << " is a proper part number!^^" << endl;
        return true;
    }
    return false;
}

vector<PartNumber> getActualPartNumbers()
{
    vector<PartNumber> actual_part_numbers;
    vector<EngineSchematic> all_symbols = getSymbols();
    vector<PartNumber> potential_part_numbers = getPotentialPartNumbers();

//    for (EngineSchematic symbol : all_symbols)
//    {
//        cout << symbol.symbol << " " << symbol.row_position << " " << symbol.column_position << endl;
//    }

    for (int i = 0; i < potential_part_numbers.size(); i++)
    {
        PartNumber potential_part_number = potential_part_numbers.at(i);
        // Check for adjacency on same row
        if (isAdjacentPartNumber(potential_part_number))
        {
            actual_part_numbers.push_back(potential_part_number);
        }
    }


    //cout << "actual_part_numbers size: " << actual_part_numbers.size() << endl;
//    for (int i = 0; i < actual_part_numbers.size(); i++)
//    {
//        cout << "Part number: " << actual_part_numbers.at(i).partNumber << endl;
//    }
//    for (int i = 0; i < potential_part_numbers.size(); i++)
//    {
//        int found = 0;
//        for(int j = 0; j < actual_part_numbers.size(); j++)
//        {
//            if (potential_part_numbers.at(i).partNumber == actual_part_numbers.at(j).partNumber)
//            {
//                found = 1;
//            }
//        }
//        if (found == 0)
//        {
//            cout << potential_part_numbers.at(i).partNumber << " is not a part number :(" << endl;
//        }
//    }
    return actual_part_numbers;
}

int getPartNumberSum()
{
    int sum = 0;
    vector<PartNumber> actual_part_numbers = getActualPartNumbers();
    for (int i = 0; i < actual_part_numbers.size(); i++)
    {
        sum += actual_part_numbers.at(i).partNumber;
    }
    return sum;
}