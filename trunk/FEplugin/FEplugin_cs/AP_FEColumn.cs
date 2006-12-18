
//AP_FEColumn.cs: implementation(file)
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
    // ==================== Active element "Column" (Column of data matrix) ================================
    
    /// <summary>
    /// Implementation of active element "Column" (ID="column")
    /// </summary>
    public class AP_FEColumn
    {
        /// <summary>
        /// Returns XML string with all occurences of Active element "Column".
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


            // processing of each box Column

            #region   searching a processing of each boxes Column (DataMiningCommon.Column)

            IBoxModule[] AttrBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, "DataMiningCommon.Column");

            
            // processing of each box Column
            foreach (IBoxModule ABox in AttrBoxes)
            {
                try
                {
                    Rec_column rColumn = new Rec_column(); // zaznam o novem sloupci

                    // searching ID
                    rColumn.id = "column" + ABox.ProjectIdentifier.ToString();

                    // searching data source name (database)
                    IBoxModule[] db_names = BoxesHelper.ListAncestBoxesWithID(ABox, "DataMiningCommon.Database");
                    if (db_names.GetLength(0) != 1)  // searched more than one data source or neither one
                        throw new System.Exception("found " + db_names.GetLength(0).ToString() + " databases");
                    rColumn.db_name = (db_names[0].GetPropertyOther("DatabaseName") as StringT).stringValue;

                    // searching data matrix name
                    IBoxModule[] matrix_names = BoxesHelper.ListAncestBoxesWithID(ABox, "DataMiningCommon.DataMatrix");
                    if (matrix_names.GetLength(0) != 1)  // searched more than one data source or neither one
                        throw new System.Exception("found " + matrix_names.GetLength(0).ToString() + " data matrixes");
                    rColumn.matrix_name = (matrix_names[0].GetPropertyOther("Name") as StringT).stringValue;

                    // searching name of column
                    rColumn.column_name = ABox.GetPropertyString("Name");

                    // searching type of values
                    rColumn.value_type = ABox.GetPropertyString("ValueSubType");

                    // searching Min
                    rColumn.min = ABox.GetPropertyString("ValueMin");

                    // searching Max
                    rColumn.max = ABox.GetPropertyString("ValueMax");

                    // searching Avg
                    rColumn.avg = ABox.GetPropertyString("ValueAverage");

                    // adding item to XML
                    resultString += rColumn.ToXML();
                 
                }
                catch (System.Exception e)
                {
                    ErrStr += "Box ProjectIdentifier=" + ABox.ProjectIdentifier.ToString() + ": " + e.Message + "\n";
                }
            }

            #endregion


            resultString += "</active_list>";

#if (LADENI)
            // Kody - storing output to file "XMLColumnExample.xml" in directory 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLColumnExample.xml");

            if (ErrStr != "")
                MessageBox.Show("Chyby pri generating seznamu Boolskych cedent:\n" + ErrStr);
#endif

            return resultString;
        }
    }

    #region --- Records ---

    /// <summary>
    /// Record of one column (of data matrix).
    /// </summary>
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

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <returns>XML string</returns>
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
