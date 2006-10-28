using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using Ferda;
using Ferda.ProjectManager;
using Ferda.ModulesManager;
using Ferda.Modules;
using Ferda.Modules.Helpers;
using Ferda.Modules.Quantifiers;
//using Ferda.FrontEnd;

namespace FEplugin_cs
{

    // ==================== Aktivni prvek Uloha (Task) ================================

    public class AP_FEferda_box
    {
        /// <summary>
        /// Implementation of Active element "ferda_box"
        /// </summary>
        /// <param name="index">index of data source in data sources tab </param>
        /// <returns>Returns XML string with all occurences of Active element type "ferda_box" (all types of task) from data source with given index</returns>
        public static string getList(int index)
        {
            string resultString = ""; // vysledny XML string
            string ErrStr = "";  // zaznamy o chybach
            //int counterID = 0;

            // nacteni DTD do resultStringu
            try { resultString = XMLHelper.loadDTD(); }
            catch (Exception e)
            {
#if (LADENI)
                MessageBox.Show("Chyba pri nacitani DTD: " + e.Message);
#endif
                return resultString;
            }

            

            bool nactena_lokalizace = false;
            //XmlDocument lokalizaceDoc = new XmlDocument(); // XML dokument s nactenou lokalizaci
            XmlNamespaceManager NS_manager; // NameSpace manager XML dokumentu

            string XPathQuery = "";     // XPath dotaz
            #region nacteni XML s jazykovou lokalizaci z konfiguracniho souboru

            try 
            {
                string FEBoxesDirPath = DirManager.get_FerdaBoxes_dir();
                if (String.IsNullOrEmpty(FEBoxesDirPath))  // nenalezena cesta k adresari s XML Boxes konfig. soubory
                    throw new Exception("Nenalezena cesta k adresari s konfig. souborem Boxu");

                string path = DirManager.get_FerdaBoxes_dir() + @"\boxesLocalization.en-US.xml";  // anglicka lokalizace

                //lokalizaceDoc.Load(path);

                nactena_lokalizace = true;
            }
            catch(Exception)
            {
                nactena_lokalizace = false;
            }
            #endregion
            

            // korenovy element
            resultString += "<active_list>";


            // nalezeni vsech boxu v archivu
            IBoxModule[] Boxes = (CFEsourcesTab.Sources[index] as CFEsource).PM.Archive.Boxes;
           
            #region Cylkus - zpracovani kazdeho Boxu z archivu

            foreach (IBoxModule box in Boxes)
            {
                // record pro Box
                Rec_ferda_box rBox = new Rec_ferda_box();

                // seznam recordu - properties Boxu
                List<Rec_febox_property> lBoxProperties = new List<Rec_febox_property>();

                try
                {
                    // nastaveni ID
                    rBox.id = "box" + box.ProjectIdentifier.ToString();
                    
                    // nalezeni typu krabicky
                    rBox.box_type = box.MadeInCreator.Identifier;

                    //zjisteni lokalizovaneho typu krabicky
                    rBox.box_type = box.MadeInCreator.Label;

                        //// zkusim zjistit Label z lokalizace
                        //if (nactena_lokalizace)
                        //{
                        //    try
                        //    {
                        //        // namespace manager - namespace pro dotaz
                        //        NS_manager = new XmlNamespaceManager(lokalizaceDoc.NameTable);
                        //        NS_manager.AddNamespace("ns", @"http://ferda.is-a-geek.net");

                        //        // sestaveni dotazu
                        //        XPathQuery = "/ns:BoxesLocalization/ns:BoxLocalization[ns:Identifier='" +
                        //                    rBox.box_type +
                        //                    "']/ns:Label";

                        //        XmlNodeList resultNodeList = lokalizaceDoc.SelectNodes(XPathQuery, NS_manager);
                        //        if (resultNodeList.Count > 0)
                        //            rBox.box_type = resultNodeList[0].InnerXml;
                        //    }
                        //    catch (Exception) { }
                        //}

                    // nalezeni uzivatelskeho jmena krabicky
                    rBox.user_name = box.UserName;
                    if (string.IsNullOrEmpty(box.UserName))
                        rBox.user_name = "";
                    
                    // nalezeni uzivatelskeho popisku krabicky - neni povinne!
                    rBox.user_hint = box.UserHint;
                    if (string.IsNullOrEmpty(box.UserHint))
                        rBox.user_hint = "";


                    #region vyplneni seznamu vsech properties krabicky

                    // nalezeni informaci vsech properties krabicky
                    PropertyInfo[] prinfos = box.MadeInCreator.Properties;

                    // cyklus pres vsechny properties
                    foreach (PropertyInfo prinf in prinfos)
                    {
                        try
                        {
                            Rec_febox_property rProp = new Rec_febox_property();
                            rProp.name = prinf.name;
    
                                // PREDELAT, jde-li lepe
                            string type_name = box.GetPropertyOther(prinf.name).ToString(); // jmeno typu vlastnosti

                            switch (type_name)
                            {
                                case "Ferda.Modules.StringTI":
                                    {
                                        rProp.value = box.GetPropertyString(prinf.name);
                                        break;
                                    }
                                case "Ferda.Modules.BoolTI":
                                    {
                                        rProp.value = box.GetPropertyBool(prinf.name).ToString();
                                        break;
                                    }
                                case "Ferda.Modules.DateTI":
                                    {
                                        rProp.value = box.GetPropertyDate(prinf.name).ToString();
                                        break;
                                    }
                                case "Ferda.Modules.DateTimeTI":
                                    {
                                        rProp.value = box.GetPropertyDateTime(prinf.name).ToString();
                                        break;
                                    }
                                
                                case "Ferda.Modules.LongTI":
                                    {
                                        rProp.value = box.GetPropertyLong(prinf.name).ToString();
                                        break;
                                    }
                                case "Ferda.Modules.IntTI":
                                    {
                                        rProp.value = box.GetPropertyInt(prinf.name).ToString();
                                        break;
                                    }
                                case "Ferda.Modules.ShortTI":
                                    {
                                        rProp.value = box.GetPropertyShort(prinf.name).ToString();
                                        break;
                                    }
                                case "Ferda.Modules.FloatTI":
                                    {
                                        rProp.value = box.GetPropertyFloat(prinf.name).ToString();
                                        break;
                                    }
                                case "Ferda.Modules.DoubleTI":
                                    {
                                        rProp.value = box.GetPropertyDouble(prinf.name).ToString();
                                        break;
                                    }
                                case "Ferda.Modules.TimeTI":
                                    {
                                        rProp.value = box.GetPropertyTime(prinf.name).ToString();
                                        break;
                                    }
                            }
                            
                            // pridani property do seznamu
                            lBoxProperties.Add(rProp);
                        }
                        catch(Exception){}
                        
                    }

                    #endregion

                    // pridani tasku do XML
                    if (lBoxProperties.Count == 0)
                        resultString += rBox.ToXML();
                    else
                        resultString += rBox.ToXML(lBoxProperties);
                }
                catch (System.Exception e)
                {
                    ErrStr += "Box ProjectIdentifier=" + box.ProjectIdentifier.ToString() + ": " + e.Message + "\n";
                }
            }

            #endregion
            

            // korenovy element
 
           resultString += "</active_list>";



#if (LADENI)
            // vypsani pripadne chybove hlasky:
            if (!String.IsNullOrEmpty(ErrStr))  // LADICI
                MessageBox.Show("Pri nacitani Tasku doslo k chybam:\n" + ErrStr, "Chyba", MessageBoxButtons.OK, MessageBoxIcon.Error);

            // Kody - ulozeni vystupu do souboru "XMLTaskExample.xml" v adresari 
            XMLHelper.saveXMLexample(resultString, "../XML/XMLBoxExample.xml");
#endif

            return resultString;
        }

    }

    #region --- Recordy  ---

    public class Rec_ferda_box
    {
        #region DATA
        public string id = "";    // ID boxu
        public string box_type = "unknown";   // typ krabicky
        public string user_name = "unknown"; // uzivatelsky nazev krabicky
        public string user_hint = "unknown";   // uzivatelsky popis krabicky

        #endregion

        #region METHODS
        // prevod recordu na XML string
        public string ToXML()
        {
            user_name = XMLHelper.replaceXMLsign(user_name);
            user_hint = XMLHelper.replaceXMLsign(user_hint);
            box_type = XMLHelper.replaceXMLsign(box_type);
            
            string XML = "";

            XML += "<ferda_box id=\"" + id + "\" box_type=\"" + box_type + 
                    "\" user_name=\"" + user_name + "\" user_hint=\"" + user_hint + "\"/>";
            return XML;
        }

        public string ToXML(List<Rec_febox_property> properties)
        {
            string XML = "";

            XML += "<ferda_box id=\"" + id + "\" box_type=\"" + box_type + 
                    "\" user_name=\"" + user_name + "\" user_hint=\"" + user_hint + "\">";
            
            foreach(Rec_febox_property prop in properties)
                XML += prop.ToXML();

            XML += "</ferda_box>";

            return XML;
        }

        #endregion
    }

    public class Rec_febox_property
    {
        #region DATA
        public string name = "unknown";   // nazev property
        public string value = "unknown"; // hodnota property

        #endregion

        #region METHODS
        // prevod recordu na XML string
        public string ToXML()
        {
            name = XMLHelper.replaceXMLsign(name);
            value = XMLHelper.replaceXMLsign(value);
            
            string XML = "";

            XML += "<febox_property name=\"" + name + 
                    "\" value=\"" + value + "\"/>";
            return XML;
        }

        #endregion
    }

    #endregion
}