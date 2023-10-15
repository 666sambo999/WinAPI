using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Text;
using System.Reflection.Emit;

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
                System.Windows.Forms.Screen.PrimaryScreen.Bounds.Top + 150
            );
            ControlsVisible(false);
            String currentDirectory = System.IO.Directory.GetCurrentDirectory();
            //MessageBox.Show(this, currentDirectory, "Current directory", MessageBoxButtons.OK);
            CreateCustomLabelFont();
        }
        void CreateCustomLabelFont()
        {
            //C:\Users\андрей\source\repos\WinAPI\Clock\Font
            PrivateFontCollection pfc = new PrivateFontCollection(); // создаем объект 
            pfc.AddFontFile("..\\..\\Font\\RADIOLANDSLIM.ttf");
            Font font = new Font(pfc.Families[0], label1.Font.Size);
            pfc.Dispose();
            label1.Font = font;

            //label1.Font =
        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            label1.Text = DateTime.Now.ToString("HH:mm:ss tt\t");
            //label1.Text = DateTime.Now.ToString("HH:mm:ss tt"); // AM PM
            if (cbShowDate.Checked)
            {
                label1.Text += DateTime.Now.ToString("dd:MM:yyyy");
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        //private void cbShowDate_CheckedChanged(object sender, EventArgs e)
        //{
        //    //label1.Text = DateTime.Now.ToString("dd:MM:yy");
        //}

        private void btnClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        private void ControlsVisible(bool visible)
        {
            if (visible) this.FormBorderStyle = FormBorderStyle.None;
            else this.FormBorderStyle = FormBorderStyle.FixedDialog;
            this.ShowInTaskbar = visible;
            cbShowDate.Visible = visible;
            btnHideControl.Visible = visible;
            btnDateCalculator.Visible = visible;
            btnClose.Visible = visible;
        }
        private void btnHideControl_Click(object sender, EventArgs e)
        {
            //this.FormBorderStyle = FormBorderStyle.None;
            ////this.BackgroundImage = BackgroundImage.Dispose();
            //this.ShowInTaskbar = false;
            //cbShowDate.Visible = false;
            //btnHideControl.Visible = false;
            //btnDateCalculator.Visible = false;
            //btnClose.Visible = false;
            ControlsVisible(false);
        }

        private void label1_MouseHover(object sender, EventArgs e)
        {
            //this.FormBorderStyle = FormBorderStyle.FixedDialog;
            //this.ShowInTaskbar = true;
            //cbShowDate.Visible = true;
            //btnHideControl.Visible = true;
            //btnDateCalculator.Visible = true;
            //btnClose.Visible = true;
            ControlsVisible(true);
        }

        private void cmExit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void cmHideControl_Click(object sender, EventArgs e)
        {
            btnHideControl_Click(sender, e);
        }

        private void cmShowControl_Click(object sender, EventArgs e)
        {
            label1_MouseHover(sender, e);
        }

        private void cmShowDate_Click(object sender, EventArgs e)
        {
            cbShowDate.Checked = !cbShowDate.Checked;
            cmShowDate.Text = cbShowDate.Checked ? "Hide date" : "Show date";
        }

        private void cmOverAllWindows_Click(object sender, EventArgs e)
        {
            this.TopMost = !this.TopMost;
            //cmOverAllWindows.Checked = !cmOverAllWindows.Checked;
        }
    }
}
