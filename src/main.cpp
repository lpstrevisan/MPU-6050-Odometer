#include <MPU6050.h>
#include <rtos.h>
#include <header.h>
#include <fstream>
#include <condition_variable>

using namespace std;

MPU6050 mpu(PIN_SDA, PIN_SCL);
KalmanFilter kf(GYRO_BIAS, GYRO_MEASURE);
Timer gyro_time;

int main()
{
    if(!mpu.initialize()) {
        return 1;
    }

    Ticker gyro_update;
    double gyro_move, gyro_z_axis = 0;
    Thread gyro_measure_csv;
    Mutex gyro_write;
    ofstream output_file("output.txt");
    string line, cell;

    if(!output_file) {
        return 1;
    }

    gyro_time.start();

    /*gyro_update.attach([&]() -> double { 
        double gyro[3];                              
        mpu.readGyro(gyro);                       
        gyro_z_axis = gyro[2] * PI / 180.0;
    }, GYRO_UPDATE_PERIOD);*/

    gyro_measure_csv.start(callback(read_csv, &gyro_z_axis));

    while(1) {
        gyro_move = kf.update(gyro_z_axis, gyro_time);

        output_file << gyro_move << "\n";

        gyro_time.reset();
    }

    output_file.close();

    return 0;
}