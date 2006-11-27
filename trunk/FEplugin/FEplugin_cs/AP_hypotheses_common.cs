using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;
using System.Windows.Forms;
using Ferda;
using Ferda.ProjectManager;
using Ferda.ModulesManager;
using Ferda.Modules;
using Ferda.Modules.Helpers;
using Ferda.Modules.Quantifiers;

// This module contains definitions of all records used in all active elements wih type "hypothese" (4FT, SD4FT, KL, SDKL, CF, SDCF)

namespace FEplugin_cs
{
    
    /// <summary>
    /// Record used for one partial boolean cedent.
    /// </summary>
    public class Rec_ti_cedent
    {
        /// <summary>
        /// ID of ti_cedent
        /// </summary>
        public string id = "";

        /// <summary>
        /// Type of cedent (Antecedent, Succedent, Condition, First set, Second set)
        /// </summary>
        public string type = "";

        /// <summary>
        /// Creates a XML string from cedent, which doesn't contain any literals.
        /// </summary>
        /// <returns>XML string with cedent</returns>
        public string ToXML()
        {
            id = XMLHelper.replaceXMLsign(id);
            type = XMLHelper.replaceXMLsign(type);

            string XML = "";
            XML += "<ti_cedent id=\"" + id + "\" type=\"" + type + "\"/>";
            return XML;
        }

        /// <summary>
        /// Creates a XML string from cedent, which contains some literals.
        /// </summary>
        /// <param name="Literals">List of literals.</param>
        /// <returns>XML string with cedent</returns>
        public string ToXML(List<Rec_ti_literal> Literals)
        {
            // gets list of literals, generates all as subelements
            id = XMLHelper.replaceXMLsign(id);
            type = XMLHelper.replaceXMLsign(type);

            string XML = "";
            XML += "<ti_cedent id=\"" + id + "\" type=\"" + type + "\">";
            // generating of all the literals
            foreach (Rec_ti_literal L in Literals)
                XML += L.ToXML();
            XML += "</ti_cedent>";
            return XML;
        }

    }

    /// <summary>
    /// Record used for one literal.
    /// </summary>
    public class Rec_ti_literal
    {
        /// <summary>
        /// ID of ti_literal
        /// </summary>
        public string id = "";

        /// <summary>
        /// Name of attribute (used in hypothese)
        /// </summary>
        public string quant = "";

        /// <summary>
        /// Value of coefficient of literal
        /// </summary>
        public string value = "";

        /// <summary>
        /// Creates a XML string from literal.
        /// </summary>
        /// <returns>XML string with literal</returns>
        public string ToXML()
        {
            // replacing of signs "<", ">" in strings
            value = XMLHelper.replaceXMLsign(value);
            quant = XMLHelper.replaceXMLsign(quant);
            string XML = "";
            XML += "<ti_literal id=\"" + id + "\" quant=\"" + quant + "\" value=\"" + value + "\"/>";
            return XML;
        }
    }

    /// <summary>
    /// Recor used for one categorial cedent. (Attribute (CF hypotheses), Row attribute, Column attribute (KL hypotheses))
    /// </summary>
    public class Rec_ti_attribute
    {
        /// <summary>
        /// ID of ti_attribute
        /// </summary>
        public string id = "";

        /// <summary>
        /// Attribute name (used in hypothesis)
        /// </summary>
        public string quant = "";

        /// <summary>
        /// Type of cedent (Row attribute, Column attribute, Attribute)
        /// </summary>
        public string type = "";

        /// <summary>
        /// Creates a XML string from cedent, which doesn't contain any categories
        /// </summary>
        /// <returns>XML string with cedent</returns>
        public string ToXML()
        {
            id = XMLHelper.replaceXMLsign(id);
            quant = XMLHelper.replaceXMLsign(quant);
            type = XMLHelper.replaceXMLsign(type);

            string XML = "";
            XML += "<ti_attribute id=\"" + id + "\" quant=\"" + quant + "\" type=\"" + type + "\"/>";
            return XML;
        }


        /// <summary>
        /// Creates a XML string from cedent, which contains some categories
        /// </summary>
        /// <returns>XML string with cedent</returns>
        public string ToXML(List<Rec_ti_category> Categories)
        {
            // gets the list of categories, generates them all like subelements
            id = XMLHelper.replaceXMLsign(id);
            quant = XMLHelper.replaceXMLsign(quant);
            type = XMLHelper.replaceXMLsign(type);

            string XML = "";
            XML += "<ti_attribute id=\"" + id + "\" quant=\"" + quant + "\" type=\"" + type + "\">";
            // generating of all categories
            foreach (Rec_ti_category C in Categories)
                XML += C.ToXML();
            XML += "</ti_attribute>";
            return XML;
        }

    }

    /// <summary>
    /// Record used for one category of categorial cedent.
    /// </summary>
    public class Rec_ti_category
    {
        /// <summary>
        /// Value of category
        /// </summary>
        public string value = "";

        /// <summary>
        /// Creates a XML string from one category
        /// </summary>
        /// <returns>XML string with category</returns>
        public string ToXML()
        {
            // replacing the "<", ">" signs in strings
            value = XMLHelper.replaceXMLsign(value);
            string XML = "";
            XML += "<ti_category value=\"" + value + "\"/>";
            return XML;
        }
    }
}