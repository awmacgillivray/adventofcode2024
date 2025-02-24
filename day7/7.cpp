#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

using namespace std;

bool perform_operations(vector<unsigned long long> numbers, unsigned long long target)
{
    // Check if vector has reduced to single element, and compare to target
    if (numbers.size() == 1)
    {
        if (numbers[0] == target)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    // Extract first two elements to perform "*" and "+" operations on
    unsigned long long first = numbers[0];
    unsigned long long second = numbers[1];
    // Catch negative values - caused by insufficiently small data types
    if (first < 0 || second < 0)
    {
        throw runtime_error("Equation values cannot be negative");
    }
    unsigned long long first_mul_second = first * second;
    unsigned long long first_add_second = first + second;
    vector<unsigned long long> mul_vector(numbers.begin() + 2, numbers.end());
    mul_vector.insert(mul_vector.begin(), first_mul_second);
    vector<unsigned long long> add_vector(numbers.begin() + 2, numbers.end());
    add_vector.insert(add_vector.begin(), first_add_second);
    // Recursively perform operations on new subtotals
    return perform_operations(mul_vector, target) || perform_operations(add_vector, target);
}

int main()
{
    // Initialise variables
    string line;
    const regex equation("([0-9]+\\:){1}|(\\ [0-9]+)");
    smatch result;
    unsigned long long calibration_result = 0;  // must be ULL to hold large values in data

    // Load data from file
    ifstream file("7_input.txt");
    while (getline(file, line))
    {
        unsigned long long equation_total;
        vector<unsigned long long> equation_numbers;
        // Iterative regex search on line to extract values
        string::const_iterator searchStart(line.cbegin());
        while (regex_search(searchStart, line.cend(), result, equation))
        {
            string match = result.str(0);
            if (match.substr(match.length() - 1) == ":")
            {
                equation_total = stoull(match.substr(0, match.length() - 1));
            }
            else
            {
                equation_numbers.push_back(stoi(match.substr(1, match.length())));
            }
            searchStart = result.suffix().first;
        }

        // Try combinations of operators to get equation total
        bool valid_equation = perform_operations(equation_numbers, equation_total);
        if (valid_equation)
        {
            calibration_result += equation_total;
        }
    }
    file.close();

    // Results
    cout << endl
         << "Total calibration result: " << calibration_result << endl;

    cout << endl;
    return 0;
}
