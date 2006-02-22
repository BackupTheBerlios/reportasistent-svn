// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
//cau Dedo:)


#if !defined(AFX_STDAFX_H__70C66A6D_B88A_4351_BBF7_2A1BEC77FD0D__INCLUDED_)
#define AFX_STDAFX_H__70C66A6D_B88A_4351_BBF7_2A1BEC77FD0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

//pripsal honza

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxole.h>



//potreba pro WordLoader z VisualBasicu
#import "..\VB-LMRA_WordLoader\LMRA_WordLoader.exe" named_guids
// vlozi namespace LMRA_WordLoader;



//potreba pro MSXML
#import <msxml3.dll>
//vlozi namespace MSXML2;



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__70C66A6D_B88A_4351_BBF7_2A1BEC77FD0D__INCLUDED_)


