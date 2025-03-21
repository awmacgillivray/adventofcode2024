#include "../common.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <set>
#include <list>

using namespace std;

vector<map<int, set<int>>> add_pages_to_transition_maps(
    int page1,
    int page2,
    vector<map<int, set<int>>> maps)
{
    /*
    Add page precedence rules to forward and backward transition maps
    */
    map<int, set<int>> fwd_transition_map = maps[0];
    map<int, set<int>> bwd_transition_map = maps[1];
    if (!fwd_transition_map.contains(page1))
    {
        fwd_transition_map[page1] = set<int>{page2};
    }
    else
    {
        fwd_transition_map.at(page1).insert(page2);
    }
    if (!bwd_transition_map.contains(page2))
    {
        bwd_transition_map[page2] = set<int>{page1};
    }
    else
    {
        bwd_transition_map.at(page2).insert(page1);
    }
    return {fwd_transition_map, bwd_transition_map};
}

tuple<bool, int, int> check_update_order(
    vector<int> update_pages_int,
    vector<map<int, set<int>>> maps)
{
    /*
    Check order of page numbers
    Returns true/false if valid along with relevant indices
    */
    map<int, set<int>> fwd_transition_map = maps[0];
    map<int, set<int>> bwd_transition_map = maps[1];
    for (int i = 0; i < update_pages_int.size(); i++)
    {
        int page = update_pages_int[i];
        // check previous pages for correct order
        for (int j = 0; j < i; j++)
        {
            int bwd_page = update_pages_int[j];
            if (bwd_transition_map.contains(page) &&
                !bwd_transition_map.at(page).contains(bwd_page))
            {
                return {false, i, j};
            }
        }
        // check subsequent pages for correct order
        for (int j = i + 1; j < update_pages_int.size(); j++)
        {
            int fwd_page = update_pages_int[j];
            if (fwd_transition_map.contains(page) &&
                !fwd_transition_map.at(page).contains(fwd_page))
            {
                return {false, i, j};
            }
        }
    }
    return {true, 0, 0};
}

int main()
{
    // initialise variables
    string line;
    const regex exp_transition("[0-9]{2}\\|[0-9]{2}");
    const regex exp_update("([0-9]{2}\\,)+[0-9]{2}");
    map<int, set<int>> fwd_transition_map;
    map<int, set<int>> bwd_transition_map;
    vector<map<int, set<int>>> maps = {fwd_transition_map, bwd_transition_map};
    int total = 0;
    int total_fixed = 0;

    // load data from file
    ifstream file("5_input.txt");
    while (getline(file, line))
    {
        // build transition maps of page printing order
        if (regex_match(line, exp_transition))
        {
            int page1 = stoi(line.substr(0, 2));
            int page2 = stoi(line.substr(3, 2));
            maps = add_pages_to_transition_maps(page1, page2, maps);
        }
        // check update sequence for correct order
        else if (regex_match(line, exp_update))
        {
            vector<string> update_pages = split_string(line, ",");
            vector<int> update_pages_int;
            for (string page : update_pages)
            {
                update_pages_int.push_back(stoi(page));
            }
            // part A
            tuple<bool, int, int> result = check_update_order(update_pages_int, maps);
            if (get<0>(result) == true)
            {
                total += update_pages_int[update_pages_int.size() / 2];
                // cout << line << endl;
            }
            // part B
            else
            {
                // find potential valid order and new total
                vector<int> new_update_pages = update_pages_int;
                // swap offending elements, check validity, and iterate
                while (true)
                {
                    int index1 = get<1>(result);
                    int index2 = get<2>(result);
                    vector<int> temp = new_update_pages;
                    new_update_pages[index1] = temp[index2];
                    new_update_pages[index2] = temp[index1];
                    result = check_update_order(new_update_pages, maps);
                    if (get<0>(result) == true)
                    {
                        total_fixed += new_update_pages[new_update_pages.size() / 2];
                        break;
                    }
                }
            }
        }
    }

    // result
    cout << endl
         << "Total: " << total;
    cout << endl
         << "Total fixed: " << total_fixed;
    cout << endl;
    return 0;
}
