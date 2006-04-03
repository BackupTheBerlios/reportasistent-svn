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

UINT CElementManager::static_elements_bitmap_id[]=
{
	IDB_UNKNOWNICO                 ,
	IDB_REPORTICO                  ,
	IDB_TEXTICO                    ,
	IDB_PARAGRAPHICO               ,
	IDB_CHAPTERICO                 ,
	IDB_UNKNOWNICO //az bude ikona pro include tak dat sem                   
};

LPCTSTR CElementManager::static_elements_names[] = 
{
	"unknown", //v menu->pridej novy prvek: NENI
	"report", //v menu->pridej novy prvek: NENI
	//STATICKE
	"text",
	"paragraph",
	"chapter", 
	//OSTATNI

//	"hyp_4ft"
	"include"
};

CElementManager::elId_t CElementManager::FirstStaticElementID = 2;

CElementManager::elId_t CElementManager::FirstActiveElementID = 5;

#define LENGTH(array) (sizeof(array) / sizeof(* array))

CElementManager::elId_t CElementManager::getLastElementId()
{
	int pom = active_elements.GetUpperBound();
	return LENGTH(static_elements_names) + active_elements.GetUpperBound();
}


LPCTSTR CElementManager::getElementName(elId_t elementID)
{
	if (elementID > getLastElementId()) elementID = ELID_UNKNOWN;

	if (! isElementActive(elementID)) return static_elements_names[elementID];

	return getActiveElementInfo(elementID)->getElementName();
}


CElementManager::elId_t CElementManager::IdentifyElement(IXMLDOMElementPtr & element)
{
	CString baseName = (BSTR) element->baseName;


	//zkusime porovnat jmeno tagu s nami znamymi jmeny
	for (int a=0; a <= getLastElementId(); a++)
	{
		if (baseName == getElementName(a)) return a;
	}
	
	
	//zkusime porovnat parametr type s nami znamymi jmeny
	if (baseName == "active_element")
	{
		CString type_name = (BSTR) (_bstr_t) element->getAttribute("type");

		for (int a=0; a <= getLastElementId(); a++)
		{
			if (type_name == getElementName(a)) return a;
		}
	}

	return ELID_UNKNOWN;
}



CElementManager::CElementManager()
{

	LoadActiveElements("..\\elements");

}

CElementManager::~CElementManager()
{
	for (int a=0; a<active_elements.GetSize(); a++)
	{
		delete active_elements[a];
	}

}

CElementManager::elId_t CElementManager::ElementIdFromName(LPCTSTR el_name)
{
	CString name = el_name;
	
	for (int a=0; a <= getLastElementId(); a++)
	{
		if (name == getElementName(a)) return a;
	}

	return ELID_UNKNOWN;
}

IXMLDOMElementPtr CElementManager::CreateEmptyElement(CElementManager::elId_t id)
{
	CSkeletonDoc * doc = ((CReportAsistentApp *) AfxGetApp())->FirstDocumentInFirstTemplate();

	if (isElementActive(id))
	{
		IXMLDOMElementPtr ret = getActiveElementInfo(id)->CreateEmptyElement();
		//nastav unikatni id parametr
		ret->setAttribute("id", (LPCTSTR) doc->CreateNewID(id));

		return ret;

	}
	
	
	
	IXMLDOMDocumentPtr element_example;
	element_example.CreateInstance(_T("Msxml2.DOMDocument"));	
	element_example->async = VARIANT_FALSE; // default - true,

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	//predelat pres directory manager
	element_example->load((LPCTSTR) _T("../XML/prazdny2.xml"));
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1

	CString select;

/*	if (isElementActive(id))
	{
		//priklad: select = "//active_element[@type = 'hyp_4ft']"
		select = "//active_element[@type = '";
		select += getElementName(id);
		select += "']";
	}
	else */
	{
		//priklad: select = "//text"
		select = "//";
		select += getElementName(id);
	}
	
	
	IXMLDOMElementPtr ret = element_example->selectSingleNode((LPCTSTR) select);
	if (ret == NULL) 
	{
		AfxMessageBox("Nezdarilo se najit odpovidajici xml prvek v souboru praznych prvku.");
		element_example.Release();
		return NULL;
	}
	
	
	//nastav unikatni id parametr
	ret->setAttribute("id", (LPCTSTR) doc->CreateNewID(id));



	element_example.Release();

/*	
	m_skeleton->documentElement->appendChild(element_example->selectSingleNode("//active_element[@type = 'hyp_4ft']"));

	element_example.Release();
*/
	return ret;
}

BOOL CElementManager::isElementActive(elId_t elementId)
{
	return (elementId >= getFirstActiveElementID()) && (elementId <= getLastElementId());
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
	catch (_com_error e)
	{
		AfxMessageBox(child->xml);
		AfxMessageBox(e.Description());
		return FALSE;
	}

	parent->removeChild(new_child_appended);

	
	/*****/    //honza: ladici klidne zakomentujete
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
BOOL CElementManager::ElementSupportedBySource(elId_t element_id, int source_index)
{
	CDataSourcesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DataSourcesManager;

	//zdroje podporuji jen aktivni prvky
	if (! isElementActive(element_id)) return FALSE;

	if (! m.isSourceValid(source_index)) return FALSE;
	
	return TRUE;
}

void CElementManager::LoadActiveElements(LPCTSTR elements_directory_path)
{
	CFileFind finder;

	CString path = elements_directory_path;

	path += "\\*.*";

	BOOL bWorking = finder.FindFile(path);
	while (bWorking)
	{
		 bWorking = finder.FindNextFile();

		 if (finder.IsDirectory() && (! finder.IsDots()))
		 {
			 CAElInfo * element_info = new CAElInfo();

			 if (element_info->LoadFromDir(finder.GetFilePath()))
			 {
				 active_elements.Add(element_info);
			 }
			 else
			 {
				 delete element_info;
			 }
		 }
	}

	finder.Close();
}

CAElInfo * CElementManager::getActiveElementInfo(elId_t id)
{
	if (! isElementActive(id)) return NULL;

	return active_elements[id - getFirstActiveElementID()];

}

CElementManager::elId_t CElementManager::getFirstStaticElementID()
{
	return FirstStaticElementID;
}

CElementManager::elId_t CElementManager::getFirstActiveElementID()
{
	//dedek: predelano takhle je to dobre
	//return FirstActiveElementID;

	return LENGTH(static_elements_names);
}

BOOL CElementManager::LoadElementIcon(elId_t element_id, CBitmap &icon)
{
	ASSERT(element_id >= 0);
	ASSERT(element_id <= getLastElementId());
	
	if (! isElementActive(element_id))
	{
		icon.LoadBitmap(static_elements_bitmap_id[element_id]);
		return TRUE;
	}

	return getActiveElementInfo(element_id)->LoadElementIcon(icon);
}

BOOL CElementManager::FillImageList(CImageList &img_list)
{
	for (int a=0; a<=getLastElementId(); a++)
	{
		CBitmap bmp;
		if (! LoadElementIcon(a, bmp)) return FALSE;
		img_list.Add(& bmp, 0xFFFFFF);
		bmp.DeleteObject();
	}

	return TRUE;

}

CString CElementManager::CreateElementCaption(IXMLDOMElementPtr &pElement)
{
	ASSERT(pElement != NULL);

	elId_t element_id = IdentifyElement(pElement);
	_bstr_t value;
	CString ret;

//	AfxMessageBox(pElement->xml);
//	AfxMessageBox(getElementName(element_id));

	
	switch (element_id)
	{
	
	case  ELID_REPORT:
		value = pElement->selectSingleNode("@title")->text;
		if ((BSTR) value == L"") return getElementName(element_id);
		else
		{
			ret.Format("Report: %.*s...", LENGTH_TREE_ITEM_NAME-3, (LPCTSTR) value);
			return ret;
		}

	case  ELID_CHAPTER:
		value = pElement->selectSingleNode("@title")->text;
		if ((BSTR) value == L"") return "Text - empty";
		else
		{
			ret.Format("%.*s...", LENGTH_TREE_ITEM_NAME-3, (LPCTSTR) value);
			return ret;
		}
	
	
	case  ELID_TEXT:
		if ((BSTR) pElement->text == L"") return "Text - empty";
		else
		{
			ret.Format("%.*s...", LENGTH_TREE_ITEM_NAME-3, (LPCTSTR) pElement->text);			 
			return ret;
		}

	case  ELID_PARAGRAPH:
	case  ELID_INCLUDE:
	case  ELID_UNKNOWN:
	default:
		if (isElementActive(element_id))
		{
//			ret.Format("%s: %s", (LPCTSTR) getElementName(element_id), (LPCTSTR) pElement->selectSingleNode("@id")->text);
			return(LPCTSTR) pElement->selectSingleNode("@id")->text;
		}
		else
		{
			return (LPCTSTR) pElement->baseName;
		}
	}

	
	//dedek: sem by se program nemel dostat
	ASSERT(FALSE);
	return "";
}
