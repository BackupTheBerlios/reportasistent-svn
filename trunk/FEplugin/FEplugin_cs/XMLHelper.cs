using System.Collections;
using System.Text;
using System.Windows.Forms;
using Ferda;
using Ferda.ProjectManager;
using Ferda.ModulesManager;
using System.IO;
using System;

namespace FEplugin_cs
{
    /// <summary>
    /// Class contains tools, which are helpful with XML operations used in FEplugin.
    /// </summary>
    public class XMLHelper
    {
        /// <summary>
        /// Loads a DTD for validation of FEplugin output corectness
        /// </summary>
        /// <returns>String with DTD</returns>
        public static string loadDTD()
        {
            string DTD = "";
            string path = "../XML/plug_output_DTD.xml";   // relative path to DTD file

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

        
        /// <summary>
        /// Stores XML string in file.
        /// </summary>
        /// <param name="XML">XMP string.</param>
        /// <param name="path">Path to file where XML string will be saved.</param>
        public static void saveXMLexample(string XML, string path)
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
        
        
        /// <summary>
        /// Replacing of signes in XML string ("&" => "&amp;" , "<" => "&lt;" , ">" => "&gt;")
        /// </summary>
        /// <param name="str">String where signes will be replaced.</param>
        /// <returns>String with replaced signs.</returns>
        public static string replaceXMLsign(string str) 
        {
            str = str.Replace("&", "&amp;");
            str = str.Replace("<", "&lt;");
            str = str.Replace(">", "&gt;");
            return str;
        }
    }
}
