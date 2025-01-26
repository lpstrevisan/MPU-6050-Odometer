#include <header.h>
#include <fstream>
#include <sstream>

using namespace std;

void read_csv(double *gyro) {
    ifstream input_file("filtered_robot_log.csv");
    string line, cell;

    getline(input_file, line);

    while(getline(input_file, line)) {
        stringstream line_stream(line);

        if(getline(line_stream, cell, ',')) {
            *gyro = stod(cell) * PI / 180.0;
            ThisThread::sleep_for(5ms);
        }
    }

    input_file.close();
}
