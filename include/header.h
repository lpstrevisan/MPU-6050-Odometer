#ifndef HEADER_H
#define HEADER_H

#include <mbed.h>

#define PI 3.14159265358979323846

#define PIN_SDA PF_0
#define PIN_SCL PF_1

#define GYRO_UPDATE_PERIOD 5
#define GYRO_N_SAMPLE 3
#define GYRO_RAD_TOLERANCE 0.03

void read_csv(double *gyro);

class KalmanFilter {
    public:
        KalmanFilter(double, double, Timer);
        double update(double, Timer);

    private:
        double m_Q_bias, m_R_measure, m_P[2][2]; 
        double m_K_value, m_K_bias;
        double m_last_time;
};

#endif