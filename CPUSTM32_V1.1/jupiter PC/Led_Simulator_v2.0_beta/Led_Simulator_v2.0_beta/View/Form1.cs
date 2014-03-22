using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Led_Simulator_v2._0_beta
{
    public partial class Form1 : Form, IView
    {
        public Form1()
        {
            InitializeComponent();
        }

        #region IView Members
        public event EventHandler FileNewCommand;
        public event EventHandler FileOpenCommand;
        public event EventHandler FileSaveCommand;
        public event EventHandler FileCloseCommand;
        public event EventHandler ExitCommand;

        public event EventHandler UndoCommand;
        public event EventHandler RedoCommand;

        public event EventHandler AddStateAboveCommand;
        public event EventHandler AddStateBelowCommand;
        public event EventHandler RemoveStateCommand;
        public event EventHandler AddStartForCommand;
        public event EventHandler AddEndForCommand;

        public event EventHandler AddLedLeftCommand;
        public event EventHandler AddLedRightCommand;
        public event EventHandler RemoveLedCommand;

        public event EventHandler StartSimulateCommand;
        public event EventHandler PauseSimulateCommand;
        public event EventHandler StopSimulateCommand;

        public event EventHandler ClearAllEffectCommand;
        public event EventHandler MaxBrightEffectCommand;
        public event EventHandler RevertEffectCommand;
        public event EventHandler BlindEffectCommand;
        public event EventHandler FireBallEffectCommand;

        public event MouseEventHandler LedNodeMouseWheelCommand;
        public event MouseEventHandler LedNodeMouseDoubleClickCommand;

        public DataLedArrayNode LedData
        {
            set 
            {
                ShowLedData(value);
            }
        }


        #endregion

        #region INotifyPropertyChanged Members

        public event PropertyChangedEventHandler PropertyChanged;

        #endregion
        private void NotifyChange(string propertyName)
        {
            if (null != PropertyChanged)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }

        private void NotifyChange<T>(string propertyName, T value)
        {
            if (null != PropertyChanged)
                PropertyChanged(this, new PropertyChangedExtendedEventArgs<T>(propertyName, value));
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            LedPanelInit();
            TranferInit();
        }

        private void mnuAddStateAbove_Click(object sender, EventArgs e)
        {
            //Inform Presenter that AddStateAbove command is called
            if (AddStateAboveCommand != null)
            {
                AddStateAboveCommand(this, e);
            }
        }

        private void mnuAddStateBelow_Click(object sender, EventArgs e)
        {
            //Inform Presenter that AddStateBelow command is called
            if (AddStateBelowCommand != null)
            {
                AddStateBelowCommand(this, e);
            }
        }

        private void mnuAddStartFor_Click(object sender, EventArgs e)
        {
            //Inform Presenter that AddStartFor command is called
            if (AddStartForCommand != null)
            {
                AddStartForCommand(this, e);
            }
        }

        private void mnuAddEndFor_Click(object sender, EventArgs e)
        {
            //Inform Presenter that AddEndFor command is called
            if (AddEndForCommand != null)
            {
                AddEndForCommand(this, e);
            }
        }

        private void mnuRemoveState_Click(object sender, EventArgs e)
        {
            //Inform Presenter that RemoveState command is called
            if (RemoveStateCommand != null)
            {
                RemoveStateCommand(this, e);
            }
        }

        private void mnuAddLedLeft_Click(object sender, EventArgs e)
        {
            //Inform Presenter that AddLedLeft command is called
            if (AddLedLeftCommand != null)
            {
                AddLedLeftCommand(this, e);
            }
        }

        private void mnuAddLedRight_Click(object sender, EventArgs e)
        {
            //Inform Presenter that AddLedRight command is called
            if (AddLedRightCommand != null)
            {
                AddLedRightCommand(this, e);
            }
        }

        private void mnuRemoveLed_Click(object sender, EventArgs e)
        {
            //Inform Presenter that RemoveLed command is called
            if (RemoveLedCommand != null)
            {
                RemoveLedCommand(this, e);
            }
        }

        private void mnuStartSimulate_Click(object sender, EventArgs e)
        {
            //Inform Presenter that StartSimulate command is called
            if (StartSimulateCommand != null)
            {
                StartSimulateCommand(this, e);
            }
        }

        private void mnuPauseSimulate_Click(object sender, EventArgs e)
        {
            //Inform Presenter that PauseSimulate command is called
            if (PauseSimulateCommand != null)
            {
                PauseSimulateCommand(this, e);
            }
        }

        private void mnuStopSimulate_Click(object sender, EventArgs e)
        {
            //Inform Presenter that StopSimulate command is called
            if (StopSimulateCommand != null)
            {
                StopSimulateCommand(this, e);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            TimeDurationImplement timeDuration = new TimeDurationImplement();
            timeDuration.Show();
        }

        private void tbGlobalInfo_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                ChangeNodeValue();
            }
        }

        private void tbValue_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                ChangeNodeValue();
            }
        }

        private void btnSetAlarm_Click(object sender, EventArgs e)
        {
            TimeSpan subTime;
            if (dtpOff.Value < dtpOn.Value)
            {
                MessageBox.Show("Thời gian Bật/Tắt không đúng!!!");
                return;
            }
            subTime = (TimeSpan)(dtpOff.Value - dtpOn.Value);

            gbVar.alarm_data.ontime = (Int16)(subTime.Hours * 60 + subTime.Minutes);
            gbVar.alarm_data.H_On = (byte)dtpOn.Value.Hour;
            gbVar.alarm_data.M_On = (byte)dtpOn.Value.Minute;
            gbVar.alarm_data.AlarmSelected = true;
        }

        private void rbtLedInfo_CheckedChanged(object sender, EventArgs e)
        {
            gbVar.TransferType = (int)Constants.DataType.SetInfoLed;
        }

        private void rbtEffect_CheckedChanged(object sender, EventArgs e)
        {
            gbVar.TransferType = (int)Constants.DataType.DataEffect;
        }

        private void rbtSettime_CheckedChanged(object sender, EventArgs e)
        {
            gbVar.TransferType = (int)Constants.DataType.SetInfoTime;
        }

        private void rbtAlarm_CheckedChanged(object sender, EventArgs e)
        {
            gbVar.TransferType = (int)Constants.DataType.SetInfoAlarm;
        }

        private void btnSetTime_Click(object sender, EventArgs e)
        {
            gbVar.time_data.Cur_H = (byte)dtpOn.Value.Hour;
            gbVar.time_data.Cur_Mi = (byte)dtpOn.Value.Minute;
            gbVar.time_data.Cur_D = (byte)dtpOn.Value.Day;
            gbVar.time_data.Cur_Mo = (byte)dtpOn.Value.Month;
            gbVar.time_data.Cur_Y = (byte)dtpOn.Value.Year;
            gbVar.time_data.TimeSelected = true;
        }

        TextBox tbx = new TextBox();
        private void btnSetAlarm_MouseEnter(object sender, EventArgs e)
        {
            tbx.Text = "Đặt thời gian Bật/Tắt!!!";
            tbx.Visible = true;
            tbx.Location = new System.Drawing.Point(482, 520);
            tbx.Size = new System.Drawing.Size(120, 20);
            this.Controls.Add(tbx);
        }

        private void btnSetAlarm_MouseLeave(object sender, EventArgs e)
        {
            this.Controls.Remove(tbx);
        }
    }
}
