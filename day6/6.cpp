#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

class Guard
{
public:
    int start_x;
    int start_y;
    int pos_x;
    int pos_y;
    enum Direction direction;
    char obstacle = '#';
    vector<vector<char>> map;
    vector<vector<bool>> mask;

    Guard(
        int pos_x,
        int pos_y,
        enum Direction direction,
        vector<vector<char>> map,
        vector<vector<bool>> mask)
    {
        this->start_x = pos_x;
        this->start_y = pos_y;
        this->pos_x = pos_x;
        this->pos_y = pos_y;
        this->direction = direction;
        this->map = map;
        this->mask = mask;
    }

    bool advance()
    {
        switch (direction)
        {
        case UP:
            if (pos_x - 1 < 0)
            {
                return true;
            }
            if (map[pos_x - 1][pos_y] == obstacle)
            {
                direction = RIGHT;
                advance();
            }
            else
            {
                pos_x -= 1;
            }
            break;
        case DOWN:
            if (pos_x + 1 >= map.size())
            {
                return true;
            }
            if (map[pos_x + 1][pos_y] == obstacle)
            {
                direction = LEFT;
                advance();
            }
            else
            {
                pos_x += 1;
            }
            break;
        case LEFT:
            if (pos_y - 1 < 0)
            {
                return true;
            }
            if (map[pos_x][pos_y - 1] == obstacle)
            {
                direction = UP;
                advance();
            }
            else
            {
                pos_y -= 1;
            }
            break;
        case RIGHT:
            if (pos_y + 1 >= map[0].size())
            {
                return true;
            }
            if (map[pos_x][pos_y + 1] == obstacle)
            {
                direction = DOWN;
                advance();
            }
            else
            {
                pos_y += 1;
            }
            break;
        }
        mask[pos_x][pos_y] = true;
        return false;
    }
};

Guard find_guard(vector<vector<char>> map)
{
    // Create mask of map to track visited cells
    int map_dimensions = map.size();
    vector<vector<bool>> mask(map_dimensions, vector<bool>(map_dimensions, false));
    // Iterate through cells to find guard
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            if (map[i][j] == '^')
            {
                Guard guard(i, j, UP, map, mask);
                return guard;
            }
        }
    }
    throw runtime_error("Guard starting location not found");
}

void print_map(vector<vector<char>> mask)
{
    /* Debugging function to print out visual representation of map */
    for (auto row : mask)
    {
        for (auto item : row)
        {
            cout << item;
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    // Initialise variables
    string line;
    vector<vector<char>> map;
    int total_visited = 0;

    // Load data from file
    ifstream file("6_input.txt");
    while (getline(file, line))
    {
        vector<char> row;
        for (char ch : line)
        {
            row.push_back(ch);
        }
        map.push_back(row);
    }

    // Initialise guard object with starting location using map
    Guard guard = find_guard(map);

    // Follow guard's path
    while (true)
    {
        bool done = guard.advance();
        if (done)
        {
            // Add starting position to mask in case it was missed
            guard.mask[guard.start_x][guard.start_y] = true;
            break;
        }
    }

    // Results
    for (int i = 0; i < guard.mask.size(); i++)
    {
        for (int j = 0; j < guard.mask[i].size(); j++)
        {
            if (guard.mask[i][j] == true)
            {
                total_visited += 1;
            }
        }
    }

    cout << "Total cells visited: " << total_visited << endl;

    cout << endl;
    return 0;
}
