//functions and classes for LM Metabase socket

#include "LM_Metabase.h"
#include "comdef.h"

CString Hyp_CF_Meta::xml_convert ()
{
	CString xml_string;

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

	for (int i = 0; i < frequencies.GetSize (); i++)
	{
		xml_string = xml_string + " <c val=\"" + frequencies.GetAt (i) + "\"/> ";
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
    for (i = 0; i < condition.GetSize (); i++)
	{
		if ((i == 0) || (condition.GetAt (i).quant != condition.GetAt (i - 1).quant))
			xml_string = xml_string + "<ti_literal  id=\"" + condition.GetAt (i).id +
				"\"  quant=\"" + condition.GetAt (i).quant +
				"\"  value=\"";
		xml_string = xml_string + condition.GetAt (i).value;
		if ((i < condition.GetSize () - 1)
			&&
			(condition.GetAt (i).quant == condition.GetAt (i + 1).quant))
			xml_string += ", ";
		else
			xml_string += "\"/> ";
	}
	xml_string = xml_string + "</ti_cedent> ";

	return xml_string;
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

	db_name.Replace ("&", "&amp;");
	matrix_name.Replace ("&", "&amp;");
	task_name.Replace ("&", "&amp;");

	db_name.Replace ("<", "&lt;");
	matrix_name.Replace ("<", "&lt;");
	task_name.Replace ("<", "&lt;");

	db_name.Replace (">", "&gt;");
	matrix_name.Replace (">", "&gt;");
	task_name.Replace (">", "&gt;");

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
		if ((i == 0) || (antecedent.GetAt (i).quant != antecedent.GetAt (i - 1).quant))
			xml_string = xml_string + "<ti_literal  id=\"" + antecedent.GetAt (i).id +
				"\"  quant=\"" + antecedent.GetAt (i).quant +
				"\"  value=\"";
		xml_string = xml_string + antecedent.GetAt (i).value;
		if ((i < antecedent.GetSize () - 1)
			&&
			(antecedent.GetAt (i).quant == antecedent.GetAt (i + 1).quant))
			xml_string += ", ";
		else
			xml_string += "\"/> ";
	}
	xml_string = xml_string + "</ti_cedent> ";
	
	//Succedent
	xml_string = xml_string + "<ti_cedent  id=\"" + suc_id + "\"  type=\"Succedent\"> ";
    for (i = 0; i < succedent.GetSize (); i++)
	{
		if ((i == 0) || (succedent.GetAt (i).quant != succedent.GetAt (i - 1).quant))
			xml_string = xml_string + "<ti_literal  id=\"" + succedent.GetAt (i).id +
				"\"  quant=\"" + succedent.GetAt (i).quant +
				"\"  value=\"";
		xml_string = xml_string + succedent.GetAt (i).value;
		if ((i < succedent.GetSize () - 1)
			&&
			(succedent.GetAt (i).quant == succedent.GetAt (i + 1).quant))
			xml_string += ", ";
		else
			xml_string += "\"/> ";
	}
	xml_string = xml_string + "</ti_cedent> ";
	
	//Condition
	xml_string = xml_string + "<ti_cedent  id=\"" + con_id + "\"  type=\"Condition\"> ";
    for (i = 0; i < condition.GetSize (); i++)
	{
		if ((i == 0) || (condition.GetAt (i).quant != condition.GetAt (i - 1).quant))
			xml_string = xml_string + "<ti_literal  id=\"" + condition.GetAt (i).id +
				"\"  quant=\"" + condition.GetAt (i).quant +
				"\"  value=\"";
		xml_string = xml_string + condition.GetAt (i).value;
		if ((i < condition.GetSize () - 1)
			&&
			(condition.GetAt (i).quant == condition.GetAt (i + 1).quant))
			xml_string += ", ";
		else
			xml_string += "\"/> ";
	}
	xml_string = xml_string + "</ti_cedent> ";
		
	return xml_string;
}

CString Hyp_SD4ft_Meta::xml_convert ()
{
	CString xml_string;

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
	int i;
    for (i = 0; i < antecedent.GetSize (); i++)
	{
		if ((i == 0) || (antecedent.GetAt (i).quant != antecedent.GetAt (i - 1).quant))
			xml_string = xml_string + "<ti_literal  id=\"" + antecedent.GetAt (i).id +
				"\"  quant=\"" + antecedent.GetAt (i).quant +
				"\"  value=\"";
		xml_string = xml_string + antecedent.GetAt (i).value;
		if ((i < antecedent.GetSize () - 1)
			&&
			(antecedent.GetAt (i).quant == antecedent.GetAt (i + 1).quant))
			xml_string += ", ";
		else
			xml_string += "\"/> ";
	}
	xml_string = xml_string + "</ti_cedent> ";
	
	//Succedent
	xml_string = xml_string + "<ti_cedent  id=\"" + suc_id + "\"  type=\"Succedent\"> ";
    for (i = 0; i < succedent.GetSize (); i++)
	{
		if ((i == 0) || (succedent.GetAt (i).quant != succedent.GetAt (i - 1).quant))
			xml_string = xml_string + "<ti_literal  id=\"" + succedent.GetAt (i).id +
				"\"  quant=\"" + succedent.GetAt (i).quant +
				"\"  value=\"";
		xml_string = xml_string + succedent.GetAt (i).value;
		if ((i < succedent.GetSize () - 1)
			&&
			(succedent.GetAt (i).quant == succedent.GetAt (i + 1).quant))
			xml_string += ", ";
		else
			xml_string += "\"/> ";
	}
	xml_string = xml_string + "</ti_cedent> ";
	
	//Condition
	xml_string = xml_string + "<ti_cedent  id=\"" + con_id + "\"  type=\"Condition\"> ";
    for (i = 0; i < condition.GetSize (); i++)
	{
		if ((i == 0) || (condition.GetAt (i).quant != condition.GetAt (i - 1).quant))
			xml_string = xml_string + "<ti_literal  id=\"" + condition.GetAt (i).id +
				"\"  quant=\"" + condition.GetAt (i).quant +
				"\"  value=\"";
		xml_string = xml_string + condition.GetAt (i).value;
		if ((i < condition.GetSize () - 1)
			&&
			(condition.GetAt (i).quant == condition.GetAt (i + 1).quant))
			xml_string += ", ";
		else
			xml_string += "\"/> ";
	}
	xml_string = xml_string + "</ti_cedent> ";

	//First set
	xml_string = xml_string + "<ti_cedent  id=\"" + set1_id + "\"  type=\"Condition\"> ";
    for (i = 0; i < set1.GetSize (); i++)
	{
		if ((i == 0) || (set1.GetAt (i).quant != set1.GetAt (i - 1).quant))
			xml_string = xml_string + "<ti_literal  id=\"" + set1.GetAt (i).id +
				"\"  quant=\"" + set1.GetAt (i).quant +
				"\"  value=\"";
		xml_string = xml_string + set1.GetAt (i).value;
		if ((i < set1.GetSize () - 1)
			&&
			(set1.GetAt (i).quant == set1.GetAt (i + 1).quant))
			xml_string += ", ";
		else
			xml_string += "\"/> ";
	}
	xml_string = xml_string + "</ti_cedent> ";

	//Second set
	xml_string = xml_string + "<ti_cedent  id=\"" + set2_id + "\"  type=\"Condition\"> ";
    for (i = 0; i < set2.GetSize (); i++)
	{
		if ((i == 0) || (set2.GetAt (i).quant != set2.GetAt (i - 1).quant))
			xml_string = xml_string + "<ti_literal  id=\"" + set2.GetAt (i).id +
				"\"  quant=\"" + set2.GetAt (i).quant +
				"\"  value=\"";
		xml_string = xml_string + set2.GetAt (i).value;
		if ((i < set2.GetSize () - 1)
			&&
			(set2.GetAt (i).quant == set2.GetAt (i + 1).quant))
			xml_string += ", ";
		else
			xml_string += "\"/> ";
	}
	xml_string = xml_string + "</ti_cedent> ";

	return xml_string;
}