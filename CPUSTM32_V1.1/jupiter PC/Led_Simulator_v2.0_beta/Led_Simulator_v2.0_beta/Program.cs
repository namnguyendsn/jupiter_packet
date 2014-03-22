using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace Led_Simulator_v2._0_beta
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            IModel model = new Model();
            IView mainForm = new Form1();
            var p = new Presenter(mainForm, model);
            Application.Run((Form)mainForm);
        }
    }
}
