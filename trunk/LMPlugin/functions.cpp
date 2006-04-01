// implementace funkci pro vyrizeni pozadavku na AP v zasuvce pro LM
// functions.h
#include "functions.h"
#include "Hyp_4ft_Recordset.h"
#include "Category_Recordset.h"
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
	CString db_name = ((CDatabase *) hSource)->GetDatabaseName ();

	long cat_id;

	TCategory_Meta_Array list;
	Category_Meta * ptcat;

	Category_Recordset rs ((CDatabase *) hSource);
	LPCTSTR q = "SELECT tmMatrix.Name, tmAttribute.Name, tmCategory.Name, tmCategory.CategoryID, tsCategorySubType.Name FROM tmCategory, tmQuantity, tmAttribute, tmMatrix, tsCategorySubType WHERE tmCategory.QuantityID=tmQuantity.QuantityID AND tmQuantity.AttributeID=tmAttribute.AttributeID AND tmAttribute.MatrixID=tmMatrix.MatrixID AND tmCategory.CategorySubTypeID=tsCategorySubType.CategorySubTypeID ORDER BY tmCategory.CategoryID";
	
	if (rs.Open(AFX_DB_USE_DEFAULT_TYPE, q))
	{
		//iteration on query results
		while (!rs.IsEOF())
		{
			ptcat = new (Category_Meta);
			ptcat->attr_name = rs.m_Attr_Name;
			ptcat->ctgr_name = rs.m_Ctgr_Name;
			ptcat->ctgr_type = rs.m_Ctgr_tp_Name;
			ptcat->db_name = db_name;
			ptcat->matrix_name = rs.m_Matrix_Name;
			cat_id = rs.m_CategoryID;
			hlp.Format ("%d", cat_id);
			ptcat->id = "cat" + hlp;
			list.Add (ptcat);
			hlp.Format("%s %s %s %s %d \n", rs.m_Attr_Name, rs.m_Ctgr_Name, rs.m_Ctgr_tp_Name, rs.m_Matrix_Name, rs.m_CategoryID);
			buf += hlp;
			rs.MoveNext();
		}
		rs.Close();
	}
	else return "";
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
// for call and test only
//    buf = fLMCategory(hSource);
	//just for test - creates a xml file with all hypothesis
	FILE * f = fopen ("test.xml", "w");
	fprintf (f, "%s", buf);
	fclose (f);

	return buf;
}



