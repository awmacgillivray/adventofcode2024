#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    // initialise variables
    string line;
    vector<vector<char>> map;

    // load data from file
    ifstream file("6_input_test.txt");
    while (getline(file, line))
    {
        vector<char> row;
        for (char ch : line)
        {
            row.push_back(ch);
        }
        map.push_back(row);
    }

    // find starting location of guard

    cout << endl;
    return 0;
}
