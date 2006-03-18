//functions and classes for LM Metabase socket

#include "LM_Metabase.h"
#include "Hyp_4ft_Recordset.h"
#include "DTD.h"


CString Hyp_4ft_Meta::xml_convert ()
{
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
	xml_string = xml_string + " conf=\"";
	hlp.Format ("%f", conf);
	xml_string = xml_string + hlp + "\" ";
	xml_string = xml_string + " d_conf=\"";
	hlp.Format ("%f", d_conf);
	xml_string = xml_string + hlp + "\" ";
	xml_string = xml_string + " e_conf=\"";
	hlp.Format ("%f", e_conf);
	xml_string = xml_string + hlp + "\" ";
	xml_string = xml_string + " support=\"";
	hlp.Format ("%f", support);
	xml_string = xml_string + hlp + "\" ";
	xml_string = xml_string + " completeness=\"";
	hlp.Format ("%f", completeness);
	xml_string = xml_string + hlp + "\" ";
	xml_string = xml_string + " avg_diff=\"";
	hlp.Format ("%f", avg_diff);
	xml_string = xml_string + hlp + "\" ";
	xml_string = xml_string + " low_bnd_imp=\"";
	hlp.Format ("%f", low_bnd_imp);
	xml_string = xml_string + hlp + "\" ";
	xml_string = xml_string + " up_bnd_imp=\"";
	hlp.Format ("%f", up_bnd_imp);
	xml_string = xml_string + hlp + "\" ";
	xml_string = xml_string + " low_bnd_dbl_imp=\"";
	hlp.Format ("%f", low_bnd_dbl_imp);
	xml_string = xml_string + hlp + "\" ";
	xml_string = xml_string + " up_bnd_dbl_imp=\"";
	hlp.Format ("%f", up_bnd_dbl_imp);
	xml_string = xml_string + hlp + "\" ";
	xml_string = xml_string + " low_bnd_eq=\"";
	hlp.Format ("%f", low_bnd_eq);
	xml_string = xml_string + hlp + "\" ";
	xml_string = xml_string + " up_bnd_eq=\"";
	hlp.Format ("%f", up_bnd_eq);
	xml_string = xml_string + hlp + "\" ";
	xml_string = xml_string + " fisher=\"";
	hlp.Format ("%f", fisher);
	xml_string = xml_string + hlp + "\" ";
	xml_string = xml_string + " chi_sq=\"";
	hlp.Format ("%f", chi_sq);
	xml_string = xml_string + hlp + "\" ";
	if (flag_a) xml_string = xml_string + " antecedent=\"" + ant_id + "\" ";
	if (flag_s) xml_string = xml_string + " succedent=\"" + suc_id + "\" ";
	if (flag_c) xml_string = xml_string + " condition=\"" + con_id + "\"";
	xml_string += "/>  ";
	//end of hyp_4ft element

	//beginning of ti_cedent elements
	//Antecedent
	if (antecedent.GetSize () != 0)
	{
		xml_string = xml_string + "<ti_cedent  id=\"" + ant_id + "\"  type=\"Antecedent\"> ";
		for (int i = 0; i < antecedent.GetSize (); i++)
		{
			xml_string = xml_string + "<ti_literal  id=\"" + antecedent.GetAt (i).id +
				"\"  quant=\"" + antecedent.GetAt (i).quant +
				"\"  value=\"" + antecedent.GetAt (i).value + "\"/> ";
		}
		xml_string = xml_string + "</ti_cedent> ";
	}
	//Succedent
	if (succedent.GetSize () != 0)
	{
		xml_string = xml_string + "<ti_cedent  id=\"" + suc_id + "\"  type=\"Succedent\"> ";
		for (int i = 0; i < succedent.GetSize (); i++)
		{
			xml_string = xml_string + "<ti_literal  id=\"" + succedent.GetAt (i).id +
				"\"  quant=\"" + succedent.GetAt (i).quant +
				"\"  value=\"" + succedent.GetAt (i).value + "\"/> ";
		}
		xml_string = xml_string + "</ti_cedent> ";
	}
	//Condition
	if (condition.GetSize () != 0)
	{
		xml_string = xml_string + "<ti_cedent  id=\"" + con_id + "\"  type=\"Condition\"> ";
		for (int i = 0; i < condition.GetSize (); i++)
		{
			xml_string = xml_string + "<ti_literal  id=\"" + condition.GetAt (i).id +
				"\"  quant=\"" + condition.GetAt (i).quant +
				"\"  value=\"" + condition.GetAt (i).value + "\"/> ";
		}
		xml_string = xml_string + "</ti_cedent> ";
	}
	
	return xml_string;
}