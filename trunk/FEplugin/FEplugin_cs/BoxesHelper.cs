using System;
using System.IO;
using System.Collections.Generic;
using System.Collections;
using System.Text;
using System.Windows.Forms;
using Ferda;
using Ferda.ProjectManager;
using Ferda.ModulesManager;
//using Ferda.FrontEnd;

namespace FEplugin_cs
{
    public class BoxesHelper
    {
        // z daneho zdroje ziska vsechny krabicky s danym identifikatorem
        public static IBoxModule[] ListBoxesWithID(CFEsource Source, string ID)
        {
            ArrayList MyBoxes = new ArrayList();
            foreach (IBoxModule box in Source.PM.Archive.Boxes)
            {
                //Console.WriteLine(box.MadeInCreator.Identifier.ToString());
                if (box.MadeInCreator.Identifier == ID)
                    MyBoxes.Add(box);
            }
            IBoxModule[] resultArray = (IBoxModule[])MyBoxes.ToArray(typeof(IBoxModule));
            return resultArray;
        }


        public static IBoxModule[] ListBoxesWithID(CFEsource Source, string[] ID)
        {
            ArrayList MyBoxes = new ArrayList();
            foreach (IBoxModule box in Source.PM.Archive.Boxes)
            {
                foreach (string boxtype in ID)
                {
                    if (box.MadeInCreator.Identifier == boxtype)
                        MyBoxes.Add(box);
                }
            }
            IBoxModule[] resultArray = (IBoxModule[])MyBoxes.ToArray(typeof(IBoxModule));
            return resultArray;
        }


        // ----------------------------------------

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

            IBoxModule[] resultArray = (IBoxModule[])MyUniqueBoxes.ToArray(typeof(IBoxModule));
            return resultArray;
        }

        // ----------------------------------------

        // vrati vsechny bezprostredni predchudce (ve strome) krabicky Box typu ID
        public static IBoxModule[] ListDirectAncestBoxesWithID(IBoxModule Box, string ID)
        {
            ArrayList MyBoxes = new ArrayList();
            IBoxModule[] Ancestors = Box.ConnectionsFrom().ToArray();
            foreach (IBoxModule b in Ancestors)
            {
                if (b.MadeInCreator.Identifier == ID)
                    MyBoxes.Add(b);
            }

            return (MyBoxes.ToArray(typeof(IBoxModule)) as IBoxModule[]);
        }


        public static IBoxModule[] ListDirectAncestBoxesWithID(IBoxModule Box, string[] IDs)
        {
            ArrayList MyBoxes = new ArrayList();
            IBoxModule[] Ancestors = Box.ConnectionsFrom().ToArray();
            foreach (IBoxModule b in Ancestors)
            {
                foreach (string ID in IDs)
                {
                    if (b.MadeInCreator.Identifier == ID)
                        MyBoxes.Add(b);
                }
            }

            return (MyBoxes.ToArray(typeof(IBoxModule)) as IBoxModule[]);
        }

        // ----------------------------------------

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
}
