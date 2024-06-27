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

int getNumberBasedOnPosition(int row_index, int column_index)
{
        for(auto pn: numbers)
        {
            if (pn.row_number == row_index)
            {
                if (column_index >= pn.start_column && column_index <= pn.end_column)
                {
                    return pn.partNumber;
                }
            }
        }
    return 0;
}

vector<EngineSchematic> getStarSymbols()
{
    vector<EngineSchematic> star_symbols;
    for (const EngineSchematic& sym: symbols)
    {
        if (sym.symbol == '*')
        {
            star_symbols.push_back(sym);
        }
    }

    return star_symbols;
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
                num = num * 10 + (line.at(end) - '0');
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
        char diagonal_below_left = getSymbolBasedOnPosition(pn.row_number - 1, pn.start_column - 1);
        char diagonal_below_right = getSymbolBasedOnPosition(pn.row_number - 1, pn.end_column + 1);
        char diagonal_above_left = getSymbolBasedOnPosition(pn.row_number + 1, pn.start_column - 1);
        char diagonal_above_right = getSymbolBasedOnPosition(pn.row_number + 1, pn.end_column + 1);

        if(diagonal_below_left != ' ' ||
           diagonal_below_right != ' ' ||
           diagonal_above_left != ' ' ||
           diagonal_above_right != ' ')
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

    // Part 2
    int gear_ratio_sum = 0;
    vector<EngineSchematic> star_symbols = getStarSymbols();
    for (auto sym : star_symbols)
    {
        if (debug == true)
        {
            cout << sym.symbol << " at row " << sym.row_position << " and column " << sym.column_position << endl;
        }

        vector<int> adjacent_part_numbers;
        int pn_count = 0;
        int part_number_below = getNumberBasedOnPosition(sym.row_position + 1, sym.column_position);
        int part_number_above = getNumberBasedOnPosition(sym.row_position - 1, sym.column_position);
        if (part_number_below != 0)
        {
            adjacent_part_numbers.push_back(part_number_below);
        }

        if (part_number_above != 0)
        {
            adjacent_part_numbers.push_back(part_number_above);
        }

        int part_number_left = getNumberBasedOnPosition(sym.row_position, sym.column_position - 1);
        if (part_number_left != 0)
            adjacent_part_numbers.push_back(part_number_left);

        int part_number_right = getNumberBasedOnPosition(sym.row_position, sym.column_position + 1);
        if (part_number_right != 0) adjacent_part_numbers.push_back(part_number_right);

        int part_number_diagonal_above_left = getNumberBasedOnPosition(sym.row_position - 1,
                                                                       sym.column_position - 1);
        if (part_number_diagonal_above_left > 0) adjacent_part_numbers.push_back(part_number_diagonal_above_left);

        int part_number_diagonal_below_left = getNumberBasedOnPosition(sym.row_position + 1,
                                                                       sym.column_position - 1);
        if (part_number_diagonal_below_left > 0) adjacent_part_numbers.push_back(part_number_diagonal_below_left);

        int part_number_diagonal_above_right = getNumberBasedOnPosition(sym.row_position - 1,
                                                                       sym.column_position + 1);
        if (part_number_diagonal_above_right > 0) adjacent_part_numbers.push_back(part_number_diagonal_above_right);

        int part_number_diagonal_below_right = getNumberBasedOnPosition(sym.row_position + 1,
                                                                       sym.column_position + 1);
        if (part_number_diagonal_below_right > 0) adjacent_part_numbers.push_back(part_number_diagonal_below_right);

        std::sort(adjacent_part_numbers.begin(), adjacent_part_numbers.end());
        for(int i = 0; i < adjacent_part_numbers.size() - 1; i++) {
            if (adjacent_part_numbers[i] == adjacent_part_numbers[i + 1]) {
                adjacent_part_numbers.erase(adjacent_part_numbers.begin() + i);
                i--;
            }
        }

        if (debug == true)
        {
            for (auto ap: adjacent_part_numbers) {
                cout << ap << " is adjacent to " << sym.symbol << " at [" << sym.row_position << ", "
                     << sym.column_position << "]." << endl;
            }
        }

        if (adjacent_part_numbers.size() == 2)
        {
            int gear_ratio = adjacent_part_numbers.at(0) * adjacent_part_numbers.at(1);
            gear_ratio_sum += gear_ratio;
        }
    }

    cout << "Gear ratio sum is: " << gear_ratio_sum << endl;
}