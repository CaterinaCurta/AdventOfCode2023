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

//    int sum_pn = getPartNumberSum();
//    cout << "Part number sum is: " << sum_pn;
      parseSchematic();
//    for (PartNumber pn : part_numbers)
//    {
//        cout << getSymbolBasedOnPosition(pn.start_column, pn.row_number);
//
//    }
//
//    vector<PartNumber> potential_part_numbers = getPotentialPartNumbers();
//    for (PartNumber pn : potential_part_numbers)
//    {
//        cout << pn.partNumber << " " << pn.start_column << " " << pn.end_column
//             << " " << pn.row_number << endl;
//    }
    return 0;
}