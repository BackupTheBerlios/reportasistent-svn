
//AP_FECF_cedent.cs: implementation(file)
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
    // ==================== Active element "CF cedent" ================================

    /// <summary>
    /// Implementation of active element "CF cedent" (ID="CF_cedent")
    /// </summary>
    public class AP_FECF_cedent
    {
        /// <summary>
        /// Returns XML string with all occurences of Active element "CF cedent".
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

            string[] BoxTypes = { "LISpMinerTasks.CFTask", "LISpMinerTasks.SDCFTask" }; // typy boxes (uloh), pro ktere se hledaji CFske cedents

            // searching all boxes of tasks
            IBoxModule[] TaskBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, BoxTypes);

            #region Loop - processing of each task found

            foreach (IBoxModule box in TaskBoxes)
            {
                Rec_CF_cedent rCFCedent = new Rec_CF_cedent();
                counterID = 0;

                try
                {
                    // setting ID
                    rCFCedent.id = "cfcdnt" + box.ProjectIdentifier.ToString() + "_";

                    // searching data source name (database)
                    IBoxModule[] db_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.Database");
                    if (db_names.GetLength(0) != 1)  // searched more than one data source or neither one
                        throw new System.Exception("found " + db_names.GetLength(0).ToString() + " databases");
                    rCFCedent.db_name = db_names[0].GetPropertyString("DatabaseName");

                    // searching data matrix name
                    IBoxModule[] matrix_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.DataMatrix");
                    if (matrix_names.GetLength(0) != 1)  // searched more than one data source or neither one
                        throw new System.Exception("found " + matrix_names.GetLength(0).ToString() + " data matrixes");
                    rCFCedent.matrix_name = matrix_names[0].GetPropertyString("Name");

                    // searching task name
                    rCFCedent.task_name = box.UserName;

                    // processing of several type of Task
                    string id = rCFCedent.id;
                    switch (box.MadeInCreator.Identifier) // all available task types
                    {
                        case "LISpMinerTasks.CFTask":
                            rCFCedent.task_type = "CF Task";

                            // Antecedent
                            rCFCedent.id = id + counterID.ToString();
                            counterID++;
                            // Kodym - choose one of following possibilities (ZJISTI)
                            //rCFCedent.cedent_type = CedentEnum.Antecedent.ToString();
                            rCFCedent.cedent_type = "Attributes";
                            resultString += getOneItemXML(box, rCFCedent, "AntecedentSetting");
                            break;

                        case "LISpMinerTasks.SDCFTask":
                            rCFCedent.task_type = "SD-CF Task";

                            // Anecedent
                            rCFCedent.id = id + counterID.ToString();
                            counterID++;
                            // Kodym - choose one of following possibilities (ZJISTI)
                            //rCFCedent.cedent_type = CedentEnum.Antecedent.ToString();
                            rCFCedent.cedent_type = "Attributes";
                            resultString += getOneItemXML(box, rCFCedent, "AntecedentSetting");
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
            // Kody - storing output to file "XMLCF_cedentExample.xml" in directory 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLCF_cedentExample.xml");

            if (ErrStr != "") // LADICI
                MessageBox.Show("Chyby pri generating seznamu CF cedent:\n" + ErrStr);
#endif

            return resultString;
        }

        /// <summary>
        /// Generates one CF cedent to XML string.
        /// </summary>
        /// <param name="subcedents">boxes with parcial cedents</param>
        /// <returns>XML string</returns>
        private static string getOneCedentXML(IBoxModule[] subcedents)
        {
            string XML = "";

            #region Loop - processing of each parcial cedent

            foreach (IBoxModule box in subcedents)  // must be boxes with ID = "DataMiningCommon.CategorialPartialCedentSetting"
            {
                Rec_sub_CF_cedent rSCFC = new Rec_sub_CF_cedent();
                // setting attribute "name"
                rSCFC.name = box.UserName;
                // setting attribute "length"
                rSCFC.length = box.GetPropertyLong("MinLen").ToString() + " - " + box.GetPropertyLong("MaxLen").ToString();
                
                // searching each CF literal (= attribute!)
                string[] AttrIDs = { "DataMiningCommon.Attributes.Attribute",
                                         "DataMiningCommon.Attributes.EquifrequencyIntervalsAttribute",
                                         "DataMiningCommon.Attributes.EquidistantIntervalsAttribute",
                                         "DataMiningCommon.Attributes.EachValueOneCategoryAttribute" };
                IBoxModule[] attributes = BoxesHelper.ListDirectAncestBoxesWithID(box, AttrIDs);

                // setting attribute "literal_cnt" (literals count)
                rSCFC.literal_cnt = attributes.Length;
                List<Rec_CF_literal> rLiterals = new List<Rec_CF_literal>();

                #region Loop - processing of each CF-literal (attribute)

                foreach (IBoxModule attrBox in attributes)
                {
                    Rec_CF_literal rLiteral = new Rec_CF_literal();
                    // setting attribute "underlying_attribute"
                    rLiteral.underlying_attribute = attrBox.GetPropertyString("NameInLiterals");
                    // setting attribute "category_cnt"
                    rLiteral.category_cnt = attrBox.GetPropertyLong("CountOfCategories");
                    rLiterals.Add(rLiteral);
                }
                #endregion

                // adding parcial cedent (and its literals) to result XML string
                XML += rSCFC.ToXML(rLiterals);
            }
            #endregion

            return XML;
        }

        /// <summary>
        /// generates one item (parcial cedent) to XML string
        /// </summary>
        /// <param name="box">box of parcial cedent</param>
        /// <param name="rCFCedent">record with CF cedent</param>
        /// <param name="CedentType">cedent type</param>
        /// <returns>XML string</returns>
        private static string getOneItemXML(IBoxModule box, Rec_CF_cedent rCFCedent, string CedentType)
        {
            string resultStr = "";
            IBoxModule[] SubCedents = box.GetConnections(CedentType);
            // setting attribute "sub_cedent_cnt" (count of parcial cedents)
            rCFCedent.sub_cedent_cnt = SubCedents.Length;
            // adding CF cedent to XML
            if (rCFCedent.sub_cedent_cnt > 0)
                resultStr = rCFCedent.ToXML(getOneCedentXML(SubCedents));

            return resultStr;
        }
    }

    #region --- Records ---

    /// <summary>
    /// Record of one CF cedent.
    /// </summary>
    public class Rec_CF_cedent
    {
        #region DATA

        public string id = "";
        public string db_name="unknown";
        public string matrix_name = "unknown";
        public string task_name = "unknown";
        public string task_type = "";
        public string cedent_type = "";
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

            XML += "<CF_cedent id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
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
                XML += "<CF_cedent id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                       "\" task_name=\"" + task_name + "\" task_type=\"" + task_type +
                       "\" cedent_type=\"" + cedent_type +
                       "\" sub_cedent_cnt=\"" + sub_cedent_cnt.ToString() + "\"/>";
            }
            else
            {
                XML += "<CF_cedent id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                       "\" task_name=\"" + task_name + "\" task_type=\"" + task_type +
                       "\" cedent_type=\"" + cedent_type +
                       "\" sub_cedent_cnt=\"" + sub_cedent_cnt.ToString() + "\">";
                // inserting XML string - element content
                XML += SubelementsXMLstring + "</CF_cedent>";
            }

            return XML;
        }
        #endregion
    }

    /// <summary>
    /// Record of one CF subcedent.
    /// </summary>
    public class Rec_sub_CF_cedent
    {
        #region DATA

        public string name = "unknown";
        public long literal_cnt = 0;
        public string length = "";
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

            XML += "<sub_CF_cedent name=\"" + name + "\" literal_cnt=\"" + literal_cnt.ToString() +
                   "\" length=\"" + length + "\"/>";
            return XML;
        }

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <param name="CF_Literals">list of CF literals (subelements)</param>
        /// <returns>XML string</returns>
        public string ToXML(List<Rec_CF_literal> CF_Literals)
        {
            string XML = "";
            length = XMLHelper.replaceXMLsign(length);
            name = XMLHelper.replaceXMLsign(name);

            XML += "<sub_CF_cedent name=\"" + name + "\" literal_cnt=\"" + literal_cnt.ToString() +
                   "\" length=\"" + length + "\">";

            // adding each subelement - literal
            foreach (Rec_CF_literal Lit in CF_Literals)
                XML += Lit.ToXML();

            XML += "</sub_CF_cedent>";
            return XML;
        }
        #endregion
    }

    /// <summary>
    /// Record of one CF literal.
    /// </summary>
    public class Rec_CF_literal
    {
        #region DATA

        public string underlying_attribute = "";
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

            XML += "<CF_literal underlying_attribute=\"" + underlying_attribute +
                   "\" category_cnt=\"" + category_cnt.ToString() + "\"/>";
            return XML;
        }
        #endregion
    }

    #endregion

}

