#include <iostream>
#include <fstream>
#include <vector>
#include <map>
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
    vector<vector<char>> grid;
    vector<vector<bool>> mask;
    map<int, map<int, Direction>> encountered_obstacles;

    Guard(
        int pos_x,
        int pos_y,
        enum Direction direction,
        vector<vector<char>> grid,
        vector<vector<bool>> mask)
    {
        this->start_x = pos_x;
        this->start_y = pos_y;
        this->pos_x = pos_x;
        this->pos_y = pos_y;
        this->direction = direction;
        this->grid = grid;
        this->mask = mask;
    }

    int advance()
    {
        int next_x;
        int next_y;
        enum Direction next_direction;

        switch (direction)
        {
        case UP:
            next_x = pos_x - 1;
            next_y = pos_y;
            next_direction = RIGHT;
            if (next_x < 0) { return 1; }
            break;
        case DOWN:
            next_x = pos_x + 1;
            next_y = pos_y;
            next_direction = LEFT;
            if (next_x >= grid.size()) { return 1; }
            break;
        case LEFT:
            next_x = pos_x;
            next_y = pos_y - 1;
            next_direction = UP;
            if (next_y < 0) { return 1; }
            break;
        case RIGHT:
            next_x = pos_x;
            next_y = pos_y + 1;
            next_direction = DOWN;
            if (next_y >= grid[0].size()) { return 1; }
            break;
        }

        if (grid[next_x][next_y] == obstacle)
        {
            if (
                encountered_obstacles.contains(next_x) &&
                encountered_obstacles[next_x].contains(next_y) &&
                encountered_obstacles[next_x][next_y] == next_direction
            ){
                // Loop detected
                return 2;
            } else {
                encountered_obstacles[next_x][next_y] = next_direction;
            }
            direction = next_direction;
            advance();
        }
        else
        {
            pos_x = next_x;
            pos_y = next_y;
        }

        mask[pos_x][pos_y] = true;
        return 0;
    }
};

Guard find_guard(vector<vector<char>> grid)
{
    // Create mask of grid to track visited cells
    int grid_dimensions = grid.size();
    vector<vector<bool>> mask(grid_dimensions, vector<bool>(grid_dimensions, false));
    // Iterate through cells to find guard
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == '^')
            {
                Guard guard(i, j, UP, grid, mask);
                return guard;
            }
        }
    }
    throw runtime_error("Guard starting location not found");
}

void print_grid(vector<vector<char>> mask)
{
    /* Debugging function to print out visual representation of grid */
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
    vector<vector<char>> grid;
    int total_visited = 0;
    int total_loops = 0;

    // Load data from file
    ifstream file("6_input.txt");
    while (getline(file, line))
    {
        vector<char> row;
        for (char ch : line)
        {
            row.push_back(ch);
        }
        grid.push_back(row);
    }

    // Initialise guard object with starting location using grid
    Guard guard = find_guard(grid);

    // Follow guard's path - PART A
    while (true)
    {
        int flag = guard.advance();
        // Reached out of bounds
        if (flag == 1)
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

    // Find possible obstructions to cause guard loop - PART B
    vector<vector<bool>> mask_copy = guard.mask;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (i == guard.start_x && j == guard.start_y)
            {
                continue;
            }
            else if (mask_copy[i][j] == false)
            {
                continue;
            }
            vector<vector<char>> new_grid = grid;
            new_grid[i][j] = '#';
            Guard guard = find_guard(new_grid);
            while (true)
            {
                int flag = guard.advance();
                // Reached out of bounds
                if (flag == 1)
                {
                    // Valid path exists, ignore
                    break;
                // Loop detected
                } else if (flag == 2)
                {
                    total_loops += 1;
                    break;
                }
            }
        }
    }
    // Results
    cout << "Total possible loops: " << total_loops << endl;

    cout << endl;
    return 0;
}
