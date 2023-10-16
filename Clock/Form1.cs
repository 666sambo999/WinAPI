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
using System.IO;

namespace Clock
{
    public partial class Form1 : Form
    {
        private string[] fonts;
        private string fontDirectory;

        public string FontDirectory

        {
            get { return fontDirectory; }
            set { fontDirectory = value; }
        }

        public string[] Fonts
        { 
            get { return fonts; }
            set { fonts = value; }  
        }
        public Form1()
        {
            InitializeComponent();
            this.Location = new System.Drawing.Point
            (
                System.Windows.Forms.Screen.PrimaryScreen.Bounds.Right - this.Width - 50,
                System.Windows.Forms.Screen.PrimaryScreen.Bounds.Top + 150
            );
            ControlsVisible(false);
            CreateCustomLabelFont();
            SetFontDirectory();
        }
        void SetFontDirectory()
        {
            String currentDirectory = System.IO.Directory.GetCurrentDirectory();
            //MessageBox.Show(this, currentDirectory, "Current directory", MessageBoxButtons.OK);
            string[] currentDirectoryItems = currentDirectory.Split('\\');
            Array.Resize(ref currentDirectoryItems, currentDirectoryItems.Length-1);
            string newCurrentDirectory = "";
            foreach(string i in currentDirectoryItems)
            {
                newCurrentDirectory += i;
                newCurrentDirectory += "\\";

            }
            newCurrentDirectory += "Font";
            //MessageBox.Show(this, $"{currentDirectory}\n:{newCurrentDirectory}", "Current Directory", MessageBoxButtons.OK);
            Fonts = Directory.GetFiles(newCurrentDirectory);
            FontDirectory = newCurrentDirectory;
        }
        void CreateCustomLabelFont()
        {
            //C:\Users\андрей\source\repos\WinAPI\Clock\Font
            PrivateFontCollection pfc = new PrivateFontCollection(); // создаем объект 
            pfc.AddFontFile("..\\..\\Font\\RADIOLANDSLIM.ttf");
            Font font = new Font(pfc.Families[0], label1.Font.Size);
            pfc.Dispose();
            label1.Font = font;

            label1.BackColor = Color.Black;
            label1.ForeColor = Color.DarkRed;
        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            //label1.PreferredWidth = 430;
            //label1.PreferredHeight = 85;
            //label1.Text = DateTime.Now.ToString("HH:mm:ss tt"); // AM PM
           
             label1.Text = DateTime.Now.ToString("HH:mm:ss \t");
                if (cbShowDate.Checked)
                {
                    label1.Text += DateTime.Now.ToString("dd:MM:yyyy");
                }
          
                //MessageBox.Show(this, error.Message);
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void cbShowDate_CheckedChanged(object sender, EventArgs e)
        {
            //label1.Text = DateTime.Now.ToString("dd:MM:yy");
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        private void ControlsVisible(bool visible)
        {
            if (!visible) this.FormBorderStyle = FormBorderStyle.None;
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
            //ControlsVisible(true);
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
            this.TopMost= !this.TopMost;
            //cmOverAllWindows.Checked = !cmOverAllWindows.Checked;
        }

        private void cms_Lbl1_ShowControl_Click(object sender, EventArgs e)
        {
            ControlsVisible(cms_Lbl1_ShowControl.Checked);
        }

        private void cms_Lbl1_ChItem_Click(object sender, EventArgs e)
        {
            Form_ChooseFont fcf = new Form_ChooseFont(label1.Font, FontDirectory);
            fcf.ShowDialog(this);
            label1.Font = fcf.OldFont;
            FontDirectory = fcf.FontDirectory;
            string str = fontDirectory;
        }
    }
}
