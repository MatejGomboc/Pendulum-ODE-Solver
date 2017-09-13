#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_trig.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

#include "pendulum.h"


bool Pendulum::calculate_step(double& t, double& phi, double& omega, const double delta_t,
                              const double damping, const double frequency)
{
    double params[2] = { damping, frequency };
    double y[2] = { phi, omega };

    gsl_odeiv2_system system = { func, jac, 2, &params };
    gsl_odeiv2_driver* driver = gsl_odeiv2_driver_alloc_y_new(&system, gsl_odeiv2_step_rkf45, 1e-15, 1e-15, 0.0);

    int status = gsl_odeiv2_driver_apply(driver, &t, delta_t, y);

    if (status != GSL_SUCCESS)
    {
        gsl_odeiv2_driver_free(driver);
        return false;
    }
    else
    {
        phi = y[0];
        omega = y[1];
        return true;
    }
}

int Pendulum::func(double t, const double y[], double f[], void *params)
{
    (void)(t); /* avoid unused parameter warning */

    double damping = ((double*)params)[0];
    double frequency = ((double*)params)[1];

    f[0] = y[1];
    f[1] = - frequency * frequency * gsl_sf_sin(y[0]) - 2 * damping * y[1];

    return GSL_SUCCESS;
}

int Pendulum::jac(double t, const double y[], double *dfdy, double dfdt[], void *params)
{
    (void)(t); /* avoid unused parameter warning */

    double damping = ((double*)params)[0];
    double frequency = ((double*)params)[1];

    gsl_matrix_view dfdy_mat = gsl_matrix_view_array(dfdy, 2, 2);
    gsl_matrix* m = &dfdy_mat.matrix;
    gsl_matrix_set(m, 0, 0, 0.0);
    gsl_matrix_set(m, 0, 1, 1.0);
    gsl_matrix_set(m, 1, 0, -frequency * frequency * gsl_sf_cos(y[0]));
    gsl_matrix_set(m, 1, 1, -2 * damping);

    dfdt[0] = 0.0;
    dfdt[1] = 0.0;

    return GSL_SUCCESS;
}
