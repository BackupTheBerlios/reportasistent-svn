using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;
using System.Windows.Forms;
using System.IO;
using Ferda;
using Ferda.ProjectManager;
using Ferda.ModulesManager;
using Ferda.Modules;
using Ferda.Modules.Helpers;
using Ferda.Modules.Quantifiers;


namespace FEplugin_cs
{

    // ==================== Active element "4FT hypothesis" ================================

    /// <summary>
    /// Implementation of Active element "4FT hypothesis" (ID="hyp_4ft")
    /// </summary>
    public class AP_FE4fthyp
    {
        /// <summary>
        /// Returns XML string with all occurences of Active element "4FT hypothesis".
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

            string PropName = "Hypotheses";  // name of Property, which contain list of hypotheses
            
            // searching all boxes with type "4FT-task"
            IBoxModule[] FFTTaskBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, "LISpMinerTasks.FFTTask");

            

            // loop over all boxes - getting all hypotheses

            string ErrStr = ""; // error report

            string matrix_name = "unknown";   // analyzed data matrix name
            string db_name="unknown";    // analyzed database name
            string task_name = "unknown";  // task name - given with user name of box FFTTast

            #region Loop - processing of each 4ft-Task from array FFTTaskBoxes

            foreach (IBoxModule box in FFTTaskBoxes)
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
                    Rec_hyp_4ft rHyp = new Rec_hyp_4ft();      // hypothesis
                    Rec_ti_cedent rAnt = new Rec_ti_cedent();  // antecedent
                    Rec_ti_cedent rSuc = new Rec_ti_cedent();  // succedent
                    Rec_ti_cedent rCon = new Rec_ti_cedent();  // condition

                    #region Loop - processing of each hypotez jedne krabicky FFTTask
                    // Loop over all hypotheses
                    for (int i = 0; i < HypList.GetLength(0); i++)
                    {
                        #region element hyp_4ft

                        rHyp.id = "hyp4ft" + box.ProjectIdentifier.ToString() + "_" + i.ToString();
                        rHyp.db_name = db_name;
                        rHyp.matrix_name = matrix_name;
                        rHyp.task_name = task_name;
                        rHyp.antecedent = "ant" + rHyp.id;
                        rHyp.succedent = "suc" + rHyp.id;
                        rHyp.condition = "con" + rHyp.id;
                        FourFoldContingencyTable FFT = new FourFoldContingencyTable(HypList[i].quantifierSetting.firstContingencyTableRows);
                        rHyp.a = FFT.A.ToString();
                        rHyp.b = FFT.B.ToString();
                        rHyp.c = FFT.C.ToString();
                        rHyp.d = FFT.D.ToString();
                        // values of quantifiers
                        rHyp.conf = FourFoldContingencyTable.FoundedImplicationValue(FFT).ToString();  // Founded implication (a/a+b)
                        rHyp.d_conf = FourFoldContingencyTable.DoubleFoundedImplicationValue(FFT).ToString(); // Double Founded implication (a/a+b+c)
                        rHyp.e_conf = FourFoldContingencyTable.FoundedEquivalenceValue(FFT).ToString();   // Founded Equivalence (a+d)/(a+b+c+d)  ??? BUG ve Ferdovi
                        rHyp.support = FourFoldContingencyTable.BaseCeilValue(FFT).ToString(); //???  Support (a/a+b+c+d)
                            // helping variable
                        double avg_diff = FourFoldContingencyTable.AboveAverageImplicationValue(FFT) - 1; // Averafe difference ((a*(a+b+c+d))/((a+b)*(a+c)) -1)
                        rHyp.avg_diff = avg_diff.ToString();
                        
                        rHyp.fisher = FFT.FisherValue().ToString();
                        rHyp.chi_sq = FFT.ChiSquareValue().ToString();

                        #endregion
                        

                        #region element ti_cedent (Antecedent)

                        rAnt.id = "ant" + rHyp.id;
                        rAnt.type = "Antecedent";
                        // literals
                        int litCounter = 0;  // counter of literals of this hypotheses
                        List<Rec_ti_literal> Lit_a = new List<Rec_ti_literal>();
                        foreach (BooleanLiteralStruct lit in HypList[i].booleanLiterals)
                        {
                            if (lit.cedentType == CedentEnum.Antecedent)
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
                                Lit_a.Add(l);
                            }
                        }
                        
                        #endregion

                        #region element ti_cedent (Succedent)

                        rSuc.id = "suc" + rHyp.id;
                        rSuc.type = "Succedent";
                        // literals
                        List<Rec_ti_literal> Lit_s = new List<Rec_ti_literal>();
                        foreach (BooleanLiteralStruct lit in HypList[i].booleanLiterals)
                        {
                            if (lit.cedentType == CedentEnum.Succedent)
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
                                Lit_s.Add(l);
                            }
                        }
                    
                        #endregion

                        #region element ti_cedent (Condition)

                        rCon.id = "con" + rHyp.id;
                        rCon.type = "Condition";
                        // literals
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
                        // generating Antecedent to XML
                        oneHypString += rAnt.ToXML(Lit_a);
                        // generating Succedent to XML
                        oneHypString += rSuc.ToXML(Lit_s);
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
            if (!String.IsNullOrEmpty(ErrStr))
                MessageBox.Show("Pri nacitani hypotez doslo k chybam:\n" + ErrStr, "Chyba", MessageBoxButtons.OK, MessageBoxIcon.Error);

            // Kody - storing output to file "XML4fthypExample.xml" in directory 
            XMLHelper.saveXMLexample(resultString, "../XML/XML4fthypExample.xml");
#endif
            return resultString;
        }
    }

    #region --- Records  ---

    /// <summary>
    /// Record of one 4FT hypothesis
    /// </summary>
    public class Rec_hyp_4ft
    {
        #region DATA
        public string id = "";    // ID 4ft-hypotheses
        public string db_name="unknown";   // database name
        public string matrix_name = "unknown"; // data matrix name
        public string task_name = "unknown";   // task name
        public string a = "unknown";
        public string b = "unknown";
        public string c = "unknown";
        public string d = "unknown";
        public string conf = "unknown";
        public string d_conf = "unknown";
        public string e_conf = "unknown";
        public string support = "unknown";
        public string completness = "unknown";
        public string avg_diff = "unknown";
        public string low_bnd_imp = "unknown";
        public string up_bnd_imp = "unknown";
        public string low_bnd_dbl_imp = "unknown";
        public string up_bnd_dbl_imp = "unknown";
        public string low_bnd_eq = "unknown";
        public string up_bnd_eq = "unknown";
        public string fisher = "unknown";
        public string chi_sq = "unknown";
        public string antecedent = "";  // reference
        public string succedent = "";   // reference
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

            XML += "<hyp_4ft id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" task_name=\"" + task_name + "\" a=\"" + a + "\" b=\"" + b +
                   "\" c=\"" + c + "\" d=\"" + d + "\" conf=\"" + conf +
                   "\" d_conf=\"" + d_conf + "\" e_conf=\"" + e_conf +
                   "\" support=\"" + support + "\" completeness=\"" + completness +
                   "\" avg_diff=\"" + avg_diff + "\" low_bnd_imp=\"" + low_bnd_imp +
                   "\" up_bnd_imp=\"" + up_bnd_imp + "\" low_bnd_dbl_imp=\"" + low_bnd_dbl_imp +
                   "\" up_bnd_dbl_imp=\"" + up_bnd_dbl_imp + "\" low_bnd_eq=\"" + low_bnd_eq +
                   "\" up_bnd_eq=\"" + up_bnd_eq + "\" fisher=\"" + fisher +
                   "\" chi_sq=\"" + chi_sq + "\" antecedent=\"" + antecedent +
                   "\" succedent=\"" + succedent + "\" condition=\"" + condition + "\"/>";
            return XML;

        }
        #endregion
    }

    // Rec_ti_cedent a Rec_ti_literal implemented in file "AP_hypotheses_common.cs"

    #endregion
}
