#ifndef HEADER_H
#define HEADER_H

#define PI 3.14159265358979323846

#define PIN_SDA PF_0
#define PIN_SCL PF_1

#define GYRO_UPDATE_PERIOD 5
#define GYRO_N_SAMPLE 3
#define GYRO_RAD_TOLERANCE 0.03

void read_csv(double *gyro);

#endif