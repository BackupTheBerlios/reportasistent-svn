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
///////////////////////////////////////////////////////////////////////

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
	src_dir_path = dir_path;
	
	//nacteni pElementDefinitionDOM
	pElementDefinitionDOM->load((LPCTSTR) (src_dir_path + "\\element.xml"));
	if (pElementDefinitionDOM->parseError->errorCode  != S_OK) return FALSE;

	
	//nacteni pSimpleFilterDOM
	pSimpleFilterDOM->load((LPCTSTR) (src_dir_path + "\\simple_filter.xsl"));
	if (pSimpleFilterDOM->parseError->errorCode  != S_OK) return FALSE;


	
	//nacti jmeno elementu
	IXMLDOMNodePtr type_attr_node = pElementDefinitionDOM->selectSingleNode("//active_element/@type");
	if (type_attr_node == NULL)
	{
		return FALSE;
	}

	el_name = (LPCTSTR) type_attr_node->text;
	type_attr_node.Release();

	return TRUE;

}

IXMLDOMNodePtr CAElInfo::getSimpleFilterTransformation()
{
	return pSimpleFilterDOM;
}

BOOL CAElInfo::LoadElementIcon(CBitmap &icon)
{
	HBITMAP hb = (HBITMAP) LoadImage(NULL, src_dir_path + "\\icon.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (hb == NULL) return FALSE;

	icon.Attach(hb);
	return TRUE;
}
