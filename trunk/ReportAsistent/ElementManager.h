// ElementManager.h: interface for the CElementManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELEMENTMANAGER_H__6942C897_7B81_4C40_AA9D_0877F1FFF55A__INCLUDED_)
#define AFX_ELEMENTMANAGER_H__6942C897_7B81_4C40_AA9D_0877F1FFF55A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <afxtempl.h>
#include "AElInfo.h"



//honza:
//trida urcena ke sprave vsech moznych typu prvku kostry






#define ELID_UNKNOWN		0
#define ELID_REPORT			1
#define ELID_CHAPTER		2
#define ELID_PARAGRAPH		3
#define ELID_TEXT			4
#define ELID_INCLUDE		5
//#define elId_t_HYP4FT		6  !!! nebude existovat 
							//aktivni prvky se vytvareji dynamicky, jdou doinstalovat

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
	CArray<CAElInfo *,CAElInfo *> active_elements;


public:
	elId_t getFirstActiveElementID();
	elId_t getFirstStaticElementID();
	CString CreateElementCaption(IXMLDOMElementPtr & element);
	BOOL FillImageList(CImageList & img_list);
	BOOL LoadElementIcon(elId_t element_id, CBitmap & icon);
	CAElInfo * getActiveElementInfo(elId_t id);
	BOOL ElementSupportedBySource(elId_t element_id, int source_index);
	BOOL CanAppendChildHere(IXMLDOMElementPtr & child, IXMLDOMElementPtr & parent);
	BOOL isElementActive(elId_t elementId);
	IXMLDOMElementPtr CreateEmptyElement(CElementManager::elId_t id);
	elId_t ElementIdFromName(LPCTSTR el_name);


	LPCTSTR getElementName(elId_t elementID);	//vrati jemno elementu s id elementID
	elId_t IdentifyElement(IXMLDOMElementPtr & element);	//identifikuje element - vrati id
	elId_t getLastElementId();	//vrati posledni id ~ pocet znamych elementu

	CElementManager();
	~CElementManager();

protected:
	void LoadActiveElements(LPCTSTR elements_directory_path);
};

#endif // !defined(AFX_ELEMENTMANAGER_H__6942C897_7B81_4C40_AA9D_0877F1FFF55A__INCLUDED_)
