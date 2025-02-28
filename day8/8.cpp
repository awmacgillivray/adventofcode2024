#include "../common.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

bool check_location_in_bounds(vector<int> location, int dimensions)
{
    if (location[0] >= 0 &&
        location[0] < dimensions &&
        location[1] >= 0 &&
        location[1] < dimensions)
    {
        return true;
    }
    else
    {
        return false;
    }
}

map<char, vector<vector<int>>> find_antenna_locations(vector<vector<char>> grid)
{
    map<char, vector<vector<int>>> antenna_locations;
    // Find occurences of each antennae type (character) and record coordinates
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            char cell = grid[i][j];
            if (cell == '.')
            {
                continue;
            }
            else
            {
                antenna_locations[cell].push_back(vector<int>{i, j});
            }
        }
    }
    return antenna_locations;
}

int main()
{
    // Initialise variables
    string line;
    vector<vector<char>> grid;
    int total_antinodes = 0;

    // Load data from file
    ifstream file("8_input.txt");
    while (getline(file, line))
    {
        vector<char> row;
        for (char ch : line)
        {
            row.push_back(ch);
        }
        grid.push_back(row);
    }
    file.close();

    // Create mask to store antinode location counts
    int grid_dimensions = grid.size();
    vector<vector<bool>> mask(grid_dimensions, vector<bool>(grid_dimensions, false));
    // Create grid copy to print visual representation
    vector<vector<char>> grid_copy = grid;

    // Find locations of all antennae
    map<char, vector<vector<int>>> antenna_locations = find_antenna_locations(grid);

    // Find pairs of antennae and find antinode locations
    for (auto antenna_locations_type : antenna_locations)
    {
        char antenna_type = antenna_locations_type.first;
        vector<vector<int>> locations = antenna_locations_type.second;
        for (int i = 0; i < locations.size(); i++)
        {
            vector<int> antenna_a = locations[i];
            for (int j = i + 1; j < locations.size(); j++)
            {
                vector<int> antenna_b = locations[j];
                vector<int> offset = {antenna_b[0] - antenna_a[0],
                                      antenna_b[1] - antenna_a[1]};
                // PART B (for PART A multiplier = 1)
                for (int multiplier = 0; multiplier < grid_dimensions; multiplier++)
                {
                    vector<int> offset_multiplied = {offset[0] * multiplier,
                                                     offset[1] * multiplier};
                    // Apply offset in opposite directions to find antenna pair antinodes
                    vector<int> antinode_a = {antenna_a[0] - offset_multiplied[0],
                                              antenna_a[1] - offset_multiplied[1]};
                    vector<int> antinode_b = {antenna_b[0] + offset_multiplied[0],
                                              antenna_b[1] + offset_multiplied[1]};
                    // Add antinodes to total count if they lie within grid bounds
                    if (check_location_in_bounds(antinode_a, grid_dimensions))
                    {
                        mask[antinode_a[0]][antinode_a[1]] = true;
                        grid_copy[antinode_a[0]][antinode_a[1]] = '#';
                    }
                    if (check_location_in_bounds(antinode_b, grid_dimensions))
                    {
                        mask[antinode_b[0]][antinode_b[1]] = true;
                        grid_copy[antinode_b[0]][antinode_b[1]] = '#';
                    }
                }
            }
        }
    }

    // Count number of unique antinodes
    for (int i = 0; i < mask.size(); i++)
    {
        for (int j = 0; j < mask[i].size(); j++)
        {
            if (mask[i][j] == true)
            {
                total_antinodes += 1;
            }
        }
    }

    // Results
    cout << endl
         << "Total antinodes: " << total_antinodes << endl;

    cout << endl;
    print_grid(grid_copy);

    cout << endl;
    return 0;
}
