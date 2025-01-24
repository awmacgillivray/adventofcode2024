#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <iostream>
#include <fstream>

using namespace std;

vector<string> split_string(string input, string delimiter) {
    vector<string> strings;
    size_t pos;
    string str1;
    string str2;
    while (true) {
        pos = input.find(delimiter);
        if (pos == -1) {
            strings.push_back(input);
            return strings;
        }
        str1 = input.substr(0, pos);
        str2 = input.substr(pos + delimiter.length(), input.length());
        strings.push_back(str1);
        input = str2;
    }
}

int main() {
    string line;
    vector<int> report;
    int safe_reports = 0;
    int unsafe_reports = 0;
    bool unsafe_flag;
    int increase;
    int decrease;

    // read input from file
    ifstream file("2_input.txt");
    while (getline (file, line)) {
        increase = 0;
        decrease = 0;
        unsafe_flag = false;
        report.clear();

        // cout << line << endl;
        vector<string> split = split_string(line, " ");
        for (auto s : split) {
            report.push_back(stoi(s));
        }

        // check if levels are increasing or decreasing only and minimally
        for (int i = 0; i < report.size() - 1; i++) {
            if (report[i+1] > report[i]) {
                increase++;
            } else if (report[i+1] < report[i]) {
                decrease++;
            }
            if ((abs(report[i+1] - report[i]) > 3) ||
                (abs(report[i+1] - report[i]) == 0)) {
                unsafe_flag = true;
                break;
            }
        }
        if (unsafe_flag == true) {
            unsafe_reports++;
            // cout << "unsafe" << endl;
        } else if (increase > 0 && decrease > 0) {
            unsafe_reports++;
            // cout << "unsafe" << endl;
        } else {
            safe_reports++;
            // cout << "safe" << endl;
        }
    }
    file.close();

    cout << "Safe reports: " << safe_reports << endl;
    cout << "Unsafe reports: " << unsafe_reports << endl;

    cout << endl;
    return 0;
}
