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

    // ==================== Aktivni prvek KL-hypoteza ================================

    public class AP_FEklhyp
    {
        /// <summary>
        /// Implementation of Active element "KL hypothesis"
        /// </summary>
        /// <param name="index">index of data source in data sources tab </param>
        /// <returns>Returns XML string with all occurences of Active element type "KL hypothesis" from data source with given index</returns>
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
            // nalezeni vsech krabicek KL-uloh
            IBoxModule[] TaskBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, "LISpMinerTasks.KLTask");

            // zpracovani kazde krabicky - ziskani z ni vsechny KL-hypotezy
            string ErrStr = ""; // zaznam o chybach

            string matrix_name = "";   // jmeno analyzovane matice
            string db_name = "";    // jmeno analyzovane databaze
            string task_name = "";  // jmeno ulohy - dano uzivatelskym nazvem krabicky FFTTast


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
                    Rec_hyp_KL rHyp = new Rec_hyp_KL();   // KL hypoteza
                    Rec_ti_attribute rAnt = new Rec_ti_attribute();  // Antecedent (Row attributes)
                    Rec_ti_attribute rSuc = new Rec_ti_attribute();  // Succedent (Column attributes)
                    Rec_ti_cedent rCon = new Rec_ti_cedent();  // condition


                    #region Cyklus - zpracovani vsech hypotez jedne krabicky KLTask
                    // cyklus pres vsechny hypotezy
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


                        // hodnoty kvantifikatoru - prvni mnozina
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
                        catch (System.Exception e) // TODO: Ferda ma chyby ve vypoctech -> opravit! 
                        {
                            ErrStr += "Box ProjectIdentifier=" + box.ProjectIdentifier.ToString() + ": chyba pri vypoctu kvantifikatoru: " + e.Message + "\n";
                        }




                        #endregion

                        #region element ti_attribute Row attributes (Antecedent)

                        rAnt.id = rHyp.row_attributes;
                        rAnt.type = "Row attributes";
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

                        #region element ti_attribute Column attributes (Succedent)

                        rSuc.id = rHyp.column_attributes;
                        rSuc.type = "Column attributes";
                        rSuc.quant = "";   // smazani predchozi hodnoty
                        // kategorie
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
                        // literaly
                        int litCounter = 0;  // pocitadlo literalu teto hypotezy
                        List<Rec_ti_literal> Lit_c = new List<Rec_ti_literal>();
                        foreach (BooleanLiteralStruct lit in HypList[i].booleanLiterals)
                        {
                            if (lit.cedentType == CedentEnum.Condition)
                            {
                                Rec_ti_literal l = new Rec_ti_literal();
                                l.id = "tiLit" + rHyp.id + "_" + litCounter.ToString();
                                litCounter++;
                                if (lit.negation)
                                    l.quant = "�";
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


                        #region Vypsani jedne hypotezy do XML stringu

                        string oneHypString = "";
                        // vypsani hypotezy do XML
                        oneHypString += rHyp.ToXML();
                        // vypsani Row attributes (Antecedentu) do XML
                        oneHypString += rAnt.ToXML(Cat_a);
                        // vypsani Column attributes (Succedentu) do XML
                        oneHypString += rSuc.ToXML(Cat_s);
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

            
             // korenovy element
            resultString += "</active_list>";
            
#if (LADENI)            
            // vypsani pripadne chybove hlasky:
            if (!String.IsNullOrEmpty(ErrStr))  // LADICI
                MessageBox.Show("Pri nacitani KL hypotez doslo k chybam:\n" + ErrStr, "Chyba", MessageBoxButtons.OK, MessageBoxIcon.Error);

            // LADICI - Kody - ulozeni vystupu do souboru "XMLsd4fthypExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLKLhypExample.xml");
#endif

            return resultString;
        }
    }

    #region --- Recordy  ---

    public class Rec_hyp_KL
    {
        #region DATA
        public string id = "";    // ID 4ft-hypotezy
        public string db_name = "";   // jmeno databaze
        public string matrix_name = ""; // jmeno datove matice
        public string task_name = "";   // jmeno ulohy

        public int[][] Tab; // kontingencni tabulka

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
        // prevod recordu na XML string
        public string ToXML()
        {
            string XML = "";

            XML += "<hyp_kl id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" task_name=\"" + task_name +
                // hodnoty kvantifikatoru
                   "\" sum=\"" + sum + "\" min=\"" + min + "\" max=\"" + max +
                   "\" chi_sq=\"" + chi_sq + "\" fnc_s=\"" + fnc_s +
                   "\" fnc_r=\"" + fnc_r + "\" h_c=\"" + h_c +
                   "\" h_r=\"" + h_r + "\" h_c_r=\"" + h_c_r +
                   "\" mi=\"" + mi + "\" aic=\"" + aic +
                   "\" kend=\"" + kend +
                // cedenty
                   "\" row_attributes=\"" + row_attributes + "\" column_attributes=\"" + column_attributes +
                   "\" condition=\"" + condition + "\">";

            // vygenerovani podelementu - ciselnych hodnot kontingencni tabulky
            XML += "<tab>";
            /* Asi blba verze - prohozeny radky a sloupce
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

    // Rec_ti_cedent & Rec_ti_literal implementovany u AP 4ft-hypoteza

    #endregion
}
