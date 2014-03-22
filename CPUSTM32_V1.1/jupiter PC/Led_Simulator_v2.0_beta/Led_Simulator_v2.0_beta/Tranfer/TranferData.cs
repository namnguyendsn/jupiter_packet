using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Windows.Forms;

namespace Led_Simulator_v2._0_beta
{
    public partial class Form1 : Form, IView
    {
        void TranferInit()
        {
            string[] availablePort = SerialPort.GetPortNames();
            cbComPort.DataSource = availablePort;
        }

        public event SerialDataReceivedEventHandler SerialPort_DataReceived;
        private void serialPort_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            if (SerialPort_DataReceived != null)
            {
                SerialPort_DataReceived(sender, e);
            }
        }
        void UpdateComStatus(bool Open)
        {
            if (Open == true)
            {
                lbCOMBaudrate.Text = "Baudrate    " + serialPort.BaudRate.ToString();
                lbCOMDataBit.Text = "Data bits   " + serialPort.DataBits.ToString();
                lbCOMParity.Text = "Parity      " + serialPort.Parity.ToString();
                lbCOMStopBit.Text = "Stop bits   " + serialPort.StopBits.ToString();
                lbCOMStatus.Text = "Status      " + "Opened";
            }
            else
            {
                lbCOMBaudrate.Text = "Baudrate    ";
                lbCOMDataBit.Text = "Data bits   ";
                lbCOMParity.Text = "Parity      ";
                lbCOMStopBit.Text = "Stop bits   ";
                lbCOMStatus.Text = "Status      " + "Closed";
            }
        }

        private void btnComConnect_Click(object sender, EventArgs e)
        {
            string portName = cbComPort.SelectedItem.ToString();
            string[] availablePort= SerialPort.GetPortNames();
            if (!availablePort.Contains(portName))
            {
                MessageBox.Show("Selected COM port is not available. Please select another port");
                cbComPort.DataSource = availablePort;
            }
            else
            {
                serialPort.BaudRate = 115200;
                serialPort.DataBits = 8;
                serialPort.Parity = 0;
                serialPort.StopBits = (StopBits)1;
                try {
                    serialPort.PortName = portName;
                }
                catch(SystemException){}

                if (serialPort.IsOpen == true)
                {
                    btnComConnect.Text = "Open Port!";
                    serialPort.Close();
                    UpdateComStatus(false);
                }
                else
                {
                    btnComConnect.Text = "Close Port!";
                    serialPort.Open();
                    UpdateComStatus(true);
                }

            }
        }

        private void btnSendData_Click(object sender, EventArgs e)
        {
            if (sendData != null)
            {
                sendData(serialPort);
            }
        }

        private SendDataDelegate sendData;
        public SendDataDelegate SendData
        {
            set
            {
                sendData = value;
            }
        }
    }
}
