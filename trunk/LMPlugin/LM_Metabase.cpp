//LM_Metabase.cpp
//functions and classes for LM Metabase socket
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova, Milan Simunek

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

LM Report Asistent is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with LM Report Asistent; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "LM_Metabase.h"
#include "comdef.h"
#include "math.h"
#include "Faktorial.h"

CString format_cedent (TLitArray & cedent)
{
	int i;
	int cnt;
	CString xml_string = "";
	CString first;
	CString last;
	for (i = 0; i < cedent.GetSize (); i++) 
	{ 
		if ((i == 0) || (cedent.GetAt (i).quant != cedent.GetAt (i - 1).quant)) 
		{ 
			xml_string = xml_string + "<ti_literal  id=\"" + cedent.GetAt (i).id + 
				"\"  quant=\"" + cedent.GetAt (i).quant + 
				"\"  value=\""; 
			cnt = 0; 
			if (cedent.GetAt (i).coef_type == "int"
				||
				cedent.GetAt (i).coef_type == "cut"
				||
				cedent.GetAt (i).coef_type == "lcut"
				||
				cedent.GetAt (i).coef_type == "rcut"
				||
				cedent.GetAt (i).coef_type == "intc") 
			{ 
				first = cedent.GetAt (i).value; 
				last = first; 
			} 
		} 
				
		cnt++; 
		if (cedent.GetAt (i).coef_type == "int"
			||
			cedent.GetAt (i).coef_type == "cut"
			||
			cedent.GetAt (i).coef_type == "lcut"
			||
			cedent.GetAt (i).coef_type == "rcut"
			||
			cedent.GetAt (i).coef_type == "intc") 
		{ 
			last = cedent.GetAt (i).value; 
		} 
		else if (	cedent.GetAt (i).coef_type == "subset" 
					|| 
					cedent.GetAt (i).coef_type == "one"
					||
					cedent.GetAt (i).coef_type == "boolt"
					||
					cedent.GetAt (i).coef_type == "boolf"
					||
					cedent.GetAt (i).coef_type == "boola") 
			xml_string = xml_string + cedent.GetAt (i).value; 
		
		
		
		if ((i < cedent.GetSize () - 1) 
			&& 
			(cedent.GetAt (i).quant == cedent.GetAt (i + 1).quant))
		{ 
			if (	cedent.GetAt (i).coef_type == "subset" 
					|| 
					cedent.GetAt (i).coef_type == "one"
					||
					cedent.GetAt (i).coef_type == "boolt"
					||
					cedent.GetAt (i).coef_type == "boolf"
					||
					cedent.GetAt (i).coef_type == "boola") 
				xml_string += ", "; 
		} 
		else 
		{ 
			if (cedent.GetAt (i).coef_type == "int"
				||
				cedent.GetAt (i).coef_type == "cut"
				||
				cedent.GetAt (i).coef_type == "lcut"
				||
				cedent.GetAt (i).coef_type == "rcut"
				||
				cedent.GetAt (i).coef_type == "intc") 
			{ 
				if (cnt == 1) xml_string += first; 
				else if (cnt == 2) xml_string = xml_string + first + ", " + last; 
				else xml_string = xml_string + first + ".." + last; 
			} 
			xml_string += "\"/> ";
		}
	}
	return xml_string;
}

CString Hyp_CF_Meta::xml_convert ()
{
	CString xml_string;
	CString hlp;

	db_name.Replace ("&", "&amp;");
	matrix_name.Replace ("&", "&amp;");
	task_name.Replace ("&", "&amp;");
	quant.Replace ("&", "&amp;");

	db_name.Replace ("<", "&lt;");
	matrix_name.Replace ("<", "&lt;");
	task_name.Replace ("<", "&lt;");
	quant.Replace ("<", "&lt;");

	db_name.Replace (">", "&gt;");
	matrix_name.Replace (">", "&gt;");
	task_name.Replace (">", "&gt;");
	quant.Replace (">", "&gt;");

	//beginning of the hyp_cf element
	xml_string = " <hyp_cf id=\"" + id + "\" db_name=\"" + db_name + "\" ";
	xml_string = xml_string + "matrix_name=\"" + matrix_name + "\" ";
	xml_string = xml_string + "task_name=\"" + task_name + "\" ";
	
	xml_string = xml_string + " sum=\"" + sum + "\" ";
	xml_string = xml_string + " min=\"" + min + "\" ";
	xml_string = xml_string + " max=\"" + max + "\" ";
	xml_string = xml_string + " v=\"" + v + "\" ";
	xml_string = xml_string + " nom_var=\"" + nom_var + "\" ";
	xml_string = xml_string + " dor_var=\"" + dor_var + "\" ";
	xml_string = xml_string + " avg_a=\"" + avg_a + "\" ";
	xml_string = xml_string + " avg_g=\"" + avg_g + "\" ";
	xml_string = xml_string + " var=\"" + var + "\" ";
	xml_string = xml_string + " st_dev=\"" + st_dev + "\" ";
	xml_string = xml_string + " skew=\"" + skew + "\" ";
	xml_string = xml_string + " asym=\"" + asym + "\" ";
	
	xml_string = xml_string + " attributes=\"" + a_id + "\" ";
	xml_string = xml_string + " condition=\"" + c_id + "\">";

	xml_string = xml_string + " <r> ";
	int i;
	for (i = 0; i < frequencies.GetSize (); i++)
	{
		hlp.Format ("%d", frequencies.GetAt (i));
		xml_string = xml_string + " <c val=\"" + hlp + "\"/> ";
	}

	xml_string = xml_string + " </r> ";

	xml_string += " </hyp_cf>  ";
	//end of hyp_cf element

	xml_string = xml_string + " <ti_attribute id=\"" +
		a_id + "\" quant=\"" + quant + "\" type=\"Attributes\"> ";
	for (i = 0; i < attributes.GetSize (); i++)
	{
		xml_string = xml_string + " <ti_category value=\""
			+ attributes.GetAt (i) + "\"/> ";
	}
	xml_string = xml_string + " </ti_attribute> ";

	xml_string = xml_string + "<ti_cedent  id=\"" + c_id + "\"  type=\"Condition\"> ";
    xml_string += format_cedent (condition);
	xml_string = xml_string + "</ti_cedent> ";

	return xml_string;
}

int Hyp_CF_Meta::get_sum ()
{
	int s = 0;
	int i;

	for (i = 0; i < frequencies.GetSize (); i++) s += frequencies.GetAt (i);

	return s;
}

int Hyp_CF_Meta::get_max ()
{
	int m = frequencies.GetAt (0);
	int i;
	for (i = 1; i < frequencies.GetSize (); i++)
		if (frequencies.GetAt (i) > m) m = frequencies.GetAt (i);

	return m;
}

CString Hyp_CF_Meta::get_min ()
{
	int m = frequencies.GetAt (0);
	int i;
	CString hlp;

	for (i = 1; i < frequencies.GetSize (); i++)
		if (frequencies.GetAt (i) < m) m = frequencies.GetAt (i);

	hlp.Format ("%d", m);
	return hlp;
}

double Hyp_CF_Meta::GetVariationRatio ()
{
	double dSum= get_sum ();
	if ( dSum == 0.0) return 0.0;

	double dMax= get_max ();
	return 1 - dMax/dSum;
}

CString Hyp_CF_Meta::get_nom_var ()
{
	int j;
	if (frequencies.GetSize () <= 1) return (LPCTSTR) (_bstr_t) (0.0);

	double dSum= get_sum ();
	if ( dSum == 0.0) return (LPCTSTR) (_bstr_t) (0.0);

	double dNomVar= 0;
	for (j= 0; j < frequencies.GetSize (); j++)
	{
		int nValue= frequencies.GetAt (j);
		double dFi= nValue / dSum;

		dNomVar+= dFi * dFi;
	}
	dNomVar= 1 - dNomVar;

	return
		(LPCTSTR) (_bstr_t) ((frequencies.GetSize () * dNomVar) / (frequencies.GetSize () - 1));
}

CString Hyp_CF_Meta::get_dor_var ()
{
	if ( frequencies.GetSize () <= 1) return (LPCTSTR) (_bstr_t) (0.0);

	double dSum= get_sum ();
	if ( dSum == 0.0) return (LPCTSTR) (_bstr_t) (0.0);

	double dDorVar= 0;
	double dSumF= 0;
	for (int j= 0; j < frequencies.GetSize (); j++)
	{
		int nValue= frequencies.GetAt (j);
		double dFi= nValue / dSum;

		dSumF+= dFi;

		dDorVar+= dSumF * (1 - dSumF);
	}
	dDorVar= 2 * dDorVar;

	return (LPCTSTR) (_bstr_t) ((2 * dDorVar) / ( frequencies.GetSize ()- 1));
}

CString Quantifier_Meta::xml_convert ()
{
	CString xml_string;

	db_name.Replace ("&", "&amp;");
	matrix_name.Replace ("&", "&amp;");
	task_name.Replace ("&", "&amp;");
	task_type.Replace ("&", "&amp;");
	name.Replace ("&", "&amp;");
	type.Replace ("&", "&amp;");
	
	db_name.Replace ("<", "&lt;");
	matrix_name.Replace ("<", "&lt;");
	task_name.Replace ("<", "&lt;");
	task_type.Replace ("<", "&lt;");
	name.Replace ("<", "&lt;");
	type.Replace ("<", "&lt;");

	db_name.Replace (">", "&gt;");
	matrix_name.Replace (">", "&gt;");
	task_name.Replace (">", "&gt;");
	task_type.Replace (">", "&gt;");
	name.Replace (">", "&gt;");
	type.Replace (">", "&gt;");

	//beggining of the task element
	xml_string = " <quantifier id=\"" + id + "\" db_name=\"" + db_name + "\" ";
	xml_string = xml_string + "matrix_name=\"" + matrix_name + "\" ";
	xml_string = xml_string + "task_name=\"" + task_name + "\" ";
	xml_string = xml_string + "task_type=\"" + task_type + "\" ";
	xml_string = xml_string + "name=\"" + name + "\" ";
	xml_string = xml_string + "type=\"" + type + "\"> ";
    for (int i = 0; i < items.GetSize (); i++)
		xml_string = xml_string + "<quant_item name=\"" + items.GetAt (i).name +
			"\" value=\"" + items.GetAt (i).value + "\" /> ";
	xml_string = xml_string + "</quantifier>";

	return xml_string;
}

CString Task_Meta::xml_convert ()
{
	CString xml_string;

	db_name.Replace ("&", "&amp;");
	matrix_name.Replace ("&", "&amp;");
	task_name.Replace ("&", "&amp;");
	task_type.Replace ("&", "&amp;");
	gen_state.Replace ("&", "&amp;");
	gen_total_time.Replace ("&", "&amp;");
	gen_start_time.Replace ("&", "&amp;");
	
	db_name.Replace ("<", "&lt;");
	matrix_name.Replace ("<", "&lt;");
	task_name.Replace ("<", "&lt;");
	task_type.Replace ("<", "&lt;");
	gen_state.Replace ("<", "&lt;");
	gen_total_time.Replace ("<", "&lt;");
	gen_start_time.Replace ("<", "&lt;");

	db_name.Replace (">", "&gt;");
	matrix_name.Replace (">", "&gt;");
	task_name.Replace (">", "&gt;");
	task_type.Replace (">", "&gt;");
	gen_state.Replace (">", "&gt;");
	gen_total_time.Replace (">", "&gt;");
	gen_start_time.Replace (">", "&gt;");

	//beggining of the task element
	xml_string = " <task id=\"" + id + "\" db_name=\"" + db_name + "\" ";
	xml_string = xml_string + "matrix_name=\"" + matrix_name + "\" ";
	xml_string = xml_string + "task_name=\"" + task_name + "\" ";
	xml_string = xml_string + "task_type=\"" + task_type + "\" ";
	xml_string = xml_string + "gen_state=\"" + gen_state + "\" ";
	xml_string = xml_string + "gen_total_time=\"" + gen_total_time + "\" ";
	xml_string = xml_string + "gen_start_time=\"" + gen_start_time + "\" ";
	xml_string = xml_string + "num_hyp=\"" + num_hyp + "\" ";
	xml_string = xml_string + "num_tests=\"" + num_tests + "\"/>";

	return xml_string;
}

CString KL_Cedent_Meta::xml_convert ()
{
	CString xml_string;

	cedent_type.Replace ("&", "&amp;");
	db_name.Replace ("&", "&amp;");
	matrix_name.Replace ("&", "&amp;");
	task_name.Replace ("&", "&amp;");
	task_type.Replace ("&", "&amp;");

	cedent_type.Replace ("<", "&lt;");
	db_name.Replace ("<", "&lt;");
	matrix_name.Replace ("<", "&lt;");
	task_name.Replace ("<", "&lt;");
	task_type.Replace ("<", "&lt;");

	cedent_type.Replace (">", "&gt;");
	db_name.Replace (">", "&gt;");
	matrix_name.Replace (">", "&gt;");
	task_name.Replace (">", "&gt;");
	task_type.Replace (">", "&gt;");

	//beggining of the cedent element
	xml_string = " <KL_cedent id=\"" + id + "\" db_name=\"" + db_name + "\" ";
	xml_string = xml_string + "matrix_name=\"" + matrix_name + "\" ";
	xml_string = xml_string + "task_name=\"" + task_name + "\" ";
	xml_string = xml_string + "task_type=\"" + task_type + "\" ";
	xml_string = xml_string + "cedent_type=\"" + cedent_type + "\" ";
	xml_string = xml_string + "sub_cedent_cnt=\"" + sub_cedent_cnt + "\" >";
	for (int i = 0; i < sub_cedents_list.GetSize (); i++)
	{
		xml_string = xml_string +
			"<sub_KL_cedent name=\"" + sub_cedents_list.GetAt (i)->name + "\" ";
		xml_string = xml_string +
			"literal_cnt=\"" + sub_cedents_list.GetAt (i)->literal_cnt + "\" ";
		xml_string = xml_string +
			"length=\"" + sub_cedents_list.GetAt (i)->length + "\" >";
		for (int j = 0; j < sub_cedents_list.GetAt (i)->lit_list.GetSize (); j++)
		{
			xml_string = xml_string +
				"<KL_literal underlying_attribute=\"" +
				sub_cedents_list.GetAt (i)->lit_list.GetAt (j).underlying_attribute + "\" ";
			xml_string = xml_string +
				"category_cnt=\"" +
				sub_cedents_list.GetAt (i)->lit_list.GetAt (j).category_cnt + "\"/> ";
		}
		xml_string = xml_string + "</sub_KL_cedent> ";
	}
	xml_string = xml_string + "</KL_cedent> ";

	return xml_string;
}

CString CF_Cedent_Meta::xml_convert ()
{
	CString xml_string;

	cedent_type.Replace ("&", "&amp;");
	db_name.Replace ("&", "&amp;");
	matrix_name.Replace ("&", "&amp;");
	task_name.Replace ("&", "&amp;");
	task_type.Replace ("&", "&amp;");

	cedent_type.Replace ("<", "&lt;");
	db_name.Replace ("<", "&lt;");
	matrix_name.Replace ("<", "&lt;");
	task_name.Replace ("<", "&lt;");
	task_type.Replace ("<", "&lt;");

	cedent_type.Replace (">", "&gt;");
	db_name.Replace (">", "&gt;");
	matrix_name.Replace (">", "&gt;");
	task_name.Replace (">", "&gt;");
	task_type.Replace (">", "&gt;");

	//beggining of the cedent element
	xml_string = " <CF_cedent id=\"" + id + "\" db_name=\"" + db_name + "\" ";
	xml_string = xml_string + "matrix_name=\"" + matrix_name + "\" ";
	xml_string = xml_string + "task_name=\"" + task_name + "\" ";
	xml_string = xml_string + "task_type=\"" + task_type + "\" ";
	xml_string = xml_string + "cedent_type=\"" + cedent_type + "\" ";
	xml_string = xml_string + "sub_cedent_cnt=\"" + sub_cedent_cnt + "\" >";
	for (int i = 0; i < sub_cedents_list.GetSize (); i++)
	{
		xml_string = xml_string +
			"<sub_CF_cedent name=\"" + sub_cedents_list.GetAt (i)->name + "\" ";
		xml_string = xml_string +
			"literal_cnt=\"" + sub_cedents_list.GetAt (i)->literal_cnt + "\" ";
		xml_string = xml_string +
			"length=\"" + sub_cedents_list.GetAt (i)->length + "\" >";
		for (int j = 0; j < sub_cedents_list.GetAt (i)->lit_list.GetSize (); j++)
		{
			xml_string = xml_string +
				"<CF_literal underlying_attribute=\"" +
				sub_cedents_list.GetAt (i)->lit_list.GetAt (j).underlying_attribute + "\" ";
			xml_string = xml_string +
				"category_cnt=\"" +
				sub_cedents_list.GetAt (i)->lit_list.GetAt (j).category_cnt + "\"/> ";
		}
		xml_string = xml_string + "</sub_CF_cedent> ";
	}
	xml_string = xml_string + "</CF_cedent> ";

	return xml_string;
}

CString Bool_Cedent_Meta::xml_convert ()
{
	CString xml_string;

	cedent_type.Replace ("&", "&amp;");
	db_name.Replace ("&", "&amp;");
	matrix_name.Replace ("&", "&amp;");
	task_name.Replace ("&", "&amp;");
	task_type.Replace ("&", "&amp;");

	cedent_type.Replace ("<", "&lt;");
	db_name.Replace ("<", "&lt;");
	matrix_name.Replace ("<", "&lt;");
	task_name.Replace ("<", "&lt;");
	task_type.Replace ("<", "&lt;");

	cedent_type.Replace (">", "&gt;");
	db_name.Replace (">", "&gt;");
	matrix_name.Replace (">", "&gt;");
	task_name.Replace (">", "&gt;");
	task_type.Replace (">", "&gt;");

	//beggining of the cedent element
	xml_string = " <bool_cedent id=\"" + id + "\" db_name=\"" + db_name + "\" ";
	xml_string = xml_string + "matrix_name=\"" + matrix_name + "\" ";
	xml_string = xml_string + "task_name=\"" + task_name + "\" ";
	xml_string = xml_string + "task_type=\"" + task_type + "\" ";
	xml_string = xml_string + "cedent_type=\"" + cedent_type + "\" ";
	xml_string = xml_string + "name=\"" + name + "\" ";
	xml_string = xml_string + "literal_cnt=\"" + literal_cnt + "\" ";
	xml_string = xml_string + "length=\"" + length + "\" >";
	for (int j = 0; j < lit_list.GetSize (); j++)
	{
		xml_string = xml_string +
			"<literal underlying_attribute=\"" +
			lit_list.GetAt (j).underlying_attribute + "\" ";
		xml_string = xml_string +
			"category_cnt=\"" +
			lit_list.GetAt (j).category_cnt + "\" ";
		xml_string = xml_string +
			"missing_type=\"" +
			lit_list.GetAt (j).missing_type + "\" ";
		xml_string = xml_string +
			"coefficient_type=\"" +
			lit_list.GetAt (j).coefficient_type + "\" ";
		xml_string = xml_string +
			"length=\"" +
			lit_list.GetAt (j).length + "\" ";
		xml_string = xml_string +
			"gace=\"" +
			lit_list.GetAt (j).gace + "\" ";
		xml_string = xml_string +
			"literal_type=\"" +
			lit_list.GetAt (j).literal_type + "\" ";
		xml_string = xml_string +
			"equivalence_class=\"" +
			lit_list.GetAt (j).equivalence_class + "\"/> ";
	}
xml_string = xml_string + "</bool_cedent> ";

return xml_string;
}

CString Attribute_Meta::xml_convert ()
{
	CString xml_string;

	attr_name.Replace ("&", "&amp;");
	db_name.Replace ("&", "&amp;");
	id.Replace ("&", "&amp;");
	matrix_name.Replace ("&", "&amp;");
	creation.Replace ("&", "&amp;");

	attr_name.Replace ("<", "&lt;");
	db_name.Replace ("<", "&lt;");
	id.Replace ("<", "&lt;");
	matrix_name.Replace ("<", "&lt;");
	creation.Replace ("<", "&lt;");

	attr_name.Replace (">", "&gt;");
	db_name.Replace (">", "&gt;");
	id.Replace (">", "&gt;");
	matrix_name.Replace (">", "&gt;");
	creation.Replace (">", "&gt;");

	//beginning of the attribute element
	xml_string = " <attribute id=\"" + id + "\" db_name=\"" + db_name + "\" ";
	xml_string = xml_string + "matrix_name=\"" + matrix_name + "\" ";
	xml_string = xml_string + "attr_name=\"" + attr_name + "\" ";
	xml_string = xml_string + "creation=\"" + creation + "\" ";
	xml_string = xml_string + "ctgr_count=\"" + ctgr_count + "\"> ";
	int i;
    for (i = 0; i < category_list.GetSize (); i++)
		xml_string = xml_string + "<ctgr name=\"" + category_list.GetAt (i).name +
			"\" freq=\"" + category_list.GetAt (i).freq + "\" /> ";
	for (i = 0; i < missing_type_list.GetSize (); i++)
		xml_string = xml_string + "<missing_value name=\"" + missing_type_list.GetAt (i) +
			"\" /> ";
	xml_string = xml_string + "</attribute>";

	return xml_string;
}

CString Category_Meta::xml_convert ()
{
	CString xml_string;
	CString hlp;

	attr_name.Replace ("&", "&amp;");
	ctgr_bool_type.Replace ("&", "&amp;");
	ctgr_freq.Replace ("&", "&amp;");
	ctgr_name.Replace ("&", "&amp;");
	ctgr_type.Replace ("&", "&amp;");
	db_name.Replace ("&", "&amp;");
	id.Replace ("&", "&amp;");
	matrix_name.Replace ("&", "&amp;");
	
	attr_name.Replace ("<", "&lt;");
	ctgr_bool_type.Replace ("<", "&lt;");
	ctgr_freq.Replace ("<", "&lt;");
	ctgr_name.Replace ("<", "&lt;");
	ctgr_type.Replace ("<", "&lt;");
	db_name.Replace ("<", "&lt;");
	id.Replace ("<", "&lt;");
	matrix_name.Replace ("<", "&lt;");
	
	attr_name.Replace (">", "&gt;");
	ctgr_bool_type.Replace (">", "&gt;");
	ctgr_freq.Replace (">", "&gt;");
	ctgr_name.Replace (">", "&gt;");
	ctgr_type.Replace (">", "&gt;");
	db_name.Replace (">", "&gt;");
	id.Replace (">", "&gt;");
	matrix_name.Replace (">", "&gt;");
	
	//beginning of category element
	xml_string = " <category id=\"" + id + "\" db_name=\"" + db_name + "\" ";
	xml_string = xml_string + "matrix_name=\"" + matrix_name + "\" ";
	xml_string = xml_string + "attr_name=\"" + attr_name + "\" ";
	xml_string = xml_string + "ctgr_name=\"" + ctgr_name + "\" ";
	xml_string = xml_string + "ctgr_type=\"" + ctgr_type + "\" ";
	xml_string = xml_string + "ctgr_freq=\"" + ctgr_freq + "\" ";
	xml_string = xml_string + "bool_type=\"" + ctgr_bool_type + "\" ";
	hlp.Format ("%d", def_length);
	xml_string = xml_string + "def_length=\"" + hlp + "\"> ";
	for (int i = 0; i < ctgr_def.GetSize (); i++)
		xml_string = xml_string + "<ctgr_def definition=\"" + ctgr_def.GetAt (i) + "\" /> ";
	xml_string = xml_string + "</category>";
	return xml_string;
}

CString Hyp_4ft_Meta::xml_convert (bool ar2nl)
{
	CString xml_string;
	CString hlp;

	if (ar2nl)
	{
		ar2nl_sentences.Replace ("<sentences>", "_xRePAssi_x1");
		ar2nl_sentences.Replace ("</sentences>", "_xRePAssi_x2");
		ar2nl_sentences.Replace ("<sentence>", "_xRePAssi_x3");
		ar2nl_sentences.Replace ("</sentence>", "_xRePAssi_x4");
		ar2nl_sentences.Replace ("<sentence/>", "_xRePAssi_x5");
		ar2nl_sentences.Replace ("<sentences/>", "_xRePAssi_x6");
	}

	db_name.Replace ("&", "&amp;");
	matrix_name.Replace ("&", "&amp;");
	task_name.Replace ("&", "&amp;");
	ar2nl_sentences.Replace ("&", "&amp;");

	db_name.Replace ("<", "&lt;");
	matrix_name.Replace ("<", "&lt;");
	task_name.Replace ("<", "&lt;");
	ar2nl_sentences.Replace ("<", "&lt;");

	db_name.Replace (">", "&gt;");
	matrix_name.Replace (">", "&gt;");
	task_name.Replace (">", "&gt;");
	ar2nl_sentences.Replace (">", "&gt;");
	
	if (ar2nl)
	{
		ar2nl_sentences.Replace ("_xRePAssi_x1", "<sentences>");
		ar2nl_sentences.Replace ("_xRePAssi_x2", "</sentences>");
		ar2nl_sentences.Replace ("_xRePAssi_x3", "<sentence>");
		ar2nl_sentences.Replace ("_xRePAssi_x4", "</sentence>");
		ar2nl_sentences.Replace ("_xRePAssi_x5", "<sentence/>");
		ar2nl_sentences.Replace ("_xRePAssi_x6", "<sentences/>");
	}

	//beginning of the hyp_4ft element
	if (!ar2nl) xml_string = " <hyp_4ft id=\"" + id + "\" db_name=\"" + db_name + "\" ";
	else xml_string = " <hyp_4ft_ar2nl id=\"" + id + "\" db_name=\"" + db_name + "\" ";
	xml_string = xml_string + "matrix_name=\"" + matrix_name + "\" ";
	xml_string = xml_string + "task_name=\"" + task_name + "\" ";
	xml_string = xml_string + "a=\"";
	hlp.Format ("%d", a);
	xml_string = xml_string + hlp + "\" ";
	xml_string = xml_string + " b=\"";
	hlp.Format ("%d", b);
	xml_string = xml_string + hlp + "\" ";
	xml_string = xml_string + " c=\"";
	hlp.Format ("%d", c);
	xml_string = xml_string + hlp + "\" ";
	xml_string = xml_string + " d=\"";
	hlp.Format ("%d", d);
	xml_string = xml_string + hlp + "\" ";
	xml_string = xml_string + " conf=\"" + (LPCTSTR) (_bstr_t) conf + "\" ";
	xml_string = xml_string + " d_conf=\"" + (LPCTSTR) (_bstr_t) d_conf + "\" ";
	xml_string = xml_string + " e_conf=\"" + (LPCTSTR) (_bstr_t) e_conf + "\" ";
	xml_string = xml_string + " support=\"" + (LPCTSTR) (_bstr_t) support + "\" ";
	xml_string = xml_string + " completeness=\"" + (LPCTSTR) (_bstr_t) completeness + "\" ";
	xml_string = xml_string + " avg_diff=\"" + (LPCTSTR) (_bstr_t) avg_diff + "\" ";
	xml_string = xml_string + " low_bnd_imp=\"" + low_bnd_imp + "\" ";
	xml_string = xml_string + " up_bnd_imp=\"" + up_bnd_imp + "\" ";
	xml_string = xml_string + " low_bnd_dbl_imp=\"" + low_bnd_dbl_imp + "\" ";
	xml_string = xml_string + " up_bnd_dbl_imp=\"" + up_bnd_dbl_imp + "\" ";
	xml_string = xml_string + " low_bnd_eq=\"" + low_bnd_eq + "\" ";
	xml_string = xml_string + " up_bnd_eq=\"" + up_bnd_eq + "\" ";
	xml_string = xml_string + " fisher=\"" + fisher + "\" ";
	xml_string = xml_string + " chi_sq=\"" + (LPCTSTR) (_bstr_t) chi_sq + "\" ";
	xml_string = xml_string + " antecedent=\"" + ant_id + "\" ";
	xml_string = xml_string + " succedent=\"" + suc_id + "\" ";
	xml_string = xml_string + " condition=\"" + con_id + "\"";
	if (ar2nl)
	{
		xml_string = xml_string + "> ";
		xml_string = xml_string + ar2nl_sentences + "</hyp_4ft_ar2nl> ";
	}
	else xml_string += "/>  ";
	//end of hyp_4ft element

	//beginning of ti_cedent elements
	//Antecedent
	xml_string = xml_string + "<ti_cedent  id=\"" + ant_id + "\"  type=\"Antecedent\"> ";
	xml_string += format_cedent (antecedent);
	xml_string = xml_string + "</ti_cedent> ";
	
	//Succedent
	xml_string = xml_string + "<ti_cedent  id=\"" + suc_id + "\"  type=\"Succedent\"> ";
    xml_string += format_cedent (succedent);
	xml_string = xml_string + "</ti_cedent> ";
	
	//Condition
	xml_string = xml_string + "<ti_cedent  id=\"" + con_id + "\"  type=\"Condition\"> ";
    xml_string += format_cedent (condition);
	xml_string = xml_string + "</ti_cedent> ";
		
	return xml_string;
}

double Hyp_4ft_Meta::get_chi_sq ()
{
	if ((a + c) * (b + d) * (a + b) * (c + d) == 0) return 0;

	double dDelta = a * d - b * c;

	return ((a + b + c + d) * dDelta * dDelta) / 
		   ((a + c) * (b + d) * (a + b) * (c + d));
}

CString Hyp_4ft_Meta::get_fisher ()
{

	if ( !gLnFaktTab.Init( a + b + c + d + 1)) return "Unknown";

	long r= a + b;
	long s= c + d;
	long k= a + c;
	long l= b + d;
	long n= r + s; //a + b + c + d

	double dValue= exp( gLnFaktTab.GetLnFakt( r)+ gLnFaktTab.GetLnFakt( s)+ 
				gLnFaktTab.GetLnFakt( k)+ gLnFaktTab.GetLnFakt( l)-
				gLnFaktTab.GetLnFakt( n)- gLnFaktTab.GetLnFakt( a)-
				gLnFaktTab.GetLnFakt( r- a)- gLnFaktTab.GetLnFakt( k- a)-
				gLnFaktTab.GetLnFakt( n- r- k+ a));

	long minRK= r < k ? r : k;	// min( r, k)

	double dSuma= dValue;		// sum of values
	long c1 = n- r- k;

	long i;

	for (i= a + 1; i <= minRK; i++)
	{
		double dDelta= ((double)( r- i+ 1)*( k- i+ 1))/ ( i* (c1+ i));
		if ( dDelta == 0) break;
		dValue= dValue* dDelta;
		dSuma+= dValue;
	}

	return (LPCTSTR) (_bstr_t) dSuma;
}

CString Hyp_4ft_Meta::get_low_bnd_imp ()
{
	if ( !gLnFaktTab.Init( a + b + 1)) return "Unknown";

	double const m_p = 0.9;
	double m_pLog = log( m_p);
	double m_1pLog = log( 1- m_p);

	long ab= a + b;

	double nSuma= 0.0;
	long i;

	for (i = a; i <= ab; i++)
	{
		nSuma += exp( gLnFaktTab.GetLnFakt(ab)- 
				( gLnFaktTab.GetLnFakt(i)+ gLnFaktTab.GetLnFakt(ab - i))+
				m_pLog*i+ m_1pLog*(ab - i));
	}

	return (LPCTSTR) (_bstr_t) nSuma;
}

CString Hyp_4ft_Meta::get_up_bnd_imp ()
{
	if ( !gLnFaktTab.Init( a + b + 1)) return "Unknown";

	double const m_p = 0.9;
	double m_pLog = log( m_p);
	double m_1pLog = log( 1- m_p);

	long r = a + b;

	double nSuma= 0.0;		// sum of values
	long i;

	for (i = 0; i <= a; i++)
	{
		nSuma += exp( gLnFaktTab.GetLnFakt( r)- 
				(gLnFaktTab.GetLnFakt( i)+ gLnFaktTab.GetLnFakt( r- i))+
				m_pLog*i+ m_1pLog*( r- i));
	}

	return (LPCTSTR) (_bstr_t) nSuma;
}

CString Hyp_4ft_Meta::get_low_bnd_dbl_imp ()
{
	if ( !gLnFaktTab.Init( a + b + c + 1)) return "Unknown";

	double const m_p = 0.9;
	double m_pLog = log( m_p);
	double m_1pLog = log( 1- m_p);

	long abc = a + b + c;

	double nSuma= 0.0;
	long i;

	for (i = a; i <= abc; i++)
	{
		nSuma += exp( gLnFaktTab.GetLnFakt( abc) - 
				( gLnFaktTab.GetLnFakt( i) + gLnFaktTab.GetLnFakt( abc- i))+
				m_pLog*i+ m_1pLog*( abc- i));
	}

	return (LPCTSTR) (_bstr_t) nSuma;
}

CString Hyp_4ft_Meta::get_up_bnd_dbl_imp ()
{
	if ( !gLnFaktTab.Init( a + b + c + 1)) return "Unknown";

	double const m_p = 0.9;
	double m_pLog = log( m_p);
	double m_1pLog = log( 1- m_p);

	long abc = a + b + c;

	double nSuma= 0.0;
	long i;

	for (i = 0; i <= a; i++)
	{
		nSuma += exp( gLnFaktTab.GetLnFakt( abc) - 
				( gLnFaktTab.GetLnFakt( i) + gLnFaktTab.GetLnFakt( abc- i))+
				m_pLog*i+ m_1pLog*( abc- i));
	}

	return (LPCTSTR) (_bstr_t) nSuma;
}

CString Hyp_4ft_Meta::get_low_bnd_eq ()
{
	if ( !gLnFaktTab.Init( a + b + c + d + 1)) return "Unknown";

	double const m_p = 0.9;
	double m_pLog= log( m_p);
	double m_1pLog= log( 1- m_p);

	long n = a + b + c + d;
	long ad= a + d;

	double nSuma= 0;
	long i;

	for (i= ad; i <= n; i++)
	{
		nSuma += exp( gLnFaktTab.GetLnFakt(n) - 
				 ( gLnFaktTab.GetLnFakt( i) + gLnFaktTab.GetLnFakt(n - i))+
				 m_pLog*i+ m_1pLog*(n - i));
	}

	return (LPCTSTR) (_bstr_t) nSuma;
}

CString Hyp_4ft_Meta::get_up_bnd_eq ()
{
	if ( !gLnFaktTab.Init( a + b + c + d + 1)) return "Unknown";

	double const m_p = 0.9;
	double m_pLog= log( m_p);
	double m_1pLog= log( 1- m_p);

	long n = a + b + c + d;
	long ad= a + d;

	double nSuma= 0;
	long i;

	for (i= 0; i <= ad; i++)
	{
		nSuma += exp( gLnFaktTab.GetLnFakt(n) - 
				( gLnFaktTab.GetLnFakt( i) + gLnFaktTab.GetLnFakt(n - i))+
				m_pLog*i+ m_1pLog*(n - i));
	}

	return (LPCTSTR) (_bstr_t) nSuma;
}

CString Hyp_SD4ft_Meta::xml_convert ()
{
	CString xml_string;
	CString first;
	CString last;

	db_name.Replace ("&", "&amp;");
	matrix_name.Replace ("&", "&amp;");
	task_name.Replace ("&", "&amp;");

	db_name.Replace ("<", "&lt;");
	matrix_name.Replace ("<", "&lt;");
	task_name.Replace ("<", "&lt;");

	db_name.Replace (">", "&gt;");
	matrix_name.Replace (">", "&gt;");
	task_name.Replace (">", "&gt;");

	//beginning of the hyp_sd4ft element
	xml_string = " <hyp_sd4ft id=\"" + id + "\" db_name=\"" + db_name + "\" ";
	xml_string = xml_string + "matrix_name=\"" + matrix_name + "\" ";
	xml_string = xml_string + "task_name=\"" + task_name + "\" ";
	xml_string = xml_string + "a=\"" + a + "\" ";
	xml_string = xml_string + "b=\"" + b + "\" ";
	xml_string = xml_string + "c=\"" + c + "\" ";
	xml_string = xml_string + "d=\"" + d + "\" ";
	xml_string = xml_string + "e=\"" + e + "\" ";
	xml_string = xml_string + "f=\"" + f + "\" ";
	xml_string = xml_string + "g=\"" + g + "\" ";
	xml_string = xml_string + "h=\"" + h + "\" ";
	
	xml_string = xml_string + " conf1=\"" + conf1 + "\" ";
	xml_string = xml_string + " d_conf1=\"" + d_conf1 + "\" ";
	xml_string = xml_string + " e_conf1=\"" + e_conf1 + "\" ";
	xml_string = xml_string + " support1=\"" + support1 + "\" ";
	xml_string = xml_string + " completeness1=\"" + completeness1 + "\" ";
	xml_string = xml_string + " avg_diff1=\"" + avg_diff1 + "\" ";
	xml_string = xml_string + " low_bnd_imp1=\"" + low_bnd_imp1 + "\" ";
	xml_string = xml_string + " up_bnd_imp1=\"" + up_bnd_imp1 + "\" ";
	xml_string = xml_string + " low_bnd_dbl_imp1=\"" + low_bnd_dbl_imp1 + "\" ";
	xml_string = xml_string + " up_bnd_dbl_imp1=\"" + up_bnd_dbl_imp1 + "\" ";
	xml_string = xml_string + " low_bnd_eq1=\"" + low_bnd_eq1 + "\" ";
	xml_string = xml_string + " up_bnd_eq1=\"" + up_bnd_eq1 + "\" ";
	xml_string = xml_string + " fisher1=\"" + fisher1 + "\" ";
	xml_string = xml_string + " chi_sq1=\"" + chi_sq1 + "\" ";

	xml_string = xml_string + " conf2=\"" + conf2 + "\" ";
	xml_string = xml_string + " d_conf2=\"" + d_conf2 + "\" ";
	xml_string = xml_string + " e_conf2=\"" + e_conf2 + "\" ";
	xml_string = xml_string + " support2=\"" + support2 + "\" ";
	xml_string = xml_string + " completeness2=\"" + completeness2 + "\" ";
	xml_string = xml_string + " avg_diff2=\"" + avg_diff2 + "\" ";
	xml_string = xml_string + " low_bnd_imp2=\"" + low_bnd_imp2 + "\" ";
	xml_string = xml_string + " up_bnd_imp2=\"" + up_bnd_imp2 + "\" ";
	xml_string = xml_string + " low_bnd_dbl_imp2=\"" + low_bnd_dbl_imp2 + "\" ";
	xml_string = xml_string + " up_bnd_dbl_imp2=\"" + up_bnd_dbl_imp2 + "\" ";
	xml_string = xml_string + " low_bnd_eq2=\"" + low_bnd_eq2 + "\" ";
	xml_string = xml_string + " up_bnd_eq2=\"" + up_bnd_eq2 + "\" ";
	xml_string = xml_string + " fisher2=\"" + fisher2 + "\" ";
	xml_string = xml_string + " chi_sq2=\"" + chi_sq2 + "\" ";

	xml_string = xml_string + " dr_sum=\"" + dr_sum + "\" ";
	xml_string = xml_string + " df_conf=\"" + df_conf + "\" ";
	xml_string = xml_string + " df_dfui=\"" + df_dfui + "\" ";
	xml_string = xml_string + " df_fue=\"" + df_fue + "\" ";
	xml_string = xml_string + " df_avg=\"" + df_avg + "\" ";

	xml_string = xml_string + " antecedent=\"" + ant_id + "\" ";
	xml_string = xml_string + " succedent=\"" + suc_id + "\" ";
	xml_string = xml_string + " condition=\"" + con_id + "\"";
	xml_string = xml_string + " set1=\"" + set1_id + "\" ";
	xml_string = xml_string + " set2=\"" + set2_id + "\"";
	xml_string += "/>  ";
	//end of hyp_sd4ft element

	//beginning of ti_cedent elements
	//Antecedent
	xml_string = xml_string + "<ti_cedent  id=\"" + ant_id + "\"  type=\"Antecedent\"> ";
	xml_string += format_cedent (antecedent);
	xml_string = xml_string + "</ti_cedent> ";
	
	//Succedent
	xml_string = xml_string + "<ti_cedent  id=\"" + suc_id + "\"  type=\"Succedent\"> ";
	xml_string += format_cedent (succedent);
	xml_string = xml_string + "</ti_cedent> ";

	//Condition
	xml_string = xml_string + "<ti_cedent  id=\"" + con_id + "\"  type=\"Condition\"> ";
	xml_string += format_cedent (condition);
	xml_string = xml_string + "</ti_cedent> ";

	//First set
	xml_string = xml_string + "<ti_cedent  id=\"" + set1_id + "\"  type=\"First set\"> ";
	xml_string += format_cedent (set1);
	xml_string = xml_string + "</ti_cedent> ";

	//Second set
	xml_string = xml_string + "<ti_cedent  id=\"" + set2_id + "\"  type=\"Second set\"> ";
	xml_string += format_cedent (set2);
	xml_string = xml_string + "</ti_cedent> ";

	return xml_string;
}

double Hyp_SD4ft_Meta::get_conf (long _a, long _b)
{
	return ((double) _a	/ (_a + _b));
}

double Hyp_SD4ft_Meta::get_d_conf (long _a, long _b, long _c)
{
	return ((double) _a / (_a + _b + _c));
}

double Hyp_SD4ft_Meta::get_e_conf (long _a, long _b, long _c, long _d)
{
	return ((double) (_a + _d) / (_a + _b + _c + _d));
}

double Hyp_SD4ft_Meta::get_support (long _a, long _b, long _c, long _d)
{
	return ((double) _a / (_a + _b + _c + _d));
}

double Hyp_SD4ft_Meta::get_completeness (long _a, long _c)
{
	return ((double) _a / (_a + _c));
}

double Hyp_SD4ft_Meta::get_avg_diff (long _a, long _b, long _c, long _d)
{
	return ((double) _a * (_a + _b + _c + _d) / ((_a + _b) * (_a + _c)) - 1);
}

double Hyp_SD4ft_Meta::get_chi_sq (long _a, long _b, long _c, long _d)
{
	if ((_a + _c) * (_b + _d) * (_a + _b) * (_c + _d) == 0) return 0;

	double dDelta = _a * _d - _b * _c;

	return ((_a + _b + _c + _d) * dDelta * dDelta) / 
		   ((_a + _c) * (_b + _d) * (_a + _b) * (_c + _d));
}

CString Hyp_SD4ft_Meta::get_fisher (long _a, long _b, long _c, long _d)
{

	if ( !gLnFaktTab.Init( _a + _b + _c + _d + 1)) return "Unknown";

	long r= _a + _b;
	long s= _c + _d;
	long k= _a + _c;
	long l= _b + _d;
	long n= r + s; //a + b + c + d

	double dValue= exp( gLnFaktTab.GetLnFakt( r)+ gLnFaktTab.GetLnFakt( s)+ 
				gLnFaktTab.GetLnFakt( k)+ gLnFaktTab.GetLnFakt( l)-
				gLnFaktTab.GetLnFakt( n)- gLnFaktTab.GetLnFakt( _a)-
				gLnFaktTab.GetLnFakt( r- _a)- gLnFaktTab.GetLnFakt( k- _a)-
				gLnFaktTab.GetLnFakt( n- r- k+ _a));

	long minRK= r < k ? r : k;	// min( r, k)

	double dSuma= dValue;
	long c1 = n- r- k;

	long i;

	for (i= _a + 1; i <= minRK; i++)
	{
		double dDelta= ((double)( r- i+ 1)*( k- i+ 1))/ ( i* (c1+ i));
		if ( dDelta == 0) break;
		dValue= dValue* dDelta;
		dSuma+= dValue;
	}

	return (LPCTSTR) (_bstr_t) dSuma;
}

CString Hyp_SD4ft_Meta::get_low_bnd_imp (long _a, long _b)
{
	if ( !gLnFaktTab.Init( _a + _b + 1)) return "Unknown";

	double const m_p = 0.9;
	double m_pLog = log( m_p);
	double m_1pLog = log( 1- m_p);

	long ab= _a + _b;

	double nSuma= 0.0;
	long i;

	for (i = _a; i <= ab; i++)
	{
		nSuma += exp( gLnFaktTab.GetLnFakt(ab)- 
				( gLnFaktTab.GetLnFakt(i)+ gLnFaktTab.GetLnFakt(ab - i))+
				m_pLog*i+ m_1pLog*(ab - i));
	}

	return (LPCTSTR) (_bstr_t) nSuma;
}

CString Hyp_SD4ft_Meta::get_up_bnd_imp (long _a, long _b)
{
	if ( !gLnFaktTab.Init( _a + _b + 1)) return "Unknown";

	double const m_p = 0.9;
	double m_pLog = log( m_p);
	double m_1pLog = log( 1- m_p);

	long r = _a + _b;

	double nSuma= 0.0;
	long i;

	for (i = 0; i <= _a; i++)
	{
		nSuma += exp( gLnFaktTab.GetLnFakt( r)- 
				(gLnFaktTab.GetLnFakt( i)+ gLnFaktTab.GetLnFakt( r- i))+
				m_pLog*i+ m_1pLog*( r- i));
	}

	return (LPCTSTR) (_bstr_t) nSuma;
}

CString Hyp_SD4ft_Meta::get_low_bnd_dbl_imp (long _a, long _b, long _c)
{
	if ( !gLnFaktTab.Init( _a + _b + _c + 1)) return "Unknown";

	double const m_p = 0.9;
	double m_pLog = log( m_p);
	double m_1pLog = log( 1- m_p);

	long abc = _a + _b + _c;

	double nSuma= 0.0;
	long i;

	for (i = _a; i <= abc; i++)
	{
		nSuma += exp( gLnFaktTab.GetLnFakt( abc) - 
				( gLnFaktTab.GetLnFakt( i) + gLnFaktTab.GetLnFakt( abc- i))+
				m_pLog*i+ m_1pLog*( abc- i));
	}

	return (LPCTSTR) (_bstr_t) nSuma;
}

CString Hyp_SD4ft_Meta::get_up_bnd_dbl_imp (long _a, long _b, long _c)
{
	if ( !gLnFaktTab.Init( _a + _b + _c + 1)) return "Unknown";

	double const m_p = 0.9;
	double m_pLog = log( m_p);
	double m_1pLog = log( 1- m_p);

	long abc = _a + _b + _c;

	double nSuma= 0.0;
	long i;

	for (i = 0; i <= _a; i++)
	{
		nSuma += exp( gLnFaktTab.GetLnFakt( abc) - 
				( gLnFaktTab.GetLnFakt( i) + gLnFaktTab.GetLnFakt( abc- i))+
				m_pLog*i+ m_1pLog*( abc- i));
	}

	return (LPCTSTR) (_bstr_t) nSuma;
}

CString Hyp_SD4ft_Meta::get_low_bnd_eq (long _a, long _b, long _c, long _d)
{
	if ( !gLnFaktTab.Init( _a + _b + _c + _d + 1)) return "Unknown";

	double const m_p = 0.9;
	double m_pLog= log( m_p);
	double m_1pLog= log( 1- m_p);

	long n = _a + _b + _c + _d;
	long ad= _a + _d;

	double nSuma= 0;
	long i;

	for (i= ad; i <= n; i++)
	{
		nSuma += exp( gLnFaktTab.GetLnFakt(n) - 
				 ( gLnFaktTab.GetLnFakt( i) + gLnFaktTab.GetLnFakt(n - i))+
				 m_pLog*i+ m_1pLog*(n - i));
	}

	return (LPCTSTR) (_bstr_t) nSuma;
}

CString Hyp_SD4ft_Meta::get_up_bnd_eq (long _a, long _b, long _c, long _d)
{
	if ( !gLnFaktTab.Init( _a + _b + _c + _d + 1)) return "Unknown";

	double const m_p = 0.9;
	double m_pLog= log( m_p);
	double m_1pLog= log( 1- m_p);

	long n = _a + _b + _c + _d;
	long ad= _a + _d;

	double nSuma= 0;
	long i;

	for (i= 0; i <= ad; i++)
	{
		nSuma += exp( gLnFaktTab.GetLnFakt(n) - 
				( gLnFaktTab.GetLnFakt( i) + gLnFaktTab.GetLnFakt(n - i))+
				m_pLog*i+ m_1pLog*(n - i));
	}

	return (LPCTSTR) (_bstr_t) nSuma;
}

double Hyp_SD4ft_Meta::get_dr_sum (long _a, long _b, long _c, long _d,
								   long _e, long _f, long _g, long _h)
{
	long sum1 = _a + _b + _c + _d;
	long sum2 = _e + _f + _g + _h;
	double dr_sum = fabs (((double) _a / sum1) - ((double) _e / sum2)) +
					fabs (((double) _b / sum1) - ((double) _f / sum2)) +
					fabs (((double) _c / sum1) - ((double) _g / sum2)) +
					fabs (((double) _d / sum1) - ((double) _h / sum2));
	return dr_sum;
}

CString Hyp_SDCF_Meta::xml_convert ()
{
	CString xml_string;
	CString hlp;

	db_name.Replace ("&", "&amp;");
	matrix_name.Replace ("&", "&amp;");
	task_name.Replace ("&", "&amp;");
	quant.Replace ("&", "&amp;");

	db_name.Replace ("<", "&lt;");
	matrix_name.Replace ("<", "&lt;");
	task_name.Replace ("<", "&lt;");
	quant.Replace ("<", "&lt;");

	db_name.Replace (">", "&gt;");
	matrix_name.Replace (">", "&gt;");
	task_name.Replace (">", "&gt;");
	quant.Replace (">", "&gt;");

	//beginning of the hyp_cf element
	xml_string = " <hyp_sdcf id=\"" + id + "\" db_name=\"" + db_name + "\" ";
	xml_string = xml_string + "matrix_name=\"" + matrix_name + "\" ";
	xml_string = xml_string + "task_name=\"" + task_name + "\" ";
	
	xml_string = xml_string + " sum1=\"" + sum1 + "\" ";
	xml_string = xml_string + " min1=\"" + min1 + "\" ";
	xml_string = xml_string + " max1=\"" + max1 + "\" ";
	xml_string = xml_string + " v1=\"" + v1 + "\" ";
	xml_string = xml_string + " nom_var1=\"" + nom_var1 + "\" ";
	xml_string = xml_string + " dor_var1=\"" + dor_var1 + "\" ";
	xml_string = xml_string + " avg_a1=\"" + avg_a1 + "\" ";
	xml_string = xml_string + " avg_g1=\"" + avg_g1 + "\" ";
	xml_string = xml_string + " var1=\"" + var1 + "\" ";
	xml_string = xml_string + " st_dev1=\"" + st_dev1 + "\" ";
	xml_string = xml_string + " skew1=\"" + skew1 + "\" ";
	xml_string = xml_string + " asym1=\"" + asym1 + "\" ";

	xml_string = xml_string + " sum2=\"" + sum2 + "\" ";
	xml_string = xml_string + " min2=\"" + min2 + "\" ";
	xml_string = xml_string + " max2=\"" + max2 + "\" ";
	xml_string = xml_string + " v2=\"" + v2 + "\" ";
	xml_string = xml_string + " nom_var2=\"" + nom_var2 + "\" ";
	xml_string = xml_string + " dor_var2=\"" + dor_var2 + "\" ";
	xml_string = xml_string + " avg_a2=\"" + avg_a2 + "\" ";
	xml_string = xml_string + " avg_g2=\"" + avg_g2 + "\" ";
	xml_string = xml_string + " var2=\"" + var2 + "\" ";
	xml_string = xml_string + " st_dev2=\"" + st_dev2 + "\" ";
	xml_string = xml_string + " skew2=\"" + skew2 + "\" ";
	xml_string = xml_string + " asym2=\"" + asym2 + "\" ";

	xml_string = xml_string + " da_sum=\"" + da_sum + "\" ";
	xml_string = xml_string + " da_min=\"" + da_min + "\" ";
	xml_string = xml_string + " da_max=\"" + da_max + "\" ";
	xml_string = xml_string + " dr_sum=\"" + dr_sum + "\" ";
	xml_string = xml_string + " dr_min=\"" + dr_min + "\" ";
	xml_string = xml_string + " dr_max=\"" + dr_max + "\" ";

	xml_string = xml_string + " attributes=\"" + a_id + "\" ";
	xml_string = xml_string + " condition=\"" + c_id + "\" ";
	xml_string = xml_string + " set1=\"" + s1_id + "\" ";
	xml_string = xml_string + " set2=\"" + s2_id + "\">";

	xml_string = xml_string + " <r> ";
	int i;
	for (i = 0; i < frequencies1.GetSize (); i++)
	{
		hlp.Format ("%d", frequencies1.GetAt (i));
		xml_string = xml_string + " <c val=\"" + hlp + "\"/> ";
	}

	xml_string = xml_string + " </r> ";

	xml_string = xml_string + " <r> ";

	for (i = 0; i < frequencies2.GetSize (); i++)
	{
		hlp.Format ("%d", frequencies2.GetAt (i));
		xml_string = xml_string + " <c val=\"" + hlp + "\"/> ";
	}

	xml_string = xml_string + " </r> ";

	xml_string += " </hyp_sdcf>  ";
	//end of hyp_sdcf element

	xml_string = xml_string + " <ti_attribute id=\"" +
		a_id + "\" quant=\"" + quant + "\" type=\"Attributes\"> ";
	for (i = 0; i < attributes.GetSize (); i++)
	{
		xml_string = xml_string + " <ti_category value=\""
			+ attributes.GetAt (i) + "\"/> ";
	}
	xml_string = xml_string + " </ti_attribute> ";

	xml_string = xml_string + "<ti_cedent  id=\"" + c_id + "\"  type=\"Condition\"> ";
    xml_string += format_cedent (condition);
	xml_string = xml_string + "</ti_cedent> ";

	xml_string = xml_string + "<ti_cedent  id=\"" + s1_id + "\"  type=\"First set\"> ";
    xml_string += format_cedent (set1);
	xml_string = xml_string + "</ti_cedent> ";

	xml_string = xml_string + "<ti_cedent  id=\"" + s2_id + "\"  type=\"Second set\"> ";
    xml_string += format_cedent (set2);
	xml_string = xml_string + "</ti_cedent> ";

	return xml_string;
}

int Hyp_SDCF_Meta::get_sum1 ()
{
	int s = 0;
	int i;

	for (i = 0; i < frequencies1.GetSize (); i++) s += frequencies1.GetAt (i);

	return s;
}

int Hyp_SDCF_Meta::get_max1 ()
{
	int m = frequencies1.GetAt (0);
	int i;
	for (i = 1; i < frequencies1.GetSize (); i++)
		if (frequencies1.GetAt (i) > m) m = frequencies1.GetAt (i);

	return m;
}

CString Hyp_SDCF_Meta::get_min1 ()
{
	int m = frequencies1.GetAt (0);
	int i;
	CString hlp;

	for (i = 1; i < frequencies1.GetSize (); i++)
		if (frequencies1.GetAt (i) < m) m = frequencies1.GetAt (i);

	hlp.Format ("%d", m);
	return hlp;
}

double Hyp_SDCF_Meta::GetVariationRatio1 ()
{
	double dSum= get_sum1 ();
	if ( dSum == 0.0) return 0.0;

	double dMax= get_max1 ();
	return 1 - dMax/dSum;
}

CString Hyp_SDCF_Meta::get_nom_var1 ()
{
	int j;
	if (frequencies1.GetSize () <= 1) return (LPCTSTR) (_bstr_t) (0.0);

	double dSum= get_sum1 ();
	if ( dSum == 0.0) return (LPCTSTR) (_bstr_t) (0.0);

	double dNomVar= 0;
	for (j= 0; j < frequencies1.GetSize (); j++)
	{
		int nValue= frequencies1.GetAt (j);
		double dFi= nValue / dSum;

		dNomVar+= dFi * dFi;
	}
	dNomVar= 1 - dNomVar;

	return
		(LPCTSTR) (_bstr_t) ((frequencies1.GetSize () * dNomVar) / (frequencies1.GetSize () - 1));
}

CString Hyp_SDCF_Meta::get_dor_var1 ()
{
	if ( frequencies1.GetSize () <= 1) return (LPCTSTR) (_bstr_t) (0.0);

	double dSum= get_sum1 ();
	if ( dSum == 0.0) return (LPCTSTR) (_bstr_t) (0.0);

	double dDorVar= 0;
	double dSumF= 0;
	for (int j= 0; j < frequencies1.GetSize (); j++)
	{
		int nValue= frequencies1.GetAt (j);
		double dFi= nValue / dSum;

		dSumF+= dFi;

		dDorVar+= dSumF * (1 - dSumF);
	}
	dDorVar= 2 * dDorVar;

	return (LPCTSTR) (_bstr_t) ((2 * dDorVar) / ( frequencies1.GetSize ()- 1));
}

int Hyp_SDCF_Meta::get_sum2 ()
{
	int s = 0;
	int i;

	for (i = 0; i < frequencies2.GetSize (); i++) s += frequencies2.GetAt (i);

	return s;
}

int Hyp_SDCF_Meta::get_max2 ()
{
	int m = frequencies2.GetAt (0);
	int i;
	for (i = 1; i < frequencies2.GetSize (); i++)
		if (frequencies2.GetAt (i) > m) m = frequencies2.GetAt (i);

	return m;
}

CString Hyp_SDCF_Meta::get_min2 ()
{
	int m = frequencies2.GetAt (0);
	int i;
	CString hlp;

	for (i = 1; i < frequencies2.GetSize (); i++)
		if (frequencies2.GetAt (i) < m) m = frequencies2.GetAt (i);

	hlp.Format ("%d", m);
	return hlp;
}

double Hyp_SDCF_Meta::GetVariationRatio2 ()
{
	double dSum= get_sum2 ();
	if ( dSum == 0.0) return 0.0;

	double dMax= get_max2 ();
	return 1 - dMax/dSum;
}

CString Hyp_SDCF_Meta::get_nom_var2 ()
{
	int j;
	if (frequencies2.GetSize () <= 1) return (LPCTSTR) (_bstr_t) (0.0);

	double dSum= get_sum2 ();
	if ( dSum == 0.0) return (LPCTSTR) (_bstr_t) (0.0);

	double dNomVar= 0;
	for (j= 0; j < frequencies2.GetSize (); j++)
	{
		int nValue= frequencies2.GetAt (j);
		double dFi= nValue / dSum;

		dNomVar+= dFi * dFi;
	}
	dNomVar= 1 - dNomVar;

	return
		(LPCTSTR) (_bstr_t) ((frequencies2.GetSize () * dNomVar) / (frequencies2.GetSize () - 1));
}

CString Hyp_SDCF_Meta::get_dor_var2 ()
{
	if ( frequencies2.GetSize () <= 1) return (LPCTSTR) (_bstr_t) (0.0);

	double dSum= get_sum2 ();
	if ( dSum == 0.0) return (LPCTSTR) (_bstr_t) (0.0);

	double dDorVar= 0;
	double dSumF= 0;
	for (int j= 0; j < frequencies2.GetSize (); j++)
	{
		int nValue= frequencies2.GetAt (j);
		double dFi= nValue / dSum;

		dSumF+= dFi;

		dDorVar+= dSumF * (1 - dSumF);
	}
	dDorVar= 2 * dDorVar;

	return (LPCTSTR) (_bstr_t) ((2 * dDorVar) / ( frequencies2.GetSize ()- 1));
}

CString Hyp_SDCF_Meta::get_da_sum ()
{
	int i;
	int sum = 0;
	CString hlp;
	for (i = 0; i < frequencies1.GetSize (); i++)
		sum += abs (frequencies1.GetAt (i) - frequencies2.GetAt (i));
	hlp.Format ("%d", sum);
	return hlp;
}

CString Hyp_SDCF_Meta::get_da_min ()
{
	int i;
	int min = abs (frequencies1.GetAt (0) - frequencies2.GetAt (0));
	CString hlp;
	for (i = 1; i < frequencies1.GetSize (); i++)
		if (abs (frequencies1.GetAt (i) - frequencies2.GetAt (i)) < min)
			min =abs (frequencies1.GetAt (i) - frequencies2.GetAt (i));
	hlp.Format ("%d", min);
	return hlp;
}

CString Hyp_SDCF_Meta::get_da_max ()
{
	int i;
	int max = abs (frequencies1.GetAt (0) - frequencies2.GetAt (0));
	CString hlp;
	for (i = 1; i < frequencies1.GetSize (); i++)
		if (abs (frequencies1.GetAt (i) - frequencies2.GetAt (i)) > max)
			max =abs (frequencies1.GetAt (i) - frequencies2.GetAt (i));
	hlp.Format ("%d", max);
	return hlp;
}

CString Hyp_SDCF_Meta::get_dr_sum ()
{
	int i;
	double sum = 0.0;
	double sum1 = (double) get_sum1 ();
	double sum2 = (double) get_sum2 ();
	for (i = 0; i < frequencies1.GetSize (); i++)
		sum += fabs (frequencies1.GetAt (i) / sum1 - frequencies2.GetAt (i) / sum2);
	return (LPCTSTR) (_bstr_t) sum;
}

CString Hyp_SDCF_Meta::get_dr_min ()
{
	int i;
	double sum1 = (double) get_sum1 ();
	double sum2 = (double) get_sum2 ();
	double min = fabs (frequencies1.GetAt (0) / sum1 - frequencies2.GetAt (0) / sum2);
	for (i = 1; i < frequencies1.GetSize (); i++)
		if (fabs (frequencies1.GetAt (i) / sum1 - frequencies2.GetAt (i) / sum2) < min)
			min = fabs (frequencies1.GetAt (i) / sum1 - frequencies2.GetAt (i) / sum2);
	return (LPCTSTR) (_bstr_t) min;
}

CString Hyp_SDCF_Meta::get_dr_max ()
{
	int i;
	double sum1 = (double) get_sum1 ();
	double sum2 = (double) get_sum2 ();
	double max = fabs (frequencies1.GetAt (0) / sum1 - frequencies2.GetAt (0) / sum2);
	for (i = 1; i < frequencies1.GetSize (); i++)
		if (fabs (frequencies1.GetAt (i) / sum1 - frequencies2.GetAt (i) / sum2) > max)
			max = fabs (frequencies1.GetAt (i) / sum1 - frequencies2.GetAt (i) / sum2);
	return (LPCTSTR) (_bstr_t) max;
}

CString Hyp_KL_Meta::xml_convert ()
{
	CString xml_string;
	CString hlp;

	db_name.Replace ("&", "&amp;");
	matrix_name.Replace ("&", "&amp;");
	task_name.Replace ("&", "&amp;");
	quant_row.Replace ("&", "&amp;");
	quant_col.Replace ("&", "&amp;");

	db_name.Replace ("<", "&lt;");
	matrix_name.Replace ("<", "&lt;");
	task_name.Replace ("<", "&lt;");
	quant_row.Replace ("<", "&lt;");
	quant_col.Replace ("<", "&lt;");

	db_name.Replace (">", "&gt;");
	matrix_name.Replace (">", "&gt;");
	task_name.Replace (">", "&gt;");
	quant_row.Replace (">", "&gt;");
	quant_col.Replace (">", "&gt;");

	//beginning of the hyp_kl element
	xml_string = " <hyp_kl id=\"" + id + "\" db_name=\"" + db_name + "\" ";
	xml_string = xml_string + "matrix_name=\"" + matrix_name + "\" ";
	xml_string = xml_string + "task_name=\"" + task_name + "\" ";
	
	xml_string = xml_string + " sum=\"" + sum + "\" ";
	xml_string = xml_string + " min=\"" + min + "\" ";
	xml_string = xml_string + " max=\"" + max + "\" ";
	xml_string = xml_string + " chi_sq=\"" + chi_sq + "\" ";
	xml_string = xml_string + " fnc_s=\"" + fnc_s + "\" ";
	xml_string = xml_string + " fnc_r=\"" + fnc_r + "\" ";
	xml_string = xml_string + " h_c=\"" + h_c + "\" ";
	xml_string = xml_string + " h_r=\"" + h_r + "\" ";
	xml_string = xml_string + " h_c_r=\"" + h_c_r + "\" ";
	xml_string = xml_string + " mi=\"" + mi + "\" ";
	xml_string = xml_string + " aic=\"" + aic + "\" ";
	xml_string = xml_string + " kend=\"" + kend + "\" ";

	xml_string = xml_string + " row_attributes=\"" + row_id + "\" ";
	xml_string = xml_string + " column_attributes=\"" + col_id + "\" ";
	xml_string = xml_string + " condition=\"" + c_id + "\">";

	xml_string = xml_string + " <tab> ";
	int i;
	for (i = 0; i < table.GetSize (); i++)
	{
		xml_string = xml_string + " <r> ";
		for (int j = 0; j < table.GetAt (i)->GetSize (); j++)
		{
			hlp.Format ("%d", table.GetAt (i)->GetAt (j));
			xml_string = xml_string + " <c val=\"" + hlp + "\"/> ";
		}
		xml_string = xml_string + " </r> ";
	}

	xml_string = xml_string + " </tab> ";

	xml_string += " </hyp_kl>  ";
	//end of hyp_kl element

	xml_string = xml_string + " <ti_attribute id=\"" +
		row_id + "\" quant=\"" + quant_row + "\" type=\"Attributes\"> ";
	for (i = 0; i < row_attributes.GetSize (); i++)
	{
		xml_string = xml_string + " <ti_category value=\""
			+ row_attributes.GetAt (i) + "\"/> ";
	}
	xml_string = xml_string + " </ti_attribute> ";

	xml_string = xml_string + " <ti_attribute id=\"" +
		col_id + "\" quant=\"" + quant_col + "\" type=\"Attributes\"> ";
	for (i = 0; i < column_attributes.GetSize (); i++)
	{
		xml_string = xml_string + " <ti_category value=\""
			+ column_attributes.GetAt (i) + "\"/> ";
	}
	xml_string = xml_string + " </ti_attribute> ";

	xml_string = xml_string + "<ti_cedent  id=\"" + c_id + "\"  type=\"Condition\"> ";
    xml_string += format_cedent (condition);
	xml_string = xml_string + "</ti_cedent> ";

	return xml_string;
}

int Hyp_KL_Meta::get_sum ()
{
	int s = 0;
	int i;
	int j;

	for (i = 0; i < table.GetSize (); i++)
		for (j = 0; j < table.GetAt (i)->GetSize (); j++)
			s += table.GetAt (i)->GetAt (j);

	return s;
}

int Hyp_KL_Meta::get_max ()
{
	int m = table.GetAt (0)->GetAt (0);
	int i;
	int j;
	for (i = 0; i < table.GetSize (); i++)
		for (j = 0; j < table.GetAt (i)->GetSize (); j++)
			if (table.GetAt (i)->GetAt (j) > m) m = table.GetAt (i)->GetAt (j);

	return m;
}

CString Hyp_KL_Meta::get_min ()
{
	int m = table.GetAt (0)->GetAt (0);
	int i;
	int j;
	CString hlp;

	for (i = 0; i < table.GetSize (); i++)
		for (j = 0; j < table.GetAt (i)->GetSize (); j++)
			if (table.GetAt (i)->GetAt (j) < m) m = table.GetAt (i)->GetAt (j);

	hlp.Format ("%d", m);
	return hlp;
}

int Hyp_KL_Meta::get_row_sum (Tint_Tab * tab, int row)
{
	int i;
	int sum = 0;
	for (i = 0; i < tab->GetAt (row)->GetSize (); i++)
		sum += tab->GetAt (row)->GetAt (i);
	return sum;
}

int Hyp_KL_Meta::get_col_sum (Tint_Tab * tab, int col)
{
	int i;
	int sum = 0;
	for (i = 0; i < tab->GetSize (); i++)
		sum += tab->GetAt (i)->GetAt (col);
	return sum;
}

CString Hyp_KL_Meta::get_chi_sq ()
{
	int sum = get_sum ();
	double dValue;
	double dChiSq= 0;
	int i;
	int j;
	int nRk;
	int nSl;

	if ( sum == 0) return "Unknown";

	for (i = 0; i < table.GetSize () ; i++)
	{
		nRk= get_row_sum (&table, i);

		for (j = 0; j < table.GetAt (i)->GetSize (); j++)
		{
			nSl= get_col_sum (&table, j);

			if ( nRk != 0 &&
				 nSl != 0)
			{
				dValue= (double)(table.GetAt (i)->GetAt (j))- ((double)nRk)*nSl/((double)sum);
				dChiSq+= (dValue*dValue)/(((double)nRk)*nSl);
			}
		}
	}
	return (LPCTSTR) (_bstr_t) (sum * dChiSq);
}

CString Hyp_KL_Meta::get_fnc_s ()
{
	int nTotalSum = get_sum ();
	if ( nTotalSum == 0) return "Unknown";

	double dSum = 0;
	int i;
	int j;
	int nMax;
	int dValue;
	for (i = 0; i < table.GetSize (); i++)
	{
		nMax= 0;
		for (j = 0; j < table.GetAt (i)->GetSize (); j++)
		{
			dValue= table.GetAt (i)->GetAt (j);
			if ( dValue > nMax) nMax = dValue;
		}
		dSum += nMax;
	}
	return (LPCTSTR) (_bstr_t) (dSum / nTotalSum);
}

CString Hyp_KL_Meta::get_fnc_r ()
{
	int nTotalSum= get_sum();
	if ( nTotalSum == 0) return "Unknown";

	double dSum= 0;
	int i;
	int j;
	int nMax;
	int nValue;
	for (i = 0; i < table.GetSize (); i++)
	{
		nMax= 0;
		for (j = 0; j < table.GetAt (i)->GetSize (); j++)
		{
			nValue = table.GetAt (i)->GetAt (j);
			if ( nValue > nMax) nMax = nValue;
		}
		dSum += nMax * get_row_sum (&table, i);
	}
	return (LPCTSTR) (_bstr_t) (dSum / (((double)nTotalSum)* nTotalSum));
}

double Hyp_KL_Meta::get_h_c ()
{
	double dSum= get_sum ();
	if ( dSum == 0) return 0.0;

	double dLog2= log((double) 2);
	int j;
	int nSl;
	double dValue;

	double dHC= 0;
	for (j = 0; j < table.GetAt (0)->GetSize (); j++)
	{
		nSl = get_col_sum (&table, j);

		if ( nSl != 0)
		{
			dValue = (nSl/dSum) * (log(nSl/dSum)/dLog2);
			dHC += dValue;
		}
	}

	dHC = -dHC;

	return dHC;
}

double Hyp_KL_Meta::get_h_r ()
{
	double dSum= get_sum ();
	if ( dSum == 0) return 0.0;

	double dLog2= log((double) 2);
	int i;
	int nRk;
	double dValue;

	double dHR= 0;
	for (i= 0; i < table.GetSize (); i++)
	{
		nRk= get_row_sum (&table, i);

		if ( nRk != 0)
		{
			dValue= (nRk/dSum)*(log(nRk/dSum)/dLog2);
			dHR+= dValue;
		}
	}

	dHR= -dHR;

	return dHR;
}

double Hyp_KL_Meta::get_h_c_r ()
{
	double dSum= get_sum ();
	if ( dSum == 0) return 0.0;

	double dLog2= log((double) 2);
	int i;
	int j;
	int nRk;
	int nSl;
	double dHAVk;
	double dValueF;
	double dValue;

	double dHA = 0;
	for (i = 0; i < table.GetSize (); i++)
	{
		nRk = get_row_sum (&table, i);

		dHAVk = 0;
		if ( nRk != 0)
		{
			for (j = 0; j < table.GetAt (i)->GetSize (); j++)
			{
				nSl = get_col_sum (&table, j);

				dValueF = (double) table.GetAt (i)->GetAt (j);
				if ( dValueF != 0)
				{
					dValue = (dValueF / nRk) * (log(dValueF / nRk) / dLog2);
					dHAVk += dValue;
				}
			}
			dHAVk = -dHAVk;

			dHA += nRk*dHAVk/dSum;
		}
	}

	return dHA;
}

CString Hyp_KL_Meta::get_mi ()
{
	if (get_sum () == 0) return "Unknown";
	double dHC = get_h_c ();

	double dHR = get_h_r ();

	double dHCR = get_h_c_r ();

	double dMin = dHC < dHR ? dHC : dHR;
	if (dMin == 0) return "Unknown";

	double dICR = (dHC - dHCR)/dMin;

	return (LPCTSTR) (_bstr_t) dICR;
}

CString Hyp_KL_Meta::get_aic ()
{
	double dSum = get_sum ();
	if ( dSum == 0) return "Unknown";

	double dNl= 0.0;
	int j;
	int i;
	int nSl;
	int nRk;
	int nValue;

	for (j = 0; j < table.GetAt (0)->GetSize (); j++)
	{
		nSl = get_col_sum (&table, j);

		if ( nSl != 0)
		{
			dNl += nSl * log((double) nSl);
		}
	}

	double dDelitel = dSum * log( dSum) - dNl;

	if (dDelitel == 0) return "Unknown";

	double dNk = 0.0;
	for (i= 0; i < table.GetSize (); i++)
	{
		nRk = get_row_sum (&table, i);

		if ( nRk != 0)
		{
			dNk += nRk * log((double) nRk);
		}
	}
	
	double dAkl= 0.0;
	{
	for (i = 0; i < table.GetSize (); i++)
	{
		for (j = 0; j < table.GetAt (0)->GetSize (); j++)
		{
			nValue = table.GetAt (i)->GetAt (j);
			if ( nValue != 0)
			{
				dAkl += nValue * log((double) nValue);
			}
		}
	}
	}

	double dDelenec = dNk - dAkl;

	double dTheta = 1 - dDelenec / dDelitel;

	return (LPCTSTR) (_bstr_t) dTheta;
}

CString Hyp_KL_Meta::get_kend ()
{
	double dSum = get_sum ();
	if (dSum == 0) return "Unknown";

	double dNk2 = 0;
	int i;
	int j;
	int nRk;
	int nSl;
	
	for (i = 0; i < table.GetSize (); i++)
	{
		nRk= get_row_sum (&table, i);
		dNk2 += ((double)nRk) * nRk;
	}

	double dNl2 = 0;
	for (j = 0; j < table.GetAt (0)->GetSize (); j++)
	{
		nSl = get_col_sum (&table, j);
		dNl2 += ((double)nSl) * nSl;
	}

	double dSum2 = dSum * dSum;

	double dDelitel = sqrt( (dSum2 - dNk2) * (dSum2 - dNl2));

	if (dDelitel == 0) return "";

	double dP = 0;
	double dQ = 0;
	double dPkl;
	double dQkl;
	int i2;
	int j2;

	{
		for (i = 0; i < table.GetSize (); i++)
		{
			for (j = 0; j < table.GetAt (0)->GetSize (); j++)
			{
				dPkl= 0;
				dQkl= 0;

				for (i2 = i+ 1; i2 < table.GetSize (); i2++)
				{
					for (j2 = 0; j2 < table.GetAt (0)->GetSize (); j2++)
					{ 
						if (j2 < j) dQkl += (double)(table.GetAt (i2)->GetAt (j2));
						if (j2 > j) dPkl += (double)(table.GetAt (i2)->GetAt (j2));    
					}
				}

				dQ += ((double)(table.GetAt (i)->GetAt (j))) * dQkl;
				dP += ((double)(table.GetAt (i)->GetAt (j))) * dPkl;
			}
		}
	}
	double dDelenec= 2 * (dP- dQ);

	double dTauB = dDelenec / dDelitel;

	return (LPCTSTR) (_bstr_t) dTauB;
}

CString Hyp_SDKL_Meta::xml_convert ()
{
	CString xml_string;
	CString hlp;

	db_name.Replace ("&", "&amp;");
	matrix_name.Replace ("&", "&amp;");
	task_name.Replace ("&", "&amp;");
	quant_row.Replace ("&", "&amp;");
	quant_col.Replace ("&", "&amp;");

	db_name.Replace ("<", "&lt;");
	matrix_name.Replace ("<", "&lt;");
	task_name.Replace ("<", "&lt;");
	quant_row.Replace ("<", "&lt;");
	quant_col.Replace ("<", "&lt;");

	db_name.Replace (">", "&gt;");
	matrix_name.Replace (">", "&gt;");
	task_name.Replace (">", "&gt;");
	quant_row.Replace (">", "&gt;");
	quant_col.Replace (">", "&gt;");

	//beginning of the hyp_sdkl element
	xml_string = " <hyp_sdkl id=\"" + id + "\" db_name=\"" + db_name + "\" ";
	xml_string = xml_string + "matrix_name=\"" + matrix_name + "\" ";
	xml_string = xml_string + "task_name=\"" + task_name + "\" ";
	
	xml_string = xml_string + " sum1=\"" + sum1 + "\" ";
	xml_string = xml_string + " min1=\"" + min1 + "\" ";
	xml_string = xml_string + " max1=\"" + max1 + "\" ";
	xml_string = xml_string + " chi_sq1=\"" + chi_sq1 + "\" ";
	xml_string = xml_string + " fnc_s1=\"" + fnc_s1 + "\" ";
	xml_string = xml_string + " fnc_r1=\"" + fnc_r1 + "\" ";
	xml_string = xml_string + " h_c1=\"" + h_c1 + "\" ";
	xml_string = xml_string + " h_r1=\"" + h_r1 + "\" ";
	xml_string = xml_string + " h_c_r1=\"" + h_c_r1 + "\" ";
	xml_string = xml_string + " mi1=\"" + mi1 + "\" ";
	xml_string = xml_string + " aic1=\"" + aic1 + "\" ";
	xml_string = xml_string + " kend1=\"" + kend1 + "\" ";

	xml_string = xml_string + " sum2=\"" + sum2 + "\" ";
	xml_string = xml_string + " min2=\"" + min2 + "\" ";
	xml_string = xml_string + " max2=\"" + max2 + "\" ";
	xml_string = xml_string + " chi_sq2=\"" + chi_sq2 + "\" ";
	xml_string = xml_string + " fnc_s2=\"" + fnc_s2 + "\" ";
	xml_string = xml_string + " fnc_r2=\"" + fnc_r2 + "\" ";
	xml_string = xml_string + " h_c2=\"" + h_c2 + "\" ";
	xml_string = xml_string + " h_r2=\"" + h_r2 + "\" ";
	xml_string = xml_string + " h_c_r2=\"" + h_c_r2 + "\" ";
	xml_string = xml_string + " mi2=\"" + mi2 + "\" ";
	xml_string = xml_string + " aic2=\"" + aic2 + "\" ";
	xml_string = xml_string + " kend2=\"" + kend2 + "\" ";

	xml_string = xml_string + " da_sum=\"" + da_sum + "\" ";
	xml_string = xml_string + " da_min=\"" + da_min + "\" ";
	xml_string = xml_string + " da_max=\"" + da_max + "\" ";
	xml_string = xml_string + " dr_sum=\"" + dr_sum + "\" ";
	xml_string = xml_string + " dr_min=\"" + dr_min + "\" ";
	xml_string = xml_string + " dr_max=\"" + dr_max + "\" ";

	xml_string = xml_string + " row_attributes=\"" + row_id + "\" ";
	xml_string = xml_string + " column_attributes=\"" + col_id + "\" ";
	xml_string = xml_string + " condition=\"" + c_id + "\" ";
	xml_string = xml_string + " set1=\"" + s1_id + "\" ";
	xml_string = xml_string + " set2=\"" + s2_id + "\">";

	xml_string = xml_string + " <tab> ";
	int i;
	for (i = 0; i < table1.GetSize (); i++)
	{
		xml_string = xml_string + " <r> ";
		for (int j = 0; j < table1.GetAt (i)->GetSize (); j++)
		{
			hlp.Format ("%d", table1.GetAt (i)->GetAt (j));
			xml_string = xml_string + " <c val=\"" + hlp + "\"/> ";
		}
		xml_string = xml_string + " </r> ";
	}

	xml_string = xml_string + " </tab> ";

	xml_string = xml_string + " <tab> ";

	for (i = 0; i < table2.GetSize (); i++)
	{
		xml_string = xml_string + " <r> ";
		for (int j = 0; j < table2.GetAt (i)->GetSize (); j++)
		{
			hlp.Format ("%d", table2.GetAt (i)->GetAt (j));
			xml_string = xml_string + " <c val=\"" + hlp + "\"/> ";
		}
		xml_string = xml_string + " </r> ";
	}

	xml_string = xml_string + " </tab> ";

	xml_string += " </hyp_sdkl>  ";
	//end of hyp_sdkl element

	xml_string = xml_string + " <ti_attribute id=\"" +
		row_id + "\" quant=\"" + quant_row + "\" type=\"Attributes\"> ";
	for (i = 0; i < row_attributes.GetSize (); i++)
	{
		xml_string = xml_string + " <ti_category value=\""
			+ row_attributes.GetAt (i) + "\"/> ";
	}
	xml_string = xml_string + " </ti_attribute> ";

	xml_string = xml_string + " <ti_attribute id=\"" +
		col_id + "\" quant=\"" + quant_col + "\" type=\"Attributes\"> ";
	for (i = 0; i < column_attributes.GetSize (); i++)
	{
		xml_string = xml_string + " <ti_category value=\""
			+ column_attributes.GetAt (i) + "\"/> ";
	}
	xml_string = xml_string + " </ti_attribute> ";

	xml_string = xml_string + "<ti_cedent  id=\"" + c_id + "\"  type=\"Condition\"> ";
    xml_string += format_cedent (condition);
	xml_string = xml_string + "</ti_cedent> ";

	xml_string = xml_string + "<ti_cedent  id=\"" + s1_id + "\"  type=\"First set\"> ";
    xml_string += format_cedent (set1);
	xml_string = xml_string + "</ti_cedent> ";

	xml_string = xml_string + "<ti_cedent  id=\"" + s2_id + "\"  type=\"Second set\"> ";
    xml_string += format_cedent (set2);
	xml_string = xml_string + "</ti_cedent> ";

	return xml_string;
}

int Hyp_SDKL_Meta::get_sum1 ()
{
	int s = 0;
	int i;
	int j;

	for (i = 0; i < table1.GetSize (); i++)
		for (j = 0; j < table1.GetAt (i)->GetSize (); j++)
			s += table1.GetAt (i)->GetAt (j);

	return s;
}

int Hyp_SDKL_Meta::get_max1 ()
{
	int m = table1.GetAt (0)->GetAt (0);
	int i;
	int j;
	for (i = 0; i < table1.GetSize (); i++)
		for (j = 0; j < table1.GetAt (i)->GetSize (); j++)
			if (table1.GetAt (i)->GetAt (j) > m) m = table1.GetAt (i)->GetAt (j);

	return m;
}

CString Hyp_SDKL_Meta::get_min1 ()
{
	int m = table1.GetAt (0)->GetAt (0);
	int i;
	int j;
	CString hlp;

	for (i = 0; i < table1.GetSize (); i++)
		for (j = 0; j < table1.GetAt (i)->GetSize (); j++)
			if (table1.GetAt (i)->GetAt (j) < m) m = table1.GetAt (i)->GetAt (j);

	hlp.Format ("%d", m);
	return hlp;
}

int Hyp_SDKL_Meta::get_row_sum (Tint_Tab * tab, int row)
{
	int i;
	int sum = 0;
	for (i = 0; i < tab->GetAt (row)->GetSize (); i++)
		sum += tab->GetAt (row)->GetAt (i);
	return sum;
}

int Hyp_SDKL_Meta::get_col_sum (Tint_Tab * tab, int col)
{
	int i;
	int sum = 0;
	for (i = 0; i < tab->GetSize (); i++)
		sum += tab->GetAt (i)->GetAt (col);
	return sum;
}

CString Hyp_SDKL_Meta::get_chi_sq1 ()
{
	int sum = get_sum1 ();
	double dValue;
	double dChiSq= 0;
	int i;
	int j;
	int nRk;
	int nSl;

	if ( sum == 0) return "";//to check

	for (i = 0; i < table1.GetSize () ; i++)
	{
		nRk= get_row_sum (&table1, i);

		for (j = 0; j < table1.GetAt (i)->GetSize (); j++)
		{
			nSl= get_col_sum (&table1, j);

			if ( nRk != 0 &&
				 nSl != 0)
			{
				dValue= (double)(table1.GetAt (i)->GetAt (j))- ((double)nRk)*nSl/((double)sum);
				dChiSq+= (dValue*dValue)/(((double)nRk)*nSl);
			}
		}
	}
	return (LPCTSTR) (_bstr_t) (sum * dChiSq);
}

CString Hyp_SDKL_Meta::get_fnc_s1 ()
{
	int nTotalSum = get_sum1 ();
	if ( nTotalSum == 0) return "";

	double dSum = 0;
	int i;
	int j;
	int nMax;
	int dValue;
	for (i = 0; i < table1.GetSize (); i++)
	{
		nMax= 0;
		for (j = 0; j < table1.GetAt (i)->GetSize (); j++)
		{
			dValue= table1.GetAt (i)->GetAt (j);
			if ( dValue > nMax) nMax = dValue;
		}
		dSum += nMax;
	}
	return (LPCTSTR) (_bstr_t) (dSum / nTotalSum);
}

CString Hyp_SDKL_Meta::get_fnc_r1 ()
{
	int nTotalSum= get_sum1 ();
	if ( nTotalSum == 0) return "";

	double dSum= 0;
	int i;
	int j;
	int nMax;
	int nValue;
	for (i = 0; i < table1.GetSize (); i++)
	{
		nMax= 0;
		for (j = 0; j < table1.GetAt (i)->GetSize (); j++)
		{
			nValue = table1.GetAt (i)->GetAt (j);
			if ( nValue > nMax) nMax = nValue;
		}
		dSum += nMax * get_row_sum (&table1, i);
	}
	return (LPCTSTR) (_bstr_t) (dSum / (((double)nTotalSum)* nTotalSum));
}

double Hyp_SDKL_Meta::get_h_c1 ()
{
	double dSum= get_sum1 ();
	if ( dSum == 0) return 0.0;

	double dLog2= log((double) 2);
	int j;
	int nSl;
	double dValue;

	double dHC= 0;
	for (j = 0; j < table1.GetAt (0)->GetSize (); j++)
	{
		nSl = get_col_sum (&table1, j);

		if ( nSl != 0)
		{
			dValue = (nSl/dSum) * (log(nSl/dSum)/dLog2);
			dHC += dValue;
		}
	}

	dHC = -dHC;

	return dHC;
}

double Hyp_SDKL_Meta::get_h_r1 ()
{
	double dSum= get_sum1 ();
	if ( dSum == 0) return 0.0;

	double dLog2= log((double) 2);
	int i;
	int nRk;
	double dValue;

	double dHR= 0;
	for (i= 0; i < table1.GetSize (); i++)
	{
		nRk= get_row_sum (&table1, i);

		if ( nRk != 0)
		{
			dValue= (nRk/dSum)*(log(nRk/dSum)/dLog2);
			dHR+= dValue;
		}
	}

	dHR= -dHR;

	return dHR;
}

double Hyp_SDKL_Meta::get_h_c_r1 ()
{
	double dSum= get_sum1 ();
	if ( dSum == 0) return 0.0;

	double dLog2= log((double) 2);
	int i;
	int j;
	int nRk;
	int nSl;
	double dHAVk;
	double dValueF;
	double dValue;

	double dHA = 0;
	for (i = 0; i < table1.GetSize (); i++)
	{
		nRk = get_row_sum (&table1, i);

		dHAVk = 0;
		if ( nRk != 0)
		{
			for (j = 0; j < table1.GetAt (i)->GetSize (); j++)
			{
				nSl = get_col_sum (&table1, j);

				dValueF = (double) table1.GetAt (i)->GetAt (j);
				if ( dValueF != 0)
				{
					dValue = (dValueF / nRk) * (log(dValueF / nRk) / dLog2);
					dHAVk += dValue;
				}
			}
			dHAVk = -dHAVk;

			dHA += nRk*dHAVk/dSum;
		}
	}

	return dHA;
}

CString Hyp_SDKL_Meta::get_mi1 ()
{
	double dHC = get_h_c1 ();

	double dHR = get_h_r1 ();

	double dHCR = get_h_c_r1 ();

	double dMin = dHC < dHR ? dHC : dHR;
	if (dMin == 0) return "";

	double dICR = (dHC - dHCR)/dMin;

	return (LPCTSTR) (_bstr_t) dICR;
}

CString Hyp_SDKL_Meta::get_aic1 ()
{
	double dSum = get_sum1 ();
	if ( dSum == 0) return "";

	double dNl= 0.0;
	int j;
	int i;
	int nSl;
	int nRk;
	int nValue;

	for (j = 0; j < table1.GetAt (0)->GetSize (); j++)
	{
		nSl = get_col_sum (&table1, j);

		if ( nSl != 0)
		{
			dNl += nSl * log((double) nSl);
		}
	}

	double dDelitel = dSum * log( dSum) - dNl;

	if (dDelitel == 0) return "";

	double dNk = 0.0;
	for (i= 0; i < table1.GetSize (); i++)
	{
		nRk = get_row_sum (&table1, i);

		if ( nRk != 0)
		{
			dNk += nRk * log((double) nRk);
		}
	}
	
	double dAkl= 0.0;
	{
	for (i = 0; i < table1.GetSize (); i++)
	{
		for (j = 0; j < table1.GetAt (0)->GetSize (); j++)
		{
			nValue = table1.GetAt (i)->GetAt (j);
			if ( nValue != 0)
			{
				dAkl += nValue * log((double) nValue);
			}
		}
	}
	}

	double dDelenec = dNk - dAkl;

	double dTheta = 1 - dDelenec / dDelitel;

	return (LPCTSTR) (_bstr_t) dTheta;
}

CString Hyp_SDKL_Meta::get_kend1 ()
{
	double dSum = get_sum1 ();
	if (dSum == 0) return "";

	double dNk2 = 0;
	int i;
	int j;
	int nRk;
	int nSl;
	
	for (i = 0; i < table1.GetSize (); i++)
	{
		nRk= get_row_sum (&table1, i);
		dNk2 += ((double)nRk) * nRk;
	}

	double dNl2 = 0;
	for (j = 0; j < table1.GetAt (0)->GetSize (); j++)
	{
		nSl = get_col_sum (&table1, j);
		dNl2 += ((double)nSl) * nSl;
	}

	double dSum2 = dSum * dSum;

	double dDelitel = sqrt( (dSum2 - dNk2) * (dSum2 - dNl2));

	if (dDelitel == 0) return "";

	double dP = 0;
	double dQ = 0;
	double dPkl;
	double dQkl;
	int i2;
	int j2;

	{
		for (i = 0; i < table1.GetSize (); i++)
		{
			for (j = 0; j < table1.GetAt (0)->GetSize (); j++)
			{
				dPkl= 0;
				dQkl= 0;

				for (i2 = i+ 1; i2 < table1.GetSize (); i2++)
				{
					for (j2 = 0; j2 < table1.GetAt (0)->GetSize (); j2++)
					{ 
						if (j2 < j) dQkl += (double)(table1.GetAt (i2)->GetAt (j2));
						if (j2 > j) dPkl += (double)(table1.GetAt (i2)->GetAt (j2));    
					}
				}

				dQ += ((double)(table1.GetAt (i)->GetAt (j))) * dQkl;
				dP += ((double)(table1.GetAt (i)->GetAt (j))) * dPkl;
			}
		}
	}
	double dDelenec= 2 * (dP- dQ);

	double dTauB = dDelenec / dDelitel;

	return (LPCTSTR) (_bstr_t) dTauB;
}

int Hyp_SDKL_Meta::get_sum2 ()
{
	int s = 0;
	int i;
	int j;

	for (i = 0; i < table2.GetSize (); i++)
		for (j = 0; j < table2.GetAt (i)->GetSize (); j++)
			s += table2.GetAt (i)->GetAt (j);

	return s;
}

int Hyp_SDKL_Meta::get_max2 ()
{
	int m = table2.GetAt (0)->GetAt (0);
	int i;
	int j;
	for (i = 0; i < table2.GetSize (); i++)
		for (j = 0; j < table2.GetAt (i)->GetSize (); j++)
			if (table2.GetAt (i)->GetAt (j) > m) m = table2.GetAt (i)->GetAt (j);

	return m;
}

CString Hyp_SDKL_Meta::get_min2 ()
{
	int m = table2.GetAt (0)->GetAt (0);
	int i;
	int j;
	CString hlp;

	for (i = 0; i < table2.GetSize (); i++)
		for (j = 0; j < table2.GetAt (i)->GetSize (); j++)
			if (table2.GetAt (i)->GetAt (j) < m) m = table2.GetAt (i)->GetAt (j);

	hlp.Format ("%d", m);
	return hlp;
}

CString Hyp_SDKL_Meta::get_chi_sq2 ()
{
	int sum = get_sum2 ();
	double dValue;
	double dChiSq= 0;
	int i;
	int j;
	int nRk;
	int nSl;

	if ( sum == 0) return "";

	for (i = 0; i < table2.GetSize () ; i++)
	{
		nRk= get_row_sum (&table2, i);

		for (j = 0; j < table2.GetAt (i)->GetSize (); j++)
		{
			nSl= get_col_sum (&table2, j);

			if ( nRk != 0 &&
				 nSl != 0)
			{
				dValue= (double)(table2.GetAt (i)->GetAt (j))- ((double)nRk)*nSl/((double)sum);
				dChiSq+= (dValue*dValue)/(((double)nRk)*nSl);
			}
		}
	}
	return (LPCTSTR) (_bstr_t) (sum * dChiSq);
}

CString Hyp_SDKL_Meta::get_fnc_s2 ()
{
	int nTotalSum = get_sum2 ();
	if ( nTotalSum == 0) return "";

	double dSum = 0;
	int i;
	int j;
	int nMax;
	int dValue;
	for (i = 0; i < table2.GetSize (); i++)
	{
		nMax= 0;
		for (j = 0; j < table2.GetAt (i)->GetSize (); j++)
		{
			dValue= table2.GetAt (i)->GetAt (j);
			if ( dValue > nMax) nMax = dValue;
		}
		dSum += nMax;
	}
	return (LPCTSTR) (_bstr_t) (dSum / nTotalSum);
}

CString Hyp_SDKL_Meta::get_fnc_r2 ()
{
	int nTotalSum= get_sum2 ();
	if ( nTotalSum == 0) return "";

	double dSum= 0;
	int i;
	int j;
	int nMax;
	int nValue;
	for (i = 0; i < table2.GetSize (); i++)
	{
		nMax= 0;
		for (j = 0; j < table2.GetAt (i)->GetSize (); j++)
		{
			nValue = table2.GetAt (i)->GetAt (j);
			if ( nValue > nMax) nMax = nValue;
		}
		dSum += nMax * get_row_sum (&table2, i);
	}
	return (LPCTSTR) (_bstr_t) (dSum / (((double)nTotalSum)* nTotalSum));
}

double Hyp_SDKL_Meta::get_h_c2 ()
{
	double dSum= get_sum2 ();
	if ( dSum == 0) return 0.0;

	double dLog2= log((double) 2);
	int j;
	int nSl;
	double dValue;

	double dHC= 0;
	for (j = 0; j < table2.GetAt (0)->GetSize (); j++)
	{
		nSl = get_col_sum (&table2, j);

		if ( nSl != 0)
		{
			dValue = (nSl/dSum) * (log(nSl/dSum)/dLog2);
			dHC += dValue;
		}
	}

	dHC = -dHC;

	return dHC;
}

double Hyp_SDKL_Meta::get_h_r2 ()
{
	double dSum= get_sum2 ();
	if ( dSum == 0) return 0.0;

	double dLog2= log((double) 2);
	int i;
	int nRk;
	double dValue;

	double dHR= 0;
	for (i= 0; i < table2.GetSize (); i++)
	{
		nRk= get_row_sum (&table2, i);

		if ( nRk != 0)
		{
			dValue= (nRk/dSum)*(log(nRk/dSum)/dLog2);
			dHR+= dValue;
		}
	}

	dHR= -dHR;

	return dHR;
}

double Hyp_SDKL_Meta::get_h_c_r2 ()
{
	double dSum= get_sum2 ();
	if ( dSum == 0) return 0.0;

	double dLog2= log((double) 2);
	int i;
	int j;
	int nRk;
	int nSl;
	double dHAVk;
	double dValueF;
	double dValue;

	double dHA = 0;
	for (i = 0; i < table2.GetSize (); i++)
	{
		nRk = get_row_sum (&table2, i);

		dHAVk = 0;
		if ( nRk != 0)
		{
			for (j = 0; j < table2.GetAt (i)->GetSize (); j++)
			{
				nSl = get_col_sum (&table2, j);

				dValueF = (double) table2.GetAt (i)->GetAt (j);
				if ( dValueF != 0)
				{
					dValue = (dValueF / nRk) * (log(dValueF / nRk) / dLog2);
					dHAVk += dValue;
				}
			}
			dHAVk = -dHAVk;

			dHA += nRk*dHAVk/dSum;
		}
	}

	return dHA;
}

CString Hyp_SDKL_Meta::get_mi2 ()
{
	double dHC = get_h_c2 ();

	double dHR = get_h_r2 ();

	double dHCR = get_h_c_r2 ();

	double dMin = dHC < dHR ? dHC : dHR;
	if (dMin == 0) return "";

	double dICR = (dHC - dHCR)/dMin;

	return (LPCTSTR) (_bstr_t) dICR;
}

CString Hyp_SDKL_Meta::get_aic2 ()
{
	double dSum = get_sum2 ();
	if ( dSum == 0) return "";

	double dNl= 0.0;
	int j;
	int i;
	int nSl;
	int nRk;
	int nValue;

	for (j = 0; j < table2.GetAt (0)->GetSize (); j++)
	{
		nSl = get_col_sum (&table2, j);

		if ( nSl != 0)
		{
			dNl += nSl * log((double) nSl);
		}
	}

	double dDelitel = dSum * log( dSum) - dNl;

	if (dDelitel == 0) return "";

	double dNk = 0.0;
	for (i= 0; i < table2.GetSize (); i++)
	{
		nRk = get_row_sum (&table2, i);

		if ( nRk != 0)
		{
			dNk += nRk * log((double) nRk);
		}
	}
	
	double dAkl= 0.0;
	{
	for (i = 0; i < table2.GetSize (); i++)
	{
		for (j = 0; j < table2.GetAt (0)->GetSize (); j++)
		{
			nValue = table2.GetAt (i)->GetAt (j);
			if ( nValue != 0)
			{
				dAkl += nValue * log((double) nValue);
			}
		}
	}
	}

	double dDelenec = dNk - dAkl;

	double dTheta = 1 - dDelenec / dDelitel;

	return (LPCTSTR) (_bstr_t) dTheta;
}

CString Hyp_SDKL_Meta::get_kend2 ()
{
	double dSum = get_sum2 ();
	if (dSum == 0) return "";

	double dNk2 = 0;
	int i;
	int j;
	int nRk;
	int nSl;
	
	for (i = 0; i < table2.GetSize (); i++)
	{
		nRk= get_row_sum (&table2, i);
		dNk2 += ((double)nRk) * nRk;
	}

	double dNl2 = 0;
	for (j = 0; j < table2.GetAt (0)->GetSize (); j++)
	{
		nSl = get_col_sum (&table2, j);
		dNl2 += ((double)nSl) * nSl;
	}

	double dSum2 = dSum * dSum;

	double dDelitel = sqrt( (dSum2 - dNk2) * (dSum2 - dNl2));

	if (dDelitel == 0) return "";

	double dP = 0;
	double dQ = 0;
	double dPkl;
	double dQkl;
	int i2;
	int j2;

	{
		for (i = 0; i < table2.GetSize (); i++)
		{
			for (j = 0; j < table2.GetAt (0)->GetSize (); j++)
			{
				dPkl= 0;
				dQkl= 0;

				for (i2 = i+ 1; i2 < table2.GetSize (); i2++)
				{
					for (j2 = 0; j2 < table2.GetAt (0)->GetSize (); j2++)
					{ 
						if (j2 < j) dQkl += (double)(table2.GetAt (i2)->GetAt (j2));
						if (j2 > j) dPkl += (double)(table2.GetAt (i2)->GetAt (j2));    
					}
				}

				dQ += ((double)(table2.GetAt (i)->GetAt (j))) * dQkl;
				dP += ((double)(table2.GetAt (i)->GetAt (j))) * dPkl;
			}
		}
	}
	double dDelenec= 2 * (dP- dQ);

	double dTauB = dDelenec / dDelitel;

	return (LPCTSTR) (_bstr_t) dTauB;
}

CString Hyp_SDKL_Meta::get_da_max ()
{
	int i;
	int j;
	int max = abs (table1.GetAt (0)->GetAt (0) - table2.GetAt (0)->GetAt (0));
	CString hlp;
	for (i = 0; i < table1.GetSize (); i++)
		for (j = 0; j < table1.GetAt (i)->GetSize (); j++)
			if (abs (table1.GetAt (i)->GetAt (j) - table2.GetAt (i)->GetAt (j)) > max)
				max = abs (table1.GetAt (i)->GetAt (j) - table2.GetAt (i)->GetAt (j));
	hlp.Format ("%d", max);
	return hlp;
}

CString Hyp_SDKL_Meta::get_da_sum ()
{
	int i;
	int j;
	int sum = 0;
	CString hlp;
	for (i = 0; i < table1.GetSize (); i++)
		for (j = 0; j < table1.GetAt (i)->GetSize (); j++)
			sum += abs (table1.GetAt (i)->GetAt (j) - table2.GetAt (i)->GetAt (j));
	hlp.Format ("%d", sum);
	return hlp;
}

CString Hyp_SDKL_Meta::get_da_min ()
{
	int i;
	int j;
	int min = abs (table1.GetAt (0)->GetAt (0) - table2.GetAt (0)->GetAt (0));
	CString hlp;
	for (i = 0; i < table1.GetSize (); i++)
		for (j = 0; j < table1.GetAt (i)->GetSize (); j++)
			if (abs (table1.GetAt (i)->GetAt (j) - table2.GetAt (i)->GetAt (j)) < min)
				min = abs (table1.GetAt (i)->GetAt (j) - table2.GetAt (i)->GetAt (j));
	hlp.Format ("%d", min);
	return hlp;
}

CString Hyp_SDKL_Meta::get_dr_sum ()
{
	int i;
	int j;
	double sum = 0.0;
	double sum1 = (double) get_sum1 ();
	double sum2 = (double) get_sum2 ();
	for (i = 0; i < table1.GetSize (); i++)
		for (j = 0; j < table1.GetAt (i)->GetSize (); j++)
		{
			sum += fabs ((table1.GetAt (i)->GetAt (j)) / sum1
			             -
						 (table2.GetAt (i)->GetAt (j)) / sum2);
		}
	return (LPCTSTR) (_bstr_t) sum;
}

CString Hyp_SDKL_Meta::get_dr_min ()
{
	int i;
	int j;
	double sum1 = (double) get_sum1 ();
	double sum2 = (double) get_sum2 ();
	double min =
		fabs ((table1.GetAt (0)->GetAt (0)) / sum1 - (table2.GetAt (0)->GetAt (0)) / sum2);
	for (i = 0; i < table1.GetSize (); i++)
		for (j = 0; j < table1.GetAt (i)->GetSize (); j++)
		{
			if (fabs ((table1.GetAt (i)->GetAt (j)) / sum1
				      -
					  (table2.GetAt (i)->GetAt (j)) / sum2) < min)
				min =
				fabs ((table1.GetAt (i)->GetAt (j)) / sum1
				      -
					  (table2.GetAt (i)->GetAt (j)) / sum2);
		}
	return (LPCTSTR) (_bstr_t) min;
}

CString Hyp_SDKL_Meta::get_dr_max ()
{
	int i;
	int j;
	double sum1 = (double) get_sum1 ();
	double sum2 = (double) get_sum2 ();
	double max =
		fabs ((table1.GetAt (0)->GetAt (0)) / sum1 - (table2.GetAt (0)->GetAt (0)) / sum2);
	for (i = 0; i < table1.GetSize (); i++)
		for (j = 0; j < table1.GetAt (i)->GetSize (); j++)
		{
			if (fabs ((table1.GetAt (i)->GetAt (j)) / sum1
				      -
					  (table2.GetAt (i)->GetAt (j)) / sum2) < max)
				max =
				fabs ((table1.GetAt (i)->GetAt (j)) / sum1
				      - (table2.GetAt (i)->GetAt (j)) / sum2);
		}
	return (LPCTSTR) (_bstr_t) max;
}

CString Data_Matrix_Meta::xml_convert ()
{
	CString xml_string;

	db_name.Replace ("&", "&amp;");
	id.Replace ("&", "&amp;");
	matrix_name.Replace ("&", "&amp;");

	db_name.Replace ("<", "&lt;");
	id.Replace ("<", "&lt;");
	matrix_name.Replace ("<", "&lt;");

	db_name.Replace (">", "&gt;");
	id.Replace (">", "&gt;");
	matrix_name.Replace (">", "&gt;");

	//beginning of the data_matrix element
	xml_string = " <data_matrix id=\"" + id + "\" db_name=\"" + db_name + "\" ";
	xml_string = xml_string + "matrix_name=\"" + matrix_name + "\" ";
	xml_string = xml_string + "record_count=\"" + (LPCSTR) (_bstr_t) record_count + "\" ";
	xml_string = xml_string + "integer_count=\"" + (LPCSTR) (_bstr_t) integer_count + "\" ";
	xml_string = xml_string + "float_count=\"" + (LPCSTR) (_bstr_t) float_count + "\" ";
	xml_string = xml_string + "string_count=\"" + (LPCSTR) (_bstr_t) string_count + "\" ";
	xml_string = xml_string + "boolean_count=\"" + (LPCSTR) (_bstr_t) boolean_count + "\" ";
	xml_string = xml_string + "date_count=\"" + (LPCSTR) (_bstr_t) date_count + "\" ";
	xml_string = xml_string + "/>";

	return xml_string;
}

CString Column_Meta::xml_convert ()
{
	CString xml_string;

	db_name.Replace ("&", "&amp;");
	id.Replace ("&", "&amp;");
	matrix_name.Replace ("&", "&amp;");
	column_name.Replace ("&", "&amp;");
	value_type.Replace ("&", "&amp;");

	db_name.Replace ("<", "&lt;");
	id.Replace ("<", "&lt;");
	matrix_name.Replace ("<", "&lt;");
	column_name.Replace ("<", "&lt;");
	value_type.Replace ("<", "&lt;");

	db_name.Replace (">", "&gt;");
	id.Replace (">", "&gt;");
	matrix_name.Replace (">", "&gt;");
	column_name.Replace (">", "&gt;");
	value_type.Replace (">", "&gt;");

	//beginning of the column element
	xml_string = " <column id=\"" + id + "\" db_name=\"" + db_name + "\" ";
	xml_string = xml_string + "matrix_name=\"" + matrix_name + "\" ";
	xml_string = xml_string + "column_name=\"" + (LPCSTR) (_bstr_t) column_name + "\" ";
	xml_string = xml_string + "value_type=\"" + (LPCSTR) (_bstr_t) value_type + "\" ";
	xml_string = xml_string + "primary_key_position=\"" + (LPCSTR) (_bstr_t) primary_key_position + "\" ";
	xml_string = xml_string + "min=\"" + (LPCSTR) (_bstr_t) min + "\" ";
	xml_string = xml_string + "max=\"" + (LPCSTR) (_bstr_t) max + "\" ";
	xml_string = xml_string + "avg=\"" + (LPCSTR) (_bstr_t) avg + "\" ";
	xml_string = xml_string + "/>";

	return xml_string;
}