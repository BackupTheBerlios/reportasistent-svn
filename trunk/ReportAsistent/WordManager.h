// WordManager.h: interface for the CWordManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORDMANAGER_H__2A5B5F90_FAA9_46F2_BC25_BE144CE6ADF6__INCLUDED_)
#define AFX_WORDMANAGER_H__2A5B5F90_FAA9_46F2_BC25_BE144CE6ADF6__INCLUDED_

#include <vector>
#include <algorithm>

#include "WordEventHandler.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CStringTable
{
public:
	int FindStringNoCase(LPCTSTR str);
	int FindString(LPCTSTR str);
	int virtual getCount() = NULL;
	LPCTSTR virtual getItem(int index) = NULL;
};

class CStringTableImpl : public CStringTable
{
private:
//	CArray<CString *, CString *> data;	// tabulka zdroju
	std::vector <CString *> data;

public:
	void Add(LPCTSTR s);
	void Clear();

	int virtual getCount();
	LPCTSTR virtual getItem(int index);

	~CStringTableImpl();
private:
/*
	bool static CStringTableImpl::str_sort_desc(CString * s1,  CString * s2);
	bool static CStringTableImpl::str_sort_asc(CString * s1,  CString * s2);

	bool static CStringTableImpl::num_sort_desc(CString * s1,  CString * s2);
	bool static CStringTableImpl::num_sort_asc(CString * s1,  CString * s2);
*/
public:
	void Sort(BOOL ascending = TRUE);
	void SortNumeric(BOOL ascending = TRUE);
	// loads items (values) from XML DOM Node - elements with type <item value="(new item)">
	BOOL loadItemsFromXML(MSXML2::IXMLDOMNodeListPtr & pNodeList);
public:
	// returns a xml string with all items : <item value="(item)"/>
	CString getItemsInXML(void);
};

class CStrCompare
{
public:
	bool static str_sort_desc(CString * s1,  CString * s2);
	bool static str_sort_asc(CString * s1,  CString * s2);

	bool static num_sort_desc(CString * s1,  CString * s2);
	bool static num_sort_asc(CString * s1,  CString * s2);
};



class CWordManager  
{
public:
	LPCTSTR getLastElementName();

	void OpenWordEditor();
	void GenerateXMLString(_bstr_t XML_str);
	BOOL InitWordLoader();
	CWordManager(CDirectoriesManager & m);
	virtual ~CWordManager();

	void LoadWordStylesAndTempates(LPCTSTR template_name = NULL);
protected:
	void LoadWordTemplates();
	void LoadParagraphStyles(LPCTSTR template_name);  // kody: kvuli novymu vlaknu a volani ze staticky metody presunuto z protected sem
	void LoadCharacterStyles(LPCTSTR template_name);
	// kody: funkce pro vlakno
	void static CWordManager::LoadWordStylesThreadFunction(LPARAM template_name, LPARAM pWordManager);
	
public:
	void PrepareParentTaskActivation();
	void WordEditShowMainWindow();
	void WordEditHideMainWindow();
	BOOL CWordManager::isWordEditorActive();
	void SetWordEditorParentTaskName();
	void GenerateXMLStringToWordEditor(_bstr_t XML_str);
	CStringTable & getWordTemplates() { return m_WordTemplates; };
	CStringTable & getWordParagraphStyles() { return m_WordParagraphStyles; };
	CStringTable & getWordCharacterStyles() { return m_WordCharacterStyles; };

private:
	WINDOWPLACEMENT m_origWINDOWPLACEMENT;
	static int LoadSafeArrayToStringTable(SAFEARRAY * sarray, CStringTableImpl & st);
	static BOOL CreateVBRAInstance(_LMRA_XML_WordLoaderPtr & refLMRAInterface);
	DWORD m_dwEventHandlerCookie;
	CWordEventHandler * m_pEventHandler;
	_LMRA_XML_WordLoaderPtr m_WordLoader;

	CStringTableImpl m_WordTemplates;
	CStringTableImpl m_WordParagraphStyles;
	CStringTableImpl m_WordCharacterStyles;
protected:
	void FillActiveElements();
	void DisconnectWordEventHandler();
	BOOL InitWordEventHandler();
	//void LoadParagraphStyles(LPCTSTR template_name);   //kody: presunuto do public
	//void LoadCharacterStyles(LPCTSTR template_name);
	BOOL isInit();
public:
	void ActivateWordEditor();
  CString getLastProcessedId(void);
  CString getLastError(void);
  
  // loads lists of Word styles from configuration XML file

private:
	BOOL loadStylesFromXML(LPCTSTR XMLFilePath);
	// saves a list of Word styles to configutation XML file
	BOOL saveStylesToXML(LPCTSTR file_path);
};

#endif // !defined(AFX_WORDMANAGER_H__2A5B5F90_FAA9_46F2_BC25_BE144CE6ADF6__INCLUDED_)
