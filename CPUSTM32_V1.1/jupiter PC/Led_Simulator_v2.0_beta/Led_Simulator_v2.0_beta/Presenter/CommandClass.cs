using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections;

namespace Led_Simulator_v2._0_beta
{
    public class Command
    {
        public string commandName;
        public CommandSet commandset;
        private Boolean enable;
        public Boolean Enable
        {
            get { return enable; }
            set
            {
                //if (enable != value)
                {
                    enable = value;
                    Invalidate();
                }
            }
        }

        private Boolean enableBackup;
        public Keys commandKey;
        public List<Control> commandControl;
        public List<ToolStripItem> commandItem;
        //public event EventHandler commandHandler;
        public string[] enableConditionList;
        public string[] disableConditionList;

        public void ReceiveCommand(string name, List<string> conditions)
        {
            if (name == "Restore")
            {
                Enable = enableBackup;
                return;
            }
            if (name == "Backup")
            {
                enableBackup = Enable;
                Enable = false;
                return;
            }
            foreach (string condition in conditions)
            {
                if (disableConditionList.Contains(condition))
                {
                    Enable = false;
                    return;
                }
                if (enableConditionList.Contains(condition))
                {
                    Enable = true;
                }
            }
        }

        private void Invalidate()
        {
            if (commandControl != null)
            {
                foreach (Control c in commandControl)
                {
                    c.Enabled = Enable;
                }
            }
            if (commandItem != null)
            {
                foreach (ToolStripItem item in commandItem)
                {
                    item.Enabled = Enable;
                }
            }
        }

        public void SendCommand()
        {
            commandset.SendCommand(commandName);
        }
    }

    public class CommandSet
    {
        public string commandSetName;
        public Mediator mediator;
        private Hashtable commands;
        public Boolean Enable;
        public string[] enableContextList;
        public string[] disableContextList;

        public CommandSet(string name)
        {
            commandSetName = name;
            commands = new Hashtable();
        }
        public void AddCommand(Command command)
        {
            if (commands[command.commandName] == null)
            {
                commands[command.commandName] = command;
                command.commandset = this;
            }
        }
        public void SendCommand(string command)
        {
            mediator.ReceiveCommand(command);
        }

        public void ReceiveCommand(List<string> contexts, List<string> condition)
        {
            if (Enable)
            {
                foreach (string context in contexts)
                {
                    if (disableContextList.Contains(context))
                    {
                        Enable = false;
                        foreach (DictionaryEntry entry in commands)
                        {
                            Command cmd = (Command)entry.Value;
                            cmd.ReceiveCommand("Backup", condition);
                        }
                        return;
                    }
                }
                foreach (DictionaryEntry entry in commands)
                {
                    Command cmd = (Command)entry.Value;
                    cmd.ReceiveCommand("None", condition);
                }
            }
            else
            {
                foreach (string context in contexts)
                {
                    if (enableContextList.Contains(context))
                    {
                        Enable = true;
                        foreach (DictionaryEntry entry in commands)
                        {
                            Command cmd = (Command)entry.Value;
                            cmd.ReceiveCommand("Restore", condition);
                        }
                        return;
                    }
                }
            }
        }
    }

    public delegate List<string> UpdateCommmandDelegate(string commandName);
    public interface ICommand
    {

        UpdateCommmandDelegate UpdateCondition { set; }
        UpdateCommmandDelegate UpdateContext { set; }
    }

    public class Mediator : ICommand
    {
        private Hashtable allCommandSet;

        private UpdateCommmandDelegate updateCondition;
        private UpdateCommmandDelegate updateContext;
        #region ICommand
        public UpdateCommmandDelegate UpdateCondition
        {
            set
            {
                updateCondition = value;
            }
        }
        public UpdateCommmandDelegate UpdateContext
        {
            set
            {
                updateContext = value;
            }
        }
        #endregion
        public Mediator()
        {
            allCommandSet = new Hashtable();
        }
        public void AddCommandSet(CommandSet commandset)
        {
            if (allCommandSet[commandset.commandSetName] == null)
            {
                allCommandSet[commandset.commandSetName] = commandset;
                commandset.mediator = this;
            }
        }

        public void ReceiveCommand(string commandName)
        {
            //Add context in command
            List<string> conditions;
            List<string> contexts;
            conditions = updateCondition(commandName);

            contexts = updateContext(commandName);

            //Send command to command sets
            foreach (DictionaryEntry entry in allCommandSet)
            {
                CommandSet cmdSet = (CommandSet)entry.Value;
                cmdSet.ReceiveCommand(contexts, conditions);
            }
        }
    }
}
