using System;
using System.IO;
using System.Collections.Generic;
using System.Collections;
using System.Text;
using System.Windows.Forms;
using Microsoft.Win32;
using System.Reflection;
using Ferda;
using Ferda.ProjectManager;
using Ferda.ModulesManager;

// This modul contain classes which ensure operations with FEplugin data sources


namespace FEplugin_cs
{
    /// <summary>
    /// This class contains information about one FEplugin data source.
    /// </summary>
    public class CFEsource
    {
        
        ///////// DATA FIELDS /////////

        /// <summary>
        /// Path to file with Ferda DataMiner (.XFP) project
        /// </summary>
        private string SourcePath;

        /// <summary>
        /// Instance of class ProjectManager.
        /// </summary>
        public ProjectManager PM;

        ///////// METHODS ///////

        /// <summary>
        /// Construction of one FEplugin data source.
        /// </summary>
        /// <param name="path">Path to file with Ferda project</param>
        public CFEsource(string path)
        {
            // initialization of SourcePath
            SourcePath = path;
            
            // initialization of PM
            try
            {
                // changing current directory to Ferda FrontEnd directory
                DirManager.SetHomeFerdaFrontEnd_dir();

                // initialization of PM
                PM = new ProjectManager(new string[0], FEplugin_globals.IceConfig.ProjectManagerOptions);

                // loading the project
                if (LoadProject() == false)
                    throw new FE_error("FEP005", "Perzist ID: " + SourcePath + "\n\nReason: project can't be loaded");
            }
            catch (FE_error)
            {
                throw;
            }
            catch (System.Exception e)
            {
                DestroyPM();
                FE_error err = new FE_error("FEP005", "Perzist ID: " + SourcePath + "\n\nReason: " + e.Message);
                throw (err);
            }
            finally 
            {
                // changing actual directory to previous
                DirManager.SetHomePrevious_dir();
            }


        }

        
        /// <summary>
        /// Destruction of PM (ProjectManager).
        /// </summary>
        public void DestroyPM()
        {
            try
            {
                PM.DestroyProjectManager();
            }
            catch (System.NullReferenceException e)
            {
                Console.WriteLine("Vyjimka: " + e.Message);
            }
        }

        /// <summary>
        /// Loading the Ferda DataMiner project
        /// </summary>
        /// <returns></returns>
        private bool LoadProject()  // path to file with project is stored in SourcePath field
        {
            System.IO.FileStream fs;
            try
            {
                fs = new System.IO.FileStream(SourcePath, System.IO.FileMode.Open);
            }
            catch (System.FieldAccessException e)
            {
                Console.WriteLine("\nException: " + e.Message);
                Console.WriteLine("File " + SourcePath + " not found\n");
                return false;
            }

            try
            {
                PM.LoadProject(fs);
            }
            catch (System.Exception e)
            {
                Console.WriteLine("\nException: " + e.Message);
                return false;
            }
            finally
            {
                fs.Close();
            }

            return true;
        }
    }

    /// <summary>
    /// This class contains table of FEplugin data sources
    /// </summary>
    public class CFEsourcesTab
    {
        /// <summary>
        /// Array of created FEplugin data sources.
        /// </summary>
        private static ArrayList sources;

        /// <summary>
        /// Array of created FEplugin data sources.
        /// </summary>
        public static ArrayList Sources
        {
            get { return sources; }
        }
        
        /// <summary>
        /// Counter of created FEplugin data sources.
        /// </summary>
        private static int SrcCount;

        /// <summary>
        /// Counter of opened FEplugin data sources.
        /// </summary>
        private static int OpenSrcCount;

        /// <summary>
        /// Array of created FEplugin data sources.
        /// </summary>
        /// <returns>content of "sources" data field</returns>
        public static CFEsource[] getSources()
        {
            CFEsource[] resultArray = (CFEsource[]) sources.ToArray(typeof(CFEsource));
            return resultArray;
        }

        // static construktor
        static CFEsourcesTab()
        {
            sources = new ArrayList();
            SrcCount = 0;
            OpenSrcCount = 0;
        }

        // pridani noveho zdroje (otevre dialog pro vyber zdroje, pote ho otevre a vrati handle (index) )
        /// <summary>
        /// Creating new data source.
        /// Creates and openes source and returns handle on it.
        /// <b>notice: </b>when IceGridNode is not set as system service and some other FEplugin data source is already opened,
        /// then new data source can not be created.
        /// </summary>
        /// <param name="PersistID">Perzist ID of new source (path to Ferda project (.xfp) file)</param>
        /// <returns>Handle to newly created and opened data source.</returns>
        public static Int32 NewSource(string PersistID)
        {
            // tries to create an instance of CFEsource class
            CFEsource NS;
            try
            {
                // test, if IceGridNode is set as system service. If not and some other source is opened, new source can not be created.
                if (FEplugin_globals.IceConfig_initialized)
                {
                    if (FEplugin_globals.IceConfig.ProjectManagerOptions.IceGridAsService == false && OpenSrcCount >= 1)
                    {
                        throw new FE_error("FEP006");
                    }
                }
                
                NS = new CFEsource(PersistID);
                int index = sources.Add(NS);
                SrcCount++;
                OpenSrcCount++;
                return index;
            }
            catch (FE_error e)
            {
                FE_err_msg.show_err_msg(e);
                return -1;
            }
            catch (System.Exception e)
            {
                FE_error err = new FE_error("FEP005", "Reason: " + e.Message);
                FE_err_msg.show_err_msg(err);
                return -1;
            }

        }

        /// <summary>
        /// Closes opened data source (destructs ProjectManager)
        /// </summary>
        /// <param name="index">index of data source in data sources table</param>
        /// <returns></returns>
        public static bool CloseSource(int index)
        {
            try
            {
                if (index >= 0 && index < sources.Count)
                {
                    ((CFEsource)sources[index]).PM.DestroyProjectManager();
                }
            }
            catch (SystemException e)
            {
                FE_error err = new FE_error("FEP004", "Reason: " + e.Message);
                FE_err_msg.show_err_msg(err);
                return false;
            }
            catch (Ice.NoEndpointException) // lost of icegridnode, source can't be closed normally
            {
                OpenSrcCount--;
                return true;
            }
            catch (System.Exception e)
            {
                FE_error err = new FE_error("FEP004", "Reason: " + e.Message);
                FE_err_msg.show_err_msg(err);
                return false;
            }
#if (LADICI)
            MessageBox.Show("Zdroj " +index.ToString()+ " byl zavren\n", "Ladici hlaska", MessageBoxButtons.OK);
#endif
            OpenSrcCount--;
            return true;
        }
        
    }


    /// <summary>
    /// Class contains helpers functions for FEplugin
    /// </summary>
    public class FEPom
    {
        /// <summary>
        /// Displays an "open file dialog" - choosing the path to Ferda (.xfp) project file.
        /// </summary>
        /// <returns>Path to selected file</returns>
        public static string OpenXfpFile()
        {
            OpenFileDialog ofd = new OpenFileDialog();

            ofd.InitialDirectory = ".\\";
            ofd.Filter = "All files (*.*)|*.*|Ferda Project files (*.xfp)|*.xfp";
            ofd.FilterIndex = 2;
            ofd.RestoreDirectory = true;

            if (ofd.ShowDialog() == DialogResult.OK)
                return ofd.FileName;
            return ofd.FileName;
        }
   
    }
}
