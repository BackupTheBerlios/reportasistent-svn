using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;
using System.Windows.Forms;
using Ferda;
using Ferda.ProjectManager;
using Ferda.ModulesManager;
using Ferda.Modules;
using Ferda.FrontEnd;

namespace FEplugin_cs
{
    public class FEAPFunctions
    {
  
        // ==================== 4ft-hypoteza ================================

        public static string fFE4fthyp(int index)
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
            // nalezeni vsech krabicek 4FT-uloh
            IBoxModule[] FFTTaskBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, "LISpMinerTasks.FFTTask");

            // zpracovani kazde krabicky - ziskani z ni vsechny 4ft-hypotezy
            string ErrStr = ""; // zaznam o chybach
            
            string matrix_name = "";   // jmeno analyzovane matice
            string db_name = "";    // jmeno analyzovane databaze
            string task_name = "";  // jmeno ulohy - dano uzivatelskym nazvem krabicky FFTTast

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

                    // cyklus pres vsechny hypotezy
                    for (int i = 0; i < HypList.GetLength(0); i++)
                    {
                        // element hyp_4ft
                        rHyp.id = "hyp4ft" + box.ProjectIdentifier.ToString() + "_" + i.ToString();
                        rHyp.db_name = db_name;
                        rHyp.matrix_name = matrix_name;
                        rHyp.task_name = task_name;
                        rHyp.antecedent = "ant" + rHyp.id;
                        rHyp.succedent = "suc" + rHyp.id;
                        rHyp.condition = "con" + rHyp.id;
                        rHyp.a = HypList[i].quantifierSetting.firstContingencyTableRows[0][0];
                        rHyp.b = HypList[i].quantifierSetting.firstContingencyTableRows[0][1];
                        rHyp.c = HypList[i].quantifierSetting.firstContingencyTableRows[1][0];
                        rHyp.d = HypList[i].quantifierSetting.firstContingencyTableRows[1][1];
                        
                           // TODO - dodelat vypocty, ostatni ciselne polozky (hodnoty kvantifikatoru atd.)

                         


                        // element ti_cedent (Antecedent)
                        rAnt.id = "ant" + rHyp.id;
                        rAnt.type = "Antecedent";
                           // literaly
                        int litCounter = 0;  // pocitadlo literalu teto hypotezy
                        ArrayList ARLit_a = new ArrayList();
                        foreach (BooleanLiteralStruct lit in HypList[i].booleanLiterals)
                        {
                            if (lit.cedentType.ToString() == "Antecedent")
                            {
                                Rec_ti_literal l = new Rec_ti_literal();
                                l.id = "tiLit" + rHyp.id + "_" + litCounter.ToString();
                                litCounter++;
                                if(lit.negation)
                                    l.quant = "¬";
                                l.quant = lit.literalName;
                                l.value = "(";
                                foreach (string s in lit.categoriesNames)
                                    l.value += s;
                                l.value += ")";
                                ARLit_a.Add(l);
                            }
                        }
                        Rec_ti_literal[] ALit_a = (Rec_ti_literal[])ARLit_a.ToArray(typeof(Rec_ti_literal)); // pole literalu daneho cedentu
                           


                        // element ti_cedent (Succedent)
                        rSuc.id = "suc" + rHyp.id;
                        rSuc.type = "Succedent";
                        // literaly
                        ArrayList ARLit_s = new ArrayList();
                        foreach (BooleanLiteralStruct lit in HypList[i].booleanLiterals)
                        {
                            if (lit.cedentType.ToString() == "Succedent")
                            {
                                Rec_ti_literal l = new Rec_ti_literal();
                                l.id = "tiLit" + rHyp.id + "_" + litCounter.ToString();
                                litCounter++;
                                if (lit.negation)
                                    l.quant = "¬";
                                l.quant = lit.literalName;
                                foreach (string s in lit.categoriesNames)
                                    l.value += s;
                                ARLit_s.Add(l);
                            }
                        }
                        Rec_ti_literal[] ALit_s = (Rec_ti_literal[])ARLit_s.ToArray(typeof(Rec_ti_literal)); // pole literalu daneho cedentu
                        


                        // element ti_cedent (Condition)
                        rCon.id = "con" + rHyp.id;
                        rCon.type = "Condition";
                        // literaly
                        ArrayList ARLit_c = new ArrayList();
                        foreach (BooleanLiteralStruct lit in HypList[i].booleanLiterals)
                        {
                            if (lit.cedentType.ToString() == "Condition")
                            {
                                Rec_ti_literal l = new Rec_ti_literal();
                                l.id = "tiLit" + rHyp.id + "_" + litCounter.ToString();
                                litCounter++;
                                if (lit.negation)
                                    l.quant = "¬";
                                l.quant = lit.literalName;
                                l.value = "(";
                                foreach (string s in lit.categoriesNames)
                                    l.value += s;
                                l.value += ")";
                                ARLit_s.Add(l);
                            }
                        }
                        Rec_ti_literal[] ALit_c = (Rec_ti_literal[])ARLit_c.ToArray(typeof(Rec_ti_literal)); // pole literalu daneho cedentu


                        // vypsani hypotezy do XML
                        resultString += rHyp.ToXML();
                        // vypsani Antecedentu do XML
                        resultString += rAnt.ToXML(ALit_a);
                        // vypsani Succedentu do XML
                        resultString += rSuc.ToXML(ALit_s);
                        // vypsani Condition do XML
                        resultString += rCon.ToXML(ALit_c);

                    }
                }
                catch (System.Exception e)
                {
                    ErrStr += "Box ProjectIdentifier=" + box.ProjectIdentifier.ToString() + ": " + e.Message + "\n";
                }                
            }
            // vypsani pripadne chybove hlasky:
            if (!String.IsNullOrEmpty(ErrStr))
                MessageBox.Show("Pri nacitani hypotez doslo k chybam:\n" + ErrStr, "Chyba", MessageBoxButtons.OK, MessageBoxIcon.Error);

            // korenovy element
            resultString += "</active_list>";

               // Kody - ulozeni vystupu do souboru "XML4fthypExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XML4fthypExample.xml");

            return resultString;
        }


        // ==================== Cedent ================================
    }

    public class Rec_hyp_4ft
    {
        public string id = "";    // ID 4ft-hypotezy
        public string db_name = "";   // jmeno databaze
        public string matrix_name = ""; // jmeno datove matice
        public string task_name = "";   // jmeno ulohy
        public int a = 0;
        public int b = 0;
        public int c = 0;
        public int d = 0;
        public int conf = 0;
        public int d_conf = 0;
        public int e_conf = 0;
        public int support = 0;
        public int completness = 0;
        public int avg_diff = 0;
        public int low_bnd_imp = 0;
        public int up_bnd_imp = 0;
        public int low_bnd_dbl_imp = 0;
        public int up_bnd_dbl_imp = 0;
        public int low_bnd_eq = 0;
        public int up_bnd_eq = 0;
        public int fisher = 0;
        public int chi_sq = 0;
        public string antecedent = "";  // reference
        public string succedent = "";   // reference
        public string condition = "";   // reference


        // prevod recordu na XML string
        public string ToXML()
        {
            string XML = "";
            
            XML += "<hyp_4ft id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" task_name=\"" + task_name + "\" a=\"" + a.ToString() + "\" b=\"" + b.ToString() +
                   "\" c=\"" + c.ToString() + "\" d=\"" + d.ToString() + "\" conf=\"" + conf.ToString() + 
                   "\" d_conf=\"" + d_conf.ToString() + "\" e_conf=\"" + e_conf.ToString() + 
                   "\" support=\"" + support.ToString() +  "\" completeness=\"" + completness.ToString() +
                   "\" avg_diff=\"" + avg_diff.ToString() + "\" low_bnd_imp=\"" + low_bnd_imp.ToString() +
                   "\" up_bnd_imp=\"" + up_bnd_imp.ToString() +  "\" low_bnd_dbl_imp=\"" + low_bnd_dbl_imp.ToString() +
                   "\" up_bnd_dbl_imp=\"" + up_bnd_dbl_imp.ToString() + "\" low_bnd_eq=\"" + low_bnd_eq.ToString() +
                   "\" up_bnd_eq=\"" + up_bnd_eq.ToString() + "\" fisher=\"" + fisher.ToString() +
                   "\" chi_sq=\"" + chi_sq.ToString() + "\" antecedent=\"" + antecedent +
                   "\" succedent=\"" + succedent + "\" condition=\"" + condition + "\"/>";
            return XML;

        }
    }

    public class Rec_ti_cedent
    {
        public string id = "";    // ID ti_cedentu
        public string type = "";  // typ cetentu (Antecedent, Succedent, Condition)

        public string ToXML()
        {
            // neobsahuje zadne literaly (podelementy)

            string XML = "";
            XML += "<ti_cedent id=\"" + id + "\" type=\"" + type + "\"/>";
            return XML;
        }      
        public string ToXML(Rec_ti_literal[] Literals)
        {
            // dostane pole literalu, vygeneruje vsechny jako podelementy

            string XML = "";
            XML += "<ti_cedent id=\"" + id + "\" type=\"" + type + "\">";
            // vygenerovani vsech literalu
            foreach(Rec_ti_literal L in Literals)
                XML += L.ToXML();
            XML += "</ti_cedent>";
            return XML;
        }

    }

    public class Rec_ti_literal
    {
        public string id = "";    // ID ti_literalu
        public string quant = "";  // jmeno vlastnosti pouzite v hypoteze (napr. "Diastolicky tlak")
        public string value = "";  // hodnota vlastnosti (napr. "<50;60)")


        public string ToXML()
        {
            // nahrazeni znaku "<", ">" v retezcich (kvuli XML)
            value = value.Replace("&", "&amp;");
            value = value.Replace("<", "&lt;");
            value = value.Replace(">", "&gt;");
            string XML = "";
            XML += "<ti_literal id=\"" + id + "\" quant=\"" + quant + "\" value=\"" + value + "\"/>";
            return XML;
        }
    }
}
