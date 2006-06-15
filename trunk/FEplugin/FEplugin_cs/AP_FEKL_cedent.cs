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
    // ==================== Aktivni prvek KL cedent ================================

    public class AP_FEKL_cedent
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
                MessageBox.Show("Chyba pri nacitani DTD: " + e.Message);
                return resultString;
            }

            // korenovy element
            resultString += "<active_list>";

            string[] BoxTypes = { "LISpMinerTasks.KLTask", "LISpMinerTasks.SDKLTask" }; // typy krabicek (uloh), pro ktere se hledaji KLske cedenty

            // nalezeni vsech boxu uloh
            IBoxModule[] TaskBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, BoxTypes);

            #region Cyklus - zpracovani vsech nalezenych uloh

            foreach (IBoxModule box in TaskBoxes)
            {
                Rec_KL_cedent rKLCedent = new Rec_KL_cedent();
                counterID = 0;

                try
                {
                    // nastaveni ID
                    rKLCedent.id = "klcdnt" + box.ProjectIdentifier.ToString() + "_";

                    // nalezeni jmena datoveho zdroje (databaze)
                    IBoxModule[] db_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.Database");
                    if (db_names.GetLength(0) != 1)  // byl nalezen pocet datovych zdroju ruzny od jedne
                        throw new System.Exception("bylo nalezeno " + db_names.GetLength(0).ToString() + " databazi");
                    rKLCedent.db_name = db_names[0].GetPropertyString("DatabaseName");

                    // nalezeni jmena datove matice
                    IBoxModule[] matrix_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.DataMatrix");
                    if (matrix_names.GetLength(0) != 1)  // byl nalezen pocet datovych matic ruzny od jedne
                        throw new System.Exception("bylo nalezeno " + matrix_names.GetLength(0).ToString() + " datovych matic");
                    rKLCedent.matrix_name = matrix_names[0].GetPropertyString("Name");

                    // nalezeni jmena ulohy
                    rKLCedent.task_name = box.UserName;

                    // zpracovani jednotlivych typu tasku
                    string id = rKLCedent.id;
                    switch (box.MadeInCreator.Identifier) // vsechny pripustne typy uloh
                    {
                        case "LISpMinerTasks.KLTask":
                            rKLCedent.task_type = "KL Task";

                            // Antecedent
                            rKLCedent.id = id + counterID.ToString();
                            counterID++;
                            // Kodym - vyber jednu z nasledujicich moznosti (ZJISTI)
                            //rKLCedent.cedent_type = CedentEnum.Antecedent.ToString();
                            rKLCedent.cedent_type = "Row attributes";
                            resultString += getOneItemXML(box, rKLCedent, "AntecedentSetting");

                            // Succedent
                            rKLCedent.id = id + counterID.ToString();
                            counterID++;
                            // Kodym - vyber jednu z nasledujicich moznosti (ZJISTI)
                            rKLCedent.cedent_type = "Column attributes";
                            //rKLCedent.cedent_type = CedentEnum.Succedent.ToString();
                            resultString += getOneItemXML(box, rKLCedent, "SuccedentSetting");
                            break;

                        case "LISpMinerTasks.SDKLTask":
                            rKLCedent.task_type = "SD-KL Task";

                            // Anecedent
                            rKLCedent.id = id + counterID.ToString();
                            counterID++;
                            // Kodym - vyber jednu z nasledujicich moznosti (ZJISTI)
                            //rKLCedent.cedent_type = CedentEnum.Antecedent.ToString();
                            rKLCedent.cedent_type = "Row attributes";
                            resultString += getOneItemXML(box, rKLCedent, "AntecedentSetting");

                            // Succedent
                            rKLCedent.id = id + counterID.ToString();
                            counterID++;
                            // Kodym - vyber jednu z nasledujicich moznosti (ZJISTI)
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

            // korenovy element
            resultString += "</active_list>";

            // Kody - ulozeni vystupu do souboru "XMLKL_cedentExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLKL_cedentExample.xml");

            if (ErrStr != "") // LADICI
                MessageBox.Show("Chyby pri generovani seznamu KL cedentu:\n" + ErrStr);

            return resultString;
        }

        private static string getOneCedentXML(IBoxModule[] subcedents)
        {
            string XML = "";
            string ErrList = "";

            #region cyklus - zpracovani vsech dilcich cedentu

            foreach (IBoxModule box in subcedents)  // musi byt boxy s ID = "DataMiningCommon.CategorialPartialCedentSetting"
            {
                Rec_sub_KL_cedent rSKLC = new Rec_sub_KL_cedent();
                // nastaveni atributu "name"
                rSKLC.name = box.UserName;
                // nastaveni atributu "length"
                rSKLC.length = box.GetPropertyLong("MinLen").ToString() + " - " + box.GetPropertyLong("MaxLen").ToString();
                
                // nalezeni vsech KL literalu (= atributu!)
                string[] AttrIDs = { "DataMiningCommon.Attributes.Attribute",
                                         "DataMiningCommon.Attributes.EquifrequencyIntervalsAttribute",
                                         "DataMiningCommon.Attributes.EquidistantIntervalsAttribute",
                                         "DataMiningCommon.Attributes.EachValueOneCategoryAttribute" };
                IBoxModule[] attributes = BoxesHelper.ListDirectAncestBoxesWithID(box, AttrIDs);
                
                // nastaveni atributu "literal_cnt" (pocet dilcich literalu)
                rSKLC.literal_cnt = attributes.Length;
                List<Rec_KL_literal> rLiterals = new List<Rec_KL_literal>();

                #region Cyklus - zpracovani vsech KL-literalu (atributu)

                foreach (IBoxModule attrBox in attributes)
                {
                    Rec_KL_literal rLiteral = new Rec_KL_literal();
                    // nastaveni atributu "underlying_attribute"
                    rLiteral.underlying_attribute = attrBox.GetPropertyString("NameInLiterals");
                    // nastaveni atributu "category_cnt"
                    rLiteral.category_cnt = attrBox.GetPropertyLong("CountOfCategories");
                    rLiterals.Add(rLiteral);
                }
                #endregion
                // pridani dilciho cedentu (a jeho literalu) do vysledneho XML stringu
                XML += rSKLC.ToXML(rLiterals);
            }
            #endregion

            return XML;
        }

        private static string getOneItemXML(IBoxModule box, Rec_KL_cedent rKLCedent, string CedentType)
        {
            string resultStr = "";
            IBoxModule[] SubCedents = box.GetConnections(CedentType);
            // nastaveni atributu "sub_cedent_cnt" (pocet dilcich cedentu)
            rKLCedent.sub_cedent_cnt = SubCedents.Length;
            // pridani KLskeho cedentu do XML
            if (rKLCedent.sub_cedent_cnt > 0)
                resultStr = rKLCedent.ToXML(getOneCedentXML(SubCedents));

            return resultStr;
        }
    }

    #region --- Recordy ---

    public class Rec_KL_cedent
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

            XML += "<KL_cedent id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
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
                // vlozeni XML stringu - obsah elementu
                XML += SubelementsXMLstring + "</KL_cedent>";
            }

            return XML;
        }
        #endregion
    }

    public class Rec_sub_KL_cedent
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

            XML += "<sub_KL_cedent name=\"" + name + "\" literal_cnt=\"" + literal_cnt.ToString() +
                   "\" length=\"" + length + "\"/>";
            return XML;
        }

        public string ToXML(List<Rec_KL_literal> KL_Literals)
        {
            string XML = "";
            length = XMLHelper.replaceXMLsign(length);
            name = XMLHelper.replaceXMLsign(name);

            XML += "<sub_KL_cedent name=\"" + name + "\" literal_cnt=\"" + literal_cnt.ToString() +
                   "\" length=\"" + length + "\">";

            // pridani vsech podelementu - literalu
            foreach (Rec_KL_literal Lit in KL_Literals)
                XML += Lit.ToXML();

            XML += "</sub_KL_cedent>";
            return XML;
        }
        #endregion
    }

    public class Rec_KL_literal
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

            XML += "<KL_literal underlying_attribute=\"" + underlying_attribute +
                   "\" category_cnt=\"" + category_cnt.ToString() + "\"/>";
            return XML;
        }
        #endregion
    }

    #endregion

}

