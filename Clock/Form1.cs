using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Clock
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            this.Location = new System.Drawing.Point
            (
                System.Windows.Forms.Screen.PrimaryScreen.Bounds.Right - this.Width - 50,
                System.Windows.Forms.Screen.PrimaryScreen.Bounds.Top + 250
            );
            
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            label1.Text = DateTime.Now.ToString("HH:mm:ss tt\n");
            //label1.Text = DateTime.Now.ToString("HH:mm:ss tt"); // AM PM
            if(cbShowDate.Checked)
            {
                label1.Text += DateTime.Now.ToString("dd:MM:yyyy");
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void cbShowDate_CheckedChanged(object sender, EventArgs e)
        {
            label1.Text = DateTime.Now.ToString("dd:MM:yyyy");
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void btnHideControl_Click(object sender, EventArgs e)
        {
            this.FormBorderStyle = FormBorderStyle.None;
            //this.BackgroundImage = BackgroundImage.Dispose();
            this.ShowInTaskbar = false;
            cbShowDate.Visible = false;
            btnHideControl.Visible = false;
            btnDateCalculator.Visible = false;
            btnClose.Visible = false;
        }

        private void label1_MouseHover(object sender, EventArgs e)
        {
            this.FormBorderStyle = FormBorderStyle.FixedDialog;
            this.ShowInTaskbar = true;
            cbShowDate.Visible = true;
            btnHideControl.Visible = true;
            btnDateCalculator.Visible = true;
            btnClose.Visible = true;
        }
    }
}
