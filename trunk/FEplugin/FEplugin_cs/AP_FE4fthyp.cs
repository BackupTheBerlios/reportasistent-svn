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

    // ==================== Aktivni prvek 4ft-hypoteza ================================

    public class AP_FE4fthyp
    {
        /// <summary>
        /// Implementation of Active element "4ft hypothese"
        /// </summary>
        /// <param name="index">index of data source in data sources tab </param>
        /// <returns>Returns XML string with all occurences of Active element type "4ft hypothese" from data source with given index</returns>
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
            // nalezeni vsech krabicek 4FT-uloh
            IBoxModule[] FFTTaskBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, "LISpMinerTasks.FFTTask");

            // zpracovani kazde krabicky - ziskani z ni vsechny 4ft-hypotezy
            string ErrStr = ""; // zaznam o chybach

            string matrix_name = "";   // jmeno analyzovane matice
            string db_name = "";    // jmeno analyzovane databaze
            string task_name = "";  // jmeno ulohy - dano uzivatelskym nazvem krabicky FFTTast

            #region Cyklus - zpracovani vsech 4ft-Tasku z pole FFTTaskBoxes

            foreach (IBoxModule box in FFTTaskBoxes)
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
                    Rec_hyp_4ft rHyp = new Rec_hyp_4ft();      // hypoteza
                    Rec_ti_cedent rAnt = new Rec_ti_cedent();  // antecedent
                    Rec_ti_cedent rSuc = new Rec_ti_cedent();  // succedent
                    Rec_ti_cedent rCon = new Rec_ti_cedent();  // condition

                    #region Cyklus - zpracovani vsech hypotez jedne krabicky FFTTask
                    // cyklus pres vsechny hypotezy
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
                        rHyp.a = FFT.A;
                        rHyp.b = FFT.B;
                        rHyp.c = FFT.C;
                        rHyp.d = FFT.D;
                        // hodnoty kvantifikatoru
                        rHyp.conf = FourFoldContingencyTable.FoundedImplicationValue(FFT);  // Founded implication (a/a+b)
                        rHyp.d_conf = FourFoldContingencyTable.DoubleFoundedImplicationValue(FFT); // Double Founded implication (a/a+b+c)
                        rHyp.e_conf = FourFoldContingencyTable.FoundedEquivalenceValue(FFT);   // Founded Equivalence (a+d)/(a+b+c+d)  ??? BUG ve Ferdovi
                        rHyp.support = FourFoldContingencyTable.BaseCeilValue(FFT); //???  Support (a/a+b+c+d)
                        rHyp.avg_diff = FourFoldContingencyTable.AboveAverageImplicationValue(FFT) - 1; // Averafe difference ((a*(a+b+c+d))/((a+b)*(a+c)) -1)
                        // tyto hodnoty se vypocitavaji (mozna zbytecne?)
                        rHyp.fisher = FFT.FisherValue();
                        rHyp.chi_sq = FFT.ChiSquareValue();

                        #endregion
                        // TODO - dodelat vypocty, ostatni ciselne polozky (hodnoty nekterych kvantifikatoru atd.)

                        #region element ti_cedent (Antecedent)

                        rAnt.id = "ant" + rHyp.id;
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

                        rSuc.id = "suc" + rHyp.id;
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
#if (LADENI)
            // vypsani pripadne chybove hlasky:
            if (!String.IsNullOrEmpty(ErrStr))
                MessageBox.Show("Pri nacitani hypotez doslo k chybam:\n" + ErrStr, "Chyba", MessageBoxButtons.OK, MessageBoxIcon.Error);
#endif

            // korenovy element
            resultString += "</active_list>";
#if (LADENI)
            // Kody - ulozeni vystupu do souboru "XML4fthypExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XML4fthypExample.xml");
#endif
            return resultString;
        }
    }

    #region --- Recordy  ---

    public class Rec_hyp_4ft
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
        public double conf = 0;
        public double d_conf = 0;
        public double e_conf = 0;
        public double support = 0;
        public double completness = 0;
        public double avg_diff = 0;
        public double low_bnd_imp = 0;
        public double up_bnd_imp = 0;
        public double low_bnd_dbl_imp = 0;
        public double up_bnd_dbl_imp = 0;
        public double low_bnd_eq = 0;
        public double up_bnd_eq = 0;
        public double fisher = 0;
        public double chi_sq = 0;
        public string antecedent = "";  // reference
        public string succedent = "";   // reference
        public string condition = "";   // reference
        #endregion

        #region METHODS
        // prevod recordu na XML string
        public string ToXML()
        {
            string XML = "";

            XML += "<hyp_4ft id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" task_name=\"" + task_name + "\" a=\"" + a.ToString() + "\" b=\"" + b.ToString() +
                   "\" c=\"" + c.ToString() + "\" d=\"" + d.ToString() + "\" conf=\"" + conf.ToString() +
                   "\" d_conf=\"" + d_conf.ToString() + "\" e_conf=\"" + e_conf.ToString() +
                   "\" support=\"" + support.ToString() + "\" completeness=\"" + completness.ToString() +
                   "\" avg_diff=\"" + avg_diff.ToString() + "\" low_bnd_imp=\"" + low_bnd_imp.ToString() +
                   "\" up_bnd_imp=\"" + up_bnd_imp.ToString() + "\" low_bnd_dbl_imp=\"" + low_bnd_dbl_imp.ToString() +
                   "\" up_bnd_dbl_imp=\"" + up_bnd_dbl_imp.ToString() + "\" low_bnd_eq=\"" + low_bnd_eq.ToString() +
                   "\" up_bnd_eq=\"" + up_bnd_eq.ToString() + "\" fisher=\"" + fisher.ToString() +
                   "\" chi_sq=\"" + chi_sq.ToString() + "\" antecedent=\"" + antecedent +
                   "\" succedent=\"" + succedent + "\" condition=\"" + condition + "\"/>";
            return XML;

        }
        #endregion
    }

    // Rec_ti_cedent a Rec_ti_literal implementovane v souboru "AP_hypotheses_common.cs"

    #endregion
}
