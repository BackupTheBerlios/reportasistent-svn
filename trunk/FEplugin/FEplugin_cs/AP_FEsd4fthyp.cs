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
#if (LADENI)
                MessageBox.Show("Chyba pri nacitani DTD: " + e.Message);
#endif
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
                        rHyp.a = FFT1.A.ToString();
                        rHyp.b = FFT1.B.ToString();
                        rHyp.c = FFT1.C.ToString();
                        rHyp.d = FFT1.D.ToString();
                        rHyp.e = FFT2.A.ToString();
                        rHyp.f = FFT2.B.ToString();
                        rHyp.g = FFT2.C.ToString();
                        rHyp.h = FFT2.D.ToString();

                        // hodnoty kvantifikatoru - prvni mnozina
                        double conf1 = FourFoldContingencyTable.FoundedImplicationValue(FFT1);  // Founded implication (a/a+b)
                        rHyp.conf1 = conf1.ToString();
                        double d_conf1 = FourFoldContingencyTable.DoubleFoundedImplicationValue(FFT1); // Double Founded implication (a/a+b+c)
                        rHyp.d_conf1 = d_conf1.ToString();
                        double e_conf1 = FourFoldContingencyTable.FoundedEquivalenceValue(FFT1);   // Founded Equivalence (a+d)/(a+b+c+d)  ??? BUG ve Ferdovi
                        rHyp.e_conf1 = e_conf1.ToString();
                        rHyp.support1 = FourFoldContingencyTable.BaseCeilValue(FFT1).ToString(); //???  Support (a/a+b+c+d)
                           // pom. promenna
                        double avg_diff1 = FourFoldContingencyTable.AboveAverageImplicationValue(FFT1) - 1; // Averafe difference ((a*(a+b+c+d))/((a+b)*(a+c)) -1)
                        rHyp.avg_diff1 = avg_diff1.ToString();
                        rHyp.fisher1 = FFT1.FisherValue().ToString();
                        rHyp.chi_sq1 = FFT1.ChiSquareValue().ToString();

                        // hodnoty kvantifikatoru - druha mnozina
                        double conf2 = FourFoldContingencyTable.FoundedImplicationValue(FFT2);  // Founded implication (a/a+b)
                        rHyp.conf2 = conf2.ToString();
                        double d_conf2 = FourFoldContingencyTable.DoubleFoundedImplicationValue(FFT2); // Double Founded implication (a/a+b+c)
                        rHyp.d_conf2 = d_conf2.ToString();
                        double e_conf2 = FourFoldContingencyTable.FoundedEquivalenceValue(FFT2);   // Founded Equivalence (a+d)/(a+b+c+d)  ??? BUG ve Ferdovi
                        rHyp.e_conf2 = e_conf2.ToString();
                        rHyp.support2 = FourFoldContingencyTable.BaseCeilValue(FFT2).ToString(); //???  Support (a/a+b+c+d)
                           // pom. promenna
                        double avg_diff2 = FourFoldContingencyTable.AboveAverageImplicationValue(FFT2) - 1; // Averafe difference ((a*(a+b+c+d))/((a+b)*(a+c)) -1)
                        rHyp.avg_diff2 = avg_diff2.ToString();
                        rHyp.fisher2 = FFT2.FisherValue().ToString();
                        rHyp.chi_sq2 = FFT2.ChiSquareValue().ToString();

                        // hodnoty kvantifikatoru - rozdil mezi prvni a druhou mnozinou
                        rHyp.dr_sum = FourFoldContingencyTable.Value<FourFoldContingencyTable>(sum_delegat, FFT1, FFT2, OperationModeEnum.DifferencesOfRelativeFrequencies).ToString();
                        double df_conf = FourFoldContingencyTable.Combine(conf1, conf2, OperationModeEnum.DifferenceOfQuantifierValues);
                        rHyp.df_conf = df_conf.ToString();
                        double df_dfui  = FourFoldContingencyTable.Combine(d_conf1, d_conf2, OperationModeEnum.DifferenceOfQuantifierValues);
                        rHyp.df_dfui = df_dfui.ToString();
                        double df_fue = FourFoldContingencyTable.Combine(e_conf1, e_conf2, OperationModeEnum.DifferenceOfQuantifierValues);
                        rHyp.df_fue = df_fue.ToString();
                        double df_avg = FourFoldContingencyTable.Combine(avg_diff1, avg_diff2, OperationModeEnum.DifferenceOfQuantifierValues);
                        rHyp.df_avg = df_avg.ToString();

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

            // korenovy element
            resultString += "</active_list>";

#if (LADENI)            
            // vypsani pripadne chybove hlasky:
            if (!String.IsNullOrEmpty(ErrStr))  // LADICI
                MessageBox.Show("Pri nacitani SD4FT hypotez doslo k chybam:\n" + ErrStr, "Chyba", MessageBoxButtons.OK, MessageBoxIcon.Error);

            // LADICI - Kody - ulozeni vystupu do souboru "XMLsd4fthypExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLsd4fthypExample.xml");
#endif

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
        public string a = "unknown";
        public string b = "unknown";
        public string c = "unknown";
        public string d = "unknown";
        public string e = "unknown";
        public string f = "unknown";
        public string g = "unknown";
        public string h = "unknown";

        public string conf1 = "unknown";
        public string d_conf1 = "unknown";
        public string e_conf1 = "unknown";
        public string support1 = "unknown";
        public string completness1 = "unknown";
        public string avg_diff1 = "unknown";
        public string low_bnd_imp1 = "unknown";
        public string up_bnd_imp1 = "unknown";
        public string low_bnd_dbl_imp1 = "unknown";
        public string up_bnd_dbl_imp1 = "unknown";
        public string low_bnd_eq1 = "unknown";
        public string up_bnd_eq1 = "unknown";
        public string fisher1 = "unknown";
        public string chi_sq1 = "unknown";

        public string conf2 = "unknown";
        public string d_conf2 = "unknown";
        public string e_conf2 = "unknown";
        public string support2 = "unknown";
        public string completness2 = "unknown";
        public string avg_diff2 = "unknown";
        public string low_bnd_imp2 = "unknown";
        public string up_bnd_imp2 = "unknown";
        public string low_bnd_dbl_imp2 = "unknown";
        public string up_bnd_dbl_imp2 = "unknown";
        public string low_bnd_eq2 = "unknown";
        public string up_bnd_eq2 = "unknown";
        public string fisher2 = "unknown";
        public string chi_sq2 = "unknown";
        
        public string dr_sum = "unknown";
        public string df_conf = "unknown";
        public string df_dfui = "unknown";
        public string df_fue = "unknown";
        public string df_avg = "unknown";
        

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
                   "\" task_name=\"" + task_name + "\" a=\"" + a + "\" b=\"" + b +
                   "\" c=\"" + c + "\" d=\"" + d +  "\" e=\"" + e + "\" f=\"" + f +
                   "\" g=\"" + g + "\" h=\"" + h + 
                   // hodnoty kvantifikatoru prvni mnoziny
                   "\" conf1=\"" + conf1 + "\" d_conf1=\"" + d_conf1 + "\" e_conf1=\"" + e_conf1 +
                   "\" support1=\"" + support1 + "\" completeness1=\"" + completness1 +
                   "\" avg_diff1=\"" + avg_diff1 + "\" low_bnd_imp1=\"" + low_bnd_imp1 +
                   "\" up_bnd_imp1=\"" + up_bnd_imp1 + "\" low_bnd_dbl_imp1=\"" + low_bnd_dbl_imp1 +
                   "\" up_bnd_dbl_imp1=\"" + up_bnd_dbl_imp1 + "\" low_bnd_eq1=\"" + low_bnd_eq1 +
                   "\" up_bnd_eq1=\"" + up_bnd_eq1 + "\" fisher1=\"" + fisher1 +
                   "\" chi_sq1=\"" + chi_sq1 +
                   // hodnoty kvantifikatoru druhe mnoziny
                   "\" conf2=\"" + conf2 + "\" d_conf2=\"" + d_conf2 + "\" e_conf2=\"" + e_conf2 +
                   "\" support2=\"" + support2 + "\" completeness2=\"" + completness2 +
                   "\" avg_diff2=\"" + avg_diff2 + "\" low_bnd_imp2=\"" + low_bnd_imp2 +
                   "\" up_bnd_imp2=\"" + up_bnd_imp2 + "\" low_bnd_dbl_imp2=\"" + low_bnd_dbl_imp2 +
                   "\" up_bnd_dbl_imp2=\"" + up_bnd_dbl_imp2 + "\" low_bnd_eq2=\"" + low_bnd_eq2 +
                   "\" up_bnd_eq2=\"" + up_bnd_eq2 + "\" fisher2=\"" + fisher2 +
                   "\" chi_sq2=\"" +  chi_sq2 + 
                   // hodnoty kvantifikatoru "kombinace mnozin"
                   "\" dr_sum=\"" + dr_sum + "\" df_conf=\"" + df_conf + "\" df_dfui=\"" + df_dfui +
                   "\" df_fue=\"" + df_fue + "\" df_avg=\"" + df_avg +
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
