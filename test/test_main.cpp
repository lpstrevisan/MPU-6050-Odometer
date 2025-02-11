#include <unity.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include "lib_test_main.h"

using namespace std;

void read_csv(const string& filename, vector<pair<double, double>>& data) {
    ifstream file(filename);
    string line;
    
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return;
    }
    
    while (getline(file, line)) {
        stringstream ss(line);
        double input, expected;
        char comma;
        if (ss >> input >> comma >> expected) {
            data.emplace_back(input, expected);
        }
    }
    file.close();
}


int main() {
    vector<pair<double, double>> test_data;
    read_csv("filtered_robot_log.csv", test_data);

    for (const auto& [input, expected] : test_data) {
        read_gyro(input);
        filter_gyro();
        cout << "Input: " << input << " | Computed: " << angle << " | Expected: " << expected << endl;
        sleep(SAMPLE_TIME);
    }

    return 0;
}
