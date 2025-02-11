#include "lib_test_main.h"

void flag_gyro() {
    is_ready = true;
}

void read_gyro(double gyro_z) {
    // Convert gyro data from degrees/sec to radians/sec
    gyro_z_rad = gyro_z * DEG_TO_RAD;
}

void filter_gyro() {
    // Apply simple low-pass filter
    angular_velocity = (ALPHA * angular_velocity) + ((1 - ALPHA) * gyro_z_rad);
}
