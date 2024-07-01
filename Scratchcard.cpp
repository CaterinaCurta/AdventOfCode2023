//
// Created by Caterina  Curta on 2024-06-26.
//
#include "Scratchcard.h"
#include "Data.h"
#include <sstream>
#include <map>

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

vector<int> getWinningNumbers(int i)
{
    vector<int> winners;
    Scratchcard current_scratchard = scratchcards.at(i);
    for (int j = 0; j < current_scratchard.winning_numbers.size(); j++)
    {
        for (int k = 0; k < current_scratchard.potential_numbers.size(); k++)
        {
            if (current_scratchard.winning_numbers.at(j) == current_scratchard.potential_numbers.at(k))
            {
                winners.push_back(current_scratchard.potential_numbers.at(k));
            }
        }
    }
    return winners;
}

int countScratchcards()
{
    vector<int> total_scratchcards;
    map<int, int> repetitions;
    // initialize each element in instance array to 1
    // because there will always be at least 1 element
    for (int i = 0; i < scratchcards.size(); i++)
    {
        repetitions[i + 1] = 1;
    }

    for (int i = 0; i < scratchcards.size(); i++)
    {
        int k = 0;
        vector<int> winning_numbers = getWinningNumbers(i);
        while (k < repetitions[scratchcards.at(i).card_id])
        {
            for (int j = 1; j <= winning_numbers.size(); j++) {
                repetitions[scratchcards.at(i).card_id + j]++;
            }
            k = k + 1;
        }
    }

    int sum = 0;
    for (const auto& repetition: repetitions)
    {
        sum += repetition.second;
    }
    return sum;
}