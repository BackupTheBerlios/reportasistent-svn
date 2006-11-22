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
    // ==================== Aktivni prvek Column (sloupec datove matice) ================================
    
    public class AP_FEColumn
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


            // zpracovani kazde krabicky Column

            #region   nalezeni a zpracovani vsech krabicek Column (DataMiningCommon.Column)

            IBoxModule[] AttrBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, "DataMiningCommon.Column");

            
            // zpracovani kazde krabicky Column
            foreach (IBoxModule ABox in AttrBoxes)
            {
                try
                {
                    Rec_column rColumn = new Rec_column(); // zaznam o novem sloupci

                    // nalezeni ID
                    rColumn.id = "column" + ABox.ProjectIdentifier.ToString();

                    // nalezeni jmena datoveho zdroje (databaze)
                    IBoxModule[] db_names = BoxesHelper.ListAncestBoxesWithID(ABox, "DataMiningCommon.Database");
                    if (db_names.GetLength(0) != 1)  // byl nalezen pocet datovych zdroju ruzny od jedne
                        throw new System.Exception("bylo nalezeno " + db_names.GetLength(0).ToString() + " databazi");
                    rColumn.db_name = (db_names[0].GetPropertyOther("DatabaseName") as StringT).stringValue;

                    // nalezeni jmena datove matice
                    IBoxModule[] matrix_names = BoxesHelper.ListAncestBoxesWithID(ABox, "DataMiningCommon.DataMatrix");
                    if (matrix_names.GetLength(0) != 1)  // byl nalezen pocet datovych matic ruzny od jedne
                        throw new System.Exception("bylo nalezeno " + matrix_names.GetLength(0).ToString() + " datovych matic");
                    rColumn.matrix_name = (matrix_names[0].GetPropertyOther("Name") as StringT).stringValue;

                    // zjisteni jmena sloupce
                    rColumn.column_name = ABox.GetPropertyString("Name");

                    // zjisteni typu hodnot
                    rColumn.value_type = ABox.GetPropertyString("ValueSubType");

                    // zjisteni Min
                    rColumn.min = ABox.GetPropertyString("ValueMin");

                    // zjisteni Max
                    rColumn.max = ABox.GetPropertyString("ValueMax");

                    // zjisteni Avg
                    rColumn.avg = ABox.GetPropertyString("ValueAverage");

                    // pridani polozky do XML
                    resultString += rColumn.ToXML();
                 
                }
                catch (System.Exception e)
                {
                    ErrStr += "Box ProjectIdentifier=" + ABox.ProjectIdentifier.ToString() + ": " + e.Message + "\n";
                }
            }

            #endregion


            resultString += "</active_list>";

#if (DEBUG)
            // Kody - ulozeni vystupu do souboru "XMLColumnExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLColumnExample.xml");

            if (ErrStr != "") // LADICI
                MessageBox.Show("Chyby pri generovani seznamu Boolskych cedentu:\n" + ErrStr);
#endif

            return resultString;
        }
    }

    #region --- Recordy ---

    public class Rec_column
    {
        #region DATA

        public string id = "";
        public string db_name = "unknown";
        public string matrix_name = "unknown";
        public string column_name = "unknown";
        public string value_type = "unknown";
        public string primary_key_position = "unknown";
        public string min = "unknown";
        public string max = "unknown";
        public string avg = "unknown";

        #endregion

        #region METHODS

        public string ToXML()
        {
            id = XMLHelper.replaceXMLsign(id);
            db_name = XMLHelper.replaceXMLsign(db_name);
            matrix_name = XMLHelper.replaceXMLsign(matrix_name);
            column_name = XMLHelper.replaceXMLsign(column_name);
            value_type = XMLHelper.replaceXMLsign(value_type);
            primary_key_position = XMLHelper.replaceXMLsign(primary_key_position);
            min = XMLHelper.replaceXMLsign(min);
            max = XMLHelper.replaceXMLsign(max);
            avg = XMLHelper.replaceXMLsign(avg);
            
            string XML = "";

            XML += "<column id=\"" + id + 
                    "\" db_name=\"" + db_name + 
                    "\" matrix_name=\"" + matrix_name +
                    "\" column_name=\"" + column_name +
                    "\" value_type=\"" + value_type +
                    "\" primary_key_position=\"" + primary_key_position +
                    "\" min=\"" + min +
                    "\" max=\"" + max +
                    "\" avg=\"" + avg + "\"/>";
            return XML;
        }

        #endregion
    }

    #endregion
}
