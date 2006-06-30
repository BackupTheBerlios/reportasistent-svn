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

    // ==================== Aktivni prvek Uloha (Task) ================================

    public class AP_FETask
    {
        /// <summary>
        /// Implementation of Active element "Task"
        /// </summary>
        /// <param name="index">index of data source in data sources tab </param>
        /// <returns>Returns XML string with all occurences of Active element type "Task" (all types of task) from data source with given index</returns>
        public static string getList(int index)
        {
            string resultString = ""; // vysledny XML string
            string ErrStr = "";  // zaznamy o chybach
            int counterID = 0;

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
            TypyTasku.Add(new TaskTypeStruct("LISpMinerTasks.FFTTask", "4FT Task"));
            TypyTasku.Add(new TaskTypeStruct("LISpMinerTasks.SDFFTTask", "SD-4FT Task"));
            TypyTasku.Add(new TaskTypeStruct("LISpMinerTasks.KLTask", "KL Task"));
            TypyTasku.Add(new TaskTypeStruct("LISpMinerTasks.SDKLTask", "SD-KL Task"));
            TypyTasku.Add(new TaskTypeStruct("LISpMinerTasks.CFTask", "CF Task"));
            TypyTasku.Add(new TaskTypeStruct("LISpMinerTasks.SDCFTask", "SD-CF Task"));

            #region Cyklus pres vsechny typy Tasku

            foreach (TaskTypeStruct TTS in TypyTasku)
            {
                // nalezeni vsech boxu Tasku daneho typu
                IBoxModule[] TaskBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, TTS.TaskBoxType);
               
                #region Cylkus - zpracovani kazdeho Tasku daneho typu

                foreach (IBoxModule box in TaskBoxes)
                { 
                    // record pro Task
                    Rec_task rTask = new Rec_task();

                    try
                    {
                        // nastaveni ID
                        rTask.id = "task" + box.ProjectIdentifier.ToString();
                        
                        // nalezeni jmena datoveho zdroje (databaze) - neni povinne!
                        IBoxModule[] db_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.Database");
                        if (db_names.GetLength(0) == 1)  // byl nalezen pocet datovych zdroju ruzny od jedne
                            rTask.db_name = db_names[0].GetPropertyString("DatabaseName");

                        // nalezeni jmena datove matice - neni povinne!
                        IBoxModule[] matrix_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.DataMatrix");
                        if (matrix_names.GetLength(0) == 1)  // byl nalezen pocet datovych matic ruzny od jedne
                            rTask.matrix_name = matrix_names[0].GetPropertyString("Name");

                        // nalezeni jmena ulohy
                        rTask.task_name = box.UserName;

                        // vyplneni "task_type"
                        rTask.task_type = TTS.TypeString;

                        // vyplneni "gen_state"
                        rTask.gen_state = box.GetPropertyString("GenerationState");

                        // vyplneni "gen_total_time"
                        rTask.gen_total_time = box.GetPropertyTime("GenerationTotalTime").ToString();

                        // vyplneni "gen_start_time"
                        rTask.gen_start_time = box.GetPropertyDateTime("GenerationStartTime").ToString();

                        // vyplneni "num_hyp"
                        rTask.num_hyp = box.GetPropertyLong("GenerationNrOfHypotheses");

                        // vyplneni "num_tests"
                        rTask.num_tests = box.GetPropertyLong("GenerationNrOfTests");

                        // pridani tasku do XML
                        resultString += rTask.ToXML();
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
                MessageBox.Show("Pri nacitani Tasku doslo k chybam:\n" + ErrStr, "Chyba", MessageBoxButtons.OK, MessageBoxIcon.Error);


            // Kody - ulozeni vystupu do souboru "XMLTaskExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLTaskExample.xml");

            return resultString;

        }


        // pomocna struktura - vsechny typy Tasku zpracovavane v cyklu v getList() a k nim potrebne polozky
        struct TaskTypeStruct
        {
            public string TaskBoxType;
            public string TypeString;

            public TaskTypeStruct(string TBT, string TS)
            {
                TaskBoxType = TBT;
                TypeString = TS;
            }
        }
    }

    #region --- Recordy  ---

    public class Rec_task
    {
        #region DATA
        public string id = "";    // ID tasku
        public string db_name = "unknown";   // jmeno databaze
        public string matrix_name = "unknown"; // jmeno datove matice
        public string task_name = "unknown";   // jmeno ulohy
        public string task_type = "unknown";   // typ ulohy (4FT, KL, ... )
        public string gen_state = "unknown";   // stav ulohy (spustena ano/ne ...)
        public string gen_total_time = "unknown";   // celkovy cas vypoctu 
        public string gen_start_time = "unknown";   // cas zacatku vypoctu 
        public long num_hyp = 0; // pocet nalezenych platnych hypotez
        public long num_tests = 0; //pocet porovnani behem vypoctu


        #endregion

        #region METHODS
        // prevod recordu na XML string
        public string ToXML()
        {
            string XML = "";

            XML += "<task id=\"" + id + "\" db_name=\"" + db_name + "\" matrix_name=\"" + matrix_name +
                   "\" task_name=\"" + task_name + "\" task_type=\"" + task_type +
                   "\" gen_state=\"" + gen_state + "\" gen_total_time=\"" + gen_total_time +
                   "\" gen_start_time=\"" + gen_start_time +
                   "\" num_hyp=\"" + num_hyp.ToString() +
                   "\" num_tests=\"" + num_tests.ToString() + "\"/>";
            return XML;
        }

        #endregion
    }

    #endregion
}