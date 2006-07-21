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

//Tento modul obsahuje tridy: - "FEPlugin_init": provede ve svem statickem konstruktoru potrebne veci v inicializaci Ferdovske zasuvky 
//                            - "FEPlugin_init": zjistovani a nastavovani cest k dulezitym adresarum



namespace FEplugin_cs
{
    // hlavni inicializacni trida FE Pluginu
    public class FEplugin_init
    {
        

        static bool success;    // priznak uspesne inicializace
        
        // inicializacni funkce
        public static bool initialize()
        {
            return success;
        }

        // staticky konstruktor - provede inicializaci
        static FEplugin_init()
        {
            
            success = true;
            
            try
            {
                #region kontrola pripadne nacteni nejnovejsich ferdovskych knihoven

                string app_file = Assembly.GetExecutingAssembly().FullName;
                string app_dir = Assembly.GetExecutingAssembly().Location;  // adresar, kam se knihovny kopiruji
                app_dir = app_dir.Replace(@"\FEplugin_cs.dll", "");

                string lib_dir = DirManager.get_FerdaFrontEnd_dir(); // adresar, kde jsou knihovny ulozeny

                if (String.IsNullOrEmpty(lib_dir))
                    throw new FE_error("FEP001");

                

                    // knihovny Ferdy potrebne pro FE Plugin
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
                            if (target_time.CompareTo(source_time) < 0)  // prekopirovani souboru
                                File.Copy(source_name, target_name);
                        }
                        else
                            File.Copy(source_name, target_name);
                    }
                    else  // soubor source_name nebyl nalezen
                    {
                        throw new FE_error("FEP003", source_name);
                    }
                    
                    // inicializace globalnich objektu
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
            catch (Exception e)
            {
                success = false;
            }
        }
    }

    // trida pro zjistovani a nastavovani cest k adresarum
    public class DirManager
    {
        static string LMRA_dir;     // adresar, kde je soubor ReportAsistent.exe
        static string FerdaFrontEnd_dir;     // adresar, kde je Ferda FrontEnd
        static string Previous_dir;


        // staticky construktor
        static DirManager()
        {
            
            // nalezeni klice LMRA adresare v registru
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

            // nalezeni klice FerdaFrontEnd adresare v registru
            RegistryKey regkey2;
            regkey2 = Registry.CurrentUser.OpenSubKey(@"Software\Ferda DataMiner");
            if (regkey2 == null)
                FerdaFrontEnd_dir = "";
            else
            {
                FerdaFrontEnd_dir = (string)regkey2.GetValue("InstallDir");
                if (FerdaFrontEnd_dir == null)
                    FerdaFrontEnd_dir = "";
                else
                    FerdaFrontEnd_dir += @"\FrontEnd";

            }

            Previous_dir = Directory.GetCurrentDirectory();

            // prekopirovani aktualnich verzi Ferdovskych knihoven do aplikacniho adresare



        }

        // nastavi jako aktualni adresar LMRA_dir a do Previous_dir uchova aktualni adresar
        public static void SetHomeLMRA_dir()  
        {
            Previous_dir = Directory.GetCurrentDirectory();
            Directory.SetCurrentDirectory(LMRA_dir);

        }

        // nastavi jako aktualni adresar FerdaFrontEnd_dir a do Previous_dir uchova aktualni adresar
        public static void SetHomeFerdaFrontEnd_dir()  
        {
            Previous_dir = Directory.GetCurrentDirectory();
            Directory.SetCurrentDirectory(FerdaFrontEnd_dir);

        }

        // nastavi jako aktualni puvodni adresar (obsah Previous_dir)
        public static void SetHomePrevious_dir() 
        {
            Directory.SetCurrentDirectory(Previous_dir);
        }


        // vrati cestu do adresare, kde je FerdaFrontEnd
        public static string get_FerdaFrontEnd_dir()
        {
            return FerdaFrontEnd_dir;
        }

        // vrati cestu do adresare, kde je ReportAsistent.exe
        public static string get_LMRA_dir()
        {
            return LMRA_dir;
        }
    }

    // trida s globalne pouzivanymi objekty v FE pluginu
    public class FEplugin_globals
    {
        static FrontEndConfig iceConfig;

        static bool iceConfig_initialized;  // priznak, zda byl iceConfig inicializovan spravne

        public static bool IceConfig_initialized
        {
            get { return iceConfig_initialized; }
        }

        // properties
        public static FrontEndConfig IceConfig
        {
            get 
            {
                return iceConfig;
            }
        }

        // staticky konstruktor
        static FEplugin_globals()
        {
            
            #region nacteni iceConfig
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
                if(e.code == "FEP002")  // spatna inicializace iceConfig
                    iceConfig_initialized = false;
            }
            
            #endregion
        }

        // inicializace globalnich objektu
        public static void init() { }

    }
}