#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <mbed.h>

using namespace std;

void read_csv(double *gyro) {
    ifstream file("../include/filtered_robot_log.csv");

    if (!file.is_open()) {
        printf("file don't opened");
    }

    std::string row;

    while(std::getline(file, row)) {
        std::stringstream ss(row);
        std::string before_comma;
        
        if(std::getline(ss, before_comma, ',')) {
            *gyro = std::stod(before_comma);
            ThisThread::sleep_for(5ms);
        }
    }
        
    file.close();
}
