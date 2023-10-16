namespace Clock
{
    partial class Form1
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.label1 = new System.Windows.Forms.Label();
            this.cms_Lbl1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.cms_Lbl1_ChItem = new System.Windows.Forms.ToolStripMenuItem();
            this.cms_Lbl1_ChFontColor = new System.Windows.Forms.ToolStripMenuItem();
            this.cms_Lbl1BackColor = new System.Windows.Forms.ToolStripMenuItem();
            this.cms_Lbl1_ShowControl = new System.Windows.Forms.ToolStripMenuItem();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.cbShowDate = new System.Windows.Forms.CheckBox();
            this.btnHideControl = new System.Windows.Forms.Button();
            this.btnClose = new System.Windows.Forms.Button();
            this.btnDateCalculator = new System.Windows.Forms.Button();
            this.notifyIcon = new System.Windows.Forms.NotifyIcon(this.components);
            this.contextMenuStrip = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.cmOverAllWindows = new System.Windows.Forms.ToolStripMenuItem();
            this.cmShowDate = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.cmShowControl = new System.Windows.Forms.ToolStripMenuItem();
            this.cmHideControl = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.cmExit = new System.Windows.Forms.ToolStripMenuItem();
            this.cms_Lbl1.SuspendLayout();
            this.contextMenuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.SystemColors.Control;
            this.label1.ContextMenuStrip = this.cms_Lbl1;
            this.label1.Font = new System.Drawing.Font("Vladimir Script", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Image = ((System.Drawing.Image)(resources.GetObject("label1.Image")));
            this.label1.Location = new System.Drawing.Point(41, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(87, 50);
            this.label1.TabIndex = 0;
            this.label1.Text = "label1";
            this.label1.UseCompatibleTextRendering = true;
            this.label1.MouseHover += new System.EventHandler(this.label1_MouseHover);
            // 
            // cms_Lbl1
            // 
            this.cms_Lbl1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.cms_Lbl1_ChItem,
            this.cms_Lbl1_ChFontColor,
            this.cms_Lbl1BackColor,
            this.cms_Lbl1_ShowControl});
            this.cms_Lbl1.Name = "cms_Lbl1";
            this.cms_Lbl1.Size = new System.Drawing.Size(169, 92);
            this.cms_Lbl1.Text = "Menu color";
            // 
            // cms_Lbl1_ChItem
            // 
            this.cms_Lbl1_ChItem.Name = "cms_Lbl1_ChItem";
            this.cms_Lbl1_ChItem.Size = new System.Drawing.Size(168, 22);
            this.cms_Lbl1_ChItem.Text = "Choose Font";
            this.cms_Lbl1_ChItem.Click += new System.EventHandler(this.cms_Lbl1_ChItem_Click);
            // 
            // cms_Lbl1_ChFontColor
            // 
            this.cms_Lbl1_ChFontColor.Name = "cms_Lbl1_ChFontColor";
            this.cms_Lbl1_ChFontColor.Size = new System.Drawing.Size(168, 22);
            this.cms_Lbl1_ChFontColor.Text = "Font color";
            // 
            // cms_Lbl1BackColor
            // 
            this.cms_Lbl1BackColor.Name = "cms_Lbl1BackColor";
            this.cms_Lbl1BackColor.Size = new System.Drawing.Size(168, 22);
            this.cms_Lbl1BackColor.Text = "Background color";
            // 
            // cms_Lbl1_ShowControl
            // 
            this.cms_Lbl1_ShowControl.Checked = true;
            this.cms_Lbl1_ShowControl.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cms_Lbl1_ShowControl.Name = "cms_Lbl1_ShowControl";
            this.cms_Lbl1_ShowControl.Size = new System.Drawing.Size(168, 22);
            this.cms_Lbl1_ShowControl.Text = "Show control";
            this.cms_Lbl1_ShowControl.Click += new System.EventHandler(this.cms_Lbl1_ShowControl_Click);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // cbShowDate
            // 
            this.cbShowDate.AutoSize = true;
            this.cbShowDate.Font = new System.Drawing.Font("MS UI Gothic", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cbShowDate.Location = new System.Drawing.Point(41, 75);
            this.cbShowDate.Name = "cbShowDate";
            this.cbShowDate.Size = new System.Drawing.Size(150, 31);
            this.cbShowDate.TabIndex = 1;
            this.cbShowDate.Text = "Show date";
            this.cbShowDate.UseVisualStyleBackColor = true;
            // 
            // btnHideControl
            // 
            this.btnHideControl.Font = new System.Drawing.Font("Snap ITC", 18F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnHideControl.Location = new System.Drawing.Point(41, 164);
            this.btnHideControl.Name = "btnHideControl";
            this.btnHideControl.Size = new System.Drawing.Size(292, 46);
            this.btnHideControl.TabIndex = 2;
            this.btnHideControl.Text = "Hide controls";
            this.btnHideControl.UseVisualStyleBackColor = true;
            this.btnHideControl.Click += new System.EventHandler(this.btnHideControl_Click);
            // 
            // btnClose
            // 
            this.btnClose.Font = new System.Drawing.Font("Snap ITC", 18F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnClose.Location = new System.Drawing.Point(41, 269);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(292, 46);
            this.btnClose.TabIndex = 3;
            this.btnClose.Text = "Close";
            this.btnClose.UseVisualStyleBackColor = true;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // btnDateCalculator
            // 
            this.btnDateCalculator.Font = new System.Drawing.Font("Snap ITC", 18F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnDateCalculator.Location = new System.Drawing.Point(41, 217);
            this.btnDateCalculator.Name = "btnDateCalculator";
            this.btnDateCalculator.Size = new System.Drawing.Size(292, 46);
            this.btnDateCalculator.TabIndex = 4;
            this.btnDateCalculator.Text = "Date calculator";
            this.btnDateCalculator.UseVisualStyleBackColor = true;
            // 
            // notifyIcon
            // 
            this.notifyIcon.ContextMenuStrip = this.contextMenuStrip;
            this.notifyIcon.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIcon.Icon")));
            this.notifyIcon.Text = "My Clock";
            this.notifyIcon.Visible = true;
            // 
            // contextMenuStrip
            // 
            this.contextMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.cmOverAllWindows,
            this.cmShowDate,
            this.toolStripSeparator2,
            this.cmShowControl,
            this.cmHideControl,
            this.toolStripSeparator1,
            this.cmExit});
            this.contextMenuStrip.Name = "contextMenuStrip1";
            this.contextMenuStrip.Size = new System.Drawing.Size(167, 126);
            // 
            // cmOverAllWindows
            // 
            this.cmOverAllWindows.CheckOnClick = true;
            this.cmOverAllWindows.Name = "cmOverAllWindows";
            this.cmOverAllWindows.Size = new System.Drawing.Size(166, 22);
            this.cmOverAllWindows.Text = "Over all Windows";
            this.cmOverAllWindows.Click += new System.EventHandler(this.cmOverAllWindows_Click);
            // 
            // cmShowDate
            // 
            this.cmShowDate.Name = "cmShowDate";
            this.cmShowDate.Size = new System.Drawing.Size(166, 22);
            this.cmShowDate.Text = "Show Date";
            this.cmShowDate.Click += new System.EventHandler(this.cmShowDate_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(163, 6);
            // 
            // cmShowControl
            // 
            this.cmShowControl.Name = "cmShowControl";
            this.cmShowControl.Size = new System.Drawing.Size(166, 22);
            this.cmShowControl.Text = "Show control";
            this.cmShowControl.Click += new System.EventHandler(this.cmShowControl_Click);
            // 
            // cmHideControl
            // 
            this.cmHideControl.Name = "cmHideControl";
            this.cmHideControl.Size = new System.Drawing.Size(166, 22);
            this.cmHideControl.Text = "Hide control";
            this.cmHideControl.Click += new System.EventHandler(this.cmHideControl_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(163, 6);
            // 
            // cmExit
            // 
            this.cmExit.Name = "cmExit";
            this.cmExit.Size = new System.Drawing.Size(166, 22);
            this.cmExit.Text = "Exit";
            this.cmExit.Click += new System.EventHandler(this.cmExit_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.ClientSize = new System.Drawing.Size(419, 322);
            this.Controls.Add(this.btnDateCalculator);
            this.Controls.Add(this.btnClose);
            this.Controls.Add(this.btnHideControl);
            this.Controls.Add(this.cbShowDate);
            this.Controls.Add(this.label1);
            this.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.ForeColor = System.Drawing.SystemColors.ControlDarkDark;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "MyClock";
            this.TransparencyKey = System.Drawing.SystemColors.ButtonFace;
            this.Load += new System.EventHandler(this.Form1_Load);
            this.cms_Lbl1.ResumeLayout(false);
            this.contextMenuStrip.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.CheckBox cbShowDate;
        private System.Windows.Forms.Button btnHideControl;
        private System.Windows.Forms.Button btnClose;
        private System.Windows.Forms.Button btnDateCalculator;
        private System.Windows.Forms.NotifyIcon notifyIcon;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem cmShowControl;
        private System.Windows.Forms.ToolStripMenuItem cmHideControl;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem cmExit;
        private System.Windows.Forms.ToolStripMenuItem cmShowDate;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem cmOverAllWindows;
        private System.Windows.Forms.ContextMenuStrip cms_Lbl1;
        private System.Windows.Forms.ToolStripMenuItem cms_Lbl1_ChItem;
        private System.Windows.Forms.ToolStripMenuItem cms_Lbl1_ChFontColor;
        private System.Windows.Forms.ToolStripMenuItem cms_Lbl1BackColor;
        private System.Windows.Forms.ToolStripMenuItem cms_Lbl1_ShowControl;
    }
}

