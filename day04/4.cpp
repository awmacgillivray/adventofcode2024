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
            if (offset1 == 0 and offset2 == 0) // ignore own cell
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
    // return vector of index matches
    return match_offsets;
}

int main()
{
    // initialise variables
    vector<vector<char>> word_search;
    int total_xmas_matches = 0;
    int total_mas_matches = 0;
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

    int i_size = word_search.size();
    for (int i = 0; i < i_size; i++)
    {
        int j_size = word_search[i].size();
        for (int j = 0; j < j_size; j++)
        {
            // find occurences of 'X' and search from there - PART A
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
                        (index1 < i_size) &&
                        (0 <= index2) &&
                        (index2 < j_size) &&
                        (word_search[index1][index2] == 'A'))
                    {
                        index1 = i + offset1 * 3;
                        index2 = j + offset2 * 3;
                        if (
                            (0 <= index1) &&
                            (index1 < i_size) &&
                            (0 <= index2) &&
                            (index2 < j_size) &&
                            (word_search[index1][index2] == 'S'))
                        {
                            total_xmas_matches++;
                        }
                    }
                }
            }
            // find occurences of 'A' and search from there - PART B
            if (word_search[i][j] == 'A')
            {
                // find location of any neighbouring 'M' characters
                vector<vector<int>> matches_M = find_neighbours(word_search, vector<int>{i, j}, 'M');
                // track occurences of 'M-A-S' matches
                int num_diag_matches = 0;
                for (int m = 0; m < matches_M.size(); m++)
                {
                    vector<int> match_M = matches_M[m];
                    int offset1 = match_M[0];
                    int offset2 = match_M[1];
                    if ((offset1 == 0) || (offset2 == 0)) // ignore 'M' matches on the vertical/horizontal
                    {
                        continue;
                    }
                    int index1 = i - offset1;
                    int index2 = j - offset2;
                    // check bounds and if character opposite 'M' is an 'S'
                    if (
                        (0 <= index1) &&
                        (index1 < i_size) &&
                        (0 <= index2) &&
                        (index2 < j_size) &&
                        (word_search[index1][index2] == 'S'))
                    {
                        num_diag_matches++;
                    }
                }
                if (num_diag_matches == 2) // must be exactly 2 diagonal 'M-A-S' matches
                {
                    total_mas_matches++;
                }
            }
        }
    }

    // result
    cout << "Total XMAS matches: " << total_xmas_matches << endl;
    cout << "Total X-MAS matches: " << total_mas_matches << endl;

    cout << endl;
    return 0;
}
