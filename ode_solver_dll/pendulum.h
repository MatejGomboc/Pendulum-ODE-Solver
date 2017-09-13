#pragma once
#ifndef PENDULUM_H
#define PENDULUM_H

#include <gsl/gsl_math.h>


class Pendulum
{
private:
    static int func (double t, const double y[], double f[], void *params);
    static int jac(double t, const double y[], double *dfdy, double dfdt[], void *params);
    Pendulum() = delete;
public:
    static bool calculate_step(double& t, double& phi, double& omega, const double delta_t = 0.0,
                               const double damping = 0.0, const double frequency = 2.0 * M_PI / 1.0);
};

#endif // PENDULUM_H
