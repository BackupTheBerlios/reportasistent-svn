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
//using Ferda.FrontEnd;




namespace FEplugin_cs
{
    public class CFEsource
    {
        
        ///////// DATA /////////
        private string SourcePath;   // cesta k souboru s projektem Ferda Dataminer (.XFP)
        public ProjectManager PM;    // instance tridy ProjectManager

        ///////// METODY ///////

        // konstruktor
        public CFEsource(string path)   // path = cesta k souboru s projektem
        {
            // inicializace SourcePath
            SourcePath = path;
            
            // inicializace PM
            try
            {
                // zmena aktualniho adresare na domovsky LMRA
                DirManager.SetHomeFerdaFrontEnd_dir();


                // inicializace polozky PM
                PM = new ProjectManager(new string[0], FEplugin_globals.IceConfig.ProjectManagerOptions);

                // nahrani projektu
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
                // zmena aktualniho adresare zpet
                DirManager.SetHomePrevious_dir();
            }


        }

        // zruseni PM (ProjectManagera)
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

        // nahrani projektu
        private bool LoadProject()  // cesta souboru projektu v polozce SourcePath
        {
            System.IO.FileStream fs;
            try
            {
                fs = new System.IO.FileStream(SourcePath, System.IO.FileMode.Open);
            }
            catch (System.FieldAccessException e)
            {
                Console.WriteLine("\nVyjimka: " + e.Message);
                Console.WriteLine("Soubor " + SourcePath + " nebyl nalezen\n");
                return false;
            }

            try
            {
                PM.LoadProject(fs);
            }
            catch (System.Exception e)
            {
                Console.WriteLine("\nVyjimka: " + e.Message);
                return false;
            }
            finally
            {
                fs.Close();
            }

            return true;
        }


    }

    public class CFEsourcesTab
    {
        // pole vytvorenych zdroju
        public static ArrayList Sources;
        
        // pocitadlo vytvorenych zdroju
        public static int SrcCount;

        // pocitadlo vytvorenych otevrenych zdroju
        public static int OpenSrcCount;

        public static CFEsource[] getSources()
        {
            CFEsource[] resultArray = (CFEsource[]) Sources.ToArray(typeof(CFEsource));
            return resultArray;
        }

        // staticky konstruktor
        static CFEsourcesTab()
        {
            Sources = new ArrayList();
            SrcCount = 0;
            OpenSrcCount = 0;
        }

        // pridani noveho zdroje (otevre dialog pro vyber zdroje, pote ho otevre a vrati handle (index) )
        public static int NewSource(string PersistID)
        {
            // pokus o vytvoreni nove instance tridy CFEsource
            CFEsource NS;
            try
            {
                // test, jestli IceGridNode je nainstalovano jako sluzba. Pokud ne a je jiz otevren jiny zdroj, nemuze byt otevren dalsi
                if (FEplugin_globals.IceConfig_initialized)
                {
                    if (FEplugin_globals.IceConfig.ProjectManagerOptions.IceGridAsService == false && OpenSrcCount >= 1)
                    {
                        throw new FE_error("FEP006");
                    }
                }
                
                NS = new CFEsource(PersistID);
                int index = Sources.Add(NS);
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

        // uzavreni zdroje (zrusi ProjectManager)
        public static bool CloseSource(int index)
        {
            try
            {
                if (index >= 0 && index < Sources.Count)
                {
                    ((CFEsource)Sources[index]).PM.DestroyProjectManager();
                }
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


    // trida pomocnych funkci pro Ferdovskou zasuvku
    public class FEPom
    {
        public static string OpenXfpFile()
        {
            /* funkce otevre OpenFileDialog a vrati retezec vybraneho souboru*/
            OpenFileDialog ofd = new OpenFileDialog();

            ofd.InitialDirectory = ".\\";
            ofd.Filter = "All files (*.*)|*.*|Ferda Project files (*.xfp)|*.xfp";
            ofd.FilterIndex = 2;
            ofd.RestoreDirectory = true;

            if (ofd.ShowDialog() == DialogResult.OK)
                return ofd.FileName;
            return ofd.FileName;
        }

        public static string Test = "Testovaci retezec";
   
    }


}
