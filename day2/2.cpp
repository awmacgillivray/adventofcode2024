#include "../common.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <fstream>

using namespace std;

bool check_report_safe(vector<int> report) {
    int increase = 0;
    int decrease = 0;
    bool unsafe_flag = false;

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
    if ((unsafe_flag == true) || (increase > 0 && decrease > 0)) {
        return false;
    } else {
        return true;
    }
}

int main() {
    string line;
    vector<int> report;
    int safe_reports = 0;
    int unsafe_reports = 0;
    int safe_reports_extra = 0;

    // read input from file
    ifstream file("2_input.txt");
    while (getline (file, line)) {
        report.clear();

        // convert split strings into ints
        // cout << line << endl;
        vector<string> split = split_string(line, " ");
        for (auto s : split) {
            report.push_back(stoi(s));
        }

        // check if levels are increasing or decreasing only and minimally
        bool safe = check_report_safe(report);
        if (safe) {
            safe_reports++;
            // cout << "^safe" << endl;
        } else {
            unsafe_reports++;
            for (int i = 0; i < report.size(); i++) {
                vector<int> report2 = report;
                report2.erase(report2.begin() + i);
                safe = check_report_safe(report2);
                if (safe) {
                    safe_reports_extra++;
                    break;
                }
            }
            // cout << "^unsafe" << endl;
        }
    }
    file.close();

    cout << "Safe reports: " << safe_reports << endl;
    cout << "Unsafe reports: " << unsafe_reports << endl;
    cout << "Safe reports extra: " << safe_reports_extra << endl;

    cout << endl;
    return 0;
}
