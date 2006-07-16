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
//using Ferda.FrontEnd;

namespace FEplugin_cs
{
    // Definice recordu pouzivanych ve vsech typech AP hypoteza

    public class Rec_ti_cedent
    {
        public string id = "";    // ID ti_cedentu
        public string type = "";  // typ cetentu (Antecedent, Succedent, Condition)

        public string ToXML()
        {
            // neobsahuje zadne literaly (podelementy)
            id = XMLHelper.replaceXMLsign(id);
            type = XMLHelper.replaceXMLsign(type);

            string XML = "";
            XML += "<ti_cedent id=\"" + id + "\" type=\"" + type + "\"/>";
            return XML;
        }
        public string ToXML(List<Rec_ti_literal> Literals)
        {
            // dostane pole literalu, vygeneruje vsechny jako podelementy
            id = XMLHelper.replaceXMLsign(id);
            type = XMLHelper.replaceXMLsign(type);

            string XML = "";
            XML += "<ti_cedent id=\"" + id + "\" type=\"" + type + "\">";
            // vygenerovani vsech literalu
            foreach (Rec_ti_literal L in Literals)
                XML += L.ToXML();
            XML += "</ti_cedent>";
            return XML;
        }

    }

    public class Rec_ti_literal
    {
        public string id = "";    // ID ti_literalu
        public string quant = "";  // jmeno vlastnosti pouzite v hypoteze (napr. "Diastolicky tlak")
        public string value = "";  // hodnota vlastnosti (napr. "<50;60)")


        public string ToXML()
        {
            // nahrazeni znaku "<", ">" v retezcich (kvuli XML)
            value = XMLHelper.replaceXMLsign(value);
            quant = XMLHelper.replaceXMLsign(quant);
            string XML = "";
            XML += "<ti_literal id=\"" + id + "\" quant=\"" + quant + "\" value=\"" + value + "\"/>";
            return XML;
        }
    }

    public class Rec_ti_attribute
    {
        public string id = "";    // ID ti_cedentu
        public string quant = "";  // jmeno vlastnosti pouzite v hypoteze (napr. "Diastolicky tlak")
        public string type = "";  // typ cetentu (Row attribute, Column attribute, Attribute)

        public string ToXML()
        {
            // neobsahuje zadne literaly (podelementy)
            id = XMLHelper.replaceXMLsign(id);
            quant = XMLHelper.replaceXMLsign(quant);
            type = XMLHelper.replaceXMLsign(type);

            string XML = "";
            XML += "<ti_attribute id=\"" + id + "\" quant=\"" + quant + "\" type=\"" + type + "\"/>";
            return XML;
        }
        public string ToXML(List<Rec_ti_category> Categories)
        {
            // dostane pole kategorii, vygeneruje vsechny jako podelementy
            id = XMLHelper.replaceXMLsign(id);
            quant = XMLHelper.replaceXMLsign(quant);
            type = XMLHelper.replaceXMLsign(type);

            string XML = "";
            XML += "<ti_attribute id=\"" + id + "\" quant=\"" + quant + "\" type=\"" + type + "\">";
            // vygenerovani vsech literalu
            foreach (Rec_ti_category C in Categories)
                XML += C.ToXML();
            XML += "</ti_attribute>";
            return XML;
        }

    }

    public class Rec_ti_category
    {
        public string value = "";  // hodnota kategorie (napr. "<50;60)")


        public string ToXML()
        {
            // nahrazeni znaku "<", ">" v retezcich (kvuli XML)
            value = XMLHelper.replaceXMLsign(value);
            string XML = "";
            XML += "<ti_category value=\"" + value + "\"/>";
            return XML;
        }
    }
}