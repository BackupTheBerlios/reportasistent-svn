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

namespace FEplugin_cs
{

    // ==================== Active element "Ferda Data Miner box" ================================

    /// <summary>
    /// Implementation of active element "Ferda Data Miner box"
    /// </summary>
    public class AP_FEferda_box
    {
        /// <summary>
        /// Returns XML string with all occurences of Active element "Ferda Data Miner box".
        /// </summary>
        /// <param name="index">index of data source in FEplugin data sources table</param>
        /// <returns>XML string</returns>
        public static string getList(int index)
        {
            string resultString = ""; // result XML string
            string ErrStr = "";  // error reports
            //int counterID = 0;

            // loading DTD to resultString
            try { resultString = XMLHelper.loadDTD(); }
            catch (Exception e)
            {
#if (LADENI)
                MessageBox.Show("error while loading DTD: " + e.Message);
#endif
                return resultString;
            }

            

            //bool localization = false;
            //XmlDocument lokalizaceDoc = new XmlDocument(); // XML dokument s nactenou lokalizaci
            //XmlNamespaceManager NS_manager; // NameSpace manager XML dokumentu

            //string XPathQuery = "";     // XPath dotaz
            //#region nacteni XML s jazykovou lokalizaci z konfiguracniho file

            //try 
            //{
            //    string FEBoxesDirPath = DirManager.get_FerdaBoxes_dir();
            //    if (String.IsNullOrEmpty(FEBoxesDirPath))  // nenalezena cesta k adresari s XML Boxes konfig. soubory
            //        throw new Exception("Nenalezena cesta k adresari s konfig. souborem Boxu");

            //    string path = DirManager.get_FerdaBoxes_dir() + @"\boxesLocalization.en-US.xml";  // anglicka lokalizace

            //    //lokalizaceDoc.Load(path);

            //    localization = true;
            //}
            //catch(Exception)
            //{
            //    localization = false;
            //}
            //#endregion
            

            // root element
            resultString += "<active_list>";


            // searching all boxes in archive
            IBoxModule[] Boxes = (CFEsourcesTab.Sources[index] as CFEsource).PM.Archive.Boxes;
           
            #region Loop - processing each box

            foreach (IBoxModule box in Boxes)
            {
                // record for Box
                Rec_ferda_box rBox = new Rec_ferda_box();

                // list of records - properties of Boxes
                List<Rec_febox_property> lBoxProperties = new List<Rec_febox_property>();

                try
                {
                    // setting ID
                    rBox.id = "box" + box.ProjectIdentifier.ToString();
                    
                    // searching box type
                    rBox.box_type = box.MadeInCreator.Identifier;

                    //searching lokalizovaneho type of krabicky
                    rBox.box_type = box.MadeInCreator.Label;

                        //// zkusim zjistit Label z lokalizace
                        //if (localization)
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

                    // searching box user name
                    rBox.user_name = box.UserName;
                    if (string.IsNullOrEmpty(box.UserName))
                        rBox.user_name = "";
                    
                    // searching user lable of box - not mandatory!
                    rBox.user_hint = box.UserHint;
                    if (string.IsNullOrEmpty(box.UserHint))
                        rBox.user_hint = "";


                    #region filling up the list of all box properties

                    // searching information of all box properties
                    PropertyInfo[] prinfos = box.MadeInCreator.Properties;

                    // Loop over all properties
                    foreach (PropertyInfo prinf in prinfos)
                    {
                        try
                        {
                            Rec_febox_property rProp = new Rec_febox_property();
                            rProp.name = prinf.name;
    
                                
                            string type_name = box.GetPropertyOther(prinf.name).ToString(); // name of property type

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
                            
                            // adding property to list
                            lBoxProperties.Add(rProp);
                        }
                        catch(Exception){}
                        
                    }

                    #endregion

                    // adding property to XML
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
            

            // root element
 
           resultString += "</active_list>";



#if (LADENI)
            // generating of error report:
            if (!String.IsNullOrEmpty(ErrStr))
                MessageBox.Show("Pri nacitani Tasku doslo k chybam:\n" + ErrStr, "Chyba", MessageBoxButtons.OK, MessageBoxIcon.Error);

            // Kody - saving output to file "XMLTaskExample.xml" in XML directory
            XMLHelper.saveXMLexample(resultString, "../XML/XMLBoxExample.xml");
#endif

            return resultString;
        }

    }

    #region --- Records  ---

    /// <summary>
    /// Record for one Ferda Data Miner box.
    /// </summary>
    public class Rec_ferda_box
    {
        #region DATA

        /// <summary>
        /// ID of box
        /// </summary>
        public string id = "";

        /// <summary>
        /// Type of box
        /// </summary>
        public string box_type = "unknown";

        /// <summary>
        /// User label of box
        /// </summary>
        public string user_name = "unknown";

        /// <summary>
        /// User hint to box
        /// </summary>
        public string user_hint = "unknown";

        #endregion

        #region METHODS

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <returns>XML string</returns>
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

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <param name="properties">list of records with Ferda boxes</param>
        /// <returns>XML string</returns>
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

    /// <summary>
    /// Record for one property of Ferda box.
    /// </summary>
    public class Rec_febox_property
    {
        #region DATA

        /// <summary>
        /// Name of property
        /// </summary>
        public string name = "unknown";

        /// <summary>
        /// Value of property
        /// </summary>
        public string value = "unknown";

        #endregion

        #region METHODS

        /// <summary>
        /// Creating XML string from record.
        /// </summary>
        /// <returns>XML string</returns>
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