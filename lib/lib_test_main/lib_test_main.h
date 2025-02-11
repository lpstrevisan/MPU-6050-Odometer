#ifndef LIB_TEST_MAIN_H
#define LIB_TEST_MAIN_H

#define DEG_TO_RAD 0.0174533f  // Conversion factor from degrees to radians
#define SAMPLE_TIME 0.005f      // 5ms sample time
#define ALPHA 0.8f             // Low-pass filter coefficient

void read_gyro(double);
void filter_gyro();

volatile double angular_velocity = 0.0f;
volatile double angle = 0.0f;
volatile double gyro_z_rad = 0.0f;
volatile bool is_ready = false;

#endif