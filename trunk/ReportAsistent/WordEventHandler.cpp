// WordEventHandler.cpp : implementation file
//

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
	CElementManager & em = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;
	CWordManager & wm = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->WordManager;

	//load element
	int element_index = em.ElementIdFromName(strElementName);
	MSXML2::IXMLDOMElementPtr active_element = 
		em.CreateEmptyElement(element_index);

	
	//load document
	MSXML2::IXMLDOMDocumentPtr doc;
	doc.CreateInstance(_T("Msxml2.DOMDocument"));
	em.LoadSkeletonDTD(doc);
	
	//insert element to chapter and document
	doc->documentElement->
		appendChild(em.CreateEmptyElement(ELID_CHAPTER))->
			appendChild(active_element);


	//configure by dilaog
	CSkeletonDoc::EditActiveElement(active_element);

	//transform and generate
	CAElTransform transform(active_element);
	
	wm.GenerateXMLStringToWordEditor(transform.DoAllTransnformations()->xml);

	
	
	active_element.Release();
	doc.Release();
}
