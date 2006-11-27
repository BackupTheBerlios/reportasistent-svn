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


namespace FEplugin_cs
{

    // ==================== Active element Task ================================

    /// <summary>
    /// Implementation of Active element "Task" (ID="task")
    /// </summary>
    public class AP_FETask
    {
        /// <summary>
        /// Returns XML string with all occurences of Active element "Task" (all types of tasks).
        /// </summary>
        /// <param name="index">index of data source in FEplugin data sources table</param>
        /// <returns>XML string</returns>
        public static string getList(int index)
        {
            string resultString = ""; // result XML string
            string ErrStr = "";  // error reports
            //int counterID = 0;

            // loading DTD to resultString
            try { resultString = XMLHelper.loadDTD(); }
            catch (Exception e)
            {
#if (LADENI)
                MessageBox.Show("error while loading DTD: " + e.Message);
#endif
                return resultString;
            }

            // root element
            resultString += "<active_list>";


            List<TaskTypeStruct> TypyTask = new List<TaskTypeStruct>();
            TypyTask.Add(new TaskTypeStruct("LISpMinerTasks.FFTTask", "4FT Task"));
            TypyTask.Add(new TaskTypeStruct("LISpMinerTasks.SDFFTTask", "SD-4FT Task"));
            TypyTask.Add(new TaskTypeStruct("LISpMinerTasks.KLTask", "KL Task"));
            TypyTask.Add(new TaskTypeStruct("LISpMinerTasks.SDKLTask", "SD-KL Task"));
            TypyTask.Add(new TaskTypeStruct("LISpMinerTasks.CFTask", "CF Task"));
            TypyTask.Add(new TaskTypeStruct("LISpMinerTasks.SDCFTask", "SD-CF Task"));

            #region Loop over all Task types

            foreach (TaskTypeStruct TTS in TypyTask)
            {
                // searching all boxes Task with given type
                IBoxModule[] TaskBoxes = BoxesHelper.ListBoxesWithID(CFEsourcesTab.Sources[index] as CFEsource, TTS.TaskBoxType);
               
                #region Loop - processing of each Task with given type

                foreach (IBoxModule box in TaskBoxes)
                { 
                    // record of Task
                    Rec_task rTask = new Rec_task();

                    try
                    {
                        // setting ID
                        rTask.id = "task" + box.ProjectIdentifier.ToString();
                        
                        // searching data source name (database) - not mandatory!
                        IBoxModule[] db_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.Database");
                        if (db_names.GetLength(0) == 1)  // searched more than one data source or neither one
                            rTask.db_name = db_names[0].GetPropertyString("DatabaseName");

                        // searching data matrix name - not mandatory!
                        IBoxModule[] matrix_names = BoxesHelper.ListAncestBoxesWithID(box, "DataMiningCommon.DataMatrix");
                        if (matrix_names.GetLength(0) == 1)  // searched more than one data source or neither one
                            rTask.matrix_name = matrix_names[0].GetPropertyString("Name");

                        // searching task name
                        rTask.task_name = box.UserName;

                        // filling the "task_type"
                        rTask.task_type = TTS.TypeString;

                        // filling the "gen_state"
                        rTask.gen_state = box.GetPropertyString("GenerationState");

                        // filling the "gen_total_time"
                        rTask.gen_total_time = box.GetPropertyTime("GenerationTotalTime").ToString();

                        // filling the "gen_start_time"
                        rTask.gen_start_time = box.GetPropertyDateTime("GenerationStartTime").ToString();

                        // filling the "num_hyp"
                        rTask.num_hyp = box.GetPropertyLong("GenerationNrOfHypotheses");

                        // filling the "num_tests"
                        rTask.num_tests = box.GetPropertyLong("GenerationNrOfTests");

                        // adding Task to XML
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

            // root element
            resultString += "</active_list>";

#if (LADENI)
            // generating of error message:
            if (!String.IsNullOrEmpty(ErrStr))  // LADICI
                MessageBox.Show("Pri nacitani Task doslo k chybam:\n" + ErrStr, "Chyba", MessageBoxButtons.OK, MessageBoxIcon.Error);

            // Kody - storing output to file "XMLTaskExample.xml" in directory 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLTaskExample.xml");
#endif

            return resultString;

        }


        // pomocna struktura - vsechny typy Task zpracovavane v cyklu v getList() a k nim potrebne item
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

    #region --- Records  ---

    /// <summary>
    /// Record of one Task.
    /// </summary>
    public class Rec_task
    {
        #region DATA
        public string id = "";    // ID Task
        public string db_name = "unknown";   // database name
        public string matrix_name = "unknown"; // data matrix name
        public string task_name = "unknown";   // task name
        public string task_type = "unknown";   // task type (4FT, KL, ... )
        public string gen_state = "unknown";   // stav task (spustena ano/ne ...)
        public string gen_total_time = "unknown";   // celkovy cas vypoctu 
        public string gen_start_time = "unknown";   // cas zacatku vypoctu 
        public long num_hyp = 0; // pocet nalezenych platnych hypotheses
        public long num_tests = 0; //pocet porovnani behem vypoctu


        #endregion

        #region METHODS
        /// <summary>
        /// Generates XML string from record.
        /// </summary>
        /// <returns>XML string</returns>
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