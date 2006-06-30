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
                    string id = "quant" + box.ProjectIdentifier;

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

                        // vyplneni typu kvantifikatoru (ulohy)
                        rQuant.task_type = TTS.TypeString;

                        // nalezeni vsech boxu - Zakladnich kvantifikatoru daneho tasku
                        IBoxModule[] BasicQuantsBoxes = box.GetConnections(TTS.QuantSocketName);

                        #region Cyklus - pres vsechny zakladni kvantifikatory

                        int bq_num = 0;  // pomocna promenna - kvuli generovani ID
                        foreach (IBoxModule BQB in BasicQuantsBoxes)
                        {
                            Rec_quantifier rQuant1 = rQuant;

                            // nastaveni ID
                            rQuant1.id = id + "_" + bq_num.ToString();
                            bq_num++;

                            // vyplneni polozky "name"
                            rQuant1.name = BQB.UserName;

                            // vyplneni polozky "type"
                            if (BQB.MadeInCreator.Identifier.IndexOf("Functional") != -1)
                                rQuant1.type = "Functional";
                            else if (BQB.MadeInCreator.Identifier.IndexOf("Aggregation") != -1)
                                rQuant1.type = "Aggregation";

                            // nalezeni vsech polozek zakladniho kvantifikatoru a jejich hodnot
                            List<Rec_quant_item> QItems = new List<Rec_quant_item>();

                            PropertyInfo[] PI = BQB.MadeInCreator.Properties;
                            foreach (PropertyInfo pi in PI)
                            {
                                // nova polozka nastaveni
                                Rec_quant_item item = new Rec_quant_item();
                                // vyplneni polozek
                                item.name = pi.name; // "name"

                                // TODO: zatim nevim, jestli lze tohle udelat lepe. Mozna predelat
                                if (pi.typeClassIceId.IndexOf("Double") != -1)
                                    item.value = BQB.GetPropertyDouble(pi.name).ToString();
                                else if (pi.typeClassIceId.IndexOf("String") != -1)
                                    item.value = BQB.GetPropertyString(pi.name);
                                else if (pi.typeClassIceId.IndexOf("Float") != -1)
                                    item.value = BQB.GetPropertyFloat(pi.name).ToString();
                                else if (pi.typeClassIceId.IndexOf("Int") != -1)
                                    item.value = BQB.GetPropertyInt(pi.name).ToString();
                                else if (pi.typeClassIceId.IndexOf("Long") != -1)
                                    item.value = BQB.GetPropertyLong(pi.name).ToString();
                                else if (pi.typeClassIceId.IndexOf("Date") != -1)
                                    item.value = BQB.GetPropertyDate(pi.name).ToString();
                                else if (pi.typeClassIceId.IndexOf("Time") != -1)
                                    item.value = BQB.GetPropertyTime(pi.name).ToString();
                                else if (pi.typeClassIceId.IndexOf("Bool") != -1)
                                    item.value = BQB.GetPropertyBool(pi.name).ToString();

                                QItems.Add(item);
                            }

                        #endregion


                            // pridani kvantifikatoru do XML
                            resultString += rQuant1.ToXML(QItems);
                        }
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
        public string task_type = "unknown";   // typ ulohy
        public string name = "unknown";   // jmeno (typ) zakladniho kvantifikatoru
        public string type = "unknown";   // typ kvantifikatoru (4FT, KL, ... )
        
        
        
        #endregion

        #region METHODS
        // prevod recordu na XML string
        public string ToXML()
        {
            string XML = "";

            XML += "<quantifier id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" task_name=\"" + task_name + "\" task_type=\"" + task_type +
                   "\" name=\"" + name + "\" type=\"" + type +  "\"/>";
            return XML;
        }

        public string ToXML(List<Rec_quant_item> items)
        {
            string XML = "";

            XML += "<quantifier id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" task_name=\"" + task_name + "\" task_type=\"" + task_type +
                   "\" name=\"" + name + "\" type=\"" + type + "\">";

            // vygenerovani podelementu - vsechny polozky
            foreach (Rec_quant_item item in items)
                XML += item.ToXML();
            
            XML += "</quantifier>";
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
