/**
 * @file command_prefilter.h
 * @author your name (you@domain.com)
 * @brief Algorithm of the command prefilter (third-order)
 * @version 0.3
 * @date 2023-05-12
 *       2021-02-27 結構變數版本
 *       2021-10-06 class 版本
 *       2023-05-12 更新 naming style
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#if ENV_PC
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <iostream>
#else
#include <ArduinoEigen.h>
#endif 

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

class CommandPrefilter
{
public:
    void init(double cutoff_freq, double sample_interval);
    void update(const double& input_sig, double& pos_f, double& vel_f, double& acc_f);

private:
    double T; // Sample interval
    double fc; // Cut-off frequency
    double tau; // Time constant
    Eigen::Matrix3d A;
    Eigen::Vector3d B;
    Eigen::Matrix<double, 3, 3> C;
    Eigen::Vector3d x;
    Eigen::Vector3d y;
};