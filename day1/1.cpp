#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <fstream>

using namespace std;

int main()
{
    // initialise variables
    vector<int> list1;
    vector<int> list2;
    vector<int> diff_list;
    int diff_total;
    vector<int> sim_list;
    int sim_total;

    string line;
    string delimiter = "   ";
    size_t pos;
    int num1;
    int num2;

    // read input from file
    ifstream file("1_input.txt");
    while (getline(file, line))
    {
        pos = line.find(delimiter);
        num1 = stoi(line.substr(0, pos));
        num2 = stoi(line.substr(pos + delimiter.length(), line.length()));
        // cout << num1 << " " << num2 << endl;  // check values were loaded correctly
        list1.push_back(num1);
        list2.push_back(num2);
    }
    file.close();

    // sort vectors
    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());

    // calculate and print item differences
    for (int i = 0; i < list1.size(); i++)
    {
        diff_list.push_back((abs(list1[i] - list2[i])));
    }

    // sum differences
    cout << "Total difference:" << endl
         << "> ";
    diff_total = reduce(diff_list.begin(), diff_list.end());
    cout << diff_total << endl;

    // find similarity score
    for (int i = 0; i < list1.size(); i++)
    {
        int target = list1[i];
        int num_occur = 0;
        auto it = find(list2.begin(), list2.end(), target);
        while (it != list2.end())
        {
            num_occur += 1;
            it = find(it + 1, list2.end(), target);
        }

        sim_list.push_back(list1[i] * num_occur);
    }
    cout << "Similarity score:" << endl
         << "> ";
    sim_total = reduce(sim_list.begin(), sim_list.end());
    cout << sim_total << endl;

    cout << endl;
    return 0;
}
