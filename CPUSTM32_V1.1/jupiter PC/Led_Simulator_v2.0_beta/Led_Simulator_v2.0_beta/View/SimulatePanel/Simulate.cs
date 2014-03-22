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
        private List<LedNodeView> simulateNodeList;
        public ArrayList SimulateData 
        {
            set
            {
                if (value == null)
                {
                    if (simulateNodeList != null)
                    {
                        simulateNodeList.Clear();
                        simulateNodeList = null;
                    }
                    pnSimulate.Controls.Clear();
                }
                else
                {
                    if (simulateNodeList == null)
                    {
                        simulateNodeList = new List<LedNodeView>();
                        int StateType = (int)value[0];
                        for (int ledIndex = 0; ledIndex < (value.Count - 2); ledIndex++)
                        {
                            LedNodeView curNode = new LedNodeView();
                            curNode.color = Color.Blue;
                            curNode.Location = new System.Drawing.Point(10 + 30 * ledIndex, 5);
                            curNode.Size = new System.Drawing.Size(25, 25);
                            curNode.Name = "simulateNode" + (char)(ledIndex);//LedNode + LedIndex + StateIndex
                            curNode.Value = (int)value[ledIndex + 2];
                            curNode.Type = Constants.StateType.Data;
                            curNode.LedIndex = ledIndex;

                            pnSimulate.Controls.Add(curNode);
                            simulateNodeList.Add(curNode);
                        }
                    }
                    else
                    {
                        foreach (LedNodeView curNode in simulateNodeList)
                        {
                            curNode.Value = (int)value[curNode.LedIndex + 2];
                        }
                    
                    }
                }
            }
        }
    }
}