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

    // ==================== Aktivni prvek SD-CF-hypoteza ================================

    public class AP_FEsdcfhyp
    {
        /// <summary>
        /// Implementation of Active element "SD-CF hypothesis"
        /// </summary>
        /// <param name="index">index of data source in data sources tab </param>
        /// <returns>Returns XML string with all occurences of Active element type "SD-CF hypothesis" from data source with given index</returns>
        public static string getList(int index)
        {
            string resultString = ""; // vysledny XML string

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

            string PropName = "Hypotheses";  // nazev Property, ktera obsahuje seznam hypotez
            // nalezeni vsech krabicek CF-uloh
            IBoxModule[] TaskBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, "LISpMinerTasks.SDCFTask");

            // zpracovani kazde krabicky - ziskani z ni vsechny CF-hypotezy
            string ErrStr = ""; // zaznam o chybach

            string matrix_name = "";   // jmeno analyzovane matice
            string db_name = "";    // jmeno analyzovane databaze
            string task_name = "";  // jmeno ulohy - dano uzivatelskym nazvem krabicky FFTTast

            // vytvoreni delegatu funkci kvantifikatoru
                // "sum of values"
            ContingencyTable.QuantifierValue<OneDimensionalContingencyTable> sum_delegat = new ContingencyTable.QuantifierValue<OneDimensionalContingencyTable>(OneDimensionalContingencyTable.GetSumOfValues);
                // "min value"
            ContingencyTable.QuantifierValue<OneDimensionalContingencyTable> min_delegat = new ContingencyTable.QuantifierValue<OneDimensionalContingencyTable>(OneDimensionalContingencyTable.GetMinValue);
                // "max value"
            ContingencyTable.QuantifierValue<OneDimensionalContingencyTable> max_delegat = new ContingencyTable.QuantifierValue<OneDimensionalContingencyTable>(OneDimensionalContingencyTable.GetMaxValue);
                


            #region Cyklus - zpracovani vsech CF-Tasku z pole TaskBoxes

            foreach (IBoxModule box in TaskBoxes)
            {
                try
                {
                    // nalezeni jmena datoveho zdroje (databaze)
                    IBoxModule[] db_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.Database");
                    if (db_names.GetLength(0) != 1)  // byl nalezen pocet datovych zdroju ruzny od jedne
                        throw new System.Exception("bylo nalezeno " + db_names.GetLength(0).ToString() + " databazi");
                    db_name = (db_names[0].GetPropertyOther("DatabaseName") as StringT).stringValue;

                    // nalezeni jmena datove matice
                    IBoxModule[] matrix_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.DataMatrix");
                    if (matrix_names.GetLength(0) != 1)  // byl nalezen pocet datovych matic ruzny od jedne
                        throw new System.Exception("bylo nalezeno " + matrix_names.GetLength(0).ToString() + " datovych matic");
                    matrix_name = (matrix_names[0].GetPropertyOther("Name") as StringT).stringValue;

                    // nalezeni jmena ulohy
                    task_name = box.UserName;

                    // nalezeni seznamu vsech hypotez v tomto Tasku
                    HypothesesT HypT = box.GetPropertyOther(PropName) as HypothesesT;
                    HypothesisStruct[] HypList = HypT.hypothesesValue.Clone() as HypothesisStruct[];

                    // recordy pro ukladani vysledku
                    Rec_hyp_sdcf rHyp = new Rec_hyp_sdcf();   // CF hypoteza
                    Rec_ti_attribute rAnt = new Rec_ti_attribute();  // Antecedent (Attributes)
                    Rec_ti_cedent rCon = new Rec_ti_cedent();  // Condition
                    Rec_ti_cedent rSet1 = new Rec_ti_cedent();  // set 1
                    Rec_ti_cedent rSet2 = new Rec_ti_cedent();  // set 2


                    #region Cyklus - zpracovani vsech hypotez jedne krabicky CFTask
                    // cyklus pres vsechny hypotezy
                    for (int i = 0; i < HypList.GetLength(0); i++)
                    {
                        #region element hyp_sdcf

                        rHyp.id = "hypsdcf" + box.ProjectIdentifier.ToString() + "_" + i.ToString();
                        rHyp.db_name = db_name;
                        rHyp.matrix_name = matrix_name;
                        rHyp.task_name = task_name;
                        rHyp.attributes = "attr" + rHyp.id;
                        rHyp.condition = "con" + rHyp.id;
                        rHyp.set1 = "set1" + rHyp.id;
                        rHyp.set2 = "set2" + rHyp.id;

                        OneDimensionalContingencyTable CT1 = new OneDimensionalContingencyTable(HypList[i].quantifierSetting.firstContingencyTableRows); // Contingency Table 1
                        OneDimensionalContingencyTable CT2 = new OneDimensionalContingencyTable(HypList[i].quantifierSetting.secondContingencyTableRows); // Contingency Table 2
                        rHyp.Tab1 = HypList[i].quantifierSetting.firstContingencyTableRows[0];
                        rHyp.Tab2 = HypList[i].quantifierSetting.secondContingencyTableRows[0];


                        // hodnoty kvantifikatoru - set1
                        try
                        {
                            rHyp.sum1 = CT1.SumOfValues.ToString();
                            rHyp.min1 = CT1.MinValue.ToString();
                            rHyp.max1 = CT1.MaxValue.ToString();
                            rHyp.v1 = CT1.VariationRatio.ToString();
                            rHyp.nom_var1 = CT1.NominalVariation.ToString();
                            rHyp.dor_var1 = CT1.DiscreteOrdinaryVariation.ToString();
                            rHyp.avg_a1 = CT1.ArithmeticAverage.ToString();
                            rHyp.avg_g1 = CT1.GeometricAverage.ToString();
                            rHyp.var1 = CT1.Variance.ToString();
                            rHyp.st_dev1 = CT1.StandardDeviation.ToString();
                            rHyp.skew1 = CT1.Skewness.ToString();
                            rHyp.asym1 = CT1.Asymentry.ToString();
                        }
                        catch (System.Exception e) // TODO: Ferda ma chyby ve vypoctech -> opravit! 
                        {
                            ErrStr += "Box ProjectIdentifier=" + box.ProjectIdentifier.ToString() + ": chyba pri vypoctu kvantifikatoru: " + e.Message + "\n";
                        }

                        // hodnoty kvantifikatoru - set2
                        try
                        {
                            rHyp.sum2 = CT2.SumOfValues.ToString();
                            rHyp.min2 = CT2.MinValue.ToString();
                            rHyp.max2 = CT2.MaxValue.ToString();
                            rHyp.v2 = CT2.VariationRatio.ToString();
                            rHyp.nom_var2 = CT2.NominalVariation.ToString();
                            rHyp.dor_var2 = CT2.DiscreteOrdinaryVariation.ToString();
                            rHyp.avg_a2 = CT2.ArithmeticAverage.ToString();
                            rHyp.avg_g2 = CT2.GeometricAverage.ToString();
                            rHyp.var2 = CT2.Variance.ToString();
                            rHyp.st_dev2 = CT2.StandardDeviation.ToString();
                            rHyp.skew2 = CT2.Skewness.ToString();
                            rHyp.asym2 = CT2.Asymentry.ToString();
                        }
                        catch (System.Exception e) // TODO: Ferda ma chyby ve vypoctech -> opravit! 
                        {
                            ErrStr += "Box ProjectIdentifier=" + box.ProjectIdentifier.ToString() + ": chyba pri vypoctu kvantifikatoru: " + e.Message + "\n";
                        }

                        // hodnoty kvantifikatoru - rozdil set1 a set2
                        try
                        {
                            rHyp.da_sum = OneDimensionalContingencyTable.Value<OneDimensionalContingencyTable>(sum_delegat, CT1, CT2, OperationModeEnum.DifferencesOfAbsoluteFrequencies).ToString();
                            rHyp.da_min = OneDimensionalContingencyTable.Value<OneDimensionalContingencyTable>(min_delegat, CT1, CT2, OperationModeEnum.DifferencesOfAbsoluteFrequencies).ToString();
                            rHyp.da_max = OneDimensionalContingencyTable.Value<OneDimensionalContingencyTable>(max_delegat, CT1, CT2, OperationModeEnum.DifferencesOfAbsoluteFrequencies).ToString();
                            rHyp.dr_sum = OneDimensionalContingencyTable.Value<OneDimensionalContingencyTable>(sum_delegat, CT1, CT2, OperationModeEnum.DifferencesOfRelativeFrequencies).ToString();
                            rHyp.dr_min = OneDimensionalContingencyTable.Value<OneDimensionalContingencyTable>(min_delegat, CT1, CT2, OperationModeEnum.DifferencesOfRelativeFrequencies).ToString();
                            rHyp.dr_max = OneDimensionalContingencyTable.Value<OneDimensionalContingencyTable>(max_delegat, CT1, CT2, OperationModeEnum.DifferencesOfRelativeFrequencies).ToString();
                        }
                        catch (System.Exception e) // TODO: Ferda ma chyby ve vypoctech -> opravit! 
                        {
                            ErrStr += "Box ProjectIdentifier=" + box.ProjectIdentifier.ToString() + ": chyba pri vypoctu kvantifikatoru: " + e.Message + "\n";
                        }



                        #endregion

                        #region element ti_attribute  Attributes (Antecedent)

                        rAnt.id = rHyp.attributes;
                        rAnt.type = "Attributes";
                        rAnt.quant = "";   // smazani predchozi hodnoty
                        // kategorie
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

                        #region element ti_cedent (Condition)

                        int litCounter = 0;  // pocitadlo literalu tohoto cedentu
                        rCon.id = "con" + rHyp.id;
                        rCon.type = "Condition";
                        // literaly
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
                        // literaly
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
                        // literaly
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


                        #region Vypsani jedne hypotezy do XML stringu

                        string oneHypString = "";
                        // vypsani hypotezy do XML
                        oneHypString += rHyp.ToXML();
                        // vypsani Attributes (Antecedentu) do XML
                        oneHypString += rAnt.ToXML(Cat_a);
                        // vypsani Condition do XML
                        oneHypString += rCon.ToXML(Lit_c);
                        // vypsani Set1 do XML
                        oneHypString += rSet1.ToXML(Lit_s1);
                        // vypsani Set2 do XML
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

            
            // korenovy element
            resultString += "</active_list>";
            
#if (LADENI)           
            // vypsani pripadne chybove hlasky:
            if (!String.IsNullOrEmpty(ErrStr))  // LADICI
                MessageBox.Show("Pri nacitani SD-CF hypotez doslo k chybam:\n" + ErrStr, "Chyba", MessageBoxButtons.OK, MessageBoxIcon.Error);

           
            // LADICI - Kody - ulozeni vystupu do souboru "XMLsd4fthypExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLsdcfhypExample.xml");
#endif

            return resultString;
        }
    }

    #region --- Recordy  ---

    public class Rec_hyp_sdcf
    {
        #region DATA
        public string id = "";    // ID 4ft-hypotezy
        public string db_name = "";   // jmeno databaze
        public string matrix_name = ""; // jmeno datove matice
        public string task_name = "";   // jmeno ulohy

        public int[] Tab1; // 1. kontingencni tabulka
        public int[] Tab2; // 2. kontingencni tabulka

        // kvantifikatory - set1
        public string sum1 = "unknown";
        public string min1 = "unknown";
        public string max1 = "unknown";
        public string v1 = "unknown";
        public string nom_var1 = "unknown";
        public string dor_var1 = "unknown";
        public string avg_a1 = "unknown";
        public string avg_g1 = "unknown";
        public string var1 = "unknown";
        public string st_dev1 = "unknown";
        public string skew1 = "unknown";
        public string asym1 = "unknown";
        
        // kvantifikatory - set2
        public string sum2 = "unknown";
        public string min2 = "unknown";
        public string max2 = "unknown";
        public string v2 = "unknown";
        public string nom_var2 = "unknown";
        public string dor_var2 = "unknown";
        public string avg_a2 = "unknown";
        public string avg_g2 = "unknown";
        public string var2 = "unknown";
        public string st_dev2 = "unknown";
        public string skew2 = "unknown";
        public string asym2 = "unknown";

        // kvantifikatory - rozdil set1 a set2
        public string da_sum = "unknown";
        public string da_min = "unknown";
        public string da_max = "unknown";
        public string dr_sum = "unknown";
        public string dr_min = "unknown";
        public string dr_max = "unknown";

        public string attributes = "";  // reference (Antecedent)
        public string condition = "";   // reference
        public string set1 = "";   // reference
        public string set2 = "";   // reference

        #endregion

        #region METHODS
        // prevod recordu na XML string
        public string ToXML()
        {
            string XML = "";

            XML += "<hyp_sdcf id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" task_name=\"" + task_name +
                // hodnoty kvantifikatoru - set1
                   "\" sum1=\"" + sum1 + "\" min1=\"" + min1 + "\" max1=\"" + max1 +
                   "\" v1=\"" + v1 + "\" nom_var1=\"" + nom_var1 +
                   "\" dor_var1=\"" + dor_var1 + "\" avg_a1=\"" + avg_a1 +
                   "\" avg_g1=\"" + avg_g1 + "\" var1=\"" + var1 +
                   "\" st_dev1=\"" + st_dev1 + "\" skew1=\"" + skew1 +
                   "\" asym1=\"" + asym1 +
                // hodnoty kvantifikatoru - set2
                   "\" sum2=\"" + sum2 + "\" min2=\"" + min2 + "\" max2=\"" + max2 +
                   "\" v2=\"" + v2 + "\" nom_var2=\"" + nom_var2 +
                   "\" dor_var2=\"" + dor_var2 + "\" avg_a2=\"" + avg_a2 +
                   "\" avg_g2=\"" + avg_g2 + "\" var2=\"" + var2 +
                   "\" st_dev2=\"" + st_dev2 + "\" skew2=\"" + skew2 +
                   "\" asym2=\"" + asym2 +
                // hodnoty kvantifikatoru - rozdil set1 a set2
                    "\" da_sum=\"" + da_sum + "\" da_min=\"" + da_min + 
                    "\" da_max=\"" + da_max + "\" dr_sum=\"" + dr_sum +
                    "\" dr_min=\"" + dr_min + "\" dr_max=\"" + dr_max +
                // cedenty
                   "\" attributes=\"" + attributes +
                   "\" condition=\"" + condition +
                   "\" set1=\"" + set1 +
                   "\" set2=\"" + set2 + "\">";

            // vygenerovani podelementu - ciselnych hodnot kontingencni tabulky
            // prvni tabulka
            XML += "<r>";
            foreach (int num in Tab1)
                XML += "<c val=\"" + num.ToString() + "\"/>";
            XML += "</r>";
            // druha tabulka
            XML += "<r>";
            foreach (int num in Tab2)
                XML += "<c val=\"" + num.ToString() + "\"/>";
            XML += "</r>";


            XML += "</hyp_sdcf>";
            return XML;

        }
        #endregion
    }

    // Rec_ti_cedent & Rec_ti_literal implementovany u AP 4ft-hypoteza

    #endregion
}
