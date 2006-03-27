// ElementManager.h: interface for the CElementManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELEMENTMANAGER_H__6942C897_7B81_4C40_AA9D_0877F1FFF55A__INCLUDED_)
#define AFX_ELEMENTMANAGER_H__6942C897_7B81_4C40_AA9D_0877F1FFF55A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000





//honza:
//trida urcena ke sprave vsech moznych typu prvku kostry






#define elId_t_UNKNOWN		0
#define elId_t_REPORT			1
#define elId_t_CHAPTER		2
#define elId_t_PARAGRAPH		3
#define elId_t_TEXT			4
#define elId_t_INCLUDE		5
//#define elId_t_HYP4FT		6  !!! nebude existovat 
							//aktivni prvky se vytvareji dynamicky, jdou doinstalovat

class CElementManager  
{
public:
	//elId_t je index typu elementu v poli el-names 
	typedef int elId_t;

private:
	//seznam typu prvku dostupnych v aplikaci :statickych(= v XML stromu jmeno tagu) i aktivnich(= v XML stromu hodnota atributu "type" prislusneho tagu).
	static LPCTSTR el_names[]; 

public:
	BOOL ElementSupportedBySource(elId_t element_id, int source_index);
	BOOL CanAppendChildHere(IXMLDOMElementPtr & child, IXMLDOMElementPtr & parent);
	BOOL IsElementActive(elId_t elementId);
	IXMLDOMElementPtr CreateEmptyElement(CElementManager::elId_t id);
	elId_t ElementIdFromName(LPCTSTR el_name);


	LPCTSTR getElementName(elId_t elementID);	//vrati jemno elementu s id elementID
	elId_t IdentifyElement(IXMLDOMElementPtr & element);	//identifikuje element - vrati id
	elId_t LastElementId();	//vrati posledni id ~ pocet znamych elementu

	CElementManager();
	~CElementManager();

};

#endif // !defined(AFX_ELEMENTMANAGER_H__6942C897_7B81_4C40_AA9D_0877F1FFF55A__INCLUDED_)
