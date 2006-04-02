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

}

CAElInfo::~CAElInfo()
{

}

LPCTSTR CAElInfo::getElementName()
{
	return el_name;
}

BOOL CAElInfo::LoadFromDir(LPCTSTR dir_path)
{
	IXMLDOMDocumentPtr dom;
	dom.CreateInstance(_T("Msxml2.DOMDocument"));

	CString path = dir_path;
	path += "\\element.xml";

	dom->load((LPCTSTR) path);
	if (dom == NULL) return FALSE;


	IXMLDOMElementPtr element = dom->selectSingleNode("//active_element");
	if (element == NULL)
	{
		dom.Release();
		return FALSE;
	}

	el_name = (LPCTSTR) (_bstr_t) element->getAttribute("type");

	dom.Release();
	element.Release();


	return TRUE;

}
