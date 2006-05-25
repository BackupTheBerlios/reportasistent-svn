using System;
using System.IO;
using System.Collections.Generic;
using System.Collections;
using System.Text;
using System.Windows.Forms;
using Ferda;
using Ferda.ProjectManager;
using Ferda.ModulesManager;
using Ferda.FrontEnd;



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
                // nahrani konfigurace Ice ze souboru
                // Kody: TODO ... odstranit "natvrdo" cesty ke konfiguracnim souborum, lepsi nacitat z registru/konf. souboru
                Ferda.FrontEnd.FrontEndConfig iceConfig = Ferda.FrontEnd.FrontEndConfig.Load();
                

                // inicializace polozky PM
                PM = new ProjectManager(new string[0], iceConfig.ProjectManagerOptions);

                // nahrani projektu
                if (LoadProject() == false)
                    throw new System.Exception("Nepodarilo se nahrat projekt ze souboru " + SourcePath);
            }
            catch (System.Exception e)
            {
                Console.WriteLine("Vyjimka: " + e.Message);
                //MessageBox.Show("Chyba :\n" + e.Message, "Vyjimka", MessageBoxButtons.OK, MessageBoxIcon.Error);
                DestroyPM();
                throw;
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

        public static CFEsource[] getSources()
        {
            CFEsource[] resultArray = (CFEsource[]) Sources.ToArray(typeof(CFEsource));
            return resultArray;
        }

        // zkusebni cast (jestli jde inicializovat polozka pole)
        static CFEsourcesTab()
        {
            Sources = new ArrayList();
            SrcCount = 0;
        }

        // pridani noveho zdroje (otevre dialog pro vyber zdroje, pote ho otevre a vrati handle (index) )
        public static int NewSource(string PersistID)
        {
            // pokus o vytvoreni nove instance tridy CFEsource
            CFEsource NS;
            try
            {
                NS = new CFEsource(PersistID);
                int index = Sources.Add(NS);
                SrcCount++;
                return index;
            }
            catch(System.Exception e)
            {
                MessageBox.Show("Chyba pri otevirani zdroje " + PersistID + " :\n" + e.Message, "Vyjimka", MessageBoxButtons.OK, MessageBoxIcon.Error);
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
                MessageBox.Show("Chyba pri zavirani zdroje :\n" + e.Message, "Vyjimka", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
            MessageBox.Show("Zdroj " +index.ToString()+ " byl zavren\n", "Ladici hlaska", MessageBoxButtons.OK);
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
