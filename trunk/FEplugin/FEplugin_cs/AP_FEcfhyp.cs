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

    // ==================== Active element "CF hypothesis" ================================

    /// <summary>
    /// Implementation of active element "CF hypothesis" (ID="hyp_cf")
    /// </summary>
    public class AP_FEcfhyp
    {
        /// <summary>
        /// Implementation of Active element "CF hypothesis"
        /// </summary>
        /// <param name="index">index of data source in data sources tab </param>
        /// <returns>Returns XML string with all occurences of Active element type "CF hypothesis" from data source with given index</returns>
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
            // searching all boxes CF-task
            IBoxModule[] TaskBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, "LISpMinerTasks.CFTask");

            // processing of each box - searching all CF-hypotheses
            string ErrStr = ""; // error report

            string matrix_name = "unknown";   // analyzed data matrix name
            string db_name="unknown";    // analyzed database name
            string task_name = "unknown";  // task name - given by user name of box FFTTast

            
            #region Loop - processing of each CF-Tasku from array TaskBoxes

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
                    Rec_hyp_cf rHyp = new Rec_hyp_cf();   // CF hypothesis
                    Rec_ti_attribute rAnt = new Rec_ti_attribute();  // Antecedent (Attributes)
                    Rec_ti_cedent rCon = new Rec_ti_cedent();  // condition
             

                    #region Loop - processing of each hypotheses jedne krabicky CFTask
                    // Loop over all hypotheses
                    for (int i = 0; i < HypList.GetLength(0); i++)
                    {
                        #region element hyp_cf

                        rHyp.id = "hypcf" + box.ProjectIdentifier.ToString() + "_" + i.ToString();
                        rHyp.db_name = db_name;
                        rHyp.matrix_name = matrix_name;
                        rHyp.task_name = task_name;
                        rHyp.attributes = "attr" + rHyp.id;
                        rHyp.condition = "con" + rHyp.id;
                        OneDimensionalContingencyTable CT = new OneDimensionalContingencyTable(HypList[i].quantifierSetting.firstContingencyTableRows); // Contingency Table
                        rHyp.Tab = HypList[i].quantifierSetting.firstContingencyTableRows[0];
                        

                        // values of quantifiers
                        try
                        {
                            rHyp.sum = CT.SumOfValues.ToString();
                            rHyp.min = CT.MinValue.ToString();
                            rHyp.max = CT.MaxValue.ToString();
                            rHyp.v = CT.VariationRatio.ToString();
                            rHyp.nom_var = CT.NominalVariation.ToString();
                            rHyp.dor_var = CT.DiscreteOrdinaryVariation.ToString();
                            rHyp.avg_a = CT.ArithmeticAverage.ToString();
                            rHyp.avg_g = CT.GeometricAverage.ToString();
                            rHyp.var = CT.Variance.ToString();
                            rHyp.st_dev = CT.StandardDeviation.ToString();
                            rHyp.skew = CT.Skewness.ToString();
                            rHyp.asym = CT.Asymentry.ToString();
                        }
                        catch (System.Exception e) // !!There are some errors in Ferda quantifier values! !
                        {
                            ErrStr += "Box ProjectIdentifier=" + box.ProjectIdentifier.ToString() + ": chyba pri vypoctu kvantifikatoru: " + e.Message + "\n";
                        }
                        
                        
                        #endregion

                        #region element ti_attribute  Attributes (Antecedent)

                        rAnt.id = rHyp.attributes;
                        rAnt.type = "Attributes";
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

                        #region element ti_cedent (Condition)
                        int litCounter = 0;  // counter of literals of this cedent
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
                        // generating Attributes (Antecedent) to XML
                        oneHypString += rAnt.ToXML(Cat_a);
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
                MessageBox.Show("Pri nacitani CF hypotheses doslo k chybam:\n" + ErrStr, "Chyba", MessageBoxButtons.OK, MessageBoxIcon.Error);

            // LADICI - Kody - storing output to file "XMLsd4fthypExample.xml" in directory 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLcfhypExample.xml");
#endif

            return resultString;
        }
    }

    #region --- Records  ---

    /// <summary>
    /// Record of one CF hypothesis
    /// </summary>
    public class Rec_hyp_cf
    {
        #region DATA
        public string id = "";    // ID 4ft-hypothesis
        public string db_name="unknown";   // database name
        public string matrix_name = "unknown"; // data matrix name
        public string task_name = "unknown";   // task name

        public int[] Tab; // contingency table

        public string sum = "unknown";
        public string min = "unknown";
        public string max = "unknown";
        public string v = "unknown";
        public string nom_var = "unknown";
        public string dor_var = "unknown";
        public string avg_a = "unknown";
        public string avg_g = "unknown";
        public string var = "unknown";
        public string st_dev = "unknown";
        public string skew= "unknown";
        public string asym = "unknown";
        
        public string attributes = "";  // reference (Antecedent)
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

            id = XMLHelper.replaceXMLsign(id);
            db_name = XMLHelper.replaceXMLsign(db_name);
            matrix_name = XMLHelper.replaceXMLsign(matrix_name);
            task_name = XMLHelper.replaceXMLsign(task_name);
            


            XML += "<hyp_cf id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" task_name=\"" + task_name +
                // values of quantifiers
                   "\" sum=\"" + sum + "\" min=\"" + min + "\" max=\"" + max +
                   "\" v=\"" + v + "\" nom_var=\"" + nom_var +
                   "\" dor_var=\"" + dor_var + "\" avg_a=\"" + avg_a +
                   "\" avg_g=\"" + avg_g + "\" var=\"" + var +
                   "\" st_dev=\"" + st_dev + "\" skew=\"" + skew +
                   "\" asym=\"" + asym +
                // cedents
                   "\" attributes=\"" + attributes +
                   "\" condition=\"" + condition + "\">";

            // generating subelements - number values of contingency table
            XML += "<r>";
            foreach (int num in Tab)
                XML += "<c val=\"" + num.ToString() + "\"/>";
            XML += "</r>";
            
            
            XML += "</hyp_cf>";
            return XML;

        }
        #endregion
    }

    // Rec_ti_cedent & Rec_ti_literal implemented by AP 4ft-hypothesis

    #endregion
}
