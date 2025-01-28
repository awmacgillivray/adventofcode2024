#ifndef MY_CLASS_H
#define MY_CLASS_H

#include <string>
#include <vector>

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

#endif
