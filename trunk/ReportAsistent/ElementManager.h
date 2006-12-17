// ElementManager.h: interface for the CElementManager class.
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
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA*/
#if !defined(AFX_ELEMENTMANAGER_H__6942C897_7B81_4C40_AA9D_0877F1FFF55A__INCLUDED_)
#define AFX_ELEMENTMANAGER_H__6942C897_7B81_4C40_AA9D_0877F1FFF55A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning( disable : 4786 )

#include <afxtempl.h>
#include "AElInfo.h"
#include "DirectoriesManager.h"
#include "WordManager.h"


//honza:
//trida urcena ke sprave vsech moznych typu prvku kostry






#define ELID_UNKNOWN			0
#define ELID_REPORT				1
#define ELID_TEXT				2
#define ELID_PARAGRAPH			3
#define ELID_CHAPTER			4
#define ELID_INCLUDE			5
#define ELID_ATTR_LINK			6
#define ELID_ATTR_LINK_TABLE	7
#define	MAX_ELEMENT_COUNT		100

/**
 * class CElementManager:
 *
 * @author 
 */
class CElementManager  
{
public:
	//elId_t je index typu elementu v poli el-names 
	typedef int elId_t;

private:
	static elId_t FirstActiveElementID;
	static elId_t FirstStaticElementID;
	//seznam typu prvku dostupnych v aplikaci :statickych(= v XML stromu jmeno tagu) i aktivnich(= v XML stromu hodnota atributu "type" prislusneho tagu).
	static UINT static_elements_bitmap_id[];
	static LPCTSTR static_elements_names[]; 
	static LPCTSTR static_elements_long_names [];
	CArray<CAElInfo *,CAElInfo *> active_elements;

	CStringTableImpl attr_link_table_styles;
	CArray<MSXML2::IXMLDOMDocument *, MSXML2::IXMLDOMDocument *> attr_link_table_doms;


public:
	/**
	 * LoadXMLDOMFromResource:
	 *
	 * @param nResourceID 
	 * @param dom 
	 * @return static void 
	 */
	static void LoadXMLDOMFromResource(UINT nResourceID, MSXML2::IXMLDOMDocumentPtr &dom);
	/**
	 * LoadSkeletonDTD:
	 *
	 * @param dom 
	 * @return static void 
	 */
	static void LoadSkeletonDTD(MSXML2::IXMLDOMDocumentPtr & dom);
	/**
	 * ValidateActiveElement:
	 *
	 * @param a_element 
	 * @return void 
	 */
	void ValidateActiveElement(MSXML2::IXMLDOMElementPtr & a_element);
	/**
	 * ValidateVisualizationOtions:
	 *
	 * @param vo_dom 
	 * @param err_msg 
	 * @return static BOOL 
	 */
	static BOOL ValidateVisualizationOtions(MSXML2::IXMLDOMDocumentPtr &vo_dom, CString & err_msg);
	/**
	 * ValidateFillElementAttributes:
	 *
	 * @param vo_dom 
	 * @param err_msg 
	 * @return static BOOL 
	 */
	static BOOL ValidateFillElementAttributes(MSXML2::IXMLDOMDocumentPtr &vo_dom, CString & err_msg);
	/**
	 * ValidateComplexFilter:
	 *
	 * @param vo_dom 
	 * @param err_msg 
	 * @return static BOOL 
	 */
	static BOOL ValidateComplexFilter(MSXML2::IXMLDOMDocumentPtr &vo_dom, CString & err_msg);



	/**
	 * TransformAttrLinkTableNoReplaceSource:
	 *
	 * @param element 
	 * @return MSXML2::IXMLDOMDocumentPtr 
	 */
	MSXML2::IXMLDOMDocumentPtr TransformAttrLinkTableNoReplaceSource(MSXML2::IXMLDOMElementPtr & element);
	/**
	 * getAttrLinkTableStyleDomByName:
	 *
	 * @param style_name 
	 * @return MSXML2::IXMLDOMDocument* 
	 */
	MSXML2::IXMLDOMDocument * getAttrLinkTableStyleDomByName(LPCTSTR style_name);
	/**
	 * getAttrLinkTableStyleDom:
	 *
	 * @param index 
	 * @return MSXML2::IXMLDOMDocument* 
	 */
	MSXML2::IXMLDOMDocument * getAttrLinkTableStyleDom(int index);
	/**
	 * getAttrLinkTableStyleName:
	 *
	 * @param index 
	 * @return LPCTSTR 
	 */
	LPCTSTR getAttrLinkTableStyleName(int index);
	/**
	 * getAttrLinkTableStylesCount:
	 *
	 * @return int 
	 */
	int getAttrLinkTableStylesCount();
	/**
	 * CanInsertBefore:
	 *
	 * @param pInserted 
	 * @param pTarget 
	 * @return BOOL 
	 */
	BOOL CanInsertBefore(MSXML2::IXMLDOMElementPtr &pInserted, MSXML2::IXMLDOMElementPtr &pTarget);
	/**
	 * getFirstActiveElementID:
	 *
	 * @return elId_t 
	 */
	elId_t getFirstActiveElementID();
	/**
	 * getFirstStaticElementID:
	 *
	 * @return elId_t 
	 */
	elId_t getFirstStaticElementID();
	/**
	 * CreateElementCaption:
	 *
	 * @param element 
	 * @return CString 
	 */
	CString CreateElementCaption(MSXML2::IXMLDOMElementPtr & element);
	/**
	 * FillImageList:
	 *
	 * @param img_list 
	 * @return BOOL 
	 */
	BOOL FillImageList(CImageList & img_list);
	/**
	 * LoadElementIcon:
	 *
	 * @param element_id 
	 * @param icon 
	 * @return BOOL 
	 */
	BOOL LoadElementIcon(elId_t element_id, CBitmap & icon);
	/**
	 * getActiveElementInfo:
	 *
	 * @param id 
	 * @return CAElInfo* 
	 */
	CAElInfo * getActiveElementInfo(elId_t id);
	/**
	 * isElementSupportedBySource:
	 *
	 * @param element_id 
	 * @param source_index 
	 * @return BOOL 
	 */
	BOOL isElementSupportedBySource(elId_t element_id, int source_index);
	/**
	 * CanInsertChildHere:
	 *
	 * @param child 
	 * @param parent 
	 * @return BOOL 
	 */
	BOOL CanInsertChildHere(MSXML2::IXMLDOMElementPtr & child, MSXML2::IXMLDOMElementPtr & parent);
	/**
	 * isActiveElementOrphan:
	 *
	 * @param element 
	 * @return BOOL 
	 */
	BOOL isActiveElementOrphan(MSXML2::IXMLDOMElementPtr & element);
	/**
	 * isElementActive:
	 *
	 * @param elementId 
	 * @return BOOL 
	 */
	BOOL isElementActive(elId_t elementId);
	/**
	 * CreateEmptyElement:
	 *
	 * @param id 
	 * @return MSXML2::IXMLDOMElementPtr 
	 */
	MSXML2::IXMLDOMElementPtr CreateEmptyElement(CElementManager::elId_t id);
	/**
	 * ElementIdFromName:
	 *
	 * @param el_name 
	 * @return elId_t 
	 */
	elId_t ElementIdFromName(LPCTSTR el_name);

	/**
	 * TransformActiveElement:
	 *
	 * @param element 
	 * @return void 
	 */
	void TransformActiveElement(MSXML2::IXMLDOMElementPtr & element);
	/**
	 * TransformAttrLinkTable:
	 *
	 * @param element 
	 * @return void 
	 */
	void TransformAttrLinkTable(MSXML2::IXMLDOMElementPtr & element);
	/**
	 * TransformAttrLink:
	 *
	 * @param element 
	 * @return void 
	 */
	void TransformAttrLink(MSXML2::IXMLDOMElementPtr & element);



	/**
	 * getElementName:
	 *
	 * @param elementID 
	 * @return LPCTSTR 
	 */
	LPCTSTR getElementName(elId_t elementID);	//vrati jemno elementu s id elementID
	/**
	 * getElementLabel:
	 *
	 * @param elementID 
	 * @return LPCTSTR 
	 */
	LPCTSTR getElementLabel(elId_t elementID);	//vrati label elementu s id elementID
	/**
	 * IdentifyElement:
	 *
	 * @param element 
	 * @return elId_t 
	 */
	elId_t IdentifyElement(MSXML2::IXMLDOMElementPtr & element);	//identifikuje element - vrati id
	/**
	 * getLastElementId:
	 *
	 * @return elId_t 
	 */
	elId_t getLastElementId();	//vrati posledni id ~ pocet znamych elementu

	/**
	 * Init:
	 *
	 * @param m 
	 * @return void 
	 */
	void Init(CDirectoriesManager & m);

	/**
	 * CElementManager:
	 *
	 * @param m 
	 * @return  
	 */
	CElementManager(CDirectoriesManager & m);
	/**
	 * ~CElementManager:
	 *
	 * @return  
	 */
	~CElementManager();

protected:
	
	/**
	 * LoadAttrLinkTableStyles:
	 *
	 * @param directory_path 
	 * @return void 
	 */
	void LoadAttrLinkTableStyles(LPCTSTR directory_path);
	/**
	 * LoadActiveElements:
	 *
	 * @param elements_directory_path 
	 * @return void 
	 */
	void LoadActiveElements(LPCTSTR elements_directory_path);
	// kody - setridi pole "active_elements" podle labelu
	/**
	 * sortActiveElementsByLabel:
	 *
	 * @return void 
	 */
	void sortActiveElementsByLabel();
};

#endif // !defined(AFX_ELEMENTMANAGER_H__6942C897_7B81_4C40_AA9D_0877F1FFF55A__INCLUDED_)
