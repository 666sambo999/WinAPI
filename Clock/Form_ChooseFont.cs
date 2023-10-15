using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Text;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace Clock
{
    public partial class Form_ChooseFont : Form
    {
        PrivateFontCollection pfc = new PrivateFontCollection();
        //string fontDirectory;
        public Form_ChooseFont()
        {
            InitializeComponent();
            SetFontDirectory();
            pfc = new PrivateFontCollection();  
        }

        void SetFontDirectory()
        {
            String currentDirectory = System.IO.Directory.GetCurrentDirectory();
            //MessageBox.Show(this, currentDirectory, "Current directory", MessageBoxButtons.OK);
            string[] currentDirectoryItems = currentDirectory.Split('\\');
            Array.Resize(ref currentDirectoryItems, currentDirectoryItems.Length - 2);
            string newCurrentDirectory = "";
            //this.fontDirectory = newCurrentDirectory;
            Directory.SetCurrentDirectory(newCurrentDirectory);
            foreach (string i in currentDirectoryItems)
            {
                newCurrentDirectory += i;
                newCurrentDirectory += "\\";

            }
            newCurrentDirectory += "Fonts";
            //MessageBox.Show(this, $"{currentDirectory}\n:{newCurrentDirectory}", "Current Directory", MessageBoxButtons.OK);
            string [] fonts = Directory.GetFiles(newCurrentDirectory, "*.ttf");
            for(int i =0; i<fonts.Length; i++)
            {
                string[] item = fonts[i].Split('\\');
                fonts[i] = item[item.Length - 1];
            }
            this.cb_Font.Items.AddRange(fonts);
        }
        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void cb_Font_SelectionChangeCommitted(object sender, EventArgs e)
        {
            //SetFontDirectory();
            //string selectedFont = cb_Font.SelectedItem.ToString();
            //PrivateFontCollection pfc = new PrivateFontCollection();
            //pfc.AddFontFile(selectedFont);
            //Font font = new Font(pfc.Families[0], label_Example.Font.Size);
            //label_Example.Font = font;
            pfc.AddFontFile(cb_Font.SelectedItem.ToString());
            label_Example.Font = new Font(pfc.Families[0], label_Example.Font.Size);
        }

        private void btn_Ok_Click(object sender, EventArgs e)
        {
            
        }
    }
}
