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
    // ==================== Aktivni prvek CF cedent ================================

    public class AP_FECF_cedent
    {
        public static string getList(int index)
        {
            string resultString = ""; // vysledny XML string
            string ErrStr = "";  // zaznamy o chybach
            int counterID = 0;

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

            string[] BoxTypes = { "LISpMinerTasks.CFTask", "LISpMinerTasks.SDCFTask" }; // typy krabicek (uloh), pro ktere se hledaji CFske cedenty

            // nalezeni vsech boxu uloh
            IBoxModule[] TaskBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, BoxTypes);

            #region Cyklus - zpracovani vsech nalezenych uloh

            foreach (IBoxModule box in TaskBoxes)
            {
                Rec_CF_cedent rCFCedent = new Rec_CF_cedent();
                counterID = 0;

                try
                {
                    // nastaveni ID
                    rCFCedent.id = "cfcdnt" + box.ProjectIdentifier.ToString() + "_";

                    // nalezeni jmena datoveho zdroje (databaze)
                    IBoxModule[] db_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.Database");
                    if (db_names.GetLength(0) != 1)  // byl nalezen pocet datovych zdroju ruzny od jedne
                        throw new System.Exception("bylo nalezeno " + db_names.GetLength(0).ToString() + " databazi");
                    rCFCedent.db_name = db_names[0].GetPropertyString("DatabaseName");

                    // nalezeni jmena datove matice
                    IBoxModule[] matrix_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.DataMatrix");
                    if (matrix_names.GetLength(0) != 1)  // byl nalezen pocet datovych matic ruzny od jedne
                        throw new System.Exception("bylo nalezeno " + matrix_names.GetLength(0).ToString() + " datovych matic");
                    rCFCedent.matrix_name = matrix_names[0].GetPropertyString("Name");

                    // nalezeni jmena ulohy
                    rCFCedent.task_name = box.UserName;

                    // zpracovani jednotlivych typu tasku
                    string id = rCFCedent.id;
                    switch (box.MadeInCreator.Identifier) // vsechny pripustne typy uloh
                    {
                        case "LISpMinerTasks.CFTask":
                            rCFCedent.task_type = "CF Task";

                            // Antecedent
                            rCFCedent.id = id + counterID.ToString();
                            counterID++;
                            // Kodym - vyber jednu z nasledujicich moznosti (ZJISTI)
                            //rCFCedent.cedent_type = CedentEnum.Antecedent.ToString();
                            rCFCedent.cedent_type = "Attributes";
                            resultString += getOneItemXML(box, rCFCedent, "AntecedentSetting");
                            break;

                        case "LISpMinerTasks.SDCFTask":
                            rCFCedent.task_type = "SD-CF Task";

                            // Anecedent
                            rCFCedent.id = id + counterID.ToString();
                            counterID++;
                            // Kodym - vyber jednu z nasledujicich moznosti (ZJISTI)
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

            // korenovy element
            resultString += "</active_list>";

#if (LADENI)
            // Kody - ulozeni vystupu do souboru "XMLCF_cedentExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLCF_cedentExample.xml");

            if (ErrStr != "") // LADICI
                MessageBox.Show("Chyby pri generovani seznamu CF cedentu:\n" + ErrStr);
#endif

            return resultString;
        }

        private static string getOneCedentXML(IBoxModule[] subcedents)
        {
            string XML = "";

            #region cyklus - zpracovani vsech dilcich cedentu

            foreach (IBoxModule box in subcedents)  // musi byt boxy s ID = "DataMiningCommon.CategorialPartialCedentSetting"
            {
                Rec_sub_CF_cedent rSCFC = new Rec_sub_CF_cedent();
                // nastaveni atributu "name"
                rSCFC.name = box.UserName;
                // nastaveni atributu "length"
                rSCFC.length = box.GetPropertyLong("MinLen").ToString() + " - " + box.GetPropertyLong("MaxLen").ToString();
                
                // nalezeni vsech CF literalu (= atributu!)
                string[] AttrIDs = { "DataMiningCommon.Attributes.Attribute",
                                         "DataMiningCommon.Attributes.EquifrequencyIntervalsAttribute",
                                         "DataMiningCommon.Attributes.EquidistantIntervalsAttribute",
                                         "DataMiningCommon.Attributes.EachValueOneCategoryAttribute" };
                IBoxModule[] attributes = BoxesHelper.ListDirectAncestBoxesWithID(box, AttrIDs);

                // nastaveni atributu "literal_cnt" (pocet dilcich literalu)
                rSCFC.literal_cnt = attributes.Length;
                List<Rec_CF_literal> rLiterals = new List<Rec_CF_literal>();

                #region Cyklus - zpracovani vsech CF-literalu (atributu)

                foreach (IBoxModule attrBox in attributes)
                {
                    Rec_CF_literal rLiteral = new Rec_CF_literal();
                    // nastaveni atributu "underlying_attribute"
                    rLiteral.underlying_attribute = attrBox.GetPropertyString("NameInLiterals");
                    // nastaveni atributu "category_cnt"
                    rLiteral.category_cnt = attrBox.GetPropertyLong("CountOfCategories");
                    rLiterals.Add(rLiteral);
                }
                #endregion

                // pridani dilciho cedentu (a jeho literalu) do vysledneho XML stringu
                XML += rSCFC.ToXML(rLiterals);
            }
            #endregion

            return XML;
        }

        private static string getOneItemXML(IBoxModule box, Rec_CF_cedent rCFCedent, string CedentType)
        {
            string resultStr = "";
            IBoxModule[] SubCedents = box.GetConnections(CedentType);
            // nastaveni atributu "sub_cedent_cnt" (pocet dilcich cedentu)
            rCFCedent.sub_cedent_cnt = SubCedents.Length;
            // pridani CFskeho cedentu do XML
            if (rCFCedent.sub_cedent_cnt > 0)
                resultStr = rCFCedent.ToXML(getOneCedentXML(SubCedents));

            return resultStr;
        }
    }

    #region --- Recordy ---

    public class Rec_CF_cedent
    {
        #region DATA

        public string id = "";
        public string db_name = "";
        public string matrix_name = "";
        public string task_name = "";
        public string task_type = "";
        public string cedent_type = "";
        public long sub_cedent_cnt = 0;
        #endregion

        #region METHODS

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
                // vlozeni XML stringu - obsah elementu
                XML += SubelementsXMLstring + "</CF_cedent>";
            }

            return XML;
        }
        #endregion
    }

    public class Rec_sub_CF_cedent
    {
        #region DATA

        public string name = "";
        public long literal_cnt = 0;
        public string length = "";
        #endregion

        #region METHODS

        public string ToXML()
        {
            string XML = "";
            length = XMLHelper.replaceXMLsign(length);
            name = XMLHelper.replaceXMLsign(name);

            XML += "<sub_CF_cedent name=\"" + name + "\" literal_cnt=\"" + literal_cnt.ToString() +
                   "\" length=\"" + length + "\"/>";
            return XML;
        }

        public string ToXML(List<Rec_CF_literal> CF_Literals)
        {
            string XML = "";
            length = XMLHelper.replaceXMLsign(length);
            name = XMLHelper.replaceXMLsign(name);

            XML += "<sub_CF_cedent name=\"" + name + "\" literal_cnt=\"" + literal_cnt.ToString() +
                   "\" length=\"" + length + "\">";

            // pridani vsech podelementu - literalu
            foreach (Rec_CF_literal Lit in CF_Literals)
                XML += Lit.ToXML();

            XML += "</sub_CF_cedent>";
            return XML;
        }
        #endregion
    }

    public class Rec_CF_literal
    {
        #region DATA

        public string underlying_attribute = "";
        public long category_cnt = 0;
        #endregion

        #region METHODS

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

