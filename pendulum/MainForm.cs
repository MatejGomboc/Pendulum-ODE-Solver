using System;
using System.Drawing;
using System.Windows.Forms;
using System.Threading;

namespace pendulum
{
    public partial class MainForm : Form
    {
        private Thread workerThread = null;
        private delegate void ThreadSafeDelegate(double value);

        private const double stepSize = 0.05;
        private const double damping = 0.2;
        private const double frequency = 7.0;

        public MainForm()
        {
            InitializeComponent();
        }

        private void calculate()
        {
            double time = 0.0;
            double phi = 0.0;
            double omega = 14.8;

            while (true)
            {
                try
                {
                    if(!PendulumODESolver.ode_solver_calculate_step(ref time, ref phi, ref omega, time + stepSize, damping, frequency))
                        throw new Exception("ODE solver failure.");

                    addPlotPoint(phi);
                    render(phi);

                    Thread.Sleep(100); // To not saturate a core
                }
                catch(ThreadAbortException)
                {
                    break;
                }
                catch(Exception ex)
                {
                    MessageBox.Show(ex.Message, "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    break;
                }
            }
        }

        private void addPlotPoint(double yValue)
        {
            if (this.chartPlot.InvokeRequired)
            {
                ThreadSafeDelegate d = new ThreadSafeDelegate(addPlotPoint);
                this.Invoke(d, new object[] { yValue });
            }
            else
            {
                this.chartPlot.Series[0].Points.AddY(yValue);
            }
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            if (workerThread == null)
            {
                workerThread = new Thread(new ThreadStart(calculate));
                workerThread.Start();
                while (!workerThread.IsAlive) ;
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (workerThread != null)
            {
                workerThread.Abort();
                workerThread.Join();
                workerThread = null;
            }
        }

        private void render(double value)
        {
            float pointSizeX = 0.05f * (float)pictureBox1.ClientRectangle.Width;
            float pointSizeY = 0.05f * (float)pictureBox1.ClientRectangle.Height;

            float pointLocationX = (1.0f + (float)Math.Cos(value - Math.PI / 2)) * (float)pictureBox1.ClientRectangle.Width / 2.0f;
            float pointLocationY = (1.0f - (float)Math.Sin(value - Math.PI / 2)) * (float)pictureBox1.ClientRectangle.Height / 2.0f;

            if (this.pictureBox1.InvokeRequired)
            {
                ThreadSafeDelegate d = new ThreadSafeDelegate(render);
                this.Invoke(d, new object[] { value });
            }
            else
            {
                Image i = new Bitmap(pictureBox1.ClientRectangle.Width, pictureBox1.ClientRectangle.Height);
                Graphics g = Graphics.FromImage(i);

                g.FillRectangle(Brushes.White, pictureBox1.ClientRectangle);

                g.DrawLine(Pens.Black, (float)pictureBox1.ClientRectangle.Width / 2.0f, (float)pictureBox1.ClientRectangle.Height / 2.0f, pointLocationX, pointLocationY);

                g.FillEllipse(Brushes.Black, pointLocationX - pointSizeX / 2.0f, pointLocationY - pointSizeY / 2.0f, pointSizeX, pointSizeY);

                pictureBox1.Image = i;

                g.Dispose();
            }
        }
    }
}
