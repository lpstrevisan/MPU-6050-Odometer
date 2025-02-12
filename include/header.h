#ifndef HEADER_H
#define HEADER_H

#include <MPU6050.h>

#define PIN_SDA PF_0
#define PIN_SCL PF_1

#define PI 3.14159265358979323846
#define ALPHA 0.8              // Low-pass filter coefficient
#define CALIBRATE_SAMPLE 100

void calibrate_gyro();
void read_gyro();
void filter_gyro();
void limit_angle();

double angular_velocity = 0.0;
double angle = 0.0;
double gyro_z_rad = 0.0;
double gyro_offset_z;

#endif