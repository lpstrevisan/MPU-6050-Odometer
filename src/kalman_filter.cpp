#include <header.h>

KalmanFilter::KalmanFilter(double bias, double measure, Timer time) {            
    m_Q_bias = bias;
    m_R_measure = measure;

    m_K_value = 0;
    m_K_bias = 0;

    m_P[0][0] = 0;
    m_P[0][1] = 0;
    m_P[1][0] = 0;
    m_P[1][1] = 0;

    m_last_time = time.elapsed_time().count() / 1000000.0;
}

double KalmanFilter::update(double gyro_measure, Timer time) {
    double current_time = time.elapsed_time().count() / 1000000.0;
    double dt = (current_time - m_last_time);

    m_K_value += (gyro_measure - m_K_bias) * dt;

    m_P[0][0] += (m_P[1][1] + m_P[0][1]) * dt + m_Q_bias * dt;
    m_P[0][1] -= m_P[1][1] * dt;
    m_P[1][0] -= m_P[1][1] * dt;
    m_P[1][1] += m_Q_bias * dt;

    double S = m_P[0][0] + m_R_measure;
    double K_gain[2];

    K_gain[0] = m_P[0][0] / S;
    K_gain[1] = m_P[1][0] / S;

    double y = gyro_measure - m_K_value;

    m_K_value += K_gain[0] * y;
    m_K_bias += K_gain[1] * y;

    m_P[0][0] -= K_gain[0] * m_P[0][0];
    m_P[0][1] -= K_gain[0] * m_P[0][1];
    m_P[1][0] -= K_gain[1] * m_P[0][0];
    m_P[1][1] -= K_gain[1] * m_P[0][1];

    m_last_time = current_time;

    return m_K_value;
}