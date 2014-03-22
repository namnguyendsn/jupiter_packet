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
        private Hashtable allCommand = new Hashtable();
        void InitCommandHub()
        {
            commandHub = new Mediator();
            #region Add Edit Command Set
            CommandSet editCommand = new CommandSet("Edit");
            editCommand.AddCommand((Command)allCommand["FileNew"]);
            editCommand.AddCommand((Command)allCommand["FileOpen"]);
            editCommand.AddCommand((Command)allCommand["FileSave"]);
            editCommand.AddCommand((Command)allCommand["FileClose"]);
            editCommand.AddCommand((Command)allCommand["Undo"]);
            editCommand.AddCommand((Command)allCommand["Redo"]);
            editCommand.AddCommand((Command)allCommand["EditNode"]);
            editCommand.AddCommand((Command)allCommand["AddStateAbove"]);
            editCommand.AddCommand((Command)allCommand["AddStateBelow"]);
            editCommand.AddCommand((Command)allCommand["RemoveState"]);
            editCommand.AddCommand((Command)allCommand["AddStartFor"]);
            editCommand.AddCommand((Command)allCommand["AddEndFor"]);
            editCommand.AddCommand((Command)allCommand["AddLedLeft"]);
            editCommand.AddCommand((Command)allCommand["AddLedRight"]);
            editCommand.AddCommand((Command)allCommand["RemoveLed"]);
            editCommand.AddCommand((Command)allCommand["ClearAllEffect"]);
            editCommand.AddCommand((Command)allCommand["MaxBrightEffect"]);
            editCommand.AddCommand((Command)allCommand["RevertBrightEffect"]);
            editCommand.AddCommand((Command)allCommand["BlindBrightEffect"]);
            editCommand.AddCommand((Command)allCommand["FireBallEffect"]);

            editCommand.enableContextList = new string[] { "SimulateStop", "SendDataDone "};
            editCommand.disableContextList = new string[] { "SimulateRun", "SendDataStart" };
            editCommand.Enable = true;
            commandHub.AddCommandSet(editCommand);
            #endregion

            #region Add Simulate Command Sets
            CommandSet simulateCommand = new CommandSet("Simulate");
            simulateCommand.AddCommand((Command)allCommand["StartSimulate"]);
            simulateCommand.AddCommand((Command)allCommand["PauseSimulate"]);
            simulateCommand.AddCommand((Command)allCommand["StopSimulate"]);

            simulateCommand.enableContextList = new string[] { "*" };
            simulateCommand.disableContextList = new string[] { "None" };
            simulateCommand.Enable = true;
            commandHub.AddCommandSet(simulateCommand);
            #endregion

            #region Update Condition and Context functions
            commandHub.UpdateCondition = new UpdateCommmandDelegate(UpdateCondition);
            commandHub.UpdateContext = new UpdateCommmandDelegate(UpdateContext);
            #endregion

        }
        Command GetCommand(string commandName)
        {
            Command command = (Command)allCommand[commandName];
            return command;
        }
        void CollectAllCommand()
        {
            Command curCommand;
            #region FileNew Command
            curCommand = new Command();
            curCommand.commandName = "FileNew";
            curCommand.Enable = true;
            curCommand.enableConditionList = new string[] {"*",};
            curCommand.disableConditionList = new string[] { "None", };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region FileOpen Command
            curCommand = new Command();
            curCommand.Enable = true;
            curCommand.commandName = "FileOpen";
            curCommand.enableConditionList = new string[] { "*", };
            curCommand.disableConditionList = new string[] { "None", };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region FileSave Command
            curCommand = new Command();
            curCommand.Enable = true;
            curCommand.commandName = "FileSave";
            curCommand.enableConditionList = new string[] { "DataChange", };
            curCommand.disableConditionList = new string[] { "DataNotChange", };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region FileClose Command
            curCommand = new Command();
            curCommand.Enable = true;
            curCommand.commandName = "FileClose";
            curCommand.enableConditionList = new string[] { "*", };
            curCommand.disableConditionList = new string[] { "None", };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region Undo Command
            curCommand = new Command();
            curCommand.Enable = true;
            curCommand.commandName = "Undo";
            curCommand.enableConditionList = new string[] { "UndoListNotEmpty", };
            curCommand.disableConditionList = new string[] { "UndoListEmpty", };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region Redo Command
            curCommand = new Command();
            curCommand.Enable = true;
            curCommand.commandName = "Redo";
            curCommand.enableConditionList = new string[] { "RedoListNotEmpty", };
            curCommand.disableConditionList = new string[] { "RedoListEmpty", };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region EditNode Command
            curCommand = new Command();
            curCommand.commandName = "EditNode";
            curCommand.Enable = true;
            curCommand.enableConditionList = new string[] { "*", };
            curCommand.disableConditionList = new string[] { "None", };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region AddStateAbove Command
            curCommand = new Command();
            curCommand.Enable = true;
            curCommand.commandName = "AddStateAbove";
            curCommand.enableConditionList = new string[] { "ValidStateSelected", };
            curCommand.disableConditionList = new string[] { "InvalidStateSelected", };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region AddStateBelow Command
            curCommand = new Command();
            curCommand.Enable = true;
            curCommand.commandName = "AddStateBelow";
            curCommand.enableConditionList = new string[] { "ValidStateSelected", };
            curCommand.disableConditionList = new string[] { "InvalidStateSelected", };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region RemoveState Command
            curCommand = new Command();
            curCommand.Enable = true;
            curCommand.commandName = "RemoveState";
            curCommand.enableConditionList = new string[] { "ValidStateSelected", "MoreThanOneState"};
            curCommand.disableConditionList = new string[] { "InvalidStateSelected", "DataEmpty" ,"OneState"};
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region AddStartFor Command
            curCommand = new Command();
            curCommand.Enable = true;
            curCommand.commandName = "AddStartFor";
            curCommand.enableConditionList = new string[] { "ValidStateSelected", };
            curCommand.disableConditionList = new string[] { "InvalidStateSelected", };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region AddEndFor Command
            curCommand = new Command();
            curCommand.Enable = true;
            curCommand.commandName = "AddEndFor";
            curCommand.enableConditionList = new string[] { "ValidStateSelected", };
            curCommand.disableConditionList = new string[] { "InvalidStateSelected", };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region AddLedLeft Command
            curCommand = new Command();
            curCommand.Enable = true;
            curCommand.commandName = "AddLedLeft";
            curCommand.enableConditionList = new string[] { "ValidLedSelected", };
            curCommand.disableConditionList = new string[] { "InvalidLedSelected", };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region AddLedRight Command
            curCommand = new Command();
            curCommand.Enable = true;
            curCommand.commandName = "AddLedRight";
            curCommand.enableConditionList = new string[] { "ValidLedSelected", };
            curCommand.disableConditionList = new string[] { "InvalidLedSelected", };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region RemoveLed Command
            curCommand = new Command();
            curCommand.Enable = true;
            curCommand.commandName = "RemoveLed";
            curCommand.enableConditionList = new string[] { "ValidLedSelected","MoreThanOneLed" };
            curCommand.disableConditionList = new string[] { "InvalidLedSelected","DataEmpty","OneLed" };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region ClearAllEffect Command
            curCommand = new Command();
            curCommand.Enable = false;
            curCommand.commandName = "ClearAllEffect";
            curCommand.enableConditionList = new string[] { "NodeSelected", };
            curCommand.disableConditionList = new string[] { "NoNodeSelected", "DataEmpty" };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region MaxBrightEffect Command
            curCommand = new Command();
            curCommand.Enable = false;
            curCommand.commandName = "MaxBrightEffect";
            curCommand.enableConditionList = new string[] { "NodeSelected", };
            curCommand.disableConditionList = new string[] { "NoNodeSelected", "DataEmpty" };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region RevertBrightEffect Command
            curCommand = new Command();
            curCommand.Enable = false;
            curCommand.commandName = "RevertBrightEffect";
            curCommand.enableConditionList = new string[] { "NodeSelected", };
            curCommand.disableConditionList = new string[] { "NoNodeSelected", "DataEmpty" };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region BlindBrightEffect Command
            curCommand = new Command();
            curCommand.Enable = false;
            curCommand.commandName = "BlindBrightEffect";
            curCommand.enableConditionList = new string[] { "NodeSelected", };
            curCommand.disableConditionList = new string[] { "NoNodeSelected", "DataEmpty" };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region FireBallEffect Command
            curCommand = new Command();
            curCommand.Enable = false;
            curCommand.commandName = "FireBallEffect";
            curCommand.enableConditionList = new string[] { "NodeSelected", };
            curCommand.disableConditionList = new string[] { "NoNodeSelected", "DataEmpty" };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region StartSimulate Command
            curCommand = new Command();
            curCommand.Enable = true;
            curCommand.commandName = "StartSimulate";
            curCommand.enableConditionList = new string[] { "NotSimulating", "PauseSimulate", "DataNotEmpty" };
            curCommand.disableConditionList = new string[] { "Simulating", "DataEmpty" };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region PauseSimulate Command
            curCommand = new Command();
            curCommand.Enable = false;
            curCommand.commandName = "PauseSimulate";
            curCommand.enableConditionList = new string[] { "Simulating", };
            curCommand.disableConditionList = new string[] { "NotSimulating", "PauseSimulate" };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region StopSimulate Command
            curCommand = new Command();
            curCommand.Enable = false;
            curCommand.commandName = "StopSimulate";
            curCommand.enableConditionList = new string[] { "Simulating", };
            curCommand.disableConditionList = new string[] { "NotSimulating", };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region ConnectSerial Command
            curCommand = new Command();
            curCommand.Enable = true;
            curCommand.commandName = "ConnectSerial";
            curCommand.enableConditionList = new string[] { "SerialPortSelected", };
            curCommand.disableConditionList = new string[] { "NoSerialPortSelected", };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion

            #region TranferData Command
            curCommand = new Command();
            curCommand.Enable = true;
            curCommand.commandName = "ConnectSerial";
            curCommand.enableConditionList = new string[] { "SerialPortValid", };
            curCommand.disableConditionList = new string[] { "SerialPortInvalid", };
            if (allCommand[curCommand.commandName] == null)
            {
                allCommand[curCommand.commandName] = curCommand;
            }
            #endregion
        }

        private void AddOnly<T>(List<T> list,T value)
    {
        if (!list.Contains(value))
        {
            list.Add(value);
        }
    }
        List<string> curCondition = new List<string>();
        public List<string> UpdateCondition(string commandName)
        {
            if ((model.LedData.StateNumber > 0)&&(model.LedData.LedNumber > 0))
            {
                if (model.LedData.StateNumber == 1)
                {
                    curCondition.Remove("MoreThanOneState");
                    AddOnly(curCondition, "OneState");
                }
                else
                {
                    curCondition.Remove("OneState");
                    AddOnly(curCondition, "MoreThanOneState");
                }
                if (model.LedData.LedNumber == 1)
                {
                    curCondition.Remove("MoreThanOneLed");
                    AddOnly(curCondition, "OneLed");
                }
                else
                {
                    curCondition.Remove("OneLed");
                    AddOnly(curCondition, "MoreThanOneLed");
                }
            }
            else
            {
                curCondition.Remove("DataNotEmpty");
                AddOnly(curCondition, "DataEmpty");
            }
            if (view.NodeSelected)
            {
                curCondition.Remove("NoNodeSelected");
                AddOnly(curCondition, "NodeSelected");
            }
            else
            {
                curCondition.Remove("NodeSelected");
                AddOnly(curCondition, "NoNodeSelected");
            }

            if (view.CurIndex.stateIndex == -1)
            {
                curCondition.Remove("ValidStateSelected");
                AddOnly(curCondition, "InvalidStateSelected");
            }
            else
            {
                curCondition.Remove("InvalidStateSelected");
                AddOnly(curCondition, "ValidStateSelected");
            }
            if (model.GetStateType(view.CurIndex.stateIndex) == Constants.StateType.Data)
            {
                curCondition.Remove("InvalidLedSelected");
                AddOnly(curCondition, "ValidLedSelected");
            }
            else
            {
                curCondition.Remove("ValidLedSelected");
                AddOnly(curCondition, "InvalidLedSelected");
            }
            switch (commandName)
            {
                case "FileNew":
                    break;
                case "FileOpen":
                    break;
                case "FileSave":
                    curCondition.Remove("DataChange");
                    AddOnly(curCondition, "DataNotChange");
                    break;
                case "FileClose":
                    break;
                case "Undo":
                    break;
                case "Redo":
                    break;
                case "AddStateAbove":
                    break;
                case "AddStateBelow":
                    break;
                case "RemoveState":
                    break;
                case "AddStartFor":
                    break;
                case "AddEndFor":
                    break;
                case "AddLedLeft":
                    break;
                case "AddLedRight":
                    break;
                case "StartSimulate":
                    curCondition.Remove("NotSimulating");
                    curCondition.Remove("PauseSimulate");
                    AddOnly(curCondition, "Simulating");
                    break;
                case "PauseSimulate":
                    curCondition.Remove("Simulating");
                    AddOnly(curCondition, "PauseSimulate");
                    break;
                case "StopSimulate":
                    curCondition.Remove("Simulating");
                    AddOnly(curCondition, "NotSimulating");
                    break;
            }
            return curCondition;
        }
        public List<string> UpdateContext(string commandName)
        {
            List<string> returnString = new List<string>();
            switch (commandName)
            {
                case "FileNew":
                case "FileOpen":
                case "FileSave":
                case "FileClose":
                case "Undo":
                case "Redo":
                case "AddStateAbove":
                case "AddStateBelow":
                case "RemoveState":
                case "AddStartFor":
                case "AddEndFor":
                case "AddLedLeft":
                case "AddLedRight":
                    returnString.Add("EditRun");
                    break;
                case "StartSimulate":
                    returnString.Remove("SimulateStop");
                    if (!returnString.Contains("SimulateRun"))
                    {
                        returnString.Add("SimulateRun");
                    }
                    break;
                case "PauseSimulate":
                    break;
                case "StopSimulate":
                    returnString.Remove("SimulateRun");
                    if (!returnString.Contains("SimulateStop"))
                    {
                        returnString.Add("SimulateStop");
                    }
                    break;
                case "StartSendData":
                    returnString.Remove("SendDataDone");
                    if (!returnString.Contains("SendDataStart"))
                    {
                        returnString.Add("SendDataStart");
                    }
                    break;
                case "SendDataDone":
                    returnString.Remove("SendDataStart");
                    if (!returnString.Contains("SendDataDone"))
                    {
                        returnString.Add("SendDataDone");
                    }
                    break;
            }
            return returnString;
        }
    }
}