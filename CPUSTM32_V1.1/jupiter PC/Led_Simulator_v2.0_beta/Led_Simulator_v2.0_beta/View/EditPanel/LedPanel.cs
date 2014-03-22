using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
using Led_Simulator_v2._0_beta.View;

namespace Led_Simulator_v2._0_beta
{
    public class LedPanel : Panel
    {
        private Boolean childSelected;
        public Boolean ChildSelected
        {
            get { return childSelected; }
            set { childSelected = value; }
        }

        protected override void OnMouseWheel(MouseEventArgs e)
        {
            if (!ChildSelected)
            {
                base.OnMouseWheel(e);
            }
        }
    }

    public partial class Form1 : Form, IView
    {
    /* This function is used to show all data to panel */
        LedPanel pnLedNode=new LedPanel();
        List<LedNodeView> selectedList = new List<LedNodeView>();
        public Boolean NodeSelected
        {
            get
            {
                return (selectedList.Count != 0);
            }
        } 
        void LedPanelInit()
        {
            pnLedNode.ChildSelected = true;
            pnLedNode.AutoScroll = true;
            pnLedNode.Top = 15;
            pnLedNode.Left = 2;
            pnLedNode.Width = gbLedEdit.Width - 3;
            pnLedNode.Height = gbLedEdit.Height - 20;
            pnLedNode.MouseClick += new MouseEventHandler(pnLedNode_MouseClick);
            pnLedNode.MouseMove+=new MouseEventHandler(pnLedNode_MouseMove);
            pnLedNode.MouseDown+=new MouseEventHandler(pnLedNode_MouseDown);
            pnLedNode.MouseUp+=new MouseEventHandler(pnLedNode_MouseUp);
            gbLedEdit.Controls.Add(pnLedNode);
             g = pnLedNode.CreateGraphics();
             bgBrush = new SolidBrush(pnLedNode.BackColor);
             pen = new Pen(Color.LightSkyBlue, 1);
             pen.DashStyle = System.Drawing.Drawing2D.DashStyle.DashDotDot;
             fgBrush = new SolidBrush(Color.FromArgb(128, 0xFF, 0xAA, 0xAA));
        }

        private void pnLedNode_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                pnLedNode.Select();
                if (curNode != null)
                {
                    curNode.Choosed = false;
                    CurNode = null;
                    CurIndex = new LedNodeIndex(-1, -1);
                    NotifyChange("CurIndex");
                }
                foreach (LedNodeView c in selectedList)
                {
                    c.Choosed = false;
                }
                selectedList.Clear();
                //selectedList.Clear();
            }
            else if (e.Button == MouseButtons.Right)
            {
                Point pt = pnLedNode.PointToScreen(e.Location);
                ctMenu.Show(pt);
            }
        }
        Boolean dragFlag =false;
        Point oldLocation;
        Point newLocation;
        Graphics g;
        Brush bgBrush;
        Pen pen;
        Brush fgBrush;
        Rectangle curRect;
        private void pnLedNode_MouseMove(object sender, MouseEventArgs e)
        {
            if (dragFlag)
            {
                if (curNode != null)
                {
                    curNode.Choosed = false;
                    CurNode = null;
                    CurIndex = new LedNodeIndex(-1, -1);
                    NotifyChange("CurIndex");
                }
                foreach (LedNodeView c in selectedList)
                {
                    c.Choosed = false;
                }
                selectedList.Clear();
                newLocation = pnLedNode.PointToClient(Cursor.Position);
                curRect = new Rectangle(Math.Min(oldLocation.X, newLocation.X), Math.Min(oldLocation.Y, newLocation.Y), Math.Abs(newLocation.X - oldLocation.X), Math.Abs(newLocation.Y - oldLocation.Y));
                g.FillRectangle(bgBrush, pnLedNode.Bounds); 
                g.DrawRectangle(pen, curRect);
                foreach (Control c in pnLedNode.Controls)
                {
                    if (c is LedNodeView)
                    {
                        LedNodeView node = (LedNodeView)c;
                        if (node.Type == Constants.StateType.Data)
                        {
                            if (curRect.IntersectsWith(c.Bounds))
                            {
                                node.Choosed = true;
                            }
                            else
                            {
                                node.Choosed = false;
                            }
                        }
                    }
                }
            }
        }
        private void pnLedNode_MouseDown(object sender, MouseEventArgs e)
        {
        dragFlag=true;
        oldLocation = pnLedNode.PointToClient(Cursor.Position);
        curRect = new Rectangle(); ;
        }
        private void pnLedNode_MouseUp(object sender, MouseEventArgs e)
        {
            //g.FillRectangle(bgBrush, pnLedNode.Bounds);
            dragFlag = false;
            foreach (Control c in pnLedNode.Controls)
            {
                if (c is LedNodeView)
                {
                    LedNodeView node = (LedNodeView)c;
                    if (node.Choosed)
                    {
                        selectedList.Add(node);
                    }
                }
            }
            NotifyChange("NodeSelectedChange");
            g.FillRectangle(bgBrush, pnLedNode.Bounds);
        }
    }
}
