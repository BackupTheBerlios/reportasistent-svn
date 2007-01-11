//InterfaceFunctions.cpp
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
#ifndef WINVER
#define WINVER 0x0400
#endif

#include <afx.h>
#include <afxdb.h>
#include <afxdlgs.h>
#include <Shlwapi.h>

#include "SockInterface.h"
#include "InterfaceFunctions.h"
#include "LMPlugin.h"
#include "LMPlErrorMessages.h"



// ---------- performLM 

BOOL performLM(hSource_t hSource, const char* APName, BSTR* Result)
{	
	CString CStrResult; // mezivysledek CString
	pFn_t pFn = LMSock.getFnAddress(APName);	// ukazatel na funkci, ktera vyridi pozadavek
	if (pFn == NULL) // chyba - neexistuje funkce vyrizujici tento AP
		return FALSE;
	CStrResult = pFn(hSource);
	*Result =  CStrResult.AllocSysString();
	return TRUE;
}
// ---------- getAPListLM

BSTR getAPListLM()
{
	CString CStrResult = LMSock.getAPList();
	BSTR Result = CStrResult.AllocSysString();
	return Result;
}






// finds the ODBC driver for Microsoft Access
/**
 * Finds the ODBC driver for MS Access.
 *
 * @param ret MS Access driver.
 * @return TRUE, if successful, otherwise it returns FALSE.
 */
BOOL FindAccesDriver(CString & ret)
{
	SQLRETURN r;
	ret.Empty();

	SQLHANDLE h;
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, & h))
	{
		h = SQL_NULL_HANDLE;
		return FALSE;
	}
	else
	{
		SQLSetEnvAttr(h, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, NULL);
	}

	SQLCHAR		desc[1000];
	SQLCHAR		attr[1000];
	SQLSMALLINT desc_len = sizeof desc;
	SQLSMALLINT attr_len = sizeof attr;

	r = SQLDrivers(h, SQL_FETCH_FIRST, desc, sizeof desc, & desc_len, attr, sizeof attr, & attr_len);

	while ((r != SQL_NO_DATA) && (r != SQL_ERROR) && (r != SQL_INVALID_HANDLE))
	{
		if (0 == strcmp((LPCTSTR) attr, "Microsoft Access Driver (*.mdb)"))
		{
			ret = attr;
			SQLFreeHandle(SQL_HANDLE_ENV, h);
			return TRUE;
		}

		r = SQLDataSources(h, SQL_FETCH_NEXT, desc, sizeof desc, & desc_len, attr, sizeof attr, & attr_len);
	}

	
	SQLFreeHandle(SQL_HANDLE_ENV, h);
	return FALSE;
}




///// funkce rozhrani pro praci se zdroji

// ---------- fNewSourceLM

hSource_t fNewSourceLM(PersistID_t * pPerzistID)
{
	 * pPerzistID = NULL;

	CDatabase * db;

//  Kody - misto "source" budeme radeji hledat Microsoft Access driver

	CString d;

	if (! FindAccesDriver(d))
	{
		CLMSock::ReportError(1, LMERR_ACCESSDRV_NFOUND);

		// kody - it depend, if we allow to choose the different driver. This is implemented later.
		// if yes, it is necessary to delete the return statement
		return NULL;
	}

	//dedek: necessary to store the actual directory
	char buf[1001];
	GetCurrentDirectory(1000, buf);

#ifdef _DEBUG

		// store the list of the ODBC drivers and sources to the file "drivers.txt"
	CString drv_enum;
	CString src_enum;
//	SQL.EnumODBCDataSources(drv_enum);
//	SQL.EnumODBCDrivers(src_enum);
	CFile f;
	f.Open((LPCTSTR) "drivers.txt", CFile::modeCreate | CFile::modeWrite);
	f.Write(drv_enum, drv_enum.GetLength());
	f.Write(src_enum, src_enum.GetLength());
	f.Close();
	// -----------
#endif

	// choose the file with the metabase in OpenFileDialog
	CString filter = "LISp-Miner metabase (*.mdb)|*.mdb|All Files (*.*)|*.*||";
	CFileDialog FD(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter);
	if(FD.DoModal() != IDOK)
	{
		//dedek
		SetCurrentDirectory(buf);

		return NULL;
	}

	CString new_pid = FD.GetPathName();
	CString conn_str;

	conn_str = "ODBC;DRIVER=";
	conn_str += d;
	conn_str += ";DBQ=";
	conn_str += new_pid; //path to the file
	conn_str += ";";

	db = new CDatabase();
	BOOL DBOpened = TRUE;
	try
	{
		if (!db->Open(NULL, FALSE, TRUE, conn_str, TRUE))
		{
			//dedek
			SetCurrentDirectory(buf);
		
			delete db;
			return NULL;
		}
	}
	catch(CDBException * e)
	{
		DBOpened = FALSE;
		e->Delete();
	}

	if(!DBOpened) // tries to open DB without specifying of DRIVER in connection string
	{
		conn_str = "ODBC;DBQ=";
		conn_str += new_pid; //path to file with metabase
		conn_str += ";";
		try
		{
			if (!db->Open(NULL, FALSE, TRUE, conn_str, TRUE))
			{
				SetCurrentDirectory(buf);
				delete db;
				return NULL;
			}
		}
		catch(CDBException * ex)
		{
			CLMSock::ReportError(2, LMERR_CANNOT_CREATE_SOURCE, new_pid, ex->m_strError);
			ex->Delete();
			SetCurrentDirectory(buf);
			delete db;
			return NULL;
		}
		
	}
	
	//dedek
	SetCurrentDirectory(buf);

	* pPerzistID = new_pid.AllocSysString();
	return db;
}


// ---------- fOpenSourceLM

hSource_t fOpenSourceLM(PersistID_t PerzistID)
{
	CString d;
	if (! FindAccesDriver(d))
	{
		
		CLMSock::ReportError(1, LMERR_ACCESSDRV_NFOUND);

		// kody - it depend, if we allow to choose the different driver. This is implemented later.
		// if yes, it is necessary to delete the return statement
		return NULL;
	}

	CString file_path = PerzistID;

	if (PathIsRelative(file_path))
	{
		TCHAR module_path[MAX_PATH];
		GetModuleFileName(NULL, module_path, MAX_PATH);
		PathFindFileName(module_path)[-1] = 0;
		PathFindFileName(module_path)[0] = 0;
		file_path = module_path;
		file_path += PerzistID;		
	}


	CString conn_str;
	conn_str = "ODBC;DRIVER=";
	conn_str += d;
	conn_str += ";DBQ=";
	conn_str += file_path; //path to the file
	conn_str += ";";

	CDatabase * db;
	
	db = new CDatabase();
	BOOL DBOpened = TRUE;
	try
	{
		if (!db->Open(NULL, FALSE, TRUE, conn_str, TRUE))
		{
			delete db;
			return NULL;
		}
	}
	catch(CDBException * e)
	{
		DBOpened = FALSE;
		e->Delete();
	}

	if(!DBOpened) // tries to open DB without specifying of DRIVER in connection string
	{
		conn_str = "ODBC;DBQ=";
		conn_str += file_path; //path to file with metabase
		conn_str += ";";
		try
		{
			if (!db->Open(NULL, FALSE, TRUE, conn_str, TRUE))
			{
				delete db;
				return NULL;
			}
		}
		catch(CDBException * ex)
		{
			CLMSock::ReportError(3, LMERR_CANNOT_OPEN_SOURCE, file_path, ex->m_strError);
			ex->Delete();
			delete db;
			return NULL;
		}
		
	}
	
	return db;
}


// ---------- fCloseSourceLM

BOOL fCloseSourceLM(hSource_t hSource)
{
	if (hSource == NULL) return FALSE;
	
	CDatabase * db = (CDatabase *) hSource;

	db->Close();

	delete db;

	return TRUE;
};

