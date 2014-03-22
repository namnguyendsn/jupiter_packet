namespace Led_Simulator_v2._0_beta
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileNew = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileOpen = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileSave = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileClose = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuExit = new System.Windows.Forms.ToolStripMenuItem();
            this.editToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUndo = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuRedo = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuAddStateAbove = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuAddStateBelow = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuRemoveState = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator6 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuAddStartFor = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuAddEndFor = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator7 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuAddLedLeft = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuAddLedRight = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuRemoveLed = new System.Windows.Forms.ToolStripMenuItem();
            this.effectsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuClearAllEffect = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuMaxBrightEffect = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuRevertEffect = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuBlindEffect = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFireBallEffect = new System.Windows.Forms.ToolStripMenuItem();
            this.simulatorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuStartSimulate = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuPauseSimulate = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuStopSimulate = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.tsAddStateAbove = new System.Windows.Forms.ToolStripButton();
            this.tsAddStateBelow = new System.Windows.Forms.ToolStripButton();
            this.tsAddStartFor = new System.Windows.Forms.ToolStripButton();
            this.tsAddEndFor = new System.Windows.Forms.ToolStripButton();
            this.tsRemoveState = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.tsAddLedLeft = new System.Windows.Forms.ToolStripButton();
            this.tsAddLedRight = new System.Windows.Forms.ToolStripButton();
            this.tsRemoveLed = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.tsStartSimulate = new System.Windows.Forms.ToolStripButton();
            this.tsPauseSimulate = new System.Windows.Forms.ToolStripButton();
            this.tsStopSimulate = new System.Windows.Forms.ToolStripButton();
            this.gbStatus = new System.Windows.Forms.GroupBox();
            this.tbGlobalInfo = new System.Windows.Forms.TextBox();
            this.lbGlobalInfo = new System.Windows.Forms.Label();
            this.btnChangeLedNode = new System.Windows.Forms.Button();
            this.tbValue = new System.Windows.Forms.TextBox();
            this.lbValue = new System.Windows.Forms.Label();
            this.lbState = new System.Windows.Forms.Label();
            this.lbLed = new System.Windows.Forms.Label();
            this.gbLedEdit = new System.Windows.Forms.GroupBox();
            this.pnSimulate = new System.Windows.Forms.Panel();
            this.gbCOM = new System.Windows.Forms.GroupBox();
            this.button1 = new System.Windows.Forms.Button();
            this.lbCOMStatus = new System.Windows.Forms.Label();
            this.btnComConnect = new System.Windows.Forms.Button();
            this.lbCOMStopBit = new System.Windows.Forms.Label();
            this.lbCOMParity = new System.Windows.Forms.Label();
            this.lbCOMDataBit = new System.Windows.Forms.Label();
            this.lbCOMBaudrate = new System.Windows.Forms.Label();
            this.cbComPort = new System.Windows.Forms.ComboBox();
            this.lbComPort = new System.Windows.Forms.Label();
            this.gbSendData = new System.Windows.Forms.Button();
            this.serialPort = new System.IO.Ports.SerialPort(this.components);
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.ctMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.effect1ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.effect2ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.effect3ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.effect4ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.dtpOn = new System.Windows.Forms.DateTimePicker();
            this.lbOn = new System.Windows.Forms.Label();
            this.lbOff = new System.Windows.Forms.Label();
            this.dtpOff = new System.Windows.Forms.DateTimePicker();
            this.btnSetAlarm = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.rbtLedInfo = new System.Windows.Forms.RadioButton();
            this.rbtEffect = new System.Windows.Forms.RadioButton();
            this.rbtSettime = new System.Windows.Forms.RadioButton();
            this.rbtAlarm = new System.Windows.Forms.RadioButton();
            this.btnSetTime = new System.Windows.Forms.Button();
            this.menuStrip1.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.gbStatus.SuspendLayout();
            this.gbCOM.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.ctMenu.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.editToolStripMenuItem,
            this.effectsToolStripMenuItem,
            this.simulatorToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(786, 24);
            this.menuStrip1.TabIndex = 3;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuFileNew,
            this.mnuFileOpen,
            this.mnuFileSave,
            this.mnuFileClose,
            this.toolStripSeparator1,
            this.mnuExit});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // mnuFileNew
            // 
            this.mnuFileNew.Name = "mnuFileNew";
            this.mnuFileNew.Size = new System.Drawing.Size(103, 22);
            this.mnuFileNew.Text = "New";
            this.mnuFileNew.Click += new System.EventHandler(this.mnuFileNew_Click);
            // 
            // mnuFileOpen
            // 
            this.mnuFileOpen.Name = "mnuFileOpen";
            this.mnuFileOpen.Size = new System.Drawing.Size(103, 22);
            this.mnuFileOpen.Text = "Open";
            this.mnuFileOpen.Click += new System.EventHandler(this.mnuFileOpen_Click);
            // 
            // mnuFileSave
            // 
            this.mnuFileSave.Name = "mnuFileSave";
            this.mnuFileSave.Size = new System.Drawing.Size(103, 22);
            this.mnuFileSave.Text = "Save";
            this.mnuFileSave.Click += new System.EventHandler(this.mnuFileSave_Click);
            // 
            // mnuFileClose
            // 
            this.mnuFileClose.Name = "mnuFileClose";
            this.mnuFileClose.Size = new System.Drawing.Size(103, 22);
            this.mnuFileClose.Text = "Close";
            this.mnuFileClose.Click += new System.EventHandler(this.mnuFileClose_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(100, 6);
            // 
            // mnuExit
            // 
            this.mnuExit.Name = "mnuExit";
            this.mnuExit.Size = new System.Drawing.Size(103, 22);
            this.mnuExit.Text = "Exit";
            this.mnuExit.Click += new System.EventHandler(this.mnuExit_Click);
            // 
            // editToolStripMenuItem
            // 
            this.editToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuUndo,
            this.mnuRedo,
            this.toolStripSeparator5,
            this.mnuAddStateAbove,
            this.mnuAddStateBelow,
            this.mnuRemoveState,
            this.toolStripSeparator6,
            this.mnuAddStartFor,
            this.mnuAddEndFor,
            this.toolStripSeparator7,
            this.mnuAddLedLeft,
            this.mnuAddLedRight,
            this.mnuRemoveLed});
            this.editToolStripMenuItem.Name = "editToolStripMenuItem";
            this.editToolStripMenuItem.Size = new System.Drawing.Size(39, 20);
            this.editToolStripMenuItem.Text = "Edit";
            // 
            // mnuUndo
            // 
            this.mnuUndo.Name = "mnuUndo";
            this.mnuUndo.Size = new System.Drawing.Size(159, 22);
            this.mnuUndo.Text = "Undo";
            this.mnuUndo.Click += new System.EventHandler(this.mnuUndo_Click);
            // 
            // mnuRedo
            // 
            this.mnuRedo.Name = "mnuRedo";
            this.mnuRedo.Size = new System.Drawing.Size(159, 22);
            this.mnuRedo.Text = "Redo";
            this.mnuRedo.Click += new System.EventHandler(this.mnuRedo_Click);
            // 
            // toolStripSeparator5
            // 
            this.toolStripSeparator5.Name = "toolStripSeparator5";
            this.toolStripSeparator5.Size = new System.Drawing.Size(156, 6);
            // 
            // mnuAddStateAbove
            // 
            this.mnuAddStateAbove.Name = "mnuAddStateAbove";
            this.mnuAddStateAbove.Size = new System.Drawing.Size(159, 22);
            this.mnuAddStateAbove.Text = "Add state above";
            this.mnuAddStateAbove.Click += new System.EventHandler(this.mnuAddStateAbove_Click);
            // 
            // mnuAddStateBelow
            // 
            this.mnuAddStateBelow.Name = "mnuAddStateBelow";
            this.mnuAddStateBelow.Size = new System.Drawing.Size(159, 22);
            this.mnuAddStateBelow.Text = "Add state below";
            this.mnuAddStateBelow.Click += new System.EventHandler(this.mnuAddStateBelow_Click);
            // 
            // mnuRemoveState
            // 
            this.mnuRemoveState.Name = "mnuRemoveState";
            this.mnuRemoveState.Size = new System.Drawing.Size(159, 22);
            this.mnuRemoveState.Text = "Remove state";
            this.mnuRemoveState.Click += new System.EventHandler(this.mnuRemoveState_Click);
            // 
            // toolStripSeparator6
            // 
            this.toolStripSeparator6.Name = "toolStripSeparator6";
            this.toolStripSeparator6.Size = new System.Drawing.Size(156, 6);
            // 
            // mnuAddStartFor
            // 
            this.mnuAddStartFor.Name = "mnuAddStartFor";
            this.mnuAddStartFor.Size = new System.Drawing.Size(159, 22);
            this.mnuAddStartFor.Text = "Add start for";
            this.mnuAddStartFor.Click += new System.EventHandler(this.mnuAddStartFor_Click);
            // 
            // mnuAddEndFor
            // 
            this.mnuAddEndFor.Name = "mnuAddEndFor";
            this.mnuAddEndFor.Size = new System.Drawing.Size(159, 22);
            this.mnuAddEndFor.Text = "Add end for";
            this.mnuAddEndFor.Click += new System.EventHandler(this.mnuAddEndFor_Click);
            // 
            // toolStripSeparator7
            // 
            this.toolStripSeparator7.Name = "toolStripSeparator7";
            this.toolStripSeparator7.Size = new System.Drawing.Size(156, 6);
            // 
            // mnuAddLedLeft
            // 
            this.mnuAddLedLeft.Name = "mnuAddLedLeft";
            this.mnuAddLedLeft.Size = new System.Drawing.Size(159, 22);
            this.mnuAddLedLeft.Text = "Add led Left";
            this.mnuAddLedLeft.Click += new System.EventHandler(this.mnuAddLedLeft_Click);
            // 
            // mnuAddLedRight
            // 
            this.mnuAddLedRight.Name = "mnuAddLedRight";
            this.mnuAddLedRight.Size = new System.Drawing.Size(159, 22);
            this.mnuAddLedRight.Text = "Add led Right";
            this.mnuAddLedRight.Click += new System.EventHandler(this.mnuAddLedRight_Click);
            // 
            // mnuRemoveLed
            // 
            this.mnuRemoveLed.Name = "mnuRemoveLed";
            this.mnuRemoveLed.Size = new System.Drawing.Size(159, 22);
            this.mnuRemoveLed.Text = "Remove led";
            this.mnuRemoveLed.Click += new System.EventHandler(this.mnuRemoveLed_Click);
            // 
            // effectsToolStripMenuItem
            // 
            this.effectsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuClearAllEffect,
            this.mnuMaxBrightEffect,
            this.mnuRevertEffect,
            this.mnuBlindEffect,
            this.mnuFireBallEffect});
            this.effectsToolStripMenuItem.Name = "effectsToolStripMenuItem";
            this.effectsToolStripMenuItem.Size = new System.Drawing.Size(54, 20);
            this.effectsToolStripMenuItem.Text = "Effects";
            // 
            // mnuClearAllEffect
            // 
            this.mnuClearAllEffect.Name = "mnuClearAllEffect";
            this.mnuClearAllEffect.Size = new System.Drawing.Size(131, 22);
            this.mnuClearAllEffect.Text = "Clear All";
            this.mnuClearAllEffect.Click += new System.EventHandler(this.mnuClearAllEffect_Click);
            // 
            // mnuMaxBrightEffect
            // 
            this.mnuMaxBrightEffect.Name = "mnuMaxBrightEffect";
            this.mnuMaxBrightEffect.Size = new System.Drawing.Size(131, 22);
            this.mnuMaxBrightEffect.Text = "Max Bright";
            this.mnuMaxBrightEffect.Click += new System.EventHandler(this.mnuMaxBrightEffect_Click);
            // 
            // mnuRevertEffect
            // 
            this.mnuRevertEffect.Name = "mnuRevertEffect";
            this.mnuRevertEffect.Size = new System.Drawing.Size(131, 22);
            this.mnuRevertEffect.Text = "Revert";
            this.mnuRevertEffect.Click += new System.EventHandler(this.mnuRevertEffect_Click);
            // 
            // mnuBlindEffect
            // 
            this.mnuBlindEffect.Name = "mnuBlindEffect";
            this.mnuBlindEffect.Size = new System.Drawing.Size(131, 22);
            this.mnuBlindEffect.Text = "Blind";
            this.mnuBlindEffect.Click += new System.EventHandler(this.mnuBlindEffect_Click);
            // 
            // mnuFireBallEffect
            // 
            this.mnuFireBallEffect.Name = "mnuFireBallEffect";
            this.mnuFireBallEffect.Size = new System.Drawing.Size(131, 22);
            this.mnuFireBallEffect.Text = "FireBall";
            this.mnuFireBallEffect.Click += new System.EventHandler(this.mnuFireBallEffect_Click);
            // 
            // simulatorToolStripMenuItem
            // 
            this.simulatorToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuStartSimulate,
            this.mnuPauseSimulate,
            this.mnuStopSimulate});
            this.simulatorToolStripMenuItem.Name = "simulatorToolStripMenuItem";
            this.simulatorToolStripMenuItem.Size = new System.Drawing.Size(70, 20);
            this.simulatorToolStripMenuItem.Text = "Simulator";
            // 
            // mnuStartSimulate
            // 
            this.mnuStartSimulate.Name = "mnuStartSimulate";
            this.mnuStartSimulate.Size = new System.Drawing.Size(105, 22);
            this.mnuStartSimulate.Text = "Start";
            this.mnuStartSimulate.Click += new System.EventHandler(this.mnuStartSimulate_Click);
            // 
            // mnuPauseSimulate
            // 
            this.mnuPauseSimulate.Name = "mnuPauseSimulate";
            this.mnuPauseSimulate.Size = new System.Drawing.Size(105, 22);
            this.mnuPauseSimulate.Text = "Pause";
            this.mnuPauseSimulate.Click += new System.EventHandler(this.mnuPauseSimulate_Click);
            // 
            // mnuStopSimulate
            // 
            this.mnuStopSimulate.Name = "mnuStopSimulate";
            this.mnuStopSimulate.Size = new System.Drawing.Size(105, 22);
            this.mnuStopSimulate.Text = "Stop";
            this.mnuStopSimulate.Click += new System.EventHandler(this.mnuStopSimulate_Click);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // toolStrip1
            // 
            this.toolStrip1.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.toolStrip1.CanOverflow = false;
            this.toolStrip1.ImageScalingSize = new System.Drawing.Size(50, 50);
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsAddStateAbove,
            this.tsAddStateBelow,
            this.tsAddStartFor,
            this.tsAddEndFor,
            this.tsRemoveState,
            this.toolStripSeparator3,
            this.tsAddLedLeft,
            this.tsAddLedRight,
            this.tsRemoveLed,
            this.toolStripSeparator4,
            this.tsStartSimulate,
            this.tsPauseSimulate,
            this.tsStopSimulate});
            this.toolStrip1.Location = new System.Drawing.Point(0, 24);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(786, 72);
            this.toolStrip1.TabIndex = 4;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // tsAddStateAbove
            // 
            this.tsAddStateAbove.Image = global::Led_Simulator_v2._0_beta.Properties.Resources.StateAddAbove;
            this.tsAddStateAbove.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.tsAddStateAbove.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsAddStateAbove.Name = "tsAddStateAbove";
            this.tsAddStateAbove.Size = new System.Drawing.Size(61, 69);
            this.tsAddStateAbove.Text = "Add state\nabove";
            this.tsAddStateAbove.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.tsAddStateAbove.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.tsAddStateAbove.Click += new System.EventHandler(this.mnuAddStateAbove_Click);
            // 
            // tsAddStateBelow
            // 
            this.tsAddStateBelow.Image = global::Led_Simulator_v2._0_beta.Properties.Resources.StateAddBelow;
            this.tsAddStateBelow.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.tsAddStateBelow.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsAddStateBelow.Name = "tsAddStateBelow";
            this.tsAddStateBelow.Size = new System.Drawing.Size(61, 69);
            this.tsAddStateBelow.Text = "Add state\nbelow";
            this.tsAddStateBelow.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.tsAddStateBelow.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.tsAddStateBelow.Click += new System.EventHandler(this.mnuAddStateBelow_Click);
            // 
            // tsAddStartFor
            // 
            this.tsAddStartFor.Image = global::Led_Simulator_v2._0_beta.Properties.Resources.StartFor;
            this.tsAddStartFor.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.tsAddStartFor.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsAddStartFor.Name = "tsAddStartFor";
            this.tsAddStartFor.Size = new System.Drawing.Size(59, 69);
            this.tsAddStartFor.Text = "Add start\nfor";
            this.tsAddStartFor.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.tsAddStartFor.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.tsAddStartFor.Click += new System.EventHandler(this.mnuAddStartFor_Click);
            // 
            // tsAddEndFor
            // 
            this.tsAddEndFor.Image = global::Led_Simulator_v2._0_beta.Properties.Resources.EndFor;
            this.tsAddEndFor.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.tsAddEndFor.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsAddEndFor.Name = "tsAddEndFor";
            this.tsAddEndFor.Size = new System.Drawing.Size(56, 69);
            this.tsAddEndFor.Text = "Add end\nfor";
            this.tsAddEndFor.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.tsAddEndFor.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.tsAddEndFor.Click += new System.EventHandler(this.mnuAddEndFor_Click);
            // 
            // tsRemoveState
            // 
            this.tsRemoveState.Image = global::Led_Simulator_v2._0_beta.Properties.Resources.StateRemove;
            this.tsRemoveState.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.tsRemoveState.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsRemoveState.Name = "tsRemoveState";
            this.tsRemoveState.Size = new System.Drawing.Size(54, 69);
            this.tsRemoveState.Text = "Remove\nstate";
            this.tsRemoveState.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.tsRemoveState.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.tsRemoveState.Click += new System.EventHandler(this.mnuRemoveState_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(6, 72);
            // 
            // tsAddLedLeft
            // 
            this.tsAddLedLeft.Image = global::Led_Simulator_v2._0_beta.Properties.Resources.LedAddLeft2;
            this.tsAddLedLeft.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.tsAddLedLeft.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsAddLedLeft.Name = "tsAddLedLeft";
            this.tsAddLedLeft.Size = new System.Drawing.Size(53, 69);
            this.tsAddLedLeft.Text = "Add led\nleft";
            this.tsAddLedLeft.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.tsAddLedLeft.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.tsAddLedLeft.Click += new System.EventHandler(this.mnuAddLedLeft_Click);
            // 
            // tsAddLedRight
            // 
            this.tsAddLedRight.Image = global::Led_Simulator_v2._0_beta.Properties.Resources.LedAddRight2;
            this.tsAddLedRight.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.tsAddLedRight.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsAddLedRight.Name = "tsAddLedRight";
            this.tsAddLedRight.Size = new System.Drawing.Size(53, 69);
            this.tsAddLedRight.Text = "Add led\nright";
            this.tsAddLedRight.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.tsAddLedRight.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.tsAddLedRight.Click += new System.EventHandler(this.mnuAddLedRight_Click);
            // 
            // tsRemoveLed
            // 
            this.tsRemoveLed.Image = global::Led_Simulator_v2._0_beta.Properties.Resources.LedRemove2;
            this.tsRemoveLed.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.tsRemoveLed.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsRemoveLed.Name = "tsRemoveLed";
            this.tsRemoveLed.Size = new System.Drawing.Size(54, 69);
            this.tsRemoveLed.Text = "Remove\nled";
            this.tsRemoveLed.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.tsRemoveLed.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.tsRemoveLed.Click += new System.EventHandler(this.mnuRemoveLed_Click);
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(6, 72);
            // 
            // tsStartSimulate
            // 
            this.tsStartSimulate.Image = global::Led_Simulator_v2._0_beta.Properties.Resources.StartSimu;
            this.tsStartSimulate.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.tsStartSimulate.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsStartSimulate.Name = "tsStartSimulate";
            this.tsStartSimulate.Size = new System.Drawing.Size(57, 69);
            this.tsStartSimulate.Text = "Simulate\n";
            this.tsStartSimulate.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.tsStartSimulate.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.tsStartSimulate.Click += new System.EventHandler(this.mnuStartSimulate_Click);
            // 
            // tsPauseSimulate
            // 
            this.tsPauseSimulate.Image = global::Led_Simulator_v2._0_beta.Properties.Resources.PauseSimu;
            this.tsPauseSimulate.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.tsPauseSimulate.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsPauseSimulate.Name = "tsPauseSimulate";
            this.tsPauseSimulate.Size = new System.Drawing.Size(42, 69);
            this.tsPauseSimulate.Text = "Pause\n";
            this.tsPauseSimulate.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.tsPauseSimulate.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.tsPauseSimulate.Click += new System.EventHandler(this.mnuPauseSimulate_Click);
            // 
            // tsStopSimulate
            // 
            this.tsStopSimulate.Image = global::Led_Simulator_v2._0_beta.Properties.Resources.StopSimu;
            this.tsStopSimulate.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.tsStopSimulate.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsStopSimulate.Name = "tsStopSimulate";
            this.tsStopSimulate.Size = new System.Drawing.Size(39, 69);
            this.tsStopSimulate.Text = "Stop\n";
            this.tsStopSimulate.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.tsStopSimulate.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.tsStopSimulate.Click += new System.EventHandler(this.mnuStopSimulate_Click);
            // 
            // gbStatus
            // 
            this.gbStatus.Controls.Add(this.tbGlobalInfo);
            this.gbStatus.Controls.Add(this.lbGlobalInfo);
            this.gbStatus.Controls.Add(this.btnChangeLedNode);
            this.gbStatus.Controls.Add(this.tbValue);
            this.gbStatus.Controls.Add(this.lbValue);
            this.gbStatus.Controls.Add(this.lbState);
            this.gbStatus.Controls.Add(this.lbLed);
            this.gbStatus.Location = new System.Drawing.Point(562, 115);
            this.gbStatus.Name = "gbStatus";
            this.gbStatus.Size = new System.Drawing.Size(212, 161);
            this.gbStatus.TabIndex = 5;
            this.gbStatus.TabStop = false;
            this.gbStatus.Text = "Status";
            // 
            // tbGlobalInfo
            // 
            this.tbGlobalInfo.Location = new System.Drawing.Point(110, 66);
            this.tbGlobalInfo.Name = "tbGlobalInfo";
            this.tbGlobalInfo.Size = new System.Drawing.Size(96, 20);
            this.tbGlobalInfo.TabIndex = 6;
            this.tbGlobalInfo.Visible = false;
            this.tbGlobalInfo.KeyDown += new System.Windows.Forms.KeyEventHandler(this.tbGlobalInfo_KeyDown);
            // 
            // lbGlobalInfo
            // 
            this.lbGlobalInfo.AutoSize = true;
            this.lbGlobalInfo.Location = new System.Drawing.Point(7, 69);
            this.lbGlobalInfo.Name = "lbGlobalInfo";
            this.lbGlobalInfo.Size = new System.Drawing.Size(58, 13);
            this.lbGlobalInfo.TabIndex = 5;
            this.lbGlobalInfo.Text = "Global Info";
            this.lbGlobalInfo.Visible = false;
            // 
            // btnChangeLedNode
            // 
            this.btnChangeLedNode.Location = new System.Drawing.Point(10, 125);
            this.btnChangeLedNode.Name = "btnChangeLedNode";
            this.btnChangeLedNode.Size = new System.Drawing.Size(75, 23);
            this.btnChangeLedNode.TabIndex = 4;
            this.btnChangeLedNode.Text = "Change";
            this.btnChangeLedNode.UseVisualStyleBackColor = true;
            this.btnChangeLedNode.Click += new System.EventHandler(this.btnChangeLedNode_Click);
            // 
            // tbValue
            // 
            this.tbValue.Location = new System.Drawing.Point(110, 92);
            this.tbValue.Name = "tbValue";
            this.tbValue.Size = new System.Drawing.Size(96, 20);
            this.tbValue.TabIndex = 3;
            this.tbValue.Visible = false;
            this.tbValue.KeyDown += new System.Windows.Forms.KeyEventHandler(this.tbValue_KeyDown);
            // 
            // lbValue
            // 
            this.lbValue.AutoSize = true;
            this.lbValue.Location = new System.Drawing.Point(6, 95);
            this.lbValue.Name = "lbValue";
            this.lbValue.Size = new System.Drawing.Size(54, 13);
            this.lbValue.TabIndex = 2;
            this.lbValue.Text = "Local Info";
            this.lbValue.Visible = false;
            // 
            // lbState
            // 
            this.lbState.AutoSize = true;
            this.lbState.Location = new System.Drawing.Point(7, 43);
            this.lbState.Name = "lbState";
            this.lbState.Size = new System.Drawing.Size(32, 13);
            this.lbState.TabIndex = 1;
            this.lbState.Text = "State";
            // 
            // lbLed
            // 
            this.lbLed.AutoSize = true;
            this.lbLed.Location = new System.Drawing.Point(7, 20);
            this.lbLed.Name = "lbLed";
            this.lbLed.Size = new System.Drawing.Size(25, 13);
            this.lbLed.TabIndex = 0;
            this.lbLed.Text = "Led";
            // 
            // gbLedEdit
            // 
            this.gbLedEdit.Location = new System.Drawing.Point(13, 115);
            this.gbLedEdit.Name = "gbLedEdit";
            this.gbLedEdit.Size = new System.Drawing.Size(531, 338);
            this.gbLedEdit.TabIndex = 6;
            this.gbLedEdit.TabStop = false;
            this.gbLedEdit.Text = "Led state";
            // 
            // pnSimulate
            // 
            this.pnSimulate.Location = new System.Drawing.Point(2, 19);
            this.pnSimulate.Name = "pnSimulate";
            this.pnSimulate.Size = new System.Drawing.Size(519, 35);
            this.pnSimulate.TabIndex = 8;
            // 
            // gbCOM
            // 
            this.gbCOM.Controls.Add(this.button1);
            this.gbCOM.Controls.Add(this.lbCOMStatus);
            this.gbCOM.Controls.Add(this.btnComConnect);
            this.gbCOM.Controls.Add(this.lbCOMStopBit);
            this.gbCOM.Controls.Add(this.lbCOMParity);
            this.gbCOM.Controls.Add(this.lbCOMDataBit);
            this.gbCOM.Controls.Add(this.lbCOMBaudrate);
            this.gbCOM.Controls.Add(this.cbComPort);
            this.gbCOM.Controls.Add(this.lbComPort);
            this.gbCOM.Location = new System.Drawing.Point(562, 282);
            this.gbCOM.Name = "gbCOM";
            this.gbCOM.Size = new System.Drawing.Size(212, 239);
            this.gbCOM.TabIndex = 9;
            this.gbCOM.TabStop = false;
            this.gbCOM.Text = "COM Connection";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(131, 117);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 114);
            this.button1.TabIndex = 0;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Visible = false;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // lbCOMStatus
            // 
            this.lbCOMStatus.AutoSize = true;
            this.lbCOMStatus.Location = new System.Drawing.Point(6, 218);
            this.lbCOMStatus.Name = "lbCOMStatus";
            this.lbCOMStatus.Size = new System.Drawing.Size(37, 13);
            this.lbCOMStatus.TabIndex = 14;
            this.lbCOMStatus.Text = "Status";
            // 
            // btnComConnect
            // 
            this.btnComConnect.Location = new System.Drawing.Point(10, 56);
            this.btnComConnect.Name = "btnComConnect";
            this.btnComConnect.Size = new System.Drawing.Size(75, 23);
            this.btnComConnect.TabIndex = 12;
            this.btnComConnect.Text = "Open Port!";
            this.btnComConnect.UseVisualStyleBackColor = true;
            this.btnComConnect.Click += new System.EventHandler(this.btnComConnect_Click);
            // 
            // lbCOMStopBit
            // 
            this.lbCOMStopBit.AutoSize = true;
            this.lbCOMStopBit.Location = new System.Drawing.Point(6, 187);
            this.lbCOMStopBit.Name = "lbCOMStopBit";
            this.lbCOMStopBit.Size = new System.Drawing.Size(48, 13);
            this.lbCOMStopBit.TabIndex = 5;
            this.lbCOMStopBit.Text = "Stop bits";
            // 
            // lbCOMParity
            // 
            this.lbCOMParity.AutoSize = true;
            this.lbCOMParity.Location = new System.Drawing.Point(7, 158);
            this.lbCOMParity.Name = "lbCOMParity";
            this.lbCOMParity.Size = new System.Drawing.Size(33, 13);
            this.lbCOMParity.TabIndex = 4;
            this.lbCOMParity.Text = "Parity";
            // 
            // lbCOMDataBit
            // 
            this.lbCOMDataBit.AutoSize = true;
            this.lbCOMDataBit.Location = new System.Drawing.Point(7, 127);
            this.lbCOMDataBit.Name = "lbCOMDataBit";
            this.lbCOMDataBit.Size = new System.Drawing.Size(49, 13);
            this.lbCOMDataBit.TabIndex = 3;
            this.lbCOMDataBit.Text = "Data bits";
            // 
            // lbCOMBaudrate
            // 
            this.lbCOMBaudrate.AutoSize = true;
            this.lbCOMBaudrate.Location = new System.Drawing.Point(7, 97);
            this.lbCOMBaudrate.Name = "lbCOMBaudrate";
            this.lbCOMBaudrate.Size = new System.Drawing.Size(50, 13);
            this.lbCOMBaudrate.TabIndex = 2;
            this.lbCOMBaudrate.Text = "Baudrate";
            // 
            // cbComPort
            // 
            this.cbComPort.FormattingEnabled = true;
            this.cbComPort.Location = new System.Drawing.Point(110, 29);
            this.cbComPort.Name = "cbComPort";
            this.cbComPort.Size = new System.Drawing.Size(96, 21);
            this.cbComPort.TabIndex = 1;
            // 
            // lbComPort
            // 
            this.lbComPort.AutoSize = true;
            this.lbComPort.Location = new System.Drawing.Point(12, 32);
            this.lbComPort.Name = "lbComPort";
            this.lbComPort.Size = new System.Drawing.Size(53, 13);
            this.lbComPort.TabIndex = 0;
            this.lbComPort.Text = "COM Port";
            // 
            // gbSendData
            // 
            this.gbSendData.Location = new System.Drawing.Point(264, 10);
            this.gbSendData.Name = "gbSendData";
            this.gbSendData.Size = new System.Drawing.Size(75, 41);
            this.gbSendData.TabIndex = 15;
            this.gbSendData.Text = "Send Data";
            this.gbSendData.UseVisualStyleBackColor = true;
            this.gbSendData.Click += new System.EventHandler(this.btnSendData_Click);
            // 
            // serialPort
            // 
            this.serialPort.BaudRate = 115200;
            this.serialPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort_DataReceived);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.pnSimulate);
            this.groupBox1.Location = new System.Drawing.Point(13, 459);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(531, 62);
            this.groupBox1.TabIndex = 10;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Simulate";
            // 
            // ctMenu
            // 
            this.ctMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.effect1ToolStripMenuItem,
            this.effect2ToolStripMenuItem,
            this.effect3ToolStripMenuItem,
            this.effect4ToolStripMenuItem});
            this.ctMenu.Name = "ctMenu";
            this.ctMenu.Size = new System.Drawing.Size(114, 92);
            // 
            // effect1ToolStripMenuItem
            // 
            this.effect1ToolStripMenuItem.Name = "effect1ToolStripMenuItem";
            this.effect1ToolStripMenuItem.Size = new System.Drawing.Size(113, 22);
            this.effect1ToolStripMenuItem.Text = "Effect 1";
            // 
            // effect2ToolStripMenuItem
            // 
            this.effect2ToolStripMenuItem.Name = "effect2ToolStripMenuItem";
            this.effect2ToolStripMenuItem.Size = new System.Drawing.Size(113, 22);
            this.effect2ToolStripMenuItem.Text = "Effect 2";
            // 
            // effect3ToolStripMenuItem
            // 
            this.effect3ToolStripMenuItem.Name = "effect3ToolStripMenuItem";
            this.effect3ToolStripMenuItem.Size = new System.Drawing.Size(113, 22);
            this.effect3ToolStripMenuItem.Text = "Effect 3";
            // 
            // effect4ToolStripMenuItem
            // 
            this.effect4ToolStripMenuItem.Name = "effect4ToolStripMenuItem";
            this.effect4ToolStripMenuItem.Size = new System.Drawing.Size(113, 22);
            this.effect4ToolStripMenuItem.Text = "Effect 4";
            // 
            // dtpOn
            // 
            this.dtpOn.CustomFormat = "HH:mm";
            this.dtpOn.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.dtpOn.Location = new System.Drawing.Point(424, 539);
            this.dtpOn.Name = "dtpOn";
            this.dtpOn.ShowUpDown = true;
            this.dtpOn.Size = new System.Drawing.Size(52, 20);
            this.dtpOn.TabIndex = 12;
            // 
            // lbOn
            // 
            this.lbOn.AutoSize = true;
            this.lbOn.Location = new System.Drawing.Point(374, 539);
            this.lbOn.Name = "lbOn";
            this.lbOn.Size = new System.Drawing.Size(44, 13);
            this.lbOn.TabIndex = 13;
            this.lbOn.Text = "Start on";
            // 
            // lbOff
            // 
            this.lbOff.AutoSize = true;
            this.lbOff.Location = new System.Drawing.Point(374, 565);
            this.lbOff.Name = "lbOff";
            this.lbOff.Size = new System.Drawing.Size(44, 13);
            this.lbOff.TabIndex = 15;
            this.lbOff.Text = "Start off";
            // 
            // dtpOff
            // 
            this.dtpOff.CustomFormat = "HH:mm";
            this.dtpOff.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.dtpOff.Location = new System.Drawing.Point(424, 565);
            this.dtpOff.Name = "dtpOff";
            this.dtpOff.ShowUpDown = true;
            this.dtpOff.Size = new System.Drawing.Size(52, 20);
            this.dtpOff.TabIndex = 14;
            // 
            // btnSetAlarm
            // 
            this.btnSetAlarm.Location = new System.Drawing.Point(482, 537);
            this.btnSetAlarm.Name = "btnSetAlarm";
            this.btnSetAlarm.Size = new System.Drawing.Size(62, 43);
            this.btnSetAlarm.TabIndex = 16;
            this.btnSetAlarm.Text = "Set Alarm";
            this.btnSetAlarm.UseVisualStyleBackColor = true;
            this.btnSetAlarm.Click += new System.EventHandler(this.btnSetAlarm_Click);
            this.btnSetAlarm.MouseEnter += new System.EventHandler(this.btnSetAlarm_MouseEnter);
            this.btnSetAlarm.MouseLeave += new System.EventHandler(this.btnSetAlarm_MouseLeave);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.rbtLedInfo);
            this.groupBox2.Controls.Add(this.rbtEffect);
            this.groupBox2.Controls.Add(this.rbtSettime);
            this.groupBox2.Controls.Add(this.rbtAlarm);
            this.groupBox2.Controls.Add(this.gbSendData);
            this.groupBox2.Location = new System.Drawing.Point(15, 527);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(345, 58);
            this.groupBox2.TabIndex = 17;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Send data";
            // 
            // rbtLedInfo
            // 
            this.rbtLedInfo.AutoSize = true;
            this.rbtLedInfo.Location = new System.Drawing.Point(189, 19);
            this.rbtLedInfo.Name = "rbtLedInfo";
            this.rbtLedInfo.Size = new System.Drawing.Size(64, 17);
            this.rbtLedInfo.TabIndex = 19;
            this.rbtLedInfo.TabStop = true;
            this.rbtLedInfo.Text = "Led Info";
            this.rbtLedInfo.UseVisualStyleBackColor = true;
            this.rbtLedInfo.CheckedChanged += new System.EventHandler(this.rbtLedInfo_CheckedChanged);
            // 
            // rbtEffect
            // 
            this.rbtEffect.AutoSize = true;
            this.rbtEffect.Location = new System.Drawing.Point(130, 19);
            this.rbtEffect.Name = "rbtEffect";
            this.rbtEffect.Size = new System.Drawing.Size(53, 17);
            this.rbtEffect.TabIndex = 18;
            this.rbtEffect.TabStop = true;
            this.rbtEffect.Text = "Effect";
            this.rbtEffect.UseVisualStyleBackColor = true;
            this.rbtEffect.CheckedChanged += new System.EventHandler(this.rbtEffect_CheckedChanged);
            // 
            // rbtSettime
            // 
            this.rbtSettime.AutoSize = true;
            this.rbtSettime.Location = new System.Drawing.Point(64, 19);
            this.rbtSettime.Name = "rbtSettime";
            this.rbtSettime.Size = new System.Drawing.Size(60, 17);
            this.rbtSettime.TabIndex = 17;
            this.rbtSettime.TabStop = true;
            this.rbtSettime.Text = "Settime";
            this.rbtSettime.UseVisualStyleBackColor = true;
            this.rbtSettime.CheckedChanged += new System.EventHandler(this.rbtSettime_CheckedChanged);
            // 
            // rbtAlarm
            // 
            this.rbtAlarm.AutoSize = true;
            this.rbtAlarm.Location = new System.Drawing.Point(7, 20);
            this.rbtAlarm.Name = "rbtAlarm";
            this.rbtAlarm.Size = new System.Drawing.Size(51, 17);
            this.rbtAlarm.TabIndex = 16;
            this.rbtAlarm.TabStop = true;
            this.rbtAlarm.Text = "Alarm";
            this.rbtAlarm.UseVisualStyleBackColor = true;
            this.rbtAlarm.CheckedChanged += new System.EventHandler(this.rbtAlarm_CheckedChanged);
            // 
            // btnSetTime
            // 
            this.btnSetTime.Location = new System.Drawing.Point(550, 537);
            this.btnSetTime.Name = "btnSetTime";
            this.btnSetTime.Size = new System.Drawing.Size(62, 43);
            this.btnSetTime.TabIndex = 18;
            this.btnSetTime.Text = "Set Time";
            this.btnSetTime.UseVisualStyleBackColor = true;
            this.btnSetTime.Click += new System.EventHandler(this.btnSetTime_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(786, 592);
            this.Controls.Add(this.btnSetTime);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.btnSetAlarm);
            this.Controls.Add(this.lbOff);
            this.Controls.Add(this.dtpOff);
            this.Controls.Add(this.lbOn);
            this.Controls.Add(this.dtpOn);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.gbCOM);
            this.Controls.Add(this.gbLedEdit);
            this.Controls.Add(this.gbStatus);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.gbStatus.ResumeLayout(false);
            this.gbStatus.PerformLayout();
            this.gbCOM.ResumeLayout(false);
            this.gbCOM.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.ctMenu.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mnuFileNew;
        private System.Windows.Forms.ToolStripMenuItem mnuFileOpen;
        private System.Windows.Forms.ToolStripMenuItem mnuFileSave;
        private System.Windows.Forms.ToolStripMenuItem mnuFileClose;
        private System.Windows.Forms.ToolStripMenuItem mnuExit;
        private System.Windows.Forms.ToolStripMenuItem editToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mnuAddStateAbove;
        private System.Windows.Forms.ToolStripMenuItem mnuAddStateBelow;
        private System.Windows.Forms.ToolStripMenuItem mnuRemoveState;
        private System.Windows.Forms.ToolStripMenuItem effectsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem simulatorToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mnuStartSimulate;
        private System.Windows.Forms.ToolStripMenuItem mnuPauseSimulate;
        private System.Windows.Forms.ToolStripMenuItem mnuStopSimulate;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton tsStartSimulate;
        private System.Windows.Forms.ToolStripButton tsPauseSimulate;
        private System.Windows.Forms.ToolStripButton tsStopSimulate;
        private System.Windows.Forms.ToolStripButton tsAddStateAbove;
        private System.Windows.Forms.ToolStripButton tsAddStateBelow;
        private System.Windows.Forms.ToolStripButton tsRemoveState;
        private System.Windows.Forms.ToolStripButton tsAddLedLeft;
        private System.Windows.Forms.ToolStripButton tsAddLedRight;
        private System.Windows.Forms.ToolStripButton tsRemoveLed;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripButton tsAddStartFor;
        private System.Windows.Forms.ToolStripButton tsAddEndFor;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
        private System.Windows.Forms.GroupBox gbStatus;
        private System.Windows.Forms.GroupBox gbLedEdit;
        private System.Windows.Forms.Label lbValue;
        private System.Windows.Forms.Label lbState;
        private System.Windows.Forms.Label lbLed;
        private System.Windows.Forms.TextBox tbValue;
        private System.Windows.Forms.Button btnChangeLedNode;
        private System.Windows.Forms.TextBox tbGlobalInfo;
        private System.Windows.Forms.Label lbGlobalInfo;
        private System.Windows.Forms.Panel pnSimulate;
        
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem mnuUndo;
        private System.Windows.Forms.ToolStripMenuItem mnuRedo;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator6;
        private System.Windows.Forms.ToolStripMenuItem mnuAddStartFor;
        private System.Windows.Forms.ToolStripMenuItem mnuAddEndFor;
        private System.Windows.Forms.ToolStripMenuItem mnuAddLedLeft;
        private System.Windows.Forms.ToolStripMenuItem mnuAddLedRight;
        private System.Windows.Forms.ToolStripMenuItem mnuRemoveLed;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator7;
        private System.Windows.Forms.GroupBox gbCOM;
        private System.Windows.Forms.Button btnComConnect;
        private System.Windows.Forms.Label lbCOMStopBit;
        private System.Windows.Forms.Label lbCOMParity;
        private System.Windows.Forms.Label lbCOMDataBit;
        private System.Windows.Forms.Label lbCOMBaudrate;
        private System.Windows.Forms.ComboBox cbComPort;
        private System.Windows.Forms.Label lbComPort;
        private System.IO.Ports.SerialPort serialPort;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ContextMenuStrip ctMenu;
        private System.Windows.Forms.ToolStripMenuItem effect1ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem effect2ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem effect3ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem effect4ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mnuClearAllEffect;
        private System.Windows.Forms.ToolStripMenuItem mnuMaxBrightEffect;
        private System.Windows.Forms.ToolStripMenuItem mnuRevertEffect;
        private System.Windows.Forms.ToolStripMenuItem mnuBlindEffect;
        private System.Windows.Forms.Label lbCOMStatus;
        private System.Windows.Forms.Button gbSendData;
        private System.Windows.Forms.ToolStripMenuItem mnuFireBallEffect;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.DateTimePicker dtpOn;
        private System.Windows.Forms.Label lbOn;
        private System.Windows.Forms.Label lbOff;
        private System.Windows.Forms.DateTimePicker dtpOff;
        private System.Windows.Forms.Button btnSetAlarm;
        private System.Windows.Forms.GroupBox groupBox2;
        public System.Windows.Forms.RadioButton rbtLedInfo;
        public System.Windows.Forms.RadioButton rbtEffect;
        public System.Windows.Forms.RadioButton rbtSettime;
        public System.Windows.Forms.RadioButton rbtAlarm;
        private System.Windows.Forms.Button btnSetTime;


    }
}

