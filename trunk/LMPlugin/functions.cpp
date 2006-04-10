// implementace funkci pro vyrizeni pozadavku na AP v zasuvce pro LM
// functions.h
#include "functions.h"
#include "Hyp_4ft_Recordset.h"
#include "Tcategory_Recordset.h"
#include "TCatDefEnum.h"
#include "TCatDefInt.h"
#include "TCatOrder.h"
#include "LM_Metabase.h"


//dedek: docasne
/*****/
//Deda: potreba pro MSXML - potreba pro muj testovci vystup jinak (az bude lesi vystup) mozno smazat
#include <afxdb.h>

#import <msxml3.dll>
using namespace MSXML2;
//vlozi namespace MSXML2;


//dedek: testovaci vystup neni to moc usetreny tak bacha :)
BOOL dedek_performLM(void * hSource, const char* AP, BSTR* result)
{
	CDatabase * db = (CDatabase *) hSource;

	CString ft = AP;

	if (ft != "hyp_4ft") return FALSE;

	IXMLDOMDocumentPtr dom;
	dom.CreateInstance(_T("Msxml2.DOMDocument"));
	dom->async = VARIANT_FALSE; // default - true,
	
	dom->load((LPCTSTR) _T("../XML/4ft_hyp.xml"));

	IXMLDOMElementPtr el_hyp = dom->selectSingleNode("/active_list/hyp_4ft");

	el_hyp->setAttribute("db_name", (LPCTSTR) db->GetDatabaseName());

	* result = dom->xml;

	return TRUE;
}

/****/

// --- AP Kategorie

CString fLMCategory(void* hSource)
{
	CString buf = "";
	CString hlp;
	CString hlp1;
	CString db_name = ((CDatabase *) hSource)->GetDatabaseName ();

	long cat_id;
	int count = 0;
	int ord = 0;

//	BOOL end;

	TCategory_Meta_Array list;
	Category_Meta * ptcat;

	Tcategory_Recordset rs ((CDatabase *) hSource);
	TCatDefEnum rs_def_enum ((CDatabase *) hSource);
	TCatDefInt rs_def_int_l ((CDatabase *) hSource);
	TCatDefInt rs_def_int_r ((CDatabase *) hSource);
	TCatOrder rs_ord ((CDatabase *) hSource);

	TCatDefArray def;

	CString subqenum;
	CString subqintervall;
	CString subqintervalr;
	CString qord;

	LPCTSTR q =	
		"SELECT * \
		 FROM	tmAttribute, tmCategory, tmMatrix, tmQuantity, tsBoolType, tsCategorySubType \
		 WHERE tmCategory.QuantityID=tmQuantity.QuantityID \
			AND tmQuantity.AttributeID=tmAttribute.AttributeID \
			AND tmAttribute.MatrixID=tmMatrix.MatrixID \
			AND tmCategory.CategorySubTypeID=tsCategorySubType.CategorySubTypeID \
			AND tmCategory.BoolTypeID = tsBoolType.BoolTypeID \
			ORDER BY tmCategory.CategoryID";

	if (rs.Open(AFX_DB_USE_DEFAULT_TYPE, q))
	{
		//iteration on query results
		while (!rs.IsEOF())
		{
			ptcat = new (Category_Meta);
			ptcat->attr_name = rs.m_Name;
			ptcat->ctgr_name = rs.m_Name2;
			ptcat->ctgr_type = rs.m_Name6;
			ptcat->db_name = db_name;
			ptcat->matrix_name = rs.m_Name3;
			cat_id = rs.m_CategoryID;
			hlp.Format ("%d", cat_id);
			ptcat->id = "cat" + hlp;
			ptcat->ctgr_bool_type = rs.m_Name5;
			if (rs.m_Name6 == "Enumeration")
			{
				subqenum =
					"SELECT * \
					 FROM tmCategoryEnumValue, tmValue, tsValueSubType \
					 WHERE tmCategoryEnumValue.CategoryID=" + hlp +
					  " AND tmCategoryEnumValue.ValueID=tmValue.ValueID \
						AND tmValue.ValueSubTypeID=tsValueSubType.ValueSubTypeID";
				if (rs_def_enum.Open(AFX_DB_USE_DEFAULT_TYPE, subqenum))
				{
					while (!rs_def_enum.IsEOF ())
					{
						if (rs_def_enum.m_Name == "Long integer")
							hlp.Format ("%d", rs_def_enum.m_ValueLong);
						else if (rs_def_enum.m_Name == "Float")
							hlp = (LPCTSTR) (_bstr_t) rs_def_enum.m_ValueFloat;
						else if (rs_def_enum.m_Name == "String")
							hlp = rs_def_enum.m_ValueString;
						else if (rs_def_enum.m_Name == "Boolean")
							if (rs_def_enum.m_ValueBool) hlp = "TRUE";
							else hlp = "FALSE";
						else if (rs_def_enum.m_Name == "Date")
							hlp = rs_def_enum.m_ValueDate.Format ("%d/%m/%Y %H:%M:%S");
						ptcat->ctgr_def.Add (hlp);
						count++;
						rs_def_enum.MoveNext ();
					}
					ptcat->def_length = count;
					count = 0;
					rs_def_enum.Close ();
				}
				else return "";
			}
			else if ((rs.m_Name6 == "Interval") || (rs.m_Name6 == "Fuzzy interval"))
			{
				subqintervall =
					"SELECT * \
					 FROM tmInterval, tmValue, tsBracketType, tsValueSubType \
					 WHERE tmInterval.CategoryID=" + hlp +
					   " AND tmInterval.FromValueID=tmValue.ValueID \
						AND tmValue.ValueSubTypeID=tsValueSubType.ValueSubTypeID \
						AND tmInterval.LeftBracketTypeID=tsBracketType.BracketTypeID";
				subqintervalr =
					"SELECT * \
					 FROM tmInterval, tmValue, tsBracketType, tsValueSubType \
					 WHERE tmInterval.CategoryID=" + hlp +
					   " AND tmInterval.ToValueID=tmValue.ValueID \
						AND tmValue.ValueSubTypeID=tsValueSubType.ValueSubTypeID \
						AND tmInterval.RightBracketTypeID=tsBracketType.BracketTypeID";
				if ((rs_def_int_l.Open(AFX_DB_USE_DEFAULT_TYPE, subqintervall))
					&&
					(rs_def_int_r.Open(AFX_DB_USE_DEFAULT_TYPE, subqintervalr)))
				{
					while ((!rs_def_int_l.IsEOF ()) && (!rs_def_int_r.IsEOF ()))
					{
						hlp1 = rs_def_int_l.m_LeftBracket;
						if (rs_def_int_l.m_Name2 == "Long integer")
							hlp.Format ("%d", rs_def_int_l.m_ValueLong);
						else if (rs_def_int_l.m_Name2 == "Float")
							hlp = (LPCTSTR) (_bstr_t) rs_def_int_l.m_ValueFloat;
						else if (rs_def_int_l.m_Name2 == "String")
							hlp = rs_def_int_l.m_ValueString;
						else if (rs_def_int_l.m_Name2 == "Boolean")
							if (rs_def_int_l.m_ValueBool) hlp = "TRUE";
							else hlp = "FALSE";
						else if (rs_def_int_l.m_Name2 == "Date")
							hlp = rs_def_int_l.m_ValueDate.Format ("%d/%m/%Y %H:%M:%S");
						hlp1 += hlp;
						hlp1 += ";";
						if (rs_def_int_r.m_Name2 == "Long integer")
							hlp.Format ("%d", rs_def_int_r.m_ValueLong);
						else if (rs_def_int_r.m_Name2 == "Float")
							hlp = (LPCTSTR) (_bstr_t) rs_def_int_r.m_ValueFloat;
						else if (rs_def_int_r.m_Name2 == "String")
							hlp = rs_def_int_r.m_ValueString;
						else if (rs_def_int_r.m_Name2 == "Boolean")
							if (rs_def_int_r.m_ValueBool) hlp = "TRUE";
							else hlp = "FALSE";
						else if (rs_def_int_r.m_Name2 == "Date")
							hlp = rs_def_int_r.m_ValueDate.Format ("%d/%m/%Y %H:%M:%S");
						hlp1 += hlp;
						hlp1 += rs_def_int_r.m_RightBracket;
						hlp1.Replace (">", "&gt;");
						hlp1.Replace ("<", "&lt;");
						ptcat->ctgr_def.Add (hlp1);
						count++;
						rs_def_int_l.MoveNext ();
						rs_def_int_r.MoveNext ();
					}
					ptcat->def_length = count;
					count = 0;
					rs_def_int_l.Close ();
					rs_def_int_r.Close ();
				}
				else return "";
			}
			else return "";
			//find the order of category according to its ID \
			for category frequency matching
/*			end = FALSE;
			ord = 0;
			qord =
				"SELECT * \
				 FROM tmAttribute, tmCategory, tmQuantity \
				 WHERE tmAttribute.Name=" + rs.m_Name + " \
					AND tmAttribute.AttributeID=tmQuantity.AttributeID \
					AND tmQuantity.QuantityID=tmCategory.QuantityID \
				 ORDER BY tmCategory.CategoryID";
			if (rs_ord.Open(AFX_DB_USE_DEFAULT_TYPE, qord))
			{
				while ((!rs_ord.IsEOF ()) && !end)
				{
					if (rs_ord.m_CategoryID == rs.m_CategoryID) end = TRUE;
					ord++;
					rs_ord.MoveNext ();
				}
				rs_ord.Close ();
			}
			else return "";
*/			//find the frequency of category, if exists
			//todo
			ptcat->ctgr_freq = "N/A";
			list.Add (ptcat);
			rs.MoveNext();
		}
		rs.Close();
	}
	else return "";

	//creation of xml string
	//load DTD
	FILE * x = fopen ("../XML/dtd.dtd", "r");
	CString buf1;
	while (fscanf (x, "%s", buf1) != EOF)
	{
		buf = buf + (const char *) buf1 + " ";
	}
	fclose (x);
	//create xml data
	buf = buf + " <active_list> ";
	for (int i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert ();
	}
	buf += " </active_list>";
	//just for test - creates a xml file with all categories
	FILE * f = fopen ("test.xml", "w");
	fprintf (f, "%s", buf);
	fclose (f);


	AfxMessageBox(buf);

	return buf;
}


// --- AP 4ft-hypoteza

CString fLM4fthyp(void * hSource)
{
	CString buf = "";
	CString id_hlp;
	THyp_4ft_Meta_Array list;
	Hyp_4ft_Recordset rs ((CDatabase *) hSource);
	Hyp_4ft_Meta * pthyp;
	long h_id;
	long m_id;
	long t_id;
	long l_id;
	long c_id;
	long h_id_tst = 0;//test variable - values from previous iteration

	BOOL neg_lit;
	CString neg_lit_smbl;
	
	CString ced_name;
	CString q_name;
	CString q_value;
	LPCTSTR q = "SELECT tiHypothesis.HypothesisID, taTask.MatrixID, tmMatrix.Name, taTask.TaskID, taTask.Name, tiHypothesis.FreqA, tiHypothesis.FreqB, tiHypothesis.FreqC, tiHypothesis.FreqD, tiLiteralI.LiteralIID, tiLiteralI.Negation, tsCedentType.Name, tmCategory.CategoryID, tmQuantity.Name, tmCategory.Name FROM tsCedentType, tiHypothesis, taTask, tmMatrix, tiLiteralI, tiCoefficient, tmCategory, tmQuantity WHERE tiCoefficient.TaskID=taTask.TaskID AND taTask.MatrixID=tmMatrix.MatrixID AND tiHypothesis.HypothesisID=tiLiteralI.HypothesisID AND tiLiteralI.LiteralIID=tiCoefficient.LiteralIID AND tiCoefficient.CategoryID=tmCategory.CategoryID AND tmCategory.QuantityID=tmQuantity.QuantityID AND tsCedentType.CedentTypeID=tiLiteralI.CedentTypeID ORDER BY tiHypothesis.HypothesisID, tiLiteralI.CedentTypeID";
	//load data from metabase
	if (rs.Open(AFX_DB_USE_DEFAULT_TYPE, q))
	{
		//iteration on query results
		while (!rs.IsEOF())
		{
			h_id = rs.m_HypothesisID;
			m_id = rs.m_MatrixID;
			t_id = rs.m_TaskID;
			l_id = rs.m_LiteralID;
			neg_lit = rs.m_Negation;
			ced_name = rs.m_CedentTypeName;
			c_id = rs.m_CategoryID;
			q_name = rs.m_QuantityID;
			q_value = rs.m_Qvalue;
			q_value.Replace ("<", "&lt;");
			if (h_id != h_id_tst)
			{
				pthyp = new (Hyp_4ft_Meta);
				pthyp->flag_a = pthyp->flag_s = pthyp->flag_c = FALSE;
				id_hlp.Format ("%d", h_id);
				pthyp->id = "hyp4ft" + id_hlp;
				pthyp->db_name = ((CDatabase *) hSource)->GetDatabaseName ();
				pthyp->matrix_name = rs.m_MatrixName;
				pthyp->task_name = rs.m_TaskName;
				pthyp->a = rs.m_FreqA;
				pthyp->b = rs.m_FreqB;
				pthyp->c = rs.m_FreqC;
				pthyp->d = rs.m_FreqD;
				pthyp->conf = ((double)rs.m_FreqA/(rs.m_FreqA+rs.m_FreqB));
				pthyp->d_conf = ((double)rs.m_FreqA/(rs.m_FreqA+rs.m_FreqB+rs.m_FreqC));
				pthyp->e_conf = ((double)(rs.m_FreqA+rs.m_FreqD)/(rs.m_FreqA+rs.m_FreqB+rs.m_FreqC+rs.m_FreqD));
				pthyp->support = ((double)rs.m_FreqA/(rs.m_FreqA+rs.m_FreqB+rs.m_FreqC+rs.m_FreqD));
				pthyp->completeness = ((double)rs.m_FreqA/(rs.m_FreqA+rs.m_FreqC));
				pthyp->avg_diff = ((double)rs.m_FreqA*(rs.m_FreqA+rs.m_FreqB+rs.m_FreqC+rs.m_FreqD)/((rs.m_FreqA+rs.m_FreqB)*(rs.m_FreqA+rs.m_FreqC))- 1);
				//not implemented yet, therefore all the values are 0
				pthyp->low_bnd_imp = 0;
				pthyp->up_bnd_imp = 0;
				pthyp->low_bnd_dbl_imp = 0;
				pthyp->up_bnd_dbl_imp = 0;
				pthyp->low_bnd_eq = 0;
				pthyp->up_bnd_eq = 0;
				pthyp->fisher = 0;
				pthyp->chi_sq = 0;

				pthyp->ant_id = "ant" + pthyp->id;
				pthyp->suc_id = "suc" + pthyp->id;
				pthyp->con_id = "con" + pthyp->id;

				list.Add (pthyp);
			}

			if (ced_name == "Antecedent")
			{
				Hyp_tiLiteral x;
				pthyp->flag_a = TRUE;
				id_hlp.Format ("%d", l_id);
				x.id = "tiLit" + id_hlp;
				id_hlp.Format ("%d", c_id);
				x.id = x.id + id_hlp;
				if (neg_lit) neg_lit_smbl = "¬"; else neg_lit_smbl = "";
				x.quant = neg_lit_smbl + q_name;
				x.value = q_value;
				pthyp->antecedent.Add (x);
			}
			else if (ced_name == "Succedent")
			{
				Hyp_tiLiteral x;
				pthyp->flag_s = TRUE;
				id_hlp.Format ("%d", l_id);
				x.id = "tiLit" + id_hlp;
				id_hlp.Format ("%d", c_id);
				x.id = x.id + id_hlp;
				if (neg_lit) neg_lit_smbl = "¬"; else neg_lit_smbl = "";
				x.quant = neg_lit_smbl + q_name;
				x.value = q_value;
				pthyp->succedent.Add (x);
			}
			else if (ced_name == "Condition")
			{
				Hyp_tiLiteral x;
				pthyp->flag_c = TRUE;
				id_hlp.Format ("%d", l_id);
				x.id = "tiLit" + id_hlp;
				id_hlp.Format ("%d", c_id);
				x.id = x.id + id_hlp;
				if (neg_lit) neg_lit_smbl = "¬"; else neg_lit_smbl = "";
				x.quant = neg_lit_smbl + q_name;
				x.value = q_value;
				pthyp->condition.Add (x);
			}
			else return "";//error

			rs.MoveNext();
			h_id_tst = h_id;
		}
		rs.Close();
	}
	else return "";
	
	//creation of xml string
	//load DTD
	FILE * x = fopen ("../XML/dtd.dtd", "r");
	CString buf1;
	while (fscanf (x, "%s", buf1) != EOF)
	{
		buf = buf + (const char *) buf1 + " ";
	}
	fclose (x);
	//create xml data
	buf = buf + " <active_list> ";
	for (int i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert ();
	}
	buf += " </active_list>";
	//just for test - creates a xml file with all hypothesis
/*	FILE * f = fopen ("test.xml", "w");
	fprintf (f, "%s", buf);
	fclose (f);
*/
	return buf;
}



