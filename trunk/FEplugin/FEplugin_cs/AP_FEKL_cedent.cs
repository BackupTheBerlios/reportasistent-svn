
//AP_FEKL_cedent.cs: implementation(file)
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
    // ==================== Active element "KL cedent" ================================

    /// <summary>
    /// Implementation of active element "KL cedent" (ID="KL_cedent")
    /// </summary>
    public class AP_FEKL_cedent
    {

        /// <summary>
        /// Returns XML string with all occurences of Active element "KL cedent".
        /// </summary>
        /// <param name="index">index of data source in FEplugin data sources table</param>
        /// <returns>XML string</returns>
        public static string getList(int index)
        {
            string resultString = ""; // result XML string
            string ErrStr = "";  // error reports
            int counterID = 0;

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

            string[] BoxTypes = { "LISpMinerTasks.KLTask", "LISpMinerTasks.SDKLTask" }; // types of boxes (tasks) for which are searched KL cedents

            // searching all boxes of tasks
            IBoxModule[] TaskBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, BoxTypes);

            #region Loop - processing of each tasks found

            foreach (IBoxModule box in TaskBoxes)
            {
                Rec_KL_cedent rKLCedent = new Rec_KL_cedent();
                counterID = 0;

                try
                {
                    // setting ID
                    rKLCedent.id = "klcdnt" + box.ProjectIdentifier.ToString() + "_";

                    // searching data source name (database)
                    IBoxModule[] db_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.Database");
                    if (db_names.GetLength(0) != 1)  // searched more than one data source or neither one
                        throw new System.Exception("found " + db_names.GetLength(0).ToString() + " databases");
                    rKLCedent.db_name = db_names[0].GetPropertyString("DatabaseName");

                    // searching data matrix name
                    IBoxModule[] matrix_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.DataMatrix");
                    if (matrix_names.GetLength(0) != 1)  // searched more than one data source or neither one
                        throw new System.Exception("found " + matrix_names.GetLength(0).ToString() + " data matrixes");
                    rKLCedent.matrix_name = matrix_names[0].GetPropertyString("Name");

                    // searching task name
                    rKLCedent.task_name = box.UserName;

                    // processing of several Task types
                    string id = rKLCedent.id;
                    switch (box.MadeInCreator.Identifier) // all available task types
                    {
                        case "LISpMinerTasks.KLTask":
                            rKLCedent.task_type = "KL Task";

                            // Antecedent
                            rKLCedent.id = id + counterID.ToString();
                            counterID++;
                            rKLCedent.cedent_type = "Row attributes";
                            resultString += getOneItemXML(box, rKLCedent, "AntecedentSetting");

                            // Succedent
                            rKLCedent.id = id + counterID.ToString();
                            counterID++;
                            rKLCedent.cedent_type = "Column attributes";
                            resultString += getOneItemXML(box, rKLCedent, "SuccedentSetting");
                            break;

                        case "LISpMinerTasks.SDKLTask":
                            rKLCedent.task_type = "SD-KL Task";

                            // Anecedent
                            rKLCedent.id = id + counterID.ToString();
                            counterID++;
                            //rKLCedent.cedent_type = CedentEnum.Antecedent.ToString();
                            rKLCedent.cedent_type = "Row attributes";
                            resultString += getOneItemXML(box, rKLCedent, "AntecedentSetting");

                            // Succedent
                            rKLCedent.id = id + counterID.ToString();
                            counterID++;
                            rKLCedent.cedent_type = "Column attributes";
                            //rKLCedent.cedent_type = CedentEnum.Succedent.ToString();
                            resultString += getOneItemXML(box, rKLCedent, "SuccedentSetting");
                            break;
                    }


                }
                catch (System.Exception e)
                {
                    ErrStr += "Box ProjectIdentifier=" + box.ProjectIdentifier.ToString() + ": " + e.Message + "\n";
                }
            }

            #endregion

            // root element
            resultString += "</active_list>";

#if (LADENI)
            // Kody - storing output to file "XMLKL_cedentExample.xml" in directory 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLKL_cedentExample.xml");

            if (ErrStr != "") // LADICI
                MessageBox.Show("Chyby pri generating seznamu KL cedent:\n" + ErrStr);
#endif

            return resultString;
        }

        /// <summary>
        /// generates one cedent to XML string
        /// </summary>
        /// <param name="subcedents">boxes with subcedents</param>
        /// <returns>XML string</returns>
        private static string getOneCedentXML(IBoxModule[] subcedents)
        {
            string XML = "";

            #region Loop - processing of each partial cedent

            foreach (IBoxModule box in subcedents)  // must be boxes with ID = "DataMiningCommon.CategorialPartialCedentSetting"
            {
                Rec_sub_KL_cedent rSKLC = new Rec_sub_KL_cedent();
                // setting attribute "name"
                rSKLC.name = box.UserName;
                // setting attribute "length"
                rSKLC.length = box.GetPropertyLong("MinLen").ToString() + " - " + box.GetPropertyLong("MaxLen").ToString();
                
                // searching each KL literal (= attributes!)
                string[] AttrIDs = { "DataMiningCommon.Attributes.Attribute",
                                         "DataMiningCommon.Attributes.EquifrequencyIntervalsAttribute",
                                         "DataMiningCommon.Attributes.EquidistantIntervalsAttribute",
                                         "DataMiningCommon.Attributes.EachValueOneCategoryAttribute" };
                IBoxModule[] attributes = BoxesHelper.ListDirectAncestBoxesWithID(box, AttrIDs);
                
                // setting attribute "literal_cnt" (literals count)
                rSKLC.literal_cnt = attributes.Length;
                List<Rec_KL_literal> rLiterals = new List<Rec_KL_literal>();

                #region Loop - processing of each KL-literal (attribute)

                foreach (IBoxModule attrBox in attributes)
                {
                    Rec_KL_literal rLiteral = new Rec_KL_literal();
                    // setting "underlying_attribute"
                    rLiteral.underlying_attribute = attrBox.GetPropertyString("NameInLiterals");
                    // setting "category_cnt"
                    rLiteral.category_cnt = attrBox.GetPropertyLong("CountOfCategories");
                    rLiterals.Add(rLiteral);
                }
                #endregion
                // adding cedent to XML string
                XML += rSKLC.ToXML(rLiterals);
            }
            #endregion

            return XML;
        }

        /// <summary>
        /// generates one cedent to XML string
        /// </summary>
        /// <param name="box">cedent box</param>
        /// <param name="rKLCedent">cedent record</param>
        /// <param name="CedentType">cedent type</param>
        /// <returns>XML string</returns>
        private static string getOneItemXML(IBoxModule box, Rec_KL_cedent rKLCedent, string CedentType)
        {
            string resultStr = "";
            IBoxModule[] SubCedents = box.GetConnections(CedentType);
            
            rKLCedent.sub_cedent_cnt = SubCedents.Length;
            // adding KL cedent to XML
            if (rKLCedent.sub_cedent_cnt > 0)
                resultStr = rKLCedent.ToXML(getOneCedentXML(SubCedents));

            return resultStr;
        }
    }

    #region --- Records ---

    /// <summary>
    /// Record of one KL cedent.
    /// </summary>
    public class Rec_KL_cedent
    {
        #region DATA

        public string id = "";
        public string db_name="unknown";
        public string matrix_name = "unknown";
        public string task_name = "unknown";
        public string task_type = "unknown";
        public string cedent_type = "unknown";
        public long sub_cedent_cnt = 0;
        #endregion

        #region METHODS

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <returns>XML string</returns>
        public string ToXML()
        {
            string XML = "";
            db_name = XMLHelper.replaceXMLsign(db_name);
            matrix_name = XMLHelper.replaceXMLsign(matrix_name);
            task_name = XMLHelper.replaceXMLsign(task_name);
            task_type = XMLHelper.replaceXMLsign(task_type);
            cedent_type = XMLHelper.replaceXMLsign(cedent_type);

            XML += "<KL_cedent id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" task_name=\"" + task_name + "\" task_type=\"" + task_type +
                   "\" cedent_type=\"" + cedent_type +
                   "\" sub_cedent_cnt=\"" + sub_cedent_cnt.ToString() + "\"/>";
            return XML;
        }

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <param name="SubelementsXMLstring">XML string with generated subelements (content of element)</param>
        /// <returns>XML string</returns>
        public string ToXML(string SubelementsXMLstring)
        {
            string XML = "";
            db_name = XMLHelper.replaceXMLsign(db_name);
            matrix_name = XMLHelper.replaceXMLsign(matrix_name);
            task_name = XMLHelper.replaceXMLsign(task_name);
            task_type = XMLHelper.replaceXMLsign(task_type);
            cedent_type = XMLHelper.replaceXMLsign(cedent_type);

            if (String.IsNullOrEmpty(SubelementsXMLstring))
            {
                XML += "<KL_cedent id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                       "\" task_name=\"" + task_name + "\" task_type=\"" + task_type +
                       "\" cedent_type=\"" + cedent_type +
                       "\" sub_cedent_cnt=\"" + sub_cedent_cnt.ToString() + "\"/>";
            }
            else
            {
                XML += "<KL_cedent id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                       "\" task_name=\"" + task_name + "\" task_type=\"" + task_type +
                       "\" cedent_type=\"" + cedent_type +
                       "\" sub_cedent_cnt=\"" + sub_cedent_cnt.ToString() + "\">";
                // inserting XML string - element content
                XML += SubelementsXMLstring + "</KL_cedent>";
            }

            return XML;
        }
        #endregion
    }

    /// <summary>
    /// Record of one KL subcedent.
    /// </summary>
    public class Rec_sub_KL_cedent
    {
        #region DATA

        public string name = "unknown";
        public long literal_cnt = 0;
        public string length = "unknown";
        #endregion

        #region METHODS

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <returns>XML string</returns>
        public string ToXML()
        {
            string XML = "";
            length = XMLHelper.replaceXMLsign(length);
            name = XMLHelper.replaceXMLsign(name);

            XML += "<sub_KL_cedent name=\"" + name + "\" literal_cnt=\"" + literal_cnt.ToString() +
                   "\" length=\"" + length + "\"/>";
            return XML;
        }

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <param name="KL_Literals">list of KL literals (subelements)</param>
        /// <returns>XML string</returns>
        public string ToXML(List<Rec_KL_literal> KL_Literals)
        {
            string XML = "";
            length = XMLHelper.replaceXMLsign(length);
            name = XMLHelper.replaceXMLsign(name);

            XML += "<sub_KL_cedent name=\"" + name + "\" literal_cnt=\"" + literal_cnt.ToString() +
                   "\" length=\"" + length + "\">";

            // adding each subelement - literal
            foreach (Rec_KL_literal Lit in KL_Literals)
                XML += Lit.ToXML();

            XML += "</sub_KL_cedent>";
            return XML;
        }
        #endregion
    }

    /// <summary>
    /// Record of one KL literal.
    /// </summary>
    public class Rec_KL_literal
    {
        #region DATA

        public string underlying_attribute = "unknown";
        public long category_cnt = 0;
        #endregion

        #region METHODS

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <returns>XML string</returns>
        public string ToXML()
        {

            string XML = "";
            underlying_attribute = XMLHelper.replaceXMLsign(underlying_attribute);

            XML += "<KL_literal underlying_attribute=\"" + underlying_attribute +
                   "\" category_cnt=\"" + category_cnt.ToString() + "\"/>";
            return XML;
        }
        #endregion
    }

    #endregion

}

