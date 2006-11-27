using System;
using System.IO;
using System.Collections.Generic;
using System.Collections;
using System.Text;
using System.Windows.Forms;
using Microsoft.Win32;
using System.Reflection;
using Ferda;
using Ferda.ProjectManager;
using Ferda.ModulesManager;

// This modul contains class "FE_err_msg", which contains list of all error messages (with their codes) in FEplugin and functions for displaying of error messages



namespace FEplugin_cs
{
    /// <summary>
    /// This class contains list of all error messages (with their codes) in FEplugin and functions for displaying of error messages.
    /// </summary>
    public class FE_err_msg
    {
        /// <summary>
        /// Structure for storing the information about one error message.
        /// </summary>
        private struct err_msg
        {
            /// <summary>
            /// Code of error message.
            /// </summary>
            public string code;

            /// <summary>
            /// Text of error message
            /// </summary>
            public string message;

            /// <summary>
            /// Constructor of one error message class.
            /// </summary>
            /// <param name="c">Code</param>
            /// <param name="m">Text of message</param>
            public err_msg(string c, string m)
            {
                code = c;
                message = m;
            }
        }


        /// <summary>
        /// List of all error messages in FEplugin.
        /// </summary>
        private static List<err_msg> messages;

        /// <summary>
        /// Filling the list of error messages (messages field).
        /// </summary>
        private static void fill_messages()
        {
            messages = new List<err_msg>();

            // SEM NAPSAT SEZNAM VSECH KODU A HLASEK
            messages.Add(new err_msg("FEP001", "Ferda DataMiner not detected on this computer. FE plugin is not functional."));
            messages.Add(new err_msg("FEP002", "Application was not able to load FrontEndConfig.xml"));
            messages.Add(new err_msg("FEP003", "Ferda DataMiner DLL library was not found."));
            messages.Add(new err_msg("FEP004", "Closing data source encountered a problem."));
            messages.Add(new err_msg("FEP005", "Opening data source encountered a problem."));
            messages.Add(new err_msg("FEP006", "Some another Ferda data source is already opened. Current Ferda DataMiner configuration not allows open more than one data source. (IceGridNode is not set as service.)"));
        }

        /// <summary>
        /// Returns text of error message.
        /// </summary>
        /// <param name="code">Code of error message.</param>
        /// <returns>Text of error message.</returns>
        private static string getMessageViaCode(string code)
        {
            string result = "";

            foreach(err_msg item in messages)
            {
                if (item.code == code)
                    result = item.message;
            }

            return result;
        }

        /// <summary>
        /// Static constructor - filling the list of messages.
        /// </summary>
        static FE_err_msg()
        {
            fill_messages();

        }


        /// <summary>
        /// Displays an message box with error code and message.
        /// </summary>
        /// <param name="error">Code of error</param>
        public static void show_err_msg(FE_error error)
        {
            string code = error.code;
            string param = "";
            string message = getMessageViaCode(code);

            if (!String.IsNullOrEmpty(error.param))
            {
                param = " (" + error.param + ")";
            }
            
            // displaying the error message
            if(!String.IsNullOrEmpty(message))
                MessageBox.Show("Program error: " + code + "\n\n" + message + param, "ReportAsistent - FE plugin", MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }
    }

    /// <summary>
    /// FEplugin error (exception) class.
    /// </summary>
    public class FE_error : System.Exception
    {
        /// <summary>
        /// Code of error
        /// </summary>
        public string code;
        
        /// <summary>
        /// Parameter of error message (i.e. reason of error)
        /// </summary>
        public string param;

        /// <summary>
        /// Constructing the FEplugin error (excption) class.
        /// </summary>
        /// <param name="code">Code of error</param>
        public FE_error(string code)
        {
            this.code = code;
            this.param = "";
        }

        /// <summary>
        /// Constructing the FEplugin error (excption) class.
        /// </summary>
        /// <param name="code">Code of error</param>
        /// <param name="param">Parameter of error message</param>
        public FE_error(string code, string param)
        {
            this.code = code;
            this.param = param;
        }
    }
}