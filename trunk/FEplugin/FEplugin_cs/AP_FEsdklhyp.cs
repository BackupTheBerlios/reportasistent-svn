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

    // ==================== Aktivni prvek SD-KL-hypoteza ================================

    public class AP_FEsdklhyp
    {
        /// <summary>
        /// Implementation of Active element "SD-KL hypothesis"
        /// </summary>
        /// <param name="index">index of data source in data sources tab </param>
        /// <returns>Returns XML string with all occurences of Active element type "SD-KL hypothesis" from data source with given index</returns>
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
            // nalezeni vsech krabicek SD-KL-uloh
            IBoxModule[] TaskBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, "LISpMinerTasks.SDKLTask");

            // zpracovani kazde krabicky - ziskani z ni vsechny KL-hypotezy
            string ErrStr = ""; // zaznam o chybach

            string matrix_name = "";   // jmeno analyzovane matice
            string db_name = "";    // jmeno analyzovane databaze
            string task_name = "";  // jmeno ulohy - dano uzivatelskym nazvem krabicky FFTTast

            // vytvoreni delegatu funkci kvantifikatoru
            // "sum of values"
            ContingencyTable.QuantifierValue<TwoDimensionalContingencyTable> sum_delegat = new ContingencyTable.QuantifierValue<TwoDimensionalContingencyTable>(TwoDimensionalContingencyTable.GetSumOfValues);
            // "min value"
            ContingencyTable.QuantifierValue<TwoDimensionalContingencyTable> min_delegat = new ContingencyTable.QuantifierValue<TwoDimensionalContingencyTable>(TwoDimensionalContingencyTable.GetMinValue);
            // "max value"
            ContingencyTable.QuantifierValue<TwoDimensionalContingencyTable> max_delegat = new ContingencyTable.QuantifierValue<TwoDimensionalContingencyTable>(TwoDimensionalContingencyTable.GetMaxValue);
                


            #region Cyklus - zpracovani vsech KL-Tasku z pole TaskBoxes

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
                    Rec_hyp_SDKL rHyp = new Rec_hyp_SDKL();   // SD-KL hypoteza
                    Rec_ti_cedent rAnt = new Rec_ti_cedent();  // Antecedent (Row attributes)
                    Rec_ti_cedent rSuc = new Rec_ti_cedent();  // Succedent (Column attributes)
                    Rec_ti_cedent rCon = new Rec_ti_cedent();  // condition
                    Rec_ti_cedent rSet1 = new Rec_ti_cedent();  // set 1
                    Rec_ti_cedent rSet2 = new Rec_ti_cedent();  // set 2


                    #region Cyklus - zpracovani vsech hypotez jedne krabicky SDKLTask
                    // cyklus pres vsechny hypotezy
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


                        // hodnoty kvantifikatoru - set1
                        try
                        {
                            rHyp.sum1 = CT1.SumOfValues;
                            rHyp.min1 = CT1.MinValue;
                            rHyp.max1 = CT1.MaxValue;
                            rHyp.chi_sq1 = TwoDimensionalContingencyTable.ChiSquare(CT1);
                            rHyp.fnc_s1 = TwoDimensionalContingencyTable.SumOfRowMaximumsValue(CT1);
                            rHyp.fnc_r1 = TwoDimensionalContingencyTable.MinOfRowMaximumsValue(CT1);
                            rHyp.h_c1 = CT1.MarginalColumnEntropy;
                            rHyp.h_r1 = CT1.MarginalRowEntropy;
                            rHyp.h_c_r1 = TwoDimensionalContingencyTable.ConditionalCREntropyValue(CT1);
                            rHyp.mi1 = CT1.MutualInformation;
                            //rHyp.aic = CT.???;  TODO
                            rHyp.kend1 = TwoDimensionalContingencyTable.KendalValue(CT1);
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
                            rHyp.chi_sq2 = TwoDimensionalContingencyTable.ChiSquare(CT2);
                            rHyp.fnc_s2 = TwoDimensionalContingencyTable.SumOfRowMaximumsValue(CT2);
                            rHyp.fnc_r2 = TwoDimensionalContingencyTable.MinOfRowMaximumsValue(CT2);
                            rHyp.h_c2 = CT2.MarginalColumnEntropy;
                            rHyp.h_r2 = CT2.MarginalRowEntropy;
                            rHyp.h_c_r2 = TwoDimensionalContingencyTable.ConditionalCREntropyValue(CT2);
                            rHyp.mi2 = CT2.MutualInformation;
                            //rHyp.aic = CT.???;  TODO
                            rHyp.kend2 = TwoDimensionalContingencyTable.KendalValue(CT2);
                        }
                        catch (System.Exception e) // TODO: Ferda ma chyby ve vypoctech -> opravit! 
                        {
                            ErrStr += "Box ProjectIdentifier=" + box.ProjectIdentifier.ToString() + ": chyba pri vypoctu kvantifikatoru: " + e.Message + "\n";
                        }
                        // hodnoty kvantifikatoru - rozdil set1 a set2
                        try
                        {
                            rHyp.da_sum = TwoDimensionalContingencyTable.Value<TwoDimensionalContingencyTable>(sum_delegat, CT1, CT2, OperationModeEnum.DifferencesOfAbsoluteFrequencies);
                            rHyp.da_min = TwoDimensionalContingencyTable.Value<TwoDimensionalContingencyTable>(min_delegat, CT1, CT2, OperationModeEnum.DifferencesOfAbsoluteFrequencies);
                            rHyp.da_max = TwoDimensionalContingencyTable.Value<TwoDimensionalContingencyTable>(max_delegat, CT1, CT2, OperationModeEnum.DifferencesOfAbsoluteFrequencies);
                            rHyp.dr_sum = TwoDimensionalContingencyTable.Value<TwoDimensionalContingencyTable>(sum_delegat, CT1, CT2, OperationModeEnum.DifferencesOfRelativeFrequencies);
                            rHyp.dr_min = TwoDimensionalContingencyTable.Value<TwoDimensionalContingencyTable>(min_delegat, CT1, CT2, OperationModeEnum.DifferencesOfRelativeFrequencies);
                            rHyp.dr_max = TwoDimensionalContingencyTable.Value<TwoDimensionalContingencyTable>(max_delegat, CT1, CT2, OperationModeEnum.DifferencesOfRelativeFrequencies);
                        }
                        catch (System.Exception e) // TODO: Ferda ma chyby ve vypoctech -> opravit! 
                        {
                            ErrStr += "Box ProjectIdentifier=" + box.ProjectIdentifier.ToString() + ": chyba pri vypoctu kvantifikatoru: " + e.Message + "\n";
                        }





                        #endregion

                        #region element ti_cedent Row attributes (Antecedent)

                        rAnt.id = rHyp.row_attributes;
                        rAnt.type = "Row attributes";
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

                        #region element ti_cedent Column attributes (Succedent)

                        rSuc.id = rHyp.column_attributes;
                        rSuc.type = "Column attributes";
                        // literaly
                        List<Rec_ti_literal> Lit_s = new List<Rec_ti_literal>();
                        foreach (LiteralStruct lit in HypList[i].literals)
                        {
                            if (lit.cedentType == CedentEnum.Succedent)
                            {
                                Rec_ti_literal l = new Rec_ti_literal();
                                l.id = "tiLit" + rHyp.id + "_" + litCounter.ToString();
                                litCounter++;
                                l.quant += lit.literalName;
                                foreach (string s in lit.categoriesNames)
                                    l.value += s;
                                // ??? k cemu je polozka LitralStruct.categoriesValues ?
                                Lit_s.Add(l);
                            }
                        }

                        #endregion

                        #region element ti_cedent (Condition)

                        rCon.id = rHyp.condition;
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
                        // vypsani Row attributes (Antecedentu) do XML
                        oneHypString += rAnt.ToXML(Lit_a);
                        // vypsani Column attributes (Succedentu) do XML
                        oneHypString += rSuc.ToXML(Lit_s);
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
                MessageBox.Show("Pri nacitani SD-KL hypotez doslo k chybam:\n" + ErrStr, "Chyba", MessageBoxButtons.OK, MessageBoxIcon.Error);

            // korenovy element
            resultString += "</active_list>";

            // LADICI - Kody - ulozeni vystupu do souboru "XMLsd4fthypExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLsdKLhypExample.xml");

            return resultString;
        }
    }

    #region --- Recordy  ---

    public class Rec_hyp_SDKL
    {
        #region DATA
        public string id = "";    // ID 4ft-hypotezy
        public string db_name = "";   // jmeno databaze
        public string matrix_name = ""; // jmeno datove matice
        public string task_name = "";   // jmeno ulohy

        public int[][] Tab1; // 1. kontingencni tabulka
        public int[][] Tab2; // 2. kontingencni tabulka

        // kvantifikatory - set1
        public double sum1 = 0;
        public double min1 = 0;
        public double max1 = 0;
        public double chi_sq1 = 0;
        public double fnc_s1 = 0;
        public double fnc_r1 = 0;
        public double h_c1 = 0;
        public double h_r1 = 0;
        public double h_c_r1 = 0;
        public double mi1 = 0;
        public double aic1 = 0;
        public double kend1 = 0;

        // kvantifikatory - set2
        public double sum2 = 0;
        public double min2 = 0;
        public double max2 = 0;
        public double chi_sq2 = 0;
        public double fnc_s2 = 0;
        public double fnc_r2 = 0;
        public double h_c2 = 0;
        public double h_r2 = 0;
        public double h_c_r2 = 0;
        public double mi2 = 0;
        public double aic2 = 0;
        public double kend2 = 0;

        // kvantifikatory - rozdil set1 a set2
        public double da_sum = 0;
        public double da_min = 0;
        public double da_max = 0;
        public double dr_sum = 0;
        public double dr_min = 0;
        public double dr_max = 0;

        public string row_attributes = "";  // reference (Antecedent)
        public string column_attributes = "";  // reference (Succedent)
        public string condition = "";   // reference
        public string set1 = "";   // reference
        public string set2 = "";   // reference

        #endregion

        #region METHODS
        // prevod recordu na XML string
        public string ToXML()
        {
            string XML = "";

            XML += "<hyp_sdkl id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" task_name=\"" + task_name +
                // hodnoty kvantifikatoru - set1
                   "\" sum1=\"" + sum1.ToString() + "\" min1=\"" + min1.ToString() + "\" max1=\"" + max1.ToString() +
                   "\" chi_sq1=\"" + chi_sq1.ToString() + "\" fnc_s1=\"" + fnc_s1.ToString() +
                   "\" fnc_r1=\"" + fnc_r1.ToString() + "\" h_c1=\"" + h_c1.ToString() +
                   "\" h_r1=\"" + h_r1.ToString() + "\" h_c_r1=\"" + h_c_r1.ToString() +
                   "\" mi1=\"" + mi1.ToString() + "\" aic1=\"" + aic1.ToString() +
                   "\" kend1=\"" + kend1.ToString() +
                // hodnoty kvantifikatoru - set2
                   "\" sum2=\"" + sum2.ToString() + "\" min2=\"" + min2.ToString() + "\" max2=\"" + max2.ToString() +
                   "\" chi_sq2=\"" + chi_sq2.ToString() + "\" fnc_s2=\"" + fnc_s2.ToString() +
                   "\" fnc_r2=\"" + fnc_r2.ToString() + "\" h_c2=\"" + h_c2.ToString() +
                   "\" h_r2=\"" + h_r2.ToString() + "\" h_c_r2=\"" + h_c_r2.ToString() +
                   "\" mi2=\"" + mi2.ToString() + "\" aic2=\"" + aic2.ToString() +
                   "\" kend2=\"" + kend2.ToString() +
                // hodnoty kvantifikatoru - rozdil set1 a set2
                   "\" da_sum=\"" + da_sum.ToString() + "\" da_min=\"" + da_min.ToString() +
                    "\" da_max=\"" + da_max.ToString() + "\" dr_sum=\"" + dr_sum.ToString() +
                    "\" dr_min=\"" + dr_min.ToString() + "\" dr_max=\"" + dr_max.ToString() +
                // cedenty
                   "\" row_attributes=\"" + row_attributes + "\" column_attributes=\"" + column_attributes +
                   "\" condition=\"" + condition +
                   "\" set1=\"" + set1 +
                   "\" set2=\"" + set2 + "\">";

            // vygenerovani podelementu - ciselnych hodnot kontingencni tabulky
                // 1. tabulka
            XML += "<tab>";
            int radku = Tab1[0].GetLength(0);
            int sloupcu = Tab1.GetLength(0);

            for (int i = 0; i < radku; i++)
            {
                XML += "<r>";
                for (int j = 0; j < sloupcu; j++)
                    XML += "<c val=\"" + Tab1[j][i].ToString() + "\"/>";
                XML += "</r>";
            }
            XML += "</tab>";

                // 2. tabulka
            XML += "<tab>";
            radku = Tab2[0].GetLength(0);
            sloupcu = Tab2.GetLength(0);

            for (int i = 0; i < radku; i++)
            {
                XML += "<r>";
                for (int j = 0; j < sloupcu; j++)
                    XML += "<c val=\"" + Tab2[j][i].ToString() + "\"/>";
                XML += "</r>";
            }
            XML += "</tab>";


            XML += "</hyp_sdkl>";
            return XML;

        }
        #endregion
    }

    // Rec_ti_cedent & Rec_ti_literal implementovany u AP 4ft-hypoteza

    #endregion
}
