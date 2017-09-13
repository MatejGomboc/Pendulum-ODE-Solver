#pragma once
#ifndef ode_solver_dll_h
#define ode_solver_dll_h

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ODE_SOLVER_DLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ODE_SOLVER_DLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef ODE_SOLVER_DLL_EXPORTS
#define ODE_SOLVER_DLL_API __declspec(dllexport)
#else
#define ODE_SOLVER_DLL_API __declspec(dllimport)
#endif

extern "C" ODE_SOLVER_DLL_API bool ode_solver_calculate_step(double& t, double& phi, double& omega, const double delta_t,
	const double damping, const double frequency);

#endif
