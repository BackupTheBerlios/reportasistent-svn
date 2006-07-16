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
#if (LADENI)
                MessageBox.Show("Chyba pri nacitani DTD: " + e.Message);
#endif
                return resultString;
            }

            // korenovy element
            resultString += "<active_list>";

            List<TaskTypeStruct> TypyTasku = new List<TaskTypeStruct>();
            CedentTypeStruct[] TypyCedentu4FT = {new CedentTypeStruct("Antecedent", "AntecedentSetting"), new CedentTypeStruct("Succedent", "SuccedentSetting"), new CedentTypeStruct("Condition", "ConditionSetting")};
            CedentTypeStruct[] TypyCedentuSD4FT = {new CedentTypeStruct("Antecedent", "AntecedentSetting"), new CedentTypeStruct("Succedent", "SuccedentSetting"), new CedentTypeStruct("Condition", "ConditionSetting"), new CedentTypeStruct("FirstSet", "Cedent1"), new CedentTypeStruct("SecondSet", "Cedent2")};
            CedentTypeStruct[] TypyCedentuKL = {new CedentTypeStruct("Condition", "ConditionSetting")};
            CedentTypeStruct[] TypyCedentuSDKL = {new CedentTypeStruct("Condition", "ConditionSetting"), new CedentTypeStruct("FirstSet", "Cedent1"), new CedentTypeStruct("SecondSet", "Cedent2")};
            CedentTypeStruct[] TypyCedentuCF = {new CedentTypeStruct("Condition", "ConditionSetting")};
            CedentTypeStruct[] TypyCedentuSDCF = {new CedentTypeStruct("Condition", "ConditionSetting"), new CedentTypeStruct("FirstSet", "Cedent1"), new CedentTypeStruct("SecondSet", "Cedent2")};
            TypyTasku.Add(new TaskTypeStruct("LISpMinerTasks.FFTTask", "4FT Task", TypyCedentu4FT));
            TypyTasku.Add(new TaskTypeStruct("LISpMinerTasks.SDFFTTask", "SD-4FT Task", TypyCedentuSD4FT));
            TypyTasku.Add(new TaskTypeStruct("LISpMinerTasks.KLTask", "KL Task", TypyCedentuKL));
            TypyTasku.Add(new TaskTypeStruct("LISpMinerTasks.SDKLTask", "SD-KL Task", TypyCedentuSDKL));
            TypyTasku.Add(new TaskTypeStruct("LISpMinerTasks.CFTask", "CF Task", TypyCedentuCF));
            TypyTasku.Add(new TaskTypeStruct("LISpMinerTasks.SDCFTask", "SD-CF Task", TypyCedentuSDCF));

            #region Cyklus - zpracovani vsech typu tasku

            foreach (TaskTypeStruct TT in TypyTasku)
            {

                // nalezeni vsech boxu uloh
                IBoxModule[] TaskBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, TT.TaskTypeID);

                #region Cyklus - zpracovani vsech nalezenych Tasku

                foreach (IBoxModule box in TaskBoxes)
                {

                    #region Cyklus - zpracovani vsech typu cedentu daneho tasku

                    counterID = 0;
                    foreach (CedentTypeStruct TypCedentu in TT.Cedents)
                    {
                        Rec_bool_cedent rBoolCedent = new Rec_bool_cedent();
                        // nastaveni ID
                        string id = "cdnt" + box.ProjectIdentifier.ToString() + "_";


                        try
                        {
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


                            // vyplneni "task_type"
                            rBoolCedent.task_type = TT.TaskTypeLabel;

                            // vyplneni "cedent_type"
                            rBoolCedent.cedent_type = TypCedentu.CedentTypeLabel;

                            // nalezeni vsech dilcich cedentu
                            IBoxModule[] Subcedenty = box.GetConnections(TypCedentu.CedentTypeID);

                            foreach (IBoxModule Subcedent in Subcedenty)
                            {
                                Rec_bool_cedent rBoolCedent1 = rBoolCedent;

                                // vyplneni ID
                                rBoolCedent1.id = id + counterID.ToString();
                                counterID++;

                                // nastaveni "name"
                                rBoolCedent1.name = Subcedent.UserName;
                                // nastaveni "length"
                                rBoolCedent1.length = Subcedent.GetPropertyLong("MinLen").ToString() + " - " + Subcedent.GetPropertyLong("MaxLen").ToString();
                                // nalezeni vsech literalu
                                IBoxModule[] literals = BoxesHelper.ListDirectAncestBoxesWithID(Subcedent, "DataMiningCommon.LiteralSetting");
                                // nastaveni atributu "literal_cnt" (pocet dilcich literalu)
                                rBoolCedent1.literal_cnt = literals.Length;

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
                                        ErrStr += "Literal ID=" + litBox.ProjectIdentifier.ToString() + " : nalezeno " + atoms.Length.ToString() + " atomu\n";
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
                                        ErrStr += "Literal ID=" + litBox.ProjectIdentifier.ToString() + " : nalezeno " + attributes.Length.ToString() + " atributu\n";
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

                                // vypsani boolskeho cedentu do XML
                                resultString += rBoolCedent1.ToXML(rLiterals);


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
            }
            #endregion
            // korenovy element
            resultString += "</active_list>";

#if (LADENI)
            // Kody - ulozeni vystupu do souboru "XMLBool_cedentExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLBool_cedentExample.xml");

            if (ErrStr != "") // LADICI
                MessageBox.Show("Chyby pri generovani seznamu Boolskych cedentu:\n" + ErrStr);
#endif

            return resultString;
        }

        

        // pomocna struktura - vsechny typy Tasku zpracovavane v cyklu v getList() a k nim potrebne polozky
        struct TaskTypeStruct
        {
            public string TaskTypeID;
            public string TaskTypeLabel;
            public CedentTypeStruct[] Cedents;
            

            public TaskTypeStruct(string TTID, string TTL, CedentTypeStruct[] Ced)
            {
                TaskTypeID = TTID;
                TaskTypeLabel = TTL;
                Cedents = Ced;
            }
        }

        // pomocna struktura - vsechny typy Tasku zpracovavane v cyklu v getList() a k nim potrebne polozky
        public struct CedentTypeStruct
        {
            public string CedentTypeLabel;
            public string CedentTypeID;
            

            public CedentTypeStruct(string CTL, string CTID)
            {
                CedentTypeLabel = CTL;
                CedentTypeID = CTID;
            }
        }
    }
   
    #region --- Recordy ---

    public class Rec_bool_cedent
    {
        #region DATA

        public string id = "";
        public string name = "";
        public string db_name = "";
        public string matrix_name = "";
        public string task_name = "";
        public string task_type = "";
        public string cedent_type = "";
        public long literal_cnt = 0;
        public string length = "";
        #endregion

        #region METHODS

        public string ToXML(List<Rec_literal> Literals)
        {
            string XML = "";
            db_name = XMLHelper.replaceXMLsign(db_name);
            matrix_name = XMLHelper.replaceXMLsign(matrix_name);
            task_name = XMLHelper.replaceXMLsign(task_name);
            task_type = XMLHelper.replaceXMLsign(task_type);
            cedent_type = XMLHelper.replaceXMLsign(cedent_type);

            XML += "<bool_cedent id=\"" + id + "\" name=\"" + name + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" task_name=\"" + task_name + "\" task_type=\"" + task_type +
                   "\" cedent_type=\"" + cedent_type + 
                   "\" literal_cnt=\"" + literal_cnt.ToString() +
                   "\" length=\"" + length + "\">";

            // pridani vsech podelementu - literalu
            foreach (Rec_literal Lit in Literals)
                XML += Lit.ToXML();

            XML += "</bool_cedent>";
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
