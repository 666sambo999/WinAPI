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
        PrivateFontCollection pfc;
        //string fontDirectory;
        private Font oldFont;
        private Font newFont;
        private string fontDirectory;

        public string FontDirectory
        {
            get { return fontDirectory; }
            set { fontDirectory = value; }
        }

        public Font NewFont
        {
            get { return newFont; }
            set { newFont = value; }
        }

        public Font OldFont
        {
            get { return oldFont; }
            set { oldFont = value; }
        }


        public Form_ChooseFont(Font font, string fontDirectory)
        {
            InitializeComponent();
            SetFontDirectory();
            //pfc = new PrivateFontCollection();
            OldFont = NewFont = font;
            label_Example.Font = OldFont;
            FontDirectory = fontDirectory;
            LoadFont();
        }

        void SetFontDirectory()
        {
            String currentDirectory = System.IO.Directory.GetCurrentDirectory();
            if (currentDirectory == FontDirectory) return;
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
            newCurrentDirectory += "Font";
            FontDirectory = newCurrentDirectory;
            //MessageBox.Show(this, $"{currentDirectory}\n:{newCurrentDirectory}", "Current Directory", MessageBoxButtons.OK);
            //Directory.SetCurrentDirectory(FontDirectory);
            //string [] fonts = Directory.GetFiles(newCurrentDirectory, "*.ttf");
            //for(int i =0; i<fonts.Length; i++)
            //{
            //    string[] item = fonts[i].Split('\\');
            //    fonts[i] = item[item.Length - 1];
            //}
            //this.cb_Font.Items.AddRange(fonts);
            LoadFont();
        }
        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
        public void LoadFont()
        {
            Directory.SetCurrentDirectory(FontDirectory);
            string[] fonts = Directory.GetFiles(FontDirectory, "*.ttf");
            for (int i = 0; i < fonts.Length; i++)
            {
                string[] item = fonts[i].Split('\\');
                fonts[i] = item[item.Length - 1];
            }
            this.cb_Font.Items.AddRange(fonts);
        }
        private void cb_Font_SelectionChangeCommitted(object sender, EventArgs e)
        {
            //SetFontDirectory();
            //string selectedFont = cb_Font.SelectedItem.ToString();
            PrivateFontCollection pfc = new PrivateFontCollection();
            //pfc.AddFontFile(selectedFont);
            //Font font = new Font(pfc.Families[0], label_Example.Font.Size);
            //pfc.Families.Clear();
            pfc.AddFontFile(cb_Font.SelectedItem.ToString());
            this.NewFont = new Font(pfc.Families[0], label_Example.Font.Size);
            //label_Example.Font = font;
            //label_Example.Font = new Font(pfc.Families[0], label_Example.Font.Size);
            label_Example.Font = this.NewFont;
        }

        private void btn_Ok_Click(object sender, EventArgs e)
        {
            OldFont = NewFont;
            this.Close();
        }
    }
}
