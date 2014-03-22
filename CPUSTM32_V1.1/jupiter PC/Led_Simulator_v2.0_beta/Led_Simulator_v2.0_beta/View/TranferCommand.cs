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
        private void mnuFileNew_Click(object sender, EventArgs e)
        {
            //Inform Presenter that FIleNew command is called
            if (FileNewCommand != null)
            {
                FileNewCommand(this, e);
            }
        }

        private void mnuFileOpen_Click(object sender, EventArgs e)
        {
            //Inform Presenter that FIleOpen command is called
            if (FileOpenCommand != null)
            {
                FileOpenCommand(this, e);
            }
        }

        private void mnuFileSave_Click(object sender, EventArgs e)
        {
            //Inform Presenter that FIleSave command is called
            if (FileSaveCommand != null)
            {
                FileSaveCommand(this, e);
            }
        }

        private void mnuFileClose_Click(object sender, EventArgs e)
        {
            //Inform Presenter that FIleClose command is called
            if (FileCloseCommand != null)
            {
                FileCloseCommand(this, e);
            }
        }

        private void mnuExit_Click(object sender, EventArgs e)
        {
            //Inform Presenter that Exit command is called
            if (ExitCommand != null)
            {
                ExitCommand(this, e);
            }
        }

        private void mnuUndo_Click(object sender, EventArgs e)
        {
            //Inform Presenter that Undo command is called
            if (UndoCommand != null)
            {
                UndoCommand(this, e);
            }
        }

        private void mnuRedo_Click(object sender, EventArgs e)
        {
            //Inform Presenter that Redo command is called
            if (RedoCommand != null)
            {
                RedoCommand(this, e);
            }
        }

        private void mnuClearAllEffect_Click(object sender, EventArgs e)
        {
            if (ClearAllEffectCommand != null)
            {
                ClearAllEffectCommand(selectedList, e);
            }
        }

        private void mnuMaxBrightEffect_Click(object sender, EventArgs e)
        {
            if (MaxBrightEffectCommand != null)
            {
                MaxBrightEffectCommand(selectedList, e);
            }
        }

        private void mnuRevertEffect_Click(object sender, EventArgs e)
        {
            if (RevertEffectCommand != null)
            {
                RevertEffectCommand(selectedList, e);
            }
        }

        private void mnuBlindEffect_Click(object sender, EventArgs e)
        {
            if (BlindEffectCommand != null)
            {
                BlindEffectCommand(selectedList, e);
            }
        }

        private void mnuFireBallEffect_Click(object sender, EventArgs e)
        {
            if (FireBallEffectCommand != null)
            {
                FireBallEffectCommand(selectedList, e);
            }
        }
    }
}
