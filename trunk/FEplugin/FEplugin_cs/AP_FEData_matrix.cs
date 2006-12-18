
//AP_FEData_matrix.cs: implementation(file)
//
//
// This file is part of LM Report Asistent. (http://reportasistent.berlios.de, reportasistent-list@lists.berlios.de)
//
// Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova 
//
// LM Report Asistent is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// LM Report Asistent is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with LM Report Asistent; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
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


namespace FEplugin_cs
{
    // ==================== Active element "Data matrix" ================================

    /// <summary>
    /// Implementation of active element "Data matrix" (ID="data_matrix")
    /// </summary>
    public class AP_FEData_matrix
    {

        /// <summary>
        /// Returns XML string with all occurences of Active element "Data matrix".
        /// </summary>
        /// <param name="index">index of data source in FEplugin data sources table</param>
        /// <returns>XML string</returns>
        public static string getList(int index)
        {
            string resultString = ""; // result XML string
            string ErrStr = "";  // error reports

            // loading DTD to resultString
            try { resultString = XMLHelper.loadDTD(); }
            catch (Exception e)
            {
#if (LADENI)
                MessageBox.Show("error while loading DTD: " + e.Message);
#endif
                return resultString;
            }

            // root element
            resultString += "<active_list>";


            // processing of each box "Data matrix"

            #region   searching a processing of each boxes Column (DataMiningCommon.DataMatrix)

            IBoxModule[] MatrBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, "DataMiningCommon.DataMatrix");

            
            // processing of each box Column
            foreach (IBoxModule MBox in MatrBoxes)
            {
                try
                {
                    Rec_data_matrix rMatrix = new Rec_data_matrix(); // zaznam o datove matici

                    // searching ID
                    rMatrix.id = "matrix" + MBox.ProjectIdentifier.ToString();

                    // searching data source name (database)
                    IBoxModule[] db_names = BoxesHelper.ListAncestBoxesWithID(MBox, "DataMiningCommon.Database");
                    if (db_names.GetLength(0) != 1)  // searched more than one data source or neither one
                        throw new System.Exception("found " + db_names.GetLength(0).ToString() + " databases");
                    rMatrix.db_name = (db_names[0].GetPropertyOther("DatabaseName") as StringT).stringValue;

                    // searching data matrix name
                    rMatrix.matrix_name = MBox.GetPropertyString("Name");

                    // searching records count
                    rMatrix.record_count = MBox.GetPropertyLong("RecordCount").ToString();

                    // adding item to XML
                    resultString += rMatrix.ToXML();
                 
                }
                catch (System.Exception e)
                {
                    ErrStr += "Box ProjectIdentifier=" + MBox.ProjectIdentifier.ToString() + ": " + e.Message + "\n";
                }
            }

            #endregion


            resultString += "</active_list>";

#if (LADENI)
            // Kody - storing output to file "XMLData_matrixExample.xml" in directory 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLData_matrixExample.xml");

            if (ErrStr != "")
                MessageBox.Show("Chyby pri generating seznamu Boolskych cedent:\n" + ErrStr);
#endif

            return resultString;
        }
    }

    #region --- Records ---

    /// <summary>
    /// Record of one data matrix.
    /// </summary>
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

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <returns>XML string</returns>
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
