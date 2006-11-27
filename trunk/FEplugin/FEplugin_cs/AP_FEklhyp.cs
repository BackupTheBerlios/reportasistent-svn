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

    // ==================== Active element "KL hypothesis" ================================

    /// <summary>
    /// Implementation of active element "KL hypothesis" (ID="hyp_kl")
    /// </summary>
    public class AP_FEklhyp
    {
        /// <summary>
        /// Returns XML string with all occurences of Active element "KL hypothesis".
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
            // searching all boxes KL-uloh
            IBoxModule[] TaskBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, "LISpMinerTasks.KLTask");

            // processing of each box - searching all KL-hypotheses
            string ErrStr = ""; // error report

            string matrix_name = "unknown";   // analyzed data matrix name
            string db_name="unknown";    // analyzed database name
            string task_name = "unknown";  // task name - given with user name of box FFTTast


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
                    Rec_hyp_KL rHyp = new Rec_hyp_KL();   // KL hypothesis
                    Rec_ti_attribute rAnt = new Rec_ti_attribute();  // Antecedent (Row attributes)
                    Rec_ti_attribute rSuc = new Rec_ti_attribute();  // Succedent (Column attributes)
                    Rec_ti_cedent rCon = new Rec_ti_cedent();  // condition


                    #region Loop - processing of each hypotheses jedne krabicky KLTask
                    // Loop over all hypotheses
                    for (int i = 0; i < HypList.GetLength(0); i++)
                    {
                        #region element hyp_KL

                        rHyp.id = "hypKL" + box.ProjectIdentifier.ToString() + "_" + i.ToString();
                        rHyp.db_name = db_name;
                        rHyp.matrix_name = matrix_name;
                        rHyp.task_name = task_name;
                        rHyp.row_attributes = "r_attr" + rHyp.id;
                        rHyp.column_attributes = "c_attr" + rHyp.id;
                        rHyp.condition = "con" + rHyp.id;
                        TwoDimensionalContingencyTable CT = new TwoDimensionalContingencyTable(HypList[i].quantifierSetting.firstContingencyTableRows); // Contingency Table
                        rHyp.Tab = HypList[i].quantifierSetting.firstContingencyTableRows;


                        // values of quantifiers - first set
                        try
                        {
                            rHyp.sum = CT.SumOfValues.ToString();
                            rHyp.min = CT.MinValue.ToString();
                            rHyp.max = CT.MaxValue.ToString();
                            rHyp.chi_sq = TwoDimensionalContingencyTable.ChiSquare(CT).ToString();
                            rHyp.fnc_s = TwoDimensionalContingencyTable.SumOfRowMaximumsValue(CT).ToString();
                            rHyp.fnc_r = TwoDimensionalContingencyTable.MinOfRowMaximumsValue(CT).ToString();
                            rHyp.h_c = CT.MarginalColumnEntropy.ToString();
                            rHyp.h_r = CT.MarginalRowEntropy.ToString();
                            rHyp.h_c_r = TwoDimensionalContingencyTable.ConditionalCREntropyValue(CT).ToString();
                            rHyp.mi = CT.MutualInformation.ToString();
                            //rHyp.aic = CT.???;  TODO
                            rHyp.kend = TwoDimensionalContingencyTable.KendalValue(CT).ToString();
                        }
                        catch (System.Exception e) // There are some errors in Ferda quantifier values! 
                        {
                            ErrStr += "Box ProjectIdentifier=" + box.ProjectIdentifier.ToString() + ": chyba pri vypoctu kvantifikatoru: " + e.Message + "\n";
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
                                // ??? k cemu je polozka LitralStruct.categoriesValues ?
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
                                // ??? k cemu je polozka LitralStruct.categoriesValues ?
                            }
                        }

                        #endregion

                        #region element ti_cedent (Condition)

                        rCon.id = "con" + rHyp.id;
                        rCon.type = "Condition";
                        // literals
                        int litCounter = 0;  // counter of literals of this hypotheses
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


                        #region Generating of one hypotheses to XML string

                        string oneHypString = "";
                        // generating hypotheses to XML
                        oneHypString += rHyp.ToXML();
                        // generating Row attributes (Antecedent) to XML
                        oneHypString += rAnt.ToXML(Cat_a);
                        // generating Column attributes (Succedent) to XML
                        oneHypString += rSuc.ToXML(Cat_s);
                        // generating Condition to XML
                        oneHypString += rCon.ToXML(Lit_c);



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
                MessageBox.Show("Pri nacitani KL hypotheses doslo k chybam:\n" + ErrStr, "Chyba", MessageBoxButtons.OK, MessageBoxIcon.Error);

            // LADICI - Kody - storing output to file "XMLsd4fthypExample.xml" in directory 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLKLhypExample.xml");
#endif

            return resultString;
        }
    }

    #region --- Records  ---

    /// <summary>
    /// Record for one KL hypothesis
    /// </summary>
    public class Rec_hyp_KL
    {
        #region DATA

        public string id = ""; // ID 
        public string db_name="unknown";   // database name
        public string matrix_name = "unknown"; // data matrix name
        public string task_name = "unknown";   // task name

        public int[][] Tab; // contingency table

        public string sum = "unknown";
        public string min = "unknown";
        public string max = "unknown";
        public string chi_sq = "unknown";
        public string fnc_s = "unknown";
        public string fnc_r = "unknown";
        public string h_c = "unknown";
        public string h_r = "unknown";
        public string h_c_r = "unknown";
        public string mi = "unknown";
        public string aic = "unknown";
        public string kend = "unknown";

        public string row_attributes = "";  // reference (Antecedent)
        public string column_attributes = "";  // reference (Succedent)
        public string condition = "";   // reference

        #endregion

        #region METHODS

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <returns>XML string</returns>
        public string ToXML()
        {
            string XML = "";

            XML += "<hyp_kl id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" task_name=\"" + task_name +
                // values of quantifiers
                   "\" sum=\"" + sum + "\" min=\"" + min + "\" max=\"" + max +
                   "\" chi_sq=\"" + chi_sq + "\" fnc_s=\"" + fnc_s +
                   "\" fnc_r=\"" + fnc_r + "\" h_c=\"" + h_c +
                   "\" h_r=\"" + h_r + "\" h_c_r=\"" + h_c_r +
                   "\" mi=\"" + mi + "\" aic=\"" + aic +
                   "\" kend=\"" + kend +
                // cedents
                   "\" row_attributes=\"" + row_attributes + "\" column_attributes=\"" + column_attributes +
                   "\" condition=\"" + condition + "\">";

            // generating subelements - number values of contingency table
            XML += "<tab>";
            /* Asi blba verze - prohozeny radky a column
             * 
            int radku = Tab[0].GetLength(0);
            int sloupcu = Tab.GetLength(0);

            for(int i=0; i<radku; i++)
            {
                XML += "<r>";
                for(int j=0; j<sloupcu; j++)
                    XML += "<c val=\"" + Tab[j][i].ToString() + "\"/>";
                XML += "</r>";
            }
             * */
            foreach (int[] radek in Tab)
            { 
                XML += "<r>";
                foreach (int num in radek)
                {
                    XML += "<c val=\"" + num.ToString() + "\"/>";
                }
                XML += "</r>";
            }

            XML += "</tab>";


            XML += "</hyp_kl>";
            return XML;

        }
        #endregion
    }

    // Rec_ti_cedent & Rec_ti_literal implemented by AP 4ft-hypothesis

    #endregion
}
