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

    // ==================== Aktivni prvek SD-4ft-hypoteza ================================

    public class AP_FEsd4fthyp
    {
        /// <summary>
        /// Implementation of Active element "sd-4ft hypothese"
        /// </summary>
        /// <param name="index">index of data source in data sources tab </param>
        /// <returns>Returns XML string with all occurences of Active element type "sd-4ft hypothese" from data source with given index</returns>
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
            // nalezeni vsech krabicek SD-4FT-uloh
            IBoxModule[] TaskBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, "LISpMinerTasks.SDFFTTask");

            // zpracovani kazde krabicky - ziskani z ni vsechny 4ft-hypotezy
            string ErrStr = ""; // zaznam o chybach

            string matrix_name = "";   // jmeno analyzovane matice
            string db_name = "";    // jmeno analyzovane databaze
            string task_name = "";  // jmeno ulohy - dano uzivatelskym nazvem krabicky FFTTast

            // vytvoreni delegatu funkci kvantifikatoru - "sum of value"
            ContingencyTable.QuantifierValue<FourFoldContingencyTable> sum_delegat = new ContingencyTable.QuantifierValue<FourFoldContingencyTable>(FourFoldContingencyTable.GetSumOfValues);
          


            #region Cyklus - zpracovani vsech SD-4ft-Tasku z pole TaskBoxes

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
                    Rec_hyp_sd4ft rHyp = new Rec_hyp_sd4ft();      // hypoteza
                    Rec_ti_cedent rAnt = new Rec_ti_cedent();  // antecedent
                    Rec_ti_cedent rSuc = new Rec_ti_cedent();  // succedent
                    Rec_ti_cedent rCon = new Rec_ti_cedent();  // condition
                    Rec_ti_cedent rSet1 = new Rec_ti_cedent();  // set 1
                    Rec_ti_cedent rSet2 = new Rec_ti_cedent();  // set 2

                    #region Cyklus - zpracovani vsech hypotez jedne krabicky SDFFTTask
                    // cyklus pres vsechny hypotezy
                    for (int i = 0; i < HypList.GetLength(0); i++)
                    {
                        #region element hyp_sd4ft

                        rHyp.id = "hypsd4ft" + box.ProjectIdentifier.ToString() + "_" + i.ToString();
                        rHyp.db_name = db_name;
                        rHyp.matrix_name = matrix_name;
                        rHyp.task_name = task_name;
                        rHyp.antecedent = "ant" + rHyp.id;
                        rHyp.succedent = "suc" + rHyp.id;
                        rHyp.condition = "con" + rHyp.id;
                        rHyp.set1 = "set1" + rHyp.id;
                        rHyp.set2 = "set2" + rHyp.id;
                        FourFoldContingencyTable FFT1 = new FourFoldContingencyTable(HypList[i].quantifierSetting.firstContingencyTableRows);
                        FourFoldContingencyTable FFT2 = new FourFoldContingencyTable(HypList[i].quantifierSetting.secondContingencyTableRows);
                        rHyp.a = FFT1.A;
                        rHyp.b = FFT1.B;
                        rHyp.c = FFT1.C;
                        rHyp.d = FFT1.D;
                        rHyp.e = FFT2.A;
                        rHyp.f = FFT2.B;
                        rHyp.g = FFT2.C;
                        rHyp.h = FFT2.D;

                        // hodnoty kvantifikatoru - prvni mnozina
                        rHyp.conf1 = FourFoldContingencyTable.FoundedImplicationValue(FFT1);  // Founded implication (a/a+b)
                        rHyp.d_conf1 = FourFoldContingencyTable.DoubleFoundedImplicationValue(FFT1); // Double Founded implication (a/a+b+c)
                        rHyp.e_conf1 = FourFoldContingencyTable.FoundedEquivalenceValue(FFT1);   // Founded Equivalence (a+d)/(a+b+c+d)  ??? BUG ve Ferdovi
                        rHyp.support1 = FourFoldContingencyTable.BaseCeilValue(FFT1); //???  Support (a/a+b+c+d)
                        rHyp.avg_diff1 = FourFoldContingencyTable.AboveAverageImplicationValue(FFT1) - 1; // Averafe difference ((a*(a+b+c+d))/((a+b)*(a+c)) -1)
                        rHyp.fisher1 = FFT1.FisherValue();
                        rHyp.chi_sq1 = FFT1.ChiSquareValue();

                        // hodnoty kvantifikatoru - druha mnozina
                        rHyp.conf2 = FourFoldContingencyTable.FoundedImplicationValue(FFT2);  // Founded implication (a/a+b)
                        rHyp.d_conf2 = FourFoldContingencyTable.DoubleFoundedImplicationValue(FFT2); // Double Founded implication (a/a+b+c)
                        rHyp.e_conf2 = FourFoldContingencyTable.FoundedEquivalenceValue(FFT2);   // Founded Equivalence (a+d)/(a+b+c+d)  ??? BUG ve Ferdovi
                        rHyp.support2 = FourFoldContingencyTable.BaseCeilValue(FFT2); //???  Support (a/a+b+c+d)
                        rHyp.avg_diff2 = FourFoldContingencyTable.AboveAverageImplicationValue(FFT2) - 1; // Averafe difference ((a*(a+b+c+d))/((a+b)*(a+c)) -1)
                        rHyp.fisher2 = FFT2.FisherValue();
                        rHyp.chi_sq2 = FFT2.ChiSquareValue();

                        // hodnoty kvantifikatoru - rozdil mezi prvni a druhou mnozinou
                        rHyp.dr_sum = FourFoldContingencyTable.Value<FourFoldContingencyTable>(sum_delegat, FFT1, FFT2, OperationModeEnum.DifferencesOfRelativeFrequencies);
                        rHyp.df_conf = FourFoldContingencyTable.Combine(rHyp.conf1, rHyp.conf2, OperationModeEnum.DifferenceOfQuantifierValues);
                        rHyp.df_dfui  = FourFoldContingencyTable.Combine(rHyp.d_conf1, rHyp.d_conf2, OperationModeEnum.DifferenceOfQuantifierValues);
                        rHyp.df_fue = FourFoldContingencyTable.Combine(rHyp.e_conf1, rHyp.e_conf2, OperationModeEnum.DifferenceOfQuantifierValues);
                        rHyp.df_avg = FourFoldContingencyTable.Combine(rHyp.avg_diff1, rHyp.avg_diff2, OperationModeEnum.DifferenceOfQuantifierValues);

                        #endregion
                        // TODO - dodelat vypocty, ostatni ciselne polozky (hodnoty nekterych kvantifikatoru atd.)

                        #region element ti_cedent (Antecedent)

                        rAnt.id = rHyp.antecedent;
                        rAnt.type = "Antecedent";
                        // literaly
                        int litCounter = 0;  // pocitadlo literalu teto hypotezy
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
                                foreach (string s in lit.categoriesNames)
                                    l.value += s;
                                Lit_a.Add(l);
                            }
                        }

                        #endregion

                        #region element ti_cedent (Succedent)

                        rSuc.id = rHyp.succedent;
                        rSuc.type = "Succedent";
                        // literaly
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
                                foreach (string s in lit.categoriesNames)
                                    l.value += s;
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

                        #region element ti_cedent (First Set)

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

                        #region element ti_cedent (Second Set)

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
                        // vypsani Antecedentu do XML
                        oneHypString += rAnt.ToXML(Lit_a);
                        // vypsani Succedentu do XML
                        oneHypString += rSuc.ToXML(Lit_s);
                        // vypsani Condition do XML
                        oneHypString += rCon.ToXML(Lit_c);
                        // vypsani First Set do XML
                        oneHypString += rSet1.ToXML(Lit_s1);
                        // vypsani Second Set do XML
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
                MessageBox.Show("Pri nacitani SD4FT hypotez doslo k chybam:\n" + ErrStr, "Chyba", MessageBoxButtons.OK, MessageBoxIcon.Error);

            // korenovy element
            resultString += "</active_list>";

            // LADICI - Kody - ulozeni vystupu do souboru "XMLsd4fthypExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLsd4fthypExample.xml");

            return resultString;
        }
    }

    #region --- Recordy  ---

    public class Rec_hyp_sd4ft
    {
        #region DATA
        public string id = "";    // ID 4ft-hypotezy
        public string db_name = "";   // jmeno databaze
        public string matrix_name = ""; // jmeno datove matice
        public string task_name = "";   // jmeno ulohy
        public double a = 0;
        public double b = 0;
        public double c = 0;
        public double d = 0;
        public double e = 0;
        public double f = 0;
        public double g = 0;
        public double h = 0;

        public double conf1 = 0;
        public double d_conf1 = 0;
        public double e_conf1 = 0;
        public double support1 = 0;
        public double completness1 = 0;
        public double avg_diff1 = 0;
        public double low_bnd_imp1 = 0;
        public double up_bnd_imp1 = 0;
        public double low_bnd_dbl_imp1 = 0;
        public double up_bnd_dbl_imp1 = 0;
        public double low_bnd_eq1 = 0;
        public double up_bnd_eq1 = 0;
        public double fisher1 = 0;
        public double chi_sq1 = 0;

        public double conf2 = 0;
        public double d_conf2 = 0;
        public double e_conf2 = 0;
        public double support2 = 0;
        public double completness2 = 0;
        public double avg_diff2 = 0;
        public double low_bnd_imp2 = 0;
        public double up_bnd_imp2 = 0;
        public double low_bnd_dbl_imp2 = 0;
        public double up_bnd_dbl_imp2 = 0;
        public double low_bnd_eq2 = 0;
        public double up_bnd_eq2 = 0;
        public double fisher2 = 0;
        public double chi_sq2 = 0;
        
        public double dr_sum = 0;
        public double df_conf = 0;
        public double df_dfui = 0;
        public double df_fue = 0;
        public double df_avg = 0;
        

        public string antecedent = "";  // reference
        public string succedent = "";   // reference
        public string condition = "";   // reference
        public string set1 = "";   // reference
        public string set2 = "";   // reference
        #endregion

        #region METHODS
        // prevod recordu na XML string
        public string ToXML()
        {
            string XML = "";

            XML += "<hyp_sd4ft id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" task_name=\"" + task_name + "\" a=\"" + a.ToString() + "\" b=\"" + b.ToString() +
                   "\" c=\"" + c.ToString() + "\" d=\"" + d.ToString() +  "\" e=\"" + e.ToString() + "\" f=\"" + f.ToString() +
                   "\" g=\"" + g.ToString() + "\" h=\"" + h.ToString() + 
                   // hodnoty kvantifikatoru prvni mnoziny
                   "\" conf1=\"" + conf1.ToString() + "\" d_conf1=\"" + d_conf1.ToString() + "\" e_conf1=\"" + e_conf1.ToString() +
                   "\" support1=\"" + support1.ToString() + "\" completeness1=\"" + completness1.ToString() +
                   "\" avg_diff1=\"" + avg_diff1.ToString() + "\" low_bnd_imp1=\"" + low_bnd_imp1.ToString() +
                   "\" up_bnd_imp1=\"" + up_bnd_imp1.ToString() + "\" low_bnd_dbl_imp1=\"" + low_bnd_dbl_imp1.ToString() +
                   "\" up_bnd_dbl_imp1=\"" + up_bnd_dbl_imp1.ToString() + "\" low_bnd_eq1=\"" + low_bnd_eq1.ToString() +
                   "\" up_bnd_eq1=\"" + up_bnd_eq1.ToString() + "\" fisher1=\"" + fisher1.ToString() +
                   "\" chi_sq1=\"" + chi_sq1.ToString() +
                   // hodnoty kvantifikatoru druhe mnoziny
                   "\" conf2=\"" + conf2.ToString() + "\" d_conf2=\"" + d_conf2.ToString() + "\" e_conf2=\"" + e_conf2.ToString() +
                   "\" support2=\"" + support2.ToString() + "\" completeness2=\"" + completness2.ToString() +
                   "\" avg_diff2=\"" + avg_diff2.ToString() + "\" low_bnd_imp2=\"" + low_bnd_imp2.ToString() +
                   "\" up_bnd_imp2=\"" + up_bnd_imp2.ToString() + "\" low_bnd_dbl_imp2=\"" + low_bnd_dbl_imp2.ToString() +
                   "\" up_bnd_dbl_imp2=\"" + up_bnd_dbl_imp2.ToString() + "\" low_bnd_eq2=\"" + low_bnd_eq2.ToString() +
                   "\" up_bnd_eq2=\"" + up_bnd_eq2.ToString() + "\" fisher2=\"" + fisher2.ToString() +
                   "\" chi_sq2=\"" +  chi_sq2.ToString() + 
                   // hodnoty kvantifikatoru "kombinace mnozin"
                   "\" dr_sum=\"" + dr_sum.ToString() + "\" df_conf=\"" + df_conf.ToString() + "\" df_dfui=\"" + df_dfui.ToString() +
                   "\" df_fue=\"" + df_fue.ToString() + "\" df_avg=\"" + df_avg.ToString() +
                   // cedenty
                   "\" antecedent=\"" + antecedent +
                   "\" succedent=\"" + succedent +
                   "\" condition=\"" + condition +
                   "\" set1=\"" + set1 +
                   "\" set2=\"" + set2 + "\"/>";
            return XML;

        }
        #endregion
    }

    // Rec_ti_cedent & Rec_ti_literal implementovany u AP 4ft-hypoteza

    #endregion
}
