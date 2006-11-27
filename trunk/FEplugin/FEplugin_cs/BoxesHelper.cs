using System;
using System.IO;
using System.Collections.Generic;
using System.Collections;
using System.Text;
using System.Windows.Forms;
using Ferda;
using Ferda.ProjectManager;
using Ferda.ModulesManager;


// This module contains BoxesHelper class - class which performs some helping operations about work with Ferda boxes in FEplugin

namespace FEplugin_cs
{
    /// <summary>
    /// Class which performs some helping operations about work with Ferda boxes in FEplugin.
    /// Particularly these operations are:
    /// <ul>
    ///     <li>Finding all boxes with given box type in Ferda Archive</li>
    ///     <li>Finding all ancestors (all boxes box) with given box type in Ferda Archive tree structure</li>
    ///     <li>Finding all direct ancestors (all boxes box) with given box type in Ferda Archive tree structure</li>
    /// </ul>
    /// </summary>
    public class BoxesHelper
    {
        /// <summary>
        /// Finding all boxes with given box type in Ferda Archive (all boxes Ferda data source)
        /// </summary>
        /// <param name="Source">data source</param>
        /// <param name="ID">type of searched boxes (string identifier)</param>
        /// <returns>Array of all found boxes</returns>
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

        /// <summary>
        /// Finding all boxes with given list of box types in Ferda Archive (all boxes Ferda data source)
        /// </summary>
        /// <param name="Source">data source</param>
        /// <param name="ID">list with types of searched boxes (string identifiers)</param>
        /// <returns>Array of all found boxes</returns>
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

        /// <summary>
        /// Finding all ancestors (all boxes box) with given box type in Ferda Archive tree structure
        /// </summary>
        /// <param name="Box">Box in archive, for which function searches the ancestors</param>
        /// <param name="ID">type of searched boxes (string identifier)</param>
        /// <returns></returns>
        public static IBoxModule[] ListAncestBoxesWithID(IBoxModule Box, string ID)
        {
            ArrayList MyBoxes = new ArrayList();
            IBoxModule[] Ancestors = Box.ConnectionsFrom().ToArray();
            foreach (IBoxModule b in Ancestors)
            {
                if (b.MadeInCreator.Identifier == ID)  // this ancestor has desired type
                    MyBoxes.Add(b);
                else  // ancestor doesn't have desired type. Further we searche among it's ancestors (recurse)
                {
                    IBoxModule[] b_ancestors = ListAncestBoxesWithID(b, ID);  // recurse
                    foreach (IBoxModule bb in b_ancestors)
                        MyBoxes.Add(bb);
                }
            }
            // eliminating the duplicites
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

        /// <summary>
        /// Finding all direct ancestors (all boxes box) with given box type in Ferda Archive tree structure
        /// </summary>
        /// <param name="Box">Box in archive, for which function searches the ancestors</param>
        /// <param name="ID">type of searched boxes (string identifier)</param>
        /// <returns></returns>
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

        /// <summary>
        /// Finding all direct ancestors (all boxes box) with given box type in Ferda Archive tree structure
        /// </summary>
        /// <param name="Box">Box in archive, for which function searches the ancestors</param>
        /// <param name="ID">list with types of searched boxes (string identifiers)</param>
        /// <returns></returns>
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

        /// <summary>
        /// Helper function. Writing out the list of all boxes in archive to console 
        /// </summary>
        /// <param name="zdroj">data source</param>
        /// <param name="ID">type of box</param>
        public static void VypisKrabky(int zdroj, string ID)
        {
            IBoxModule[] seznam = ListBoxesWithID((CFEsourcesTab.getSources())[0], ID);
            Console.WriteLine("{0} of boxes with ID={1} was found\n", seznam.Length.ToString(), ID);

            // writing out all boxes
            Console.WriteLine("\nList of all boxes:\n");
            foreach (IBoxModule box in (CFEsourcesTab.getSources())[0].PM.Archive.Boxes)
                Console.WriteLine("Box:   " + box.MadeInCreator.Identifier + "  name:  " + box.ProjectIdentifier.ToString());
        }
    }
}
