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
                MessageBox.Show("Chyba pri nacitani DTD: " + e.Message);
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
                    Rec_ti_cedent rAttr = new Rec_ti_cedent();  // Antecedent (attributes)
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
                            rHyp.sum1 = CT1.SumOfValues;
                            rHyp.min1 = CT1.MinValue;
                            rHyp.max1 = CT1.MaxValue;
                            rHyp.v1 = CT1.VariationRatio;
                            rHyp.nom_var1 = CT1.NominalVariation;
                            rHyp.dor_var1 = CT1.DiscreteOrdinaryVariation;
                            rHyp.avg_a1 = CT1.ArithmeticAverage;
                            rHyp.avg_g1 = CT1.GeometricAverage;
                            rHyp.var1 = CT1.Variance;
                            rHyp.st_dev1 = CT1.StandardDeviation;
                            rHyp.skew1 = CT1.Skewness;
                            rHyp.asym1 = CT1.Asymentry;
                        }
                        catch (System.Exception e) // TODO: Ferda ma chyby ve vypoctech -> opravit! 
                        {
                            ErrStr += "Box ProjectIdentifier=" + box.ProjectIdentifier.ToString() + ": chyba pri vypoctu kvantifikatoru: " + e.Message + "\n";
                        }

                        // hodnoty kvantifikatoru - set2
                        try
                        {
                            rHyp.sum2 = CT2.SumOfValues;
                            rHyp.min2 = CT2.MinValue;
                            rHyp.max2 = CT2.MaxValue;
                            rHyp.v2 = CT2.VariationRatio;
                            rHyp.nom_var2 = CT2.NominalVariation;
                            rHyp.dor_var2 = CT2.DiscreteOrdinaryVariation;
                            rHyp.avg_a2 = CT2.ArithmeticAverage;
                            rHyp.avg_g2 = CT2.GeometricAverage;
                            rHyp.var2 = CT2.Variance;
                            rHyp.st_dev2 = CT2.StandardDeviation;
                            rHyp.skew2 = CT2.Skewness;
                            rHyp.asym2 = CT2.Asymentry;
                        }
                        catch (System.Exception e) // TODO: Ferda ma chyby ve vypoctech -> opravit! 
                        {
                            ErrStr += "Box ProjectIdentifier=" + box.ProjectIdentifier.ToString() + ": chyba pri vypoctu kvantifikatoru: " + e.Message + "\n";
                        }

                        // hodnoty kvantifikatoru - rozdil set1 a set2
                        try
                        {
                            rHyp.da_sum = OneDimensionalContingencyTable.Value<OneDimensionalContingencyTable>(sum_delegat, CT1, CT2, OperationModeEnum.DifferencesOfAbsoluteFrequencies);
                            rHyp.da_min = OneDimensionalContingencyTable.Value<OneDimensionalContingencyTable>(min_delegat, CT1, CT2, OperationModeEnum.DifferencesOfAbsoluteFrequencies);
                            rHyp.da_max = OneDimensionalContingencyTable.Value<OneDimensionalContingencyTable>(max_delegat, CT1, CT2, OperationModeEnum.DifferencesOfAbsoluteFrequencies);
                            rHyp.dr_sum = OneDimensionalContingencyTable.Value<OneDimensionalContingencyTable>(sum_delegat, CT1, CT2, OperationModeEnum.DifferencesOfRelativeFrequencies);
                            rHyp.dr_min = OneDimensionalContingencyTable.Value<OneDimensionalContingencyTable>(min_delegat, CT1, CT2, OperationModeEnum.DifferencesOfRelativeFrequencies);
                            rHyp.dr_max = OneDimensionalContingencyTable.Value<OneDimensionalContingencyTable>(max_delegat, CT1, CT2, OperationModeEnum.DifferencesOfRelativeFrequencies);
                        }
                        catch (System.Exception e) // TODO: Ferda ma chyby ve vypoctech -> opravit! 
                        {
                            ErrStr += "Box ProjectIdentifier=" + box.ProjectIdentifier.ToString() + ": chyba pri vypoctu kvantifikatoru: " + e.Message + "\n";
                        }



                        #endregion

                        #region element ti_cedent Attributes (Antecedent)

                        rAttr.id = rHyp.attributes;
                        rAttr.type = "Attributes";
                        // literaly
                        int litCounter = 0;  // pocitadlo literalu teto hypotezy
                        List<Rec_ti_literal> Lit_a = new List<Rec_ti_literal>();
                        foreach (LiteralStruct lit in HypList[i].literals)
                        {
                            if (lit.cedentType == CedentEnum.Antecedent)
                            {
                                Rec_ti_literal l = new Rec_ti_literal();
                                l.id = "tiLit" + rHyp.id + "_" + litCounter.ToString();
                                litCounter++;
                                l.quant += lit.literalName;
                                foreach (string s in lit.categoriesNames)
                                    l.value += s;
                                // ??? k cemu je polozka LitralStruct.categoriesValues ?
                                Lit_a.Add(l);
                            }
                        }

                        #endregion

                        #region element ti_cedent (Condition)

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
                                foreach (string s in lit.categoriesNames)
                                    l.value += s;
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
                                foreach (string s in lit.categoriesNames)
                                    l.value += s;
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
                                foreach (string s in lit.categoriesNames)
                                    l.value += s;
                                Lit_s2.Add(l);
                            }
                        }

                        #endregion


                        #region Vypsani jedne hypotezy do XML stringu

                        string oneHypString = "";
                        // vypsani hypotezy do XML
                        oneHypString += rHyp.ToXML();
                        // vypsani Attributes (Antecedentu) do XML
                        oneHypString += rAttr.ToXML(Lit_a);
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

            // vypsani pripadne chybove hlasky:
            if (!String.IsNullOrEmpty(ErrStr))  // LADICI
                MessageBox.Show("Pri nacitani SD-CF hypotez doslo k chybam:\n" + ErrStr, "Chyba", MessageBoxButtons.OK, MessageBoxIcon.Error);

            // korenovy element
            resultString += "</active_list>";

            // LADICI - Kody - ulozeni vystupu do souboru "XMLsd4fthypExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLsdcfhypExample.xml");

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
        public double sum1 = 0;
        public double min1 = 0;
        public double max1 = 0;
        public double v1 = 0;
        public double nom_var1 = 0;
        public double dor_var1 = 0;
        public double avg_a1 = 0;
        public double avg_g1 = 0;
        public double var1 = 0;
        public double st_dev1 = 0;
        public double skew1 = 0;
        public double asym1 = 0;
        
        // kvantifikatory - set2
        public double sum2 = 0;
        public double min2 = 0;
        public double max2 = 0;
        public double v2 = 0;
        public double nom_var2 = 0;
        public double dor_var2 = 0;
        public double avg_a2 = 0;
        public double avg_g2 = 0;
        public double var2 = 0;
        public double st_dev2 = 0;
        public double skew2 = 0;
        public double asym2 = 0;

        // kvantifikatory - rozdil set1 a set2
        public double da_sum = 0;
        public double da_min = 0;
        public double da_max = 0;
        public double dr_sum = 0;
        public double dr_min = 0;
        public double dr_max = 0;

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
                   "\" sum1=\"" + sum1.ToString() + "\" min1=\"" + min1.ToString() + "\" max1=\"" + max1.ToString() +
                   "\" v1=\"" + v1.ToString() + "\" nom_var1=\"" + nom_var1.ToString() +
                   "\" dor_var1=\"" + dor_var1.ToString() + "\" avg_a1=\"" + avg_a1.ToString() +
                   "\" avg_g1=\"" + avg_g1.ToString() + "\" var1=\"" + var1.ToString() +
                   "\" st_dev1=\"" + st_dev1.ToString() + "\" skew1=\"" + skew1.ToString() +
                   "\" asym1=\"" + asym1.ToString() +
                // hodnoty kvantifikatoru - set2
                   "\" sum2=\"" + sum2.ToString() + "\" min2=\"" + min2.ToString() + "\" max2=\"" + max2.ToString() +
                   "\" v2=\"" + v2.ToString() + "\" nom_var2=\"" + nom_var2.ToString() +
                   "\" dor_var2=\"" + dor_var2.ToString() + "\" avg_a2=\"" + avg_a2.ToString() +
                   "\" avg_g2=\"" + avg_g2.ToString() + "\" var2=\"" + var2.ToString() +
                   "\" st_dev2=\"" + st_dev2.ToString() + "\" skew2=\"" + skew2.ToString() +
                   "\" asym2=\"" + asym2.ToString() +
                // hodnoty kvantifikatoru - rozdil set1 a set2
                    "\" da_sum=\"" + da_sum.ToString() + "\" da_min=\"" + da_min.ToString() + 
                    "\" da_max=\"" + da_max.ToString() + "\" dr_sum=\"" + dr_sum.ToString() +
                    "\" dr_min=\"" + dr_min.ToString() + "\" dr_max=\"" + dr_max.ToString() +
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
