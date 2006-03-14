// ElementManager.cpp: implementation of the CElementManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReportAsistent.h"
#include "ElementManager.h"

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
