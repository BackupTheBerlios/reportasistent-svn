using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Collections;
using System.Xml;
using FEplugin_cs;
using System.Windows.Forms;
using System.Reflection;
//using Microsoft.Win32;



namespace FEPtestap_cs
{
    class Program
    {
        static void Main(string[] args)
        {
            //DirManager.SetHomeFerdaFrontEnd_dir();
            //Directory.SetCurrentDirectory(@"c:\FerdaDataminer\FrontEnd");

            // zkouska XML
            //XMLzkus.zkus();

            if (!FEplugin_init.initialize())
                return;
            

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
            /* 
            Console.WriteLine("Bylo vytvoreno " + CFEsourcesTab.SrcCount.ToString() + " zdroju\n");
            Console.WriteLine("pole CFEsourcesTab obsahuje " + CFEsourcesTab.Sources.Count.ToString() + " zdroju\n");
            
             */
            CFEsource src = (CFEsource) CFEsourcesTab.Sources[0];
            
            //Console.WriteLine("Zdroj " + index1.ToString() + " obsahuje " + ((CFEsource)CFEsourcesTab.Sources[index1]).PM.Archive.Boxes.GetLength(0).ToString() + " krabicek");
         //   Console.WriteLine("Zdroj " + index2.ToString() + " obsahuje " + ((CFEsource)CFEsourcesTab.Sources[index2]).PM.Archive.Boxes.GetLength(0).ToString() + " krabicek");
    
            // prohrabani se v archivu
            //BoxesHelper.VypisKrabky(0, "LISpMinerTasks.FFTTask");
            string blabla = AP_FEData_matrix.getList(0);
            Console.Write("\n\n" + blabla);
            //AP_FECF_cedent.getList(0);
            Console.WriteLine("\n\nKONEC");
        }

        //public static string OtevriSoubor()
        //{
        //    OpenFileDialog ofd = new OpenFileDialog();

        //    ofd.InitialDirectory = ".\\";
        //    ofd.Filter = "Ferda Project files (*.xfp)|*.xfp|All files (*.*)|*.*";
        //    ofd.FilterIndex = 2;
        //    ofd.RestoreDirectory = true;

        //    if (ofd.ShowDialog() == DialogResult.OK)
        //        return ofd.FileName;
        //    return ofd.FileName;
        //}
    }

    public class XMLzkus
    {
        public static void zkus()
        {
            string path = @"d:\xml2.xml";
            XmlDocument doc = new XmlDocument();

            doc.Load(path);

            // nalezeni  nejmspejsu elementu BoxesLocalization
            XmlNode atr = doc.SelectSingleNode("/BoxesLocalization");
            //string URI = atr.NamespaceURI;

            XmlNamespaceManager NSM = new XmlNamespaceManager(doc.NameTable);

            NSM.AddNamespace("ns", @"http://ferda.is-a-geek.net");

            string query = "/ns:BoxesLocalization/ns:BoxLocalization[ns:Identifier='DataMiningCommon.DerivedColumn']/ns:Label";

            XmlNodeList l = doc.SelectNodes(query,NSM);
            if (l.Count > 0)
            {
                foreach (XmlNode n in l)
                {
                    Console.WriteLine("\n\n");
                    Console.Write(n.InnerText);
                }
            }
        }
    }
}
