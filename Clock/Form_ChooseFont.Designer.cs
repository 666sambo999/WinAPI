namespace Clock
{
    partial class Form_ChooseFont
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.cb_Font = new System.Windows.Forms.ComboBox();
            this.btn_Ok = new System.Windows.Forms.Button();
            this.btn_cancel = new System.Windows.Forms.Button();
            this.label_Example = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // cb_Font
            // 
            this.cb_Font.FormattingEnabled = true;
            this.cb_Font.Location = new System.Drawing.Point(31, 35);
            this.cb_Font.Name = "cb_Font";
            this.cb_Font.Size = new System.Drawing.Size(361, 21);
            this.cb_Font.TabIndex = 0;
            this.cb_Font.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            this.cb_Font.SelectionChangeCommitted += new System.EventHandler(this.cb_Font_SelectionChangeCommitted);
            // 
            // btn_Ok
            // 
            this.btn_Ok.Font = new System.Drawing.Font("Microsoft Sans Serif", 21.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btn_Ok.Location = new System.Drawing.Point(46, 140);
            this.btn_Ok.Name = "btn_Ok";
            this.btn_Ok.Size = new System.Drawing.Size(131, 44);
            this.btn_Ok.TabIndex = 1;
            this.btn_Ok.Text = "Ok";
            this.btn_Ok.UseVisualStyleBackColor = true;
            this.btn_Ok.Click += new System.EventHandler(this.btn_Ok_Click);
            // 
            // btn_cancel
            // 
            this.btn_cancel.Font = new System.Drawing.Font("Microsoft Sans Serif", 21.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btn_cancel.Location = new System.Drawing.Point(267, 140);
            this.btn_cancel.Name = "btn_cancel";
            this.btn_cancel.Size = new System.Drawing.Size(125, 44);
            this.btn_cancel.TabIndex = 2;
            this.btn_cancel.Text = "Cancel";
            this.btn_cancel.UseVisualStyleBackColor = true;
            // 
            // label_Example
            // 
            this.label_Example.AutoSize = true;
            this.label_Example.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label_Example.Location = new System.Drawing.Point(113, 77);
            this.label_Example.Name = "label_Example";
            this.label_Example.Size = new System.Drawing.Size(237, 37);
            this.label_Example.TabIndex = 3;
            this.label_Example.Text = "Example: 12:34";
            // 
            // Form_ChooseFont
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(432, 197);
            this.Controls.Add(this.label_Example);
            this.Controls.Add(this.btn_cancel);
            this.Controls.Add(this.btn_Ok);
            this.Controls.Add(this.cb_Font);
            this.Name = "Form_ChooseFont";
            this.Text = "Form_ChooseFont";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox cb_Font;
        private System.Windows.Forms.Button btn_Ok;
        private System.Windows.Forms.Button btn_cancel;
        private System.Windows.Forms.Label label_Example;
    }
}