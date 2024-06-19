#ifndef GAMES_H
#define GAMES_H
#include <vector>
#include "Data.h"

using namespace std;

struct Game
{
    int gameId;
    vector<int> redCubes = {0};
    vector<int> greenCubes = {0};
    vector<int> blueCubes = {0};
};

vector<Game> getGames();
int getSumOfIds();
int getSumOfPowerGames();
#endif // GAMES_H