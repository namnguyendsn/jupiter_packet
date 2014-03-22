using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace Led_Simulator_v2._0_beta
{
    using System;

    public class TimeDurationReporter : Panel,IObserver<TimeDuration>
    {
        event EventHandler DataChange; 
        private IDisposable unsubscriber;
        private string instName;
        private DateTimePicker startTime;
        private DateTimePicker endTime;
        private Label lbStartTime;
        private Label lbEndTime;

        public TimeDurationReporter(string name)
        {
            this.instName = name;
            startTime = new DateTimePicker();
            
            
            //startTime.Size = new System.Drawing.Size(20, 10);
            endTime = new DateTimePicker();
            lbStartTime = new Label();
            
            lbEndTime = new Label();
            lbStartTime.AutoSize = true;
            lbEndTime.AutoSize = true;
            lbStartTime.Text = "Start Time";
            lbEndTime.Text = "End Time";
            startTime.Format = DateTimePickerFormat.Custom;
            startTime.CustomFormat = "HH:mm";
            startTime.ShowUpDown = true;
            startTime.ShowCheckBox = false;
            endTime.Format = DateTimePickerFormat.Custom;
            endTime.CustomFormat = "HH:mm";
            endTime.ShowUpDown = true;
            endTime.ShowCheckBox = false;
            startTime.ValueChanged+=new EventHandler(ValueChanged);
            //Add child controls
            this.Controls.Add(startTime);
            this.Controls.Add(endTime);
            this.Controls.Add(lbStartTime);
            this.Controls.Add(lbEndTime);
            //Invalidate();
        }

        public string Name
        { get { return this.instName; } }
        #region IObserver Method
        public virtual void Subscribe(IObservable<TimeDuration> provider)
        {
            if (provider != null)
                unsubscriber = provider.Subscribe(this);
        }

        public virtual void OnCompleted()
        {
            Console.WriteLine("The TimeDuration Tracker has completed transmitting data to {0}.", this.Name);
            this.Unsubscribe();
        }

        public virtual void OnError(Exception e)
        {
            Console.WriteLine("{0}: The TimeDuration cannot be determined.", this.Name);
        }

        public virtual void OnNext(TimeDuration value)
        {
            //Console.WriteLine("{2}: The current TimeDuration is {0}, {1}", value.Latitude, value.Longitude, this.Name);
        }

        public virtual void Unsubscribe()
        {
            unsubscriber.Dispose();
        }
        #endregion
        #region Control View
        protected override void OnPaint(PaintEventArgs e)
        {
            //base.OnPaint(e);
        }

        protected override void OnSizeChanged(EventArgs e)
        {
            base.OnSizeChanged(e);
            ShowDuration();
        }

        protected override void OnGotFocus(EventArgs e)
        {
            base.OnGotFocus(e);
            Graphics gfx = this.CreateGraphics();
            Pen blackPen = new Pen(Color.Black, 2);
            Rectangle boder = new Rectangle(this.Location, this.Size);
            gfx.DrawRectangle(blackPen, ClientRectangle);
            //this.BackColor = Color.Yellow;
        }

        protected override void OnLostFocus(EventArgs e)
        {
            base.OnLostFocus(e);
            Graphics gfx = this.CreateGraphics();
            Pen blackPen = new Pen(this.BackColor, 2);
            Rectangle boder = new Rectangle(this.Location, this.Size);
            gfx.DrawRectangle(blackPen, ClientRectangle);
        }

        void ShowDuration()
        {
            lbStartTime.Size = new System.Drawing.Size(lbStartTime.Width, this.Height-10);
            lbStartTime.Location = new System.Drawing.Point(5, (this.Height - lbStartTime.Height) / 2);
            //startTime

            startTime.Size = new System.Drawing.Size(50, this.Height-10);
            startTime.Location = new System.Drawing.Point(lbStartTime.Location.X + lbStartTime.Width + 5, (this.Height - startTime.Height) / 2);
            //lbEndTime


            lbEndTime.Size = new System.Drawing.Size(lbEndTime.Width, this.Height-10);
            lbEndTime.Location = new System.Drawing.Point(5+ this.Width / 2, (this.Height - lbEndTime.Height) / 2);
            //endTime

            endTime.Size = new System.Drawing.Size(50, this.Height-10);
            endTime.Location = new System.Drawing.Point(lbEndTime.Location.X + lbEndTime.Width + 5, (this.Height - endTime.Height) / 2);

        }
        #endregion
        #region Custom event
        void ValueChanged(object sender, EventArgs e)
        {
            if (DataChange != null)
            {
                DataChange(this, e);
            }
        }
        #endregion
    }
}
