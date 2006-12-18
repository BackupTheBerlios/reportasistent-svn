
//AP_FEAttribute.cs: implementation(file)
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
    // ==================== Active element "Attribute" ================================

    /// <summary>
    /// Implementation of active element "Attribute" (ID="attribute")
    /// </summary>
    public class AP_FEAttribute
    {
        /// <summary>
        /// Returns XML string with all occurences of Active element "Attribute".
        /// </summary>
        /// <param name="index">index of data source in FEplugin data sources table</param>
        /// <returns>XML string</returns>
        public static string getList(int index)
        {
            string resultString = ""; // result XML string

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
            string ErrStr = ""; // error report


            #region  A) searching all boxes - Attributes (DataMiningCommon.Attributes.Attribute)

            IBoxModule[] AttrBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, "DataMiningCommon.Attributes.Attribute");

            // processing of each box - searching all Attributes
            foreach (IBoxModule ABox in AttrBoxes)
            {
                try
                {
                    Rec_attribute rAttr = new Rec_attribute();

                    // setting ID attribute
                    rAttr.id = "Attr" + ABox.ProjectIdentifier.ToString();

                    // searching name of literal
                    rAttr.attr_name = ABox.GetPropertyString("NameInLiterals");

                    // searching data source name (database)
                    IBoxModule[] db_names = BoxesHelper.ListAncestBoxesWithID(ABox, "DataMiningCommon.Database");
                    if (db_names.GetLength(0) != 1)  // searched more than one data source or neither one
                        throw new System.Exception("found " + db_names.GetLength(0).ToString() + " databases");
                    rAttr.db_name = (db_names[0].GetPropertyOther("DatabaseName") as StringT).stringValue;

                    // searching data matrix name
                    IBoxModule[] matrix_names = BoxesHelper.ListAncestBoxesWithID(ABox, "DataMiningCommon.DataMatrix");
                    if (matrix_names.GetLength(0) != 1)  // searched more than one data source or neither one
                        throw new System.Exception("found " + matrix_names.GetLength(0).ToString() + " data matrixes");
                    rAttr.matrix_name = (matrix_names[0].GetPropertyOther("Name") as StringT).stringValue;


                    // searching name of source column or manner of derivation
                    IBoxModule[] col_names = BoxesHelper.ListDirectAncestBoxesWithID(ABox, "DataMiningCommon.Column");
                    if (col_names.GetLength(0) != 1 && col_names.GetLength(0) != 0)  // incorrect number of source columns found
                        throw new System.Exception("found " + col_names.GetLength(0).ToString() + " zdrojovych sloupcu");
                    if (col_names.GetLength(0) == 1)
                        rAttr.creation = col_names[0].GetPropertyString("Name");

                    IBoxModule[] dercol_names = BoxesHelper.ListDirectAncestBoxesWithID(ABox, "DataMiningCommon.DerivedColumn");
                    if (dercol_names.GetLength(0) != 1 && dercol_names.GetLength(0) != 0)  // incorrect number of source columns found
                        throw new System.Exception("found " + dercol_names.GetLength(0).ToString() + " zdrojovych odvozenych sloupcu");
                    if (dercol_names.GetLength(0) == 1)
                        rAttr.creation = dercol_names[0].GetPropertyString("Formula");


                    // searching number of categories
                    rAttr.ctgr_count = ABox.GetPropertyLong("CountOfCategories");

                    // searching the category "missisng value"
                    string nul_cat = ABox.GetPropertyString("IncludeNullCategory");
                    List<Rec_missing_value> MisVal_list = new List<Rec_missing_value>();  // array of records with missing values
                    if (!String.IsNullOrEmpty(nul_cat))
                    {
                        Rec_missing_value MisVal = new Rec_missing_value();
                        MisVal.name = nul_cat;
                        MisVal_list.Add(MisVal);
                    }

                    // searching category names and their frequencies
                    List<Rec_ctgr> cat_list = new List<Rec_ctgr>(); // list of categories
                    CategoriesStruct cat_str = (ABox.GetPropertyOther("Categories") as CategoriesT).categoriesValue;

                    // long intervals
                    foreach (string key in cat_str.longIntervals.Keys)
                    {
                        Rec_ctgr new_li = new Rec_ctgr();
                        new_li.freq = "N/A";  // Not Available - TODO (if possible)
                        //KODY 27.11.2006 - not possible to gain attribute frequencies directly from Ferda. Can be resolved via creating CF task

                        new_li.name = key;
                        cat_list.Add(new_li);
                    }
                    // float intervals
                    foreach (string key in cat_str.floatIntervals.Keys)
                    {
                        Rec_ctgr new_li = new Rec_ctgr();
                        new_li.freq = "N/A";  // Not Available - TODO (if possible)
                        new_li.name = key;
                        cat_list.Add(new_li);
                    }
                    //  date time intervals
                    foreach (string key in cat_str.dateTimeIntervals.Keys)
                    {
                        Rec_ctgr new_li = new Rec_ctgr();
                        new_li.freq = "N/A";  // Not Available - TODO (if possible)
                        new_li.name = key;
                        cat_list.Add(new_li);
                    }
                    // enums
                    foreach (string key in cat_str.enums.Keys)
                    {
                        Rec_ctgr new_li = new Rec_ctgr();
                        new_li.freq = "N/A";  // Not Available - TODO (if possible)
                        new_li.name = key;
                        cat_list.Add(new_li);
                    }



                    #region Generating of one attribute to XML string

                    string oneAttrString = "";
                    // generating hypotheses to XML

                    if (MisVal_list.Count == 0 && cat_list.Count == 0)
                        oneAttrString += rAttr.ToXML();
                    else
                        oneAttrString += rAttr.ToXML(cat_list, MisVal_list);

                    resultString += oneAttrString;

                    #endregion
                }
                catch (System.Exception e)
                {
                    ErrStr += "Box ProjectIdentifier=" + ABox.ProjectIdentifier.ToString() + ": " + e.Message + "\n";
                }

            }

            #endregion

            // root element
            resultString += "</active_list>";

#if (LADENI)
            // generating of error message:
            if (!String.IsNullOrEmpty(ErrStr))
                MessageBox.Show("Pri nacitani category doslo k chybam:\n" + ErrStr, "Chyba", MessageBoxButtons.OK, MessageBoxIcon.Error);


            // Kody - storing output to file "XMLAttrExample.xml" in directory 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLAttrExample.xml");
#endif

            return resultString;
        }  // TODO: Attributes v krabickach EachValueOneCategory, Equidistant, Equifrequency???
    }
   
    #region --- Records ---

    /// <summary>
    /// Record of one Attribute.
    /// </summary>
    public class Rec_attribute
    {
        #region DATA

        public string id = "";
        public string db_name="unknown";
        public string matrix_name = "unknown";
        public string attr_name = "unknown";
        public string creation = "unknown";
        public long ctgr_count = 0;
        #endregion

        #region METHODS

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <returns>XML string</returns>
        public string ToXML()
        {
            string XML = "";

            XML += "<attribute id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" attr_name=\"" + attr_name + "\" creation=\"" + creation +
                   "\" ctgr_count=\"" + ctgr_count.ToString() + "\"/>";
            return XML;
        }

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <param name="Categories">list of attribute categories</param>
        /// <param name="MissingValue">list of missing value categories</param>
        /// <returns>XML string</returns>
        public string ToXML(List<Rec_ctgr> Categories, List<Rec_missing_value> MissingValue)
        {
            string XML = "";

            XML += "<attribute id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" attr_name=\"" + attr_name + "\" creation=\"" + creation +
                   "\" ctgr_count=\"" + ctgr_count.ToString() + "\">";
            // generating each subelement - ctgr
            if (Categories.Count > 0)
            {
                foreach (Rec_ctgr ctgr in Categories)
                    XML += ctgr.ToXML();
            }
            // generating each subelement - missing_value
            if (MissingValue.Count > 0)
            {
                foreach(Rec_missing_value mv in MissingValue)    
                    XML += mv.ToXML();
            }
            XML += "</attribute>";
            return XML;
        }
        #endregion
    }

    /// <summary>
    /// Record of one Attribute category.
    /// </summary>
    public class Rec_ctgr
    {
        #region DATA

        public string name = "unknown";
        public string freq = "unknown";
        #endregion

        #region METHODS

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <returns>XML string</returns>
        public string ToXML()
        {
            name = XMLHelper.replaceXMLsign(name);
            freq = XMLHelper.replaceXMLsign(freq);

            string XML = "";
            XML += "<ctgr name=\"" + name + "\" freq=\"" + freq + "\"/>";
            return XML;
        }
        #endregion
    }

    /// <summary>
    /// Record of missing value category.
    /// </summary>
    public class Rec_missing_value
    {
        #region DATA

        public string name = "unknown";
        #endregion

        #region METHODS

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <returns>XML string</returns>
        public string ToXML()
        {
            name = XMLHelper.replaceXMLsign(name);

            string XML = "";
            XML += "<missing_value name=\"" + name + "\"/>";
            return XML;
        }
        #endregion
    }

    #endregion

}
