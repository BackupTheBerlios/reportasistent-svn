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
    // ==================== Active element "Boolean cedent" ================================

    /// <summary>
    /// Implementation of active element "Boolean cedent" (ID="bool_cedent")
    /// </summary>
    public class AP_FEBool_cedent
    {
        /// <summary>
        /// Returns XML string with all occurences of Active element "Boolean cedent".
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

            List<TaskTypeStruct> TypyTask = new List<TaskTypeStruct>();
            CedentTypeStruct[] Typycedent4FT = {new CedentTypeStruct("Antecedent", "AntecedentSetting"), new CedentTypeStruct("Succedent", "SuccedentSetting"), new CedentTypeStruct("Condition", "ConditionSetting")};
            CedentTypeStruct[] TypycedentSD4FT = {new CedentTypeStruct("Antecedent", "AntecedentSetting"), new CedentTypeStruct("Succedent", "SuccedentSetting"), new CedentTypeStruct("Condition", "ConditionSetting"), new CedentTypeStruct("FirstSet", "Cedent1"), new CedentTypeStruct("SecondSet", "Cedent2")};
            CedentTypeStruct[] TypycedentKL = {new CedentTypeStruct("Condition", "ConditionSetting")};
            CedentTypeStruct[] TypycedentSDKL = {new CedentTypeStruct("Condition", "ConditionSetting"), new CedentTypeStruct("FirstSet", "Cedent1"), new CedentTypeStruct("SecondSet", "Cedent2")};
            CedentTypeStruct[] TypycedentCF = {new CedentTypeStruct("Condition", "ConditionSetting")};
            CedentTypeStruct[] TypycedentSDCF = {new CedentTypeStruct("Condition", "ConditionSetting"), new CedentTypeStruct("FirstSet", "Cedent1"), new CedentTypeStruct("SecondSet", "Cedent2")};
            TypyTask.Add(new TaskTypeStruct("LISpMinerTasks.FFTTask", "4FT Task", Typycedent4FT));
            TypyTask.Add(new TaskTypeStruct("LISpMinerTasks.SDFFTTask", "SD-4FT Task", TypycedentSD4FT));
            TypyTask.Add(new TaskTypeStruct("LISpMinerTasks.KLTask", "KL Task", TypycedentKL));
            TypyTask.Add(new TaskTypeStruct("LISpMinerTasks.SDKLTask", "SD-KL Task", TypycedentSDKL));
            TypyTask.Add(new TaskTypeStruct("LISpMinerTasks.CFTask", "CF Task", TypycedentCF));
            TypyTask.Add(new TaskTypeStruct("LISpMinerTasks.SDCFTask", "SD-CF Task", TypycedentSDCF));

            #region Loop - processing of each type of Task

            foreach (TaskTypeStruct TT in TypyTask)
            {

                // searching all boxes of tasks
                IBoxModule[] TaskBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, TT.TaskTypeID);

                #region Loop - processing of each found Task

                foreach (IBoxModule box in TaskBoxes)
                {

                    #region Loop - processing of each type of cedent of given Task

                    counterID = 0;
                    foreach (CedentTypeStruct Typcedent in TT.Cedents)
                    {
                        Rec_bool_cedent rBoolCedent = new Rec_bool_cedent();
                        // setting ID
                        string id = "cdnt" + box.ProjectIdentifier.ToString() + "_";


                        try
                        {
                            // searching data source name (database)
                            IBoxModule[] db_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.Database");
                            if (db_names.GetLength(0) != 1)  // searched more than one data source or neither one
                                throw new System.Exception("found " + db_names.GetLength(0).ToString() + " databases");
                            rBoolCedent.db_name = db_names[0].GetPropertyString("DatabaseName");

                            // searching data matrix name
                            IBoxModule[] matrix_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.DataMatrix");
                            if (matrix_names.GetLength(0) != 1)  // searched more than one data source or neither one
                                throw new System.Exception("found " + matrix_names.GetLength(0).ToString() + " data matrixes");
                            rBoolCedent.matrix_name = matrix_names[0].GetPropertyString("Name");

                            // searching task name
                            rBoolCedent.task_name = box.UserName;


                            // filling the "task_type"
                            rBoolCedent.task_type = TT.TaskTypeLabel;

                            // filling the "cedent_type"
                            rBoolCedent.cedent_type = Typcedent.CedentTypeLabel;

                            // searching all parcial cedent
                            IBoxModule[] Subcedents = box.GetConnections(Typcedent.CedentTypeID);

                            foreach (IBoxModule Subcedent in Subcedents)
                            {
                                Rec_bool_cedent rBoolCedent1 = rBoolCedent;

                                // filling the ID
                                rBoolCedent1.id = id + counterID.ToString();
                                counterID++;

                                // setting "name"
                                rBoolCedent1.name = Subcedent.UserName;
                                // setting "length"
                                rBoolCedent1.length = Subcedent.GetPropertyLong("MinLen").ToString() + " - " + Subcedent.GetPropertyLong("MaxLen").ToString();
                                // searching all literals
                                IBoxModule[] literals = BoxesHelper.ListDirectAncestBoxesWithID(Subcedent, "DataMiningCommon.LiteralSetting");
                                // setting attribute "literal_cnt" (count of literals of parcial cedent)
                                rBoolCedent1.literal_cnt = literals.Length;

                                List<Rec_literal> rLiterals = new List<Rec_literal>();

                                #region Loop - processing of each literal of parcial cedent

                                foreach (IBoxModule litBox in literals)
                                {
                                    Rec_literal rLiteral = new Rec_literal();
                                    // setting attribute "literal_type" {Basic/Remaining}
                                    rLiteral.literal_type = litBox.GetPropertyString("LiteralType");
                                    // setting attribute "gace" {Positive/Negative/Both}
                                    rLiteral.gace = litBox.GetPropertyString("GaceType");

                                    // searching atom
                                    IBoxModule[] atoms = BoxesHelper.ListDirectAncestBoxesWithID(litBox, "DataMiningCommon.AtomSetting");
                                    if (atoms.Length != 1) // just one atom should be found
                                    {
                                        ErrStr += "Literal ID=" + litBox.ProjectIdentifier.ToString() + " : nalezeno " + atoms.Length.ToString() + " atom\n";
                                        continue; // processing of next literal
                                    }
                                    IBoxModule atomBox = atoms[0].Clone();

                                    // setting attribute "coefficient_type" {Interval/Subset/Cut/....}
                                    rLiteral.coefficient_type = atomBox.GetPropertyString("CoefficientType");
                                    // setting attribute "length"
                                    rLiteral.length = atomBox.GetPropertyLong("MinLen").ToString() + " - " + atomBox.GetPropertyLong("MaxLen").ToString();

                                    // searching attribute
                                    string[] AttrIDs = { "DataMiningCommon.Attributes.Attribute",
                                         "DataMiningCommon.Attributes.EquifrequencyIntervalsAttribute",
                                         "DataMiningCommon.Attributes.EquidistantIntervalsAttribute",
                                         "DataMiningCommon.Attributes.EachValueOneCategoryAttribute" };
                                    IBoxModule[] attributes = BoxesHelper.ListDirectAncestBoxesWithID(atomBox, AttrIDs);
                                    if (attributes.Length != 1) //just one attribute should be found
                                    {
                                        ErrStr += "Literal ID=" + litBox.ProjectIdentifier.ToString() + " : nalezeno " + attributes.Length.ToString() + " attribute\n";
                                        continue; // processing of next literal
                                    }
                                    IBoxModule attrBox = attributes[0].Clone();

                                    // setting attribute "underlying_attribute"
                                    rLiteral.underlying_attribute = attrBox.GetPropertyString("NameInLiterals");
                                    // setting attribute "category_cnt"
                                    rLiteral.category_cnt = attrBox.GetPropertyLong("CountOfCategories");
                                    // setting attribute "missing_type"
                                    rLiteral.missing_type = attrBox.GetPropertyString("IncludeNullCategory");

                                    // adding literal to list
                                    rLiterals.Add(rLiteral);
                                }
                                #endregion

                                // generating boolean cedent to XML
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
            // root element
            resultString += "</active_list>";

#if (LADENI)
            // Kody - storing output to file "XMLBool_cedentExample.xml" in directory 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLBool_cedentExample.xml");

            if (ErrStr != "") // LADICI
                MessageBox.Show("Chyby pri generating seznamu Boolskych cedent:\n" + ErrStr);
#endif

            return resultString;
        }

        

        /// <summary>
        /// Helping structure - all types of tasks processed in loop in getList() and it's items.
        /// </summary>
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

        /// <summary>
        /// Helping structure - all types of cedents processed in loop in getList() and it's items.
        /// </summary>
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
   
    #region --- Records ---

    /// <summary>
    /// Record of one boolean cedent.
    /// </summary>
    public class Rec_bool_cedent
    {
        #region DATA

        public string id = "";
        public string name = "unknown";
        public string db_name="unknown";
        public string matrix_name = "unknown";
        public string task_name = "unknown";
        public string task_type = "unknown";
        public string cedent_type = "unknown";
        public long literal_cnt = 0;
        public string length = "unknown";
        #endregion

        #region METHODS

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <param name="Literals">list of literals (subelements)</param>
        /// <returns>XML string</returns>
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

            // adding each subelement - literal
            foreach (Rec_literal Lit in Literals)
                XML += Lit.ToXML();

            XML += "</bool_cedent>";
            return XML;
        }

        #endregion
    }


    /// <summary>
    /// Record of one literal.
    /// </summary>
    public class Rec_literal
    {
        #region DATA

        public string underlying_attribute = "unknown";
        public long category_cnt = 0;
        public string missing_type = "unknown";
        public string coefficient_type = "unknown";
        public string length = "unknown";
        public string gace = "unknown";
        public string literal_type = "unknown";
        public string equivalence_class = "unknown";
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
