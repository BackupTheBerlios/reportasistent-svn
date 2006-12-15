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

//This modul contain classes: - "FEPlugin_init": in static constructor of this class important initialization operations of FEplugin are performed 
//                            - "DirManager": finding and setting of paths to important directories
//                            - "FEplugin_globals": class with global objects used in FEplugin



namespace FEplugin_cs
{
    /// <summary>
    /// Class which takes care of FEplugin initialization.
    /// </summary>
    public class FEplugin_init
    {
        /// <summary>
        /// Indication of successful initialization.
        /// </summary>
        static bool success;
        
        /// <summary>
        /// Initialization function.
        /// </summary>
        /// <returns>Sign of success of initialization operation.</returns>
        public static bool initialize()
        {
            return success;
        }

        /// <summary>
        /// Static constructor - performs the initialization (global objects).
        /// Presence of Ferda libraries is checked and missing libraries are found in Ferda install directory and copied
        /// into LM-RA directory.
        /// Here is a list of required Ferda libraries:
        /// <ul>
        ///     <li>FerdaProjectManager.dll</li>
        ///     <li>FerdaBoxInterfaces.dll</li>
        ///     <li>FerdaBoxInterfaces.dll</li>
        ///     <li>FerdaBase.dll</li>
        ///     <li>FerdaHelpers.dll</li>
        /// </ul>
        /// </summary>
        static FEplugin_init()
        {   
            success = true;
            
            try
            {
                #region Controling of presence of required Ferda DataMiner libraries and copying them if they are missing

                string app_file = Assembly.GetExecutingAssembly().FullName;
                string app_dir = Assembly.GetExecutingAssembly().Location;  // directory where libraries are copied to
                app_dir = app_dir.Replace(@"\FEplugin_cs.dll", "");

                string lib_dir = DirManager.get_FerdaFrontEnd_dir(); // directory, where the libraries are placed (Ferda FrontEnd dir)

                if (String.IsNullOrEmpty(lib_dir))
                    throw new FE_error("FEP001");

                

                    // libraries required for FEplugin FE Plugin
                string[] Libraries = new string[] { //"FerdaProjectManager.dll",
                                                    "FerdaModulesManager.dll",
                                                    "FerdaBoxInterfaces.dll",
                                                    "FerdaBase.dll",
                                                    "FerdaHelpers.dll" };

                foreach (string lib in Libraries)
                {
                    string source_name = lib_dir + @"\" + lib;
                    string target_name = app_dir + @"\" + lib;

                    
                    if (File.Exists(source_name))
                    {
                        DateTime source_time = File.GetLastWriteTime(source_name);
                        DateTime target_time;
                        if (File.Exists(target_name))
                        {
                            target_time = File.GetLastWriteTime(target_name);
                            if (target_time.CompareTo(source_time) < 0)  // copying the file
                                File.Copy(source_name, target_name);
                        }
                        else
                            File.Copy(source_name, target_name);
                    }
                    else  // file with name "source_name" wasn't found
                    {
                        throw new FE_error("FEP003", source_name);
                    }
                    
                    // initialization of global objects
                    FEplugin_globals.init();
                    if (FEplugin_globals.IceConfig_initialized == false)
                        throw new FE_error("FEP002");
                }
                #endregion


            }
            catch(FE_error e)
            {
                FE_err_msg.show_err_msg(e);
                success = false;
            }
            catch (Exception)
            {
                success = false;
            }
        }
    }

    /// <summary>
    /// Clas which searches and sets paths to important directories used in FEplugin.
    /// </summary>
    public class DirManager
    {
        /// <summary>
        /// Path to LM-Report Asistent application root directory (value in registry key HKCU\Software\LISp-Miner\ReportAsistent\Settings\ApplicationRoot).
        /// </summary>
        static string LMRA_dir;

        /// <summary>
        /// Path to directory, where Ferda FrontEnd is installed.
        /// </summary>
        static string FerdaFrontEnd_dir;

        /// <summary>
        /// Path to directory, where are stored information about Ferda boxes installed in ferda DataMiner.
        /// </summary>
        static string FerdaBoxes_dir;
        static string Previous_dir;


        /// <summary>
        /// Statical constructor - initialization of static data fields.
        /// </summary>
        static DirManager()
        {
            
            // searching the key in registry - path to LM-RA home directory
            RegistryKey regkey;
            regkey = Registry.CurrentUser.OpenSubKey(@"Software\LISp-Miner\ReportAsistent\Settings");
            if (regkey == null)
                LMRA_dir = "";
            else
            {
                LMRA_dir = (string)regkey.GetValue("ApplicationRoot");
                if (LMRA_dir == null)
                    LMRA_dir = "";
            }
//#if (DEBUG)
//            MessageBox.Show("LMRA Application root: " + LMRA_dir);
//#endif

            // searching the keys in registry -paths to FerdaFrontEnd and FerdaBoxes directories
            RegistryKey regkey2;
            regkey2 = Registry.CurrentUser.OpenSubKey(@"Software\Ferda DataMiner");
            if (regkey2 == null)
            {
                FerdaFrontEnd_dir = "";
                FerdaBoxes_dir = "";
            }
            else
            {
                FerdaFrontEnd_dir = (string)regkey2.GetValue("InstallDir");
                FerdaBoxes_dir = (string)regkey2.GetValue("InstallDir");
                if (FerdaFrontEnd_dir == null)
                {
                    FerdaFrontEnd_dir = "";
                    FerdaBoxes_dir = "";
                }
                else
                {
                    FerdaFrontEnd_dir += @"\FrontEnd";
                    FerdaBoxes_dir += @"\Server\BoxModulesServices";
                }

            }

            Previous_dir = Directory.GetCurrentDirectory();

        }

        
        /// <summary>
        /// Sets the path stored in LMRA_dir field as "current directory" and stores the actual "current directory" into Previous_dir field
        /// </summary>
        public static void SetHomeLMRA_dir()  
        {
            try
            {
                Previous_dir = Directory.GetCurrentDirectory();
                Directory.SetCurrentDirectory(LMRA_dir);
            }
            catch (Exception)
            {
#if (LADICI)
                MessageBox.Show("DirManager.SetHomeLMRA_dir(): exception");
#endif
            }

        }

        
        /// <summary>
        /// Sets the path stored in FerdaFrontEnd_dir field as "current directory" and stores the actual "current directory" into Previous_dir field
        /// </summary>
        public static void SetHomeFerdaFrontEnd_dir()  
        {
            try
            {
                Previous_dir = Directory.GetCurrentDirectory();
                Directory.SetCurrentDirectory(FerdaFrontEnd_dir);
            }
            catch (Exception)
            {
#if (LADICI)
                MessageBox.Show("DirManager.SetHomeFerdaFrontEnd_dir(): exception");
#endif
            }
        }

        
        /// <summary>
        /// Reverts the value of current directory to previous (content of Previous_dir field).
        /// </summary>
        public static void SetHomePrevious_dir() 
        {
            try
            {
                Directory.SetCurrentDirectory(Previous_dir);
            }
            catch (Exception)
            {
#if (LADICI)
                MessageBox.Show("DirManager.SetHomePrevious_dir(): exception");
#endif
            }
        }


        
        /// <summary>
        /// Returns path to Ferda FrontEnd install directory.
        /// </summary>
        /// <returns>value of FerdaFrontEnd_dir field</returns>
        public static string get_FerdaFrontEnd_dir()
        {
            return FerdaFrontEnd_dir;
        }

        
        /// <summary>
        /// Returns path to directory, where information about Ferda Boxes are stored.
        /// </summary>
        /// <returns>value of FerdaBoxes_dir field</returns>
        public static string get_FerdaBoxes_dir()
        {
            return FerdaBoxes_dir;
        }


     
        /// <summary>
        /// Returns path to LM-RA root directory.
        /// </summary>
        /// <returns>value of LMRA_dir field</returns>
        public static string get_LMRA_dir()
        {
            return LMRA_dir;
        }
    }

    /// <summary>
    /// Class which contains global objects used in FEplugin.
    /// </summary>
    public class FEplugin_globals
    {
        /// <summary>
        /// Structure with ICE configuration.
        /// </summary>
        private static FrontEndConfig iceConfig;

        /// <summary>
        /// Indicates if iceConfig was successfuly initialized
        /// </summary>
        private static bool iceConfig_initialized; 

        /// <summary>
        /// Indicates if iceConfig was successfuly initialized
        /// </summary>
        public static bool IceConfig_initialized
        {
            get { return iceConfig_initialized; }
        }

        /// <summary>
        /// Structure with ICE configuration.
        /// </summary>
        public static FrontEndConfig IceConfig
        {
            get 
            {
                return iceConfig;
            }
        }

        /// <summary>
        /// Static construktor - loading of iceConfig
        /// </summary>
        static FEplugin_globals()
        {
            
            #region loading of iceConfig
            try
            {
                FEplugin_globals.iceConfig = FrontEndConfig.Load();

                //if (FEplugin_globals.iceConfig.ProjectManagerOptions.IceGridAsService != true)  // IceGrid musi byt spusteno jako sluzba
                //    FEplugin_globals.iceConfig.ProjectManagerOptions.IceGridAsService = true;
                //if (FEplugin_globals.iceConfig.ProjectManagerOptions.StartIceGridLocaly != true)
                //    FEplugin_globals.iceConfig.ProjectManagerOptions.StartIceGridLocaly = true;
                //if (FEplugin_globals.iceConfig.ProjectManagerOptions.StopIceGridLocaly != false)
                //    FEplugin_globals.iceConfig.ProjectManagerOptions.StopIceGridLocaly = false;

                iceConfig_initialized = true;
            }
            catch (FE_error e)
            {
                if(e.code == "FEP002")  // initialization of iceConfig failed
                    iceConfig_initialized = false;
            }
            
            #endregion
        }

        /// <summary>
        /// Initialization of FEplugin global objects.
        /// </summary>
        public static void init() { }

    }
}