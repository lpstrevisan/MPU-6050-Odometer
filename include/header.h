#ifndef HEADER_H
#define HEADER_H

#include <mbed.h>

#define PI 3.14159265358979323846

#define PIN_SDA PF_0
#define PIN_SCL PF_1

#define GYRO_UPDATE_PERIOD 0.005
#define GYRO_BIAS 0.003
#define GYRO_MEASURE 0.03

class KalmanFilter {
    public:
        KalmanFilter(double, double);
        double update(double, Timer);

    private:
        double m_Q_bias, m_R_measure, m_P[2][2]; 
        double m_K_value, m_K_bias;
};

void read_csv(double *);

#endif