using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;
using System.Windows.Forms;
using Ferda;
using Ferda.ProjectManager;
using Ferda.ModulesManager;
using Ferda.Modules;
using Ferda.Modules.Helpers;
using Ferda.Modules.Quantifiers;
//using Ferda.FrontEnd;

namespace FEplugin_cs
{
    // ==================== Aktivni prvek Data matrix ================================
    
    public class AP_FEData_matrix
    {
        public static string getList(int index)
        {
            string resultString = ""; // vysledny XML string
            string ErrStr = "";  // zaznamy o chybach

            // nacteni DTD do resultStringu
            try { resultString = XMLHelper.loadDTD(); }
            catch (Exception e)
            {
#if (LADENI)
                MessageBox.Show("Chyba pri nacitani DTD: " + e.Message);
#endif
                return resultString;
            }

            // korenovy element
            resultString += "<active_list>";


            // zpracovani kazde krabicky "Data matrix"

            #region   nalezeni a zpracovani vsech krabicek Column (DataMiningCommon.DataMatrix)

            IBoxModule[] MatrBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, "DataMiningCommon.DataMatrix");

            
            // zpracovani kazde krabicky Column
            foreach (IBoxModule MBox in MatrBoxes)
            {
                try
                {
                    Rec_data_matrix rMatrix = new Rec_data_matrix(); // zaznam o datove matici

                    // nalezeni ID
                    rMatrix.id = "matrix" + MBox.ProjectIdentifier.ToString();

                    // nalezeni jmena datoveho zdroje (databaze)
                    IBoxModule[] db_names = BoxesHelper.ListAncestBoxesWithID(MBox, "DataMiningCommon.Database");
                    if (db_names.GetLength(0) != 1)  // byl nalezen pocet datovych zdroju ruzny od jedne
                        throw new System.Exception("bylo nalezeno " + db_names.GetLength(0).ToString() + " databazi");
                    rMatrix.db_name = (db_names[0].GetPropertyOther("DatabaseName") as StringT).stringValue;

                    // nalezeni jmena datove matice
                    rMatrix.matrix_name = MBox.GetPropertyString("Name");

                    // zjisteni poctu zaznamu
                    rMatrix.record_count = MBox.GetPropertyLong("RecordCount").ToString();

                    // pridani polozky do XML
                    resultString += rMatrix.ToXML();
                 
                }
                catch (System.Exception e)
                {
                    ErrStr += "Box ProjectIdentifier=" + MBox.ProjectIdentifier.ToString() + ": " + e.Message + "\n";
                }
            }

            #endregion


            resultString += "</active_list>";

#if (DEBUG)
            // Kody - ulozeni vystupu do souboru "XMLData_matrixExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLData_matrixExample.xml");

            if (ErrStr != "") // LADICI
                MessageBox.Show("Chyby pri generovani seznamu Boolskych cedentu:\n" + ErrStr);
#endif

            return resultString;
        }
    }

    #region --- Recordy ---

    public class Rec_data_matrix
    {
        #region DATA

        public string id = "";
        public string db_name = "unknown";
        public string matrix_name = "unknown";
        public string record_count = "unknown";
        public string integer_count = "unknown";
        public string float_count = "unknown";
        public string string_count = "unknown";
        public string boolean_count = "unknown";
        public string date_count = "unknown";

        #endregion

        #region METHODS

        public string ToXML()
        {
            id = XMLHelper.replaceXMLsign(id);
            db_name = XMLHelper.replaceXMLsign(db_name);
            matrix_name = XMLHelper.replaceXMLsign(matrix_name);
            record_count = XMLHelper.replaceXMLsign(record_count);
            integer_count = XMLHelper.replaceXMLsign(integer_count);
            float_count = XMLHelper.replaceXMLsign(float_count);
            string_count = XMLHelper.replaceXMLsign(string_count);
            boolean_count = XMLHelper.replaceXMLsign(boolean_count);
            date_count = XMLHelper.replaceXMLsign(date_count);
            
            string XML = "";

            XML += "<data_matrix id=\"" + id + 
                    "\" db_name=\"" + db_name + 
                    "\" matrix_name=\"" + matrix_name +
                    "\" record_count=\"" + record_count +
                    "\" integer_count=\"" + integer_count +
                    "\" float_count=\"" + float_count +
                    "\" string_count=\"" + string_count +
                    "\" boolean_count=\"" + boolean_count +
                    "\" date_count=\"" + date_count + "\"/>";
            return XML;
        }

        #endregion
    }

    #endregion
}
