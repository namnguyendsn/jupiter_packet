using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Collections;
using System.Windows.Forms;
using Led_Simulator_v2._0_beta.View;

namespace Led_Simulator_v2._0_beta
{
    public partial class Presenter
    {
        private readonly IModel model;
        private readonly IView view;

        private LedNodeIndex viewIndex=new LedNodeIndex(-1,-1);
        LedNodeIndex ViewIndex
        {
            get
            { 
                return viewIndex; 
            }
            set
            {
                if (viewIndex != value)
                {
                    //if (viewIndex.stateIndex != value.stateIndex)
                    {
                        view.StateCommonInfo = model.GetStateInfo(value.stateIndex);
                    }
                    viewIndex = value;
                    if (view.CurIndex != value)
                    {
                        view.CurIndex = value;
                        view.Bright = model.GetBright(viewIndex);
                    }
                }
            }
        }

        private System.Windows.Forms.SaveFileDialog saveFileDialog;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.Timer timer;
        Mediator commandHub;
        public Presenter(IView view, IModel model)
        {
            this.saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.timer = new System.Windows.Forms.Timer();
            timer.Interval = 100;
            timer.Tick += new EventHandler(timer_Tick);
            #region Init model and view
            this.view = view;
            this.model = model;
            view.FileNewCommand += fileNewCommand_Called;
            view.FileOpenCommand += fileOpenCommand_Called;
            view.FileSaveCommand += fileSaveCommand_Called;
            view.FileCloseCommand += fileCloseCommand_Called;
            view.ExitCommand += exitCommand_Called;

            view.UndoCommand += undoCommand_Called;
            view.RedoCommand += redoCommand_Called;

            view.AddStateAboveCommand += addStateAboveCommand_Called;
            view.AddStateBelowCommand += addStateBelowCommand_Called;
            view.RemoveStateCommand += removeStateCommand_Called;
            view.AddStartForCommand += addStartForCommand_Called;
            view.AddEndForCommand += addEndForCommand_Called;

            view.AddLedLeftCommand += addLedLeftCommand_Called;
            view.AddLedRightCommand += addLedRightCommand_Called;
            view.RemoveLedCommand += removeLedCommand_Called;

            view.StartSimulateCommand += startSimulateCommand_Called;
            view.PauseSimulateCommand += pauseSimulateCommand_Called;
            view.StopSimulateCommand += stopSimulateCommand_Called;
            view.ClearAllEffectCommand += clearAllEffectCommand_Called;
            view.MaxBrightEffectCommand += maxBrightEffectCommand_Called;
            view.RevertEffectCommand += revertEffectCommand_Called;
            view.BlindEffectCommand += blindEffectCommand_Called;
            view.FireBallEffectCommand += fireBallEffectCommand_Called;
            view.LedNodeMouseWheelCommand += mouseWheelCommand_Called;
            view.LedNodeMouseDoubleClickCommand += mouseDoubleClickCommand_Called;
            view.SerialPort_DataReceived += serialPort_DataReceived;
            view.SendData = new SendDataDelegate(SendData);

            model.PropertyChanged += model_PropertyChanged;
            view.PropertyChanged += view_PropertyChanged;
            view.LedData = model.LedData;
            //view.CurIndex = new LedNodeIndex(0, 0);
            //ViewIndex = new LedNodeIndex(0, 0);
            #endregion

            CollectAllCommand();
            view.AllCommand = allCommand;
            view.CommandHub = commandHub;
            #region Init CommandHub
            InitCommandHub();
            AddOnly(curCondition, "NotSimulating");
            commandHub.ReceiveCommand("InitCommand");
            #endregion
        }

        #region IView handlers
        void fileNewCommand_Called(object sender, EventArgs e)
        {
            if (model.NewFile())
            {
                view.LedData = model.LedData;
                ViewIndex = new LedNodeIndex(0, 0);
                commandHub.ReceiveCommand("FileNew");
            }
        }

        void fileOpenCommand_Called(object sender, EventArgs e)
        {
            openFileDialog.ShowDialog();
            string filePath = openFileDialog.FileName;
            if (model.ReadFile("bin", filePath))
            {
                view.LedData = model.LedData;
                ViewIndex = new LedNodeIndex(0, 0);
                commandHub.ReceiveCommand("FileOpen");
            }
        }

        void fileSaveCommand_Called(object sender, EventArgs e)
        {
            saveFileDialog.ShowDialog();
            string filePath = saveFileDialog.FileName;
            if (model.SaveFile("bin", filePath))
            {
                commandHub.ReceiveCommand("FileSave");
            }
        }

        void fileCloseCommand_Called(object sender, EventArgs e)
        {

        }

        void exitCommand_Called(object sender, EventArgs e)
        {

        }

        void undoCommand_Called(object sender, EventArgs e)
        {
            if (model.GetUndoStep())
            {
                view.LedData = model.LedData;
                //ViewIndex = new LedNodeIndex(0, 0);
                commandHub.ReceiveCommand("Undo");
            }
        }

        void redoCommand_Called(object sender, EventArgs e)
        {
            if (model.GetRedoStep())
            {
                view.LedData = model.LedData;
                //ViewIndex = new LedNodeIndex(0, 0);
                commandHub.ReceiveCommand("Redo");
            }
        }

        void addStateAboveCommand_Called(object sender, EventArgs e)
        {
            if (model.AddStateAbove(ViewIndex.stateIndex))
            {
                //TODO:Update view and curIndex
                ViewIndex = new LedNodeIndex(viewIndex.stateIndex++, viewIndex.ledIndex);
                view.LedData = model.LedData;
                commandHub.ReceiveCommand("AddStateAbove");
            }
        }

        void addStateBelowCommand_Called(object sender, EventArgs e)
        {
            if (model.AddStateBelow(ViewIndex.stateIndex))
            {
                //TODO:Update view and curIndex
                view.LedData = model.LedData;
                commandHub.ReceiveCommand("AddStateBelow");
            }
        }

        void removeStateCommand_Called(object sender, EventArgs e)
        {
            if (model.StateNumber > 1)
            {
                if (model.RemoveState(ViewIndex.stateIndex))
                {
                    int newStateIndex = ViewIndex.stateIndex;
                    int newLedIndex = ViewIndex.ledIndex;
                    if (newStateIndex > 1)
                    {
                        newStateIndex--;
                    }
                    if (model.GetStateType(ViewIndex.stateIndex) != Constants.StateType.Data)
                    {
                        //This is StartFor or EndFor state, so the cur_led_index must be 0
                        newLedIndex = 0;
                    }
                    view.LedData = model.LedData;
                    ViewIndex = new LedNodeIndex(newStateIndex, newLedIndex);
                    commandHub.ReceiveCommand("RemoveState");
                }
            }
        }

        void addStartForCommand_Called(object sender, EventArgs e)
        {
            if (model.AddStartFor(ViewIndex.stateIndex))
            {
                int newStateIndex=ViewIndex.stateIndex+1;
                view.LedData = model.LedData;
                ViewIndex = new LedNodeIndex(newStateIndex, ViewIndex.ledIndex);
                commandHub.ReceiveCommand("AddStartFor");
            }
        }

        void addEndForCommand_Called(object sender, EventArgs e)
        {
            if (model.AddEndFor(ViewIndex.stateIndex+1))
            {
                view.LedData = model.LedData;
                commandHub.ReceiveCommand("AddEndFor");
            }
        }

        void addLedLeftCommand_Called(object sender, EventArgs e)
        {
            if (model.AddLedLeft(ViewIndex.ledIndex))
            {
                int newLedIndex = ViewIndex.ledIndex + 1;
                view.LedData = model.LedData;
                ViewIndex = new LedNodeIndex(newLedIndex, ViewIndex.ledIndex);
                commandHub.ReceiveCommand("AddLedLeft");
            }
        }

        void addLedRightCommand_Called(object sender, EventArgs e)
        {
            if (model.AddLedRight(ViewIndex.ledIndex))
            {
                view.LedData = model.LedData;
                commandHub.ReceiveCommand("AddLedRight");
            }
        }

        void removeLedCommand_Called(object sender, EventArgs e)
        {
            if (model.LedNumber > 1)
            {
                if (model.RemoveLed(ViewIndex.ledIndex))
                {
                    view.LedData = model.LedData;
                    ViewIndex.ledIndex--;
                    ViewIndex = new LedNodeIndex(ViewIndex.stateIndex, ViewIndex.ledIndex - 1);
                    commandHub.ReceiveCommand("RemoveLed");
                }
            }
        }

        Boolean forLoopValid = false;
        int timerCount = 1;
        int curStateShow = 0;
        Stack<int> stackStartFor = new Stack<int>();
        Stack<int> stackLoopTime = new Stack<int>();
        void startSimulateCommand_Called(object sender, EventArgs e)
        {
            if (!forLoopValid)
            {
                forLoopValid = model.LedData.CheckForLoop();
            }
            if (forLoopValid)
            {
                timer.Enabled = true;
                timer.Start();
            }
            else
            {
                MessageBox.Show("For loop is invalid. Please re-config for loop");
            }
            commandHub.ReceiveCommand("StartSimulate");
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            timerCount--;
            ///tbTimer.Text = string.Format("{0:0}", timerCount);
            if (timerCount == 0)
            {
                Constants.StateType StateType = model.LedData.GetStateType(curStateShow);
                while (StateType != Constants.StateType.Data)
                {
                    if (StateType == Constants.StateType.StartFor)
                    {
                        /* Check if it's in stack already*/
                        if (stackStartFor.Contains(curStateShow) == false)
                        {
                            int loop_time = model.LedData.GetCommonValue(curStateShow);
                            /* Push index and loop time into stack */
                            stackStartFor.Push(curStateShow);
                            if (loop_time == 0)
                            {
                                MessageBox.Show("Loop time error");
                            }
                            else
                            {
                                stackLoopTime.Push(loop_time);
                            }
                        }
                        curStateShow++;
                    }
                    else if (StateType == Constants.StateType.Endfor)
                    {
                        /* Pop loop time, descrease and push to stack */
                        int temp_LoopTime = stackLoopTime.Pop();
                        if (temp_LoopTime == 0)
                        {
                            MessageBox.Show("Conflict");
                        }
                        temp_LoopTime--;
                        if (temp_LoopTime > 0)
                        {
                            /* Reset index */
                            curStateShow = stackStartFor.Peek();
                            stackLoopTime.Push(temp_LoopTime);
                        }
                        else
                        {
                            /* Increase index and remove start for from stack*/
                            curStateShow++;
                            stackStartFor.Pop();
                        }
                    }
                    if (curStateShow >= model.LedData.StateNumber)
                    {
                        curStateShow = 0;
                    }
                    StateType = model.LedData.GetStateType(curStateShow);
                }
                //cur_property = Common_pro.Get_Item(curStateShow);
                //Show_State(Demo, curStateShow);
                view.SimulateData = model.GetBrightState(curStateShow);
                timerCount = model.LedData.GetCommonValue(curStateShow);
                curStateShow++;
                if (curStateShow >= model.LedData.StateNumber)
                {
                    curStateShow = 0;
                }
            }
        }

        void pauseSimulateCommand_Called(object sender, EventArgs e)
        {
            timer.Stop();
            commandHub.ReceiveCommand("PauseSimulate");
        }

        void stopSimulateCommand_Called(object sender, EventArgs e)
        {
            timer.Stop();
            timer.Enabled = false;
            //Reset values
            forLoopValid = false;
            curStateShow = 0;
            timerCount = 1;
            stackLoopTime.Clear();
            stackStartFor.Clear();
            view.SimulateData = null;
            commandHub.ReceiveCommand("StopSimulate");
        }

        void mouseWheelCommand_Called(object sender, MouseEventArgs e)
        {
            LedNodeView curNode = (LedNodeView)sender;
            Constants.StateType curType = curNode.Type;
            int curValue = 0;
            int step = 0; ;
            switch (curType)
            {
                case Constants.StateType.Data:
                    step = Constants.BRIGHT_STEP;
                    curValue = model.GetBright(viewIndex);
                    break;
                case Constants.StateType.StartFor:
                    step = Constants.FORLOOP_STEP;
                    curValue = model.GetStateInfo(viewIndex.stateIndex);
                    break;
            }
            if (e.Delta > 0)
            {
                curValue += step;
            }
            else if (e.Delta < 0)
            {
                curValue -= step;
            }
            switch (curType)
            {
                case Constants.StateType.Data:
                    int updateBright = model.SetBright(viewIndex, curValue);
                    if (updateBright > -1)
                    {
                        view.Bright = updateBright;
                    }
                    break;
                case Constants.StateType.StartFor:
                    int updateStateInfo = model.SetStateInfo(viewIndex.stateIndex, curValue);
                    if (updateStateInfo > -1)
                    {
                        view.StateCommonInfo = updateStateInfo;
                    }
                    break;
            }
        }

        void mouseDoubleClickCommand_Called(object sender, MouseEventArgs e)
        {
            LedNodeView curNode = (LedNodeView)sender;
            int curValue = model.GetBright(viewIndex);
            int updateBright;
            if (curValue != Constants.MAX_BRIGHT)
            {
                updateBright = model.SetBright(viewIndex, Constants.MAX_BRIGHT);
            }
            else
            {
                updateBright = model.SetBright(viewIndex, Constants.DEFAULT_BRIGHT);
            }
            if (updateBright >= 0)
            {
                view.Bright = updateBright;
            }
        }

        void clearAllEffectCommand_Called(object sender, EventArgs e)
        {
            List<LedNodeView> selectedNode = (List<LedNodeView>)sender;
            foreach (LedNodeView c in selectedNode)
            {
                LedNodeIndex curIndex = new LedNodeIndex(c.StateIndex, c.LedIndex);
                int updateBright = model.SetBright(curIndex, 0);
                if (updateBright != -1)
                {
                    c.Value = updateBright;
                }
            }
        }
        void maxBrightEffectCommand_Called(object sender, EventArgs e)
        {
            List<LedNodeView> selectedNode = (List<LedNodeView>)sender;
            foreach (LedNodeView c in selectedNode)
            {
                LedNodeIndex curIndex = new LedNodeIndex(c.StateIndex, c.LedIndex);
                int updateBright = model.SetBright(curIndex, Constants.MAX_BRIGHT);
                if (updateBright != -1)
                {
                    c.Value = updateBright;
                }
            }
        }
        void revertEffectCommand_Called(object sender, EventArgs e)
        {
            List<LedNodeView> selectedNode = (List<LedNodeView>)sender;
            foreach (LedNodeView c in selectedNode)
            {
                LedNodeIndex curIndex = new LedNodeIndex(c.StateIndex, c.LedIndex);
                int updateBright = model.SetBright(curIndex, Constants.MAX_BRIGHT - c.Value);
                if (updateBright != -1)
                {
                    c.Value = updateBright;
                }
            }
        }
        void blindEffectCommand_Called(object sender, EventArgs e)
        {
            List<LedNodeView> selectedNode = (List<LedNodeView>)sender;
            int brightValue = 0;
            foreach (LedNodeView c in selectedNode)
            {
                LedNodeIndex curIndex = new LedNodeIndex(c.StateIndex, c.LedIndex);
                int updateBright = model.SetBright(curIndex, Constants.MAX_BRIGHT - brightValue);
                if (updateBright != -1)
                {
                    c.Value = updateBright;
                    brightValue = updateBright;
                }
            }
        }

        void fireBallEffectCommand_Called(object sender, EventArgs e)
        {
            List<LedNodeView> selectedNode = (List<LedNodeView>)sender;
            //Find max and min index of selected node
            LedNodeIndex maxIndex = new LedNodeIndex(-1, -1);
            LedNodeIndex minIndex = new LedNodeIndex(selectedNode.Count, selectedNode.Count);
            foreach (LedNodeView c in selectedNode)
            {
                LedNodeIndex curIndex = new LedNodeIndex(c.StateIndex, c.LedIndex);
                if (curIndex.stateIndex > maxIndex.stateIndex)
                {
                    maxIndex.stateIndex = curIndex.stateIndex;
                }
                if (curIndex.ledIndex > maxIndex.ledIndex)
                {
                    maxIndex.ledIndex = curIndex.ledIndex;
                }
                if (curIndex.stateIndex < minIndex.stateIndex)
                {
                    minIndex.stateIndex = curIndex.stateIndex;
                }
                if (curIndex.ledIndex < minIndex.ledIndex)
                {
                    minIndex.ledIndex = curIndex.ledIndex;
                }
            }
            //Set bright for selected nodes
            int brightStep = (Constants.MAX_BRIGHT - Constants.DEFAULT_BRIGHT) / (maxIndex.ledIndex - minIndex.ledIndex);
            for (int stateIndex = minIndex.stateIndex; stateIndex <= maxIndex.stateIndex; stateIndex++)
            {
                int curBright = Constants.DEFAULT_BRIGHT;
                for (int ledIndex = minIndex.ledIndex; ledIndex <= maxIndex.ledIndex; ledIndex++)
                {
                    LedNodeIndex curIndex = new LedNodeIndex(stateIndex, ledIndex);
                    foreach (LedNodeView c in selectedNode)
                    {
                        if ((c.LedIndex == ledIndex) && (c.StateIndex == stateIndex))
                        {
                            int updateBright = model.SetBright(curIndex, curBright);
                            if (updateBright != -1)
                            {
                                c.Value = curBright;
                                curBright += brightStep;
                            }
                        }
                    }
                }
            }
        }
        #endregion

        private void model_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            //PropertyChangedExtendedEventArgs<int> eventArgs;
            //switch (e.PropertyName)
            //{
            //    case "LedData":
            //        view.LedData = model.LedData;
            //        curCondition.Remove("DataNotChange");
            //        AddOnly(curCondition, "DataChange");
            //        break;
            //    case "CurIndex":
            //        view.CurIndex = model.CurIndex;
            //        commandHub.ReceiveCommand("SelectNode");
            //        //if (model.)
            //        break;
            //    case "Bright":
            //        eventArgs = (PropertyChangedExtendedEventArgs<int>)e;
            //        view.Bright = eventArgs.NewValue;
            //        break;
            //    case "BrightIndex":
            //        //PropertyChangedExtendedEventArgs<ArrayList>  eventArgsList = (PropertyChangedExtendedEventArgs<ArrayList>)e;
            //        //ArrayList temp = eventArgsList.NewValue;

            //        break;
            //    case "StateCommonValue":
            //        eventArgs = (PropertyChangedExtendedEventArgs<int>)e;
            //        view.StateCommonInfo = eventArgs.NewValue;
            //        break;
            //}
        }

        private void view_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            PropertyChangedExtendedEventArgs<int> eventArgs;
            switch (e.PropertyName)
            {

                case "CurIndex":
                    ViewIndex = view.CurIndex;
                    commandHub.ReceiveCommand("SelectNode");
                    break;
                case "Bright":
                    eventArgs = (PropertyChangedExtendedEventArgs<int>)e;
                    int updateBright = model.SetBright(viewIndex,eventArgs.NewValue);
                    if (updateBright >= 0)
                    {
                        view.Bright = updateBright;
                    }
                    break;
                case "StateCommonValue":
                    eventArgs = (PropertyChangedExtendedEventArgs<int>)e;
                    int updateStateInfo=model.SetStateInfo(viewIndex.stateIndex, eventArgs.NewValue);
                    if (updateStateInfo > -1)
                    {
                        view.StateCommonInfo = updateStateInfo;
                    }
                    break;
                case "NodeSelectedChange":
                    commandHub.ReceiveCommand("NodeSelectedChange");
                    break;
            }
        }
    }
}
