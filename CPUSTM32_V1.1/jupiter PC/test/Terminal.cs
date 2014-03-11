/* 
 * Project:    SerialPort Terminal
 * Company:    Coad .NET, http://coad.net
 * Author:     Noah Coad, http://coad.net/noah
 * Created:    March 2005
 * 
 * Notes:      This was created to demonstrate how to use the SerialPort control for
 *             communicating with your PC's Serial RS-232 COM Port
 * 
 *             It is for educational purposes only and not sanctified for industrial use. :)
 *             Written to support the blog post article at: http://msmvps.com/blogs/coad/archive/2005/03/23/39466.aspx
 * 
 *             Search for "comport" to see how I'm using the SerialPort control.
 */

#region Namespace Inclusions
using System;
using System.Linq;
using System.Data;
using System.Text;
using System.Drawing;
using System.IO.Ports;
using System.Windows.Forms;
using System.ComponentModel;
using System.Collections.Generic;

using TestTransfer.Properties;
using System.Threading;
using System.IO;
#endregion

namespace SerialPortTerminal
{
  #region Public Enumerations
  public enum DataMode { Text, Hex }
  public enum LogMsgType { Incoming, Outgoing, Normal, Warning, Error };
  #endregion

  public partial class frmTerminal : Form
  {
    #region Local Variables

    // The main control for communicating through the RS-232 port
    private SerialPort comport = new SerialPort();

    // Various colors for logging info
    private Color[] LogMsgTypeColor = { Color.Blue, Color.Green, Color.Black, Color.Orange, Color.Red };

    // Temp holder for whether a key was pressed
    private bool KeyHandled = false;

		private Settings settings = Settings.Default;
    #endregion

    #region Constructor
    public frmTerminal()
    {
			// Load user settings
			settings.Reload();

      // Build the form
      InitializeComponent();

      // Restore the users settings
      InitializeControlValues();

      // Enable/disable controls based on the current state
      EnableControls();

      // When data is recieved through the port, call this method
      comport.DataReceived += new SerialDataReceivedEventHandler(port_DataReceived);
			comport.PinChanged += new SerialPinChangedEventHandler(comport_PinChanged);
    }

		void comport_PinChanged(object sender, SerialPinChangedEventArgs e)
		{
			// Show the state of the pins
			UpdatePinState();
		}

		private void UpdatePinState()
		{
			this.Invoke(new ThreadStart(() => {
				// Show the state of the pins
			}));
		}
    #endregion

    #region Local Methods
    
    /// <summary> Save the user's settings. </summary>
    private void SaveSettings()
    {
			settings.BaudRate = 115200;
			settings.DataBits = 8;
			settings.DataMode = CurrentDataMode;
			settings.Parity = 0;
			settings.StopBits = (StopBits)1;
			settings.PortName = cmbPortName.Text;

			settings.Save();
    }

    /// <summary> Populate the form's controls with default settings. </summary>
    private void InitializeControlValues()
    {
			CurrentDataMode = settings.DataMode;

			RefreshComPortList();

			// If it is still avalible, select the last com port used
			if (cmbPortName.Items.Contains(settings.PortName)) cmbPortName.Text = settings.PortName;
      else if (cmbPortName.Items.Count > 0) cmbPortName.SelectedIndex = cmbPortName.Items.Count - 1;
      else
      {
        MessageBox.Show(this, "There are no COM Ports detected on this computer.\nPlease install a COM Port and restart this app.", "No COM Ports Installed", MessageBoxButtons.OK, MessageBoxIcon.Error);
        this.Close();
      }
    }

    /// <summary> Enable/disable controls based on the app's current state. </summary>
    private void EnableControls()
    {
      // Enable/disable controls based on whether the port is open or not
      gbPortSettings.Enabled = !comport.IsOpen;
      txtSendData.Enabled = btnSend.Enabled = comport.IsOpen;
			//chkDTR.Enabled = chkRTS.Enabled = comport.IsOpen;

      if (comport.IsOpen) btnOpenPort.Text = "&Close Port";
      else btnOpenPort.Text = "&Open Port";
    }

    /// <summary> Send the user's data currently entered in the 'send' box.</summary>
    private void SendData()
    {
        int framenum;
        int frame_sent;
        int frame_remain;
        int frame_len;
        int offset = 0;
        int data_remain;
        byte[] frame_packed = new byte[36];
        byte[] effect_packed = new byte[1000];
      if (CurrentDataMode == DataMode.Text)
      {
        // Send the user's text straight out the port
        comport.Write(txtSendData.Text);

        // Show in the terminal window the user's text
        Log(LogMsgType.Outgoing, txtSendData.Text + "\n");
      }
      else
      {
        try
        {
          // Convert the user's string of hex digits (ex: B4 CA E2) to a byte array
          byte[] data_ = HexStringToByteArray(txtSendData.Text);

          effect_packed[0] = 0xE0;
          effect_packed[1] = (byte)(data_.Length << 8);
          effect_packed[2] = (byte)(data_.Length);
          effect_packed[3] = 0xD5;
          Array.Copy(data_, 0, effect_packed, 4, data_.Length);
          effect_packed[data_.Length + 4] = 0xE1;

          byte[] data = new byte[data_.Length + 5];
          Array.Copy(effect_packed, 0, data, 0, data_.Length + 5);

          // Send the binary data out the port
          framenum = data.Length / 32;
          if (data.Length % 32 != 0)
              framenum++;
          frame_sent = 0;
          for (int i = 0; i < framenum; i++)
          {
              frame_remain = framenum - frame_sent;
              data_remain = data.Length - 32 * frame_sent;
              if (data_remain > 32)
                  frame_len = 32;
              else if (data_remain == 32)
                  frame_len = data.Length - 32 * frame_sent - 1;
              else
                  frame_len = data.Length - 32 * frame_sent;

              Array.Clear(frame_packed, 0, frame_packed.Length);
              frame_packed[0] = 0xD0;// SOF
              frame_packed[1] = (byte)(frame_len);// length
              frame_packed[2] = 0x77;// crc

              Array.Copy(data, offset, frame_packed, 3, frame_len);
              frame_packed[frame_len + 3] = 0xD1;// EOF

              comport.Write(frame_packed, 0, frame_len + 4);
              Thread.Sleep(100);
              ++frame_sent;
              offset += 32;
              // Show the hex digits on in the terminal window
              Log(LogMsgType.Outgoing, ByteArrayToHexString(frame_packed) + "\n");
          }
        }
        catch (FormatException)
        {
          // Inform the user if the hex string was not properly formatted
          Log(LogMsgType.Error, "Not properly formatted hex string: " + txtSendData.Text + "\n");
        }
      }
      txtSendData.SelectAll();
    }

    /// <summary> Log data to the terminal window. </summary>
    /// <param name="msgtype"> The type of message to be written. </param>
    /// <param name="msg"> The string containing the message to be shown. </param>
    private void Log(LogMsgType msgtype, string msg)
    {
      rtfTerminal.Invoke(new EventHandler(delegate
      {
        rtfTerminal.SelectedText = string.Empty;
        rtfTerminal.SelectionFont = new Font(rtfTerminal.SelectionFont, FontStyle.Bold);
        rtfTerminal.SelectionColor = LogMsgTypeColor[(int)msgtype];
        rtfTerminal.AppendText(msg);
        rtfTerminal.ScrollToCaret();
      }));
    }

    /// <summary> Convert a string of hex digits (ex: E4 CA B2) to a byte array. </summary>
    /// <param name="s"> The string containing the hex digits (with or without spaces). </param>
    /// <returns> Returns an array of bytes. </returns>
    private byte[] HexStringToByteArray(string s)
    {
      s = s.Replace(" ", "");
      byte[] buffer = new byte[s.Length / 2];
      for (int i = 0; i < s.Length; i += 2)
        buffer[i / 2] = (byte)Convert.ToByte(s.Substring(i, 2), 16);
      return buffer;
    }

    /// <summary> Converts an array of bytes into a formatted string of hex digits (ex: E4 CA B2)</summary>
    /// <param name="data"> The array of bytes to be translated into a string of hex digits. </param>
    /// <returns> Returns a well formatted string of hex digits with spacing. </returns>
    private string ByteArrayToHexString(byte[] data)
    {
      StringBuilder sb = new StringBuilder(data.Length * 3);
      foreach (byte b in data)
        sb.Append(Convert.ToString(b, 16).PadLeft(2, '0').PadRight(3, ' '));
      return sb.ToString().ToUpper();
    }
    #endregion

    #region Local Properties
    private DataMode CurrentDataMode
    {
      get
      {
        return DataMode.Hex;
      }
      set
      {

      }
    }
    #endregion

    #region Event Handlers
    private void lnkAbout_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
    {
      // Show the user the about dialog
      (new frmAbout()).ShowDialog(this);
    }
    
    private void frmTerminal_Shown(object sender, EventArgs e)
    {
      Log(LogMsgType.Normal, String.Format("Application Started at {0}\n", DateTime.Now));
    }
    private void frmTerminal_FormClosing(object sender, FormClosingEventArgs e)
    {
      // The form is closing, save the user's preferences
      SaveSettings();
    }

    private void btnOpenPort_Click(object sender, EventArgs e)
    {
			bool error = false;

      // If the port is open, close it.
      if (comport.IsOpen) comport.Close();
      else
      {
        // Set the port's settings
        comport.BaudRate = 115200;
        comport.PortName = cmbPortName.Text;

		try
		{
			// Open the port
			comport.Open();
		}
		catch (UnauthorizedAccessException) { error = true; }
		catch (IOException) { error = true; }
		catch (ArgumentException) { error = true; }

		if (error) MessageBox.Show(this, "Could not open the COM port.  Most likely it is already in use, has been removed, or is unavailable.", "COM Port Unavalible", MessageBoxButtons.OK, MessageBoxIcon.Stop);
		else
		{
			// Show the initial pin states
			UpdatePinState();
		}
      }

      // Change the state of the form's controls
      EnableControls();

      // If the port is open, send focus to the send data box
	    if (comport.IsOpen)
	    {
		    txtSendData.Focus();
	    }
    }
    private void btnSend_Click(object sender, EventArgs e)
    { SendData(); }

    private void port_DataReceived(object sender, SerialDataReceivedEventArgs e)
    {
			// If the com port has been closed, do nothing
			if (!comport.IsOpen) return;

      // This method will be called when there is data waiting in the port's buffer

      // Determain which mode (string or binary) the user is in
      if (CurrentDataMode == DataMode.Text)
      {
        // Read all the data waiting in the buffer
        string data = comport.ReadExisting();

        // Display the text to the user in the terminal
        Log(LogMsgType.Incoming, data);
      }
      else
      {
        // Obtain the number of bytes waiting in the port's buffer
        int bytes = comport.BytesToRead;

        // Create a byte array buffer to hold the incoming data
        byte[] buffer = new byte[bytes];

        // Read the data from the port and store it in our buffer
        comport.Read(buffer, 0, bytes);

        // Show the user the incoming data in hex format
        Log(LogMsgType.Incoming, ByteArrayToHexString(buffer));
      }
    }

    private void txtSendData_KeyDown(object sender, KeyEventArgs e)
    { 
      // If the user presses [ENTER], send the data now
      if (KeyHandled = e.KeyCode == Keys.Enter) { e.Handled = true; SendData(); } 
    }
    private void txtSendData_KeyPress(object sender, KeyPressEventArgs e)
    { e.Handled = KeyHandled; }
    #endregion



		private void btnClear_Click(object sender, EventArgs e)
		{
			ClearTerminal();
		}

		private void ClearTerminal()
		{
			rtfTerminal.Clear();
            txtSendData.Clear();
		}

		private void tmrCheckComPorts_Tick(object sender, EventArgs e)
		{
			// checks to see if COM ports have been added or removed
			// since it is quite common now with USB-to-Serial adapters
			RefreshComPortList();
		}

		private void RefreshComPortList()
		{
			// Determain if the list of com port names has changed since last checked
			string selected = RefreshComPortList(cmbPortName.Items.Cast<string>(), cmbPortName.SelectedItem as string, comport.IsOpen);

			// If there was an update, then update the control showing the user the list of port names
			if (!String.IsNullOrEmpty(selected))
			{
				cmbPortName.Items.Clear();
				cmbPortName.Items.AddRange(OrderedPortNames());
				cmbPortName.SelectedItem = selected;
			}
		}

		private string[] OrderedPortNames()
		{
			// Just a placeholder for a successful parsing of a string to an integer
			int num;

			// Order the serial port names in numberic order (if possible)
			return SerialPort.GetPortNames().OrderBy(a => a.Length > 3 && int.TryParse(a.Substring(3), out num) ? num : 0).ToArray(); 
		}
		
		private string RefreshComPortList(IEnumerable<string> PreviousPortNames, string CurrentSelection, bool PortOpen)
		{
			// Create a new return report to populate
			string selected = null;

			// Retrieve the list of ports currently mounted by the operating system (sorted by name)
			string[] ports = SerialPort.GetPortNames();

			// First determain if there was a change (any additions or removals)
			bool updated = PreviousPortNames.Except(ports).Count() > 0 || ports.Except(PreviousPortNames).Count() > 0;

			// If there was a change, then select an appropriate default port
			if (updated)
			{
				// Use the correctly ordered set of port names
				ports = OrderedPortNames();

				// Find newest port if one or more were added
				string newest = SerialPort.GetPortNames().Except(PreviousPortNames).OrderBy(a => a).LastOrDefault();

				// If the port was already open... (see logic notes and reasoning in Notes.txt)
				if (PortOpen)
				{
					if (ports.Contains(CurrentSelection)) selected = CurrentSelection;
					else if (!String.IsNullOrEmpty(newest)) selected = newest;
					else selected = ports.LastOrDefault();
				}
				else
				{
					if (!String.IsNullOrEmpty(newest)) selected = newest;
					else if (ports.Contains(CurrentSelection)) selected = CurrentSelection;
					else selected = ports.LastOrDefault();
				}
			}

			// If there was a change to the port list, return the recommended default selection
			return selected;
		}
	}
}