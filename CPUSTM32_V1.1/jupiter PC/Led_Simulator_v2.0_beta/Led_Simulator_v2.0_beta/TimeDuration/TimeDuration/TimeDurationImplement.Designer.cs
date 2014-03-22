namespace Led_Simulator_v2._0_beta
{
    partial class TimeDurationImplement
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
            this.button1 = new System.Windows.Forms.Button();
            this.pnTimeReport = new System.Windows.Forms.Panel();
            this.pnTimeClock = new System.Windows.Forms.Panel();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(394, 327);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // pnTimeReport
            // 
            this.pnTimeReport.AutoScroll = true;
            this.pnTimeReport.BackColor = System.Drawing.SystemColors.Highlight;
            this.pnTimeReport.Location = new System.Drawing.Point(341, 28);
            this.pnTimeReport.Name = "pnTimeReport";
            this.pnTimeReport.Size = new System.Drawing.Size(246, 293);
            this.pnTimeReport.TabIndex = 1;
            this.pnTimeReport.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pnTimeReport_MouseClick);
            // 
            // pnTimeClock
            // 
            this.pnTimeClock.Location = new System.Drawing.Point(13, 28);
            this.pnTimeClock.Name = "pnTimeClock";
            this.pnTimeClock.Size = new System.Drawing.Size(300, 300);
            this.pnTimeClock.TabIndex = 2;
            this.pnTimeClock.Paint += new System.Windows.Forms.PaintEventHandler(this.pnTimeClock_Paint);
            // 
            // TimeDurationImplement
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(599, 349);
            this.Controls.Add(this.pnTimeClock);
            this.Controls.Add(this.pnTimeReport);
            this.Controls.Add(this.button1);
            this.Name = "TimeDurationImplement";
            this.Text = "TimeDurationImplement";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Panel pnTimeReport;
        private System.Windows.Forms.Panel pnTimeClock;
    }
}