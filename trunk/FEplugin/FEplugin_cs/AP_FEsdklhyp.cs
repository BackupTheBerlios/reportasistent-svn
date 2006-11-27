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

    // ==================== Active element "SD-KL hypothesis" ================================

    /// <summary>
    /// Implementation of Active element "SD-KL hypothesis" (ID="hyp_sdkl")
    /// </summary>
    public class AP_FEsdklhyp
    {
        /// <summary>
        /// Returns XML string with all occurences of Active element "SD-KL hypothesis".
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

            string PropName = "Hypotheses";  // name of property which contain a list of hypotheses
            // searching all boxes SD-KL-tasks
            IBoxModule[] TaskBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, "LISpMinerTasks.SDKLTask");

            // processing of each box -  searching all KL-hypotheses
            string ErrStr = ""; // error report

            string matrix_name = "unknown";   // analyzed data matrix name
            string db_name="unknown";    // analyzed database name
            string task_name = "unknown";  // task name - given with user name of box FFTTast

            // creatind delegates for functions of quantifiers
            // "sum of values"
            ContingencyTable.QuantifierValue<TwoDimensionalContingencyTable> sum_delegat = new ContingencyTable.QuantifierValue<TwoDimensionalContingencyTable>(TwoDimensionalContingencyTable.GetSumOfValues);
            // "min value"
            ContingencyTable.QuantifierValue<TwoDimensionalContingencyTable> min_delegat = new ContingencyTable.QuantifierValue<TwoDimensionalContingencyTable>(TwoDimensionalContingencyTable.GetMinValue);
            // "max value"
            ContingencyTable.QuantifierValue<TwoDimensionalContingencyTable> max_delegat = new ContingencyTable.QuantifierValue<TwoDimensionalContingencyTable>(TwoDimensionalContingencyTable.GetMaxValue);
                


            #region Loop - processing of each KL-Task from array TaskBoxes

            foreach (IBoxModule box in TaskBoxes)
            {
                try
                {
                    // searching data source name (database)
                    IBoxModule[] db_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.Database");
                    if (db_names.GetLength(0) != 1)  // searched more than one data source or neither one
                        throw new System.Exception("found " + db_names.GetLength(0).ToString() + " databases");
                    db_name = (db_names[0].GetPropertyOther("DatabaseName") as StringT).stringValue;

                    // searching data matrix name
                    IBoxModule[] matrix_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.DataMatrix");
                    if (matrix_names.GetLength(0) != 1)  // searched more than one data source or neither one
                        throw new System.Exception("found " + matrix_names.GetLength(0).ToString() + " data matrixes");
                    matrix_name = (matrix_names[0].GetPropertyOther("Name") as StringT).stringValue;

                    // searching task name
                    task_name = box.UserName;

                    // searching the list of all hypotheses in this task
                    HypothesesT HypT = box.GetPropertyOther(PropName) as HypothesesT;
                    HypothesisStruct[] HypList = HypT.hypothesesValue.Clone() as HypothesisStruct[];

                    // records for storing the results
                    Rec_hyp_SDKL rHyp = new Rec_hyp_SDKL();   // SD-KL hypothesis
                    Rec_ti_attribute rAnt = new Rec_ti_attribute();  // Antecedent (Row attributes)
                    Rec_ti_attribute rSuc = new Rec_ti_attribute();  // Succedent (Column attributes)
                    Rec_ti_cedent rCon = new Rec_ti_cedent();  // condition
                    Rec_ti_cedent rSet1 = new Rec_ti_cedent();  // set 1
                    Rec_ti_cedent rSet2 = new Rec_ti_cedent();  // set 2


                    #region Loop - processing of each hypotheses jedne krabicky SDKLTask
                    // Loop over all hypotheses
                    for (int i = 0; i < HypList.GetLength(0); i++)
                    {
                        #region element hyp_SDKL

                        rHyp.id = "hypSDKL" + box.ProjectIdentifier.ToString() + "_" + i.ToString();
                        rHyp.db_name = db_name;
                        rHyp.matrix_name = matrix_name;
                        rHyp.task_name = task_name;
                        rHyp.row_attributes = "r_attr" + rHyp.id;
                        rHyp.column_attributes = "c_attr" + rHyp.id;
                        rHyp.condition = "con" + rHyp.id;
                        rHyp.set1 = "set1" + rHyp.id;
                        rHyp.set2 = "set2" + rHyp.id;
                        TwoDimensionalContingencyTable CT1 = new TwoDimensionalContingencyTable(HypList[i].quantifierSetting.firstContingencyTableRows); // Contingency Table 1
                        TwoDimensionalContingencyTable CT2 = new TwoDimensionalContingencyTable(HypList[i].quantifierSetting.secondContingencyTableRows); // Contingency Table 2
                        rHyp.Tab1 = HypList[i].quantifierSetting.firstContingencyTableRows;
                        rHyp.Tab2 = HypList[i].quantifierSetting.secondContingencyTableRows;


                        // values of quantifiers - set1
                        try
                        {
                            rHyp.sum1 = CT1.SumOfValues.ToString();
                            rHyp.min1 = CT1.MinValue.ToString();
                            rHyp.max1 = CT1.MaxValue.ToString();
                            rHyp.chi_sq1 = TwoDimensionalContingencyTable.ChiSquare(CT1).ToString();
                            rHyp.fnc_s1 = TwoDimensionalContingencyTable.SumOfRowMaximumsValue(CT1).ToString();
                            rHyp.fnc_r1 = TwoDimensionalContingencyTable.MinOfRowMaximumsValue(CT1).ToString();
                            rHyp.h_c1 = CT1.MarginalColumnEntropy.ToString();
                            rHyp.h_r1 = CT1.MarginalRowEntropy.ToString();
                            rHyp.h_c_r1 = TwoDimensionalContingencyTable.ConditionalCREntropyValue(CT1).ToString();
                            rHyp.mi1 = CT1.MutualInformation.ToString();
                            //rHyp.aic = CT.???;  TODO
                            rHyp.kend1 = TwoDimensionalContingencyTable.KendalValue(CT1).ToString();
                        }
                        catch (System.Exception e) // TODO: Ferda ma chyby ve vypoctech -> opravit! 
                        {
                            ErrStr += "Box ProjectIdentifier=" + box.ProjectIdentifier.ToString() + ": chyba pri vypoctu quantifier: " + e.Message + "\n";
                        }
                        // values of quantifiers - set2
                        try
                        {
                            rHyp.sum2 = CT2.SumOfValues.ToString();
                            rHyp.min2 = CT2.MinValue.ToString();
                            rHyp.max2 = CT2.MaxValue.ToString();
                            rHyp.chi_sq2 = TwoDimensionalContingencyTable.ChiSquare(CT2).ToString();
                            rHyp.fnc_s2 = TwoDimensionalContingencyTable.SumOfRowMaximumsValue(CT2).ToString();
                            rHyp.fnc_r2 = TwoDimensionalContingencyTable.MinOfRowMaximumsValue(CT2).ToString();
                            rHyp.h_c2 = CT2.MarginalColumnEntropy.ToString();
                            rHyp.h_r2 = CT2.MarginalRowEntropy.ToString();
                            rHyp.h_c_r2 = TwoDimensionalContingencyTable.ConditionalCREntropyValue(CT2).ToString();
                            rHyp.mi2 = CT2.MutualInformation.ToString();
                            //rHyp.aic = CT.???;  TODO
                            rHyp.kend2 = TwoDimensionalContingencyTable.KendalValue(CT2).ToString();
                        }
                        catch (System.Exception e) // Ferda ma chyby ve vypoctech! 
                        {
                            ErrStr += "Box ProjectIdentifier=" + box.ProjectIdentifier.ToString() + ": chyba pri vypoctu quantifier: " + e.Message + "\n";
                        }
                        // values of quantifiers - diffrent of set1 a set2
                        try
                        {
                            rHyp.da_sum = TwoDimensionalContingencyTable.Value<TwoDimensionalContingencyTable>(sum_delegat, CT1, CT2, OperationModeEnum.DifferencesOfAbsoluteFrequencies).ToString();
                            rHyp.da_min = TwoDimensionalContingencyTable.Value<TwoDimensionalContingencyTable>(min_delegat, CT1, CT2, OperationModeEnum.DifferencesOfAbsoluteFrequencies).ToString();
                            rHyp.da_max = TwoDimensionalContingencyTable.Value<TwoDimensionalContingencyTable>(max_delegat, CT1, CT2, OperationModeEnum.DifferencesOfAbsoluteFrequencies).ToString();
                            rHyp.dr_sum = TwoDimensionalContingencyTable.Value<TwoDimensionalContingencyTable>(sum_delegat, CT1, CT2, OperationModeEnum.DifferencesOfRelativeFrequencies).ToString();
                            rHyp.dr_min = TwoDimensionalContingencyTable.Value<TwoDimensionalContingencyTable>(min_delegat, CT1, CT2, OperationModeEnum.DifferencesOfRelativeFrequencies).ToString();
                            rHyp.dr_max = TwoDimensionalContingencyTable.Value<TwoDimensionalContingencyTable>(max_delegat, CT1, CT2, OperationModeEnum.DifferencesOfRelativeFrequencies).ToString();
                        }
                        catch (System.Exception e) // Ferda ma chyby ve vypoctech! 
                        {
                            ErrStr += "Box ProjectIdentifier=" + box.ProjectIdentifier.ToString() + ": chyba pri vypoctu quantifier: " + e.Message + "\n";
                        }





                        #endregion

                        #region element ti_attribute Row attributes (Antecedent)

                        rAnt.id = rHyp.row_attributes;
                        rAnt.type = "Row attributes";
                        rAnt.quant = "";   // deleting previous value
                        // category
                        List<Rec_ti_category> Cat_a = new List<Rec_ti_category>();
                        foreach (LiteralStruct lit in HypList[i].literals)
                        {
                            if (lit.cedentType == CedentEnum.Antecedent)
                            {
                                rAnt.quant += lit.literalName;
                                foreach (string s in lit.categoriesNames)
                                {
                                    Rec_ti_category C = new Rec_ti_category();
                                    C.value = s;
                                    Cat_a.Add(C);
                                }
                            }
                        }

                        #endregion

                        #region element ti_attribute Column attributes (Succedent)

                        rSuc.id = rHyp.column_attributes;
                        rSuc.type = "Column attributes";
                        rSuc.quant = "";   // deleting previous value
                        // category
                        List<Rec_ti_category> Cat_s = new List<Rec_ti_category>();
                        foreach (LiteralStruct lit in HypList[i].literals)
                        {
                            if (lit.cedentType == CedentEnum.Succedent)
                            {
                                rSuc.quant += lit.literalName;
                                foreach (string s in lit.categoriesNames)
                                {
                                    Rec_ti_category C = new Rec_ti_category();
                                    C.value = s;
                                    Cat_s.Add(C);
                                }
                            }
                        }

                        #endregion

                        #region element ti_cedent (Condition)

                        rCon.id = "con" + rHyp.id;
                        rCon.type = "Condition";
                        // literals
                        int litCounter = 0;  // counter of literals of this hypothesis
                        List<Rec_ti_literal> Lit_c = new List<Rec_ti_literal>();
                        foreach (BooleanLiteralStruct lit in HypList[i].booleanLiterals)
                        {
                            if (lit.cedentType == CedentEnum.Condition)
                            {
                                Rec_ti_literal l = new Rec_ti_literal();
                                l.id = "tiLit" + rHyp.id + "_" + litCounter.ToString();
                                litCounter++;
                                if (lit.negation)
                                    l.quant = "¬";
                                l.quant += lit.literalName;
                                int counter = 0;
                                foreach (string s in lit.categoriesNames)
                                {
                                    if (counter > 0)
                                        l.value += ",";
                                    l.value += s;
                                    counter++;
                                }
                                Lit_c.Add(l);
                            }
                        }

                        #endregion

                        #region element ti_cedent (Set1)

                        rSet1.id = rHyp.set1;
                        rSet1.type = "First Set";
                        // literals
                        List<Rec_ti_literal> Lit_s1 = new List<Rec_ti_literal>();
                        foreach (BooleanLiteralStruct lit in HypList[i].booleanLiterals)
                        {
                            if (lit.cedentType == CedentEnum.FirstSet)
                            {
                                Rec_ti_literal l = new Rec_ti_literal();
                                l.id = "tiLit" + rHyp.id + "_" + litCounter.ToString();
                                litCounter++;
                                if (lit.negation)
                                    l.quant = "¬";
                                l.quant += lit.literalName;
                                int counter = 0;
                                foreach (string s in lit.categoriesNames)
                                {
                                    if (counter > 0)
                                        l.value += ",";
                                    l.value += s;
                                    counter++;
                                }
                                Lit_s1.Add(l);
                            }
                        }

                        #endregion

                        #region element ti_cedent (Set2)

                        rSet2.id = rHyp.set2;
                        rSet2.type = "Second Set";
                        // literals
                        List<Rec_ti_literal> Lit_s2 = new List<Rec_ti_literal>();
                        foreach (BooleanLiteralStruct lit in HypList[i].booleanLiterals)
                        {
                            if (lit.cedentType == CedentEnum.SecondSet)
                            {
                                Rec_ti_literal l = new Rec_ti_literal();
                                l.id = "tiLit" + rHyp.id + "_" + litCounter.ToString();
                                litCounter++;
                                if (lit.negation)
                                    l.quant = "¬";
                                l.quant += lit.literalName;
                                int counter = 0;
                                foreach (string s in lit.categoriesNames)
                                {
                                    if (counter > 0)
                                        l.value += ",";
                                    l.value += s;
                                    counter++;
                                }
                                Lit_s2.Add(l);
                            }
                        }

                        #endregion


                        #region Generating of one hypothesis to XML string

                        string oneHypString = "";
                        // generating hypotheses to XML
                        oneHypString += rHyp.ToXML();
                        // generating Row attributes (Antecedent) to XML
                        oneHypString += rAnt.ToXML(Cat_a);
                        // generating Column attributes (Succedent) to XML
                        oneHypString += rSuc.ToXML(Cat_s);
                        // generating Condition to XML
                        oneHypString += rCon.ToXML(Lit_c);
                        // generating Set1 to XML
                        oneHypString += rSet1.ToXML(Lit_s1);
                        // generating Set2 to XML
                        oneHypString += rSet2.ToXML(Lit_s2);



                        resultString += oneHypString;

                        #endregion
                    }
                    #endregion
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
            // generating of error message:
            if (!String.IsNullOrEmpty(ErrStr))  // LADICI
                MessageBox.Show("Pri nacitani SD-KL hypotheses doslo k chybam:\n" + ErrStr, "Chyba", MessageBoxButtons.OK, MessageBoxIcon.Error);

            // LADICI - Kody - storing output to file "XMLsd4fthypExample.xml" in directory 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLsdKLhypExample.xml");
#endif

            return resultString;
        }
    }

    #region --- Records  ---

    /// <summary>
    /// Record for one SDKL hypothesis
    /// </summary>
    public class Rec_hyp_SDKL
    {
        #region DATA
        public string id = "";    // ID 4ft-hypotheses
        public string db_name = "unkonown";   // database name
        public string matrix_name = "unkonown"; // data matrix name
        public string task_name = "unkonown";   // task name

        public int[][] Tab1; // 1. contingency table
        public int[][] Tab2; // 2. contingency table

        // quantifiers - set1
        public string sum1 = "unknown";
        public string min1 = "unknown";
        public string max1 = "unknown";
        public string chi_sq1 = "unknown";
        public string fnc_s1 = "unknown";
        public string fnc_r1 = "unknown";
        public string h_c1 = "unknown";
        public string h_r1 = "unknown";
        public string h_c_r1 = "unknown";
        public string mi1 = "unknown";
        public string aic1 = "unknown";
        public string kend1 = "unknown";

        // quantifiers - set2
        public string sum2 = "unknown";
        public string min2 = "unknown";
        public string max2 = "unknown";
        public string chi_sq2 = "unknown";
        public string fnc_s2 = "unknown";
        public string fnc_r2 = "unknown";
        public string h_c2 = "unknown";
        public string h_r2 = "unknown";
        public string h_c_r2 = "unknown";
        public string mi2 = "unknown";
        public string aic2 = "unknown";
        public string kend2 = "unknown";

        // quantifiers - diffrent of set1 and set2
        public string da_sum = "unknown";
        public string da_min = "unknown";
        public string da_max = "unknown";
        public string dr_sum = "unknown";
        public string dr_min = "unknown";
        public string dr_max = "unknown";

        public string row_attributes = "";  // reference (Antecedent)
        public string column_attributes = "";  // reference (Succedent)
        public string condition = "";   // reference
        public string set1 = "";   // reference
        public string set2 = "";   // reference

        #endregion

        #region METHODS

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <returns>XML string</returns>
        public string ToXML()
        {
            string XML = "";

            XML += "<hyp_sdkl id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" task_name=\"" + task_name +
                // values of quantifiers - set1
                   "\" sum1=\"" + sum1 + "\" min1=\"" + min1 + "\" max1=\"" + max1 +
                   "\" chi_sq1=\"" + chi_sq1 + "\" fnc_s1=\"" + fnc_s1 +
                   "\" fnc_r1=\"" + fnc_r1 + "\" h_c1=\"" + h_c1 +
                   "\" h_r1=\"" + h_r1 + "\" h_c_r1=\"" + h_c_r1 +
                   "\" mi1=\"" + mi1 + "\" aic1=\"" + aic1 +
                   "\" kend1=\"" + kend1 +
                // values of quantifiers - set2
                   "\" sum2=\"" + sum2 + "\" min2=\"" + min2 + "\" max2=\"" + max2 +
                   "\" chi_sq2=\"" + chi_sq2 + "\" fnc_s2=\"" + fnc_s2 +
                   "\" fnc_r2=\"" + fnc_r2 + "\" h_c2=\"" + h_c2 +
                   "\" h_r2=\"" + h_r2 + "\" h_c_r2=\"" + h_c_r2 +
                   "\" mi2=\"" + mi2 + "\" aic2=\"" + aic2 +
                   "\" kend2=\"" + kend2 +
                // values of quantifiers - diffrent of set1 a set2
                   "\" da_sum=\"" + da_sum + "\" da_min=\"" + da_min +
                    "\" da_max=\"" + da_max + "\" dr_sum=\"" + dr_sum +
                    "\" dr_min=\"" + dr_min + "\" dr_max=\"" + dr_max +
                // cedents
                   "\" row_attributes=\"" + row_attributes + "\" column_attributes=\"" + column_attributes +
                   "\" condition=\"" + condition +
                   "\" set1=\"" + set1 +
                   "\" set2=\"" + set2 + "\">";

            // generating subelements - number values of contingency table
                // 1. table
            XML += "<tab>";
            foreach (int[] radek in Tab1)
            {
                XML += "<r>";
                foreach (int num in radek)
                {
                    XML += "<c val=\"" + num.ToString() + "\"/>";
                }
                XML += "</r>";
            }
            XML += "</tab>";

                // 2. table
            XML += "<tab>";
            foreach (int[] radek in Tab2)
            {
                XML += "<r>";
                foreach (int num in radek)
                {
                    XML += "<c val=\"" + num.ToString() + "\"/>";
                }
                XML += "</r>";
            }
            XML += "</tab>";


            XML += "</hyp_sdkl>";
            return XML;

        }
        #endregion
    }

    // Rec_ti_cedent & Rec_ti_literal implemented by AP_hypothesis_common

    #endregion
}
