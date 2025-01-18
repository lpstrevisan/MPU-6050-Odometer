#include <MPU6050.h>
#include <header.h>
#include <fstream>

MPU6050 mpu(PIN_SDA, PIN_SCL);

int main()
{
    Timer time;
    Ticker gyro_update;
    double gyro_z_axis_accumulated, gyro_move;

    if(!mpu.initialize()) {
        return 1;
    }

    time.start();

    gyro_update.attach_us([&]() -> double { 
        double gyro[3];
            
        gyro_z_axis_accumulated = 0;
        gyro_move = 0;                                 
            
        for(int i = 0; i < GYRO_N_SAMPLE; i++) {
            //mpu.readGyro(gyro); 
            read_csv(&gyro[2]);                         
            gyro_z_axis_accumulated += gyro[2] * PI / 180.0; 
        }

        gyro_z_axis_accumulated /= GYRO_N_SAMPLE;

        if(gyro_z_axis_accumulated < GYRO_RAD_TOLERANCE) {
            gyro_z_axis_accumulated = 0;
        }

        double dt = time.elapsed_time().count() / 1000000.0;

        gyro_move += gyro_z_axis_accumulated * dt;

        std::ofstream file("output.txt");

        if(!file.is_open()) {
            return 1;
        }

        file << gyro_move << std::endl;

        file.close();

        time.reset();
    }, GYRO_UPDATE_PERIOD);

    return 0;
}