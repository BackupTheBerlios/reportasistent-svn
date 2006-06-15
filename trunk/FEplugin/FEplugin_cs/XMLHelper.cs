using System.Collections;
using System.Text;
using System.Windows.Forms;
using Ferda;
using Ferda.ProjectManager;
using Ferda.ModulesManager;
using Ferda.FrontEnd;
using System.IO;
using System;

namespace FEplugin_cs
{
    public class XMLHelper
    {
        public static string loadDTD()  // vrati DTD aktivnich prvku
        {
            string DTD = "";
            string path = "../XML/dtd.dtd";   // relativni cesta k DTD souboru

            if (!File.Exists(path))
            {
                throw new Exception("Soubor " + path + " nebyl nalezen");
            }

            using (StreamReader sr = File.OpenText(path))
            {
                String block;
                // Read and display lines from the file until the end of 
                // the file is reached.
                while ((block = sr.ReadLine()) != null)
                {
                    DTD += block;
                }
                sr.Close();
            }


            return DTD;

        }

        public static void saveXMLexample(string XML, string path)  // ulozi XML string do souboru path
        {
            try
            {
                using (StreamWriter sw = new StreamWriter(path))
                {
                    sw.Write(XML);
                    sw.Close();
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
            }
        }

        public static string replaceXMLsign(string str) // v retezci str nahradi xml znaky ("&" => "&amp;" , "<" => "&lt;" , ">" => "&gt;")
        {
            str = str.Replace("&", "&amp;");
            str = str.Replace("<", "&lt;");
            str = str.Replace(">", "&gt;");
            return str;
        }
    }
}
