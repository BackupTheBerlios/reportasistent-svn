//functions and classes for LM Metabase socket

#include "LM_Metabase.h"
#include "Hyp_4ft_Recordset.h"
#include "comdef.h"

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
	for (int i = 0; i < ctgr_def.GetSize (); i++)
		ctgr_def.GetAt (i).Replace ("&", "&amp;");

	attr_name.Replace ("<", "&lt;");
	ctgr_bool_type.Replace ("<", "&lt;");
	ctgr_freq.Replace ("<", "&lt;");
	ctgr_name.Replace ("<", "&lt;");
	ctgr_type.Replace ("<", "&lt;");
	db_name.Replace ("<", "&lt;");
	id.Replace ("<", "&lt;");
	matrix_name.Replace ("<", "&lt;");
	//todo in functions.cpp
	for (i = 0; i < ctgr_def.GetSize (); i++)
		ctgr_def.GetAt (i).Replace ("<", "&lt;");

	attr_name.Replace (">", "&gt;");
	ctgr_bool_type.Replace (">", "&gt;");
	ctgr_freq.Replace (">", "&gt;");
	ctgr_name.Replace (">", "&gt;");
	ctgr_type.Replace (">", "&gt;");
	db_name.Replace (">", "&gt;");
	id.Replace (">", "&gt;");
	matrix_name.Replace (">", "&gt;");
	for (i = 0; i < ctgr_def.GetSize (); i++)
		ctgr_def.GetAt (i).Replace (">", "&gt;");

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
	for (i = 0; i < ctgr_def.GetSize (); i++)
		xml_string = xml_string + "<ctgr_def definition=\"" + ctgr_def.GetAt (i) + "\" /> ";
	xml_string = xml_string + "</category>";
	return xml_string;
}

CString Hyp_4ft_Meta::xml_convert ()
{
	//todo: replace <,>, &
	CString xml_string;
	CString hlp;
	//beginning of the hyp_4ft element
	xml_string = " <hyp_4ft id=\"" + id + "\" db_name=\"" + db_name + "\" ";
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
	xml_string = xml_string + " low_bnd_imp=\"" + (LPCTSTR) (_bstr_t) low_bnd_imp + "\" ";
	xml_string = xml_string + " up_bnd_imp=\"" + (LPCTSTR) (_bstr_t) up_bnd_imp + "\" ";
	xml_string = xml_string + " low_bnd_dbl_imp=\"" + (LPCTSTR) (_bstr_t) low_bnd_dbl_imp + "\" ";
	xml_string = xml_string + " up_bnd_dbl_imp=\"" + (LPCTSTR) (_bstr_t) up_bnd_dbl_imp + "\" ";
	xml_string = xml_string + " low_bnd_eq=\"" + (LPCTSTR) (_bstr_t) low_bnd_eq + "\" ";
	xml_string = xml_string + " up_bnd_eq=\"" + (LPCTSTR) (_bstr_t) up_bnd_eq + "\" ";
	xml_string = xml_string + " fisher=\"" + (LPCTSTR) (_bstr_t) fisher + "\" ";
	xml_string = xml_string + " chi_sq=\"" + (LPCTSTR) (_bstr_t) chi_sq + "\" ";
	xml_string = xml_string + " antecedent=\"" + ant_id + "\" ";
	xml_string = xml_string + " succedent=\"" + suc_id + "\" ";
	xml_string = xml_string + " condition=\"" + con_id + "\"";
	xml_string += "/>  ";
	//end of hyp_4ft element

	//beginning of ti_cedent elements
	//Antecedent
	xml_string = xml_string + "<ti_cedent  id=\"" + ant_id + "\"  type=\"Antecedent\"> ";
	for (int i = 0; i < antecedent.GetSize (); i++)
	{
		xml_string = xml_string + "<ti_literal  id=\"" + antecedent.GetAt (i).id +
			"\"  quant=\"" + antecedent.GetAt (i).quant +
			"\"  value=\"" + antecedent.GetAt (i).value + "\"/> ";
	}
	xml_string = xml_string + "</ti_cedent> ";
	
	//Succedent
	xml_string = xml_string + "<ti_cedent  id=\"" + suc_id + "\"  type=\"Succedent\"> ";
	for (i = 0; i < succedent.GetSize (); i++)
	{
		xml_string = xml_string + "<ti_literal  id=\"" + succedent.GetAt (i).id +
			"\"  quant=\"" + succedent.GetAt (i).quant +
			"\"  value=\"" + succedent.GetAt (i).value + "\"/> ";
	}
	xml_string = xml_string + "</ti_cedent> ";
	
	//Condition
	xml_string = xml_string + "<ti_cedent  id=\"" + con_id + "\"  type=\"Condition\"> ";
	for (i = 0; i < condition.GetSize (); i++)
	{
		xml_string = xml_string + "<ti_literal  id=\"" + condition.GetAt (i).id +
			"\"  quant=\"" + condition.GetAt (i).quant +
			"\"  value=\"" + condition.GetAt (i).value + "\"/> ";
	}
	xml_string = xml_string + "</ti_cedent> ";
		
	return xml_string;
}