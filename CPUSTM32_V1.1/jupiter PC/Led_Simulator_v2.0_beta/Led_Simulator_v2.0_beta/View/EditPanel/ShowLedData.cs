using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using System.Drawing;
using Led_Simulator_v2._0_beta.View;

namespace Led_Simulator_v2._0_beta
{
    public partial class Form1 : Form, IView
    {
        private int stateNumber;
        private int ledNumber;
        private LedNodeIndex defaultIndex = new LedNodeIndex(-1, -1);
        private LedNodeIndex curIndex=new LedNodeIndex(-1,-1);
        public LedNodeIndex CurIndex
        {
            get { return curIndex; }
            set
            {
                if (curIndex!=value)
                {
                    SelectNode(value.stateIndex, value.ledIndex);
                    //curIndex = value;
                }
            }
        }

        private LedNodeView curNode=null;
        private LedNodeView CurNode
        {
            set
            {
                if (curNode != value)
                {
                    //UpdateStatus(value);
                    if (value == null)
                    {
                        curNode.Choosed = false;
                        pnLedNode.ChildSelected = false;
                        curNode = null;
                        curIndex = new LedNodeIndex(-1, -1);
                        UpdateStatus(null);
                    }
                    else
                    {
                        if (curNode != null)
                        {
                            curNode.Choosed = false;
                        }
                        curNode = value;
                        if (curNode.Type != Constants.StateType.Endfor)
                        {
                            pnLedNode.ChildSelected = true;
                        }
                        curIndex = new LedNodeIndex(curNode.StateIndex, curNode.LedIndex);
                        curNode.Select();
                        curNode.Choosed = true;
                        bright = curNode.Value;
                        UpdateStatus(curNode);
                    }
                }
            }
        }

        //private int stateCommonInfo;
        public int StateCommonInfo
        {
            get { return Convert.ToInt32(tbGlobalInfo.Text); }
            set
            {
                //tbGlobalInfo.Visible = true;
                tbGlobalInfo.Text = value.ToString();
                if (curNode != null)
                {
                    if (curNode.Type == Constants.StateType.StartFor)
                    {
                        curNode.Value = value;
                    }
                }
            }
        }

        private int bright;
        public int Bright
        {
            get { return bright; }
            set
            {
                if (bright != value)
                {
                    bright = value;
                    curNode.Value = value;
                    tbValue.Text = curNode.Value.ToString();
                }
            }
        }

        private void LedNodeView_Click(object sender, MouseEventArgs e)
        {
            foreach (LedNodeView c in selectedList)
            {
                c.Choosed = false;
            }
            selectedList.Clear();
            if (curNode != (LedNodeView)sender)
            {

                CurNode = (LedNodeView)sender;
                NotifyChange("CurIndex");
            }
        }

        private void LedNodeView_Mouse_Wheel(object sender, MouseEventArgs e)
        {
            if (LedNodeMouseWheelCommand != null)
            {
                LedNodeMouseWheelCommand(sender, e);
            }
        }

        private void LedNodeView_Mouse_Double_Click(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                if (LedNodeMouseDoubleClickCommand != null)
                {
                    LedNodeMouseDoubleClickCommand(sender, e);
                }
            }
        }

        private void LedNodeView_MouseMove(object sender, MouseEventArgs e)
        {
            LedNodeView curNode = (LedNodeView)sender;
            pnLedNode_MouseMove(sender, e);
        }

        private void btnChangeLedNode_Click(object sender, EventArgs e)
        {
            ChangeNodeValue();
        }

        private void LedNodeView_MouseDown(object sender, MouseEventArgs e)
        {
            pnLedNode_MouseDown(sender, e);
        }

        private List<LedNodeView> showList = new List<LedNodeView>();

        private void UpdateStatus(LedNodeView curNode)
        {
            
            //Update information in to Status box
            tbGlobalInfo.Visible = false;
            lbGlobalInfo.Visible = false;
            tbValue.Visible = false;
            lbValue.Visible = false;
            lbState.Visible = false;
            lbLed.Visible = false;
            if (curNode != null)
            {
                int ledIndex = curNode.LedIndex;
                int stateIndex = curNode.StateIndex;
                lbState.Visible = true;
                lbState.Text = "State        " + (stateIndex+1).ToString() + "/"+stateNumber.ToString();
                {
                    //Update value only
                    switch (curNode.Type)
                    {
                        case Constants.StateType.Data:
                            lbLed.Visible = true;
                            tbValue.Visible = true;
                            lbValue.Visible = true;
                            lbGlobalInfo.Visible = true;
                            tbGlobalInfo.Visible = true;
                            lbLed.Text = "Led          " + (ledIndex+1).ToString()+"/"+ledNumber.ToString();
                            lbValue.Text = "Bright Value";
                            tbValue.Text = curNode.Value.ToString();

                            lbGlobalInfo.Text = "Bright time";

                            //tbGlobalInfo.Text = Data.Get_time(cur_state_index).ToString();
                            break;
                        case Constants.StateType.StartFor:
                            lbGlobalInfo.Visible = true;
                            tbGlobalInfo.Visible = true;
                            lbGlobalInfo.Text = "Loop time";
                            break;
                    }
                }
            }
        }
        private void SelectNode(int stateIndex, int ledIndex)
        {
            foreach (Control c in pnLedNode.Controls)
            {
                if (c is LedNodeView)
                {
                    LedNodeView node = (LedNodeView)c;
                    if ((node.LedIndex == ledIndex) && (node.StateIndex == stateIndex))
                    {
                        CurNode = node;
                        break;
                    }
                }
            }
        }

        private void ChangeNodeValue()
        {
            if (curNode == null)
                return;
            switch (curNode.Type)
            { 
                case Constants.StateType.Data:
                    NotifyChange("Bright", Convert.ToInt32(tbValue.Text));
                    NotifyChange("StateCommonValue", StateCommonInfo);
                    break;
                case Constants.StateType.StartFor:
                    NotifyChange("StateCommonValue", StateCommonInfo);
                    break;
            }
        }
        
        private void ShowLedData(DataLedArrayNode dataStructure)
        {
            //TODO:
            showList.Clear();
            pnLedNode.Controls.Clear();
            //ArrayList led_state= (ArrayList)dataStructure.Led[0];
            stateNumber = dataStructure.StateNumber;
            ledNumber = dataStructure.LedNumber;
            for (int stateIndex = 0; stateIndex < dataStructure.StateNumber; stateIndex++)
            {
                ArrayList CurState = (ArrayList)dataStructure.GetState(stateIndex);
                Constants.StateType StateType = dataStructure.GetStateType(stateIndex);
                switch (StateType)
                {
                    case Constants.StateType.Data:
                        for (int ledIndex = 0; ledIndex < dataStructure.LedNumber; ledIndex++)
                        {
                            LedNodeView StateNode = new LedNodeView();
                            StateNode.color = Color.Blue;
                            StateNode.Location = new System.Drawing.Point(10 + 30 * ledIndex, 5 + 30 * stateIndex);
                            StateNode.Size = new System.Drawing.Size(25, 25);
                            StateNode.Name = "LedNodeView" + (char)(ledIndex + 1) + (char)(stateIndex + 1);//LedNodeView + LedIndex + StateIndex
                            StateNode.Value = (int)CurState[ledIndex + 2];
                            StateNode.Type = Constants.StateType.Data;
                            StateNode.LedIndex = ledIndex;
                            StateNode.StateIndex = stateIndex;

                            StateNode.MouseClick += new MouseEventHandler(LedNodeView_Click);
                            StateNode.MouseWheel += new MouseEventHandler(LedNodeView_Mouse_Wheel);
                            StateNode.MouseDoubleClick += new MouseEventHandler(LedNodeView_Mouse_Double_Click);
                            StateNode.MouseMove += new MouseEventHandler(LedNodeView_MouseMove);
                            StateNode.MouseDown += new MouseEventHandler(pnLedNode_MouseDown);
                            StateNode.MouseUp += new MouseEventHandler(pnLedNode_MouseUp);
                            pnLedNode.Controls.Add(StateNode);
                            showList.Add(StateNode);
                            //if (curNode == null) curNode = StateNode;
                        }
                        break;
                    case Constants.StateType.StartFor:
                        LedNodeView StartForNode = new LedNodeView();
                        StartForNode.color = Color.Red;
                        StartForNode.Location = new System.Drawing.Point(10, 5 + 30 * stateIndex);
                        StartForNode.Size = new System.Drawing.Size((int)(30 * dataStructure.LedNumber) - 5, 25);
                        StartForNode.Name = "LedNodeView" + (char)1 + (char)(stateIndex + 1);//LedNodeView + StateIndex
                        StartForNode.Value = dataStructure.GetCommonValue(stateIndex);
                        StartForNode.Type = Constants.StateType.StartFor;
                        StartForNode.LedIndex = 0;
                        StartForNode.StateIndex = stateIndex;

                        StartForNode.MouseClick += new MouseEventHandler(LedNodeView_Click);
                        StartForNode.MouseWheel += new MouseEventHandler(LedNodeView_Mouse_Wheel);
                        pnLedNode.Controls.Add(StartForNode);
                        showList.Add(StartForNode);
                        break;
                    case Constants.StateType.Endfor:
                        LedNodeView EndForNode = new LedNodeView();
                        EndForNode.color = Color.Yellow;
                        EndForNode.Location = new System.Drawing.Point(10, 5 + 30 * stateIndex);
                        EndForNode.Size = new System.Drawing.Size((int)(30 * dataStructure.LedNumber) - 5, 25);
                        EndForNode.Name = "LedNodeView" + (char)1 + (char)(stateIndex + 1);//LedNodeView + StateIndex
                        EndForNode.Value = (int)Constants.MAX_BRIGHT;
                        EndForNode.Type = Constants.StateType.Endfor;
                        EndForNode.LedIndex = 0;
                        EndForNode.StateIndex = stateIndex;
                        EndForNode.Text = "}";
                        //EndForNode.TextAlign = StringAlignment.Far;

                        EndForNode.MouseClick += new MouseEventHandler(LedNodeView_Click);
                        EndForNode.MouseWheel += new MouseEventHandler(LedNodeView_Mouse_Wheel);
                        pnLedNode.Controls.Add(EndForNode);
                        showList.Add(EndForNode);
                        break;
                }
            }
            if (curIndex != defaultIndex)
            {
                SelectNode(curIndex.stateIndex, curIndex.ledIndex);
            }
        }
    }
}