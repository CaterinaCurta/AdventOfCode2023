#include "EngineSchematics.h"

vector<PartNumber> numbers;
vector<EngineSchematic> symbols;

bool debug = false;

char getSymbolBasedOnPosition(int row_index, int column_index)
{


    //vector<EngineSchematic> symbols = getSymbols();
    for (int i = 0; i < symbols.size(); i++)
    {
        if(symbols.at(i).row_position == row_index && symbols.at(i).column_position == column_index)
        {
            return symbols.at(i).symbol;
        }
    }
    return ' ';
}

void parseSchematic()
{
    vector<string> data = getDataFromFile("day3.txt");
    int row_index = 0;

    // Iterate on the lines here. getDataFromFile already seems to split lines, so we can just use a loop
    for (string line : data)
    {
        // First, parse out non-digits by iterating per-char
        for (int column_index = 0; column_index < line.length(); column_index++)
        {
            char sym = line.at(column_index);
            if (!isdigit(sym) && sym != '.') {
                symbols.push_back(
                        EngineSchematic {
                                .symbol = sym,
                                .row_position = row_index,
                                .column_position = column_index,
                        }
                );
            }
        }

        // Then, go across the string again and parse out the numbers
        int start = 0;
        while (start < line.length())
        {
            char sym = line.at(start);
            if (!isdigit(sym)) {
                start++;
                continue;
            }

            // alright, time to begin parsing a number
            int end = start;
            int num = 0;
            while (end < line.length() && isdigit(line.at(end))) {
                num = num*10 + (line.at(end) - '0');
                end++;
            }

            numbers.push_back(
                    PartNumber {
                            .partNumber = num,
                            .row_number = row_index,
                            .start_column = start,
                            .end_column = end - 1,
                    }
            );

            // advance read cursor to end of number
            start = end;
        }


        row_index++;
    }

    if (debug == true)
    {
        cout << "symbols:" <<endl;
        for (auto sym : symbols) {
            cout << "  " << sym.symbol << " at " << sym.row_position << "," << sym.column_position <<endl;
        }
        cout << "numbers:" <<endl;
        for (auto num : numbers) {
            cout << "  " << num.partNumber << " on row " << num.row_number << " at [" << num.start_column << "," << num.end_column << "]" << endl;
        }
    }

    vector<PartNumber> actual_part_numbers;
    for (PartNumber pn: numbers)
    {
        // Check diagonal adjacency
        if(getSymbolBasedOnPosition(pn.row_number - 1, pn.start_column - 1) != ' ' ||
           getSymbolBasedOnPosition(pn.row_number - 1, pn.end_column + 1) != ' ' ||
           getSymbolBasedOnPosition(pn.row_number + 1, pn.start_column - 1) != ' ' ||
           getSymbolBasedOnPosition(pn.row_number + 1, pn.end_column + 1) != ' ')
        {
            actual_part_numbers.push_back(pn);
        }
        // Check adjacency above and below
        for (int i = pn.start_column; i <= pn.end_column; i++)
        {
            char symbol_above = getSymbolBasedOnPosition(pn.row_number - 1, i);
            char symbol_below = getSymbolBasedOnPosition(pn.row_number + 1, i);
            if (symbol_above != ' ' || symbol_below != ' ')
            {
                actual_part_numbers.push_back(pn);
                break;
            }
        }

        //Check adjacency left and right
        if (getSymbolBasedOnPosition(pn.row_number, pn.start_column - 1) != ' '
            || getSymbolBasedOnPosition(pn.row_number, pn.end_column + 1) != ' ')
        {
            actual_part_numbers.push_back(pn);
        }

    }

    int sum = 0;

    for (PartNumber pn : actual_part_numbers)
    {
        sum += pn.partNumber;
    }

    cout << "Part numbers sum is: " << sum << endl;
}