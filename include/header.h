#ifndef HEADER_H
#define HEADER_H

#include <MPU6050.h>
#include <chrono>

#define PIN_SDA PF_0
#define PIN_SCL PF_1

#define DEG_TO_RAD 0.0174533   // Conversion factor from degrees to radians
#define ALPHA 0.8              // Low-pass filter coefficient
#define CALIBRATE_SAMPLES 100

void calibrate_gyro();
void flag_gyro();
void read_gyro();
void filter_gyro();

volatile double angular_velocity = 0.0;
volatile double angle = 0.0;
volatile double gyro_z_rad = 0.0;
volatile bool is_ready = false;
double gyro_offset_z;

#endif