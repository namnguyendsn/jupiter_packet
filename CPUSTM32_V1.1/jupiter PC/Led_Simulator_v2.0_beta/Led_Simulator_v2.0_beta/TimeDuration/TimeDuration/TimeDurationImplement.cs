using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections;

namespace Led_Simulator_v2._0_beta
{
    public partial class TimeDurationImplement : Form
    {
        public TimeDurationImplement()
        {
            InitializeComponent();
            timeDurationList = new ArrayList();
        }
        ArrayList timeDurationList;
        private void button1_Click(object sender, EventArgs e)
        {
            TimeDuration newDuration = new TimeDuration();
            timeDurationList.Add(newDuration);
            TimeDurationReporter reportTime = new TimeDurationReporter("reportTime");
            reportTime.Location = new System.Drawing.Point(5, 15+(timeDurationList.Count-1)*30);
            reportTime.Size = new System.Drawing.Size(pnTimeReport.Width - 10, 30);
            pnTimeReport.Controls.Add(reportTime);
            //reportTime.Subscribe(newDuration);
            TimeDurationClock clockTime = new TimeDurationClock("clockTime");
            clockTime.Location = new System.Drawing.Point(0, 0);
            clockTime.Size = pnTimeClock.Size;
            pnTimeClock.Controls.Add(clockTime);
        }

        private void pnTimeReport_MouseClick(object sender, MouseEventArgs e)
        {
            //MessageBox.Show("xxx");
        }

        private void pnTimeClock_Paint(object sender, PaintEventArgs e)
        {
            
        }


    }
}
