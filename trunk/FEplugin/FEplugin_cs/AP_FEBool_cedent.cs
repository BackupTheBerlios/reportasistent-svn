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
    // ==================== Aktivni prvek Boolsky cedent ================================

    public class AP_FEBool_cedent
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

            string[] BoxTypes = { "LISpMinerTasks.FFTTask",
                                  "LISpMinerTasks.SDFFTTask",
                                  "LISpMinerTasks.KLTask",
                                  "LISpMinerTasks.SDKLTask",
                                  "LISpMinerTasks.CFTask",
                                  "LISpMinerTasks.SDCFTask" }; // typy krabicek (uloh), pro ktere se hledaji boolske cedenty
            
            // nalezeni vsech boxu uloh
            IBoxModule[] TaskBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, BoxTypes);

            #region Cyklus - zpracovani vsech nalezenych uloh

            foreach (IBoxModule box in TaskBoxes)
            {
                Rec_bool_cedent rBoolCedent = new Rec_bool_cedent();
                counterID = 0;

                try
                {
                    // nastaveni ID
                    rBoolCedent.id = "cdnt" + box.ProjectIdentifier.ToString() + "_";
                    
                    // nalezeni jmena datoveho zdroje (databaze)
                    IBoxModule[] db_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.Database");
                    if (db_names.GetLength(0) != 1)  // byl nalezen pocet datovych zdroju ruzny od jedne
                        throw new System.Exception("bylo nalezeno " + db_names.GetLength(0).ToString() + " databazi");
                     rBoolCedent.db_name = db_names[0].GetPropertyString("DatabaseName");

                    // nalezeni jmena datove matice
                    IBoxModule[] matrix_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.DataMatrix");
                    if (matrix_names.GetLength(0) != 1)  // byl nalezen pocet datovych matic ruzny od jedne
                        throw new System.Exception("bylo nalezeno " + matrix_names.GetLength(0).ToString() + " datovych matic");
                    rBoolCedent.matrix_name = matrix_names[0].GetPropertyString("Name");

                    // nalezeni jmena ulohy
                    rBoolCedent.task_name = box.UserName;

                    // zpracovani jednotlivych typu tasku
                    string id = rBoolCedent.id;
                    switch (box.MadeInCreator.Identifier) // vsechny pripustne typy uloh
                    {
                        case "LISpMinerTasks.FFTTask":
                            rBoolCedent.task_type = "4FT Task";

                            // Antecedent
                            rBoolCedent.id = id + counterID.ToString();
                            counterID++;
                            rBoolCedent.cedent_type = CedentEnum.Antecedent.ToString();
                            resultString += getOneItemXML(box, rBoolCedent, "AntecedentSetting");

                            // Succedent
                            rBoolCedent.id = id + counterID.ToString();
                            counterID++;
                            rBoolCedent.cedent_type = CedentEnum.Succedent.ToString();
                            resultString += getOneItemXML(box, rBoolCedent, "SuccedentSetting");

                            // Condition
                            rBoolCedent.id = id + counterID.ToString();
                            counterID++;
                            rBoolCedent.cedent_type = CedentEnum.Condition.ToString();
                            resultString += getOneItemXML(box, rBoolCedent, "ConditionSetting");
                            break;

                        case "LISpMinerTasks.SDFFTTask":
                            rBoolCedent.task_type = "SD-4FT Task";

                            // Anecedent
                            rBoolCedent.id = id + counterID.ToString();
                            counterID++;
                            rBoolCedent.cedent_type = CedentEnum.Antecedent.ToString();
                            resultString += getOneItemXML(box, rBoolCedent, "AntecedentSetting");

                            // Succedent
                            rBoolCedent.id = id + counterID.ToString();
                            counterID++;
                            rBoolCedent.cedent_type = CedentEnum.Succedent.ToString();
                            resultString += getOneItemXML(box, rBoolCedent, "SuccedentSetting");

                            // Condition
                            rBoolCedent.id = id + counterID.ToString();
                            counterID++;
                            rBoolCedent.cedent_type = CedentEnum.Condition.ToString();
                            resultString += getOneItemXML(box, rBoolCedent, "ConditionSetting");

                            // FirstSet
                            rBoolCedent.id = id + counterID.ToString();
                            counterID++;
                            rBoolCedent.cedent_type = CedentEnum.FirstSet.ToString();
                            resultString += getOneItemXML(box, rBoolCedent, "Cedent1");

                            // SecondSet
                            rBoolCedent.id = id + counterID.ToString();
                            counterID++;
                            rBoolCedent.cedent_type = CedentEnum.SecondSet.ToString();
                            resultString += getOneItemXML(box, rBoolCedent, "Cedent2");
                            break;

                        case "LISpMinerTasks.KLTask":
                            rBoolCedent.task_type = "KL Task";

                            // Condition
                            rBoolCedent.id = id + counterID.ToString();
                            counterID++;
                            rBoolCedent.cedent_type = CedentEnum.Condition.ToString();
                            resultString += getOneItemXML(box, rBoolCedent, "ConditionSetting");
                            break;

                        case "LISpMinerTasks.SDKLTask":
                            rBoolCedent.task_type = "SD-KL Task";

                            // Condition
                            rBoolCedent.id = id + counterID.ToString();
                            counterID++;
                            rBoolCedent.cedent_type = CedentEnum.Condition.ToString();
                            resultString += getOneItemXML(box, rBoolCedent, "ConditionSetting");

                            // FirstSet
                            rBoolCedent.id = id + counterID.ToString();
                            counterID++;
                            rBoolCedent.cedent_type = CedentEnum.FirstSet.ToString();
                            resultString += getOneItemXML(box, rBoolCedent, "Cedent1");

                            // SecondSet
                            rBoolCedent.id = id + counterID.ToString();
                            counterID++;
                            rBoolCedent.cedent_type = CedentEnum.SecondSet.ToString();
                            resultString += getOneItemXML(box, rBoolCedent, "Cedent2");
                            break;

                        case "LISpMinerTasks.CFTask":
                            rBoolCedent.task_type = "CF Task";

                            // Condition
                            rBoolCedent.id = id + counterID.ToString();
                            counterID++;
                            rBoolCedent.cedent_type = CedentEnum.Condition.ToString();
                            resultString += getOneItemXML(box, rBoolCedent, "ConditionSetting");
                            break;

                        case "LISpMinerTasks.SDCFTask":
                            rBoolCedent.task_type = "SD-CF Task";

                            // Condition
                            rBoolCedent.id = id + counterID.ToString();
                            counterID++;
                            rBoolCedent.cedent_type = CedentEnum.Condition.ToString();
                            resultString += getOneItemXML(box, rBoolCedent, "ConditionSetting");

                            // FirstSet
                            rBoolCedent.id = id + counterID.ToString();
                            counterID++;
                            rBoolCedent.cedent_type = CedentEnum.FirstSet.ToString();
                            resultString += getOneItemXML(box, rBoolCedent, "Cedent1");

                            // SecondSet
                            rBoolCedent.id = id + counterID.ToString();
                            counterID++;
                            rBoolCedent.cedent_type = CedentEnum.SecondSet.ToString();
                            resultString += getOneItemXML(box, rBoolCedent, "Cedent2");
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

            // Kody - ulozeni vystupu do souboru "XMLBool_cedentExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLBool_cedentExample.xml");

            if (ErrStr != "") // LADICI
                MessageBox.Show("Chyby pri generovani seznamu Boolskych cedentu:\n" + ErrStr);

            return resultString;
        }

        private static string getOneCedentXML(IBoxModule[] subcedents)
        {
            string XML = "";
            string ErrList = "";

            #region cyklus - zpracovani vsech dilcich cedentu

            foreach (IBoxModule box in subcedents)  // musi byt boxy s ID = "DataMiningCommon.BooleanPartialCedentSetting"
            {
                Rec_sub_bool_cedent rSBC = new Rec_sub_bool_cedent();
                // nastaveni atributu "name"
                rSBC.name = box.UserName;
                // nastaveni atributu "length"
                rSBC.length = box.GetPropertyLong("MinLen").ToString() + " - " + box.GetPropertyLong("MaxLen").ToString();
                // nalezeni vsech literalu
                IBoxModule[] literals = BoxesHelper.ListDirectAncestBoxesWithID(box, "DataMiningCommon.LiteralSetting");
                // nastaveni atributu "literal_cnt" (pocet dilcich literalu)
                rSBC.literal_cnt = literals.Length;

                List<Rec_literal> rLiterals = new List<Rec_literal>();

                #region cyklus - zpracovani vsech literalu dilciho cedentu

                foreach (IBoxModule litBox in literals)
                {
                    Rec_literal rLiteral = new Rec_literal();
                    // nastaveni atributu "literal_type" {Basic/Remaining}
                    rLiteral.literal_type = litBox.GetPropertyString("LiteralType");
                    // nastaveni atributu "gace" {Positive/Negative/Both}
                    rLiteral.gace = litBox.GetPropertyString("GaceType");

                    // nalezeni atomu
                    IBoxModule[] atoms = BoxesHelper.ListDirectAncestBoxesWithID(litBox, "DataMiningCommon.AtomSetting");
                    if (atoms.Length != 1) // mel by byt nalezen prave jeden atom
                    {
                        ErrList += "Literal ID=" + litBox.ProjectIdentifier.ToString() + " : nalezeno " + atoms.Length.ToString() + " atomu\n";
                        continue; // zpracovani dalsiho literalu
                    }
                    IBoxModule atomBox = atoms[0].Clone();

                    // nastaveni atributu "coefficient_type" {Interval/Subset/Cut/....}
                    rLiteral.coefficient_type = atomBox.GetPropertyString("CoefficientType");
                    // nastaveni atributu "length"
                    rLiteral.length = atomBox.GetPropertyLong("MinLen").ToString() + " - " + atomBox.GetPropertyLong("MaxLen").ToString();

                    // nalezeni atributu
                    string[] AttrIDs = { "DataMiningCommon.Attributes.Attribute",
                                         "DataMiningCommon.Attributes.EquifrequencyIntervalsAttribute",
                                         "DataMiningCommon.Attributes.EquidistantIntervalsAttribute",
                                         "DataMiningCommon.Attributes.EachValueOneCategoryAttribute" };
                    IBoxModule[] attributes = BoxesHelper.ListDirectAncestBoxesWithID(atomBox, AttrIDs);
                    if (attributes.Length != 1) // mel by byt nalezen prave jeden atribut
                    {
                        ErrList += "Literal ID=" + litBox.ProjectIdentifier.ToString() + " : nalezeno " + attributes.Length.ToString() + " atributu\n";
                        continue; // zpracovani dalsiho literalu
                    }
                    IBoxModule attrBox = attributes[0].Clone();

                    // nastaveni atributu "underlying_attribute"
                    rLiteral.underlying_attribute = attrBox.GetPropertyString("NameInLiterals");
                    // nastaveni atributu "category_cnt"
                    rLiteral.category_cnt = attrBox.GetPropertyLong("CountOfCategories");
                    // nastaveni atributu "missing_type"
                    rLiteral.missing_type = attrBox.GetPropertyString("IncludeNullCategory");

                    // pridani literalu do seznamu
                    rLiterals.Add(rLiteral);
                }
                #endregion

                // pridani dilciho cedentu (a jeho literalu) do vysledneho XML stringu
                XML += rSBC.ToXML(rLiterals);
            }
            #endregion

            return XML;
        }

        private static string getOneItemXML(IBoxModule box, Rec_bool_cedent rBoolCedent, string CedentType)
        {
            string resultStr = "";
            IBoxModule[] SubCedents = box.GetConnections(CedentType);
            // nastaveni atributu "sub_cedent_cnt" (pocet dilcich cedentu)
            rBoolCedent.sub_cedent_cnt = SubCedents.Length;
            // pridani boolskeho cedentu do XML
            if(rBoolCedent.sub_cedent_cnt > 0)
                resultStr = rBoolCedent.ToXML(getOneCedentXML(SubCedents));

            return resultStr;
        }
    }
   
    #region --- Recordy ---

    public class Rec_bool_cedent
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

            XML += "<bool_cedent id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
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
                XML += "<bool_cedent id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                       "\" task_name=\"" + task_name + "\" task_type=\"" + task_type +
                       "\" cedent_type=\"" + cedent_type +
                       "\" sub_cedent_cnt=\"" + sub_cedent_cnt.ToString() + "\"/>";
            }
            else
            {
                XML += "<bool_cedent id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                       "\" task_name=\"" + task_name + "\" task_type=\"" + task_type +
                       "\" cedent_type=\"" + cedent_type +
                       "\" sub_cedent_cnt=\"" + sub_cedent_cnt.ToString() + "\">";
                // vlozeni XML stringu - obsah elementu
                XML += SubelementsXMLstring + "</bool_cedent>";
            }

            return XML;
        }
        #endregion
    }

    public class Rec_sub_bool_cedent
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

            XML += "<sub_bool_cedent name=\"" + name + "\" literal_cnt=\"" + literal_cnt.ToString() +
                   "\" length=\"" + length + "\"/>";
            return XML;
        }

        public string ToXML(List<Rec_literal> Literals)
        {            
            string XML = "";
            length = XMLHelper.replaceXMLsign(length);
            name = XMLHelper.replaceXMLsign(name);

            XML += "<sub_bool_cedent name=\"" + name + "\" literal_cnt=\"" + literal_cnt.ToString() +
                   "\" length=\"" + length + "\">";
            
            // pridani vsech podelementu - literalu
            foreach(Rec_literal Lit in Literals)
                XML += Lit.ToXML();

            XML += "</sub_bool_cedent>";
            return XML;
        }
        #endregion
    }

    public class Rec_literal
    {
        #region DATA

        public string underlying_attribute = "";
        public long category_cnt = 0;
        public string missing_type = "";
        public string coefficient_type = "";
        public string length = "";
        public string gace = "";
        public string literal_type = "";
        public string equivalence_class = "";
        #endregion

        #region METHODS

        public string ToXML()
        {
            
            string XML = "";
            underlying_attribute = XMLHelper.replaceXMLsign(underlying_attribute);
            missing_type = XMLHelper.replaceXMLsign(missing_type);
            coefficient_type = XMLHelper.replaceXMLsign(coefficient_type);
            length = XMLHelper.replaceXMLsign(length);
            gace = XMLHelper.replaceXMLsign(gace);
            literal_type = XMLHelper.replaceXMLsign(literal_type);
            equivalence_class = XMLHelper.replaceXMLsign(equivalence_class);

            XML += "<literal underlying_attribute=\"" + underlying_attribute + 
                   "\" category_cnt=\"" + category_cnt.ToString() +
                   "\" missing_type=\"" + missing_type +
                   "\" coefficient_type=\"" + coefficient_type + "\" length=\"" + length +
                   "\" gace=\"" + gace + "\" literal_type=\"" + literal_type +
                   "\" equivalence_class=\"" + equivalence_class + "\"/>";
            return XML;
        }
        #endregion
    }

    #endregion

}
