#include <header.h>
#include <chrono>

MPU6050 mpu(PIN_SDA, PIN_SCL); // Assuming I2C is connected to PF_0 (SDA) and PF_1 (SCL)
Ticker gyroTicker;
volatile double angular_velocity = 0.0f;
volatile double angle = 0.0f;
volatile double gyro_z_rad = 0.0f;
volatile bool is_ready = false;

int main() {
    mpu.initialize();
    gyroTicker.attach(&flag_gyro, SAMPLE_TIME);
    
    while (true) {
        if(is_ready) {
            read_gyro();
            filter_gyro();
        }
        // Integrate to get angular position (simple Euler integration)
        angle += angular_velocity * SAMPLE_TIME;

        printf("Angular Position (rad): %f\n", angle);
        ThisThread::sleep_for(4ms);
    }

    return 0;
}

void flag_gyro() {
    is_ready = true;
}

void read_gyro() {
    double gyro_data[3] = {0};
    mpu.readGyro(gyro_data);
    
    // Convert gyro data from degrees/sec to radians/sec
    gyro_z_rad = gyro_data[2] * DEG_TO_RAD;
}

void filter_gyro() {
    // Apply simple low-pass filter
    angular_velocity = (ALPHA * angular_velocity) + ((1 - ALPHA) * gyro_z_rad);
}
