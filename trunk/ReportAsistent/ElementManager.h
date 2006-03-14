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






#define ELID_UNKNOWN		0
#define ELID_REPORT			1
#define ELID_CHAPTER		2
#define ELID_PARAGRAPH		3
#define ELID_TEXT			4
#define ELID_INCLUDE		5
//#define ELID_HYP4FT		6  !!! nebude existovat 
							//aktivni prvky se vytvareji dynamicky, jdou doinstalovat

class CElementManager  
{
public:
	typedef int elId;

private:
	static LPCTSTR el_names[];

public:
	BOOL CanAppendChildHere(IXMLDOMElementPtr & child, IXMLDOMElementPtr & parent);
	BOOL IsElementActive(elId elementId);
	IXMLDOMElementPtr CreateEmptyExampleElement(CElementManager::elId id);
	elId ElementIdFromName(LPCTSTR el_name);


	LPCTSTR ElementName(elId elementID);	//vrati jemno elementu s id elementID
	elId IdentifyElement(IXMLDOMElementPtr & element);	//identifikuje element - vrati id
	elId LastElementId();	//vrati posledni id ~ pocet znamych elementu

	CElementManager();
	~CElementManager();

};

#endif // !defined(AFX_ELEMENTMANAGER_H__6942C897_7B81_4C40_AA9D_0877F1FFF55A__INCLUDED_)
