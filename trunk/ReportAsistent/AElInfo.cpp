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

	pFillElementAttributesDOM.CreateInstance("Msxml2.DOMDocument");
	pFillElementAttributesDOM->async = VARIANT_FALSE;
}

CAElInfo::~CAElInfo()
{
	if (pSimpleFilterDOM != NULL) pSimpleFilterDOM.Release();
	if (pElementDefinitionDOM != NULL) pElementDefinitionDOM.Release();
	if (pFillElementAttributesDOM != NULL) 	pFillElementAttributesDOM.Release();


	for (int a=0; a<getTranformationsCount(); a++)
	{
		m_transformations[a]->doc.Release();
		
		delete m_transformations[a];
	}
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

	
	//nacteni pFillElementAttributesDOM
	pFillElementAttributesDOM->load((LPCTSTR) (src_dir_path + "\\fill_element_attributes.xsl"));
	if (pSimpleFilterDOM->parseError->errorCode  != S_OK) return FALSE;

	
	
	//nacti jmeno elementu
	MSXML2::IXMLDOMNodePtr type_attr_node = pElementDefinitionDOM->selectSingleNode("//active_element/@type");
	if (type_attr_node == NULL)
	{
		return FALSE;
	}

	el_name = (LPCTSTR) type_attr_node->text;
	type_attr_node.Release();

	
	//nacti transformace
	LoadTransformations((CString) dir_path + "\\transformations");

	return TRUE;

}

MSXML2::IXMLDOMNodePtr CAElInfo::getFillElementAttributesTransformation()
{
	return pFillElementAttributesDOM;
}

MSXML2::IXMLDOMNodePtr CAElInfo::getSimpleFilterTransformation()
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

MSXML2::IXMLDOMElementPtr CAElInfo::CreateEmptyElement()
{
	ASSERT(pElementDefinitionDOM != NULL);
	ASSERT(pElementDefinitionDOM->documentElement != NULL);
	
	return pElementDefinitionDOM->documentElement->cloneNode(VARIANT_TRUE);

}



void CAElInfo::LoadTransformations(LPCTSTR dir_path)
{
	CFileFind finder;

	

	BOOL bWorking = finder.FindFile((CString) dir_path + "\\*.*");
	while (bWorking)
	{
		 bWorking = finder.FindNextFile();

		 if (finder.IsDirectory() && (! finder.IsDots()))
		 {
			 s_transformation * tr = new s_transformation;

			 
			 tr->name = finder.GetFileName();
			 
			 tr->doc.CreateInstance(_T("Msxml2.DOMDocument"));
			 tr->doc->async = VARIANT_FALSE;
			 tr->doc->load((LPCTSTR) (finder.GetFilePath() + "\\transform.xsl"));

			 long options_error = S_OK;
			 CFileFind options_find;
			 if ((options_find.FindFile(finder.GetFilePath() + "\\options.xml")) &&
					options_find.FindNextFile())
			 {
				 tr->options.CreateInstance(_T("Msxml2.DOMDocument"));
				 tr->options->async = VARIANT_FALSE;
				 tr->options->load((LPCTSTR) (finder.GetFilePath() + "\\options.xml"));
				 options_error = tr->options->parseError->errorCode;
			 }
			 options_find.Close();
			 
			 if ((tr->doc->parseError->errorCode == S_OK) && (options_error == S_OK))
			 {
				 m_transformations.Add(tr);
			 }
			 else
			 {
				 //poslat error maessage ????????????
				 /*
				 if (tr->doc->parseError->errorCode != S_OK)
				 {
					 AfxMessageBox(tr->doc->parseError->reason);
				 }
				 */
				 if (options_error != S_OK)
				 {
					 AfxMessageBox(tr->options->parseError->reason);
				 }


				 delete tr;
			 }
				 	
		 }
	}

	finder.Close();
}

int CAElInfo::getTranformationsCount()
{
	return m_transformations.GetSize();
}

CString CAElInfo::getTranformationName(int tr_index)
{
	ASSERT(tr_index >= 0);
	ASSERT(tr_index < getTranformationsCount());

	return m_transformations[tr_index]->name;
}


MSXML2::IXMLDOMNodePtr CAElInfo::getTranformationNode(int tr_index)
{
	ASSERT(tr_index >= 0);
	ASSERT(tr_index < getTranformationsCount());

	return m_transformations[tr_index]->doc;
}

int CAElInfo::FindTransformationByName(LPCTSTR tr_name)
{
	for (int a = 0; a < getTranformationsCount(); a++)
	{
		if (getTranformationName(a) == tr_name) return a;
	}

	return -1;
}
