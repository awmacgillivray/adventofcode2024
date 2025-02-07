#include "../common.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <set>
#include <list>

using namespace std;

int main()
{
    // initialise variables
    string line;
    const regex exp_transition("[0-9]{2}\\|[0-9]{2}");
    const regex exp_update("([0-9]{2}\\,)+[0-9]{2}");
    map<int, set<int>> fwd_transition_map;
    map<int, set<int>> bwd_transition_map;
    int total = 0;

    // load data from file
    ifstream file("5_input.txt");
    while (getline(file, line))
    {
        // build transition maps of page printnig order
        if (regex_match(line, exp_transition))
        {
            int page1 = stoi(line.substr(0, 2));
            int page2 = stoi(line.substr(3, 2));
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
        }
        // check update sequence for correct order
        else if (regex_match(line, exp_update))
        {
            bool valid_update = true;
            vector<string> update_pages = split_string(line, ",");
            for (int i = 0; i < update_pages.size(); i++)
            {
                int page = stoi(update_pages[i]);
                for (int j = 0; j < i; j++)
                {
                    int bwd_page = stoi(update_pages[j]);
                    if (bwd_transition_map.contains(page) &&
                        !bwd_transition_map.at(page).contains(bwd_page))
                    {
                        valid_update = false;
                        break;
                    }
                }
                for (int j = i + 1; j < update_pages.size(); j++)
                {
                    int fwd_page = stoi(update_pages[j]);
                    if (fwd_transition_map.contains(page) &&
                        !fwd_transition_map.at(page).contains(fwd_page))
                    {
                        valid_update = false;
                        break;
                    }
                }
                if (!valid_update)
                {
                    break;
                }
            }
            if (valid_update)
            {
                total += stoi(update_pages[update_pages.size() / 2]);
                cout << line << endl;
            }
        }
    }

    // result
    cout << "Total: " << total << endl;
    cout << endl;
    return 0;
}
