#include "../common.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string>

using namespace std;

int main() {
    // initialise variables
    string line;
    const regex exp("mul\\([0-9]+\\,[0-9]+\\)");
    smatch result;
    int total = 0;

    // read input from file
    ifstream file("3_input.txt");
    while (getline (file, line)) {
        // perform iterative regex search for expected pattern
        string::const_iterator searchStart(line.cbegin());
        while (regex_search(searchStart, line.cend(), result, exp)) {
            string match = result.str(0);
            // extract numbers for multiplication
            string numbers = match.substr(4, match.length() - 5);
            vector<string> numbers_list = split_string(numbers, ",");
            total += (stoi(numbers_list[0]) * stoi(numbers_list[1]));
            // cout << (searchStart == line.begin() ? "" : " ") << result1[0];
            searchStart = result.suffix().first;
        }
    }

    cout << "Total: " << total << endl;
    cout << endl;
    return 0;
}
