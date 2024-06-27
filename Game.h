#ifndef GAMES_H
#define GAMES_H
#include <vector>
#include "Data.h"

using namespace std;
// ALWAYS INITIALIZE VARIABLES ({} - if you don't know what to initialize it to)
struct Game
{
    int gameId = 0;
    vector<int> redCubes = {0};
    vector<int> greenCubes = {0};
    vector<int> blueCubes = {0};
};

vector<Game> getGames();
int getSumOfIds();
int getSumOfPowerGames();
#endif // GAMES_H