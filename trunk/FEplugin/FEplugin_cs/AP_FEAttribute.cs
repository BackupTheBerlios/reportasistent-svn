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
    // ==================== Aktivni prvek Atribut ================================

    public class AP_FEAttribute
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


            #region  A) nalezeni vsech krabicek Atributu (DataMiningCommon.Attributes.Attribute)

            IBoxModule[] AttrBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, "DataMiningCommon.Attributes.Attribute");

            // zpracovani kazde krabicky - ziskani z ni vsechny Atributy
            foreach (IBoxModule ABox in AttrBoxes)
            {
                Rec_attribute rAttr = new Rec_attribute();

                // nastaveni ID atributu
                rAttr.id = "Attr" + ABox.ProjectIdentifier.ToString();
                
                // zjisteni jmena literalu
                rAttr.attr_name = ABox.GetPropertyString("NameInLiterals");

                // nalezeni jmena datoveho zdroje (databaze)
                IBoxModule[] db_names = BoxesHelper.ListAncestBoxesWithID(ABox, "DataMiningCommon.Database");
                if (db_names.GetLength(0) != 1)  // byl nalezen pocet datovych zdroju ruzny od jedne
                    throw new System.Exception("bylo nalezeno " + db_names.GetLength(0).ToString() + " databazi");
                rAttr.db_name = (db_names[0].GetPropertyOther("DatabaseName") as StringT).stringValue;

                // nalezeni jmena datove matice
                IBoxModule[] matrix_names = BoxesHelper.ListAncestBoxesWithID(ABox, "DataMiningCommon.DataMatrix");
                if (matrix_names.GetLength(0) != 1)  // byl nalezen pocet datovych matic ruzny od jedne
                    throw new System.Exception("bylo nalezeno " + matrix_names.GetLength(0).ToString() + " datovych matic");
                rAttr.matrix_name = (matrix_names[0].GetPropertyOther("Name") as StringT).stringValue;

                
                // nalezeni jmena zdrojoveho sloupce nebo zpusobu odvozeni
                IBoxModule[] col_names = BoxesHelper.ListDirectAncestBoxesWithID(ABox, "DataMiningCommon.Column");
                if (col_names.GetLength(0) != 1 && col_names.GetLength(0) != 0)  // byl nalezen chybny pocet zdrojovych sloupcu
                    throw new System.Exception("bylo nalezeno " + col_names.GetLength(0).ToString() + " zdrojovych sloupcu");
                if(col_names.GetLength(0) == 1)
                    rAttr.creation = col_names[0].GetPropertyString("Name");

                IBoxModule[] dercol_names = BoxesHelper.ListDirectAncestBoxesWithID(ABox, "DataMiningCommon.DerivedColumn");
                if (dercol_names.GetLength(0) != 1 && dercol_names.GetLength(0) != 0)  // byl nalezen chybny pocet zdrojovych sloupcu
                    throw new System.Exception("bylo nalezeno " + dercol_names.GetLength(0).ToString() + " zdrojovych odvozenych sloupcu");
                if (dercol_names.GetLength(0) == 1)
                    rAttr.creation = dercol_names[0].GetPropertyString("Formula");
                
                  
                // nalezeni poctu kategorii
                rAttr.ctgr_count = ABox.GetPropertyLong("CountOfCategories");

                // zjisteni kategorie "chybejici hodnota"
                string nul_cat = ABox.GetPropertyString("IncludeNullCategory");
                List<Rec_missing_value> MisVal_list = new List<Rec_missing_value>();  // pole recordu chybejicich hodnot
                if (!String.IsNullOrEmpty(nul_cat))
                {
                    Rec_missing_value MisVal = new Rec_missing_value();
                    MisVal.name = nul_cat;
                    MisVal_list.Add(MisVal);
                }

                // nalezeni nazvu kategorii a jejich frekvenci
                List<Rec_ctgr> cat_list = new List<Rec_ctgr>(); // seznam kategorii
                CategoriesStruct cat_str = (ABox.GetPropertyOther("Categories") as CategoriesT).categoriesValue;
                
                // long intervals
                foreach (string key in cat_str.longIntervals.Keys)
                {
                        Rec_ctgr new_li = new Rec_ctgr();
                        new_li.freq = "N/A";  // Not Available - TODO (doimplementovat, bude-li mozno)
                        new_li.name = key;
                        cat_list.Add(new_li);
                }
                // float intervals
                foreach (string key in cat_str.floatIntervals.Keys)
                {
                    Rec_ctgr new_li = new Rec_ctgr();
                    new_li.freq = "N/A";  // Not Available - TODO (doimplementovat, bude-li mozno)
                    new_li.name = key;
                    cat_list.Add(new_li);
                }
                //  date time intervals
                foreach (string key in cat_str.dateTimeIntervals.Keys)
                {
                    Rec_ctgr new_li = new Rec_ctgr();
                    new_li.freq = "N/A";  // Not Available - TODO (doimplementovat, bude-li mozno)
                    new_li.name = key;
                    cat_list.Add(new_li);
                }
                // enums
                foreach (string key in cat_str.enums.Keys)
                {
                    Rec_ctgr new_li = new Rec_ctgr();
                    new_li.freq = "N/A";  // Not Available - TODO (doimplementovat, bude-li mozno)
                    new_li.name = key;
                    cat_list.Add(new_li);
                }



                #region Vypsani jednoho Atributu do XML stringu

                string oneAttrString = "";
                // vypsani hypotezy do XML

                if (MisVal_list.Count == 0 && cat_list.Count == 0)
                    oneAttrString += rAttr.ToXML();
                else
                    oneAttrString += rAttr.ToXML(cat_list, MisVal_list);
                
                resultString += oneAttrString;

                #endregion


            }

            #endregion

            // korenovy element
            resultString += "</active_list>";

            // Kody - ulozeni vystupu do souboru "XMLAttrExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLAttrExample.xml");

            return resultString;
        }  // TODO: atributy v krabickach EachValueOneCategory, Equidistant, Equifrequency???
    }
   
    #region --- Recordy ---

    public class Rec_attribute
    {
        #region DATA

        public string id = "";
        public string db_name = "";
        public string matrix_name = "";
        public string attr_name = "";
        public string creation = "";
        public long ctgr_count = 0;
        #endregion

        #region METHODS

        public string ToXML()
        {
            string XML = "";

            XML += "<attribute id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" attr_name=\"" + attr_name + "\" creation=\"" + creation +
                   "\" ctgr_count=\"" + ctgr_count.ToString() + "\"/>";
            return XML;
        }

        public string ToXML(List<Rec_ctgr> Categories, List<Rec_missing_value> MissingValue)
        {
            string XML = "";

            XML += "<attribute id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" attr_name=\"" + attr_name + "\" creation=\"" + creation +
                   "\" ctgr_count=\"" + ctgr_count.ToString() + "\">";
            // vygenerovani vsech podelementu - ctgr
            if (Categories.Count > 0)
            {
                foreach (Rec_ctgr ctgr in Categories)
                    XML += ctgr.ToXML();
            }
            // vygenerovani vsech podelementu - missing_value
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

    public class Rec_ctgr
    {
        #region DATA

        public string name = "";
        public string freq = "";
        #endregion

        #region METHODS

        public string ToXML()
        {
            // nahrazeni znaku "<", ">" v retezcich (kvuli XML)
            name = name.Replace("&", "&amp;");
            name = name.Replace("<", "&lt;");
            name = name.Replace(">", "&gt;");
            string XML = "";
            XML += "<ctgr name=\"" + name + "\" freq=\"" + freq + "\"/>";
            return XML;
        }
        #endregion
    }

    public class Rec_missing_value
    {
        #region DATA

        public string name = "";
        #endregion

        #region METHODS

        public string ToXML()
        {
            // nahrazeni znaku "<", ">" v retezcich (kvuli XML)
            name = name.Replace("&", "&amp;");
            name = name.Replace("<", "&lt;");
            name = name.Replace(">", "&gt;");
            string XML = "";
            XML += "<missing_value name=\"" + name + "\"/>";
            return XML;
        }
        #endregion
    }

    #endregion

}
