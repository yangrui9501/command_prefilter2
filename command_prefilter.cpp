#include "command_prefilter.h"

// Parameters Set Up for Third-Order Command Prefilter
void CommandPrefilter::init(double cutoff_freq, double sample_interval)
{
    fc = cutoff_freq;
    T = sample_interval;

    tau = 1.0 / (2.0 * PI * fc); // Time Constant

    Eigen::Matrix3d Ac;
    Eigen::Vector3d Bc;
    Eigen::Matrix3d I = Eigen::Matrix3d::Identity();

    // Continuous-time system matrix
    Ac.fill(0.0);
    Ac(0, 1) = 1.0;
    Ac(1, 2) = 1.0;
    Ac(2, 0) = -1.0 / (tau * tau * tau);
    Ac(2, 1) = -3.0 / (tau * tau);
    Ac(2, 2) = -3.0 / (tau);

    // Continuous-time input matrix
    Bc.fill(0.0);
    Bc(2) = 1.0;

    // Output matrix
    C.fill(0.0);
    C.diagonal().fill(-Ac(2, 0));

    // Initialize the discrete-time state
    x.fill(0.0);

    // Discrete-time system and input matrices
    A = I + Ac * T + 0.5 * Ac * Ac * T * T + 1.0 / 6.0 * Ac * Ac * Ac * T * T * T + 1.0 / 24.0 * Ac * Ac * Ac * Ac * T * T * T * T;
    B = Ac.inverse() * (A - I) * Bc;
}

// Algorithm of Third-Order Command Prefilter
void CommandPrefilter::update(const double& input_sig, double& pos_f, double& vel_f, double& acc_f)
{
    // Output equation
    y = C * x;

    // State equation
    x = A * x + B * input_sig;

    // Copy data
    pos_f = y(0);
    vel_f = y(1);
    acc_f = y(2);
}
