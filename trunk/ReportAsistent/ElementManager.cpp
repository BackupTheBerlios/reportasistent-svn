// ElementManager.cpp: implementation of the CElementManager class.
//
//////////////////////////////////////////////////////////////////////
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

LM Report Asistent is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with LM Report Asistent; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
;*/
#include "stdafx.h"
#include "ReportAsistent.h"
#include "ElementManager.h"
#include "CSkeletonDoc.h"
#include "APTransform.h"

#pragma warning( disable : 4786 )


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
	IDB_INCLUDEICO, //az bude ikona pro include tak dat sem                   
	IDB_ATTRLINKICO, //az bude ikona pro atr_link tak dat sem                   
	IDB_ATTRLINKTABLEICO //az bude ikona pro atr_link_table tak dat sem                   
};

LPCTSTR CElementManager::static_elements_names[] = 
{
	"unknown", //v menu->pridej novy prvek: NENI
	"report", //v menu->pridej novy prvek: NENI
	//STATICKE
	"text",
	"paragraph",
	"chapter", 
	"include",
	"attr_link",
	"attr_link_table"
};

LPCTSTR CElementManager::static_elements_long_names[] = 
{
	"unknown", //v menu->pridej novy prvek: NENI
	"Report", //v menu->pridej novy prvek: NENI
	//STATICKE
	"Text",
	"Paragraph",
	"Chapter", 
	"Include",
	"Attribute Link",
	"Attribute Link Table"
};
CElementManager::elId_t CElementManager::FirstStaticElementID = 2;

CElementManager::elId_t CElementManager::FirstActiveElementID = 5;

#define LENGTH(array) (sizeof(array) / sizeof(* array))

CElementManager::elId_t CElementManager::getLastElementId()
{
//	int pom = active_elements.GetUpperBound();
	return LENGTH(static_elements_names) + active_elements.GetUpperBound();
}


LPCTSTR CElementManager::getElementName(elId_t elementID)
{
	if (elementID > getLastElementId()) elementID = ELID_UNKNOWN;

	if (! isElementActive(elementID)) return static_elements_names[elementID];

	return getActiveElementInfo(elementID)->getElementName();
}

// kody
LPCTSTR CElementManager::getElementLabel(elId_t elementID)
{
	if (elementID > getLastElementId()) elementID = ELID_UNKNOWN;
	if (elementID < getFirstStaticElementID()) elementID = ELID_UNKNOWN;

	if (! isElementActive(elementID)) return static_elements_long_names[elementID];

	return getActiveElementInfo(elementID)->getElementLabel();
}


CElementManager::elId_t CElementManager::IdentifyElement(MSXML2::IXMLDOMElementPtr & element)
{
	if (element == NULL) 
		return ELID_UNKNOWN;

	CString baseName = (BSTR) element->baseName;

	//zkusime porovnat parametr type se jmeny aktivnich prvku
	if (baseName == "active_element")
	{
		CString type_name = (BSTR) (_bstr_t) element->getAttribute("type");

		for (int a=0; a <= getLastElementId(); a++)
		{
			if (! isElementActive(a)) continue;

			if (type_name == getElementName(a)) return a;
		}

		return ELID_UNKNOWN;
	}

	//zkusime porovnat jmeno tagu se jmeny statickych prvku
	for (int a=0; a <= getLastElementId(); a++)
	{
		if (isElementActive(a)) continue;
		
		if (baseName == getElementName(a)) return a;
	}
	
	return ELID_UNKNOWN;
}


void CElementManager::Init(CDirectoriesManager & m)
{
	LoadActiveElements(m.getElementsDirectory());
	LoadAttrLinkTableStyles(m.getAttrLinkTableStylesDirectory());
}


CElementManager::CElementManager(CDirectoriesManager & m)
{
//  AfxMessageBox(m.getElementsDirectory());
}

CElementManager::~CElementManager()
{
	int a;
	
	for (a=0; a<active_elements.GetSize(); a++)
	{
		delete active_elements[a];
	}

	for (a=0; a<attr_link_table_doms.GetSize(); a++)
	{
		ASSERT(attr_link_table_doms[a] != NULL);
		
		attr_link_table_doms[a]->Release();
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

MSXML2::IXMLDOMElementPtr CElementManager::CreateEmptyElement(CElementManager::elId_t id)
{
	CSkeletonDoc * doc = ((CReportAsistentApp *) AfxGetApp())->FirstDocumentInFirstTemplate();
	
	MSXML2::IXMLDOMElementPtr ret;

	if (isElementActive(id))
	{
		ret = getActiveElementInfo(id)->CreateEmptyElement();
		//nastav unikatni id parametr
		if (doc != NULL)
			ret->setAttribute("id", (LPCTSTR) doc->CreateNewID(id));

		return ret;

	}
	
	
	
	MSXML2::IXMLDOMDocumentPtr element_example;
	element_example.CreateInstance(_T("Msxml2.DOMDocument"));	
	element_example->async = VARIANT_FALSE; // default - true,

	LoadXMLDOMFromResource(IDR_STATIC_ELEMENTS, element_example);

	CString select = "//";
	select += getElementName(id);
	
	
	ret = element_example->selectSingleNode((LPCTSTR) select);
	if (ret == NULL) 
	{

#ifdef _DEBUG
		AfxMessageBox("Nezdarilo se najit odpovidajici xml prvek v souboru praznych prvku.");
#endif
		element_example.Release();
		return NULL;
	}
	
	
	//nastav unikatni id parametr
	if (doc != NULL)
		ret->setAttribute("id", (LPCTSTR) doc->CreateNewID(id));



	element_example.Release();

	return ret;
}

BOOL CElementManager::isActiveElementOrphan(MSXML2::IXMLDOMElementPtr & element)
{	
	ASSERT(isElementActive(IdentifyElement(element)));

	CDataSourcesManager & DSM = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DataSourcesManager;
			
	CString sourceID = (LPCTSTR) (_bstr_t) element->getAttribute("source");  // public ID of data source connected with given active element

	// test - data source exists in sources tab and is valid source
	if(!DSM.isSourceValid(DSM.FindSourceByPublicID((public_source_id_t) sourceID)))
	{
		return TRUE;
	}

	return FALSE;	
}

BOOL CElementManager::isElementActive(elId_t elementId)
{
	return (elementId >= getFirstActiveElementID()) && (elementId <= getLastElementId());
}


//rozhodne, jestli element child muze byt pridan pod element parent
BOOL CElementManager::CanInsertChildHere(MSXML2::IXMLDOMElementPtr &child, MSXML2::IXMLDOMElementPtr &parent)
{
	MSXML2::IXMLDOMNodePtr new_child_appended;
	
	MSXML2::IXMLDOMParseErrorPtr err;
	
	//zkusi ho pridat a kdyz to projde tak ho zase vynda :-)
	try
	{
		new_child_appended = parent->appendChild(child);
		MSXML2::IXMLDOMDocument2 * doc2 = NULL; 
		parent->ownerDocument.QueryInterface(__uuidof(MSXML2::IXMLDOMDocument2), &doc2);

		err = doc2->validate();
		
		doc2->Release();

	}
	catch (_com_error e)
	{
		//AfxMessageBox(child->xml);
#ifdef _DEBUG
		AfxMessageBox(e.ErrorMessage());
#endif
		return FALSE;
	}

	parent->removeChild(new_child_appended);

	
	/*****    //honza: ladici klidne zakomentujete
	int a = err->errorCode;
	if (a != S_OK) AfxMessageBox(err->reason);
	/*****/

	return 	err->errorCode == S_OK;	
}


//varti TRUE pokud zdroj podporuje tento typ aktivniho prvku
BOOL CElementManager::isElementSupportedBySource(elId_t element_id, int source_index)
{
	CDataSourcesManager & m = ((CReportAsistentApp *) AfxGetApp())->m_pGeneralManager->DataSourcesManager;

	//zdroje podporuji jen aktivni prvky
	if (! isElementActive(element_id)) return FALSE;

	if (! m.isSourceValid(source_index)) return FALSE;

	return m.isElementSupportedByPlugin(m.getSourcePluginIndex(source_index), getElementName(element_id));
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

		 if (finder.IsDirectory() && (! finder.IsDots()) && (! finder.IsHidden()))
		 {
			 CAElInfo * element_info = new CAElInfo();

//			 AfxMessageBox(finder.GetFilePath());
       
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

	// kody - setrideni pole "active_elements" podle labelu akt. prvku
	sortActiveElementsByLabel();
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

	//static elements:
	if (! isElementActive(element_id))
	{
		icon.LoadBitmap(static_elements_bitmap_id[element_id]);
		return TRUE;
	}
	//active elements:
	int Res = getActiveElementInfo(element_id)->LoadElementIcon(icon);
		//if active element doesn't have icon, it gets icon of "unknown" element
	if (0==Res) icon.LoadBitmap(static_elements_bitmap_id[ELID_UNKNOWN]);
	return TRUE;
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

CString CElementManager::CreateElementCaption(MSXML2::IXMLDOMElementPtr &pElement)
{
	ASSERT(pElement != NULL);

	CReportAsistentApp * App = ((CReportAsistentApp *) AfxGetApp());


	elId_t element_id = IdentifyElement(pElement);
	_bstr_t bsValue;
	_bstr_t bsId;
	_bstr_t bsAttr;
	_bstr_t bsTarget;
	CString sRet;
	CString sText;

//	AfxMessageBox(pElement->xml);
//	AfxMessageBox(getElementName(element_id));


	if (element_id != ELID_UNKNOWN)
		bsId = pElement->selectSingleNode("@id")->text;
	
	switch (element_id)
	{

	case  ELID_UNKNOWN:
		return "Unknown element";
		break;
	
	case  ELID_REPORT:
	case  ELID_CHAPTER:		
		bsValue = pElement->selectSingleNode("@title")->text;
		if (bsValue.length() == 0) 
		{
			sRet.Format("No name");
			break;
		}
		if ((bsValue.length()+bsId.length()+2) <=App->m_iTreeItemNameLength) 					 
		{
			sRet.Format("%s",(LPCTSTR) bsValue);
			break;
		}
		else
		{
			sRet.Format("%.*s...",App->m_iTreeItemNameLength -3, (LPCTSTR) bsValue);
			break;
		}
		break;

	
	case  ELID_TEXT:
		sText=CSkeletonDoc::HtmlToStr((LPCTSTR) pElement->text);

		if (sText.GetLength() == 0) 
		{
			sRet.Format("Empty");
			break;
		}
		if ((sText.GetLength()+bsId.length()+2) <= App->m_iTreeItemNameLength) 					 
		{
			sRet.Format("%s",sText);
			break;
		}
		else
		{
			CString Pom = sText;
			Pom = Pom.Right((App->m_iTreeItemNameLength-5)/2);
			sRet.Format("%.*s ... %.*s",(App->m_iTreeItemNameLength-5)/2, (LPCTSTR)sText,(App->m_iTreeItemNameLength-5)/2, (LPCTSTR) Pom);
			break;
		}
		break;
	case  ELID_ATTR_LINK:
			bsAttr = pElement->selectSingleNode("@attr_name")->text;
			bsTarget = pElement->selectSingleNode("@target")->text;
			
			if ((bsAttr.length() == 0) || (bsTarget.length() == 0)) 
			{
				sRet.Format("Empty");
				break;
			}
			else //Iva: length is probably reasonable, so check of length is missing
			{
				sRet.Format("%s of %s", (LPCTSTR) bsAttr, (LPCTSTR) bsTarget);			 
				break;
			}
			break;

	case  ELID_PARAGRAPH:
	case  ELID_ATTR_LINK_TABLE:
		//Id is restricted, thus length is not checked.
		return(LPCTSTR) bsId;
		break;

	case  ELID_INCLUDE:
		bsValue = pElement->selectSingleNode("@file")->text;
		if (bsValue.length() == 0) 
		{
			sRet.Format("No file");
			break;
		}
		else
		{
			sRet.Format("%s",(LPCTSTR) bsValue);
			break;
		}
		break;

	default:
		if (isElementActive(element_id))
		{
			//Id is restricted, thus length is not checked.
			return(LPCTSTR) bsId;
		}
		else
		{
			return (LPCTSTR) pElement->baseName;
		}
		break;
	}
	CString sRet2;
	if 	(((CReportAsistentApp *)AfxGetApp())->m_bIdInItemName)
	{
		sRet2.Format("%s: %s",(LPCTSTR)bsId, sRet); 
		sRet=sRet2;
	}

	return sRet;
	
	//dedek: sem by se program nemel dostat
	ASSERT(FALSE);
	return "";
}

BOOL CElementManager::CanInsertBefore(MSXML2::IXMLDOMElementPtr &pToInsert, MSXML2::IXMLDOMElementPtr &pTarget)
{
	MSXML2::IXMLDOMNodePtr pInserted;
	MSXML2::IXMLDOMElementPtr pParent=pTarget->GetparentNode();
	MSXML2::IXMLDOMParseErrorPtr err;


	//zkusi ho pridat a kdyz to projde tak ho zase vynda :-)
	try
	{
		pInserted = pParent->insertBefore(pToInsert,(MSXML2::IXMLDOMElement*)pTarget);
		MSXML2::IXMLDOMDocument2 * doc2 = NULL; 
		pParent->ownerDocument.QueryInterface(__uuidof(MSXML2::IXMLDOMDocument2), &doc2);

		err = doc2->validate();
		
		doc2->Release();

	}
	catch (_com_error e)
	{
#ifdef _DEBUG
		AfxMessageBox(e.ErrorMessage());
#endif
		return FALSE;
	}


	pParent->removeChild(pInserted);

	
	/*****    //honza: ladici klidne zakomentujete
	int a = err->errorCode;
	if (a != S_OK)
	{
		AfxMessageBox(err->reason);
		CString s;
		s.Format("%d", err->filepos);
		AfxMessageBox(s);
		
	}
	/*****/

	return 	err->errorCode == S_OK;	
}

void CElementManager::LoadAttrLinkTableStyles(LPCTSTR directory_path)
{
	CFileFind finder;

	CString path = directory_path;

	path += "\\*.xsl";

	BOOL bWorking = finder.FindFile(path);
	while (bWorking)
	{
		 bWorking = finder.FindNextFile();

		 if (! finder.IsDots())
		 {
			 MSXML2::IXMLDOMDocumentPtr style_dom;
			 style_dom.CreateInstance("Msxml2.DOMDocument");
			 style_dom->async = VARIANT_FALSE;

			 style_dom->load((LPCTSTR) finder.GetFilePath());

			 if (style_dom->parseError->errorCode == S_OK)
			 {
				 attr_link_table_styles.Add(finder.GetFileTitle());
				 attr_link_table_doms.Add(style_dom.Detach());
			 }
			 else
			 {
				 style_dom.Release();
			 }
		 }
	}

	finder.Close();
}

int CElementManager::getAttrLinkTableStylesCount()
{
	return attr_link_table_styles.getCount();
}

LPCTSTR CElementManager::getAttrLinkTableStyleName(int index)
{
	ASSERT(index >= 0);
	ASSERT(index < getAttrLinkTableStylesCount());

	return attr_link_table_styles.getItem(index);
}

MSXML2::IXMLDOMDocument * CElementManager::getAttrLinkTableStyleDom(int index)
{
	ASSERT(index >= 0);
	ASSERT(index < getAttrLinkTableStylesCount());
	ASSERT(index < attr_link_table_doms.GetSize());

	return attr_link_table_doms.GetAt(index);
}

MSXML2::IXMLDOMDocument * CElementManager::getAttrLinkTableStyleDomByName(LPCTSTR style_name)
{
	int style_index = attr_link_table_styles.FindString(style_name);
	if (style_index != -1)
	{
		return getAttrLinkTableStyleDom(style_index);
	}

	return NULL;
}

void CElementManager::TransformActiveElement(MSXML2::IXMLDOMElementPtr & element)
{

	CAElTransform tr(element);
	tr.DoAllTransnformations();
}


void CElementManager::TransformAttrLinkTable(MSXML2::IXMLDOMElementPtr &element)
{
	MSXML2::IXMLDOMDocumentPtr transformed_table = TransformAttrLinkTableNoReplaceSource(element);

	if (transformed_table == NULL) return;
	
	//jak s lementy co nemaji rodice - budou takove?
	ASSERT(element->parentNode != NULL);
	
	element->parentNode->replaceChild(transformed_table->documentElement, element);
	
	transformed_table.Release();
}


void CElementManager::TransformAttrLink(MSXML2::IXMLDOMElementPtr &element)
{

	MSXML2::IXMLDOMElementPtr txt_elem = CreateEmptyElement(ELID_TEXT);
	
	//nastav style
	_variant_t vt_style = element->getAttribute("style");
	if (vt_style.vt != VT_NULL)
	{
		MSXML2::IXMLDOMAttributePtr style_attr = element->ownerDocument->createAttribute("style");
		style_attr->text = (_bstr_t) vt_style;
		txt_elem->setAttributeNode(style_attr);
		style_attr.Release();
	}

	
	//ziskej hodnotu attribut
	CString query;
	query.Format("id(\"%s\")/attributes/element_attributes/attribute[@name = \"%s\"]/@value",
		(LPCTSTR) (_bstr_t) element->getAttribute("target"),
		(LPCTSTR) (_bstr_t) element->getAttribute("attr_name"));


	MSXML2::IXMLDOMNodePtr value_node = element->ownerDocument->selectSingleNode((LPCTSTR) query);

	if (value_node != NULL)
	{
		txt_elem->text = value_node->text;
		value_node.Release();
		element->parentNode->replaceChild(txt_elem, element);
	}
	else
	{
		element->parentNode->removeChild(element);
	}

}

MSXML2::IXMLDOMDocumentPtr CElementManager::TransformAttrLinkTableNoReplaceSource(MSXML2::IXMLDOMElementPtr &element)
{
	CString target_str = (LPCTSTR) (_bstr_t) element->getAttribute("target");
	CString style_str = (LPCTSTR) (_bstr_t) element->getAttribute("style");

	if ((target_str.GetLength() == 0) || (style_str.GetLength() == 0)) return NULL;

	MSXML2::IXMLDOMDocumentPtr transformed_table;
	transformed_table.CreateInstance(_T("Msxml2.DOMDocument"));	
	transformed_table->async = VARIANT_FALSE;
	
	if (getAttrLinkTableStyleDomByName(style_str) != NULL)
	{
		transformed_table->loadXML(
			element->transformNode(getAttrLinkTableStyleDomByName(style_str)));
	}
	else
	{
		transformed_table.Release();
		return NULL;
	}

	return transformed_table;
}

void CElementManager::LoadXMLDOMFromResource(UINT nResourceID, MSXML2::IXMLDOMDocumentPtr &dom)
{
	HRSRC rsc = FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(nResourceID), "XML");
	HGLOBAL hg = LoadResource(AfxGetResourceHandle(), rsc);

	LPTSTR ps = (LPTSTR) LockResource(hg);
	ps[SizeofResource(AfxGetResourceHandle(), rsc)-1] = 0;
	dom->loadXML(ps);
	
	if (dom->parseError->errorCode != S_OK)
	{
		AfxMessageBox((LPCTSTR) LockResource(hg));
	}

}

BOOL CElementManager::ValidateComplexFilter(MSXML2::IXMLDOMDocumentPtr &vo_dom, CString & err_msg)
{
	MSXML2::IXMLDOMDocumentPtr validator;
	validator.CreateInstance(_T("Msxml2.DOMDocument"));
	validator->async = VARIANT_FALSE;

	LoadXMLDOMFromResource(IDR_COMPLEX_FILTER_DTD, validator);

	if (validator->parseError->errorCode != S_OK) return TRUE;

	MSXML2::IXMLDOMNodePtr clone = vo_dom->documentElement->cloneNode(VARIANT_TRUE);

	try
	{
		validator->replaceChild(clone,	validator->documentElement);
	}
	catch (_com_error e)
	{
		err_msg = (LPCTSTR) e.ErrorMessage();
		return FALSE;
	}

	//odstranit values - nikdy nebudou validni
	MSXML2::IXMLDOMNodeListPtr values = validator->selectNodes("/dialog_data/values/value");
	if (values != NULL)
	{
		((MSXML2::IXMLDOMSelectionPtr) values)->removeAll();
	}

	MSXML2::IXMLDOMParseErrorPtr err = 
		((MSXML2::IXMLDOMDocument2Ptr) validator)->validate();

	if (err->errorCode == S_OK)
	{
		err_msg = "";
		return TRUE;
	}


	err_msg = (LPCTSTR) err->reason;
	return FALSE;
}


BOOL CElementManager::ValidateFillElementAttributes(MSXML2::IXMLDOMDocumentPtr &vo_dom, CString & err_msg)
{
	MSXML2::IXMLDOMDocumentPtr attributes_DOM;
	attributes_DOM.CreateInstance(_T("Msxml2.DOMDocument"));
	attributes_DOM->async = VARIANT_FALSE;

	LoadXMLDOMFromResource(IDR_FILL_ELEMENT_ATTRIBUTES_DTD, attributes_DOM);

	if (attributes_DOM->parseError->errorCode != S_OK) return TRUE;

	MSXML2::IXMLDOMNodePtr clone = vo_dom->documentElement->cloneNode(VARIANT_TRUE);

	try
	{
		attributes_DOM->replaceChild(clone,	attributes_DOM->documentElement);
	}
	catch (_com_error e)
	{
		err_msg = (LPCTSTR) e.ErrorMessage();
		return FALSE;
	}

	MSXML2::IXMLDOMParseErrorPtr err = 
		((MSXML2::IXMLDOMDocument2Ptr) attributes_DOM)->validate();

	if (err->errorCode == S_OK)
	{
		err_msg = "";
		return TRUE;
	}


	err_msg = (LPCTSTR) err->reason;
	return FALSE;
}


BOOL CElementManager::ValidateVisualizationOtions(MSXML2::IXMLDOMDocumentPtr &vo_dom, CString & err_msg)
{

	MSXML2::IXMLDOMDocumentPtr validator;
	validator.CreateInstance(_T("Msxml2.DOMDocument"));
	validator->async = VARIANT_FALSE;

	LoadXMLDOMFromResource(IDR_VISUALIZATION_OPTIONS_DTD, validator);

	if (validator->parseError->errorCode != S_OK) return TRUE;


  MSXML2::IXMLDOMNodePtr clone = vo_dom->documentElement->cloneNode(VARIANT_TRUE);

/*
  if (clone != NULL) AfxMessageBox("no problem");
  AfxMessageBox(clone->xml);
  AfxMessageBox(validator->xml);
*/
	try
	{
		validator->replaceChild(clone,	validator->documentElement);
	}
	catch (_com_error e)
	{
		err_msg = (LPCTSTR) e.ErrorMessage();
		validator.Release();

		return FALSE;
	}

	MSXML2::IXMLDOMParseErrorPtr err = 
		((MSXML2::IXMLDOMDocument2Ptr) validator)->validate();

	if (err->errorCode == S_OK)
	{
		err.Release();
		validator.Release();
		err_msg = "";
		return TRUE;
	}


	err_msg = (LPCTSTR) err->reason;
	err.Release();
	validator.Release();

  return FALSE;
}

void CElementManager::ValidateActiveElement(MSXML2::IXMLDOMElementPtr & a_element)
{
	ASSERT (a_element != NULL);

	BOOL ret = FALSE;

	MSXML2::IXMLDOMDocumentPtr DTD_doc;
	DTD_doc.CreateInstance(_T("Msxml2.DOMDocument"));
	DTD_doc->async = VARIANT_FALSE;

	LoadSkeletonDTD(DTD_doc);

	MSXML2::IXMLDOMElementPtr chapter = CreateEmptyElement(ELID_CHAPTER);
	chapter->appendChild(a_element->cloneNode(VARIANT_TRUE));
	DTD_doc->documentElement->appendChild(chapter);


	MSXML2::IXMLDOMDocument2Ptr validator = DTD_doc;
	MSXML2::IXMLDOMParseErrorPtr err = validator->validate();

	DTD_doc.Release();
	chapter.Release();
	validator.Release();

	if (err->errorCode != S_OK) throw err;
}

void CElementManager::LoadSkeletonDTD(MSXML2::IXMLDOMDocumentPtr &dom)
{
	LoadXMLDOMFromResource(IDR_SKELETON_DTD, dom);
}


void CElementManager::sortActiveElementsByLabel()
{
	//CArray<CAElInfo *,CAElInfo *> active_elements;
	int pozice,	min, i;
	int	prvku = active_elements.GetSize();
	CAElInfo *pom;
	if (prvku > 1)
	{
		for(pozice = 0; pozice < prvku-1; pozice++ )
		{
			min= pozice;
			for (i=pozice+1; i<prvku; i++)
			{
				if ((CString) (active_elements[i]->getElementLabel()) < (CString) (active_elements[min]->getElementLabel()))
					min = i;
			}
			if (min != pozice)
			{
				pom = active_elements[pozice];
				active_elements[pozice] = active_elements[min];
				active_elements[min] = pom;
			}
		}
	}
}