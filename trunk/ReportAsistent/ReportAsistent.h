// ReportAsistent.h : main header file for the REPORTASISTENT application
//

#if !defined(AFX_REPORTASISTENT_H__B8BFBABC_4887_44AF_92CC_FD8D82E85539__INCLUDED_)
#define AFX_REPORTASISTENT_H__B8BFBABC_4887_44AF_92CC_FD8D82E85539__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

//Iva: konstanty
//pocet obrazku pro ikony v TreeCtrl
#if !defined NUM_PICTURES_TREECTRL
#define NUM_PICTURES_TREECTRL 6
#endif

// Delka nazvu prvku typu text v TreeCtrl
#if !defined LENGTH_TREE_ITEM_NAME
#define LENGTH_TREE_ITEM_NAME 10
#endif



#include "ElementManager.h"

//honza: sem vkaldejte vsechny globalni managery
//konstruuje se v inti instance a nici v Exit instance
struct CGeneralManager
{
public:
	CElementManager ElementManager;

};


/////////////////////////////////////////////////////////////////////////////
// CReportAsistentApp:
// See ReportAsistent.cpp for the implementation of this class
//

class CReportAsistentApp : public CWinApp
{
public:
	CGeneralManager * m_pGeneralManager;
	CReportAsistentApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportAsistentApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CReportAsistentApp)
	afx_msg void OnAppAbout();
	afx_msg void OnMMNewText();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTASISTENT_H__B8BFBABC_4887_44AF_92CC_FD8D82E85539__INCLUDED_)
