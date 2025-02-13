#include <header.h>

const auto sample_time = 5ms; // define frenquency (1 / 200Hz = 0,005s = 5ms)

MPU6050 mpu(PIN_SDA, PIN_SCL); // Assuming I2C is connected to PF_0 (SDA) and PF_1 (SCL)


int main() {
    mpu.initialize();
    calibrate_gyro();
    
    while (true) {
        read_gyro();
        filter_gyro();

        // Integrate to get angular position (simple Euler integration)
        angle += angular_velocity * (sample_time.count() / 1000.0);
        limit_angle();

        printf("Angular Position (rad): %f\n", angle);

        ThisThread::sleep_for(sample_time);
    }

    return 0;
}


void calibrate_gyro() {
    double gyro_raw[3], sum = 0;

    for(int i = 0; i < CALIBRATE_SAMPLE; i++) {
        mpu.readGyro(gyro_raw);
        sum += gyro_raw[2];
    }

    gyro_offset_z = sum / CALIBRATE_SAMPLE;
}

void read_gyro() {
    double gyro_data[3];
    mpu.readGyro(gyro_data);
    
    gyro_z_rad = (gyro_data[2] - gyro_offset_z) * (PI / 180.0); // degrees per second to radians per second 
}

void filter_gyro() {
    // Apply simple low-pass filter
    angular_velocity = (ALPHA * angular_velocity) + ((1 - ALPHA) * gyro_z_rad);
}

//limit an angle between -PI and +PI
void limit_angle() {
    if(angle > PI) {
        angle -= 2.0 * PI;
    }
    else if(angle < -PI) {
        angle += 2.0 * PI;
    }
}