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
                        ArrayList ARLit_a = new ArrayList();
                        foreach (BooleanLiteralStruct lit in HypList[i].booleanLiterals)
                        {
                            if (lit.cedentType == CedentEnum.Antecedent)
                            {
                                Rec_ti_literal l = new Rec_ti_literal();
                                l.id = "tiLit" + rHyp.id + "_" + litCounter.ToString();
                                litCounter++;
                                if(lit.negation)
                                    l.quant = "¬";
                                l.quant = lit.literalName;
                                foreach (string s in lit.categoriesNames)
                                    l.value += s;
                                ARLit_a.Add(l);
                            }
                        }
                        Rec_ti_literal[] ALit_a = (Rec_ti_literal[])ARLit_a.ToArray(typeof(Rec_ti_literal)); // pole literalu daneho cedentu
                        #endregion

                        #region element ti_cedent (Succedent)

                        rSuc.id = "suc" + rHyp.id;
                        rSuc.type = "Succedent";
                        // literaly
                        ArrayList ARLit_s = new ArrayList();
                        foreach (BooleanLiteralStruct lit in HypList[i].booleanLiterals)
                        {
                            if (lit.cedentType == CedentEnum.Succedent)
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
                        #endregion

                        #region element ti_cedent (Condition)

                        rCon.id = "con" + rHyp.id;
                        rCon.type = "Condition";
                        // literaly
                        ArrayList ARLit_c = new ArrayList();
                        foreach (BooleanLiteralStruct lit in HypList[i].booleanLiterals)
                        {
                            if (lit.cedentType == CedentEnum.Condition)
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
                        Rec_ti_literal[] ALit_c = (Rec_ti_literal[])ARLit_c.ToArray(typeof(Rec_ti_literal)); // pole literalu daneho cedentu
                        #endregion

                        #region Vypsani jedne hypotezy do XML stringu

                        string oneHypString = "";
                        // vypsani hypotezy do XML
                        oneHypString += rHyp.ToXML();
                        // vypsani Antecedentu do XML
                        oneHypString += rAnt.ToXML(ALit_a);
                        // vypsani Succedentu do XML
                        oneHypString += rSuc.ToXML(ALit_s);
                        // vypsani Condition do XML
                        oneHypString += rCon.ToXML(ALit_c);

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
            if (!String.IsNullOrEmpty(ErrStr))
                MessageBox.Show("Pri nacitani hypotez doslo k chybam:\n" + ErrStr, "Chyba", MessageBoxButtons.OK, MessageBoxIcon.Error);

            // korenovy element
            resultString += "</active_list>";

               // Kody - ulozeni vystupu do souboru "XML4fthypExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XML4fthypExample.xml");

            return resultString;
        }


        // ==================== Kategorie ================================

        public static string fFECategory(int index)
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


            // zpracovani kazde krabicky - ziskani z ni vsechny kategorie
            string ErrStr = ""; // zaznam o chybach

            #region   nalezeni a zpracovani vsech krabicek Atributu (DataMiningCommon.Attributes.Attribute)

            IBoxModule[] AttrBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, "DataMiningCommon.Attributes.Attribute");

            string db_name = "";
            string matrix_name = "";
            string attr_name = "";
            int cat_id_counter = 0;

            // zpracovani kazde krabicky - ziskani z ni vsechny Kategorie
            foreach (IBoxModule ABox in AttrBoxes)
            {
                List<Rec_category> rCats = new List<Rec_category>();  // seznam vsech kategorii daneho atributu
                cat_id_counter = 1;

                // zjisteni jmena atributu (v literalu)
                attr_name = ABox.GetPropertyString("NameInLiterals");

                // nalezeni jmena datoveho zdroje (databaze)
                IBoxModule[] db_names = BoxesHelper.ListAncestBoxesWithID(ABox, "DataMiningCommon.Database");
                if (db_names.GetLength(0) != 1)  // byl nalezen pocet datovych zdroju ruzny od jedne
                    throw new System.Exception("bylo nalezeno " + db_names.GetLength(0).ToString() + " databazi");
                db_name = (db_names[0].GetPropertyOther("DatabaseName") as StringT).stringValue;

                // nalezeni jmena datove matice
                IBoxModule[] matrix_names = BoxesHelper.ListAncestBoxesWithID(ABox, "DataMiningCommon.DataMatrix");
                if (matrix_names.GetLength(0) != 1)  // byl nalezen pocet datovych matic ruzny od jedne
                    throw new System.Exception("bylo nalezeno " + matrix_names.GetLength(0).ToString() + " datovych matic");
                matrix_name = (matrix_names[0].GetPropertyOther("Name") as StringT).stringValue;



                // nalezeni seznamu kategorii daneho atributu
                List<Rec_ctgr> cat_list = new List<Rec_ctgr>(); // seznam kategorii
                CategoriesStruct cat_str = (ABox.GetPropertyOther("Categories") as CategoriesT).categoriesValue;

                #region Zpracovani kategorii typu Interval 

                // long intervals
                foreach (string key in cat_str.longIntervals.Keys)
                {
                    Rec_category rCat = new Rec_category();
                    rCat.id = "cat" + ABox.ProjectIdentifier.ToString() +"_" + cat_id_counter.ToString();
                    cat_id_counter++;
                    rCat.db_name = db_name;
                    rCat.matrix_name = matrix_name;
                    rCat.attr_name = attr_name;
                    rCat.ctgr_name = key;
                    rCat.ctgr_type = "Interval";
                    rCat.ctgr_freq = "N/A";     // TODO: doimplementovat, pujde-li
                    rCat.bool_type = "No boolean"; // TODO: co to je? Dodelat.
                    rCat.def_length = cat_str.longIntervals[key].GetLength(0);

                    List<Rec_ctgr_def> ctgr_defs = new List<Rec_ctgr_def>();
                    foreach (LongIntervalStruct lis in cat_str.longIntervals[key])
                    {
                        Rec_ctgr_def ctgr_def = new Rec_ctgr_def();
                        switch (lis.leftBoundType)
                        {
                            case BoundaryEnum.Infinity:
                                ctgr_def.definition += "(-inf";
                                break;
                            case BoundaryEnum.Round:
                                ctgr_def.definition += "(";
                                break;
                            case BoundaryEnum.Sharp:
                                ctgr_def.definition += "<";
                                break;
                        }
                        if (lis.leftBoundType != BoundaryEnum.Infinity)
                            ctgr_def.definition += lis.leftBound.ToString() + ";";
                        if (lis.rightBoundType != BoundaryEnum.Infinity)
                            ctgr_def.definition += lis.rightBound.ToString();
                        switch (lis.rightBoundType)
                        {
                            case BoundaryEnum.Infinity:
                                ctgr_def.definition += "+inf)";
                                break;
                            case BoundaryEnum.Round:
                                ctgr_def.definition += ")";
                                break;
                            case BoundaryEnum.Sharp:
                                ctgr_def.definition += ">";
                                break;
                        }
                        ctgr_defs.Add(ctgr_def);
                    }
                    // vypsani jedne kategorie do XML
                    string OneCatString = "";
                    if (ctgr_defs.Count == 0)
                        OneCatString += rCat.ToXML();
                    else
                        OneCatString += rCat.ToXML(ctgr_defs);

                    resultString += OneCatString;

                }
                // float intervals
                foreach (string key in cat_str.floatIntervals.Keys)
                {
                    Rec_category rCat = new Rec_category();
                    rCat.id = "cat" + ABox.ProjectIdentifier.ToString() + "_" + cat_id_counter.ToString();
                    cat_id_counter++;
                    rCat.db_name = db_name;
                    rCat.matrix_name = matrix_name;
                    rCat.attr_name = attr_name;
                    rCat.ctgr_name = key;
                    rCat.ctgr_type = "Interval";
                    rCat.ctgr_freq = "N/A";     // TODO: doimplementovat, pujde-li
                    rCat.bool_type = "No boolean"; // TODO: co to je? Dodelat.
                    rCat.def_length = cat_str.floatIntervals[key].GetLength(0);

                    List<Rec_ctgr_def> ctgr_defs = new List<Rec_ctgr_def>();
                    foreach (FloatIntervalStruct fis in cat_str.floatIntervals[key])
                    {
                        Rec_ctgr_def ctgr_def = new Rec_ctgr_def();
                        switch (fis.leftBoundType)
                        {
                            case BoundaryEnum.Infinity:
                                ctgr_def.definition += "(-inf";
                                break;
                            case BoundaryEnum.Round:
                                ctgr_def.definition += "(";
                                break;
                            case BoundaryEnum.Sharp:
                                ctgr_def.definition += "<";
                                break;
                        }
                        if (fis.leftBoundType != BoundaryEnum.Infinity)
                            ctgr_def.definition += fis.leftBound.ToString() + ";";
                        if (fis.rightBoundType != BoundaryEnum.Infinity)
                            ctgr_def.definition += fis.rightBound.ToString();
                        switch (fis.rightBoundType)
                        {
                            case BoundaryEnum.Infinity:
                                ctgr_def.definition += "+inf)";
                                break;
                            case BoundaryEnum.Round:
                                ctgr_def.definition += ")";
                                break;
                            case BoundaryEnum.Sharp:
                                ctgr_def.definition += ">";
                                break;
                        }
                        ctgr_defs.Add(ctgr_def);
                    }
                    // vypsani jedne kategorie do XML
                    string OneCatString = "";
                    if (ctgr_defs.Count == 0)
                        OneCatString += rCat.ToXML();
                    else
                        OneCatString += rCat.ToXML(ctgr_defs);

                    resultString += OneCatString;

                }
                //  date time intervals  
                foreach (string key in cat_str.dateTimeIntervals.Keys)
                {
                    Rec_category rCat = new Rec_category();
                    rCat.id = "cat" + ABox.ProjectIdentifier.ToString() + "_" + cat_id_counter.ToString();
                    cat_id_counter++;
                    rCat.db_name = db_name;
                    rCat.matrix_name = matrix_name;
                    rCat.attr_name = attr_name;
                    rCat.ctgr_name = key;
                    rCat.ctgr_type = "Interval";
                    rCat.ctgr_freq = "N/A";     // TODO: doimplementovat, pujde-li
                    rCat.bool_type = "No boolean"; // TODO: co to je? Dodelat.
                    rCat.def_length = cat_str.floatIntervals[key].GetLength(0);

                    List<Rec_ctgr_def> ctgr_defs = new List<Rec_ctgr_def>();
                    foreach (DateTimeIntervalStruct dis in cat_str.dateTimeIntervals[key])
                    {
                        Rec_ctgr_def ctgr_def = new Rec_ctgr_def();
                        switch (dis.leftBoundType)
                        {
                            case BoundaryEnum.Infinity:
                                ctgr_def.definition += "(-inf";
                                break;
                            case BoundaryEnum.Round:
                                ctgr_def.definition += "(";
                                break;
                            case BoundaryEnum.Sharp:
                                ctgr_def.definition += "<";
                                break;
                        }
                        if (dis.leftBoundType != BoundaryEnum.Infinity)
                            ctgr_def.definition += dis.leftBound.ToString() + ";";
                        if (dis.rightBoundType != BoundaryEnum.Infinity)
                            ctgr_def.definition += dis.rightBound.ToString();
                        switch (dis.rightBoundType)
                        {
                            case BoundaryEnum.Infinity:
                                ctgr_def.definition += "+inf)";
                                break;
                            case BoundaryEnum.Round:
                                ctgr_def.definition += ")";
                                break;
                            case BoundaryEnum.Sharp:
                                ctgr_def.definition += ">";
                                break;
                        }
                        ctgr_defs.Add(ctgr_def);
                    }
                    // vypsani jedne kategorie do XML
                    string OneCatString = "";
                    if (ctgr_defs.Count == 0)
                        OneCatString += rCat.ToXML();
                    else
                        OneCatString += rCat.ToXML(ctgr_defs);

                    resultString += OneCatString;
                }
                #endregion

                // enums
                foreach (string key in cat_str.enums.Keys)
                {
                    Rec_category rCat = new Rec_category();
                    rCat.id = "cat" + ABox.ProjectIdentifier.ToString() + "_" + cat_id_counter.ToString();
                    cat_id_counter++;
                    rCat.db_name = db_name;
                    rCat.matrix_name = matrix_name;
                    rCat.attr_name = attr_name;
                    rCat.ctgr_name = key;
                    rCat.ctgr_type = "Enumeration";
                    rCat.ctgr_freq = "N/A";     // TODO: doimplementovat, pujde-li
                    rCat.bool_type = "No boolean"; // TODO: co to je? Dodelat.
                    rCat.def_length = cat_str.enums[key].GetLength(0);

                    List<Rec_ctgr_def> ctgr_defs = new List<Rec_ctgr_def>();
                    foreach (string enu in cat_str.enums[key])
                    {
                        Rec_ctgr_def ctgr_def = new Rec_ctgr_def();
                        ctgr_def.definition = enu;
                        ctgr_defs.Add(ctgr_def);
                    }
                    // vypsani jedne kategorie do XML
                    string OneCatString = "";
                    if (ctgr_defs.Count == 0)
                        OneCatString += rCat.ToXML();
                    else
                        OneCatString += rCat.ToXML(ctgr_defs);

                    resultString += OneCatString;
                }

            }

            #endregion


            resultString += "</active_list>";

            // Kody - ulozeni vystupu do souboru "XMLAttrExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLCatExample.xml");

            return resultString;
        }


        // ==================== Atribut ================================

        public static string fFEAttribute(int index)
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

            string ErrStr = ""; // zaznam o chybach

            #region  A) nalezeni vsech krabicek Atributu (DataMiningCommon.Attributes.Attribute)

            IBoxModule[] AttrBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, "DataMiningCommon.Attributes.Attribute");

            // zpracovani kazde krabicky - ziskani z ni vsechny Atributy
            foreach (IBoxModule ABox in AttrBoxes)
            {
                Rec_attribute rAttr = new Rec_attribute();

                // nastaveni ID atributu
                rAttr.id = "Attr" + ABox.ProjectIdentifier.ToString();
                
                // zjisteni jmena literalu
                rAttr.attr_name = ABox.GetPropertyString("NameInLiterals");

                // nalezeni jmena datoveho zdroje (databaze)
                IBoxModule[] db_names = BoxesHelper.ListAncestBoxesWithID(ABox, "DataMiningCommon.Database");
                if (db_names.GetLength(0) != 1)  // byl nalezen pocet datovych zdroju ruzny od jedne
                    throw new System.Exception("bylo nalezeno " + db_names.GetLength(0).ToString() + " databazi");
                rAttr.db_name = (db_names[0].GetPropertyOther("DatabaseName") as StringT).stringValue;

                // nalezeni jmena datove matice
                IBoxModule[] matrix_names = BoxesHelper.ListAncestBoxesWithID(ABox, "DataMiningCommon.DataMatrix");
                if (matrix_names.GetLength(0) != 1)  // byl nalezen pocet datovych matic ruzny od jedne
                    throw new System.Exception("bylo nalezeno " + matrix_names.GetLength(0).ToString() + " datovych matic");
                rAttr.matrix_name = (matrix_names[0].GetPropertyOther("Name") as StringT).stringValue;

                
                // nalezeni jmena zdrojoveho sloupce nebo zpusobu odvozeni
                IBoxModule[] col_names = BoxesHelper.ListDirectAncestBoxesWithID(ABox, "DataMiningCommon.Column");
                if (col_names.GetLength(0) != 1 && col_names.GetLength(0) != 0)  // byl nalezen chybny pocet zdrojovych sloupcu
                    throw new System.Exception("bylo nalezeno " + col_names.GetLength(0).ToString() + " zdrojovych sloupcu");
                if(col_names.GetLength(0) == 1)
                    rAttr.creation = col_names[0].GetPropertyString("Name");

                IBoxModule[] dercol_names = BoxesHelper.ListDirectAncestBoxesWithID(ABox, "DataMiningCommon.DerivedColumn");
                if (dercol_names.GetLength(0) != 1 && dercol_names.GetLength(0) != 0)  // byl nalezen chybny pocet zdrojovych sloupcu
                    throw new System.Exception("bylo nalezeno " + dercol_names.GetLength(0).ToString() + " zdrojovych odvozenych sloupcu");
                if (dercol_names.GetLength(0) == 1)
                    rAttr.creation = dercol_names[0].GetPropertyString("Formula");
                
                  
                // nalezeni poctu kategorii
                rAttr.ctgr_count = ABox.GetPropertyLong("CountOfCategories");

                // zjisteni kategorie "chybejici hodnota"
                string nul_cat = ABox.GetPropertyString("IncludeNullCategory");
                List<Rec_missing_value> MisVal_list = new List<Rec_missing_value>();  // pole recordu chybejicich hodnot
                if (!String.IsNullOrEmpty(nul_cat))
                {
                    Rec_missing_value MisVal = new Rec_missing_value();
                    MisVal.name = nul_cat;
                    MisVal_list.Add(MisVal);
                }

                // nalezeni nazvu kategorii a jejich frekvenci
                List<Rec_ctgr> cat_list = new List<Rec_ctgr>(); // seznam kategorii
                CategoriesStruct cat_str = (ABox.GetPropertyOther("Categories") as CategoriesT).categoriesValue;
                
                // long intervals
                foreach (string key in cat_str.longIntervals.Keys)
                {
                        Rec_ctgr new_li = new Rec_ctgr();
                        new_li.freq = "N/A";  // Not Available - TODO (doimplementovat, bude-li mozno)
                        new_li.name = key;
                        cat_list.Add(new_li);
                }
                // float intervals
                foreach (string key in cat_str.floatIntervals.Keys)
                {
                    Rec_ctgr new_li = new Rec_ctgr();
                    new_li.freq = "N/A";  // Not Available - TODO (doimplementovat, bude-li mozno)
                    new_li.name = key;
                    cat_list.Add(new_li);
                }
                //  date time intervals
                foreach (string key in cat_str.dateTimeIntervals.Keys)
                {
                    Rec_ctgr new_li = new Rec_ctgr();
                    new_li.freq = "N/A";  // Not Available - TODO (doimplementovat, bude-li mozno)
                    new_li.name = key;
                    cat_list.Add(new_li);
                }
                // enums
                foreach (string key in cat_str.enums.Keys)
                {
                    Rec_ctgr new_li = new Rec_ctgr();
                    new_li.freq = "N/A";  // Not Available - TODO (doimplementovat, bude-li mozno)
                    new_li.name = key;
                    cat_list.Add(new_li);
                }



                #region Vypsani jednoho Atributu do XML stringu

                string oneAttrString = "";
                // vypsani hypotezy do XML

                if (MisVal_list.Count == 0 && cat_list.Count == 0)
                    oneAttrString += rAttr.ToXML();
                else
                    oneAttrString += rAttr.ToXML(cat_list, MisVal_list);
                
                resultString += oneAttrString;

                #endregion


            }

            #endregion

            // korenovy element
            resultString += "</active_list>";

            // Kody - ulozeni vystupu do souboru "XMLAttrExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLAttrExample.xml");

            return resultString;
        }  // TODO: atributy v krabickach EachValueOneCategory, Equidistant, Equifrequency???
    }

    #region Recordy pro jednotlive aktivni prvky

    #region --- 4ft-hypoteza ---

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
                   "\" support=\"" + support.ToString() +  "\" completeness=\"" + completness.ToString() +
                   "\" avg_diff=\"" + avg_diff.ToString() + "\" low_bnd_imp=\"" + low_bnd_imp.ToString() +
                   "\" up_bnd_imp=\"" + up_bnd_imp.ToString() +  "\" low_bnd_dbl_imp=\"" + low_bnd_dbl_imp.ToString() +
                   "\" up_bnd_dbl_imp=\"" + up_bnd_dbl_imp.ToString() + "\" low_bnd_eq=\"" + low_bnd_eq.ToString() +
                   "\" up_bnd_eq=\"" + up_bnd_eq.ToString() + "\" fisher=\"" + fisher.ToString() +
                   "\" chi_sq=\"" + chi_sq.ToString() + "\" antecedent=\"" + antecedent +
                   "\" succedent=\"" + succedent + "\" condition=\"" + condition + "\"/>";
            return XML;

        }
        #endregion
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
    #endregion

    #region --- Atribut ---

    public class Rec_attribute
    {
        #region DATA

        public string id = "";
        public string db_name = "";
        public string matrix_name = "";
        public string attr_name = "";
        public string creation = "";
        public long ctgr_count = 0;
        #endregion

        #region METHODS

        public string ToXML()
        {
            string XML = "";

            XML += "<attribute id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" attr_name=\"" + attr_name + "\" creation=\"" + creation +
                   "\" ctgr_count=\"" + ctgr_count.ToString() + "\"/>";
            return XML;
        }

        public string ToXML(List<Rec_ctgr> Categories, List<Rec_missing_value> MissingValue)
        {
            string XML = "";

            XML += "<attribute id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" attr_name=\"" + attr_name + "\" creation=\"" + creation +
                   "\" ctgr_count=\"" + ctgr_count.ToString() + "\">";
            // vygenerovani vsech podelementu - ctgr
            if (Categories.Count > 0)
            {
                foreach (Rec_ctgr ctgr in Categories)
                    XML += ctgr.ToXML();
            }
            // vygenerovani vsech podelementu - missing_value
            if (MissingValue.Count > 0)
            {
                foreach(Rec_missing_value mv in MissingValue)    
                    XML += mv.ToXML();
            }
            XML += "</attribute>";
            return XML;
        }
        #endregion
    }

    public class Rec_ctgr
    {
        #region DATA

        public string name = "";
        public string freq = "";
        #endregion

        #region METHODS

        public string ToXML()
        {
            // nahrazeni znaku "<", ">" v retezcich (kvuli XML)
            name = name.Replace("&", "&amp;");
            name = name.Replace("<", "&lt;");
            name = name.Replace(">", "&gt;");
            string XML = "";
            XML += "<ctgr name=\"" + name + "\" freq=\"" + freq + "\"/>";
            return XML;
        }
        #endregion
    }

    public class Rec_missing_value
    {
        #region DATA

        public string name = "";
        #endregion

        #region METHODS

        public string ToXML()
        {
            // nahrazeni znaku "<", ">" v retezcich (kvuli XML)
            name = name.Replace("&", "&amp;");
            name = name.Replace("<", "&lt;");
            name = name.Replace(">", "&gt;");
            string XML = "";
            XML += "<missing_value name=\"" + name + "\"/>";
            return XML;
        }
        #endregion
    }

    #endregion

    #region --- Kategorie ---

    public class Rec_category
    {
        #region DATA

        public string id = "";
        public string db_name = "";
        public string matrix_name = "";
        public string attr_name = "";
        public string ctgr_name = "";
        public string ctgr_type = "";
        public string ctgr_freq = "";
        public string bool_type = "";
        public long def_length = 0;

        #endregion

        #region METHODS

        public string ToXML()
        {
            string XML = "";

            XML += "<category id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" attr_name=\"" + attr_name + "\" ctgr_name=\"" + ctgr_name + "\" ctgr_type=\"" + ctgr_type +
                   "\" ctgr_freq=\"" + ctgr_freq + "\" bool_type=\"" + bool_type + 
                   "\" def_length=\"" + def_length.ToString() + "\"/>";
            return XML;
        }

        public string ToXML(List<Rec_ctgr_def> Cat_defs)
        {
            string XML = "";

            XML += "<category id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" attr_name=\"" + attr_name + "\" ctgr_name=\"" + ctgr_name + "\" ctgr_type=\"" + ctgr_type +
                   "\" ctgr_freq=\"" + ctgr_freq + "\" bool_type=\"" + bool_type +
                   "\" def_length=\"" + def_length.ToString() + "\">";
            // vygenerovani vsech podelementu - ctgr_def
            if (Cat_defs.Count > 0)
            {
                foreach (Rec_ctgr_def ctgr_def in Cat_defs)
                    XML += ctgr_def.ToXML();
            }
            
            XML += "</category>";
            return XML;
        }
        #endregion
    }

    public class Rec_ctgr_def
    {
        #region DATA

        public string definition = "";

        #endregion

        #region METHODS

        public string ToXML()
        {
            // nahrazeni znaku "<", ">" v retezcich (kvuli XML)
            definition = definition.Replace("&", "&amp;");
            definition = definition.Replace("<", "&lt;");
            definition = definition.Replace(">", "&gt;");
            string XML = "";
            XML += "<ctgr_def definition=\"" + definition + "\"/>";
            return XML;
        }
        #endregion
    }
    #endregion

    #endregion
}
