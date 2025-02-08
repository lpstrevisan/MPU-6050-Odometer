#ifndef HEADER_H
#define HEADER_H

#include <MPU6050.h>

#define PIN_SDA PF_0
#define PIN_SCL PF_1

#define DEG_TO_RAD 0.0174533f  // Conversion factor from degrees to radians
#define SAMPLE_TIME 0.005f      // 5ms sample time
#define ALPHA 0.8f             // Low-pass filter coefficient

void flag_gyro();
void read_gyro();
void filter_gyro();

#endif