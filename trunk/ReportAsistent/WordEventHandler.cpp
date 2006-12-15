// WordEventHandler.cpp : implementation file
//
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "stdafx.h"
#include "ReportAsistent.h"
#include "WordEventHandler.h"
#include "CSkeletonDoc.h"
#include "APTransform.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWordEventHandler

IMPLEMENT_DYNCREATE(CWordEventHandler, CCmdTarget)

CWordEventHandler::CWordEventHandler()
{
	EnableAutomation();
}

CWordEventHandler::~CWordEventHandler()
{
}


void CWordEventHandler::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CWordEventHandler, CCmdTarget)
	//{{AFX_MSG_MAP(CWordEventHandler)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CWordEventHandler, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CWordEventHandler)
	DISP_FUNCTION(CWordEventHandler, "ActiveElementSelected", onActiveElementSelected, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CWordEventHandler, "SetSources", onSetSources, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CWordEventHandler, "SetOptions", onSetOptions, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CWordEventHandler, "SkeletonEditor", onSkeletonEditor, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CWordEventHandler, "WordQuit", onWordQuit, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CWordEventHandler, "PrepareParentTaskActivation", onPrepareParentTaskActivation, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IWordEventHandler to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

BEGIN_INTERFACE_MAP(CWordEventHandler, CCmdTarget)
	INTERFACE_PART(CWordEventHandler, DIID___LMRA_XML_WordLoader, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWordEventHandler message handlers

void CWordEventHandler::onActiveElementSelected(LPCTSTR strElementName) 
{
	m_strLastElementName = strElementName;

	AfxGetApp()->GetMainWnd()->SendMessage(WM_COMMAND, ID_WORD_EDITOR_EDIT_ACTIVE_ELEMENT);
	((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager.OpenWordEditor();

//	 ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager.OpenWordEditor();
	
/**

  CElementManager & em = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
	CWordManager & wm = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager;

	//load element
	int element_index = em.ElementIdFromName(strElementName);
	MSXML2::IXMLDOMElementPtr active_element = 
		em.CreateEmptyElement(element_index);

	
	//load document
	MSXML2::IXMLDOMDocument2Ptr doc;
	doc.CreateInstance(_T("Msxml2.DOMDocument"));
	em.LoadSkeletonDTD((MSXML2::IXMLDOMDocumentPtr &) doc);
	
	//insert element to chapter and document
	doc->documentElement->
		appendChild(em.CreateEmptyElement(ELID_CHAPTER))->
			appendChild(active_element);


	//configure by dilaog
	if (CSkeletonDoc::EditActiveElement(active_element))
	{
		//transform and generate
		CAElTransform transform(active_element);

		transform.DoAllTransnformations();

#ifdef _DEBUG
		MSXML2::IXMLDOMParseErrorPtr err = doc->validate();

		if (err->errorCode != S_OK)
		{
			AfxMessageBox(err->reason);
			AfxMessageBox(active_element->selectSingleNode("output")->xml);
		}
#endif
	
		wm.GenerateXMLStringToWordEditor(active_element->xml);
	}

	
	
	active_element.Release();
	doc.Release();

	
	
//	((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager.SetWordEditorParentTaskName();

	 ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager.OpenWordEditor();

/****/
}

void CWordEventHandler::onSetOptions() 
{
	 AfxGetApp()->GetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_OPTIONS);

	 ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager.OpenWordEditor();
}

void CWordEventHandler::onSetSources() 
{
	 AfxGetApp()->GetMainWnd()->SendMessage(WM_COMMAND, ID_MMSOURCES);

	 ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager.OpenWordEditor();
}

void CWordEventHandler::onSkeletonEditor() 
{
//	AfxGetApp()->GetMainWnd()->ShowWindow(SW_SHOW);
//	AfxGetApp()->GetMainWnd()->EnableWindow();
	//AfxGetApp()->GetMainWnd()->BringWindowToTop();

	((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager.WordEditShowMainWindow();
}

void CWordEventHandler::onWordQuit() 
{
	((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager.WordEditShowMainWindow();
}


void CWordEventHandler::onPrepareParentTaskActivation() 
{
	((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager.PrepareParentTaskActivation();
}
