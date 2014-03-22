using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace Led_Simulator_v2._0_beta
{
    using System;

    public class TimeDurationClock : GroupBox,IObserver<TimeDuration>
    {
        private IDisposable unsubscriber;
        //private string instName;
        private int locationX;
        private int locationY;
        private Point refPoint;
        private int radius;
        private int startMinute;
        private int endMinute;
        private int startMinuteOld;
        private int endMinuteOld;
        Button btnStartMinute;
        Button btnEndMinute;
        Boolean draw = false;
        Boolean firstTime = true;
        //private int durationMinute;

        public int StartMinute
        {
            get { return startMinute; }
            set
            {
                if (startMinute != value)
                {
                    startMinute = value;
                    UpdateDuration();
                    //Invalidate();
                }
            }
        }


        public int EndMinute
        {
            get { return endMinute; }
            set
            {
                if (endMinute != value)
                {
                    endMinute = value;
                    Invalidate();
                }
            }
        }

        public TimeDurationClock(string name)
        {
            //Invalidate();
            startMinute = 45*4;
            endMinute = 90*4;
            startMinuteOld = startMinute;
            endMinuteOld = endMinute;
            locationX = this.Location.X + radius;
            locationY = this.Location.Y + radius;
            btnStartMinute = new Button();
            btnStartMinute.Name = "startMinutePoint";
            btnStartMinute.Size = new Size(Constants.clockPoint, Constants.clockPoint);
            btnStartMinute.MouseDown+=new MouseEventHandler(btnStartMinute_MouseDown);
            btnStartMinute.MouseUp+=new MouseEventHandler(btnStartMinute_MouseUp);
            btnStartMinute.MouseMove+=new MouseEventHandler(btnStartMinute_MouseMove);
            btnStartMinute.BackColor = Color.Blue;

            btnEndMinute = new Button();
            btnEndMinute.Name = "endMinutePoint";
            btnEndMinute.Size = new Size(Constants.clockPoint, Constants.clockPoint);
            btnEndMinute.BackColor = Color.Red;

            this.Controls.Add(btnStartMinute);
            this.Controls.Add(btnEndMinute);
            draw = true;
        }
        #region Clock Point event
        Boolean startPointHold = false;
        void btnStartMinute_MouseDown(object sender, MouseEventArgs e)
        {
            startPointHold = true;
        }

        void btnStartMinute_MouseMove(object sender, MouseEventArgs e)
        {
            if (startPointHold)
            { 
            //Calculate new angel
                Point curMousePoint = this.PointToClient(Cursor.Position);
                double newAngel=GetAngleFromPoint(curMousePoint, refPoint);
            //Calculate new start minute
                StartMinute = (int)(newAngel * 4 *180/ Math.PI);
            }
        }

        void btnStartMinute_MouseUp(object sender, MouseEventArgs e)
        {
            startPointHold = false;
        }

        internal double GetAngleFromPoint(Point point, Point centerPoint)
        {
            double dy = (point.Y - centerPoint.Y);
            double dx = (point.X - centerPoint.X);
            double angle = Math.Acos(dx / (Math.Sqrt(dx * dx + dy * dy)));
            if (dy < 0) { angle = 2*Math.PI - angle; }
            return angle;
        }
        #endregion

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
        Rectangle boder;
        protected override void OnPaint(PaintEventArgs pe)
        {
            if (firstTime)
            {
                Graphics gfx = pe.Graphics;
                pe.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;

                Brush solidBrush = new SolidBrush(Color.Blue);

                //if (startMinute > startMinuteOld)
                //{
                    //DrawDuration(gfx, startMinuteOld, startMinute, new SolidBrush(this.BackColor));
                //}
                //else if (startMinute < startMinuteOld)
                //{
                    //DrawDuration(gfx, startMinute, startMinuteOld, solidBrush);
                //}

                    DrawDuration(gfx, startMinute, endMinute, solidBrush);
                    firstTime = false;
                }
        }

        void DrawDuration(Graphics gfx, int startMinute, int endMinute, Brush solidBrush)
        {
            if (endMinute > startMinute)
            {
                gfx.FillPie(solidBrush, boder, startMinute / 4, endMinute / 4 - startMinute / 4);
            }
            else
            {
                gfx.FillPie(solidBrush, boder, startMinute / 4, 360+(endMinute- startMinute) / 4);
            }
        }

        void UpdateDuration()
        {
            Graphics gfx = this.CreateGraphics();
            gfx.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            gfx.CompositingQuality = System.Drawing.Drawing2D.CompositingQuality.HighQuality;
            gfx.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
            Brush solidBrush = new SolidBrush(Color.Blue);
            
            
            double startAngel = (startMinute / 4) * (Math.PI / 180);
            double endAngel = (endMinute / 4) * (Math.PI / 180);
            btnStartMinute.Location = new Point((int)(boder.Location.X + boder.Width / 2 - Constants.clockPoint / 2 + radius * Math.Cos(startAngel)), (int)(boder.Location.Y + boder.Height / 2 - Constants.clockPoint / 2 + radius * Math.Sin(startAngel)));


            btnEndMinute.Location = new Point((int)(boder.Location.X + boder.Width / 2 - Constants.clockPoint / 2 + radius * Math.Cos(endAngel)), (int)(boder.Location.Y + boder.Height / 2 - Constants.clockPoint / 2 + radius * Math.Sin(endAngel)));
            if ((startMinute > startMinuteOld) & (startMinute < endMinute))
            {
                DrawDuration(gfx, startMinuteOld, startMinute, new SolidBrush(this.BackColor));
            }
            else if ((startMinute < startMinuteOld) & (startMinuteOld < endMinute))
            {
                DrawDuration(gfx, startMinute, startMinuteOld, solidBrush);
            }
            DrawDuration(gfx, startMinute, endMinute, solidBrush);
            startMinuteOld = startMinute;
            endMinuteOld = endMinute;
        }

        protected override void OnLocationChanged(EventArgs e)
        {
            //base.OnLocationChanged(e);
            //ShowDuration();
        }
        protected override void OnSizeChanged(EventArgs e)
        {
            radius = Math.Min(this.Width, this.Height) / 2;
            boder = new Rectangle(new Point(Constants.clockPoint / 2, Constants.clockPoint / 2), new Size(2 * radius - Constants.clockPoint, 2 * radius - Constants.clockPoint));
            ShowDuration();
        }
        void ShowDuration()
        {
            Graphics gfx = this.CreateGraphics();
            gfx.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            // the next two lines of code (not comments) are needed to get the highest 
            // possible quiality of anti-aliasing. Remove them if you want the image to render faster.
            //pe.Graphics.CompositingQuality = System.Drawing.Drawing2D.CompositingQuality.HighQuality;
            //pe.Graphics.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;

            Brush solidBrush = new SolidBrush(Color.Blue);
            Pen blackPen = new Pen(Color.Blue, 1);
            
            radius = Math.Min(this.Width, this.Height) / 2;
            boder = new Rectangle(new Point(Constants.clockPoint / 2, Constants.clockPoint / 2), new Size(2 * radius - Constants.clockPoint, 2 * radius - Constants.clockPoint));
            radius = boder.Width / 2;
            refPoint = new Point(boder.Location.X + boder.Width / 2, boder.Location.Y + boder.Height / 2);
            double startAngel = (startMinute / 4) * (Math.PI / 180);
            double endAngel = (endMinute / 4) * (Math.PI / 180);
            btnStartMinute.Location = new Point((int)(boder.Location.X + boder.Width / 2 - Constants.clockPoint / 2 + radius * Math.Cos(startAngel)), (int)(boder.Location.Y + boder.Height / 2 - Constants.clockPoint / 2 + radius * Math.Sin(startAngel)));
            

            btnEndMinute.Location = new Point((int)(boder.Location.X + boder.Width / 2 - Constants.clockPoint / 2 + radius * Math.Cos(endAngel)), (int)(boder.Location.Y + boder.Height / 2 - Constants.clockPoint / 2 + radius * Math.Sin(endAngel)));
            
        }
        #endregion
    }
}
