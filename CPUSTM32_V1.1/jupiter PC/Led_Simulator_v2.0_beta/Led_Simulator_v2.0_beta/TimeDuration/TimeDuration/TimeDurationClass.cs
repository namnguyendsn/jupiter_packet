using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Led_Simulator_v2._0_beta
{
    public class TimeDuration
    {
        public TimeDuration()
        {
            startTime = DateTime.Now.ToString("HH:mm");
            endTime = DateTime.Now.ToString("HH:mm");
        }
        private string startTime;
        private string endTime;
        private TimeSpan duration;
        public string StartTime
        {
            get { return startTime; }
            set
            {
                if (startTime != value)
                { 
                    startTime = value;
                    if (endTime!=null)
                    {
                        duration = DateTime.Parse(endTime).Subtract(DateTime.Parse(startTime)); ;
                    }
                }
            }
        }
        public string EndTime
        {
            get { return endTime; }
            set
            {
                if (endTime != value)
                {
                    endTime = value;
                    if (startTime != null)
                    {
                        duration = DateTime.Parse(endTime).Subtract(DateTime.Parse(startTime)); ;
                    }
                }
            }
        }
        public TimeSpan Duration
        {
            get { return duration; }
        }
    }
}
