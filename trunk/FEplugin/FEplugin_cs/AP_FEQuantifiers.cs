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

    // ==================== Aktivni prvek Kvantifikator ================================

    public class AP_FEQuantifier
    {
        /// <summary>
        /// Implementation of Active element "Quantifier"
        /// </summary>
        /// <param name="index">index of data source in data sources tab </param>
        /// <returns>Returns XML string with all occurences of Active element type "Quantifier" from data source with given index</returns>
        public static string getList(int index)
        {
            string resultString = ""; // vysledny XML string
            string ErrStr = ""; // zaznam o chybach

            // nacteni DTD do resultStringu
            try { resultString = XMLHelper.loadDTD(); }
            catch (Exception e)
            {
                MessageBox.Show("Chyba pri nacitani DTD: " + e.Message);
                return resultString;
            }
            
            // korenovy element
            resultString += "<active_list>";

            List<TaskTypeStruct> TypyTasku = new List<TaskTypeStruct>();
            TypyTasku.Add(new TaskTypeStruct("LISpMinerTasks.FFTTask", "FFTQuantifier", "4FT"));
            TypyTasku.Add(new TaskTypeStruct("LISpMinerTasks.SDFFTTask", "SDFFTQuantifier", "SD-4FT"));
            TypyTasku.Add(new TaskTypeStruct("LISpMinerTasks.KLTask", "KLQuantifier", "KL"));
            TypyTasku.Add(new TaskTypeStruct("LISpMinerTasks.SDKLTask", "SDKLQuantifier", "SD-KL"));
            TypyTasku.Add(new TaskTypeStruct("LISpMinerTasks.CFTask", "CFQuantifier", "CF"));
            TypyTasku.Add(new TaskTypeStruct("LISpMinerTasks.SDCFTask", "SDCFQuantifier", "SD-CF"));

            #region Cyklus pres vsechny typy Tasku

            foreach (TaskTypeStruct TTS in TypyTasku)
            {
                // nalezeni vsech boxu Tasku daneho typu
                IBoxModule[] TaskBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, TTS.TaskBoxType);
                #region Cylkus - zpracovani kazdeho Tasku daneho typu

                foreach (IBoxModule box in TaskBoxes)
                {
                    // record pro novy kvantfikator
                    Rec_quantifier rQuant = new Rec_quantifier();

                    // vyplneni ID kvantifikatoru
                    rQuant.id = "quant" + box.ProjectIdentifier;

                    try
                    {
                        // nalezeni jmena datoveho zdroje (databaze) - neni povinne!
                        IBoxModule[] db_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.Database");
                        if (db_names.GetLength(0) == 1)  // byl nalezen pocet datovych zdroju ruzny od jedne
                            rQuant.db_name = (db_names[0].GetPropertyOther("DatabaseName") as StringT).stringValue;

                        // nalezeni jmena datove matice - neni povinne!
                        IBoxModule[] matrix_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.DataMatrix");
                        if (matrix_names.GetLength(0) == 1)  // byl nalezen pocet datovych matic ruzny od jedne
                            rQuant.matrix_name = (matrix_names[0].GetPropertyOther("Name") as StringT).stringValue;

                        // nalezeni jmena ulohy
                        rQuant.task_name = box.UserName;

                        // vyplneni typu kvantifikatoru
                        rQuant.type = TTS.TypeString;

                        // nalezeni vsech boxu - Zakladnich kvantifikatoru daneho tasku
                        IBoxModule[] BasicQuantsBoxes = box.GetConnections(TTS.QuantSocketName);

                        // vyplneni poctu zakladnich kvantifikatoru
                        rQuant.basic_count = BasicQuantsBoxes.GetLength(0);

                        string subelementsXML = "";
                        foreach (IBoxModule BQB in BasicQuantsBoxes)
                            subelementsXML += getBasicQuantXML(BQB);
                        
                        // pridani kvantifikatoru do XML
                        resultString += rQuant.ToXML(subelementsXML);
                    }
                    catch (System.Exception e)
                    {
                        ErrStr += "Box ProjectIdentifier=" + box.ProjectIdentifier.ToString() + ": " + e.Message + "\n";
                    }
                }
                #endregion

            }

            #endregion

            // korenovy element
            resultString += "</active_list>";

            // vypsani pripadne chybove hlasky:
            if (!String.IsNullOrEmpty(ErrStr))  // LADICI
                MessageBox.Show("Pri nacitani Kvantifikatoru doslo k chybam:\n" + ErrStr, "Chyba", MessageBoxButtons.OK, MessageBoxIcon.Error);


            // Kody - ulozeni vystupu do souboru "XMLQuantExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLQuantExample.xml");

            return resultString;
        }

        
        // vygeneruje XMLstring pro dany box zakladniho kvantifikatoru
        private static string getBasicQuantXML(IBoxModule BasicQuantifierBox)
        {
            string resultStr = "";

            // record pro dany zaklani kvantifikator (BasicQuantifierBox)
            Rec_basic_quantifier rBQ = new Rec_basic_quantifier();

            // vyplneni polozky "name"
            rBQ.name = BasicQuantifierBox.UserName;

            // vyplneni polozky "type"
            if (BasicQuantifierBox.MadeInCreator.Identifier.IndexOf("Functional") != -1)
                rBQ.type = "Functional";
            else if (BasicQuantifierBox.MadeInCreator.Identifier.IndexOf("Aggregation") != -1)
                rBQ.type = "Aggregation";

            // nalezeni vsech polozek zakladniho kvantifikatoru a jejich hodnot
            List<Rec_quant_item> QItems = new List<Rec_quant_item>();

            PropertyInfo[] PI = BasicQuantifierBox.MadeInCreator.Properties;
            foreach (PropertyInfo pi in PI)
            {
                // nova polozka nastaveni
                Rec_quant_item item = new Rec_quant_item();
                // vyplneni polozek
                item.name = pi.name; // "name"

                // TODO: zatim nevim, jestli lze tohle udelat lepe. Mozna predelat
                if (pi.typeClassIceId.IndexOf("Double") != -1)
                    item.value = BasicQuantifierBox.GetPropertyDouble(pi.name).ToString();
                else if (pi.typeClassIceId.IndexOf("String") != -1)
                    item.value = BasicQuantifierBox.GetPropertyString(pi.name);
                else if (pi.typeClassIceId.IndexOf("Float") != -1)
                    item.value = BasicQuantifierBox.GetPropertyFloat(pi.name).ToString();
                else if (pi.typeClassIceId.IndexOf("Int") != -1)
                    item.value = BasicQuantifierBox.GetPropertyInt(pi.name).ToString();
                else if (pi.typeClassIceId.IndexOf("Long") != -1)
                    item.value = BasicQuantifierBox.GetPropertyLong(pi.name).ToString();
                else if (pi.typeClassIceId.IndexOf("Date") != -1)
                    item.value = BasicQuantifierBox.GetPropertyDate(pi.name).ToString();
                else if (pi.typeClassIceId.IndexOf("Time") != -1)
                    item.value = BasicQuantifierBox.GetPropertyTime(pi.name).ToString();
                else if (pi.typeClassIceId.IndexOf("Bool") != -1)
                    item.value = BasicQuantifierBox.GetPropertyBool(pi.name).ToString();

                QItems.Add(item);
            }

            resultStr += rBQ.ToXML(QItems);

            return resultStr;
        }

        
        // pomocna struktura - vsechny typy Tasku zpracovavane v cyklu v getList() a k nim potrebne polozky
        struct TaskTypeStruct
        {
            public string TaskBoxType;
            public string QuantSocketName;
            public string TypeString;

            public TaskTypeStruct(string TBT, string QSN, string TS)
            {
                TaskBoxType = TBT;
                QuantSocketName = QSN;
                TypeString = TS;
            }
        }
    }

    #region --- Recordy  ---

    public class Rec_quantifier
    {
        #region DATA
        public string id = "";    // ID kvantifikatoru
        public string db_name = "unknown";   // jmeno databaze
        public string matrix_name = "unknown"; // jmeno datove matice
        public string task_name = "unknown";   // jmeno ulohy
        public string type = "unknown";   // typ kvantifikatoru (4FT, KL, ... )
        public int basic_count = 0; //pocet zakladnich kvantifikatoru
        
        
        #endregion

        #region METHODS
        // prevod recordu na XML string
        public string ToXML()
        {
            string XML = "";

            XML += "<quantifier id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" task_name=\"" + task_name + "\" type=\"" + type + 
                   "\" basic_count=\"" + basic_count.ToString() + "\"/>";
            return XML;
        }

        public string ToXML(List<Rec_basic_quantifier> basic_quants)
        {
            string XML = "";

            XML += "<quantifier id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" task_name=\"" + task_name + "\" type=\"" + type + 
                   "\" basic_count=\"" + basic_count.ToString() + "\">";

            // vygenerovani vsech podelementu
            foreach(Rec_basic_quantifier quant in basic_quants)
                XML += quant.ToXML();
            
            XML += "</quantifier>";
            return XML;
        }

        public string ToXML(string subelements_string)
        {
            string XML = "";

            XML += "<quantifier id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" task_name=\"" + task_name + "\" type=\"" + type +
                   "\" basic_count=\"" + basic_count.ToString() + "\">";

            // vlozeni retezce podelementu
                XML += subelements_string;

            XML += "</quantifier>";
            return XML;
        }

        #endregion
    }

    public class Rec_basic_quantifier
        {
        #region DATA
        public string name = "";    // jmeno (typ) zakladniho kvantifikatoru (Founded implication, Chi-square, .....)
        public string type = "";   // typ zakladniho kvantifikatoru (Aggregation, Functional)
                
        #endregion

        #region METHODS
        // prevod recordu na XML string
        public string ToXML()
        {
            string XML = "";

            XML += "<basic_quantifier name=\"" + name + "\" type=\"" + type + "\"/>";
            return XML;

        }

        public string ToXML(List<Rec_quant_item> items)
        {
            string XML = "";

            XML += "<basic_quantifier name=\"" + name + "\" type=\"" + type + "\">";

            // vygenerovani podelementu - vsechny polozky
            foreach(Rec_quant_item item in items)
                XML += item.ToXML();

            XML += "</basic_quantifier>";
            return XML;

        }
        #endregion
    }

    public class Rec_quant_item
        {
        #region DATA
        public string name = "";    // nazev polozky zakladniho kvantifikatoru (napr. parametr)
        public string value = "";   // hodnota polozky
                
        #endregion

        #region METHODS
        // prevod recordu na XML string
        public string ToXML()
        {
            string XML = "";

            XML += "<quant_item name=\"" + name + "\" value=\"" + value + "\"/>";
            return XML;

        }
        #endregion
    }

    #endregion
}
