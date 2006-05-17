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

    public class BoxesHelper
    {   
        // z daneho zdroje ziska vsechny krabicky s danym identifikatorem
        public static IBoxModule[] ListBoxesWithID(CFEsource Source, string ID)
        {
            ArrayList MyBoxes = new ArrayList();
            foreach(IBoxModule box in Source.PM.Archive.Boxes)
            {
                //Console.WriteLine(box.MadeInCreator.Identifier.ToString());
                if(box.MadeInCreator.Identifier == ID)
                    MyBoxes.Add(box);
            }
            IBoxModule[] resultArray = (IBoxModule[]) MyBoxes.ToArray(typeof(IBoxModule));
            return resultArray;
        }


        // vrati vsechny predchudce (ve strome) krabicky Box typu ID
        public static IBoxModule[] ListAncestBoxesWithID(IBoxModule Box, string ID)
        {
            ArrayList MyBoxes = new ArrayList();
            IBoxModule[] Ancestors = Box.ConnectionsFrom().ToArray();
            foreach (IBoxModule b in Ancestors)
            {
                if (b.MadeInCreator.Identifier == ID)  // tento predek je hledaneho typu
                    MyBoxes.Add(b);
                else  // predek neni hledaneho typu, hledame mezi jeho predky
                {
                    IBoxModule[] b_ancestors = ListAncestBoxesWithID(b, ID);  // rekurze
                    foreach (IBoxModule bb in b_ancestors)
                        MyBoxes.Add(bb);
                }
            }
            // vyrazeni duplicit
            MyBoxes.Sort();
            IBoxModule[] SortedBoxes = (IBoxModule[])MyBoxes.ToArray(typeof(IBoxModule));
            ArrayList MyUniqueBoxes = new ArrayList();
            foreach (IBoxModule bbb in SortedBoxes)
            {
                if (MyUniqueBoxes.BinarySearch(bbb) < 0)
                    MyUniqueBoxes.Add(bbb);
            }
            
            IBoxModule[] resultArray = (IBoxModule[]) MyUniqueBoxes.ToArray(typeof(IBoxModule));
            return resultArray;
        }
        
        
        public static void VypisKrabky(int zdroj, string ID)
        {
            IBoxModule[] seznam = ListBoxesWithID((CFEsourcesTab.getSources())[0], ID);
            Console.WriteLine("Bylo nalezeno {0} krabicek s ID={1}\n", seznam.Length.ToString(), ID);

            // vypsani vsech krabicek
            Console.WriteLine("\nSeznam vsech krabicek:\n");
            foreach (IBoxModule box in (CFEsourcesTab.getSources())[0].PM.Archive.Boxes)
                Console.WriteLine("Box:   " + box.MadeInCreator.Identifier + "  name:  " + box.ProjectIdentifier.ToString());
        }
    }

    public class XMLHelper
    {
        public static string loadDTD()  // vrati DTD aktivnich prvku
        {
            string DTD = "";
            string path = "../XML/dtd.dtd";   // relativni cesta k DTD souboru

            if (!File.Exists(path))
            {
                throw new Exception("Soubor " + path + " nebyl nalezen");
            }
            
            using (StreamReader sr = File.OpenText(path))
             {
                   String block;
                   // Read and display lines from the file until the end of 
                   // the file is reached.
                   while ((block = sr.ReadLine()) != null) 
                   {
                       DTD += block;
                   }
                   sr.Close();
             }
            
            
            return DTD;

        }

        public static void saveXMLexample(string XML, string path)  // ulozi XML string do souboru path
        {
            try
            {
                using (StreamWriter sw = new StreamWriter(path))
                {
                    sw.Write(XML);
                    sw.Close();
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
            }
        }
    }
}
