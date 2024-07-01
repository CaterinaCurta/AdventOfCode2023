#include <iostream>
#include <fstream>
#include <vector>
#include <ctype.h>
#include <string>
#include <sstream>
#include <chrono>
#include "Game.h"
#include "EngineSchematics.h"
#include "Scratchcard.h"
//#include "Numbers.h"

using namespace std;
using namespace std::chrono;

/*void getTotalCalibration()
{


  vector<string> data = getDataFromFile("day1.txt");;
  int total_calibration = 0;
  vector<int> calibrations;
  Number n;

  for (int i = 0; i < data.size(); i++)
  {
    string sequence = data[i];
    calibrations.push_back(stoi(n.retrieveNumbers(sequence)));
  }

  for(int calibration : calibrations)
  {
    total_calibration += calibration;
  }

  cout << total_calibration << endl;
}
*/

int main() {
    //getTotalCalibration();

    int power = getSumOfPowerGames();
    int sum = getSumOfIds();
    cout << "The sum of ids is: " << sum << endl;
    cout << "The power of games is: " << power << endl;

    auto start = high_resolution_clock::now();
    parseSchematic();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by parseSchematic(): " << duration.count() << " microseconds." << endl;

    auto start_pile = high_resolution_clock::now();
    int pile_sum = computePile();
    cout << "Pile sum is: " << pile_sum << endl;
    auto stop_pile = high_resolution_clock::now();
    auto duration_pile = duration_cast<microseconds>(stop_pile - start_pile);
    cout << "Time taken by computePile(): " << duration_pile.count() << " microseconds." << endl;

    auto start_game = high_resolution_clock::now();
    int number_of_scratchcards = countScratchcards();
    cout << "Number of scratchcards: " << number_of_scratchcards << endl;
    auto stop_game = high_resolution_clock::now();
    auto duration_game = duration_cast<microseconds>(stop_game - start_game);
    cout << "Time taken by countScratchcards(): " << duration_game.count() << " microseconds." << endl;
    return 0;
}