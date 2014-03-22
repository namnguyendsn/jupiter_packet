using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Led_Simulator_v2._0_beta.View
{
    public partial class LedNodeView : Control
    {
        public LedNodeView()
        {
            InitializeComponent();
        }

        private Boolean choosed;
        public Boolean Choosed
        {
            get { return choosed;}
            set 
            {
                if (choosed != value)
                {
                    choosed = value;
                    Invalidate();
                }
            }
        }
        private int _Value;
        public int Value
        {
            get { return _Value; }
            set
            {
                if (_Value == value)
                    return;
                _Value = value;
                Invalidate();
            }
        }
        private int _LedIndex;
        public int LedIndex
        {
            get { return _LedIndex; }
            set
            {
                if (_LedIndex == value)
                    return;
                _LedIndex = value;
            }
        }
        private int _StateIndex;
        public int StateIndex
        {
            get { return _StateIndex; }
            set
            {
                if (_StateIndex == value)
                    return;
                _StateIndex = value;
            }
        }
        private Color _Color;
        public Color color
        {
            get { return _Color; }
            set
            {
                _Color = value;
                Invalidate();
            }
        }

        private Constants.StateType _Type;
        public Constants.StateType Type
        {
            get { return _Type; }
            set
            {
                switch (value)
                {
                    case Constants.StateType.Data:
                     case Constants.StateType.StartFor:
                    case Constants.StateType.Endfor:
                        _Type = value;
                        break;
                    default:
                        _Type = Constants.StateType.None;
                        break;
                }
            }
        }

        protected override void OnPaint(PaintEventArgs pe)
        {
            Graphics gfx = pe.Graphics;
            Rectangle rc = ClientRectangle;
            // Create pen.
            Pen blackPen = new Pen(Color.Black, 1);
            SolidBrush Brush = new SolidBrush(_Color);
            SolidBrush BrushBG = new SolidBrush(Color.DarkSeaGreen);
            // Create rectangle.
            Rectangle rectFill = rc;

            // Draw background rectangle to screen.
            gfx.FillRectangle(BrushBG, rectFill);
            // Draw value
            if (_Type == Constants.StateType.Data)
            {
                rectFill.Height = (int)((rectFill.Height * _Value) / Constants.MAX_BRIGHT);
            }
            else
            {
                rectFill.Height = rc.Height;
            }
            rectFill.Y = rc.Height - rectFill.Height;
            //rectFill.Width -= 4;
            //rectFill.X += 2;
            gfx.FillRectangle(Brush, rectFill);
            if (Choosed)
            {
                Rectangle rectBoder = rc;
                rectBoder.Height -= 1;
                gfx.DrawRectangle(blackPen, rectBoder);
                //Add text
                RectangleF drawStr = rc;
                StringFormat drawFormat = new StringFormat();
                SolidBrush drawBrush = new SolidBrush(Color.Black);
                Font drawFont = new Font("Segoe UI", rectBoder.Height / 3);
                String Str;
                switch (_Type)
                {
                    case Constants.StateType.Data:
                        Str = _Value.ToString();
                        drawFormat.Alignment = StringAlignment.Center;
                        drawFormat.LineAlignment = StringAlignment.Center;

                        gfx.DrawString(Str, drawFont, drawBrush, drawStr, drawFormat);
                        break;
                    case Constants.StateType.StartFor:

                        Str = "{ " + _Value.ToString();
                        drawFormat.Alignment = StringAlignment.Near;
                        drawFormat.LineAlignment = StringAlignment.Center;
                        gfx.DrawString(Str, drawFont, drawBrush, drawStr, drawFormat);
                        break;
                    case Constants.StateType.Endfor:
                        Str = "}";

                        drawFormat.Alignment = StringAlignment.Near;
                        drawFormat.LineAlignment = StringAlignment.Center;
                        gfx.DrawString(Str, drawFont, drawBrush, drawStr, drawFormat);
                        break;
                    default:
                        break;
                }

            }
        }
    }
}
