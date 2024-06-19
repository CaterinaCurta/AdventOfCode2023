#include <iostream>
#include <fstream>
#include <vector>
#include <ctype.h>
#include <string>
#include <sstream>
#include "Game.h"
#include "EngineSchematics.h"
//#include "Numbers.h"

using namespace std;

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

    evaluateSchematics();
    return 0;
}