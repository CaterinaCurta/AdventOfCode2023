#include "Game.h"
#include <sstream>

vector<Game> getGames()
{
    vector<string> data = getDataFromFile("day2.txt");
    vector<Game> allGames;
    for (int i = 0; i < data.size(); i++)
    {
        Game newGame;
        unsigned first = data.at(i).find(" ");
        unsigned last = data.at(i).find(":");
        newGame.gameId = stoi(data.at(i).substr (first, last-first));
        string currentGame = data.at(i);
        string subsets = currentGame.substr(last+1,
                                            currentGame.length() - 1);

        subsets = subsets.substr(1, subsets.length() - 1);
        stringstream ss(subsets);
        string parsed;
        int j = 0;
        while (getline(ss,parsed,';'))
        {
            string round = parsed;

            stringstream gs(round);
            string cube;
            while(getline(gs,cube,','))
            {
                string current_cube = cube;
                if(current_cube.find("red") != string::npos)
                {
                    string red_number;
                    if (current_cube.at(0) != ' ')
                    {
                        red_number = current_cube.substr(0, current_cube.find("blue") - 1);
                    }
                    else
                    {
                        red_number = current_cube.substr(1, current_cube.find("blue") - 2);
                    }
                    if (j < newGame.redCubes.size())
                    {
                        newGame.redCubes.at(j) += stoi(red_number);
                    }
                    else
                    {
                        newGame.redCubes.push_back(stoi(red_number));
                    }
                }

                // If index is unnecessary, have a contains-like function
                if(current_cube.find("green") != string::npos)
                {
                    string green_number;
                    if (current_cube.at(0) != ' ')
                    {
                        green_number = current_cube.substr(0, current_cube.find("blue") - 1);
                    }
                    else
                    {
                        green_number = current_cube.substr(1, current_cube.find("blue") - 2);
                    }
                    if (j < newGame.greenCubes.size())
                    {
                        newGame.greenCubes.at(j) += stoi(green_number);
                    }
                    else
                    {
                        newGame.greenCubes.push_back(stoi(green_number));
                    }
                }
                if(current_cube.find("blue") != string::npos)
                {
                    string blue_number;
                    if (current_cube.at(0) != ' ')
                    {
                        blue_number = current_cube.substr(0, current_cube.find("blue") - 1);
                    }
                    else
                    {
                        blue_number = current_cube.substr(1, current_cube.find("blue") - 2);
                    }
                    if (j < newGame.blueCubes.size())
                    {
                        newGame.blueCubes.at(j) += stoi(blue_number);
                    }
                    else
                    {
                        newGame.blueCubes.push_back(stoi(blue_number));
                    }
                }
            }
            j++;
        }

        allGames.push_back(newGame);
    }

    return allGames;
}

int getSumOfIds()
{
    int id_sum = 0;
    vector<Game> allGames = getGames();
    for (int i = 0; i < allGames.size(); i++)
    {
        int bad_cubes = 0;
        for (int j = 0; j < allGames.at(i).blueCubes.size(); j++)
        {
            if (allGames.at(i).blueCubes.at(j) > 14)
            {
                bad_cubes++; // think about ways to exit the for-loop early and
                             // skip the other loops
            }
        }
        for (int j = 0; j < allGames.at(i).redCubes.size(); j++)
        {
            if (allGames.at(i).redCubes.at(j) > 12)
            {
                bad_cubes++;
            }
        }
        for (int j = 0; j < allGames.at(i).greenCubes.size(); j++)
        {
            if (allGames.at(i).greenCubes.at(j) > 13)
            {
                bad_cubes++;
            }
        }

        if (bad_cubes == 0)  id_sum += allGames.at(i).gameId;
    }
    return id_sum;
}

int getSumOfPowerGames()
{
    int sum_of_games = 0;
    vector<Game> allGames = getGames();

    for (int i = 0; i < allGames.size(); i++)
    {
        int power = 1;
        int max_blue = allGames.at(i).blueCubes.at(0);
        vector<int> blue_cubes = allGames.at(i).blueCubes;
        int max_red = allGames.at(i).redCubes.at(0);
        vector<int> red_cubes = allGames.at(i).redCubes;
        int max_green = allGames.at(i).greenCubes.at(0);
        vector<int> green_cubes = allGames.at(i).greenCubes;
        for(int j = 0; j < blue_cubes.size(); j++)
        {
            if (blue_cubes.at(j) > max_blue)
            {
                max_blue = blue_cubes.at(j);
            }
        }

        for(int j = 0; j < green_cubes.size(); j++)
        {
            if (green_cubes.at(j) > max_green)
            {
                max_green = green_cubes.at(j);
            }
        }

        for(int j = 0; j < red_cubes.size(); j++)
        {
            if (red_cubes.at(j) > max_red)
            {
                max_red = red_cubes.at(j);
            }
        }
        power = max_blue * max_green * max_red;
        sum_of_games += power;
    }

    return sum_of_games;
}
