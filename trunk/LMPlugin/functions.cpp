// implementace funkci pro vyrizeni pozadavku na AP v zasuvce pro LM
// functions.h
#include "functions.h"
#include "Hyp_4ft_Recordset.h"
#include "Tcategory_Recordset.h"
#include "TCatDefEnum.h"
#include "TCatDefInt.h"
#include "TCatOrder.h"
#include "TAttribute_Recordset.h"
#include "TCategory_list.h"
#include "LM_Metabase.h"
#include "Bool_Cedent_Recordset.h"
#include "Equivalence_Lit_Rs.h"
#include "TCategory_Scan.h"
#include "TEmpty_Cedents_Recordset.h"
#include "TLit_Scan_Recordset.h"
#include "CF_Cedent_Recordset.h"
#include "TCFLiteral.h"
#include "KL_Cedent_Recordset.h"
#include "TKLLiteral.h"

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

	MSXML2::IXMLDOMDocumentPtr dom;
	dom.CreateInstance(_T("Msxml2.DOMDocument"));
	dom->async = VARIANT_FALSE; // default - true,
	
	dom->load((LPCTSTR) _T("../XML/4ft_hyp.xml"));

	MSXML2::IXMLDOMElementPtr el_hyp = dom->selectSingleNode("/active_list/hyp_4ft");

	el_hyp->setAttribute("db_name", (LPCTSTR) db->GetDatabaseName());

	* result = dom->xml;

	return TRUE;
}

/****/

// ---AP Task

CString fLMTask (void* hSource)
{
	CString buf = "";
	return buf;
}

// ---AP KL cedent

CString fLMKLCedent (void* hSource)
{
	CString buf = "";
	CString hlp;
	CString hlp1;
	CString db_name = ((CDatabase *) hSource)->GetDatabaseName ();
	CString q_lit;
	CString q_cat;
	
	long sub_cedent_cnt = 0;
	long literal_cnt = 0;
	long ct_id;
	long ct_id_tst = 0;  //test, wheather the new cedent type appears
	long c_id;
	long c_id_tst = 0; //test, wheather the new sub cedent appears
	long c = 0; //counter


	KL_Cedent_Recordset rs ((CDatabase *) hSource);
	TKLLiteral rs_lit ((CDatabase *) hSource);
	TCategory_Scan rs_cat ((CDatabase *) hSource);

	TKL_Cedent_Meta_Array list;
	KL_Cedent_Meta * ptklcdnt;
	Sub_KL_Cedent_Meta * ptsub_kl_cedent;

	KL_Literal_Meta lit;

	LPCTSTR q =
		"SELECT * \
		 FROM  taTask, tdKLCedentD, tmMatrix, tsCedentType, tsTaskSubType \
		 WHERE taTask.TaskID=tdKLCedentD.TaskID \
			AND taTask.MatrixID=tmMatrix.MatrixID \
			AND tdKLCedentD.CedentTypeID=tsCedentType.CedentTypeID \
			AND taTask.TaskSubTypeID=tsTaskSubType.TaskSubTypeID \
		 ORDER BY taTask.TaskID, tdKLCedentD.CedentTypeID";

	if (rs.Open(AFX_DB_USE_DEFAULT_TYPE, q))
	{
		//iteration on query results
		while (!rs.IsEOF())
		{
			ct_id = rs.m_CedentTypeID;
			c_id = rs.m_KLCedentDID;
			if (ct_id != ct_id_tst) //new cedent
			{
				sub_cedent_cnt = 0;
				literal_cnt = 0;
				ptklcdnt = new (KL_Cedent_Meta);
				ptklcdnt->db_name = db_name;
				hlp.Format ("%d", rs.m_KLCedentDID);
				ptklcdnt->id = "KLcdnt" + hlp;
				ptklcdnt->matrix_name = rs.m_Name3;
				ptklcdnt->task_name = rs.m_Name;
				ptklcdnt->task_type = rs.m_Name5;
				ptklcdnt->cedent_type = rs.m_Name4;
				list.Add (ptklcdnt);
			}
			if (c_id != c_id_tst) //new sub cedent
			{
				ptsub_kl_cedent = new (Sub_KL_Cedent_Meta);
				literal_cnt = 0;
				sub_cedent_cnt++;
				ptklcdnt->sub_cedent_cnt.Format ("%d", sub_cedent_cnt);
				hlp = rs.m_Name2;
				hlp.Replace ("&", "&amp;");
				hlp.Replace ("<", "&lt;");
				hlp.Replace (">", "&gt;");
				ptsub_kl_cedent->name = hlp;
				hlp.Format ("%d", rs.m_MinLen);
				hlp1.Format ("%d", rs.m_MaxLen);
				hlp += " - ";
				hlp += hlp1;
				ptsub_kl_cedent->length = hlp;
				ptklcdnt->sub_cedents_list.Add (ptsub_kl_cedent);
				hlp.Format ("%d", c_id);
				q_lit =
					"SELECT * \
					 FROM tdKLLiteralD, tmAttribute, tmQuantity \
					 WHERE tdKLLiteralD.KLCedentDID=" + hlp +
					"	AND tmQuantity.QuantityID=tdKLLiteralD.QuantityID \
						AND tmQuantity.AttributeID=tmAttribute.AttributeID";
				if (rs_lit.Open(AFX_DB_USE_DEFAULT_TYPE, q_lit))
				{
					//iteration on query results
					while (!rs_lit.IsEOF())
					{
						literal_cnt++;
						ptsub_kl_cedent->literal_cnt.Format ("%d", literal_cnt);
						lit.underlying_attribute = rs_lit.m_Name;
						hlp.Format ("%d", rs_lit.m_QuantityID2);
						q_cat =
							"SELECT * \
							 FROM tmCategory \
							 WHERE tmCategory.QuantityID=" + hlp;
						if (rs_cat.Open(AFX_DB_USE_DEFAULT_TYPE, q_cat))
						{
							c = 0;
							//iteration on query results
							while (!rs_cat.IsEOF())
							{
								c++;
								rs_cat.MoveNext ();
							}
							rs_cat.Close ();
						}
						else return "";
						lit.category_cnt.Format ("%d", c);
						ptsub_kl_cedent->lit_list.Add (lit);
						rs_lit.MoveNext ();
					}
					rs_lit.Close ();
				}
				else return "";
			}
			c_id_tst = c_id;
			ct_id_tst = ct_id;
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
	int i;
    for (i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert ();
	}
	buf += " </active_list>";
/*	//just for test - creates a xml file with all attributes
	FILE * f = fopen ("test.xml", "w");
	fprintf (f, "%s", buf);
	fclose (f);


	AfxMessageBox(buf);
*/
	for (i = 0; i < list.GetSize (); i++)
	{
		for (int j = 0; j < list.GetAt (i)->sub_cedents_list.GetSize (); j++)
		{
			delete (list.GetAt (i)->sub_cedents_list.GetAt (j));
		}
		list.GetAt (i)->sub_cedents_list.RemoveAll ();
		delete (list.GetAt (i));
	}
	list.RemoveAll ();

	return buf;
}

// ---AP CF cedent

CString fLMCFCedent (void* hSource)
{
	CString buf = "";
	CString hlp;
	CString hlp1;
	CString db_name = ((CDatabase *) hSource)->GetDatabaseName ();
	CString q_lit;
	CString q_cat;
	
	long sub_cedent_cnt = 0;
	long literal_cnt = 0;
	long ct_id;
	long ct_id_tst = 0;  //test, wheather the new cedent type appears
	long c_id;
	long c_id_tst = 0; //test, wheather the new sub cedent appears
	long c = 0; //counter


	CF_Cedent_Recordset rs ((CDatabase *) hSource);
	TCFLiteral rs_lit ((CDatabase *) hSource);
	TCategory_Scan rs_cat ((CDatabase *) hSource);

	TCF_Cedent_Meta_Array list;
	CF_Cedent_Meta * ptcfcdnt;
	Sub_CF_Cedent_Meta * ptsub_cf_cedent;

	CF_Literal_Meta lit;

	LPCTSTR q =
		"SELECT * \
		 FROM  taTask, tdCFCedentD, tmMatrix, tsCedentType, tsTaskSubType \
		 WHERE taTask.TaskID=tdCFCedentD.TaskID \
			AND taTask.MatrixID=tmMatrix.MatrixID \
			AND tdCFCedentD.CedentTypeID=tsCedentType.CedentTypeID \
			AND taTask.TaskSubTypeID=tsTaskSubType.TaskSubTypeID \
		 ORDER BY taTask.TaskID, tdCFCedentD.CedentTypeID";

	if (rs.Open(AFX_DB_USE_DEFAULT_TYPE, q))
	{
		//iteration on query results
		while (!rs.IsEOF())
		{
			ct_id = rs.m_CedentTypeID;
			c_id = rs.m_CFCedentDID;
			if (ct_id != ct_id_tst) //new cedent
			{
				sub_cedent_cnt = 0;
				literal_cnt = 0;
				ptcfcdnt = new (CF_Cedent_Meta);
				ptcfcdnt->db_name = db_name;
				hlp.Format ("%d", rs.m_CFCedentDID);
				ptcfcdnt->id = "CFcdnt" + hlp;
				ptcfcdnt->matrix_name = rs.m_Name3;
				ptcfcdnt->task_name = rs.m_Name;
				ptcfcdnt->task_type = rs.m_Name5;
				ptcfcdnt->cedent_type = rs.m_Name4;
				list.Add (ptcfcdnt);
			}
			if (c_id != c_id_tst) //new sub cedent
			{
				ptsub_cf_cedent = new (Sub_CF_Cedent_Meta);
				literal_cnt = 0;
				sub_cedent_cnt++;
				ptcfcdnt->sub_cedent_cnt.Format ("%d", sub_cedent_cnt);
				hlp = rs.m_Name2;
				hlp.Replace ("&", "&amp;");
				hlp.Replace ("<", "&lt;");
				hlp.Replace (">", "&gt;");
				ptsub_cf_cedent->name = hlp;
				hlp.Format ("%d", rs.m_MinLen);
				hlp1.Format ("%d", rs.m_MaxLen);
				hlp += " - ";
				hlp += hlp1;
				ptsub_cf_cedent->length = hlp;
				ptcfcdnt->sub_cedents_list.Add (ptsub_cf_cedent);
				hlp.Format ("%d", c_id);
				q_lit =
					"SELECT * \
					 FROM tdCFLiteralD, tmAttribute, tmQuantity \
					 WHERE tdCFLiteralD.CFCedentDID=" + hlp +
					"	AND tmQuantity.QuantityID=tdCFLiteralD.QuantityID \
						AND tmQuantity.AttributeID=tmAttribute.AttributeID";
				if (rs_lit.Open(AFX_DB_USE_DEFAULT_TYPE, q_lit))
				{
					//iteration on query results
					while (!rs_lit.IsEOF())
					{
						literal_cnt++;
						ptsub_cf_cedent->literal_cnt.Format ("%d", literal_cnt);
						lit.underlying_attribute = rs_lit.m_Name;
						hlp.Format ("%d", rs_lit.m_QuantityID2);
						q_cat =
							"SELECT * \
							 FROM tmCategory \
							 WHERE tmCategory.QuantityID=" + hlp;
						if (rs_cat.Open(AFX_DB_USE_DEFAULT_TYPE, q_cat))
						{
							c = 0;
							//iteration on query results
							while (!rs_cat.IsEOF())
							{
								c++;
								rs_cat.MoveNext ();
							}
							rs_cat.Close ();
						}
						else return "";
						lit.category_cnt.Format ("%d", c);
						ptsub_cf_cedent->lit_list.Add (lit);
						rs_lit.MoveNext ();
					}
					rs_lit.Close ();
				}
				else return "";
			}
			c_id_tst = c_id;
			ct_id_tst = ct_id;
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
	int i;
    for (i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert ();
	}
	buf += " </active_list>";
/*	//just for test - creates a xml file with all attributes
	FILE * f = fopen ("test.xml", "w");
	fprintf (f, "%s", buf);
	fclose (f);


	AfxMessageBox(buf);
*/
	for (i = 0; i < list.GetSize (); i++)
	{
		for (int j = 0; j < list.GetAt (i)->sub_cedents_list.GetSize (); j++)
		{
			delete (list.GetAt (i)->sub_cedents_list.GetAt (j));
		}
		list.GetAt (i)->sub_cedents_list.RemoveAll ();
		delete (list.GetAt (i));
	}
	list.RemoveAll ();

	return buf;
}


// ---AP bool cedent

CString fLMBoolCedent (void* hSource)
{
	CString buf = "";
	CString hlp;
	CString hlp1;
	CString db_name = ((CDatabase *) hSource)->GetDatabaseName ();
	
	long sub_cedent_cnt = 0;
	long literal_cnt = 0;
	long ct_id;
	long ct_id_tst = 0;  //test, wheather the new cedent type appears
	long c_id;
	long c_id_tst = 0; //test, wheather the new sub cedent appears
	long l_id;
	long l_id_tst = 0; //test, wheather the new literal appears
	long c = 0; //counter - help variable
	long indx; //help variable
	long y; //help variable

	BOOL missing_type = FALSE;

	TBool_Cedent_Meta_Array list;
	Bool_Cedent_Meta * ptboolcdnt;

	Bool_Cedent_Recordset rs ((CDatabase *) hSource);
	Equivalence_Lit_Rs rs_eq ((CDatabase *) hSource);
	TCategory_Scan rs_cat ((CDatabase *) hSource);
	TEmpty_Cedents_Recordset rs_em ((CDatabase *) hSource);
	TLit_Scan_Recordset rs_lit ((CDatabase *) hSource);

	Sub_Bool_Cedent_Meta * ptsub_bool_cedent;
	Literal_Meta lit;

	CString q_eq;
	CString q_cat;
	CString q_lit;
	LPCTSTR q =
		"SELECT * \
		 FROM taTask, tdCedentD, tdLiteralD, tmAttribute, \
			tmMatrix, tmQuantity, tsCedentType, tsCoefficientType, tsGaceType, \
			tsLiteralType, tsTaskSubType \
		 WHERE tdCedentD.CedentTypeID=tsCedentType.CedentTypeID \
			AND tdCedentD.TaskID=taTask.TaskID \
			AND tdCedentD.CedentDID=tdLiteralD.CedentDID \
			AND tdLiteralD.QuantityID=tmQuantity.QuantityID \
			AND tdLiteralD.LiteralTypeID=tsLiteralType.LiteralTypeID \
			AND tdLiteralD.GaceTypeID=tsGaceType.GaceTypeID \
			AND tdLiteralD.CoefficientTypeID=tsCoefficientType.CoefficientTypeID \
			AND tmQuantity.AttributeID=tmAttribute.AttributeID \
			AND tmAttribute.MatrixID=tmMatrix.MatrixID \
			AND taTask.TaskSubTypeID=tsTaskSubType.TaskSubTypeID \
		 ORDER BY tdCedentD.TaskID, tdCedentD.CedentTypeID, tdLiteralD.LiteralDID";
	LPCTSTR q_em =
		"SELECT * \
		 FROM taTask, tdCedentD, tmMatrix, tsCedentType, tsTaskSubType \
		 WHERE tdCedentD.CedentTypeID=tsCedentType.CedentTypeID \
		 AND taTask.TaskSubTypeID=tsTaskSubType.TaskSubTypeID \
		 AND tdCedentD.TaskID=taTask.TaskID \
		 AND taTask.MatrixID=tmMatrix.MatrixID";

	if (rs.Open(AFX_DB_USE_DEFAULT_TYPE, q))
	{
		//iteration on query results
		while (!rs.IsEOF())
		{
			c++;
			ct_id = rs.m_CedentTypeID;
			c_id = rs.m_CedentDID;
			l_id = rs.m_LiteralDID;
			if (ct_id != ct_id_tst) //new cedent
			{
				sub_cedent_cnt = 0;
				literal_cnt = 0;
				ptboolcdnt = new (Bool_Cedent_Meta);
				ptboolcdnt->db_name = db_name;
				hlp.Format ("%d", rs.m_CedentDID);
				ptboolcdnt->id = "cdnt" + hlp;
				ptboolcdnt->matrix_name = rs.m_Name4;
				ptboolcdnt->task_name = rs.m_Name;
				ptboolcdnt->task_type = rs.m_Name10;
				ptboolcdnt->cedent_type = rs.m_Name6;
				list.Add (ptboolcdnt);
			}
			if (c_id != c_id_tst) //new sub cedent
			{
				ptsub_bool_cedent = new (Sub_Bool_Cedent_Meta);
				literal_cnt = 0;
				sub_cedent_cnt++;
				ptboolcdnt->sub_cedent_cnt.Format ("%d", sub_cedent_cnt);
				hlp = rs.m_Name2;
				hlp.Replace ("&", "&amp;");
				hlp.Replace ("<", "&lt;");
				hlp.Replace (">", "&gt;");
				ptsub_bool_cedent->name = hlp;
				hlp.Format ("%d", rs.m_MinLen);
				hlp1.Format ("%d", rs.m_MaxLen);
				hlp += " - ";
				hlp += hlp1;
				ptsub_bool_cedent->length = hlp;
				ptboolcdnt->sub_cedents_list.Add (ptsub_bool_cedent);
			}
			if (l_id != l_id_tst) //new literal
			{
				literal_cnt++;
				ptsub_bool_cedent->literal_cnt.Format ("%d", literal_cnt);
				hlp = rs.m_Name3;
				hlp.Replace ("&", "&amp;");
				hlp.Replace ("<", "&lt;");
				hlp.Replace (">", "&gt;");
				lit.underlying_attribute = hlp;
				hlp = rs.m_Name7;
				hlp.Replace ("&", "&amp;");
				hlp.Replace ("<", "&lt;");
				hlp.Replace (">", "&gt;");
				lit.coefficient_type = hlp;
				if (rs.m_ShortName3 == "one")
				{
					hlp.Format ("%d", rs.m_CategoryID);
					//this query returns only one row - primary key in WHERE clause
					q_cat = "SELECT * \
							 FROM tmCategory \
							 WHERE CategoryID=" + hlp;
					//find one category value
					if (rs_cat.Open(AFX_DB_USE_DEFAULT_TYPE, q_cat))
					{
						//iteration on query results - one row
						while (!rs_cat.IsEOF())
						{
							hlp = rs_cat.m_Name;
							rs_cat.MoveNext ();
						}
						rs_cat.Close ();
					}
					else return "";
					hlp = "(" + hlp + ")";
					hlp.Replace ("&", "&amp;");
					hlp.Replace ("<", "&lt;");
					hlp.Replace (">", "&gt;");
					lit.coefficient_type += hlp;
				}
				hlp.Format ("%d", rs.m_MinLen2);
				hlp1.Format ("%d", rs.m_MaxLen2);
				hlp += " - ";
				hlp += hlp1;
				lit.length = hlp;
				hlp = rs.m_Name8;
				hlp.Replace ("&", "&amp;");
				hlp.Replace ("<", "&lt;");
				hlp.Replace (">", "&gt;");
				lit.gace = hlp;
				hlp = rs.m_Name9;
				hlp.Replace ("&", "&amp;");
				hlp.Replace ("<", "&lt;");
				hlp.Replace (">", "&gt;");
				lit.literal_type = hlp;
				hlp.Format ("%d", c_id);
				q_eq = "SELECT * \
					FROM tdEquivalenceClass \
					WHERE CedentDID=" + hlp;
				//find all equivalence classes
				hlp = "";
				if (rs_eq.Open(AFX_DB_USE_DEFAULT_TYPE, q_eq))
				{
					c = 0;
					//iteration on query results
					while (!rs_eq.IsEOF())
					{
						c++;
						if (c != 1) hlp += "; ";
						hlp += rs_eq.m_Name;
						rs_eq.MoveNext ();
					}
					rs_eq.Close ();
				}
				else return "";
				hlp.Replace ("&", "&amp;");
				hlp.Replace ("<", "&lt;");
				hlp.Replace (">", "&gt;");
				lit.equivalence_class = hlp;
				hlp.Format ("%d", rs.m_QuantityID2);
				q_cat ="SELECT * \
						FROM tmCategory \
						WHERE QuantityID=" + hlp;
				//find categories and missing values
				missing_type = FALSE;
				if (rs_cat.Open(AFX_DB_USE_DEFAULT_TYPE, q_cat))
				{
					c = 0;
					//iteration on query results
					while (!rs_cat.IsEOF())
					{
						c++;
						if (rs_cat.m_XCategory) missing_type = TRUE;
						rs_cat.MoveNext ();
					}
					rs_cat.Close ();
				}
				else return "";
				lit.category_cnt.Format ("%d", c);
				if (missing_type) lit.missing_type = "Yes";
				else lit.missing_type = "No";
				ptsub_bool_cedent->lit_list.Add (lit);
			}
			l_id_tst = l_id;
			c_id_tst = c_id;
			ct_id_tst = ct_id;
			rs.MoveNext();
		}
		rs.Close();
	}
	else return "";
	//add empty subcedents
	if (rs_em.Open(AFX_DB_USE_DEFAULT_TYPE, q_em))
	{
		//iteration on query results
		while (!rs_em.IsEOF())
		{
			hlp.Format ("%d", rs_em.m_CedentDID);
			q_lit = "SELECT * FROM tdLiteralD WHERE CedentDID=" + hlp;
			c = 0;
			if (rs_lit.Open (AFX_DB_USE_DEFAULT_TYPE, q_lit))
			{
				while (!rs_lit.IsEOF ())
				{
					c++;
					rs_lit.MoveNext ();
				}
				rs_lit.Close ();
			}
			else return "";
			if (c == 0) //new empty subcedent
			{
				//find cedent for this subcedent, if not exists, create new cedent or subcedent
				indx = -1;
				for (y = 0; y < list.GetSize (); y++)
				{
					if ((list.GetAt (y)->task_name == rs_em.m_Name)
						&&
						(list.GetAt (y)->task_type == rs_em.m_Name5)
						&&
						(list.GetAt (y)->cedent_type == rs_em.m_Name4))
					{
						indx = y;
						break;
					}
				}
				ptsub_bool_cedent = new (Sub_Bool_Cedent_Meta);
				ptsub_bool_cedent->literal_cnt.Format ("%d", 0);
				ptsub_bool_cedent->name = rs_em.m_Name2;
				hlp.Format ("%d", rs_em.m_MinLen);
				hlp1.Format ("%d", rs_em.m_MaxLen);
				hlp += " - ";
				hlp += hlp1;
				ptsub_bool_cedent->length = hlp;
				ptsub_bool_cedent->lit_list.RemoveAll ();
				if (indx == -1) //new cedent must be created
				{
					ptboolcdnt = new (Bool_Cedent_Meta);
					sub_cedent_cnt = 1;
					ptboolcdnt->db_name = db_name;
					hlp.Format ("%d", rs_em.m_CedentDID);
					ptboolcdnt->id = "cdnt" + hlp;
					ptboolcdnt->matrix_name = rs_em.m_Name3;
					ptboolcdnt->task_name = rs_em.m_Name;
					ptboolcdnt->task_type = rs_em.m_Name5;
					ptboolcdnt->cedent_type = rs_em.m_Name4;
					ptboolcdnt->sub_cedent_cnt.Format ("%d", sub_cedent_cnt);
					ptboolcdnt->sub_cedents_list.Add (ptsub_bool_cedent);
					list.Add (ptboolcdnt);
				}
				else //add subcedent to existing cedent
				{
					list.GetAt (indx)->sub_cedents_list.Add (ptsub_bool_cedent);
					sub_cedent_cnt = atol (list.GetAt (indx)->sub_cedent_cnt);
					sub_cedent_cnt++;
					list.GetAt (indx)->sub_cedent_cnt.Format ("%d", sub_cedent_cnt);
				}
			}
			rs_em.MoveNext ();
		}
		rs_em.Close ();
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
	int i;
    for (i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert ();
	}
	buf += " </active_list>";
	//just for test - creates a xml file with all attributes
/*	FILE * f = fopen ("test.xml", "w");
	fprintf (f, "%s", buf);
	fclose (f);


	AfxMessageBox(buf);
*/
	for (i = 0; i < list.GetSize (); i++)
	{
		for (int j = 0; j < list.GetAt (i)->sub_cedents_list.GetSize (); j++)
		{
			delete (list.GetAt (i)->sub_cedents_list.GetAt (j));
		}
		list.GetAt (i)->sub_cedents_list.RemoveAll ();
		delete (list.GetAt (i));
	}
	list.RemoveAll ();
	
	return buf;
}


// --- AP attribute

CString fLMAttribute(void* hSource)
{
	CString buf = "";
	CString hlp;
	CString db_name = ((CDatabase *) hSource)->GetDatabaseName ();
	CString qcat;

	long count = 0;

	TAttribute_Recordset rs ((CDatabase *) hSource);
	TCategory_list rscat ((CDatabase *) hSource);

	Attribute_Meta * ptatt;
	TAttribute_Meta_Array list;

	TCtgr cat;

	LPCTSTR q =
		"SELECT * \
		 FROM tmAttribute, tmMatrix, tsAttributeSubType \
		 WHERE tmAttribute.MatrixID=tmMatrix.MatrixID \
			AND tmAttribute.AttributeSubTypeID=tsAttributeSubType.AttributeSubTypeID";
	if (rs.Open(AFX_DB_USE_DEFAULT_TYPE, q))
	{
		//iteration on query results
		while (!rs.IsEOF())
		{
			ptatt = new (Attribute_Meta);
			ptatt->attr_name = rs.m_Name;
			ptatt->db_name = db_name;
			ptatt->matrix_name = rs.m_Name2;
			hlp.Format ("%d", rs.m_AttributeID);
			ptatt->id = "attr" + hlp;
//zkontrolovat typy atributu...!!!			
			if (rs.m_Formula == "")
				ptatt->creation = rs.m_Name;
			else ptatt->creation = rs.m_Formula;
			hlp.Format ("%d", rs.m_AttributeID);
			qcat =
				"SELECT * \
				 FROM tmAttribute, tmCategory, tmQuantity \
				 WHERE tmAttribute.AttributeID=" + hlp + " \
					AND tmAttribute.AttributeID=tmQuantity.AttributeID \
					AND tmQuantity.QuantityID=tmCategory.QuantityID";
			if (rscat.Open(AFX_DB_USE_DEFAULT_TYPE, qcat))
			{
				while (!rscat.IsEOF ())
				{
					count++;
					hlp = rscat.m_Name2;
					hlp.Replace ("&", "&amp;");
					hlp.Replace ("<", "&lt;");
					hlp.Replace (">", "&gt;");
					cat.name = hlp;
					cat.freq = "N/A";
					ptatt->category_list.Add (cat);
					//add missing category
					if (rscat.m_XCategory)
						ptatt->missing_type_list.Add (hlp);
					rscat.MoveNext ();
				}
				rscat.Close ();
				ptatt->ctgr_count.Format ("%d", count);
				count = 0;
			}
			else return "";
			list.Add (ptatt);
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
	int i;
    for (i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert ();
	}
	buf += " </active_list>";
	//just for test - creates a xml file with all attributes
/*	FILE * f = fopen ("test.xml", "w");
	fprintf (f, "%s", buf);
	fclose (f);


	AfxMessageBox(buf);
*/
	for (i = 0; i < list.GetSize (); i++)
	{
		delete (list.GetAt (i));
	}
	list.RemoveAll ();
	
	return buf;
}

// --- AP category

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

//	fLMCedent (hSource);

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
						hlp1.Replace ("&", "&amp;");
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
			//find the order of category according to its ID
			//for category frequency matching
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
	int i;
    for (i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert ();
	}
	buf += " </active_list>";
	//just for test - creates a xml file with all categories
/*	FILE * f = fopen ("test.xml", "w");
	fprintf (f, "%s", buf);
	fclose (f);


	AfxMessageBox(buf);
*/
	for (i = 0; i < list.GetSize (); i++)
	{
		delete (list.GetAt (i));
	}
	list.RemoveAll ();

	return buf;
}


// --- AP 4ft-hypotesis

CString fLM4fthyp(void * hSource)
{
	CString buf;
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
				x.id = "tiLit" + id_hlp + pthyp->id;
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
				x.id = "tiLit" + id_hlp + pthyp->id;
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
				x.id = "tiLit" + id_hlp + pthyp->id;
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
/***** dedek: korektni verze nejen pro VS 2005 ****/
  CFile f("../XML/dtd.dtd", CFile::modeRead);
  int size = (int) f.GetLength();
  LPTSTR ps = buf.GetBuffer(size);
  f.Read(ps, size);
  f.Close();
  ps[size] = 0; //data nactena ze souboru se jete musi ukoncit nulou aby reprezentovala validni string
  buf.ReleaseBuffer(); //od teto chvile je ps neplatny a nemelo by se do nej zapisovat
  
/** dedek predelano nahore *
  FILE * x = fopen ("../XML/dtd.dtd", "r");
	CString buf1;
	while (fscanf (x, "%s", buf1) != EOF)
	{
		buf = buf + (const char *) buf1 + " ";
	}
	fclose (x);
/*****/

	//create xml data
	buf = buf + " <active_list> ";
	int i;
    for (i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert ();
	}
	buf += " </active_list>";
	//just for test - creates a xml file with all hypothesis
/*	FILE * f = fopen ("test.xml", "w");
	fprintf (f, "%s", buf);
	fclose (f);
*/
	for (i = 0; i < list.GetSize (); i++)
	{
		delete (list.GetAt (i));
	}
	list.RemoveAll ();

	return buf;
}



