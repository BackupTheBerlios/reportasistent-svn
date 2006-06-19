//functions and classes for LM Metabase socket

#include "LM_Metabase.h"
#include "Hyp_4ft_Recordset.h"
#include "comdef.h"

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

	//beggining of the cedent element
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
	xml_string = xml_string + "sub_cedent_cnt=\"" + sub_cedent_cnt + "\" >";
	for (int i = 0; i < sub_cedents_list.GetSize (); i++)
	{
		xml_string = xml_string +
			"<sub_bool_cedent name=\"" + sub_cedents_list.GetAt (i)->name + "\" ";
		xml_string = xml_string +
			"literal_cnt=\"" + sub_cedents_list.GetAt (i)->literal_cnt + "\" ";
		xml_string = xml_string +
			"length=\"" + sub_cedents_list.GetAt (i)->length + "\" >";
		for (int j = 0; j < sub_cedents_list.GetAt (i)->lit_list.GetSize (); j++)
		{
			xml_string = xml_string +
				"<literal underlying_attribute=\"" +
				sub_cedents_list.GetAt (i)->lit_list.GetAt (j).underlying_attribute + "\" ";
			xml_string = xml_string +
				"category_cnt=\"" +
				sub_cedents_list.GetAt (i)->lit_list.GetAt (j).category_cnt + "\" ";
			xml_string = xml_string +
				"missing_type=\"" +
				sub_cedents_list.GetAt (i)->lit_list.GetAt (j).missing_type + "\" ";
			xml_string = xml_string +
				"coefficient_type=\"" +
				sub_cedents_list.GetAt (i)->lit_list.GetAt (j).coefficient_type + "\" ";
			xml_string = xml_string +
				"length=\"" +
				sub_cedents_list.GetAt (i)->lit_list.GetAt (j).length + "\" ";
			xml_string = xml_string +
				"gace=\"" +
				sub_cedents_list.GetAt (i)->lit_list.GetAt (j).gace + "\" ";
			xml_string = xml_string +
				"literal_type=\"" +
				sub_cedents_list.GetAt (i)->lit_list.GetAt (j).literal_type + "\" ";
			xml_string = xml_string +
				"equivalence_class=\"" +
				sub_cedents_list.GetAt (i)->lit_list.GetAt (j).equivalence_class + "\"/> ";
		}
		xml_string = xml_string + "</sub_bool_cedent> ";
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
	int i;
    for (i = 0; i < antecedent.GetSize (); i++)
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