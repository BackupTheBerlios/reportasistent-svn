// SQL_Pomocnik.h: interface for the CSQL_Pomocnik class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SQL_POMOCNIK_H__C1AFBF8E_542B_49A4_8CF4_B10EFF6144A6__INCLUDED_)
#define AFX_SQL_POMOCNIK_H__C1AFBF8E_542B_49A4_8CF4_B10EFF6144A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef WINVER
#define WINVER 0x0400
#endif

#define EDIT_NEWLINE "\r\n"


// KODY
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
//#include <afx.h>

// ----

class SQL_Pomocnik
{
protected:
	SQLHANDLE h;

	BOOL handle_ok()
	{
		return h != SQL_NULL_HANDLE;
	}

public:
	
	SQL_Pomocnik()
	{
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, & h))
		{
			h = SQL_NULL_HANDLE;
		}
		else
		{
			SQLSetEnvAttr(h, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, NULL);
		}
	}


	BOOL EnumODBCDrivers(CString & ret)
	{
		SQLRETURN r;
		ret.Empty();

		if (! handle_ok()) return FALSE;
	
		SQLCHAR		desc[1000];
		SQLCHAR		attr[1000];
		SQLSMALLINT desc_len = sizeof desc;
		SQLSMALLINT attr_len = sizeof attr;

		r = SQLDrivers(h, SQL_FETCH_FIRST, desc, sizeof desc, & desc_len, attr, sizeof attr, & attr_len);

//		vhodne pro odchytavani chyb
//		SQLGetDiagRec(SQL_HANDLE_ENV, h, 1, desc, & nerr, attr, sizeof attr, & attr_len);


		while ((r != SQL_NO_DATA) && (r != SQL_ERROR) && (r != SQL_INVALID_HANDLE))
		{

			ret += EDIT_NEWLINE;
			ret += "-------------- dalsi driver -----------" EDIT_NEWLINE;
			ret += (LPCTSTR) desc;
			ret += EDIT_NEWLINE;

			SQLCHAR * pc;
		
			for (pc = attr; (*pc != 0) && (pc - attr <= sizeof attr); pc = (SQLCHAR *) strchr((LPCTSTR) pc, 0)+1)
			{
				ret += (LPCTSTR) pc;
				ret += EDIT_NEWLINE;
			}
		
			r = SQLDrivers(h, SQL_FETCH_NEXT, desc, sizeof desc, & desc_len, attr, sizeof attr, & attr_len);
		}

		
		return TRUE;
	}

	BOOL EnumODBCDataSources(CString & ret, SQLSMALLINT DataSources_enum_type = SQL_FETCH_FIRST /* SQL_FETCH_FIRST_USER, SQL_FETCH_FIRST_SYSTEM */)
	{
		SQLRETURN r;
		ret.Empty();

		if (! handle_ok()) return FALSE;

		SQLCHAR		desc[1000];
		SQLCHAR		attr[1000];
		SQLSMALLINT desc_len = sizeof desc;
		SQLSMALLINT attr_len = sizeof attr;

		r = SQLDataSources(h, DataSources_enum_type, desc, sizeof desc, & desc_len, attr, sizeof attr, & attr_len);

		while ((r != SQL_NO_DATA) && (r != SQL_ERROR) && (r != SQL_INVALID_HANDLE))
		{

			ret += EDIT_NEWLINE;
			ret += "-------------- dalsi datasource -----------" EDIT_NEWLINE;
			ret += (LPCTSTR) desc;
			ret += EDIT_NEWLINE;
			ret += (LPCTSTR) attr;
			ret += EDIT_NEWLINE;
		
			r = SQLDataSources(h, SQL_FETCH_NEXT, desc, sizeof desc, & desc_len, attr, sizeof attr, & attr_len);
		}

		return TRUE;
	}

	BOOL FindAccesDatasource(CString & ret)
	{
		SQLRETURN r;
		ret.Empty();

		if (! handle_ok()) return FALSE;

		SQLCHAR		desc[1000];
		SQLCHAR		attr[1000];
		SQLSMALLINT desc_len = sizeof desc;
		SQLSMALLINT attr_len = sizeof attr;

		r = SQLDataSources(h, SQL_FETCH_FIRST, desc, sizeof desc, & desc_len, attr, sizeof attr, & attr_len);

		while ((r != SQL_NO_DATA) && (r != SQL_ERROR) && (r != SQL_INVALID_HANDLE))
		{
			//ten string "Microsoft Access Driver (*.mdb)" by se mel ulozit jinam (header nebo resources)..
			//mozna pridat konfigurovatelnost
			if (0 == strcmp((LPCTSTR) attr, "Microsoft Access Driver (*.mdb)"))
			{
				ret = desc;
				return TRUE;
			}

			r = SQLDataSources(h, SQL_FETCH_NEXT, desc, sizeof desc, & desc_len, attr, sizeof attr, & attr_len);
		}

		
		return FALSE;
	}

		
	~SQL_Pomocnik()
	{
		if (handle_ok())
			SQLFreeHandle(SQL_HANDLE_ENV, h);
	}

};

#endif // !defined(AFX_SQL_POMOCNIK_H__C1AFBF8E_542B_49A4_8CF4_B10EFF6144A6__INCLUDED_)
