using System.Runtime.InteropServices;

namespace pendulum
{
    class PendulumODESolver
    {
        /// <summary>
        /// Calculate next phi and omega using ODE solver.
        /// </summary>
        [DllImport("ode_solver.dll")]
        public static extern bool ode_solver_calculate_step(ref double t, ref double phi, ref double omega,
            double delta_t, double damping, double frequency);
    }
}
