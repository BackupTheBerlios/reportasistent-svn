// ReportAsistent.h : main header file for the REPORTASISTENT application
//

#if !defined(AFX_REPORTASISTENT_H__B8BFBABC_4887_44AF_92CC_FD8D82E85539__INCLUDED_)
#define AFX_REPORTASISTENT_H__B8BFBABC_4887_44AF_92CC_FD8D82E85539__INCLUDED_
#endif

#if _MSC_VER > 1000
#pragma once
#endif 
// _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

//Iva: konstanty
//pocet obrazku pro ikony v TreeCtrl
#if !defined NUM_PICTURES_TREECTRL
#define NUM_PICTURES_TREECTRL 6
#endif

// Delka nazvu prvku v TreeCtrl
#if !defined LENGTH_TREE_ITEM_NAME
#define LENGTH_TREE_ITEM_NAME 40	//dedek: prepsal z 10 na 15, 40
#endif

//IDs from Help file ReportAsistent.hlp
#if !defined IDH_CONTENTS
#define IDH_CONTENTS 77001
#endif



#include "ElementManager.h"
#include "DataSourceManager.h"
#include "WordManager.h"
#include "DirectoriesManager.h"	// Added by ClassView

//honza: sem vkaldejte vsechny globalni managery
//konstruuje se v inti instance a nici v Exit instance
struct CGeneralManager
{
private:

//dedek: sry ale kdyz to vidim..
/*
	enum Languages_enum {cz, en};  // moznosti jazyku
	Languages_enum language;		// nastaveni jazyka
*/
	CString m_strLanguage;

public:

	CDirectoriesManager DirectoriesManager;
	CElementManager ElementManager;
	CDataSourcesManager DataSourcesManager;
	CWordManager WordManager;

	CGeneralManager() : 
		WordManager(DirectoriesManager),  // kody - pridano kvuli nacitani stylu ze souboru
		DataSourcesManager(DirectoriesManager),
		ElementManager(DirectoriesManager),
		m_strLanguage("en")
	{};

	// jazyk
	LPCTSTR getLanguage()  // vrati retezec s identifikatorem jazyka
	{
		return m_strLanguage;
	};

	void setLanguage(LPCTSTR lng)
	{
		if((lng != CString("en")) && (lng != CString("cz"))) return;

		m_strLanguage = lng;
	};
};


/////////////////////////////////////////////////////////////////////////////
// CReportAsistentApp:
// See ReportAsistent.cpp for the implementation of this class
//
class CSkeletonDoc;

class CReportAsistentApp : public CWinApp
{
public:
	int static ReportError(UINT nResourceErrorStringID, ...);
	
	CSkeletonDoc * FirstDocumentInFirstTemplate();
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
	afx_msg void OnMmsources();
	afx_msg void OnFileOptions();
	afx_msg void OnOpenWordEditor();
	afx_msg void OnHlpTopics();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bMarkOrphans;
	BOOL m_bIdInItemName; // 0/1.. whether or not to show id at the Tree item name
	int m_iTreeItemHeight;
	int m_iTreeItemIndent;
	BOOL m_bTreeHasLines;
	BOOL m_bTreeHasButtons;


	BOOL m_bWordPluginMode;
public:
	int m_iTextEditSize;
	int m_iTreeItemNameLength;
public:
	virtual int DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt);
};


