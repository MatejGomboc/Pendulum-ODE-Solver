#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// Including SDKDDKVer.h defines the highest available Windows platform.
// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.
#include <SDKDDKVer.h>

#include "ode_solver_dll.h"
#include "pendulum.h"

ODE_SOLVER_DLL_API bool ode_solver_calculate_step(double& t, double& phi, double& omega, const double delta_t,
	const double damping, const double frequency)
{
	return Pendulum::calculate_step(t, phi, omega, delta_t, damping, frequency);
}
