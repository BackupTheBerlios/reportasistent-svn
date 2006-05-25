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
using Ferda.FrontEnd;

namespace FEplugin_cs
{
    // ==================== Aktivni prvek Kategorie ================================
    
    public class AP_FECategory
    {
        public static string getList(int index)
        {
            string resultString = ""; // vysledny XML string

            // nacteni DTD do resultStringu
            try { resultString = XMLHelper.loadDTD(); }
            catch (Exception e)
            {
                MessageBox.Show("Chyba pri nacitani DTD: " + e.Message);
                return resultString;
            }

            // korenovy element
            resultString += "<active_list>";


            // zpracovani kazde krabicky - ziskani z ni vsechny kategorie

            #region   nalezeni a zpracovani vsech krabicek Atributu (DataMiningCommon.Attributes.Attribute)

            IBoxModule[] AttrBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, "DataMiningCommon.Attributes.Attribute");

            string db_name = "";
            string matrix_name = "";
            string attr_name = "";
            int cat_id_counter = 0;

            // zpracovani kazde krabicky - ziskani z ni vsechny Kategorie
            foreach (IBoxModule ABox in AttrBoxes)
            {
                List<Rec_category> rCats = new List<Rec_category>();  // seznam vsech kategorii daneho atributu
                cat_id_counter = 1;

                // zjisteni jmena atributu (v literalu)
                attr_name = ABox.GetPropertyString("NameInLiterals");

                // nalezeni jmena datoveho zdroje (databaze)
                IBoxModule[] db_names = BoxesHelper.ListAncestBoxesWithID(ABox, "DataMiningCommon.Database");
                if (db_names.GetLength(0) != 1)  // byl nalezen pocet datovych zdroju ruzny od jedne
                    throw new System.Exception("bylo nalezeno " + db_names.GetLength(0).ToString() + " databazi");
                db_name = (db_names[0].GetPropertyOther("DatabaseName") as StringT).stringValue;

                // nalezeni jmena datove matice
                IBoxModule[] matrix_names = BoxesHelper.ListAncestBoxesWithID(ABox, "DataMiningCommon.DataMatrix");
                if (matrix_names.GetLength(0) != 1)  // byl nalezen pocet datovych matic ruzny od jedne
                    throw new System.Exception("bylo nalezeno " + matrix_names.GetLength(0).ToString() + " datovych matic");
                matrix_name = (matrix_names[0].GetPropertyOther("Name") as StringT).stringValue;



                // nalezeni seznamu kategorii daneho atributu
                List<Rec_ctgr> cat_list = new List<Rec_ctgr>(); // seznam kategorii
                CategoriesStruct cat_str = (ABox.GetPropertyOther("Categories") as CategoriesT).categoriesValue;

                #region Zpracovani kategorii typu Interval

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
                    rCat.ctgr_freq = "N/A";     // TODO: doimplementovat, pujde-li
                    rCat.bool_type = "No boolean"; // TODO: co to je? Dodelat.
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
                    // vypsani jedne kategorie do XML
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
                    rCat.ctgr_freq = "N/A";     // TODO: doimplementovat, pujde-li
                    rCat.bool_type = "No boolean"; // TODO: co to je? Dodelat.
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
                    // vypsani jedne kategorie do XML
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
                    rCat.ctgr_freq = "N/A";     // TODO: doimplementovat, pujde-li
                    rCat.bool_type = "No boolean"; // TODO: co to je? Dodelat.
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
                    // vypsani jedne kategorie do XML
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
                    rCat.ctgr_freq = "N/A";     // TODO: doimplementovat, pujde-li
                    rCat.bool_type = "No boolean"; // TODO: co to je? Dodelat.
                    rCat.def_length = cat_str.enums[key].GetLength(0);

                    List<Rec_ctgr_def> ctgr_defs = new List<Rec_ctgr_def>();
                    foreach (string enu in cat_str.enums[key])
                    {
                        Rec_ctgr_def ctgr_def = new Rec_ctgr_def();
                        ctgr_def.definition = enu;
                        ctgr_defs.Add(ctgr_def);
                    }
                    // vypsani jedne kategorie do XML
                    string OneCatString = "";
                    if (ctgr_defs.Count == 0)
                        OneCatString += rCat.ToXML();
                    else
                        OneCatString += rCat.ToXML(ctgr_defs);

                    resultString += OneCatString;
                }

            }

            #endregion


            resultString += "</active_list>";

            // Kody - ulozeni vystupu do souboru "XMLAttrExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLCatExample.xml");

            return resultString;
        }
    }

    #region --- Recordy ---

    public class Rec_category
    {
        #region DATA

        public string id = "";
        public string db_name = "";
        public string matrix_name = "";
        public string attr_name = "";
        public string ctgr_name = "";
        public string ctgr_type = "";
        public string ctgr_freq = "";
        public string bool_type = "";
        public long def_length = 0;

        #endregion

        #region METHODS

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
            // vygenerovani vsech podelementu - ctgr_def
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

    public class Rec_ctgr_def
    {
        #region DATA

        public string definition = "";

        #endregion

        #region METHODS

        public string ToXML()
        {
            // nahrazeni znaku "<", ">" v retezcich (kvuli XML)
            definition = XMLHelper.replaceXMLsign(definition);
            string XML = "";
            XML += "<ctgr_def definition=\"" + definition + "\"/>";
            return XML;
        }
        #endregion
    }
    #endregion
}
