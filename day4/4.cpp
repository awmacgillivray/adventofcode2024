#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> find_neighbours(vector<vector<char>> table, vector<int> start, char target)
{
    vector<vector<int>> match_offsets;
    // search in 8 neighbouring cells for target character
    for (int offset1 : {-1, 0, 1})
    {
        for (int offset2 : {-1, 0, 1})
        {
            if (offset1 == 0 and offset2 == 0)
            {
                continue;
            }
            int index1 = start[0] + offset1;
            int index2 = start[1] + offset2;
            // check if indices go outside boundaries of table
            if (
                (index1 < 0) ||
                (index1 >= table.size()) ||
                (index2 < 0) ||
                (index2 >= table[index1].size()))
            {
                continue;
            }
            if (table[index1][index2] == target)
            {
                match_offsets.push_back(vector<int>{offset1, offset2});
            }
        }
    }
    return match_offsets;
}

int main()
{
    // initialise variables
    vector<vector<char>> word_search;
    int total_matches = 0;
    string line;

    // load data from file
    ifstream file("4_input.txt");
    while (getline(file, line))
    {
        vector<char> row;
        for (char ch : line)
        {
            row.push_back(ch);
        }
        word_search.push_back(row);
    }

    // find occurences of 'X' and search from there
    for (int i = 0; i < word_search.size(); i++)
    {
        for (int j = 0; j < word_search[i].size(); j++)
        {
            if (word_search[i][j] == 'X')
            {
                // find location of any neighbouring 'M' characters
                vector<vector<int>> matches_M = find_neighbours(word_search, vector<int>{i, j}, 'M');
                if (matches_M.size() == 0)
                {
                    continue;
                }
                for (int m = 0; m < matches_M.size(); m++)
                {
                    vector<int> match_M = matches_M[m];
                    int offset1 = match_M[0];
                    int offset2 = match_M[1];
                    // scale offset to search for subsequent 'A' and 'S' characters
                    int index1 = i + offset1 * 2;
                    int index2 = j + offset2 * 2;
                    if (
                        (0 <= index1) &&
                        (index1 < word_search.size()) &&
                        (0 <= index2) &&
                        (index2 < word_search[i].size()) &&
                        ((word_search[index1][index2]) == 'A'))
                    {
                        index1 = i + offset1 * 3;
                        index2 = j + offset2 * 3;
                        if (
                            (0 <= index1) &&
                            (index1 < word_search.size()) &&
                            (0 <= index2) &&
                            (index2 < word_search[i].size()) &&
                            (word_search[index1][index2] == 'S'))
                        {
                            total_matches++;
                        }
                    }
                }
            }
        }
    }

    // result
    cout << "Total matches: " << total_matches << endl;

    cout << endl;
    return 0;
}
