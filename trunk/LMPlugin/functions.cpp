// implementace funkci pro vyrizeni pozadavku na AP v zasuvce pro LM
// functions.cpp
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

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
#include "functions.h"
#include "Hyp_4ft_Recordset.h"
#include "TCategory_Recordset.h"
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
#include "Task_Recordset.h"
#include "tiHypothesis_Recordset.h"
#include "TFTQuantifier_Recordset.h"
#include "TCFQuantifier_Recordset.h"
#include "TKLQuantifier_Recordset.h"
#include "TDFQuantifier_Recordset.h"
#include "TDCQuantifier_Recordset.h"
#include "TDKQuantifier_Recordset.h"
#include "Hyp_CF_Recordset.h"
#include "tiCFFrequencyI_Recordset.h"
#include "tmCategory_Recordset.h"
#include "TCondition_Recordset.h"
#include "Hyp_SD4ft_Recordset.h"
#include "Hyp_SDCF_Recordset.h"
#include "tiDCFrequencyI_Recordset.h"
#include "Hyp_KL_Recordset.h"
#include "tiKLFrequencyI_Recordset.h"
#include "TKLquant_Recordset.h"
#include "TKLCategory_Recordset.h"
#include "Hyp_SDKL_Recordset.h"
#include "tiDKFrequencyI_Recordset.h"
#include "TCoef_type_Recordset.h"
#include "ODBCINST.H"
#include "TData_Matrix_Recordset.h"
#include "TColumn_Recordset.h"
#include "direct.h"
#include "math.h"
#include "LMPlErrorMessages.h"
#include "LMPlugin.h"
#include "CTime_Utils.h"
#include <afxdb.h>
#include <Shlwapi.h>

#import <msxml3.dll>
using namespace MSXML2;
//pastes the namespace MSXML2;

bool ar2nl_err = false;

CString Get_4ftar2nl_output (LPCTSTR file_path)
{
	// kody - reading and serialization of the outputof the AR2NL using XML DOM
	MSXML2::IXMLDOMDocumentPtr dom;
	dom.CreateInstance(_T("Msxml2.DOMDocument"));
	dom->async = VARIANT_FALSE; // default - true,

	if (dom->load((LPCTSTR) file_path)!=VARIANT_TRUE)
	{
		return "";
	}

	MSXML2::IXMLDOMElementPtr el_hyp = dom->GetdocumentElement();

	dom.Release();

	if (el_hyp != NULL)
	{
		return (LPCTSTR) el_hyp->Getxml();
	}
	else
	{
		return "";
	}
}

class CAR2NLHlp
{
	CString DSN;
	CString AR2NL_exe_command;
	CString AR2NL_path;
	CString config;

	BOOL source_is_set;

	void ReplaceDollars(LPSTR str)
	{
		while (* str)
		{
			if (* str == '$') * str = '\0';
			str++;
		}
	}

public:
	LPCTSTR getConfig() {return config;};
	CString getEXEPath() {return AR2NL_path + "\\bin";};
	LPCTSTR getEXECommand() {return AR2NL_exe_command;};
	CString getOutput12Path() {return AR2NL_path + "\\output\\output12.xml";};

	CAR2NLHlp (long hypno, CString db_name)
	{
		source_is_set = FALSE;

		DSN.Format("LMxRepAssistxtempx%d", hypno);

		TCHAR module_path[MAX_PATH];
		GetModuleFileName(NULL, module_path, MAX_PATH);
		//deletes the last two levels from the path
		PathFindFileName(module_path)[-1] = 0;
		PathFindFileName(module_path)[-1] = 0;
		PathFindFileName(module_path)[-1] = 0;
		
		AR2NL_path.Format("%s\\4ftAR2NL", module_path);
		AR2NL_exe_command.Format("4ftar2nl.exe -DSN=%s  -hypno=%d", (LPCTSTR) DSN, hypno);

		config.Format("DSN=%s$ DESCRIPTION=Temporary ODBC$ DBQ=%s.mdb$ FIL=MicrosoftAccess$ DEFAULTDIR= $",
			(LPCSTR) DSN, (LPCTSTR) db_name);
	}

	BOOL setODBCSource()
	{
		CString conf_str = getConfig();
		LPSTR buf = conf_str.GetBuffer(0);

		ReplaceDollars(buf);

		source_is_set = SQLConfigDataSource (NULL, ODBC_ADD_DSN, "Microsoft Access Driver (*.mdb)\0", buf);

		conf_str.ReleaseBuffer();

		return source_is_set;
	}
		
	~CAR2NLHlp()
	{
		if (source_is_set)
		{
			CString conf_str = "DSN=" + DSN + "$";
			LPSTR buf = conf_str.GetBuffer(0);

			ReplaceDollars(buf);

			if (FALSE == SQLConfigDataSource (NULL, ODBC_REMOVE_DSN,
						"Microsoft Access Driver (*.mdb)", buf))
			{
				conf_str.ReleaseBuffer();
				CLMSock::ReportError (5, LMERR_CANNOT_REMOVE_ODBC);
			}

			conf_str.ReleaseBuffer();
		}
	}
};

CString Get_4ftAR2NL (long hypno, CString db_name)
{
	CAR2NLHlp AR2NLHlp(hypno, db_name);

	//create the temporary datasource
	if (FALSE == AR2NLHlp.setODBCSource())
	{
		CLMSock::ReportError (4, LMERR_CANNOT_CREATE_ODBC);
		ar2nl_err = true;
		return "";
	}

	//change the working directory
	if (_chdir (AR2NLHlp.getEXEPath()) != 0)
	{
		CLMSock::ReportError(6, LMERR_CANNOT_FIND_AR2NL_EXE_PATH, (LPCTSTR) AR2NLHlp.getEXEPath());
		ar2nl_err = true;
		return "";
	}

	
	CFileStatus status;
	bool file_exists;
	CTime last_modif_time;

	
	try
	{
		CFile f (AR2NLHlp.getOutput12Path(), CFile::modeRead);
		if(f.GetStatus (status))
		{
			file_exists = true;
			last_modif_time = status.m_mtime;
		}
		else file_exists = false;
		f.Close ();
	}
	catch (...)
	{
		file_exists = false;
	}
	
	
	STARTUPINFO si;
	ZeroMemory(& si, sizeof si);
	si.cb = sizeof si;
	
	PROCESS_INFORMATION pi;
	ZeroMemory(& pi, sizeof pi);
	
	try
	{
		//run the 4ftAR2NL application
		CString exe_cmd = AR2NLHlp.getEXECommand();
		if (!CreateProcess(NULL, exe_cmd.GetBuffer(0),
					NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, & si, & pi)) 
		{
			exe_cmd.ReleaseBuffer();
			CLMSock::ReportError (7, LMERR_AR2NL_EXE_FAIL, 
					(LPCTSTR) (AR2NLHlp.getEXEPath() + "\\" + AR2NLHlp.getEXECommand()));
			ar2nl_err = true;
			return "";
		}
		exe_cmd.ReleaseBuffer();
	}
	catch (...)
	{
		CLMSock::ReportError (7, LMERR_AR2NL_EXE_FAIL, 
				(LPCTSTR) (AR2NLHlp.getEXEPath() + "\\" + AR2NLHlp.getEXECommand()));
		ar2nl_err = true;
		return "";
	}

	try
	{
		DWORD exit_code = 1;//0 = successful
	
		if (!GetExitCodeProcess (pi.hProcess, &exit_code))
		{
			CLMSock::ReportError (8, LMERR_AR2NL_EXIT_FAIL);
			ar2nl_err = true;
			return "";
		}
		
		int cnt = 0;
		while (exit_code == STILL_ACTIVE)
		{
			if (!GetExitCodeProcess (pi.hProcess, &exit_code))
			{
				CLMSock::ReportError (8, LMERR_AR2NL_EXIT_FAIL);
				ar2nl_err = true;
				return "";
			}
			Sleep (500);
			cnt += 500;
			if (cnt > 60000) exit_code = 0;
		}

		if (exit_code != 0)
		{
			return "";
		}
	}
	catch (...)
	{
		CLMSock::ReportError (8, LMERR_AR2NL_EXIT_FAIL);
		ar2nl_err = true;
		return "";
	}
	
	try
	{
		if (!CloseHandle(pi.hProcess) || !CloseHandle(pi.hThread))
		{
			ar2nl_err = true;
			return "";
		}
	}
	catch (...)
	{
		ar2nl_err = true;
		return "";
	}
	
	try
	{
		CFile f1 (AR2NLHlp.getOutput12Path(), CFile::modeRead);
		if (f1.GetStatus (status))
		{
			if (file_exists && status.m_mtime == last_modif_time)
			{
				return "";
			}
		}
		else
		{
			f1.Close ();
			return "";
		}
		f1.Close ();
	}
	catch (...)
	{
		return "";
	}

	try
	{
		return Get_4ftar2nl_output (AR2NLHlp.getOutput12Path());
	}
	catch (...)
	{
		CLMSock::ReportError (9, LMERR_CANNOT_READ_AR2NL_OUTPUT);
		ar2nl_err = true;
		return "";
	}

	return "";
}


CString Get_DTD ()
{
	TCHAR module_path[MAX_PATH];
	GetModuleFileName(NULL, module_path, MAX_PATH);

	//deletes the last two levels from the path
	PathFindFileName(module_path)[-1] = 0;
	PathFindFileName(module_path)[-1] = 0;
	PathFindFileName(module_path)[-1] = 0;

	CString file_path = module_path;
	file_path += "\\XML\\plug_output_DTD.xml";
	
	CString buf;
	CFile f(file_path, CFile::modeRead);
	int size = (int) f.GetLength();
	LPTSTR ps = buf.GetBuffer(size);
	f.Read(ps, size);
	f.Close();
	ps[size] = 0; //the data read from the output must be ended by zero to represent the valid string
	buf.ReleaseBuffer(); //ps is not valid from now and no further actions are allowed
	return buf;
}

// ---AP Quantifier

CString fLMQuantifier (void* hSource)
{
	CString buf = "";
	CString hlp;
	CString db_name = ((CDatabase *) hSource)->GetDatabaseName ();

	TQuantifier_Meta_Array list;
	Quantifier_Meta * ptquant;
	quant_item item;

	BOOL result;
	bool exc = false;

	TFTQuantifier_Recordset rs ((CDatabase *) hSource);
	TCFQuantifier_Recordset rsCF ((CDatabase *) hSource);
	TKLQuantifier_Recordset rsKL ((CDatabase *) hSource);
	TDFQuantifier_Recordset rsDF ((CDatabase *) hSource);
	TDCQuantifier_Recordset rsDC ((CDatabase *) hSource);
	TDKQuantifier_Recordset rsDK ((CDatabase *) hSource);

	LPCTSTR q = "SELECT * \
				 FROM taTask, tdFTQuantifier, tmMatrix, tsQuantifierType, tsTaskSubType \
				 WHERE taTask.MatrixID=tmMatrix.MatrixID \
				   AND taTask.TaskSubTypeID=tsTaskSubType.TaskSubTypeID \
				   AND tdFTQuantifier.TaskID=taTask.TaskID \
				   AND tsQuantifierType.QuantifierTypeID=tdFTQuantifier.FTQuantifierTypeID";

	try
	{
		result = rs.Open(AFX_DB_USE_DEFAULT_TYPE, q);
	}
	catch (CDBException* e)
	{
		exc = true;
		CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
		e->Delete ();
	}
	if (exc) return "";
	
	if (result)
	{
		//iteration on query results
		while (!rs.IsEOF())
		{
			ptquant = new (Quantifier_Meta);
			ptquant->db_name = db_name;
			ptquant->matrix_name = rs.m_Name2;
			ptquant->name = rs.m_Name3;
			ptquant->task_name = rs.m_Name;
			ptquant->task_type = rs.m_Name4;
			ptquant->type = "N/A";
			hlp.Format ("%d", rs.m_FTQuantifierID);
			hlp = "quantFT" + hlp;
			ptquant->id = hlp;
			if (rs.m_ShortName == "FUI")
			{
				item.name = "p";
				item.value = (LPCTSTR) (_bstr_t) rs.m_ParamP;
				ptquant->items.Add (item);
			}
			else if (rs.m_ShortName == "LCI")
			{
				item.name = "p";
				item.value = (LPCTSTR) (_bstr_t) rs.m_ParamP;
				ptquant->items.Add (item);
				item.name = "Alpha";
				item.value = (LPCTSTR) (_bstr_t) rs.m_ParamAlfa;
				ptquant->items.Add (item);
			}
			else if (rs.m_ShortName == "SUPP")
			{
				item.name = "p";
				item.value = (LPCTSTR) (_bstr_t) rs.m_ParamP;
				ptquant->items.Add (item);
			}
			else if (rs.m_ShortName == "UCI")
			{
				item.name = "p";
				item.value = (LPCTSTR) (_bstr_t) rs.m_ParamP;
				ptquant->items.Add (item);
				item.name = "Alpha";
				item.value = (LPCTSTR) (_bstr_t) rs.m_ParamAlfa;
				ptquant->items.Add (item);
			}
			else if (rs.m_ShortName == "AAI")
			{
				item.name = "p";
				item.value = (LPCTSTR) (_bstr_t) rs.m_ParamP;
				ptquant->items.Add (item);
			}
			else if (rs.m_ShortName == "BAI")
			{
				item.name = "p";
				item.value = (LPCTSTR) (_bstr_t) rs.m_ParamP;
				ptquant->items.Add (item);
			}
			else if (rs.m_ShortName == "DFUI")
			{
				item.name = "p";
				item.value = (LPCTSTR) (_bstr_t) rs.m_ParamP;
				ptquant->items.Add (item);
			}
			else if (rs.m_ShortName == "DLCI")
			{
				item.name = "p";
				item.value = (LPCTSTR) (_bstr_t) rs.m_ParamP;
				ptquant->items.Add (item);
				item.name = "Alpha";
				item.value = (LPCTSTR) (_bstr_t) rs.m_ParamAlfa;
				ptquant->items.Add (item);
			}
			else if (rs.m_ShortName == "DUCI")
			{
				item.name = "p";
				item.value = (LPCTSTR) (_bstr_t) rs.m_ParamP;
				ptquant->items.Add (item);
				item.name = "Alpha";
				item.value = (LPCTSTR) (_bstr_t) rs.m_ParamAlfa;
				ptquant->items.Add (item);
			}
			else if (rs.m_ShortName == "FUE")
			{
				item.name = "p";
				item.value = (LPCTSTR) (_bstr_t) rs.m_ParamP;
				ptquant->items.Add (item);
			}
			else if (rs.m_ShortName == "LCE")
			{
				item.name = "p";
				item.value = (LPCTSTR) (_bstr_t) rs.m_ParamP;
				ptquant->items.Add (item);
				item.name = "Alpha";
				item.value = (LPCTSTR) (_bstr_t) rs.m_ParamAlfa;
				ptquant->items.Add (item);
			}
			else if (rs.m_ShortName == "UCE")
			{
				item.name = "p";
				item.value = (LPCTSTR) (_bstr_t) rs.m_ParamP;
				ptquant->items.Add (item);
				item.name = "Alpha";
				item.value = (LPCTSTR) (_bstr_t) rs.m_ParamAlfa;
				ptquant->items.Add (item);
			}
			else if (rs.m_ShortName == "SID")
			{
				item.name = "Delta";
				item.value = (LPCTSTR) (_bstr_t) rs.m_ParamDelta;
				ptquant->items.Add (item);
			}
			else if (rs.m_ShortName == "FSH")
			{
				item.name = "Alpha";
				item.value = (LPCTSTR) (_bstr_t) rs.m_ParamAlfa;
				ptquant->items.Add (item);
			}
			else if (rs.m_ShortName == "CHI")
			{
				item.name = "Alpha";
				item.value = (LPCTSTR) (_bstr_t) rs.m_ParamAlfa;
				ptquant->items.Add (item);
			}
			else if (rs.m_ShortName == "E-Q")
			{
				item.name = "Delta";
				item.value = (LPCTSTR) (_bstr_t) rs.m_ParamDelta;
				ptquant->items.Add (item);
			}
			else if (rs.m_ShortName == "BASE")
			{
				if (rs.m_ParamRelativ)
				{
					item.name = "p";
					item.value = (LPCTSTR) (_bstr_t) rs.m_ParamBeta;
				}
				else
				{
					item.name = "count";
					item.value = (LPCTSTR) (_bstr_t) rs.m_ParamAlfa;
				}
				ptquant->items.Add (item);
			}
			else if (rs.m_ShortName == "CEIL")
			{
			if (rs.m_ParamRelativ)
				{
					item.name = "p";
					item.value = (LPCTSTR) (_bstr_t) rs.m_ParamBeta;
				}
				else
				{
					item.name = "count";
					item.value = (LPCTSTR) (_bstr_t) rs.m_ParamAlfa;
				}
				ptquant->items.Add (item);
			}
			list.Add (ptquant);
			rs.MoveNext();
		}
		rs.Close();
	}
	else return "";

	q = "SELECT * \
		 FROM taTask, tdCFQuantifier, tmMatrix, tsCFQuantifierType,\
		      tsCFQuantifierValueType, tsCompareType, tsTaskSubType \
		 WHERE taTask.MatrixID=tmMatrix.MatrixID \
		   AND taTask.TaskSubTypeID=tsTaskSubType.TaskSubTypeID \
		   AND tdCFQuantifier.TaskID=taTask.TaskID \
		   AND tsCFQuantifierType.CFQuantifierTypeID=tdCFQuantifier.CFQuantifierTypeID \
		   AND tsCFQuantifierValueType.CFQuantifierValueTypeID=tdCFQuantifier.CFQuantifierValueTypeID \
		   AND tsCompareType.CompareTypeID=tdCFQuantifier.CompareTypeID";

	try
	{
		result = rsCF.Open(AFX_DB_USE_DEFAULT_TYPE, q);
	}
	catch (CDBException* e)
	{
		exc = true;
		CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
		e->Delete ();
	}
	if (exc) return "";
	
	if (result)
	{
		//iteration on query results
		while (!rsCF.IsEOF())
		{
			ptquant = new (Quantifier_Meta);
			ptquant->db_name = db_name;
			ptquant->matrix_name = rsCF.m_Name2;
			ptquant->name = rsCF.m_Name3;
			ptquant->task_name = rsCF.m_Name;
			ptquant->task_type = rsCF.m_Name6;
			ptquant->type = "N/A";
			hlp.Format ("%d", rsCF.m_CFQuantifierID);
			hlp = "quantCF" + hlp;
			ptquant->id = hlp;
			
			item.name = "Value type";
			item.value = rsCF.m_Name4;
			ptquant->items.Add (item);

			item.name = "From";
			item.value = (LPCTSTR) (_bstr_t) rsCF.m_FromCol;
			ptquant->items.Add (item);

			item.name = "To";
			item.value = (LPCTSTR) (_bstr_t) rsCF.m_ToCol;
			ptquant->items.Add (item);

			item.name = "Param";
			item.value = (LPCTSTR) (_bstr_t) rsCF.m_ValuePar;
			ptquant->items.Add (item);

			item.name = "Comparation";
			item.value = rsCF.m_ShortName3;
			ptquant->items.Add (item);
			
			list.Add (ptquant);
			rsCF.MoveNext();
		}
		rsCF.Close();
	}
	else return "";

	q = "SELECT * \
		 FROM taTask, tdKLQuantifier, tmMatrix, tsCompareType,\
		      tsKLQuantifierType, tsKLQuantifierValueType, tsTaskSubType \
		 WHERE taTask.MatrixID=tmMatrix.MatrixID \
		   AND taTask.TaskSubTypeID=tsTaskSubType.TaskSubTypeID \
		   AND tdKLQuantifier.TaskID=taTask.TaskID \
		   AND tsKLQuantifierType.KLQuantifierTypeID=tdKLQuantifier.KLQuantifierTypeID \
		   AND tsKLQuantifierValueType.KLQuantifierValueTypeID=tdKLQuantifier.KLQuantifierValueTypeID \
		   AND tsCompareType.CompareTypeID=tdKLQuantifier.CompareTypeID";

	try
	{
		result = rsKL.Open(AFX_DB_USE_DEFAULT_TYPE, q);
	}
	catch (CDBException* e)
	{
		exc = true;
		CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
		e->Delete ();
	}
	if (exc) return "";
	
	if (result)
	{
		//iteration on query results
		while (!rsKL.IsEOF())
		{
			ptquant = new (Quantifier_Meta);
			ptquant->db_name = db_name;
			ptquant->matrix_name = rsKL.m_Name2;
			ptquant->name = rsKL.m_Name4;
			ptquant->task_name = rsKL.m_Name;
			ptquant->task_type = rsKL.m_Name6;
			ptquant->type = "N/A";
			hlp.Format ("%d", rsKL.m_KLQuantifierID);
			hlp = "quantKL" + hlp;
			ptquant->id = hlp;
			
			item.name = "Value type";
			item.value = rsKL.m_Name5;
			ptquant->items.Add (item);

			item.name = "From Column";
			item.value = (LPCTSTR) (_bstr_t) rsKL.m_FromCol;
			ptquant->items.Add (item);

			item.name = "To Column";
			item.value = (LPCTSTR) (_bstr_t) rsKL.m_ToCol;
			ptquant->items.Add (item);

			item.name = "From Row";
			item.value = (LPCTSTR) (_bstr_t) rsKL.m_FromRow;
			ptquant->items.Add (item);

			item.name = "To Row";
			item.value = (LPCTSTR) (_bstr_t) rsKL.m_ToRow;
			ptquant->items.Add (item);

			item.name = "Param";
			item.value = (LPCTSTR) (_bstr_t) rsKL.m_ValuePar;
			ptquant->items.Add (item);

			item.name = "Comparation";
			item.value = rsKL.m_ShortName;
			ptquant->items.Add (item);
			
			list.Add (ptquant);
			rsKL.MoveNext();
		}
		rsKL.Close();
	}
	else return "";

	q = "SELECT * \
		 FROM taTask, tdDFQuantifier, tmMatrix, tsCompareType,\
		      tsDFQuantifierType, tsDFQuantifierValueType, \
			  tsSDQuantifierSourceType, tsTaskSubType \
		 WHERE taTask.MatrixID=tmMatrix.MatrixID \
		   AND taTask.TaskSubTypeID=tsTaskSubType.TaskSubTypeID \
		   AND tdDFQuantifier.TaskID=taTask.TaskID \
		   AND tsDFQuantifierType.DFQuantifierTypeID=tdDFQuantifier.DFQuantifierTypeID \
		   AND tsDFQuantifierValueType.DFQuantifierValueTypeID=tdDFQuantifier.DFQuantifierValueTypeID \
		   AND tsCompareType.CompareTypeID=tdDFQuantifier.CompareTypeID \
		   AND tsSDQuantifierSourceType.SDQuantifierSourceTypeID=tdDFQuantifier.SDQuantifierSourceTypeID";

	try
	{
		result = rsDF.Open(AFX_DB_USE_DEFAULT_TYPE, q);
	}
	catch (CDBException* e)
	{
		exc = true;
		CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
		e->Delete ();
	}
	if (exc) return "";
	
	if (result)
	{
		//iteration on query results
		while (!rsDF.IsEOF())
		{
			ptquant = new (Quantifier_Meta);
			ptquant->db_name = db_name;
			ptquant->matrix_name = rsDF.m_Name2;
			ptquant->name = rsDF.m_Name4;
			ptquant->task_name = rsDF.m_Name;
			ptquant->task_type = rsDF.m_Name7;
			ptquant->type = "N/A";
			hlp.Format ("%d", rsDF.m_DFQuantifierID);
			hlp = "quantDF" + hlp;
			ptquant->id = hlp;
			
			item.name = "Value type";
			item.value = rsDF.m_Name5;
			ptquant->items.Add (item);

			item.name = "Param";
			item.value = (LPCTSTR) (_bstr_t) rsDF.m_ValuePar;
			ptquant->items.Add (item);

			item.name = "Comparation";
			item.value = rsDF.m_ShortName;
			ptquant->items.Add (item);

			item.name = "Source";
			item.value = rsDF.m_Name6;
			ptquant->items.Add (item);
			
			list.Add (ptquant);
			rsDF.MoveNext();
		}
		rsDF.Close();
	}
	else return "";

	q = "SELECT * \
		 FROM taTask, tdDCQuantifier, tmMatrix, tsCompareType,\
		      tsDCQuantifierType, tsDCQuantifierValueType, \
			  tsSDQuantifierSourceType, tsTaskSubType \
		 WHERE taTask.MatrixID=tmMatrix.MatrixID \
		   AND taTask.TaskSubTypeID=tsTaskSubType.TaskSubTypeID \
		   AND tdDCQuantifier.TaskID=taTask.TaskID \
		   AND tsDCQuantifierType.DCQuantifierTypeID=tdDCQuantifier.DCQuantifierTypeID \
		   AND tsDCQuantifierValueType.DCQuantifierValueTypeID=tdDCQuantifier.DCQuantifierValueTypeID \
		   AND tsCompareType.CompareTypeID=tdDCQuantifier.CompareTypeID \
		   AND tsSDQuantifierSourceType.SDQuantifierSourceTypeID=tdDCQuantifier.SDQuantifierSourceTypeID";

	try
	{
		result = rsDC.Open(AFX_DB_USE_DEFAULT_TYPE, q);
	}
	catch (CDBException* e)
	{
		exc = true;
		CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
		e->Delete ();
	}
	if (exc) return "";
	
	if (result)
	{
		//iteration on query results
		while (!rsDC.IsEOF())
		{
			ptquant = new (Quantifier_Meta);
			ptquant->db_name = db_name;
			ptquant->matrix_name = rsDC.m_Name2;
			ptquant->name = rsDC.m_Name4;
			ptquant->task_name = rsDC.m_Name;
			ptquant->task_type = rsDC.m_Name7;
			ptquant->type = "N/A";
			hlp.Format ("%d", rsDC.m_DCQuantifierID);
			hlp = "quantDC" + hlp;
			ptquant->id = hlp;
			
			item.name = "Value type";
			item.value = rsDC.m_Name5;
			ptquant->items.Add (item);

			item.name = "Param";
			item.value = (LPCTSTR) (_bstr_t) rsDC.m_ValuePar;
			ptquant->items.Add (item);

			item.name = "Comparation";
			item.value = rsDC.m_ShortName;
			ptquant->items.Add (item);

			item.name = "Source";
			item.value = rsDC.m_Name6;
			ptquant->items.Add (item);

			item.name = "From Column";
			item.value = (LPCTSTR) (_bstr_t) rsKL.m_FromCol;
			ptquant->items.Add (item);

			item.name = "To Column";
			item.value = (LPCTSTR) (_bstr_t) rsKL.m_ToCol;
			ptquant->items.Add (item);
			
			list.Add (ptquant);
			rsDC.MoveNext();
		}
		rsDC.Close();
	}
	else return "";

	q = "SELECT * \
		 FROM taTask, tdDKQuantifier, tmMatrix, tsCompareType,\
		      tsDKQuantifierType, tsDKQuantifierValueType, \
			  tsSDQuantifierSourceType, tsTaskSubType \
		 WHERE taTask.MatrixID=tmMatrix.MatrixID \
		   AND taTask.TaskSubTypeID=tsTaskSubType.TaskSubTypeID \
		   AND tdDKQuantifier.TaskID=taTask.TaskID \
		   AND tsDKQuantifierType.DKQuantifierTypeID=tdDKQuantifier.DKQuantifierTypeID \
		   AND tsDKQuantifierValueType.DKQuantifierValueTypeID=tdDKQuantifier.DKQuantifierValueTypeID \
		   AND tsCompareType.CompareTypeID=tdDKQuantifier.CompareTypeID \
		   AND tsSDQuantifierSourceType.SDQuantifierSourceTypeID=tdDKQuantifier.SDQuantifierSourceTypeID";

	try
	{
		result = rsDK.Open(AFX_DB_USE_DEFAULT_TYPE, q);
	}
	catch (CDBException* e)
	{
		exc = true;
		CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
		e->Delete ();
	}
	if (exc) return "";
	
	if (result)
	{
		//iteration on query results
		while (!rsDK.IsEOF())
		{
			ptquant = new (Quantifier_Meta);
			ptquant->db_name = db_name;
			ptquant->matrix_name = rsDK.m_Name2;
			ptquant->name = rsDK.m_Name4;
			ptquant->task_name = rsDK.m_Name;
			ptquant->task_type = rsDK.m_Name7;
			ptquant->type = "N/A";
			hlp.Format ("%d", rsDK.m_DKQuantifierID);
			hlp = "quantDK" + hlp;
			ptquant->id = hlp;
			
			item.name = "Value type";
			item.value = rsDK.m_Name5;
			ptquant->items.Add (item);

			item.name = "Param";
			item.value = (LPCTSTR) (_bstr_t) rsDK.m_ValuePar;
			ptquant->items.Add (item);

			item.name = "Comparation";
			item.value = rsDK.m_ShortName;
			ptquant->items.Add (item);

			item.name = "Source";
			item.value = rsDK.m_Name6;
			ptquant->items.Add (item);

			item.name = "From Column";
			item.value = (LPCTSTR) (_bstr_t) rsKL.m_FromCol;
			ptquant->items.Add (item);

			item.name = "To Column";
			item.value = (LPCTSTR) (_bstr_t) rsKL.m_ToCol;
			ptquant->items.Add (item);

			item.name = "From Row";
			item.value = (LPCTSTR) (_bstr_t) rsKL.m_FromRow;
			ptquant->items.Add (item);

			item.name = "To Row";
			item.value = (LPCTSTR) (_bstr_t) rsKL.m_ToRow;
			ptquant->items.Add (item);
			
			list.Add (ptquant);
			rsDK.MoveNext();
		}
		rsDK.Close();
	}
	else return "";

	//creation of xml string
	//load DTD
	try
	{
		buf = Get_DTD ();
	}
	catch (...)
	{
		CLMSock::ReportError (12, LMERR_DTD_ERROR);
		return "";
	}
	//create xml data
	buf = buf + " <active_list> ";
	int i;
    for (i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert ();
	}
	buf += " </active_list>";

	for (i = 0; i < list.GetSize (); i++)
	{
		list.GetAt (i)->items.RemoveAll ();
		delete (list.GetAt (i));
	}
	list.RemoveAll ();

	return buf;
}

// ---AP Task

CString fLMTask (void* hSource)
{
	CString buf = "";
	CString hlp;
	CString hlp1;
	CString db_name = ((CDatabase *) hSource)->GetDatabaseName ();
	CString q_hyp;

	int hours;
	int minutes;
	int seconds;
	double secf;
	long up;
	long down;

	BOOL result;
	bool exc = false;

	TTask_Meta_Array list;
	Task_Meta * pttask;
	
	Task_Recordset rs ((CDatabase *) hSource);
	tiHypothesis_Recordset rs_hyp ((CDatabase *) hSource);

	long hyp_cnt = 0; //number of hypothesis

	LPCTSTR q = "SELECT * \
				 FROM taTask, tmMatrix, tsTaskSubType \
				 WHERE taTask.MatrixID=tmMatrix.MatrixID \
				   AND taTask.TaskSubTypeID=tsTaskSubType.TaskSubTypeID";

	try
	{
		result = rs.Open(AFX_DB_USE_DEFAULT_TYPE, q);
	}
	catch (CDBException* e)
	{
		exc = true;
		CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
		e->Delete ();
	}
	if (exc) return "";
	
	if (result)
	{
		//iteration on query results
		while (!rs.IsEOF())
		{
			pttask = new (Task_Meta);
			pttask->db_name = db_name;
			try
			{
				pttask->gen_start_time =
					get_date_in_user_format (rs.m_GenerationStartTime) + " ";
				pttask->gen_start_time += get_time_in_user_format (rs.m_GenerationStartTime);
				pttask->gen_start_time.Replace ("/", ".");
			}
			catch (...)
			{
				pttask->gen_start_time = rs.m_GenerationStartTime.Format ("%c");
			}
			secf = rs.m_GenerationTotalTime / 1000;
			up = (long) ceil (secf);
			down = (long) floor (secf);
			if ((up - secf) < 0.5) seconds = up;
			else seconds = down;
			hours = seconds / 3600;
			seconds = seconds - hours * 3600;
			minutes = (int) floor (float(seconds / 60));
			seconds = seconds - minutes * 60;
			hlp1.Format ("%d", hours);
			if (hlp1.GetLength () == 1) hlp1 = "0" + hlp1;
			hlp = hlp1 + ":";
			hlp1.Format ("%d", minutes);
			if (hlp1.GetLength () == 1) hlp1 = "0" + hlp1;
			hlp += hlp1;
			hlp += ":";
			hlp1.Format ("%d", seconds);
			if (hlp1.GetLength () == 1) hlp1 = "0" + hlp1;
			hlp += hlp1;
			pttask->gen_total_time = hlp;

			hlp.Format ("%d", rs.m_TaskID);
			pttask->id = "Task" + hlp;
			pttask->matrix_name = rs.m_Name2;
			pttask->num_tests.Format ("%d", rs.m_GenerationNrOfTests);
			pttask->task_name = rs.m_Name;
			pttask->task_type = rs.m_Name3;
			q_hyp = "SELECT * \
					 FROM tiHypothesis \
					 WHERE TaskID=" + hlp;
			try
			{
				result = rs_hyp.Open (AFX_DB_USE_DEFAULT_TYPE, q_hyp);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				hyp_cnt = 0;
				while (!rs_hyp.IsEOF())
				{
					hyp_cnt++;
					rs_hyp.MoveNext ();
				}
				rs_hyp.Close ();
			}
			else return "";
			pttask->num_hyp.Format ("%d", hyp_cnt);
			if (hyp_cnt >= HYPOTHESIS_LIMIT)
			{
				pttask->gen_state = "Limit of hypotheses reached";
			}
			else if (rs.m_GenerationInterrupted)
			{
				pttask->gen_state = "Generation interrupted";
			}
			else if (rs.m_HypothesisGenerated)
			{
				pttask->gen_state = "Hypotheses generated";
			}
			else pttask->gen_state = "Modified task has not been processed yet";
			list.Add (pttask);
			rs.MoveNext();
		}
		rs.Close();
	}
	else return "";

	//creation of xml string
	//load DTD
	try
	{
		buf = Get_DTD ();
	}
	catch (...)
	{
		CLMSock::ReportError (12, LMERR_DTD_ERROR);
		return "";
	}
	//create xml data
	buf = buf + " <active_list> ";
	int i;
    for (i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert ();
	}
	buf += " </active_list>";

	for (i = 0; i < list.GetSize (); i++)
		delete (list.GetAt (i));
	list.RemoveAll ();

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

	BOOL result;
	bool exc = false;


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

	try
	{
		result = rs.Open(AFX_DB_USE_DEFAULT_TYPE, q);
	}
	catch (CDBException* e)
	{
		exc = true;
		CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
		e->Delete ();
	}
	if (exc) return "";
	
	if (result)
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
				if (ptklcdnt->cedent_type == "Antecedent")
					ptklcdnt->cedent_type = "Row attributes";
				else if (ptklcdnt->cedent_type == "Succedent")
					ptklcdnt->cedent_type = "Column attributes";
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
				try
				{
					result = rs_lit.Open(AFX_DB_USE_DEFAULT_TYPE, q_lit);
				}
				catch (CDBException* e)
				{
					exc = true;
					CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
					e->Delete ();
				}
				if (exc) return "";
				
				if (result)
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
						try
						{
							result = rs_cat.Open(AFX_DB_USE_DEFAULT_TYPE, q_cat);
						}
						catch (CDBException* e)
						{
							exc = true;
							CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
							e->Delete ();
						}
						if (exc) return "";
						
						if (result)
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
	try
	{
		buf = Get_DTD ();
	}
	catch (...)
	{
		CLMSock::ReportError (12, LMERR_DTD_ERROR);
		return "";
	}
	//create xml data
	buf = buf + " <active_list> ";
	int i;
    for (i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert ();
	}
	buf += " </active_list>";

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

	BOOL result;
	bool exc = false;


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

	try
	{
		result = rs.Open(AFX_DB_USE_DEFAULT_TYPE, q);
	}
	catch (CDBException* e)
	{
		exc = true;
		CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
		e->Delete ();
	}
	if (exc) return "";
	
	if (result)
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
				ptcfcdnt->cedent_type = "Attributes";
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
				try
				{
					result = rs_lit.Open(AFX_DB_USE_DEFAULT_TYPE, q_lit);
				}
				catch (CDBException* e)
				{
					exc = true;
					CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
					e->Delete ();
				}
				if (exc) return "";
				
				if (result)
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
						try
						{
							result = rs_cat.Open(AFX_DB_USE_DEFAULT_TYPE, q_cat);
						}
						catch (CDBException* e)
						{
							exc = true;
							CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
							e->Delete ();
						}
						if (exc) return "";
						
						if (result)
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
	try
	{
		buf = Get_DTD ();
	}
	catch (...)
	{
		CLMSock::ReportError (12, LMERR_DTD_ERROR);
		return "";
	}
	//create xml data
	buf = buf + " <active_list> ";
	int i;
    for (i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert ();
	}
	buf += " </active_list>";

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
	long c_id;
	long c_id_tst = 0; //test, wheather the new sub cedent appears
	long l_id;
	long l_id_tst = 0; //test, wheather the new literal appears
	long c = 0; //counter - help variable

	BOOL result;
	bool exc = false;
	BOOL missing_type = FALSE;

	TBool_Cedent_Meta_Array list;
	Bool_Cedent_Meta * ptboolcdnt;

	Bool_Cedent_Recordset rs ((CDatabase *) hSource);
	Equivalence_Lit_Rs rs_eq ((CDatabase *) hSource);
	TCategory_Scan rs_cat ((CDatabase *) hSource);
	TEmpty_Cedents_Recordset rs_em ((CDatabase *) hSource);
	TLit_Scan_Recordset rs_lit ((CDatabase *) hSource);

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

	try
	{
		result = rs.Open(AFX_DB_USE_DEFAULT_TYPE, q);
	}
	catch (CDBException* e)
	{
		exc = true;
		CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
		e->Delete ();
	}
	if (exc) return "";
	
	if (result)
	{
		//iteration on query results
		while (!rs.IsEOF())
		{
			c++;
			c_id = rs.m_CedentDID;
			l_id = rs.m_LiteralDID;
			if (c_id != c_id_tst) //new sub cedent
			{
				literal_cnt = 0;
				ptboolcdnt = new (Bool_Cedent_Meta);
				ptboolcdnt->db_name = db_name;
				hlp.Format ("%d", rs.m_CedentDID);
				ptboolcdnt->id = "cdnt" + hlp;
				ptboolcdnt->matrix_name = rs.m_Name4;
				ptboolcdnt->task_name = rs.m_Name;
				ptboolcdnt->task_type = rs.m_Name10;
				ptboolcdnt->cedent_type = rs.m_Name6;
				hlp = rs.m_Name2;
				hlp.Replace ("&", "&amp;");
				hlp.Replace ("<", "&lt;");
				hlp.Replace (">", "&gt;");
				ptboolcdnt->name = hlp;
				hlp.Format ("%d", rs.m_MinLen);
				hlp1.Format ("%d", rs.m_MaxLen);
				hlp += " - ";
				hlp += hlp1;
				ptboolcdnt->length = hlp;
				list.Add (ptboolcdnt);
			}
			if (l_id != l_id_tst) //new literal
			{
				literal_cnt++;
				ptboolcdnt->literal_cnt.Format ("%d", literal_cnt);
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
					try
					{
						result = rs_cat.Open(AFX_DB_USE_DEFAULT_TYPE, q_cat);
					}
					catch (CDBException* e)
					{
						exc = true;
						CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
						e->Delete ();
					}
					if (exc) return "";
					
					if (result)
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
				try
				{
					result = rs_eq.Open(AFX_DB_USE_DEFAULT_TYPE, q_eq);
				}
				catch (CDBException* e)
				{
					exc = true;
					CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
					e->Delete ();
				}
				if (exc) return "";
				
				if (result)
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
				try
				{
					result = rs_cat.Open(AFX_DB_USE_DEFAULT_TYPE, q_cat);
				}
				catch (CDBException* e)
				{
					exc = true;
					CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
					e->Delete ();
				}
				if (exc) return "";
				
				if (result)
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
				ptboolcdnt->lit_list.Add (lit);
			}
			l_id_tst = l_id;
			c_id_tst = c_id;
			rs.MoveNext();
		}
		rs.Close();
	}
	else return "";
	//add empty subcedents
	try
	{
		result = rs_em.Open(AFX_DB_USE_DEFAULT_TYPE, q_em);
	}
	catch (CDBException* e)
	{
		exc = true;
		CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
		e->Delete ();
	}
	if (exc) return "";
	
	if (result)
	{
		//iteration on query results
		while (!rs_em.IsEOF())
		{
			hlp.Format ("%d", rs_em.m_CedentDID);
			q_lit = "SELECT * FROM tdLiteralD WHERE CedentDID=" + hlp;
			c = 0;
			try
			{
				result = rs_lit.Open (AFX_DB_USE_DEFAULT_TYPE, q_lit);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
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
				ptboolcdnt = new (Bool_Cedent_Meta);
				ptboolcdnt->literal_cnt.Format ("%d", 0);
				ptboolcdnt->name = rs_em.m_Name2;
				hlp.Format ("%d", rs_em.m_MinLen);
				hlp1.Format ("%d", rs_em.m_MaxLen);
				hlp += " - ";
				hlp += hlp1;
				ptboolcdnt->length = hlp;
				ptboolcdnt->lit_list.RemoveAll ();
				ptboolcdnt->db_name = db_name;
				hlp.Format ("%d", rs_em.m_CedentDID);
				ptboolcdnt->id = "cdnt" + hlp;
				ptboolcdnt->matrix_name = rs_em.m_Name3;
				ptboolcdnt->task_name = rs_em.m_Name;
				ptboolcdnt->task_type = rs_em.m_Name5;
				ptboolcdnt->cedent_type = rs_em.m_Name4;
				list.Add (ptboolcdnt);
			}
			rs_em.MoveNext ();
		}
		rs_em.Close ();
	}
	else return "";

	//creation of xml string
	//load DTD
	try
	{
		buf = Get_DTD ();
	}
	catch (...)
	{
		CLMSock::ReportError (12, LMERR_DTD_ERROR);
		return "";
	}
	//create xml data
	buf = buf + " <active_list> ";
	int i;
    for (i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert ();
	}
	buf += " </active_list>";

	for (i = 0; i < list.GetSize (); i++)
	{
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

	BOOL result;
	bool exc = false;

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
	try
	{
		result = rs.Open(AFX_DB_USE_DEFAULT_TYPE, q);
	}
	catch (CDBException* e)
	{
		exc = true;
		CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
		e->Delete ();
	}
	if (exc) return "";
	
	if (result)
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
			try
			{
				result = rscat.Open(AFX_DB_USE_DEFAULT_TYPE, qcat);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
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
	try
	{
		buf = Get_DTD ();
	}
	catch (...)
	{
		CLMSock::ReportError (12, LMERR_DTD_ERROR);
		return "";
	}
	//create xml data
	buf = buf + " <active_list> ";
	int i;
    for (i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert ();
	}
	buf += " </active_list>";

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

	TCategory_Meta_Array list;
	Category_Meta * ptcat;

	TCategory_Recordset rs ((CDatabase *) hSource);
	TCatDefEnum rs_def_enum ((CDatabase *) hSource);
	TCatDefInt rs_def_int_l ((CDatabase *) hSource);
	TCatDefInt rs_def_int_r ((CDatabase *) hSource);
	TCatOrder rs_ord ((CDatabase *) hSource);

	TCatDefArray def;

	CString subqenum;
	CString subqintervall;
	CString subqintervalr;
	CString qord;
	BOOL result;
	bool exc = false;

	LPCTSTR q =	
		"SELECT * \
		 FROM	tmAttribute, tmCategory, tmMatrix, tmQuantity, tsBoolType, tsCategorySubType \
		 WHERE tmCategory.QuantityID=tmQuantity.QuantityID \
			AND tmQuantity.AttributeID=tmAttribute.AttributeID \
			AND tmAttribute.MatrixID=tmMatrix.MatrixID \
			AND tmCategory.CategorySubTypeID=tsCategorySubType.CategorySubTypeID \
			AND tmCategory.BoolTypeID = tsBoolType.BoolTypeID \
			ORDER BY tmCategory.CategoryID";

	try
	{
		result = rs.Open(AFX_DB_USE_DEFAULT_TYPE, q);
	}
	catch (CDBException* e)
	{
		exc = true;
		CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
		e->Delete ();
	}
	if (exc) return "";
	
	if (result)
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
				try
				{
					result = rs_def_enum.Open(AFX_DB_USE_DEFAULT_TYPE, subqenum);
				}
				catch (CDBException* e)
				{
					exc = true;
					CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
					e->Delete ();
				}
				if (exc) return "";
				if (result)
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
				try
				{
					result = (rs_def_int_l.Open(AFX_DB_USE_DEFAULT_TYPE, subqintervall))
							  &&
							 (rs_def_int_r.Open(AFX_DB_USE_DEFAULT_TYPE, subqintervalr));
				}
				catch (CDBException* e)
				{
					exc = true;
					CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
					e->Delete ();
				}
				if (exc) return "";
				if (result)
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
			ptcat->ctgr_freq = "N/A";
			list.Add (ptcat);
			rs.MoveNext();
		}
		rs.Close();
	}
	else return "";

	//creation of xml string
	//load DTD
	try
	{
		buf = Get_DTD ();
	}
	catch (...)
	{
		CLMSock::ReportError (12, LMERR_DTD_ERROR);
		return "";
	}
	//create xml data
	buf = buf + " <active_list> ";
	int i;
    for (i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert ();
	}
	buf += " </active_list>";

	for (i = 0; i < list.GetSize (); i++)
	{
		delete (list.GetAt (i));
	}
	list.RemoveAll ();

	return buf;
}


// --- AP 4ft-hypothese

CString fLM4fthyp_hlp(void * hSource, bool ar2nl)
{
	CString buf;
	CString db_name = ((CDatabase *) hSource)->GetDatabaseName ();
	CString id_hlp;
	THyp_4ft_Meta_Array list;
	Hyp_4ft_Recordset rs ((CDatabase *) hSource);
	TCoef_type_Recordset rs_coef_type ((CDatabase *) hSource);
	Hyp_4ft_Meta * pthyp;
	long h_id;
	long l_id;
	long c_id;
	long ld_id;//store the tdCedentDID
	long h_id_tst = 0;//test variable - values from previous iteration

	BOOL result;
	bool exc = false;

	BOOL neg_lit;
	CString neg_lit_smbl;
	
	CString ced_name;
	CString q_name;
	CString q_value;
	CString q_type;
	CString q_coef_type;
	CString q = "SELECT * \
				 FROM taTask,tiCoefficient,  tiHypothesis, tiLiteralI, tmCategory, \
				      tmMatrix, tmQuantity, tsCedentType, tsTaskSubType \
				 WHERE tiCoefficient.TaskID=taTask.TaskID \
				   AND taTask.MatrixID=tmMatrix.MatrixID \
				   AND tiHypothesis.HypothesisID=tiLiteralI.HypothesisID \
				   AND tiLiteralI.LiteralIID=tiCoefficient.LiteralIID \
				   AND tiCoefficient.CategoryID=tmCategory.CategoryID \
				   AND tmCategory.QuantityID=tmQuantity.QuantityID \
				   AND tsCedentType.CedentTypeID=tiLiteralI.CedentTypeID \
				   AND tsTaskSubType.ShortName=";
	q +=									 "'CDASSOC'";
	q +=		  "AND taTask.TaskSubTypeID=tsTaskSubType.TaskSubTypeID \
				 ORDER BY taTask.TaskID, tiHypothesis.HypothesisID, \
						  tiLiteralI.CedentTypeID, tmQuantity.QuantityID, \
						  tmCategory.Ord";
	//load data from metabase
	try
	{
		result = rs.Open(AFX_DB_USE_DEFAULT_TYPE, q);
	}
	catch (CDBException* e)
	{
		exc = true;
		CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
		e->Delete ();
	}
	if (exc) return "";
	
	if (result)
	{
		//iteration on query results
		while (!rs.IsEOF())
		{
			h_id = rs.m_HypothesisID;
			l_id = rs.m_LiteralIID2;
			ld_id = rs.m_LiteralDID;
			id_hlp.Format ("%d", ld_id);
			//exactly one row expected to return by the following query:
			q_coef_type = "SELECT * \
						   FROM tdLiteralD, tsCoefficientType \
						  WHERE LiteralDID=" + id_hlp;
			q_coef_type +=
				" AND tdLiteralD.CoefficientTypeID=tsCoefficientType.CoefficientTypeID";
			try
			{
				result = rs_coef_type.Open(AFX_DB_USE_DEFAULT_TYPE, q_coef_type);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				while (!rs_coef_type.IsEOF())
				{
					q_type = rs_coef_type.m_ShortName;
					q_type.Replace ("&", "&amp;");
					q_type.Replace (">", "&gt;");
					q_type.Replace ("<", "&lt;");
					rs_coef_type.MoveNext ();
				}
				rs_coef_type.Close ();
			}
			else return "";
			neg_lit = rs.m_Negation;
			ced_name = rs.m_Name5;
			c_id = rs.m_CategoryID2;
			q_name = rs.m_Name4;
			q_name.Replace ("&", "&amp;");
			q_name.Replace (">", "&gt;");
			q_name.Replace ("<", "&lt;");
			q_value = rs.m_Name2;
			q_value.Replace ("&", "&amp;");
			q_value.Replace (">", "&gt;");
			q_value.Replace ("<", "&lt;");
			if (h_id != h_id_tst)
			{
				pthyp = new (Hyp_4ft_Meta);
				pthyp->ar2nl_sentences = "";
				id_hlp.Format ("%d", h_id);
				if (!ar2nl) pthyp->id = "hyp4ft" + id_hlp;
				else pthyp->id = "hyp4ftar2nl" + id_hlp;
				pthyp->db_name = db_name;
				pthyp->matrix_name = rs.m_Name3;
				pthyp->task_name = rs.m_Name;
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
				pthyp->low_bnd_imp = pthyp->get_low_bnd_imp ();
				pthyp->up_bnd_imp = pthyp->get_up_bnd_imp ();
				pthyp->low_bnd_dbl_imp = pthyp->get_low_bnd_dbl_imp ();
				pthyp->up_bnd_dbl_imp = pthyp->get_up_bnd_dbl_imp ();
				pthyp->low_bnd_eq = pthyp->get_low_bnd_eq ();
				pthyp->up_bnd_eq = pthyp->get_up_bnd_eq ();
				pthyp->fisher = pthyp->get_fisher ();
				pthyp->chi_sq = pthyp->get_chi_sq ();

				ar2nl_err = false;
				try
				{
					if (ar2nl) pthyp->ar2nl_sentences = Get_4ftAR2NL (h_id, db_name);
				}
				catch (...)
				{
					ar2nl_err = true;
				}
				if (ar2nl_err)
				{
					CLMSock::ReportError (10, LMERR_AR2NL_ERR);
					return "";
				}

				pthyp->ant_id = "ant" + pthyp->id;
				pthyp->suc_id = "suc" + pthyp->id;
				pthyp->con_id = "con" + pthyp->id;

				list.Add (pthyp);
			}

			if (ced_name == "Antecedent")
			{
				Hyp_tiLiteral x;
				id_hlp.Format ("%d", l_id);
				x.id = "tiLit" + id_hlp + pthyp->id;
				id_hlp.Format ("%d", c_id);
				x.id = x.id + id_hlp;
				if (neg_lit) neg_lit_smbl = "�"; else neg_lit_smbl = "";
				x.quant = neg_lit_smbl + q_name;
				x.value = q_value;
				x.coef_type = q_type;
				pthyp->antecedent.Add (x);
			}
			else if (ced_name == "Succedent")
			{
				Hyp_tiLiteral x;
				id_hlp.Format ("%d", l_id);
				x.id = "tiLit" + id_hlp + pthyp->id;
				id_hlp.Format ("%d", c_id);
				x.id = x.id + id_hlp;
				if (neg_lit) neg_lit_smbl = "�"; else neg_lit_smbl = "";
				x.quant = neg_lit_smbl + q_name;
				x.value = q_value;
				x.coef_type = q_type;
				pthyp->succedent.Add (x);
			}
			else if (ced_name == "Condition")
			{
				Hyp_tiLiteral x;
				id_hlp.Format ("%d", l_id);
				x.id = "tiLit" + id_hlp + pthyp->id;
				id_hlp.Format ("%d", c_id);
				x.id = x.id + id_hlp;
				if (neg_lit) neg_lit_smbl = "�"; else neg_lit_smbl = "";
				x.quant = neg_lit_smbl + q_name;
				x.value = q_value;
				x.coef_type = q_type;
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
	try
	{
		buf = Get_DTD ();
	}
	catch (...)
	{
		CLMSock::ReportError (12, LMERR_DTD_ERROR);
		return "";
	}

	//create xml data
	buf = buf + " <active_list> ";
	int i;
    for (i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert (ar2nl);
	}
	buf += " </active_list>";
	for (i = 0; i < list.GetSize (); i++)
	{
		delete (list.GetAt (i));
	}
	list.RemoveAll ();

	return buf;
}

CString fLM4fthyp (void * hSource)
{
	return fLM4fthyp_hlp (hSource, false);
}

CString fLM4fthyp_ar2nl(void* hSource)
{
	return fLM4fthyp_hlp (hSource, true);
}

// --- AP CF-hypothese

CString fLMCFhyp(void* hSource)
{
	CString buf;
	CString db_name = ((CDatabase *) hSource)->GetDatabaseName ();
	CString id_hlp;
	CString hlp;
	CString q_coef_type;

	THyp_CF_Meta_Array list;
	Hyp_CF_Recordset rs ((CDatabase *) hSource);
	tiCFFrequencyI_Recordset rs_freq ((CDatabase *) hSource);
	tmCategory_Recordset rs_attr ((CDatabase *) hSource);
	TCondition_Recordset rs_cond ((CDatabase *) hSource);
	TCoef_type_Recordset rs_coef_type ((CDatabase *) hSource);
	Hyp_CF_Meta * pthyp;

	long h_id;
	long ld_id;

	BOOL result;
	bool exc = false;;

	CString neg_lit_smbl;

	CString q_name;
	CString q_value;

	Hyp_tiLiteral lit;

	CString q = "SELECT * \
				 FROM taTask, tdCFLiteralD, tiHypothesisCF, tmMatrix, tmQuantity \
				 WHERE taTask.TaskID=tiHypothesisCF.TaskID \
				   AND taTask.MatrixID=tmMatrix.MatrixID \
				   AND tiHypothesisCF.CFLiteralDID=tdCFLiteralD.CFLiteralDID \
				   AND tdCFLiteralD.QuantityID=tmQuantity.QuantityID";
	//load data from metabase
	try
	{
		result = rs.Open(AFX_DB_USE_DEFAULT_TYPE, q);
	}
	catch (CDBException* e)
	{
		exc = true;
		CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
		e->Delete ();
	}
	if (exc) return "";
	
	if (result)
	{
		//iteration on query results
		while (!rs.IsEOF())
		{
			h_id = rs.m_HypothesisCFID;
			pthyp = new (Hyp_CF_Meta);
			id_hlp.Format ("%d", h_id);
			pthyp->id = "hypCF" + id_hlp;
			pthyp->db_name = db_name;
			pthyp->matrix_name = rs.m_Name2;
			pthyp->task_name = rs.m_Name;
			pthyp->quant = rs.m_Name3;
			pthyp->a_id = "attr_" + pthyp->id;
			pthyp->c_id = "cond_" + pthyp->id;

			id_hlp.Format ("%d", rs.m_HypothesisCFID);

			CString q_freq = "SELECT * \
							  FROM tiCFFrequencyI \
							  WHERE tiCFFrequencyI.HypothesisCFID=" + id_hlp +
							" ORDER BY Col";			
			try
			{
				result = rs_freq.Open(AFX_DB_USE_DEFAULT_TYPE, q_freq);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				while (!rs_freq.IsEOF())
				{
					pthyp->frequencies.Add (rs_freq.m_Frequency);
					rs_freq.MoveNext();
				}
				rs_freq.Close();
			}
			else return "";

			id_hlp.Format ("%d", rs.m_QuantityID2);
			CString q_attr = "SELECT * \
							  FROM tmCategory \
							  WHERE tmCategory.QuantityID=" + id_hlp;
			q_attr += " ORDER BY Ord";
			try
			{
				result = rs_attr.Open(AFX_DB_USE_DEFAULT_TYPE, q_attr);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				while (!rs_attr.IsEOF())
				{
					if (rs_attr.m_XCategory) goto next_attr_cf;
					hlp = rs_attr.m_Name;
					hlp.Replace ("&", "&amp;");
					hlp.Replace (">", "&gt;");
					hlp.Replace ("<", "&lt;");
					pthyp->attributes.Add (hlp);
next_attr_cf:
					rs_attr.MoveNext();
				}
				rs_attr.Close();
			}
			else return "";

			id_hlp.Format ("%d", rs.m_HypothesisID);
			CString q_cond = "SELECT * \
							  FROM tiCoefficient, tiLiteralI, tmCategory, tmQuantity \
							  WHERE tiLiteralI.LiteralIID=tiCoefficient.LiteralIID \
								AND tiCoefficient.CategoryID=tmCategory.CategoryID \
								AND tmCategory.QuantityID=tmQuantity.QuantityID \
								AND tiLiteralI.HypothesisID=" + id_hlp +
							" ORDER BY tmQuantity.QuantityID, tmCategory.Ord";
			try
			{
				result = rs_cond.Open(AFX_DB_USE_DEFAULT_TYPE, q_cond);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				while (!rs_cond.IsEOF())
				{
					if (rs_cond.m_Negation)
						neg_lit_smbl = "�";
					else
						neg_lit_smbl = "";
					id_hlp.Format ("%d", rs_cond.m_LiteralIID);
					lit.id = "tiCFLit" + id_hlp + pthyp->id;
					hlp = rs_cond.m_Name2;
					hlp.Replace ("&", "&amp;");
					hlp.Replace (">", "&gt;");
					hlp.Replace ("<", "&lt;");
					lit.quant = neg_lit_smbl + hlp;
					hlp = rs_cond.m_Name;
					hlp.Replace ("&", "&amp;");
					hlp.Replace (">", "&gt;");
					hlp.Replace ("<", "&lt;");
					lit.value = hlp;
					ld_id = rs_cond.m_LiteralDID;
					id_hlp.Format ("%d", ld_id);
					//exactly one row expected to return by the following query:
					q_coef_type = "SELECT * \
									 FROM tdLiteralD, tsCoefficientType \
									WHERE LiteralDID=" + id_hlp;
					q_coef_type +=
						" AND tdLiteralD.CoefficientTypeID=tsCoefficientType.CoefficientTypeID";
					try
					{
						result = rs_coef_type.Open(AFX_DB_USE_DEFAULT_TYPE, q_coef_type);
					}
					catch (CDBException* e)
					{
						exc = true;
						CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
						e->Delete ();
					}
					if (exc) return "";
					
					if (result)
					{
						while (!rs_coef_type.IsEOF())
						{
							hlp = rs_coef_type.m_ShortName;
							hlp.Replace ("&", "&amp;");
							hlp.Replace (">", "&gt;");
							hlp.Replace ("<", "&lt;");
							rs_coef_type.MoveNext ();
						}
						rs_coef_type.Close ();
					}
					else return "";
					lit.coef_type = hlp;
					pthyp->condition.Add (lit);
					rs_cond.MoveNext();
				}
				rs_cond.Close();
			}
			else return "";

			pthyp->asym = "Unknown";
			pthyp->avg_a = "Unknown";
			pthyp->avg_g = "Unknown";
			pthyp->dor_var = pthyp->get_dor_var ();
			hlp.Format ("%d", pthyp->get_max ());
			pthyp->max = hlp;
			pthyp->min = pthyp->get_min ();
			pthyp->nom_var = pthyp->get_nom_var ();
			pthyp->skew = "Unknown";
			pthyp->st_dev = "Unknown";
			hlp.Format ("%d", pthyp->get_sum ());
			pthyp->sum = hlp;
			pthyp->v = "Unknown";
			pthyp->var = "Unknown";

			list.Add (pthyp);
			rs.MoveNext();
		}
		rs.Close();
	}
	else return "";

	//creation of xml string
	
  
	//load DTD
	try
	{
		buf = Get_DTD ();
	}
	catch (...)
	{
		CLMSock::ReportError (12, LMERR_DTD_ERROR);
		return "";
	}

	//create xml data
	buf = buf + " <active_list> ";
	int i;
    for (i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert ();
	}
	buf += " </active_list>";

	for (i = 0; i < list.GetSize (); i++)
	{
		list.GetAt (i)->attributes.RemoveAll ();
		list.GetAt (i)->condition.RemoveAll ();
		list.GetAt (i)->frequencies.RemoveAll ();
		delete (list.GetAt (i));
	}
	list.RemoveAll ();

	return buf;
}

// --- AP SD4FT-hypothese

CString fLMSD4fthyp(void * hSource)
{
	CString buf;
	CString db_name = ((CDatabase *) hSource)->GetDatabaseName ();
	CString id_hlp;
	THyp_SD4ft_Meta_Array list;
	Hyp_SD4ft_Recordset rs ((CDatabase *) hSource);
	TCoef_type_Recordset rs_coef_type ((CDatabase *) hSource);
	Hyp_SD4ft_Meta * pthyp;
	long h_id;
	long l_id;
	long c_id;
	long h_id_tst = 0;//test variable - values from previous iteration
	long ld_id;//store the tdCedentDID

	BOOL result;
	bool exc = false;

	BOOL neg_lit;
	CString neg_lit_smbl;
	
	CString ced_name;
	CString q_name;
	CString q_value;
	CString q_type;
	CString q_coef_type;
	CString q = "SELECT * \
				 FROM taTask,tiCoefficient,  tiHypothesisDF, tiLiteralI, tmCategory, \
				      tmMatrix, tmQuantity, tsCedentType \
				 WHERE tiCoefficient.TaskID=taTask.TaskID \
				   AND taTask.MatrixID=tmMatrix.MatrixID \
				   AND tiHypothesisDF.HypothesisID=tiLiteralI.HypothesisID \
				   AND tiLiteralI.LiteralIID=tiCoefficient.LiteralIID \
				   AND tiCoefficient.CategoryID=tmCategory.CategoryID \
				   AND tmCategory.QuantityID=tmQuantity.QuantityID \
				   AND tsCedentType.CedentTypeID=tiLiteralI.CedentTypeID \
				 ORDER BY taTask.TaskID, tiHypothesisDF.HypothesisID, \
						  tiLiteralI.CedentTypeID, tmQuantity.QuantityID, \
						  tmCategory.Ord";
	//load data from metabase
	try
	{
		result = rs.Open(AFX_DB_USE_DEFAULT_TYPE, q);
	}
	catch (CDBException* e)
	{
		exc = true;
		CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
		e->Delete ();
	}
	if (exc) return "";
	
	if (result)
	{
		//iteration on query results
		while (!rs.IsEOF())
		{
			h_id = rs.m_HypothesisDFID;
			l_id = rs.m_LiteralIID2;
			ld_id = rs.m_LiteralDID;
			id_hlp.Format ("%d", ld_id);
			//exactly one row expected to return by the following query:
			q_coef_type = "SELECT * \
						   FROM tdLiteralD, tsCoefficientType \
						  WHERE LiteralDID=" + id_hlp;
			q_coef_type +=
				" AND tdLiteralD.CoefficientTypeID=tsCoefficientType.CoefficientTypeID";
			try
			{
				result = rs_coef_type.Open(AFX_DB_USE_DEFAULT_TYPE, q_coef_type);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				while (!rs_coef_type.IsEOF())
				{
					q_type = rs_coef_type.m_ShortName;
					q_type.Replace ("&", "&amp;");
					q_type.Replace (">", "&gt;");
					q_type.Replace ("<", "&lt;");
					rs_coef_type.MoveNext ();
				}
				rs_coef_type.Close ();
			}
			else return "";
			neg_lit = rs.m_Negation;
			ced_name = rs.m_Name5;
			c_id = rs.m_CategoryID2;
			q_name = rs.m_Name4;
			q_name.Replace ("&", "&amp;");
			q_name.Replace (">", "&gt;");
			q_name.Replace ("<", "&lt;");
			q_value = rs.m_Name2;
			q_value.Replace ("&", "&amp;");
			q_value.Replace (">", "&gt;");
			q_value.Replace ("<", "&lt;");
			if (h_id != h_id_tst)
			{
				pthyp = new (Hyp_SD4ft_Meta);
				id_hlp.Format ("%d", h_id);
				pthyp->id = "hypSD4ft" + id_hlp;
				pthyp->db_name = db_name;
				pthyp->matrix_name = rs.m_Name3;
				pthyp->task_name = rs.m_Name;
				pthyp->a.Format ("%d", rs.m_FirstFreqA);
				pthyp->b.Format ("%d", rs.m_FirstFreqB);
				pthyp->c.Format ("%d", rs.m_FirstFreqC);
				pthyp->d.Format ("%d", rs.m_FirstFreqD);
				pthyp->e.Format ("%d", rs.m_SecondFreqA);
				pthyp->f.Format ("%d", rs.m_SecondFreqB);
				pthyp->g.Format ("%d", rs.m_SecondFreqC);
				pthyp->h.Format ("%d", rs.m_SecondFreqD);

				pthyp->conf1 = (LPCTSTR) (_bstr_t)
					(pthyp->get_conf (rs.m_FirstFreqA, rs.m_FirstFreqB));
				pthyp->d_conf1 = (LPCTSTR) (_bstr_t)
					(pthyp->get_d_conf (rs.m_FirstFreqA, rs.m_FirstFreqB, rs.m_FirstFreqC));
				pthyp->e_conf1 = (LPCTSTR) (_bstr_t)
					(pthyp->get_e_conf (rs.m_FirstFreqA, rs.m_FirstFreqB, rs.m_FirstFreqC, rs.m_FirstFreqD));
				pthyp->support1 = (LPCTSTR) (_bstr_t)
					(pthyp->get_support (rs.m_FirstFreqA, rs.m_FirstFreqB, rs.m_FirstFreqC, rs.m_FirstFreqD));
				pthyp->completeness1 = (LPCTSTR) (_bstr_t)
					(pthyp->get_completeness (rs.m_FirstFreqA, rs.m_FirstFreqC));
				pthyp->avg_diff1 = (LPCTSTR) (_bstr_t)
					(pthyp->get_avg_diff (rs.m_FirstFreqA, rs.m_FirstFreqB, rs.m_FirstFreqC, rs.m_FirstFreqD));
				pthyp->low_bnd_imp1 =
					(pthyp->get_low_bnd_imp (rs.m_FirstFreqA, rs.m_FirstFreqB));
				pthyp->up_bnd_imp1 =
					(pthyp->get_up_bnd_imp (rs.m_FirstFreqA, rs.m_FirstFreqB));
				pthyp->low_bnd_dbl_imp1 =
					(pthyp->get_low_bnd_dbl_imp (rs.m_FirstFreqA, rs.m_FirstFreqB, rs.m_FirstFreqC));
				pthyp->up_bnd_dbl_imp1 =
					(pthyp->get_up_bnd_dbl_imp (rs.m_FirstFreqA, rs.m_FirstFreqB, rs.m_FirstFreqC));
				pthyp->low_bnd_eq1 =
					(pthyp->get_low_bnd_eq (rs.m_FirstFreqA, rs.m_FirstFreqB, rs.m_FirstFreqC, rs.m_FirstFreqD));
				pthyp->up_bnd_eq1 =
					(pthyp->get_up_bnd_eq (rs.m_FirstFreqA, rs.m_FirstFreqB, rs.m_FirstFreqC, rs.m_FirstFreqD));
				pthyp->fisher1 =
					(pthyp->get_fisher (rs.m_FirstFreqA, rs.m_FirstFreqB, rs.m_FirstFreqC, rs.m_FirstFreqD));
				pthyp->chi_sq1 = (LPCTSTR) (_bstr_t)
					(pthyp->get_chi_sq (rs.m_FirstFreqA, rs.m_FirstFreqB, rs.m_FirstFreqC, rs.m_FirstFreqD));

				pthyp->conf2 = (LPCTSTR) (_bstr_t)
					(pthyp->get_conf (rs.m_SecondFreqA, rs.m_SecondFreqB));
				pthyp->d_conf2 = (LPCTSTR) (_bstr_t)
					(pthyp->get_d_conf (rs.m_SecondFreqA, rs.m_SecondFreqB, rs.m_SecondFreqC));
				pthyp->e_conf2 = (LPCTSTR) (_bstr_t)
					(pthyp->get_e_conf (rs.m_SecondFreqA, rs.m_SecondFreqB, rs.m_SecondFreqC, rs.m_SecondFreqD));
				pthyp->support2 = (LPCTSTR) (_bstr_t)
					(pthyp->get_support (rs.m_SecondFreqA, rs.m_SecondFreqB, rs.m_SecondFreqC, rs.m_SecondFreqD));
				pthyp->completeness2 = (LPCTSTR) (_bstr_t)
					(pthyp->get_completeness (rs.m_SecondFreqA, rs.m_SecondFreqC));
				pthyp->avg_diff2 = (LPCTSTR) (_bstr_t)
					(pthyp->get_avg_diff (rs.m_SecondFreqA, rs.m_SecondFreqB, rs.m_SecondFreqC, rs.m_SecondFreqD));
				pthyp->low_bnd_imp2 =
					(pthyp->get_low_bnd_imp (rs.m_SecondFreqA, rs.m_SecondFreqB));
				pthyp->up_bnd_imp2 =
					(pthyp->get_up_bnd_imp (rs.m_SecondFreqA, rs.m_SecondFreqB));
				pthyp->low_bnd_dbl_imp2 =
					(pthyp->get_low_bnd_dbl_imp (rs.m_SecondFreqA, rs.m_SecondFreqB, rs.m_SecondFreqC));
				pthyp->up_bnd_dbl_imp2 =
					(pthyp->get_up_bnd_dbl_imp (rs.m_SecondFreqA, rs.m_SecondFreqB, rs.m_SecondFreqC));
				pthyp->low_bnd_eq2 =
					(pthyp->get_low_bnd_eq (rs.m_SecondFreqA, rs.m_SecondFreqB, rs.m_SecondFreqC, rs.m_SecondFreqD));
				pthyp->up_bnd_eq2 =
					(pthyp->get_up_bnd_eq (rs.m_SecondFreqA, rs.m_SecondFreqB, rs.m_SecondFreqC, rs.m_SecondFreqD));
				pthyp->fisher2 =
					(pthyp->get_fisher (rs.m_SecondFreqA, rs.m_SecondFreqB, rs.m_SecondFreqC, rs.m_SecondFreqD));
				pthyp->chi_sq2 = (LPCTSTR) (_bstr_t)
					(pthyp->get_chi_sq (rs.m_SecondFreqA, rs.m_SecondFreqB, rs.m_SecondFreqC, rs.m_SecondFreqD));

				pthyp->dr_sum = (LPCTSTR) (_bstr_t) (
					pthyp->get_dr_sum (	rs.m_FirstFreqA, rs.m_FirstFreqB, rs.m_FirstFreqC, rs.m_FirstFreqD,
										rs.m_SecondFreqA, rs.m_SecondFreqB, rs.m_SecondFreqC, rs.m_SecondFreqD));
				pthyp->df_conf = (LPCTSTR) (_bstr_t) (pthyp->get_conf (rs.m_FirstFreqA, rs.m_FirstFreqB) -
					pthyp->get_conf (rs.m_SecondFreqA, rs.m_SecondFreqB));
				pthyp->df_dfui = (LPCTSTR) (_bstr_t) (pthyp->get_d_conf (rs.m_FirstFreqA, rs.m_FirstFreqB, rs.m_FirstFreqC) -
					pthyp->get_d_conf (rs.m_SecondFreqA, rs.m_SecondFreqB, rs.m_SecondFreqC));
				pthyp->df_fue = (LPCTSTR) (_bstr_t) (pthyp->get_e_conf (rs.m_FirstFreqA, rs.m_FirstFreqB, rs.m_FirstFreqC, rs.m_FirstFreqD) -
					pthyp->get_e_conf (rs.m_SecondFreqA, rs.m_SecondFreqB, rs.m_SecondFreqC, rs.m_SecondFreqD));
				pthyp->df_avg = (LPCTSTR) (_bstr_t) (pthyp->get_avg_diff (rs.m_FirstFreqA, rs.m_FirstFreqB, rs.m_FirstFreqC, rs.m_FirstFreqD) -
					pthyp->get_avg_diff (rs.m_SecondFreqA, rs.m_SecondFreqB, rs.m_SecondFreqC, rs.m_SecondFreqD));

				pthyp->ant_id = "ant" + pthyp->id;
				pthyp->suc_id = "suc" + pthyp->id;
				pthyp->con_id = "con" + pthyp->id;
				pthyp->set1_id = "set1" + pthyp->id;
				pthyp->set2_id = "set2" + pthyp->id;

				list.Add (pthyp);
			}

			if (ced_name == "Antecedent")
			{
				Hyp_tiLiteral x;
				id_hlp.Format ("%d", l_id);
				x.id = "tiLit" + id_hlp + pthyp->id;
				id_hlp.Format ("%d", c_id);
				x.id = x.id + id_hlp;
				if (neg_lit) neg_lit_smbl = "�"; else neg_lit_smbl = "";
				x.quant = neg_lit_smbl + q_name;
				x.value = q_value;
				x.coef_type = q_type;
				pthyp->antecedent.Add (x);
			}
			else if (ced_name == "Succedent")
			{
				Hyp_tiLiteral x;
				id_hlp.Format ("%d", l_id);
				x.id = "tiLit" + id_hlp + pthyp->id;
				id_hlp.Format ("%d", c_id);
				x.id = x.id + id_hlp;
				if (neg_lit) neg_lit_smbl = "�"; else neg_lit_smbl = "";
				x.quant = neg_lit_smbl + q_name;
				x.value = q_value;
				x.coef_type = q_type;
				pthyp->succedent.Add (x);
			}
			else if (ced_name == "Condition")
			{
				Hyp_tiLiteral x;
				id_hlp.Format ("%d", l_id);
				x.id = "tiLit" + id_hlp + pthyp->id;
				id_hlp.Format ("%d", c_id);
				x.id = x.id + id_hlp;
				if (neg_lit) neg_lit_smbl = "�"; else neg_lit_smbl = "";
				x.quant = neg_lit_smbl + q_name;
				x.value = q_value;
				x.coef_type = q_type;
				pthyp->condition.Add (x);
			}
			else if (ced_name == "First set")
			{
				Hyp_tiLiteral x;
				id_hlp.Format ("%d", l_id);
				x.id = "tiLit" + id_hlp + pthyp->id;
				id_hlp.Format ("%d", c_id);
				x.id = x.id + id_hlp;
				if (neg_lit) neg_lit_smbl = "�"; else neg_lit_smbl = "";
				x.quant = neg_lit_smbl + q_name;
				x.value = q_value;
				x.coef_type = q_type;
				pthyp->set1.Add (x);
			}
			else if (ced_name == "Second set")
			{
				Hyp_tiLiteral x;
				id_hlp.Format ("%d", l_id);
				x.id = "tiLit" + id_hlp + pthyp->id;
				id_hlp.Format ("%d", c_id);
				x.id = x.id + id_hlp;
				if (neg_lit) neg_lit_smbl = "�"; else neg_lit_smbl = "";
				x.quant = neg_lit_smbl + q_name;
				x.value = q_value;
				x.coef_type = q_type;
				pthyp->set2.Add (x);
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
	try
	{
		buf = Get_DTD ();
	}
	catch (...)
	{
		CLMSock::ReportError (12, LMERR_DTD_ERROR);
		return "";
	}

	//create xml data
	buf = buf + " <active_list> ";
	int i;
    for (i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert ();
	}
	buf += " </active_list>";

	for (i = 0; i < list.GetSize (); i++)
	{
		delete (list.GetAt (i));
	}
	list.RemoveAll ();

	return buf;
}

// --- AP SDCF-hypothese

CString fLMSDCFhyp(void * hSource)
{
	CString buf;
	CString db_name = ((CDatabase *) hSource)->GetDatabaseName ();
	CString id_hlp;
	CString hlp;
	CString q_coef_type;
	
	TCoef_type_Recordset rs_coef_type ((CDatabase *) hSource);
	THyp_SDCF_Meta_Array list;
	Hyp_SDCF_Recordset rs ((CDatabase *) hSource);
	tiDCFrequencyI_Recordset rs_freq ((CDatabase *) hSource);
	tmCategory_Recordset rs_attr ((CDatabase *) hSource);
	TCondition_Recordset rs_cond ((CDatabase *) hSource);
	Hyp_SDCF_Meta * pthyp;

	long h_id;
	long ld_id;

	BOOL result;
	bool exc = false;

	CString neg_lit_smbl;

	CString q_name;
	CString q_value;

	Hyp_tiLiteral lit;

	CString q = "SELECT * \
				 FROM taTask, tdCFLiteralD, tiHypothesisDC, tmMatrix, tmQuantity \
				 WHERE taTask.TaskID=tiHypothesisDC.TaskID \
				   AND taTask.MatrixID=tmMatrix.MatrixID \
				   AND tiHypothesisDC.CFLiteralDID=tdCFLiteralD.CFLiteralDID \
				   AND tdCFLiteralD.QuantityID=tmQuantity.QuantityID";
	//load data from metabase
	try
	{
		result = rs.Open(AFX_DB_USE_DEFAULT_TYPE, q);
	}
	catch (CDBException* e)
	{
		exc = true;
		CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
		e->Delete ();
	}
	if (exc) return "";
	
	if (result)
	{
		//iteration on query results
		while (!rs.IsEOF())
		{
			h_id = rs.m_HypothesisDCID;
			pthyp = new (Hyp_SDCF_Meta);
			id_hlp.Format ("%d", h_id);
			pthyp->id = "hypDC" + id_hlp;
			pthyp->db_name = db_name;
			pthyp->matrix_name = rs.m_Name2;
			pthyp->task_name = rs.m_Name;
			pthyp->quant = rs.m_Name3;
			pthyp->a_id = "attr_" + pthyp->id;
			pthyp->c_id = "cond_" + pthyp->id;
			pthyp->s1_id = "set1_" + pthyp->id;
			pthyp->s2_id = "set2_" + pthyp->id;

			id_hlp.Format ("%d", rs.m_HypothesisDCID);

			CString q_freq = "SELECT * \
							  FROM tiDCFrequencyI \
							  WHERE tiDCFrequencyI.CedentTypeID = 5 \
							    AND tiDCFrequencyI.HypothesisDCID=" + id_hlp +
							" ORDER BY Col";						
			try
			{
				result = rs_freq.Open(AFX_DB_USE_DEFAULT_TYPE, q_freq);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				while (!rs_freq.IsEOF())
				{
					pthyp->frequencies1.Add (rs_freq.m_Frequency);
					rs_freq.MoveNext();
				}
				rs_freq.Close();
			}
			else return "";

			q_freq = "SELECT * \
					  FROM tiDCFrequencyI \
					  WHERE tiDCFrequencyI.CedentTypeID = 6 \
					    AND tiDCFrequencyI.HypothesisDCID=" + id_hlp +
					" ORDER BY Col";						
			try
			{
				result = rs_freq.Open(AFX_DB_USE_DEFAULT_TYPE, q_freq);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				while (!rs_freq.IsEOF())
				{
					pthyp->frequencies2.Add (rs_freq.m_Frequency);
					rs_freq.MoveNext();
				}
				rs_freq.Close();
			}
			else return "";

			id_hlp.Format ("%d", rs.m_QuantityID2);
			CString q_attr = "SELECT * \
							  FROM tmCategory \
							  WHERE tmCategory.QuantityID=" + id_hlp;
			q_attr += " ORDER BY Ord";
			try
			{
				result = rs_attr.Open(AFX_DB_USE_DEFAULT_TYPE, q_attr);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				while (!rs_attr.IsEOF())
				{
					if (rs_attr.m_XCategory) goto next_attr_sdcf;
					hlp = rs_attr.m_Name;
					hlp.Replace ("&", "&amp;");
					hlp.Replace (">", "&gt;");
					hlp.Replace ("<", "&lt;");
					pthyp->attributes.Add (hlp);
next_attr_sdcf:
					rs_attr.MoveNext();
				}
				rs_attr.Close();
			}
			else return "";

			//condition
			id_hlp.Format ("%d", rs.m_HypothesisID);
			CString q_cond = "SELECT * \
							  FROM tiCoefficient, tiLiteralI, tmCategory, tmQuantity \
							  WHERE tiLiteralI.LiteralIID=tiCoefficient.LiteralIID \
							    AND tiLiteralI.CedentTypeID=4 \
								AND tiCoefficient.CategoryID=tmCategory.CategoryID \
								AND tmCategory.QuantityID=tmQuantity.QuantityID \
								AND tiLiteralI.HypothesisID=" + id_hlp +
							" ORDER BY tmQuantity.QuantityID, tmCategory.Ord";
			try
			{
				result = rs_cond.Open(AFX_DB_USE_DEFAULT_TYPE, q_cond);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				while (!rs_cond.IsEOF())
				{
					if (rs_cond.m_Negation)
						neg_lit_smbl = "�";
					else
						neg_lit_smbl = "";
					id_hlp.Format ("%d", rs_cond.m_LiteralIID);
					lit.id = "tiCFLit" + id_hlp + pthyp->id;
					hlp = rs_cond.m_Name2;
					hlp.Replace ("&", "&amp;");
					hlp.Replace (">", "&gt;");
					hlp.Replace ("<", "&lt;");
					lit.quant = neg_lit_smbl + hlp;
					hlp = rs_cond.m_Name;
					hlp.Replace ("&", "&amp;");
					hlp.Replace (">", "&gt;");
					hlp.Replace ("<", "&lt;");
					lit.value = hlp;
					ld_id = rs_cond.m_LiteralDID;
					id_hlp.Format ("%d", ld_id);
					//exactly one row expected to return by the following query:
					q_coef_type = "SELECT * \
									 FROM tdLiteralD, tsCoefficientType \
									WHERE LiteralDID=" + id_hlp;
					q_coef_type +=
						" AND tdLiteralD.CoefficientTypeID=tsCoefficientType.CoefficientTypeID";
					try
					{
						result = rs_coef_type.Open(AFX_DB_USE_DEFAULT_TYPE, q_coef_type);
					}
					catch (CDBException* e)
					{
						exc = true;
						CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
						e->Delete ();
					}
					if (exc) return "";
					
					if (result)
					{
						while (!rs_coef_type.IsEOF())
						{
							hlp = rs_coef_type.m_ShortName;
							hlp.Replace ("&", "&amp;");
							hlp.Replace (">", "&gt;");
							hlp.Replace ("<", "&lt;");
							rs_coef_type.MoveNext ();
						}
						rs_coef_type.Close ();
					}
					else return "";
					lit.coef_type = hlp;
					pthyp->condition.Add (lit);
					rs_cond.MoveNext();
				}
				rs_cond.Close();
			}
			else return "";

			//first set
			id_hlp.Format ("%d", rs.m_HypothesisID);
			q_cond = "SELECT * \
					  FROM tiCoefficient, tiLiteralI, tmCategory, tmQuantity \
					  WHERE tiLiteralI.LiteralIID=tiCoefficient.LiteralIID \
					    AND tiLiteralI.CedentTypeID=5 \
						AND tiCoefficient.CategoryID=tmCategory.CategoryID \
						AND tmCategory.QuantityID=tmQuantity.QuantityID \
						AND tiLiteralI.HypothesisID=" + id_hlp +
					" ORDER BY tmQuantity.QuantityID, tmCategory.Ord";
			try
			{
				result = rs_cond.Open(AFX_DB_USE_DEFAULT_TYPE, q_cond);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				while (!rs_cond.IsEOF())
				{
					if (rs_cond.m_Negation)
						neg_lit_smbl = "�";
					else
						neg_lit_smbl = "";
					id_hlp.Format ("%d", rs_cond.m_LiteralIID);
					lit.id = "tiCFLit" + id_hlp + pthyp->id;
					hlp = rs_cond.m_Name2;
					hlp.Replace ("&", "&amp;");
					hlp.Replace (">", "&gt;");
					hlp.Replace ("<", "&lt;");
					lit.quant = neg_lit_smbl + hlp;
					hlp = rs_cond.m_Name;
					hlp.Replace ("&", "&amp;");
					hlp.Replace (">", "&gt;");
					hlp.Replace ("<", "&lt;");
					lit.value = hlp;
					ld_id = rs_cond.m_LiteralDID;
					id_hlp.Format ("%d", ld_id);
					//exactly one row expected to return by the following query:
					q_coef_type = "SELECT * \
									 FROM tdLiteralD, tsCoefficientType \
									WHERE LiteralDID=" + id_hlp;
					q_coef_type +=
						" AND tdLiteralD.CoefficientTypeID=tsCoefficientType.CoefficientTypeID";
					try
					{
						result = rs_coef_type.Open(AFX_DB_USE_DEFAULT_TYPE, q_coef_type);
					}
					catch (CDBException* e)
					{
						exc = true;
						CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
						e->Delete ();
					}
					if (exc) return "";
					
					if (result)
					{
						while (!rs_coef_type.IsEOF())
						{
							hlp = rs_coef_type.m_ShortName;
							hlp.Replace ("&", "&amp;");
							hlp.Replace (">", "&gt;");
							hlp.Replace ("<", "&lt;");
							rs_coef_type.MoveNext ();
						}
						rs_coef_type.Close ();
					}
					else return "";
					lit.coef_type = hlp;
					pthyp->set1.Add (lit);
					rs_cond.MoveNext();
				}
				rs_cond.Close();
			}
			else return "";

			//second set
			id_hlp.Format ("%d", rs.m_HypothesisID);
			q_cond = "SELECT * \
					  FROM tiCoefficient, tiLiteralI, tmCategory, tmQuantity \
					  WHERE tiLiteralI.LiteralIID=tiCoefficient.LiteralIID \
					    AND tiLiteralI.CedentTypeID=6 \
						AND tiCoefficient.CategoryID=tmCategory.CategoryID \
						AND tmCategory.QuantityID=tmQuantity.QuantityID \
						AND tiLiteralI.HypothesisID=" + id_hlp +
					" ORDER BY tmQuantity.QuantityID, tmCategory.Ord";
			try
			{
				result = rs_cond.Open(AFX_DB_USE_DEFAULT_TYPE, q_cond);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				while (!rs_cond.IsEOF())
				{
					if (rs_cond.m_Negation)
						neg_lit_smbl = "�";
					else
						neg_lit_smbl = "";
					id_hlp.Format ("%d", rs_cond.m_LiteralIID);
					lit.id = "tiDCLit" + id_hlp + pthyp->id;
					hlp = rs_cond.m_Name2;
					hlp.Replace ("&", "&amp;");
					hlp.Replace (">", "&gt;");
					hlp.Replace ("<", "&lt;");
					lit.quant = neg_lit_smbl + hlp;
					hlp = rs_cond.m_Name;
					hlp.Replace ("&", "&amp;");
					hlp.Replace (">", "&gt;");
					hlp.Replace ("<", "&lt;");
					lit.value = hlp;
					ld_id = rs_cond.m_LiteralDID;
					id_hlp.Format ("%d", ld_id);
					//exactly one row expected to return by the following query:
					q_coef_type = "SELECT * \
									 FROM tdLiteralD, tsCoefficientType \
									WHERE LiteralDID=" + id_hlp;
					q_coef_type +=
						" AND tdLiteralD.CoefficientTypeID=tsCoefficientType.CoefficientTypeID";
					try
					{
						result = rs_coef_type.Open(AFX_DB_USE_DEFAULT_TYPE, q_coef_type);
					}
					catch (CDBException* e)
					{
						exc = true;
						CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
						e->Delete ();
					}
					if (exc) return "";
					
					if (result)
					{
						while (!rs_coef_type.IsEOF())
						{
							hlp = rs_coef_type.m_ShortName;
							hlp.Replace ("&", "&amp;");
							hlp.Replace (">", "&gt;");
							hlp.Replace ("<", "&lt;");
							rs_coef_type.MoveNext ();
						}
						rs_coef_type.Close ();
					}
					else return "";
					lit.coef_type = hlp;
					pthyp->set2.Add (lit);
					rs_cond.MoveNext();
				}
				rs_cond.Close();
			}
			else return "";

			pthyp->asym1 = "Unknown";
			pthyp->avg_a1 = "Unknown";
			pthyp->avg_g1 = "Unknown";
			pthyp->dor_var1 = pthyp->get_dor_var1 ();
			hlp.Format ("%d", pthyp->get_max1 ());
			pthyp->max1 = hlp;
			
			pthyp->min1 = pthyp->get_min1 ();
			pthyp->nom_var1 = pthyp->get_nom_var1 ();
			pthyp->skew1 = "Unknown";
			pthyp->st_dev1 = "Unknown";
			hlp.Format ("%d", pthyp->get_sum1 ());
			pthyp->sum1 = hlp;
			pthyp->v1 = "Unknown";
			pthyp->var1 = "Unknown";

			pthyp->asym2 = "Unknown";
			pthyp->avg_a2 = "Unknown";
			pthyp->avg_g2 = "Unknown";
			pthyp->dor_var2 = pthyp->get_dor_var2 ();
			hlp.Format ("%d", pthyp->get_max2 ());
			pthyp->max2 = hlp;
			
			pthyp->min2 = pthyp->get_min2 ();
			pthyp->nom_var2 = pthyp->get_nom_var2 ();
			pthyp->skew2 = "Unknown";
			pthyp->st_dev2 = "Unknown";
			hlp.Format ("%d", pthyp->get_sum2 ());
			pthyp->sum2 = hlp;
			pthyp->v2 = "Unknown";
			pthyp->var2 = "Unknown";
			
            pthyp->da_sum = pthyp->get_da_sum ();
            pthyp->da_min = pthyp->get_da_min ();
            pthyp->da_max = pthyp->get_da_max ();
            pthyp->dr_sum = pthyp->get_dr_sum ();;
            pthyp->dr_min = pthyp->get_dr_min ();
            pthyp->dr_max = pthyp->get_dr_max ();

			list.Add (pthyp);
			rs.MoveNext();
		}
		rs.Close();
	}
	else return "";

	//load DTD
	try
	{
		buf = Get_DTD ();
	}
	catch (...)
	{
		CLMSock::ReportError (12, LMERR_DTD_ERROR);
		return "";
	}

	//create xml data
	buf = buf + " <active_list> ";
	int i;
    for (i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert ();
	}
	buf += " </active_list>";

	for (i = 0; i < list.GetSize (); i++)
	{
		list.GetAt (i)->attributes.RemoveAll ();
		list.GetAt (i)->condition.RemoveAll ();
		list.GetAt (i)->frequencies1.RemoveAll ();
		list.GetAt (i)->frequencies2.RemoveAll ();
		list.GetAt (i)->set1.RemoveAll ();
		list.GetAt (i)->set2.RemoveAll ();
		delete (list.GetAt (i));
	}
	list.RemoveAll ();

	return buf;
}

CString fLMKLhyp(void* hSource)
{
	CString buf;
	CString db_name = ((CDatabase *) hSource)->GetDatabaseName ();
	CString id_hlp;
	CString hlp;
	CString q_coef_type;
	
	TCoef_type_Recordset rs_coef_type ((CDatabase *) hSource);

	THyp_KL_Meta_Array list;
	Hyp_KL_Recordset rs ((CDatabase *) hSource);
	tiKLFrequencyI_Recordset rs_freq ((CDatabase *) hSource);
	TKLCategory_Recordset rs_attr ((CDatabase *) hSource);
	TCondition_Recordset rs_cond ((CDatabase *) hSource);
	TKLquant_Recordset rs_quant ((CDatabase *) hSource);
	Hyp_KL_Meta * pthyp;

	long h_id;
	long ld_id;
	long row;

	BOOL result;
	bool exc = false;

	CString neg_lit_smbl;

	CString q_name;
	CString q_value;

	Cint_Array * row_freq_hlp;

	Hyp_tiLiteral lit;

	CString q = "SELECT * \
				 FROM taTask, tiHypothesisKL, tmMatrix \
				 WHERE taTask.TaskID=tiHypothesisKL.TaskID \
				   AND taTask.MatrixID=tmMatrix.MatrixID";
	//load data from metabase
	try
	{
		result = rs.Open(AFX_DB_USE_DEFAULT_TYPE, q);
	}
	catch (CDBException* e)
	{
		exc = true;
		CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
		e->Delete ();
	}
	if (exc) return "";
	
	if (result)
	{
		//iteration on query results
		while (!rs.IsEOF())
		{
			h_id = rs.m_HypothesisKLID;
			pthyp = new (Hyp_KL_Meta);
			id_hlp.Format ("%d", h_id);
			pthyp->id = "hypKL" + id_hlp;
			pthyp->db_name = db_name;
			pthyp->matrix_name = rs.m_Name2;
			pthyp->task_name = rs.m_Name;

			id_hlp.Format ("%d", rs.m_KLLiteralDColID);

			CString q_quant = "SELECT * \
							   FROM tdKLLiteralD, tmQuantity \
							   WHERE tdKLLiteralD.QuantityID=tmQuantity.QuantityID \
							     AND tdKLLiteralD.KLLiteralDID=" + id_hlp;
			//single row returned expected
			try
			{
				result = rs_quant.Open(AFX_DB_USE_DEFAULT_TYPE, q_quant);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				while (!rs_quant.IsEOF())
				{
					pthyp->quant_col = rs_quant.m_Name;
					rs_quant.MoveNext();
				}
				rs_quant.Close();
			}
			else return "";

			id_hlp.Format ("%d", rs.m_KLLiteralDRowID);

			q_quant = "SELECT * \
					   FROM tdKLLiteralD, tmQuantity \
					   WHERE tdKLLiteralD.QuantityID=tmQuantity.QuantityID \
					     AND tdKLLiteralD.KLLiteralDID=" + id_hlp;
			//single row returned expected
			try
			{
				result = rs_quant.Open(AFX_DB_USE_DEFAULT_TYPE, q_quant);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				while (!rs_quant.IsEOF())
				{
					pthyp->quant_row = rs_quant.m_Name;
					rs_quant.MoveNext();
				}
				rs_quant.Close();
			}
			else return "";
			
			pthyp->row_id = "attr_row_" + pthyp->id;
			pthyp->col_id = "attr_col_" + pthyp->id;
			pthyp->c_id = "cond_" + pthyp->id;

			id_hlp.Format ("%d", rs.m_HypothesisKLID);

			CString q_freq = "SELECT * \
							  FROM tiKLFrequencyI \
							  WHERE tiKLFrequencyI.HypothesisKLID=" + id_hlp +
							" ORDER BY Row, Col";			
			try
			{
				result = rs_freq.Open(AFX_DB_USE_DEFAULT_TYPE, q_freq);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				row_freq_hlp = new (Cint_Array);
				row = -1;
				while (!rs_freq.IsEOF())
				{
					if ((row != rs_freq.m_Row) && (row != -1))
					{
						pthyp->table.Add (row_freq_hlp);
						row_freq_hlp = new (Cint_Array);
					}
					row_freq_hlp->Add (rs_freq.m_Frequency);
					row = rs_freq.m_Row;
					rs_freq.MoveNext();
				}
				rs_freq.Close();
				if (row_freq_hlp->GetSize () > 0)
					pthyp->table.Add (row_freq_hlp);
			}
			else return "";

			id_hlp.Format ("%d", rs.m_KLLiteralDColID);

			CString q_attr = "SELECT * \
							  FROM tdKLLiteralD, tmCategory, tmQuantity \
							  WHERE tdKLLiteralD.QuantityID=tmQuantity.QuantityID \
							    AND tmCategory.QuantityID=tmQuantity.QuantityID \
							    AND tdKLLiteralD.KLLiteralDID=" + id_hlp;
			q_attr += " ORDER BY tmCategory.Ord";
			try
			{
				result = rs_attr.Open(AFX_DB_USE_DEFAULT_TYPE, q_attr);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				while (!rs_attr.IsEOF())
				{
					if (rs_attr.m_XCategory) goto next_col_kl;
					hlp = rs_attr.m_Name;
					hlp.Replace ("&", "&amp;");
					hlp.Replace (">", "&gt;");
					hlp.Replace ("<", "&lt;");
					pthyp->column_attributes.Add (hlp);
next_col_kl:
					rs_attr.MoveNext();
				}
				rs_attr.Close();
			}
			else return "";

			id_hlp.Format ("%d", rs.m_KLLiteralDRowID);

			q_attr = "SELECT * \
					  FROM tdKLLiteralD, tmCategory, tmQuantity \
					  WHERE tdKLLiteralD.QuantityID=tmQuantity.QuantityID \
					    AND tmCategory.QuantityID=tmQuantity.QuantityID \
					    AND tdKLLiteralD.KLLiteralDID=" + id_hlp;
			q_attr += " ORDER BY tmCategory.Ord";
			try
			{
				result = rs_attr.Open(AFX_DB_USE_DEFAULT_TYPE, q_attr);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
	
			if (result)
			{
				//iteration on query results
				while (!rs_attr.IsEOF())
				{
					if (rs_attr.m_XCategory) goto next_row_kl;
					hlp = rs_attr.m_Name;
					hlp.Replace ("&", "&amp;");
					hlp.Replace (">", "&gt;");
					hlp.Replace ("<", "&lt;");
					pthyp->row_attributes.Add (hlp);
next_row_kl:
					rs_attr.MoveNext();
				}
				rs_attr.Close();
			}
			else return "";

			id_hlp.Format ("%d", rs.m_HypothesisID);
			CString q_cond = "SELECT * \
							  FROM tiCoefficient, tiLiteralI, tmCategory, tmQuantity \
							  WHERE tiLiteralI.LiteralIID=tiCoefficient.LiteralIID \
								AND tiCoefficient.CategoryID=tmCategory.CategoryID \
								AND tmCategory.QuantityID=tmQuantity.QuantityID \
								AND tiLiteralI.HypothesisID=" + id_hlp +
							" ORDER BY tmQuantity.QuantityID, tmCategory.Ord";
			try
			{
				result = rs_cond.Open(AFX_DB_USE_DEFAULT_TYPE, q_cond);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				while (!rs_cond.IsEOF())
				{
					if (rs_cond.m_Negation)
						neg_lit_smbl = "�";
					else
						neg_lit_smbl = "";
					id_hlp.Format ("%d", rs_cond.m_LiteralIID);
					lit.id = "tiKLLit" + id_hlp + pthyp->id;
					hlp = rs_cond.m_Name2;
					hlp.Replace ("&", "&amp;");
					hlp.Replace (">", "&gt;");
					hlp.Replace ("<", "&lt;");
					lit.quant = neg_lit_smbl + hlp;
					hlp = rs_cond.m_Name;
					hlp.Replace ("&", "&amp;");
					hlp.Replace (">", "&gt;");
					hlp.Replace ("<", "&lt;");
					lit.value = hlp;
					ld_id = rs_cond.m_LiteralDID;
					id_hlp.Format ("%d", ld_id);
					//exactly one row expected to return by the following query:
					q_coef_type = "SELECT * \
									 FROM tdLiteralD, tsCoefficientType \
									WHERE LiteralDID=" + id_hlp;
					q_coef_type +=
						" AND tdLiteralD.CoefficientTypeID=tsCoefficientType.CoefficientTypeID";
					try
					{
						result = rs_coef_type.Open(AFX_DB_USE_DEFAULT_TYPE, q_coef_type);
					}
					catch (CDBException* e)
					{
						exc = true;
						CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
						e->Delete ();
					}
					if (exc) return "";
					
					if (result)
					{
						while (!rs_coef_type.IsEOF())
						{
							hlp = rs_coef_type.m_ShortName;
							hlp.Replace ("&", "&amp;");
							hlp.Replace (">", "&gt;");
							hlp.Replace ("<", "&lt;");
							rs_coef_type.MoveNext ();
						}
						rs_coef_type.Close ();
					}
					else return "";
					lit.coef_type = hlp;
					pthyp->condition.Add (lit);
					rs_cond.MoveNext();
				}
				rs_cond.Close();
			}
			else return "";

			hlp.Format ("%d", pthyp->get_sum ());
			pthyp->sum = hlp;
            pthyp->min = pthyp->get_min ();
			hlp.Format ("%d", pthyp->get_max ());
            pthyp->max = hlp;
            pthyp->chi_sq = pthyp->get_chi_sq ();
            pthyp->fnc_s = pthyp->get_fnc_s ();
            pthyp->fnc_r = pthyp->get_fnc_r ();
            pthyp->mi = pthyp->get_mi ();
			if (pthyp->mi == "Unknown")
			{
				pthyp->h_c = "Unknown";
				pthyp->h_r = "Unknown";
				pthyp->h_c_r = "Unknown";

			}
			else
			{
				pthyp->h_c = (LPCTSTR) (_bstr_t) pthyp->get_h_c ();
				pthyp->h_r = (LPCTSTR) (_bstr_t) pthyp->get_h_r ();
				pthyp->h_c_r = (LPCTSTR) (_bstr_t) pthyp->get_h_c_r ();
			}
            pthyp->aic = pthyp->get_aic ();
            pthyp->kend = pthyp->get_kend (); 

			list.Add (pthyp);
			rs.MoveNext();
		}
		rs.Close();
	}
	else return "";

	//creation of xml string
	
  
	//load DTD
	try
	{
		buf = Get_DTD ();
	}
	catch (...)
	{
		CLMSock::ReportError (12, LMERR_DTD_ERROR);
		return "";
	}

	//create xml data
	buf = buf + " <active_list> ";
	int i;
    for (i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert ();
	}
	buf += " </active_list>";

	for (i = 0; i < list.GetSize (); i++)
	{
		list.GetAt (i)->row_attributes.RemoveAll ();
		list.GetAt (i)->column_attributes.RemoveAll ();
		list.GetAt (i)->condition.RemoveAll ();
		for (int j = 0; j < list.GetAt (i)->table.GetSize (); j++)
		{
			for (int k = 0; list.GetAt (i)->table.GetAt (j)->GetSize (); k++)
			{
				list.GetAt (i)->table.GetAt (j)->RemoveAll ();
			}
			delete (list.GetAt (i)->table.GetAt (j));
		}
		list.GetAt (i)->table.RemoveAll ();
		delete (list.GetAt (i));
	}
	list.RemoveAll ();

	return buf;
}

CString fLMSDKLhyp(void* hSource)
{
	CString buf;
	CString db_name = ((CDatabase *) hSource)->GetDatabaseName ();
	CString id_hlp;
	CString hlp;
	CString q_coef_type;
	
	TCoef_type_Recordset rs_coef_type ((CDatabase *) hSource);
	THyp_SDKL_Meta_Array list;
	Hyp_SDKL_Recordset rs ((CDatabase *) hSource);
	tiDKFrequencyI_Recordset rs_freq ((CDatabase *) hSource);
	TKLCategory_Recordset rs_attr ((CDatabase *) hSource);
	TCondition_Recordset rs_cond ((CDatabase *) hSource);
	TKLquant_Recordset rs_quant ((CDatabase *) hSource);
	Hyp_SDKL_Meta * pthyp;

	long h_id;
	long ld_id;
	long row;

	BOOL result;
	bool exc = false;

	CString neg_lit_smbl;

	CString q_name;
	CString q_value;

	Cint_Array * row_freq_hlp;

	Hyp_tiLiteral lit;

	CString q = "SELECT * \
				 FROM taTask, tiHypothesisDK, tmMatrix \
				 WHERE taTask.TaskID=tiHypothesisDK.TaskID \
				   AND taTask.MatrixID=tmMatrix.MatrixID";
	//load data from metabase
	try
	{
		result = rs.Open(AFX_DB_USE_DEFAULT_TYPE, q);
	}
	catch (CDBException* e)
	{
		exc = true;
		CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
		e->Delete ();
	}
	if (exc) return "";
	
	if (result)
	{
		//iteration on query results
		while (!rs.IsEOF())
		{
			h_id = rs.m_HypothesisDKID;
			pthyp = new (Hyp_SDKL_Meta);
			id_hlp.Format ("%d", h_id);
			pthyp->id = "hypSDKL" + id_hlp;
			pthyp->db_name = db_name;
			pthyp->matrix_name = rs.m_Name2;
			pthyp->task_name = rs.m_Name;

			id_hlp.Format ("%d", rs.m_KLLiteralDColID);

			CString q_quant = "SELECT * \
							   FROM tdKLLiteralD, tmQuantity \
							   WHERE tdKLLiteralD.QuantityID=tmQuantity.QuantityID \
							     AND tdKLLiteralD.KLLiteralDID=" + id_hlp;
			//single row returned expected
			try
			{
				result = rs_quant.Open(AFX_DB_USE_DEFAULT_TYPE, q_quant);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				while (!rs_quant.IsEOF())
				{
					pthyp->quant_col = rs_quant.m_Name;
					rs_quant.MoveNext();
				}
				rs_quant.Close();
			}
			else return "";

			id_hlp.Format ("%d", rs.m_KLLiteralDRowID);

			q_quant = "SELECT * \
					   FROM tdKLLiteralD, tmQuantity \
					   WHERE tdKLLiteralD.QuantityID=tmQuantity.QuantityID \
					     AND tdKLLiteralD.KLLiteralDID=" + id_hlp;
			//single row returned expected
			try
			{
				result = rs_quant.Open(AFX_DB_USE_DEFAULT_TYPE, q_quant);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				while (!rs_quant.IsEOF())
				{
					pthyp->quant_row = rs_quant.m_Name;
					rs_quant.MoveNext();
				}
				rs_quant.Close();
			}
			else return "";
			
			pthyp->row_id = "attr_row_" + pthyp->id;
			pthyp->col_id = "attr_col_" + pthyp->id;
			pthyp->c_id = "cond_" + pthyp->id;
			pthyp->s1_id = "set1_" + pthyp->id;
			pthyp->s2_id = "set2_" + pthyp->id;

			id_hlp.Format ("%d", rs.m_HypothesisDKID);
			//first set frequencies
			CString q_freq = "SELECT * \
							  FROM tiDKFrequencyI \
							  WHERE HypothesisDKID=" + id_hlp +
							 "  AND CedentTypeID=5 \
							  ORDER BY Row, Col";			
			try
			{
				result = rs_freq.Open(AFX_DB_USE_DEFAULT_TYPE, q_freq);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				row_freq_hlp = new (Cint_Array);
				row = -1;
				while (!rs_freq.IsEOF())
				{
					if ((row != rs_freq.m_Row) && (row != -1))
					{
						pthyp->table1.Add (row_freq_hlp);
						row_freq_hlp = new (Cint_Array);
					}
					row_freq_hlp->Add (rs_freq.m_Frequency);
					row = rs_freq.m_Row;
					rs_freq.MoveNext();
				}
				rs_freq.Close();
				if (row_freq_hlp->GetSize () > 0)
					pthyp->table1.Add (row_freq_hlp);
			}
			else return "";

			//second set frequencies
			q_freq = "SELECT * \
					  FROM tiDKFrequencyI \
					  WHERE HypothesisDKID=" + id_hlp +
					 "  AND CedentTypeID=6 \
					  ORDER BY Row, Col";			
			try
			{
				result = rs_freq.Open(AFX_DB_USE_DEFAULT_TYPE, q_freq);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				row_freq_hlp = new (Cint_Array);
				row = -1;
				while (!rs_freq.IsEOF())
				{
					if ((row != rs_freq.m_Row) && (row != -1))
					{
						pthyp->table2.Add (row_freq_hlp);
						row_freq_hlp = new (Cint_Array);
					}
					row_freq_hlp->Add (rs_freq.m_Frequency);
					row = rs_freq.m_Row;
					rs_freq.MoveNext();
				}
				rs_freq.Close();
				if (row_freq_hlp->GetSize () > 0)
					pthyp->table2.Add (row_freq_hlp);
			}
			else return "";

			id_hlp.Format ("%d", rs.m_KLLiteralDColID);

			CString q_attr = "SELECT * \
							  FROM tdKLLiteralD, tmCategory, tmQuantity \
							  WHERE tdKLLiteralD.QuantityID=tmQuantity.QuantityID \
							    AND tmCategory.QuantityID=tmQuantity.QuantityID \
							    AND tdKLLiteralD.KLLiteralDID=" + id_hlp;
			q_attr += " ORDER BY tmCategory.Ord";
			try
			{
				result = rs_attr.Open(AFX_DB_USE_DEFAULT_TYPE, q_attr);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				while (!rs_attr.IsEOF())
				{
					if (rs_attr.m_XCategory) goto next_col_sdkl;
					hlp = rs_attr.m_Name;
					hlp.Replace ("&", "&amp;");
					hlp.Replace (">", "&gt;");
					hlp.Replace ("<", "&lt;");
					pthyp->column_attributes.Add (hlp);
next_col_sdkl:
					rs_attr.MoveNext();
				}
				rs_attr.Close();
			}
			else return "";

			id_hlp.Format ("%d", rs.m_KLLiteralDRowID);

			q_attr = "SELECT * \
					  FROM tdKLLiteralD, tmCategory, tmQuantity \
					  WHERE tdKLLiteralD.QuantityID=tmQuantity.QuantityID \
					    AND tmCategory.QuantityID=tmQuantity.QuantityID \
					    AND tdKLLiteralD.KLLiteralDID=" + id_hlp;
			q_attr += " ORDER BY tmCategory.Ord";
			try
			{
				result = rs_attr.Open(AFX_DB_USE_DEFAULT_TYPE, q_attr);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				while (!rs_attr.IsEOF())
				{
					if (rs_attr.m_XCategory) goto next_row_sdkl;
					hlp = rs_attr.m_Name;
					hlp.Replace ("&", "&amp;");
					hlp.Replace (">", "&gt;");
					hlp.Replace ("<", "&lt;");
					pthyp->row_attributes.Add (hlp);
next_row_sdkl:
					rs_attr.MoveNext();
				}
				rs_attr.Close();
			}
			else return "";

			//condition
			id_hlp.Format ("%d", rs.m_HypothesisID);
			CString q_cond = "SELECT * \
							  FROM tiCoefficient, tiLiteralI, tmCategory, tmQuantity \
							  WHERE tiLiteralI.LiteralIID=tiCoefficient.LiteralIID \
							    AND tiLiteralI.CedentTypeID=4 \
								AND tiCoefficient.CategoryID=tmCategory.CategoryID \
								AND tmCategory.QuantityID=tmQuantity.QuantityID \
								AND tiLiteralI.HypothesisID=" + id_hlp +
							" ORDER BY tmQuantity.QuantityID, tmCategory.Ord";
			try
			{
				result = rs_cond.Open(AFX_DB_USE_DEFAULT_TYPE, q_cond);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				while (!rs_cond.IsEOF())
				{
					if (rs_cond.m_Negation)
						neg_lit_smbl = "�";
					else
						neg_lit_smbl = "";
					id_hlp.Format ("%d", rs_cond.m_LiteralIID);
					lit.id = "tiDKLit" + id_hlp + pthyp->id;
					hlp = rs_cond.m_Name2;
					hlp.Replace ("&", "&amp;");
					hlp.Replace (">", "&gt;");
					hlp.Replace ("<", "&lt;");
					lit.quant = neg_lit_smbl + hlp;
					hlp = rs_cond.m_Name;
					hlp.Replace ("&", "&amp;");
					hlp.Replace (">", "&gt;");
					hlp.Replace ("<", "&lt;");
					lit.value = hlp;
					ld_id = rs_cond.m_LiteralDID;
					id_hlp.Format ("%d", ld_id);
					//exactly one row expected to return by the following query:
					q_coef_type = "SELECT * \
									 FROM tdLiteralD, tsCoefficientType \
									WHERE LiteralDID=" + id_hlp;
					q_coef_type +=
						" AND tdLiteralD.CoefficientTypeID=tsCoefficientType.CoefficientTypeID";
					try
					{
						result = rs_coef_type.Open(AFX_DB_USE_DEFAULT_TYPE, q_coef_type);
					}
					catch (CDBException* e)
					{
						exc = true;
						CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
						e->Delete ();
					}
					if (exc) return "";
					
					if (result)
					{
						while (!rs_coef_type.IsEOF())
						{
							hlp = rs_coef_type.m_ShortName;
							hlp.Replace ("&", "&amp;");
							hlp.Replace (">", "&gt;");
							hlp.Replace ("<", "&lt;");
							rs_coef_type.MoveNext ();
						}
						rs_coef_type.Close ();
					}
					else return "";
					lit.coef_type = hlp;
					pthyp->condition.Add (lit);
					rs_cond.MoveNext();
				}
				rs_cond.Close();
			}
			else return "";

			//first set
			id_hlp.Format ("%d", rs.m_HypothesisID);
			q_cond = "SELECT * \
					  FROM tiCoefficient, tiLiteralI, tmCategory, tmQuantity \
					  WHERE tiLiteralI.LiteralIID=tiCoefficient.LiteralIID \
					    AND tiLiteralI.CedentTypeID=5 \
						AND tiCoefficient.CategoryID=tmCategory.CategoryID \
						AND tmCategory.QuantityID=tmQuantity.QuantityID \
						AND tiLiteralI.HypothesisID=" + id_hlp +
					" ORDER BY tmQuantity.QuantityID, tmCategory.Ord";
			try
			{
				result = rs_cond.Open(AFX_DB_USE_DEFAULT_TYPE, q_cond);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				while (!rs_cond.IsEOF())
				{
					if (rs_cond.m_Negation)
						neg_lit_smbl = "�";
					else
						neg_lit_smbl = "";
					id_hlp.Format ("%d", rs_cond.m_LiteralIID);
					lit.id = "tiDKLit" + id_hlp + pthyp->id;
					hlp = rs_cond.m_Name2;
					hlp.Replace ("&", "&amp;");
					hlp.Replace (">", "&gt;");
					hlp.Replace ("<", "&lt;");
					lit.quant = neg_lit_smbl + hlp;
					hlp = rs_cond.m_Name;
					hlp.Replace ("&", "&amp;");
					hlp.Replace (">", "&gt;");
					hlp.Replace ("<", "&lt;");
					lit.value = hlp;
					ld_id = rs_cond.m_LiteralDID;
					id_hlp.Format ("%d", ld_id);
					//exactly one row expected to return by the following query:
					q_coef_type = "SELECT * \
									 FROM tdLiteralD, tsCoefficientType \
									WHERE LiteralDID=" + id_hlp;
					q_coef_type +=
						" AND tdLiteralD.CoefficientTypeID=tsCoefficientType.CoefficientTypeID";
					try
					{
						result = rs_coef_type.Open(AFX_DB_USE_DEFAULT_TYPE, q_coef_type);
					}
					catch (CDBException* e)
					{
						exc = true;
						CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
						e->Delete ();
					}
					if (exc) return "";
					
					if (result)
					{
						while (!rs_coef_type.IsEOF())
						{
							hlp = rs_coef_type.m_ShortName;
							hlp.Replace ("&", "&amp;");
							hlp.Replace (">", "&gt;");
							hlp.Replace ("<", "&lt;");
							rs_coef_type.MoveNext ();
						}
						rs_coef_type.Close ();
					}
					else return "";
					lit.coef_type = hlp;
					pthyp->set1.Add (lit);
					rs_cond.MoveNext();
				}
				rs_cond.Close();
			}
			else return "";

			//second set
			id_hlp.Format ("%d", rs.m_HypothesisID);
			q_cond = "SELECT * \
					  FROM tiCoefficient, tiLiteralI, tmCategory, tmQuantity \
					  WHERE tiLiteralI.LiteralIID=tiCoefficient.LiteralIID \
					    AND tiLiteralI.CedentTypeID=6 \
						AND tiCoefficient.CategoryID=tmCategory.CategoryID \
						AND tmCategory.QuantityID=tmQuantity.QuantityID \
						AND tiLiteralI.HypothesisID=" + id_hlp +
					" ORDER BY tmQuantity.QuantityID, tmCategory.Ord";
			try
			{
				result = rs_cond.Open(AFX_DB_USE_DEFAULT_TYPE, q_cond);
			}
			catch (CDBException* e)
			{
				exc = true;
				CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
				e->Delete ();
			}
			if (exc) return "";
			
			if (result)
			{
				//iteration on query results
				while (!rs_cond.IsEOF())
				{
					if (rs_cond.m_Negation)
						neg_lit_smbl = "�";
					else
						neg_lit_smbl = "";
					id_hlp.Format ("%d", rs_cond.m_LiteralIID);
					lit.id = "tiDKLit" + id_hlp + pthyp->id;
					hlp = rs_cond.m_Name2;
					hlp.Replace ("&", "&amp;");
					hlp.Replace (">", "&gt;");
					hlp.Replace ("<", "&lt;");
					lit.quant = neg_lit_smbl + hlp;
					hlp = rs_cond.m_Name;
					hlp.Replace ("&", "&amp;");
					hlp.Replace (">", "&gt;");
					hlp.Replace ("<", "&lt;");
					lit.value = hlp;
					ld_id = rs_cond.m_LiteralDID;
					id_hlp.Format ("%d", ld_id);
					//exactly one row expected to return by the following query:
					q_coef_type = "SELECT * \
									 FROM tdLiteralD, tsCoefficientType \
									WHERE LiteralDID=" + id_hlp;
					q_coef_type +=
						" AND tdLiteralD.CoefficientTypeID=tsCoefficientType.CoefficientTypeID";
					try
					{
						result = rs_coef_type.Open(AFX_DB_USE_DEFAULT_TYPE, q_coef_type);
					}
					catch (CDBException* e)
					{
						exc = true;
						CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
						e->Delete ();
					}
					if (exc) return "";
					
					if (result)
					{
						while (!rs_coef_type.IsEOF())
						{
							hlp = rs_coef_type.m_ShortName;
							hlp.Replace ("&", "&amp;");
							hlp.Replace (">", "&gt;");
							hlp.Replace ("<", "&lt;");
							rs_coef_type.MoveNext ();
						}
						rs_coef_type.Close ();
					}
					else return "";
					lit.coef_type = hlp;
					pthyp->set2.Add (lit);
					rs_cond.MoveNext();
				}
				rs_cond.Close();
			}
			else return "";

			hlp.Format ("%d", pthyp->get_sum1 ());
			pthyp->sum1 = hlp;
            pthyp->min1 = pthyp->get_min1 ();
			hlp.Format ("%d", pthyp->get_max1 ());
            pthyp->max1 = hlp;
            pthyp->chi_sq1 = pthyp->get_chi_sq1 ();
            pthyp->fnc_s1 = pthyp->get_fnc_s1 ();
            pthyp->fnc_r1 = pthyp->get_fnc_r1 ();
			pthyp->h_c1 = (LPCTSTR) (bstr_t) pthyp->get_h_c1 ();
            pthyp->h_r1 = (LPCTSTR) (bstr_t) pthyp->get_h_r1 ();
            pthyp->h_c_r1 = (LPCTSTR) (bstr_t) pthyp->get_h_c_r1 ();
            pthyp->mi1 = pthyp->get_mi1 ();
            pthyp->aic1 = pthyp->get_aic1 ();
            pthyp->kend1 = pthyp->get_kend1 ();
			
			hlp.Format ("%d", pthyp->get_sum2 ());
			pthyp->sum2 = hlp;
            pthyp->min2 = pthyp->get_min2 ();
			hlp.Format ("%d", pthyp->get_max2 ());
            pthyp->max2 = hlp;
            pthyp->chi_sq2 = pthyp->get_chi_sq2 ();
            pthyp->fnc_s2 = pthyp->get_fnc_s2 ();
            pthyp->fnc_r2 = pthyp->get_fnc_r2 ();
			pthyp->h_c2 = (LPCTSTR) (bstr_t) pthyp->get_h_c2 ();
            pthyp->h_r2 = (LPCTSTR) (bstr_t) pthyp->get_h_r2 ();
            pthyp->h_c_r2 = (LPCTSTR) (bstr_t) pthyp->get_h_c_r2 ();
            pthyp->mi2 = pthyp->get_mi2 ();
            pthyp->aic2 = pthyp->get_aic2 ();
            pthyp->kend2 = pthyp->get_kend2 ();

			pthyp->da_sum = pthyp->get_da_sum ();
            pthyp->da_min = pthyp->get_da_min ();
            pthyp->da_max = pthyp->get_da_max ();
            pthyp->dr_sum = pthyp->get_dr_sum ();
            pthyp->dr_min = pthyp->get_dr_min ();
            pthyp->dr_max = pthyp->get_dr_max ();

			list.Add (pthyp);
			rs.MoveNext();
		}
		rs.Close();
	}
	else return "";

	//creation of xml string
	
  
	//load DTD
	try
	{
		buf = Get_DTD ();
	}
	catch (...)
	{
		CLMSock::ReportError (12, LMERR_DTD_ERROR);
		return "";
	}

	//create xml data
	buf = buf + " <active_list> ";
	int i;
    for (i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert ();
	}
	buf += " </active_list>";

	for (i = 0; i < list.GetSize (); i++)
	{
		list.GetAt (i)->row_attributes.RemoveAll ();
		list.GetAt (i)->column_attributes.RemoveAll ();
		list.GetAt (i)->condition.RemoveAll ();
		list.GetAt (i)->set1.RemoveAll ();
		list.GetAt (i)->set2.RemoveAll ();
		int j;
		for (j = 0; j < list.GetAt (i)->table1.GetSize (); j++)
		{
			for (int k = 0; list.GetAt (i)->table1.GetAt (j)->GetSize (); k++)
			{
				list.GetAt (i)->table1.GetAt (j)->RemoveAll ();
			}
			delete (list.GetAt (i)->table1.GetAt (j));
		}
		for (j = 0; j < list.GetAt (i)->table2.GetSize (); j++)
		{
			for (int k = 0; list.GetAt (i)->table2.GetAt (j)->GetSize (); k++)
			{
				list.GetAt (i)->table2.GetAt (j)->RemoveAll ();
			}
			delete (list.GetAt (i)->table2.GetAt (j));
		}
		list.GetAt (i)->table1.RemoveAll ();
		list.GetAt (i)->table2.RemoveAll ();
		delete (list.GetAt (i));
	}
	list.RemoveAll ();

	return buf;
}

CString fLMdata_matrix (void* hSource)
{
	CString buf = "";
	CString hlp;
	CString db_name = ((CDatabase *) hSource)->GetDatabaseName ();

	long matrix_id = -1;
	long matrix_id_tst = 0;

	BOOL result;
	bool exc = false;

	TData_Matrix_Recordset rs ((CDatabase *) hSource);

	Data_Matrix_Meta * ptatt;
	TData_Matrix_Meta_Array list;

	LPCTSTR q =
		"SELECT * \
		 FROM tmAttribute, tmMatrix, tsValueSubType \
		 WHERE tmAttribute.MatrixID=tmMatrix.MatrixID \
			AND tmAttribute.ValueSubTypeID=tsValueSubType.ValueSubTypeID \
		 ORDER BY tmAttribute.MatrixID";
	try
	{
		result = rs.Open(AFX_DB_USE_DEFAULT_TYPE, q);
	}
	catch (CDBException* e)
	{
		exc = true;
		CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
		e->Delete ();
	}
	if (exc) return "";
	
	if (result)
	{
		//iteration on query results
		while (!rs.IsEOF())
		{
			matrix_id_tst = rs.m_MatrixID;
			if (matrix_id != matrix_id_tst)
			{
				hlp.Format ("%d", matrix_id_tst);
				ptatt = new (Data_Matrix_Meta);
				ptatt->db_name = db_name;
				ptatt->id = "table" + hlp;
				ptatt->matrix_name = rs.m_Name2;
				ptatt->record_count = rs.m_RecordCount;
				ptatt->integer_count = 0;
				ptatt->float_count = 0;
				ptatt->string_count = 0;
				ptatt->boolean_count = 0;
				ptatt->date_count = 0;
				list.Add (ptatt);
			}
			
			if (rs.m_ShortName == "long") ptatt->integer_count++;
			else if (rs.m_ShortName == "float") ptatt->float_count++;
			else if (rs.m_ShortName == "string") ptatt->string_count++;
			else if (rs.m_ShortName == "bool") ptatt->boolean_count++;
			else if (rs.m_ShortName == "date") ptatt->date_count++;

			matrix_id = matrix_id_tst;
			rs.MoveNext();
		}
		rs.Close();
	}
	else return "";

	//creation of xml string
	//load DTD
	try
	{
		buf = Get_DTD ();
	}
	catch (...)
	{
		CLMSock::ReportError (12, LMERR_DTD_ERROR);
		return "";
	}
	//create xml data
	buf = buf + " <active_list> ";
	int i;
    for (i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert ();
	}
	buf += " </active_list>";

	for (i = 0; i < list.GetSize (); i++)
	{
		delete (list.GetAt (i));
	}
	list.RemoveAll ();
	
	return buf;
}

CString fLMcolumn(void* hSource)
{
	CString buf = "";
	CString hlp;
	CString db_name = ((CDatabase *) hSource)->GetDatabaseName ();
	CString qcat;

	long count = 0;
	BOOL result;
	bool exc = false;

	TColumn_Recordset rs ((CDatabase *) hSource);

	Column_Meta * ptatt;
	TColumn_Meta_Array list;

	CString q =
		"SELECT * \
		 FROM tmAttribute, tmMatrix, tsAttributeSubType, tsValueSubType \
		 WHERE tmAttribute.MatrixID=tmMatrix.MatrixID \
			AND tmAttribute.AttributeSubTypeID=tsAttributeSubType.AttributeSubTypeID \
			AND tsAttributeSubType.ShortName=";
	q +=									 "'DB'";
	q += "AND tmAttribute.ValueSubTypeID=tsValueSubType.ValueSubTypeID";
	try
	{
		result = rs.Open(AFX_DB_USE_DEFAULT_TYPE, q);
	}
	catch (CDBException* e)
	{
		exc = true;
		CLMSock::ReportError (11, LMERR_BAD_MDB_VERSION);
		e->Delete ();
	}
	if (exc) return "";
	
	if (result)
	{
		//iteration on query results
		while (!rs.IsEOF())
		{
			ptatt = new (Column_Meta);
			ptatt->column_name = rs.m_Name;
			ptatt->db_name = db_name;
			ptatt->matrix_name = rs.m_Name2;
			hlp.Format ("%d", rs.m_AttributeID);
			ptatt->id = "col" + hlp;
			ptatt->value_type = rs.m_Name4;
			ptatt->primary_key_position.Format("%d", rs.m_PrimaryKeyPosition);
			ptatt->avg = (LPCSTR) (_bstr_t) rs.m_ValueAvg;
			ptatt->min = (LPCSTR) (_bstr_t) rs.m_ValueMin;
			ptatt->max = (LPCSTR) (_bstr_t) rs.m_ValueMax;
			list.Add (ptatt);
			rs.MoveNext();
		}
		rs.Close();
	}
	else return "";

	//creation of xml string
	//load DTD
	try
	{
		buf = Get_DTD ();
	}
	catch (...)
	{
		CLMSock::ReportError (12, LMERR_DTD_ERROR);
		return "";
	}
	//create xml data
	buf = buf + " <active_list> ";
	int i;
    for (i = 0; i < list.GetSize (); i++)
	{
		buf = buf + list.GetAt (i)->xml_convert ();
	}
	buf += " </active_list>";

	for (i = 0; i < list.GetSize (); i++)
	{
		delete (list.GetAt (i));
	}
	list.RemoveAll ();
	
	return buf;
}