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

    // ==================== Aktivni prvek CF-hypoteza ================================

    public class AP_FEcfhyp
    {
        /// <summary>
        /// Implementation of Active element "CF hypothesis"
        /// </summary>
        /// <param name="index">index of data source in data sources tab </param>
        /// <returns>Returns XML string with all occurences of Active element type "CF hypothesis" from data source with given index</returns>
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
            IBoxModule[] TaskBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, "LISpMinerTasks.CFTask");

            // zpracovani kazde krabicky - ziskani z ni vsechny CF-hypotezy
            string ErrStr = ""; // zaznam o chybach

            string matrix_name = "";   // jmeno analyzovane matice
            string db_name = "";    // jmeno analyzovane databaze
            string task_name = "";  // jmeno ulohy - dano uzivatelskym nazvem krabicky FFTTast

            
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
                    Rec_hyp_cf rHyp = new Rec_hyp_cf();   // CF hypoteza
                    Rec_ti_attribute rAnt = new Rec_ti_attribute();  // Antecedent (Attributes)
                    Rec_ti_cedent rCon = new Rec_ti_cedent();  // condition
             

                    #region Cyklus - zpracovani vsech hypotez jedne krabicky CFTask
                    // cyklus pres vsechny hypotezy
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
                        

                        // hodnoty kvantifikatoru - prvni mnozina
                        try
                        {
                            rHyp.sum = CT.SumOfValues;
                            rHyp.min = CT.MinValue;
                            rHyp.max = CT.MaxValue;
                            rHyp.v = CT.VariationRatio;
                            rHyp.nom_var = CT.NominalVariation;
                            rHyp.dor_var = CT.DiscreteOrdinaryVariation;
                            rHyp.avg_a = CT.ArithmeticAverage;
                            rHyp.avg_g = CT.GeometricAverage;
                            rHyp.var = CT.Variance;
                            rHyp.st_dev = CT.StandardDeviation;
                            rHyp.skew = CT.Skewness;
                            rHyp.asym = CT.Asymentry;
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
                        // vypsani Attributes (Antecedentu) do XML
                        oneHypString += rAnt.ToXML(Cat_a);
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
                MessageBox.Show("Pri nacitani CF hypotez doslo k chybam:\n" + ErrStr, "Chyba", MessageBoxButtons.OK, MessageBoxIcon.Error);

            // LADICI - Kody - ulozeni vystupu do souboru "XMLsd4fthypExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLcfhypExample.xml");
#endif

            return resultString;
        }
    }

    #region --- Recordy  ---

    public class Rec_hyp_cf
    {
        #region DATA
        public string id = "";    // ID 4ft-hypotezy
        public string db_name = "";   // jmeno databaze
        public string matrix_name = ""; // jmeno datove matice
        public string task_name = "";   // jmeno ulohy

        public int[] Tab; // kontingencni tabulka

        public double sum = 0;
        public double min = 0;
        public double max = 0;
        public double v = 0;
        public double nom_var = 0;
        public double dor_var = 0;
        public double avg_a = 0;
        public double avg_g = 0;
        public double var = 0;
        public double st_dev = 0;
        public double skew= 0;
        public double asym = 0;
        
        public string attributes = "";  // reference (Antecedent)
        public string condition = "";   // reference
    
        #endregion

        #region METHODS
        // prevod recordu na XML string
        public string ToXML()
        {
            string XML = "";

            XML += "<hyp_cf id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" task_name=\"" + task_name +
                // hodnoty kvantifikatoru
                   "\" sum=\"" + sum.ToString() + "\" min=\"" + min.ToString() + "\" max=\"" + max.ToString() +
                   "\" v=\"" + v.ToString() + "\" nom_var=\"" + nom_var.ToString() +
                   "\" dor_var=\"" + dor_var.ToString() + "\" avg_a=\"" + avg_a.ToString() +
                   "\" avg_g=\"" + avg_g.ToString() + "\" var=\"" + var.ToString() +
                   "\" st_dev=\"" + st_dev.ToString() + "\" skew=\"" + skew.ToString() +
                   "\" asym=\"" + asym.ToString() +
                // cedenty
                   "\" attributes=\"" + attributes +
                   "\" condition=\"" + condition + "\">";

            // vygenerovani podelementu - ciselnych hodnot kontingencni tabulky
            XML += "<r>";
            foreach (int num in Tab)
                XML += "<c val=\"" + num.ToString() + "\"/>";
            XML += "</r>";
            
            
            XML += "</hyp_cf>";
            return XML;

        }
        #endregion
    }

    // Rec_ti_cedent & Rec_ti_literal implementovany u AP 4ft-hypoteza

    #endregion
}
