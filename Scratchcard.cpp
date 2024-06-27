//
// Created by Caterina  Curta on 2024-06-26.
//
#include "Scratchcard.h"
#include "Data.h"
#include <sstream>

vector<Scratchcard> scratchcards;
bool debug_scratchcards = false;
vector<Scratchcard> parseScratchcard()
{
    vector<string> data = getDataFromFile("day4.txt");

    for (string line: data)
    {
        unsigned first = line.find(" ");
        unsigned last = line.find(":");
        int card_id = stoi(line.substr (first, last-first));
        vector<int> winning_numbers;
        vector<int> my_numbers;
        string subsets = line.substr(last+1,line.length() - 1);

        int separator_index = subsets.find('|');

        string winners = subsets.substr(1, separator_index - 2);
        stringstream ss(winners);
        string winning_number;
        while(getline(ss,winning_number,' '))
        {
            if (!winning_number.empty())
            {
                winning_numbers.push_back(stoi(winning_number));
            }
        }

        string lucky_numbers = subsets.substr(separator_index + 2, subsets.length());
        stringstream ss2(lucky_numbers);
        string potential_number;
        while (getline(ss2, potential_number, ' '))
        {
            if (!potential_number.empty())
            {
                my_numbers.push_back(stoi(potential_number));
            }
        }

        scratchcards.push_back(
                Scratchcard {
                    .card_id = card_id,
                    .winning_numbers = winning_numbers,
                    .potential_numbers = my_numbers
                }
                );
    }

    if (debug_scratchcards == true)
    {
        for (auto sc : scratchcards)
        {
            cout << "Card id: " << sc.card_id << endl;
            cout << "Winning numbers: " << endl;
            for (int wn : sc.winning_numbers) cout << wn << " ";
            cout << endl;
            cout << "Potential numbers: " << endl;
            for (int pn : sc.potential_numbers) cout << pn << " ";
            cout << endl;
        }
    }
    return scratchcards;
}

bool isWinningNumber(int number, vector<int> winningNumbers)
{
    for (const int i : winningNumbers)
    {
        if (number == i)
        {
            return true;
        }
    }
    return false;
}

int computePile()
{
    int pile_sum = 0;
    vector<Scratchcard> scratchcards = parseScratchcard();
    for (const Scratchcard& sc : scratchcards)
    {
        int winning_sum = 0;
        int j = 0;
        for (int i = 0; i < sc.potential_numbers.size(); i++)
        {

            if (isWinningNumber(sc.potential_numbers.at(i), sc.winning_numbers))
            {
                j++;
            }
        }
        if (j > 0)
        {
            winning_sum = pow(2, j - 1);
        }
        pile_sum += winning_sum;
    }
    return pile_sum;
}

int countScratchcards()
{
    return 0;
}