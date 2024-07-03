#ifndef ALMANAC_H
#define ALMANAC_H

#include <vector>
#include <tuple>
#include "Data.h"
using namespace std;

struct Almanac
{
    vector<int> seeds;
    vector<tuple<int, int, int>> seed_to_soil_map;
    vector<tuple<int, int, int>> soil_to_fertilizer_map;
    vector<tuple<int, int, int>> fertilizer_to_water_map;
    vector<tuple<int, int, int>> water_to_light_map;
    vector<tuple<int, int, int>> light_to_temperature_map;
    vector<tuple<int, int, int>> temperature_to_humididty_map;
    vector<tuple<int, int, int>> humidity_to_location_map;
};

void parseAlmanac();
#endif //ALMANAC_H
