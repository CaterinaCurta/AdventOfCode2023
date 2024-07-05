#include "Almanac.h"

void parseAlmanac()
{
    vector<string> data = getDataFromFile("day5.txt");
    vector<vector<tuple<int, int, int>>> all_maps;
    // Retrieve seeds
    string seeds = data.at(0) + " " + data.at(1);
    cout << seeds << endl;
    unsigned first = seeds.find(" ");
    unsigned last = seeds.find("\n");
    string all_seeds = seeds.substr (first + 1, last-first - 1);
    cout << all_seeds << endl;

    vector<tuple<int, int, int>> current_mapping;
    for (int i = 2; i < data.size(); i++)
    {
        // variable used to check changes
        if (data.at(i).empty())
        {
            if (current_mapping.size() > 0) all_maps.push_back(current_mapping);
            cout << "Size of map: " << current_mapping.size() << endl;
            current_mapping.clear();
        }
        if (!data.at(i).empty()) {
            if (isdigit(data.at(i).at(0)))
            {
                stringstream ss(data.at(i));
                string current_number;
                // vector that shall store the tuple elements for each tuple
                vector<int> tuple_elements;

                while(getline(ss,current_number,' '))
                {
                    tuple_elements.push_back(stoi(current_number));
                }
                current_mapping.push_back(make_tuple(tuple_elements.at(0), tuple_elements.at(1),
                                                    tuple_elements.at(2)));
            }
        }
        for (int i = 0; i < current_mapping.size(); i++)
        {
            cout << "Tuple " << i << ": " << get<0>(current_mapping.at(i)) << ", " << get<1>(current_mapping.at(i))
                 << ", " << get<2>(current_mapping.at(i)) << endl;
        }
        if (current_mapping.size() > 0 && i == data.size() - 1)
        {
            all_maps.push_back(current_mapping);
        }
    }


    cout << all_maps.size() <<  " oooooooof" << endl;

    for (int i = 0; i < all_maps.size(); i++)
    {
        cout << "Vector " << i << ":\n";
        vector<tuple<int,int,int>> current_vector = all_maps.at(i);
        for (int j = 0; j < all_maps.at(i).size(); j++)
        {
            cout << "Strawberry tuple " << j << ": " << get<0>(current_vector.at(j)) << ", " << get<1>(current_vector.at(j))
                 << ", " << get<2>(current_vector.at(j)) << endl;
        }
    }
}
