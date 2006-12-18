
//AP_FEQuantifiers.cs: implementation(file)
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

    // ==================== Active element "Quantifier" ================================

    /// <summary>
    /// Implementation of active element "Quantifier" (ID="quantifier")
    /// </summary>
    public class AP_FEQuantifier
    {
        /// <summary>
        /// Returns XML string with all occurences of Active element "Quantifier".
        /// </summary>
        /// <param name="index">index of data source in FEplugin data sources table</param>
        /// <returns>XML string</returns>
        public static string getList(int index)
        {
            string resultString = ""; // result XML string
            string ErrStr = ""; // error report

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

            List<TaskTypeStruct> TypyTask = new List<TaskTypeStruct>();
            TypyTask.Add(new TaskTypeStruct("LISpMinerTasks.FFTTask", "FFTQuantifier", "4FT"));
            TypyTask.Add(new TaskTypeStruct("LISpMinerTasks.SDFFTTask", "SDFFTQuantifier", "SD-4FT"));
            TypyTask.Add(new TaskTypeStruct("LISpMinerTasks.KLTask", "KLQuantifier", "KL"));
            TypyTask.Add(new TaskTypeStruct("LISpMinerTasks.SDKLTask", "SDKLQuantifier", "SD-KL"));
            TypyTask.Add(new TaskTypeStruct("LISpMinerTasks.CFTask", "CFQuantifier", "CF"));
            TypyTask.Add(new TaskTypeStruct("LISpMinerTasks.SDCFTask", "SDCFQuantifier", "SD-CF"));

            #region Loop over all Task types

            foreach (TaskTypeStruct TTS in TypyTask)
            {
                // searching all Task boxes with given type
                IBoxModule[] TaskBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, TTS.TaskBoxType);
                #region Loop - processing of each Task with given type

                foreach (IBoxModule box in TaskBoxes)
                {
                    // record of basic quantifier
                    Rec_quantifier rQuant = new Rec_quantifier();

                    // fillinf ID of quantifier
                    string id = "quant" + box.ProjectIdentifier;

                    try
                    {
                        // searching data source name (database) - not mandatory!
                        IBoxModule[] db_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.Database");
                        if (db_names.GetLength(0) == 1)  // searched more than one data source or neither one
                            rQuant.db_name = (db_names[0].GetPropertyOther("DatabaseName") as StringT).stringValue;

                        // searching data matrix name - not mandatory!
                        IBoxModule[] matrix_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.DataMatrix");
                        if (matrix_names.GetLength(0) == 1)  // searched more than one data source or neither one
                            rQuant.matrix_name = (matrix_names[0].GetPropertyOther("Name") as StringT).stringValue;

                        // searching task name
                        rQuant.task_name = box.UserName;

                        // filling the type of quantifier (task)
                        rQuant.task_type = TTS.TypeString;

                        // searching all boxes - basic quantifiers of given Task
                        IBoxModule[] BasicQuantsBoxes = box.GetConnections(TTS.QuantSocketName);

                        #region Loop - over all basic quantifiers

                        int bq_num = 0;  // helping variable - due to generating ID
                        foreach (IBoxModule BQB in BasicQuantsBoxes)
                        {
                            Rec_quantifier rQuant1 = rQuant;

                            // setting ID
                            rQuant1.id = id + "_" + bq_num.ToString();
                            bq_num++;

                            // filling the item "name"
                            rQuant1.name = BQB.UserName;

                            // filling the item "type"
                            if (BQB.MadeInCreator.Identifier.IndexOf("Functional") != -1)
                                rQuant1.type = "Functional";
                            else if (BQB.MadeInCreator.Identifier.IndexOf("Aggregation") != -1)
                                rQuant1.type = "Aggregation";

                            // searching all items of basic quantifier and its values
                            List<Rec_quant_item> QItems = new List<Rec_quant_item>();

                            PropertyInfo[] PI = BQB.MadeInCreator.Properties;
                            foreach (PropertyInfo pi in PI)
                            {
                                // new item setting
                                Rec_quant_item item = new Rec_quant_item();
                                // filling the items
                                item.name = pi.name; // "name"

                                
                                if (pi.typeClassIceId.IndexOf("Double") != -1)
                                    item.value = BQB.GetPropertyDouble(pi.name).ToString();
                                else if (pi.typeClassIceId.IndexOf("String") != -1)
                                    item.value = BQB.GetPropertyString(pi.name);
                                else if (pi.typeClassIceId.IndexOf("Float") != -1)
                                    item.value = BQB.GetPropertyFloat(pi.name).ToString();
                                else if (pi.typeClassIceId.IndexOf("Int") != -1)
                                    item.value = BQB.GetPropertyInt(pi.name).ToString();
                                else if (pi.typeClassIceId.IndexOf("Long") != -1)
                                    item.value = BQB.GetPropertyLong(pi.name).ToString();
                                else if (pi.typeClassIceId.IndexOf("Date") != -1)
                                    item.value = BQB.GetPropertyDate(pi.name).ToString();
                                else if (pi.typeClassIceId.IndexOf("Time") != -1)
                                    item.value = BQB.GetPropertyTime(pi.name).ToString();
                                else if (pi.typeClassIceId.IndexOf("Bool") != -1)
                                    item.value = BQB.GetPropertyBool(pi.name).ToString();

                                QItems.Add(item);
                            }

                        #endregion


                            // adding quantifier to XML
                            resultString += rQuant1.ToXML(QItems);
                        }
                    }
                    catch (System.Exception e)
                    {
                        ErrStr += "Box ProjectIdentifier=" + box.ProjectIdentifier.ToString() + ": " + e.Message + "\n";
                    }
                }
                #endregion

            }

            #endregion

            // root element
            resultString += "</active_list>";

#if (LADENI)
            // generating of error message:
            if (!String.IsNullOrEmpty(ErrStr))  // LADICI
                MessageBox.Show("Pri nacitani quantifier doslo k chybam:\n" + ErrStr, "Chyba", MessageBoxButtons.OK, MessageBoxIcon.Error);

            // Kody - storing output to file "XMLQuantExample.xml" in directory 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLQuantExample.xml");
#endif

            return resultString;
        }

        
        
        /// <summary>
        /// helping structure - all types of Task processed in loop in getList() and their items
        /// </summary>
        struct TaskTypeStruct
        {
            public string TaskBoxType;
            public string QuantSocketName;
            public string TypeString;

            public TaskTypeStruct(string TBT, string QSN, string TS)
            {
                TaskBoxType = TBT;
                QuantSocketName = QSN;
                TypeString = TS;
            }
        }
    }

    #region --- Records  ---

    /// <summary>
    /// Record for one basic quantifier
    /// </summary>
    public class Rec_quantifier
    {
        #region DATA
        public string id = "";    // ID quantifier
        public string db_name = "unknown";   // database name
        public string matrix_name = "unknown"; // data matrix name
        public string task_name = "unknown";   // task name
        public string task_type = "unknown";   // task type
        public string name = "unknown";   // name of (typ) basic quantifier
        public string type = "unknown";   // type of quantifier (4FT, KL, ... )
        
        
        
        #endregion

        #region METHODS

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <returns>XML string</returns>
        public string ToXML()
        {
            string XML = "";

            XML += "<quantifier id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" task_name=\"" + task_name + "\" task_type=\"" + task_type +
                   "\" name=\"" + name + "\" type=\"" + type +  "\"/>";
            return XML;
        }

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <param name="items">list of records with basic quantifiers</param>
        /// <returns>XML string</returns>
        public string ToXML(List<Rec_quant_item> items)
        {
            string XML = "";

            XML += "<quantifier id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" task_name=\"" + task_name + "\" task_type=\"" + task_type +
                   "\" name=\"" + name + "\" type=\"" + type + "\">";

            // generating subelements - all items
            foreach (Rec_quant_item item in items)
                XML += item.ToXML();
            
            XML += "</quantifier>";
            return XML;
        }

        #endregion
    }

    /// <summary>
    /// Record for one basic quantifier item (i.e. parameter and its value)
    /// </summary>
    public class Rec_quant_item
        {
        #region DATA

        /// <summary>
            /// Name of item of basic quantifier (i.e. parameter)
        /// </summary>
        public string name = "unknown"; 

        /// <summary>
        /// Value of item
        /// </summary>
        public string value = "unknown";
                
        #endregion

        #region METHODS

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <returns>XML string</returns>
        public string ToXML()
        {
            string XML = "";

            XML += "<quant_item name=\"" + name + "\" value=\"" + value + "\"/>";
            return XML;

        }
        #endregion
    }

    #endregion
}
