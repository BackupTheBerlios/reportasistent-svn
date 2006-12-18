
//AP_FECategory.cs: implementation(file)
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
    // ==================== Active element "Category" ================================
    /// <summary>
    /// Implementation of active element "Category" (ID="category")
    /// </summary>
    public class AP_FECategory
    {
        /// <summary>
        /// Returns XML string with all occurences of Active element "Category".
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


            // processing of each box - searching all category

            #region   searching and processing of each boxes of attributes (DataMiningCommon.Attributes.Attribute)

            IBoxModule[] AttrBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, "DataMiningCommon.Attributes.Attribute");

            string db_name="unknown";
            string matrix_name = "unknown";
            string attr_name = "unknown";
            int cat_id_counter = 0;

            // processing of each box - searching all category
            foreach (IBoxModule ABox in AttrBoxes)
            {
                try
                {
                    List<Rec_category> rCats = new List<Rec_category>();  // seznam vsech category of given attribute
                    cat_id_counter = 1;

                    // searching name of attribute (in literal)
                    attr_name = ABox.GetPropertyString("NameInLiterals");

                    // searching data source name (database)
                    IBoxModule[] db_names = BoxesHelper.ListAncestBoxesWithID(ABox, "DataMiningCommon.Database");
                    if (db_names.GetLength(0) != 1)  // searched more than one data source or neither one
                        throw new System.Exception("found " + db_names.GetLength(0).ToString() + " databases");
                    db_name = (db_names[0].GetPropertyOther("DatabaseName") as StringT).stringValue;

                    // searching data matrix name
                    IBoxModule[] matrix_names = BoxesHelper.ListAncestBoxesWithID(ABox, "DataMiningCommon.DataMatrix");
                    if (matrix_names.GetLength(0) != 1)  // searched more than one data source or neither one
                        throw new System.Exception("found " + matrix_names.GetLength(0).ToString() + " data matrixes");
                    matrix_name = (matrix_names[0].GetPropertyOther("Name") as StringT).stringValue;



                    // searching list of categories of given attribute
                    List<Rec_ctgr> cat_list = new List<Rec_ctgr>(); // list of categories
                    CategoriesStruct cat_str = (ABox.GetPropertyOther("Categories") as CategoriesT).categoriesValue;

                    #region processing of category type of Interval

                    // long intervals
                    foreach (string key in cat_str.longIntervals.Keys)
                    {
                        Rec_category rCat = new Rec_category();
                        rCat.id = "cat" + ABox.ProjectIdentifier.ToString() + "_" + cat_id_counter.ToString();
                        cat_id_counter++;
                        rCat.db_name = db_name;
                        rCat.matrix_name = matrix_name;
                        rCat.attr_name = attr_name;
                        rCat.ctgr_name = key;
                        rCat.ctgr_type = "Interval";
                        rCat.ctgr_freq = "N/A";     // TODO: if possible
                        rCat.bool_type = "No boolean"; // TODO: What is this?
                        rCat.def_length = cat_str.longIntervals[key].GetLength(0);

                        List<Rec_ctgr_def> ctgr_defs = new List<Rec_ctgr_def>();
                        foreach (LongIntervalStruct lis in cat_str.longIntervals[key])
                        {
                            Rec_ctgr_def ctgr_def = new Rec_ctgr_def();
                            switch (lis.leftBoundType)
                            {
                                case BoundaryEnum.Infinity:
                                    ctgr_def.definition += "(-inf";
                                    break;
                                case BoundaryEnum.Round:
                                    ctgr_def.definition += "(";
                                    break;
                                case BoundaryEnum.Sharp:
                                    ctgr_def.definition += "<";
                                    break;
                            }
                            if (lis.leftBoundType != BoundaryEnum.Infinity)
                                ctgr_def.definition += lis.leftBound.ToString() + ";";
                            if (lis.rightBoundType != BoundaryEnum.Infinity)
                                ctgr_def.definition += lis.rightBound.ToString();
                            switch (lis.rightBoundType)
                            {
                                case BoundaryEnum.Infinity:
                                    ctgr_def.definition += "+inf)";
                                    break;
                                case BoundaryEnum.Round:
                                    ctgr_def.definition += ")";
                                    break;
                                case BoundaryEnum.Sharp:
                                    ctgr_def.definition += ">";
                                    break;
                            }
                            ctgr_defs.Add(ctgr_def);
                        }
                        // Generating of one category to XML
                        string OneCatString = "";
                        if (ctgr_defs.Count == 0)
                            OneCatString += rCat.ToXML();
                        else
                            OneCatString += rCat.ToXML(ctgr_defs);

                        resultString += OneCatString;

                    }
                    // float intervals
                    foreach (string key in cat_str.floatIntervals.Keys)
                    {
                        Rec_category rCat = new Rec_category();
                        rCat.id = "cat" + ABox.ProjectIdentifier.ToString() + "_" + cat_id_counter.ToString();
                        cat_id_counter++;
                        rCat.db_name = db_name;
                        rCat.matrix_name = matrix_name;
                        rCat.attr_name = attr_name;
                        rCat.ctgr_name = key;
                        rCat.ctgr_type = "Interval";
                        rCat.ctgr_freq = "N/A";     // TODO: if possible
                        rCat.bool_type = "No boolean"; // TODO: What is this?
                        rCat.def_length = cat_str.floatIntervals[key].GetLength(0);

                        List<Rec_ctgr_def> ctgr_defs = new List<Rec_ctgr_def>();
                        foreach (FloatIntervalStruct fis in cat_str.floatIntervals[key])
                        {
                            Rec_ctgr_def ctgr_def = new Rec_ctgr_def();
                            switch (fis.leftBoundType)
                            {
                                case BoundaryEnum.Infinity:
                                    ctgr_def.definition += "(-inf";
                                    break;
                                case BoundaryEnum.Round:
                                    ctgr_def.definition += "(";
                                    break;
                                case BoundaryEnum.Sharp:
                                    ctgr_def.definition += "<";
                                    break;
                            }
                            if (fis.leftBoundType != BoundaryEnum.Infinity)
                                ctgr_def.definition += fis.leftBound.ToString() + ";";
                            if (fis.rightBoundType != BoundaryEnum.Infinity)
                                ctgr_def.definition += fis.rightBound.ToString();
                            switch (fis.rightBoundType)
                            {
                                case BoundaryEnum.Infinity:
                                    ctgr_def.definition += "+inf)";
                                    break;
                                case BoundaryEnum.Round:
                                    ctgr_def.definition += ")";
                                    break;
                                case BoundaryEnum.Sharp:
                                    ctgr_def.definition += ">";
                                    break;
                            }
                            ctgr_defs.Add(ctgr_def);
                        }
                        // Generating of one category to XML
                        string OneCatString = "";
                        if (ctgr_defs.Count == 0)
                            OneCatString += rCat.ToXML();
                        else
                            OneCatString += rCat.ToXML(ctgr_defs);

                        resultString += OneCatString;

                    }
                    //  date time intervals  
                    foreach (string key in cat_str.dateTimeIntervals.Keys)
                    {
                        Rec_category rCat = new Rec_category();
                        rCat.id = "cat" + ABox.ProjectIdentifier.ToString() + "_" + cat_id_counter.ToString();
                        cat_id_counter++;
                        rCat.db_name = db_name;
                        rCat.matrix_name = matrix_name;
                        rCat.attr_name = attr_name;
                        rCat.ctgr_name = key;
                        rCat.ctgr_type = "Interval";
                        rCat.ctgr_freq = "N/A";     // TODO: implement if possible
                        rCat.bool_type = "No boolean"; // TODO: what is this?
                        rCat.def_length = cat_str.floatIntervals[key].GetLength(0);

                        List<Rec_ctgr_def> ctgr_defs = new List<Rec_ctgr_def>();
                        foreach (DateTimeIntervalStruct dis in cat_str.dateTimeIntervals[key])
                        {
                            Rec_ctgr_def ctgr_def = new Rec_ctgr_def();
                            switch (dis.leftBoundType)
                            {
                                case BoundaryEnum.Infinity:
                                    ctgr_def.definition += "(-inf";
                                    break;
                                case BoundaryEnum.Round:
                                    ctgr_def.definition += "(";
                                    break;
                                case BoundaryEnum.Sharp:
                                    ctgr_def.definition += "<";
                                    break;
                            }
                            if (dis.leftBoundType != BoundaryEnum.Infinity)
                                ctgr_def.definition += dis.leftBound.ToString() + ";";
                            if (dis.rightBoundType != BoundaryEnum.Infinity)
                                ctgr_def.definition += dis.rightBound.ToString();
                            switch (dis.rightBoundType)
                            {
                                case BoundaryEnum.Infinity:
                                    ctgr_def.definition += "+inf)";
                                    break;
                                case BoundaryEnum.Round:
                                    ctgr_def.definition += ")";
                                    break;
                                case BoundaryEnum.Sharp:
                                    ctgr_def.definition += ">";
                                    break;
                            }
                            ctgr_defs.Add(ctgr_def);
                        }
                        // Generating of one category to XML
                        string OneCatString = "";
                        if (ctgr_defs.Count == 0)
                            OneCatString += rCat.ToXML();
                        else
                            OneCatString += rCat.ToXML(ctgr_defs);

                        resultString += OneCatString;
                    }
                    #endregion

                    // enums
                    foreach (string key in cat_str.enums.Keys)
                    {
                        Rec_category rCat = new Rec_category();
                        rCat.id = "cat" + ABox.ProjectIdentifier.ToString() + "_" + cat_id_counter.ToString();
                        cat_id_counter++;
                        rCat.db_name = db_name;
                        rCat.matrix_name = matrix_name;
                        rCat.attr_name = attr_name;
                        rCat.ctgr_name = key;
                        rCat.ctgr_type = "Enumeration";
                        rCat.ctgr_freq = "N/A";     // TODO: if possible
                        rCat.bool_type = "No boolean"; // TODO: What is this?
                        rCat.def_length = cat_str.enums[key].GetLength(0);

                        List<Rec_ctgr_def> ctgr_defs = new List<Rec_ctgr_def>();
                        foreach (string enu in cat_str.enums[key])
                        {
                            Rec_ctgr_def ctgr_def = new Rec_ctgr_def();
                            ctgr_def.definition = enu;
                            ctgr_defs.Add(ctgr_def);
                        }
                        // Generating of one category to XML
                        string OneCatString = "";
                        if (ctgr_defs.Count == 0)
                            OneCatString += rCat.ToXML();
                        else
                            OneCatString += rCat.ToXML(ctgr_defs);

                        resultString += OneCatString;
                    }
                }
                catch (System.Exception e)
                {
                    ErrStr += "Box ProjectIdentifier=" + ABox.ProjectIdentifier.ToString() + ": " + e.Message + "\n";
                }
            }

            #endregion


            resultString += "</active_list>";

#if (LADENI)
            // Kody - storing output to file "XMLAttrExample.xml" in directory 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLCatExample.xml");

            if (ErrStr != "") // LADICI
                MessageBox.Show("Chyby pri generating seznamu Boolskych cedent:\n" + ErrStr);
#endif

            return resultString;
        }
    }

    #region --- Records ---

    /// <summary>
    /// Record of one category.
    /// </summary>
    public class Rec_category
    {
        #region DATA

        public string id = "";
        public string db_name="unknown";
        public string matrix_name = "unknown";
        public string attr_name = "unknown";
        public string ctgr_name = "unknown";
        public string ctgr_type = "unknown";
        public string ctgr_freq = "unknown";
        public string bool_type = "unknown";
        public long def_length = 0;

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
            attr_name = XMLHelper.replaceXMLsign(attr_name);
            ctgr_name = XMLHelper.replaceXMLsign(ctgr_name);
            ctgr_type = XMLHelper.replaceXMLsign(ctgr_type);
            ctgr_freq = XMLHelper.replaceXMLsign(ctgr_freq);
            bool_type = XMLHelper.replaceXMLsign(bool_type);
            
            string XML = "";

            XML += "<category id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" attr_name=\"" + attr_name + "\" ctgr_name=\"" + ctgr_name + "\" ctgr_type=\"" + ctgr_type +
                   "\" ctgr_freq=\"" + ctgr_freq + "\" bool_type=\"" + bool_type +
                   "\" def_length=\"" + def_length.ToString() + "\"/>";
            return XML;
        }

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <param name="Cat_defs">list of definitions of categories</param>
        /// <returns>XML string</returns>
        public string ToXML(List<Rec_ctgr_def> Cat_defs)
        {
            id = XMLHelper.replaceXMLsign(id);
            db_name = XMLHelper.replaceXMLsign(db_name);
            matrix_name = XMLHelper.replaceXMLsign(matrix_name);
            attr_name = XMLHelper.replaceXMLsign(attr_name);
            ctgr_name = XMLHelper.replaceXMLsign(ctgr_name);
            ctgr_type = XMLHelper.replaceXMLsign(ctgr_type);
            ctgr_freq = XMLHelper.replaceXMLsign(ctgr_freq);
            bool_type = XMLHelper.replaceXMLsign(bool_type);

            string XML = "";

            XML += "<category id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" attr_name=\"" + attr_name + "\" ctgr_name=\"" + ctgr_name + "\" ctgr_type=\"" + ctgr_type +
                   "\" ctgr_freq=\"" + ctgr_freq + "\" bool_type=\"" + bool_type +
                   "\" def_length=\"" + def_length.ToString() + "\">";
            // generating each subelement - ctgr_def
            if (Cat_defs.Count > 0)
            {
                foreach (Rec_ctgr_def ctgr_def in Cat_defs)
                    XML += ctgr_def.ToXML();
            }

            XML += "</category>";
            return XML;
        }
        #endregion
    }

    /// <summary>
    /// Record of one category definition.
    /// </summary>
    public class Rec_ctgr_def
    {
        #region DATA

        public string definition = "unknown";

        #endregion

        #region METHODS

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <returns>XML string</returns>
        public string ToXML()
        {
            definition = XMLHelper.replaceXMLsign(definition);
            string XML = "";
            XML += "<ctgr_def definition=\"" + definition + "\"/>";
            return XML;
        }
        #endregion
    }
    
#endregion
}
