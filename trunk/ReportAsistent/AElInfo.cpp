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
	HRESULT hr;
	hr = pElementDefinitionDOM.CreateInstance("Msxml2.DOMDocument");

	if (hr != S_OK)
	{
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
//					n = GetLastError(),
			hr,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);
		// Process any inserts in lpMsgBuf.
		// ...
		// Display the string.			
		// CReportAsistentApp::ReportError(IDS_WB_WORD_LOADER_NOT_REGISTRED, (LPCTSTR) lpMsgBuf);
		CReportAsistentApp::ReportError(IDS_FAILED_CREATE_XML_DOM_INSTANCE, (LPCTSTR) lpMsgBuf);

		// Free the buffer.
		LocalFree( lpMsgBuf );		
		ExitProcess(-1);
		return;
	}



	pElementDefinitionDOM->async = VARIANT_FALSE;

	pFillElementAttributesDOM.CreateInstance("Msxml2.DOMDocument");
	pFillElementAttributesDOM->async = VARIANT_FALSE;
}

CAElInfo::~CAElInfo()
{
	if (pComplexFilterDOM != NULL) pComplexFilterDOM.Release();
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

LPCTSTR CAElInfo::getElementLabel()
{
	return el_label;
}

BOOL CAElInfo::LoadFromDir(LPCTSTR dir_path)
{  
	src_dir_path = dir_path;
	
	//nacteni pElementDefinitionDOM
	pElementDefinitionDOM->load((LPCTSTR) (src_dir_path + "\\element.xml"));
	if (pElementDefinitionDOM->parseError->errorCode  != S_OK)
	{
		CReportAsistentApp::ReportError(IDS_AEL_LOAD_FAILED, dir_path, "element.xml",
			(LPCTSTR) pElementDefinitionDOM->parseError->reason);

		return FALSE;
	}

/*	
			 CFileFind options_find;
			 //if file exists options.xml
			 if (options_find.FindFile(finder.GetFilePath() + "\\options.xml"))
			 {
				 tr->options.CreateInstance(_T("Msxml2.DOMDocument"));
				 tr->options->async = VARIANT_FALSE;
				 tr->options->load((LPCTSTR) (finder.GetFilePath() + "\\options.xml"));
				 options_error = tr->options->parseError->errorCode;
			 }
			 options_find.Close();
*/	
	CFileFind exists_file_find;

	//nacteni pSimpleFilterDOM
/*
	if (exists_file_find.FindFile(src_dir_path + "\\simple_filter.xsl"))
	{
		pSimpleFilterDOM.CreateInstance("Msxml2.DOMDocument");
		pSimpleFilterDOM->async = VARIANT_FALSE;

		pSimpleFilterDOM->load((LPCTSTR) (src_dir_path + "\\simple_filter.xsl"));
		if (pSimpleFilterDOM->parseError->errorCode  != S_OK)
		{
			CReportAsistentApp::ReportError(IDS_AEL_LOAD_FAILED, dir_path, "simple_filter.xsl",
				(LPCTSTR) pSimpleFilterDOM->parseError->reason);

			pSimpleFilterDOM.Release();
		}
	}
	exists_file_find.Close();
*/

	//nacteni pComplexFilterDOM
	if (exists_file_find.FindFile(src_dir_path + "\\complex_filter.xsl"))
	{
		pComplexFilterDOM.CreateInstance("Msxml2.DOMDocument");
		pComplexFilterDOM->async = VARIANT_FALSE;

		pComplexFilterDOM->load((LPCTSTR) (src_dir_path + "\\complex_filter.xsl"));
		if (pComplexFilterDOM->parseError->errorCode  != S_OK)
		{

			long code = pComplexFilterDOM->parseError->errorCode;
			CReportAsistentApp::ReportError(IDS_AEL_LOAD_FAILED, dir_path, "complex_filter.xsl",
				(LPCTSTR) pComplexFilterDOM->parseError->reason);

			pComplexFilterDOM.Release();
		}
	}

	if (pComplexFilterDOM == NULL)
	{
		//nepodarilo se nacist zadny filter, prvek pridan do databaze AP
		CReportAsistentApp::ReportError(IDS_AEL_NOFILTER, dir_path);
		return FALSE;
	}

	
	//nacteni pFillElementAttributesDOM
	pFillElementAttributesDOM->load((LPCTSTR) (src_dir_path + "\\fill_element_attributes.xsl"));
	if (pFillElementAttributesDOM->parseError->errorCode  != S_OK)
	{
		CReportAsistentApp::ReportError(IDS_AEL_LOAD_FAILED, dir_path, "fill_element_attributes.xsl",
			(LPCTSTR) pFillElementAttributesDOM->parseError->reason);

		return FALSE;
	}


	
	//nacti jmeno elementu
	MSXML2::IXMLDOMNodePtr type_attr_node = pElementDefinitionDOM->selectSingleNode("//active_element/@type");
	if (type_attr_node == NULL)
	{
		CReportAsistentApp::ReportError(IDS_AEL_LOAD_FAILED, dir_path, "element.xml",
			"Unable to locate attribute \"type\" of \"active_element\" tag.");

		return FALSE;
	}

	el_name = (LPCTSTR) type_attr_node->text;
	type_attr_node.Release();


	// kody: nacti label elementu
	MSXML2::IXMLDOMNodePtr label_attr_node = pElementDefinitionDOM->selectSingleNode("//active_element/@label");
	if (label_attr_node == NULL)
	{
		CReportAsistentApp::ReportError(IDS_AEL_LOAD_FAILED, dir_path, "element.xml",
			"Unable to locate attribute \"label\" of \"active_element\" tag.");

		return FALSE;
	}

	el_label = (LPCTSTR) label_attr_node->text;
	label_attr_node.Release();


  //nacti transformace
	LoadTransformations((CString) dir_path + "\\transformations");

	return TRUE;

}



MSXML2::IXMLDOMNodePtr CAElInfo::getFillElementAttributesTransformation()
{
	// kody: nastaveni jazyka transformace
	setLanguageInTransformation(pFillElementAttributesDOM);
	
	return pFillElementAttributesDOM;
}

MSXML2::IXMLDOMNodePtr CAElInfo::getComplexFilterTransformation()
{
	// kody: nastaveni jazyka transformace
	setLanguageInTransformation(pComplexFilterDOM);

	return pComplexFilterDOM;
}


CString CAElInfo::getElementIconPath()
{
	return src_dir_path + "\\icon.bmp";
}

BOOL CAElInfo::LoadElementIcon(CBitmap &icon)
{
	HBITMAP hb = (HBITMAP) LoadImage(NULL, getElementIconPath(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

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

	CElementManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->ElementManager;


	

	BOOL bWorking = finder.FindFile((CString) dir_path + "\\*.*");
	while (bWorking)
	{
		 bWorking = finder.FindNextFile();

		 if (finder.IsDirectory() && (! finder.IsDots()) && (! finder.IsHidden()))
		 {
			 s_transformation * tr = new s_transformation;

			 
			 tr->name = finder.GetFileName();
			 
			 tr->doc.CreateInstance(_T("Msxml2.DOMDocument"));
			 tr->doc->async = VARIANT_FALSE;
			 tr->doc->load((LPCTSTR) (finder.GetFilePath() + "\\transform.xsl"));


       long options_error = S_OK;
			 CFileFind options_find;
			 //if file exists options.xml
			 if (options_find.FindFile(finder.GetFilePath() + "\\options.xml"))
			 {
				 tr->options.CreateInstance(_T("Msxml2.DOMDocument"));
				 tr->options->async = VARIANT_FALSE;
				 tr->options->load((LPCTSTR) (finder.GetFilePath() + "\\options.xml"));
				 options_error = tr->options->parseError->errorCode;
			 }
			 options_find.Close();
			 
			 
			 
			 if (tr->doc->parseError->errorCode == S_OK)
			 {
				 if (options_error == S_OK)
				 {
					 CString err_msg;
					 if ((tr->options == NULL) || (m.ValidateVisualizationOtions(tr->options, err_msg)))
					 {
						 m_transformations.Add(tr);
					 }
					 else
					 {
						 CReportAsistentApp::ReportError(
							 IDS_AEL_TRANSFORTION_LOAD_FAILED,
							 getElementName(), (LPCTSTR) finder.GetFileTitle(),
							 "options.xml", (LPCTSTR) err_msg);
						 delete tr;
					 }
				 }
				 else
				 {
					 CReportAsistentApp::ReportError(
						 IDS_AEL_TRANSFORTION_LOAD_FAILED,
						 getElementName(), (LPCTSTR) finder.GetFileTitle(),
						 "options.xml", (LPCTSTR) tr->options->parseError->reason);
					 delete tr;
				 }
			 }
			 else
			 {
				 CReportAsistentApp::ReportError(
					 IDS_AEL_TRANSFORTION_LOAD_FAILED,
					 getElementName(), (LPCTSTR) finder.GetFileTitle(),
					 "transform.xsl", (LPCTSTR) tr->doc->parseError->reason);
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

	// kody: nastaveni jazyka transformace
	setLanguageInTransformation(m_transformations[tr_index]->doc->documentElement);	

	return m_transformations[tr_index]->doc->documentElement;
}

MSXML2::IXMLDOMNodePtr CAElInfo::getTranformationOptionsDoc(int tr_index)
{
	ASSERT(tr_index >= 0);
	ASSERT(tr_index < getTranformationsCount());

	return m_transformations[tr_index]->options;
}

int CAElInfo::FindTransformationByName(LPCTSTR tr_name)
{
	for (int a = 0; a < getTranformationsCount(); a++)
	{
		if (getTranformationName(a) == tr_name) return a;
	}

	return -1;
}


// -------------
// kody: nazev xsl:variable v transformaci s nastavenim jazyka ("cz"= cesky, "en"= anglicky)
#define _LANGUAGE_VAR_NAME "lng"


// kody: nastaveni jazyka transformace (hodnoty promenne "lng")
BOOL CAElInfo::setLanguageInTransformation(MSXML2::IXMLDOMNodePtr pTransf)
{
	
	MSXML2::IXMLDOMElementPtr variable_element;  // element s promennou 

	CString variable_qury_str;
	variable_qury_str.Format("/xsl:stylesheet/xsl:variable[@name=\'%s\']", (LPCTSTR) _LANGUAGE_VAR_NAME);
	try
	{
		variable_element = pTransf->selectSingleNode((LPCTSTR) variable_qury_str);

		if (variable_element != NULL)
		{
			variable_element->text = (_bstr_t) ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->getLanguage();
		
			variable_element.Release();
			
		}
		
		return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}

}

// -------------



