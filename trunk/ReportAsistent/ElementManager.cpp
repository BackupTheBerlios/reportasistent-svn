// ElementManager.cpp: implementation of the CElementManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReportAsistent.h"
#include "ElementManager.h"
#include "CSkeletonDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


LPCTSTR CElementManager::el_names[] = 
{
	"unknown",
	"report",
	"chapter",
	"paragraph",
	"text",
	"include",
	"hyp_4ft"
};

#define LENGTH(array) (sizeof(array) / sizeof(* array))

CElementManager::elId CElementManager::LastElementId()
{
	return LENGTH(el_names) -1;
}


LPCTSTR CElementManager::ElementName(elId elementID)
{
	if (elementID >= LENGTH(el_names)) elementID = ELID_UNKNOWN;

	return el_names[elementID];
}


CElementManager::elId CElementManager::IdentifyElement(IXMLDOMElementPtr & element)
{
	CString baseName = (BSTR) element->baseName;


	//zkusime poravnat jmeno tagu s nami znamymi jmeny
	for (int a=0; a <= LastElementId(); a++)
	{
		if (baseName == ElementName(a)) return a;
	}
	
	
	//zkusime porovnat parametr type s nami znamymi jmeny
	if (baseName == "active_element")
	{
		CString type_name = (BSTR) (_bstr_t) element->getAttribute("type");

		for (int a=0; a <= LastElementId(); a++)
		{
			if (type_name == ElementName(a)) return a;
		}
	}

	return ELID_UNKNOWN;
}



CElementManager::CElementManager()
{

}

CElementManager::~CElementManager()
{

}

CElementManager::elId CElementManager::ElementIdFromName(LPCTSTR el_name)
{
	CString name = el_name;
	
	for (int a=0; a <= LastElementId(); a++)
	{
		if (name == ElementName(a)) return a;
	}

	return ELID_UNKNOWN;
}

IXMLDOMElementPtr CElementManager::CreateEmptyExampleElement(CElementManager::elId id)
{
	IXMLDOMDocumentPtr element_example;
	element_example.CreateInstance(_T("Msxml2.DOMDocument"));	
	element_example->async = VARIANT_FALSE; // default - true,

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	//predelat pres directory manager
	element_example->load((LPCTSTR) _T("../XML/prazdny.xml"));
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1

	CString select;

	if (IsElementActive(id))
	{
		//priklad: select = "//active_element[@type = 'hyp_4ft']"
		select = "//active_element[@type = '";
		select += ElementName(id);
		select += "']";
	}
	else
	{
		//priklad: select = "//text"
		select = "//";
		select += ElementName(id);
	}
	
	
	IXMLDOMElementPtr ret = element_example->selectSingleNode((LPCTSTR) select);
	
	
	
	CSkeletonDoc * doc = ((CReportAsistentApp *) AfxGetApp())->FirstDocumentInFirstTemplate();
	
	
	//nastav unikatni id parametr
	ret->setAttribute("id", (LPCTSTR) doc->m_SkeletonManager.CreateNewID(id));



	element_example.Release();

/*	
	m_skeleton->documentElement->appendChild(element_example->selectSingleNode("//active_element[@type = 'hyp_4ft']"));

	element_example.Release();
*/
	return ret;
}

BOOL CElementManager::IsElementActive(elId elementId)
{
	return elementId > ELID_INCLUDE;
}


//rozhodne, jestli element child muze byt pridan pod element parent
BOOL CElementManager::CanAppendChildHere(IXMLDOMElementPtr &child, IXMLDOMElementPtr &parent)
{
	IXMLDOMNodePtr new_child_appended;
	
	IXMLDOMParseErrorPtr err;
	
	//zkusi ho pridat a kdyz to projde tak ho zase vynda :-)
	try
	{
		new_child_appended = parent->appendChild(child);
		IXMLDOMDocument2 * doc2 = NULL; 
		parent->ownerDocument.QueryInterface(__uuidof(IXMLDOMDocument2), &doc2);

		err = doc2->validate();
		
		doc2->Release();

	}
	catch (...)
	{
		return FALSE;
	}

	parent->removeChild(new_child_appended);

	
	/*****///honza: ladici klidne zakomentujete
	int a = err->errorCode;
	if (a != S_OK) AfxMessageBox(err->reason);
	/*****/

	return 	err->errorCode == S_OK;	
}


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
//honza: velmi pracovni - prijde prepsat podle CDataSourceManageru a plugin manageru
//ma vratit TRUE pokud zdroj podporuje tento typ aktivniho prvku
BOOL CElementManager::ElementSupportedBySource(elId element_id, int source_index)
{
	//zdroje podporuji jen aktivni prvky
	if (! IsElementActive(element_id)) return FALSE;
	
	return TRUE;
}
