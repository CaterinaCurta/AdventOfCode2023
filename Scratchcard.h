//
// Created by Caterina  Curta on 2024-06-26.
//
#include <vector>
#ifndef ADVENTOFCODE2023_SCRATCHCARD_H
#define ADVENTOFCODE2023_SCRATCHCARD_H

using namespace std;

struct Scratchcard
{
    int card_id;
    vector<int> winning_numbers;
    vector<int> potential_numbers;
};

vector<Scratchcard> parseScratchcard();
int computePile();
int countScratchcards();
#endif //ADVENTOFCODE2023_SCRATCHCARD_H
