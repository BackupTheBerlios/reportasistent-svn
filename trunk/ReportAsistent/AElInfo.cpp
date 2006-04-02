// AElInfo.cpp: implementation of the CAElInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReportAsistent.h"
#include "AElInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAElInfo::CAElInfo()
{
	pSimpleFilterDOM.CreateInstance("Msxml2.DOMDocument");
	pSimpleFilterDOM->async = VARIANT_FALSE;

	pElementDefinitionDOM.CreateInstance("Msxml2.DOMDocument");
	pElementDefinitionDOM->async = VARIANT_FALSE;
}

CAElInfo::~CAElInfo()
{
	pSimpleFilterDOM.Release();
	pElementDefinitionDOM.Release();
}

LPCTSTR CAElInfo::getElementName()
{
	return el_name;
}

BOOL CAElInfo::LoadFromDir(LPCTSTR dir_path)
{
	CString path = dir_path;
	
	//nacteni pElementDefinitionDOM
	pElementDefinitionDOM->load((LPCTSTR) (path + "\\element.xml"));
	if (pElementDefinitionDOM == NULL) return FALSE;

	
	//nacteni pSimpleFilterDOM
	pSimpleFilterDOM->load((LPCTSTR) (path + "\\simple_filter.xsl"));
	if (pSimpleFilterDOM == NULL) return FALSE;


	
	
/**/
	IXMLDOMElementPtr element = pElementDefinitionDOM->selectSingleNode("//active_element");
	if (element == NULL)
	{
		return FALSE;
	}

	el_name = (LPCTSTR) (_bstr_t) element->getAttribute("type");
	element.Release();
/**/
//zdratka za predchozi:
//	el_name = (LPCTSTR) (pElementDefinitionDOM->selectSingleNode("//active_element/@type")->text);
//	nefunguje nevim proc :(



	return TRUE;

}

IXMLDOMNode * CAElInfo::getSimpleFilterTransformation()
{
	return pSimpleFilterDOM;
}
