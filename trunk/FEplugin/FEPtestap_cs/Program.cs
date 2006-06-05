using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;
using FEplugin_cs;
using System.Windows.Forms;



namespace FEPtestap_cs
{
    class Program
    {
        static void Main(string[] args)
        {
            int index1 = 0;
            int index2 = 0;
            /*string soubor = OtevriSoubor();
            Console.WriteLine("byl otevren soubor " + soubor);
             * */
            // vytvoreni noveho zdroje a pridani ho do seznamu
            try
            {
                //CFEsource src2 = new CFEsource(@"c:\Documents and Settings\Honza\Dokumenty\Barbora1.xfp");
                //index1 = CFEsourcesTab.NewSource(@"c:\Documents and Settings\Honza\Dokumenty\FERDA_CABG.xfp");
                index1 = CFEsourcesTab.NewSource(@"D:\Projekt\Vyvoj\ReportAsistent\FEProjects\Barbora1.xfp");
                //index2 = CFEsourcesTab.NewSource(@"c:\Documents and Settings\Honza\Dokumenty\FERDA_CABG.xfp");
            }
            catch (System.Exception e)
            {
                Console.WriteLine("Vyjimka: " + e.Message);
            }
            // 
            Console.WriteLine("Bylo vytvoreno " + CFEsourcesTab.SrcCount.ToString() + " zdroju\n");
            Console.WriteLine("pole CFEsourcesTab obsahuje " + CFEsourcesTab.Sources.Count.ToString() + " zdroju\n");
            CFEsource src = (CFEsource) CFEsourcesTab.Sources[0];
            Console.WriteLine("Zdroj " + index1.ToString() + " obsahuje " + ((CFEsource)CFEsourcesTab.Sources[index1]).PM.Archive.Boxes.GetLength(0).ToString() + " krabicek");
         //   Console.WriteLine("Zdroj " + index2.ToString() + " obsahuje " + ((CFEsource)CFEsourcesTab.Sources[index2]).PM.Archive.Boxes.GetLength(0).ToString() + " krabicek");
    
            // prohrabani se v archivu
            BoxesHelper.VypisKrabky(0, "LISpMinerTasks.FFTTask");
            AP_FEKL_cedent.getList(0);
            AP_FECF_cedent.getList(0);
        }

        public static string OtevriSoubor()
        {
            OpenFileDialog ofd = new OpenFileDialog();

            ofd.InitialDirectory = ".\\";
            ofd.Filter = "Ferda Project files (*.xfp)|*.xfp|All files (*.*)|*.*";
            ofd.FilterIndex = 2;
            ofd.RestoreDirectory = true;

            if (ofd.ShowDialog() == DialogResult.OK)
                return ofd.FileName;
            return ofd.FileName;
        }
    }
}
