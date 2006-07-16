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

// Tento modul obsahuje tridu "FE_err_msg", ktera obsahuje seznam chybovych hlasek FE pluginu a funkce pro jejich zobrazovani



namespace FEplugin_cs
{
    public class FE_err_msg
    {
        // struktura pro uchovavani chybovych hlasek
        struct err_msg
        {
            public string code;  // kod hlasky
            public string message; // text hlasky

            // konstruktor
            public err_msg(string c, string m)
            {
                code = c;
                message = m;
            }
        }


        // seznam chybovych hlasek
        static List<err_msg> messages;

        // naplni seznam messages
        static void fill_messages()
        {
            messages = new List<err_msg>();

            // SEM NAPSAT SEZNAM VSECH KODU A HLASEK
            messages.Add(new err_msg("FEP001", "Ferda DataMiner not detected on this computer. FE plugin is not functional."));
            messages.Add(new err_msg("FEP002", "Application was not able to load FrontEndConfig.xml"));
            messages.Add(new err_msg("FEP003", "Ferda DataMiner DLL library was not found."));
        }

        // vrati text chybove hlasky podle kodu chyby
        static string getMessageViaCode(string code)
        {
            string result = "";

            foreach(err_msg item in messages)
            {
                if (item.code == code)
                    result = item.message;
            }

            return result;
        }

        // staticky konstruktor
        static FE_err_msg()
        {
            fill_messages();

        }


        // //////////////////////////
        // vypise MessageBox s chybovou hlaskou
        
        public static void show_err_msg(FE_error error)
        {
            string code = error.code;
            string param = "";
            string message = getMessageViaCode(code);

            if (!String.IsNullOrEmpty(error.param))
            {
                param = " (" + error.param + ")";
            }
            
            if(!String.IsNullOrEmpty(message))
                MessageBox.Show(code + ": " + message + param, "FE plugin error " + code, MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }

    // trida
    public class FE_error : System.Exception
    {
        public string code;  // kod chyby
        public string param; // parametr

        // konstruktory
        public FE_error(string code)
        {
            this.code = code;
            this.param = "";
        }
        public FE_error(string code, string param)
        {
            this.code = code;
            this.param = param;
        }
    }
}