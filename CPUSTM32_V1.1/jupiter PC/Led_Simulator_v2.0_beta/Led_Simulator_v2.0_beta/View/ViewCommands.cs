using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using System.IO.Ports;
//This file is used to initialize global variables for Form1
namespace Led_Simulator_v2._0_beta
{
    public partial class Form1 : Form, IView
    {
        private Mediator commandHub;
        public Mediator CommandHub
        {
            set
            {
                commandHub = value;
            }
        }

        private Hashtable allCommand;
        public Hashtable AllCommand
        {
            set
            {
                allCommand = value;
                InitializeCommandHub();
            }
        }

        private void InitializeCommandHub()
        {
            //This function is used to init command list and all control to call each command of this application
            Command curCommand;
            //Creat New file
            curCommand = (Command)allCommand["FileNew"];
            if (curCommand != null)
            {
                curCommand.commandKey = Keys.Control | Keys.N;
                curCommand.commandItem = new List<ToolStripItem>();
                curCommand.commandItem.Add(mnuFileNew);
            }

            //Open file
            curCommand = (Command)allCommand["FileOpen"];
            if (curCommand != null)
            {
                curCommand.commandKey = Keys.Control | Keys.O;
                curCommand.commandItem = new List<ToolStripItem>();
                curCommand.commandItem.Add(mnuFileOpen);
            }

            //Save file
            curCommand = (Command)allCommand["FileSave"];
            if (curCommand != null)
            {
            curCommand.commandKey = Keys.Control | Keys.S;
            curCommand.commandItem = new List<ToolStripItem>();
            curCommand.commandItem.Add(mnuFileSave);
            }

            //Close file
            
            curCommand = (Command)allCommand["FileClose"];
            if (curCommand != null)
            {
                curCommand.commandItem = new List<ToolStripItem>();
            curCommand.commandItem.Add(mnuFileClose);
            }

            //Exit
            curCommand = (Command)allCommand["Exit"];
            if (curCommand != null)
            {
                curCommand.commandItem = new List<ToolStripItem>();
            curCommand.commandItem.Add(mnuExit);
            }

            //Undo
            curCommand = (Command)allCommand["Undo"];
            if (curCommand != null)
            {
            curCommand.commandKey = Keys.Control | Keys.Z;
            curCommand.commandItem = new List<ToolStripItem>();
            curCommand.commandItem.Add(mnuUndo);
            }

            //Redo
            curCommand = (Command)allCommand["Redo"];
            if (curCommand != null)
            {
            curCommand.commandKey = Keys.Control | Keys.Y;
            curCommand.commandItem = new List<ToolStripItem>();
            curCommand.commandItem.Add(mnuRedo);
            }

            //Add State Above
            curCommand = (Command)allCommand["EditNode"];
            if (curCommand != null)
            {
                curCommand.commandControl = new List<Control>();
                curCommand.commandControl.Add(pnLedNode);
                curCommand.commandControl.Add(gbStatus);
            }

            //Add State Above
            curCommand = (Command)allCommand["AddStateAbove"];
            if (curCommand != null)
            {
                curCommand.commandItem = new List<ToolStripItem>();
            curCommand.commandItem.Add(mnuAddStateAbove);
            curCommand.commandItem.Add(tsAddStateAbove);
            }

            //Add State Below
            curCommand = (Command)allCommand["AddStateBelow"];
            if (curCommand != null)
            {
                curCommand.commandItem = new List<ToolStripItem>();
            curCommand.commandItem.Add(mnuAddStateBelow);
            curCommand.commandItem.Add(tsAddStateBelow);
            }

            //Remove State
            curCommand = (Command)allCommand["RemoveState"];
            if (curCommand != null)
            {
                curCommand.commandItem = new List<ToolStripItem>();
            curCommand.commandItem.Add(mnuRemoveState);
            curCommand.commandItem.Add(tsRemoveState);
            }

            //Add Start For
            curCommand = (Command)allCommand["AddStartFor"];
            if (curCommand != null)
            {
                curCommand.commandItem = new List<ToolStripItem>();
            curCommand.commandItem.Add(mnuAddStartFor);
            curCommand.commandItem.Add(tsAddStartFor);
            }

            //Add End For
            curCommand = (Command)allCommand["AddEndFor"];
            if (curCommand != null)
            {
                curCommand.commandItem = new List<ToolStripItem>();
            curCommand.commandItem.Add(mnuAddEndFor);
            curCommand.commandItem.Add(tsAddEndFor);
            }

            //Add Led Left
            curCommand = (Command)allCommand["AddLedLeft"];
            if (curCommand != null)
            {
                curCommand.commandItem = new List<ToolStripItem>();
            curCommand.commandItem.Add(mnuAddLedLeft);
            curCommand.commandItem.Add(tsAddLedLeft);
            }

            //Add Led Right
            curCommand = (Command)allCommand["AddLedRight"];
            if (curCommand != null)
            {
                curCommand.commandItem = new List<ToolStripItem>();
            curCommand.commandItem.Add(mnuAddLedRight);
            curCommand.commandItem.Add(tsAddLedRight);
            }

            //Remove Led
            curCommand = (Command)allCommand["RemoveLed"];
            if (curCommand != null)
            {
                curCommand.commandItem = new List<ToolStripItem>();
            curCommand.commandItem.Add(mnuRemoveLed);
            curCommand.commandItem.Add(tsRemoveLed);
            }

            //ClearAllEffect
            curCommand = (Command)allCommand["ClearAllEffect"];
            if (curCommand != null)
            {
                curCommand.commandItem = new List<ToolStripItem>();
                curCommand.commandItem.Add(mnuClearAllEffect);
            }

            //MaxBrightEffect
            curCommand = (Command)allCommand["MaxBrightEffect"];
            if (curCommand != null)
            {
                curCommand.commandItem = new List<ToolStripItem>();
                curCommand.commandItem.Add(mnuMaxBrightEffect);
            }

            //RevertBrightEffect
            curCommand = (Command)allCommand["RevertBrightEffect"];
            if (curCommand != null)
            {
                curCommand.commandItem = new List<ToolStripItem>();
                curCommand.commandItem.Add(mnuRevertEffect);
            }

            //BlindBrightEffect
            curCommand = (Command)allCommand["BlindBrightEffect"];
            if (curCommand != null)
            {
                curCommand.commandItem = new List<ToolStripItem>();
                curCommand.commandItem.Add(mnuBlindEffect);
            }

            //FireBallEffect
            curCommand = (Command)allCommand["FireBallEffect"];
            if (curCommand != null)
            {
                curCommand.commandItem = new List<ToolStripItem>();
                curCommand.commandItem.Add(mnuFireBallEffect);
            }

            //Start Simulate
            curCommand = (Command)allCommand["StartSimulate"];
            if (curCommand != null)
            {
                curCommand.commandItem = new List<ToolStripItem>();
            curCommand.commandItem.Add(mnuStartSimulate);
            curCommand.commandItem.Add(tsStartSimulate);
            }

            //Pause Simulate
            curCommand = (Command)allCommand["PauseSimulate"];
            if (curCommand != null)
            {
                curCommand.commandItem = new List<ToolStripItem>();
            curCommand.commandItem.Add(mnuPauseSimulate);
            curCommand.commandItem.Add(tsPauseSimulate);
            }

            //Stop Simulate
            curCommand = (Command)allCommand["StopSimulate"];
            if (curCommand != null)
            {
                curCommand.commandItem = new List<ToolStripItem>();
            curCommand.commandItem.Add(mnuStopSimulate);
            curCommand.commandItem.Add(tsStopSimulate);
            }
        }
    }
}