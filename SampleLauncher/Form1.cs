using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace SampleLauncher
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_MouseMove(object sender, MouseEventArgs e)
        {
            if (lockP.HasValue)
            {
                int varX = e.X - lockP.Value.X,
                    varY = e.Y - lockP.Value.Y;
                this.Location = new Point(this.Location.X + varX, this.Location.Y + varY);
            }
        }
        Point? lockP;
        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            int x = e.X,
                y = e.Y;
            if (e.X < 13 || e.X > Width - 13 || e.Y < 19 || e.Y > Height - 19)
            {
                lockP = e.Location;
            }
            else
                lockP = null;
        }

        private void Form1_MouseUp(object sender, MouseEventArgs e)
        {
            lockP = null;
        }

        private void pictureBox2_MouseEnter(object sender, EventArgs e)
        {
            pictureBox2.Image = Properties.Resources.submitover;
        }

        private void pictureBox2_MouseLeave(object sender, EventArgs e)
        {
            pictureBox2.Image = Properties.Resources.submit;
        }

        private void pictureBox2_MouseDown(object sender, MouseEventArgs e)
        {
            pictureBox2.Image = Properties.Resources.submitclick;
        }

        private void pictureBox2_MouseUp(object sender, MouseEventArgs e)
        {
            pictureBox2.Image = Properties.Resources.submitover;
            // Launch

            //Exit
            Application.Exit();
        }
    }
}
