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
    const regex exp_A("mul\\([0-9]+\\,[0-9]+\\)");
    const regex exp_B("mul\\([0-9]+\\,[0-9]+\\)|do\\(\\)|don\\'t\\(\\)");
    smatch result;
    int total = 0;
    bool do_mul = true;

    // read input from file
    ifstream file("3_input.txt");
    while (getline (file, line)) {
        // perform iterative regex search for expected pattern
        string::const_iterator searchStart(line.cbegin());
        while (regex_search(searchStart, line.cend(), result, exp_B)) { // A or B matcher
            string match = result.str(0);
            if (match == "do()") {
                do_mul = true;
            } else if (match == "don't()") {
                do_mul = false;
            } else {
                // extract numbers for multiplication
                string numbers = match.substr(4, match.length() - 5);
                vector<string> numbers_list = split_string(numbers, ",");
                // check if do is enabled, and if so add to total // PART B
                if (do_mul) {
                    total += (stoi(numbers_list[0]) * stoi(numbers_list[1]));
                }
            }
            // cout << (searchStart == line.begin() ? "" : " ") << result1[0];
            searchStart = result.suffix().first;
        }
    }
    file.close();

    cout << "Total: " << total << endl;
    cout << endl;
    return 0;
}
