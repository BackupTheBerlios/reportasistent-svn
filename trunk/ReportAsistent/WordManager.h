// WordManager.h: interface for the CWordManager class.
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
*/
#if !defined(AFX_WORDMANAGER_H__2A5B5F90_FAA9_46F2_BC25_BE144CE6ADF6__INCLUDED_)
#define AFX_WORDMANAGER_H__2A5B5F90_FAA9_46F2_BC25_BE144CE6ADF6__INCLUDED_

#include <vector>
#include <algorithm>

#include "WordEventHandler.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/**
 * class CStringTable: An interface for CStringTableImpl class. It doesn't make it possible to change attributes of the CStringTableImpl class.
 *
 * @author 
 */
class CStringTable
{
public:
	/**
	 * FindStringNoCase:
	 *
	 * @param str 
	 * @return int 
	 */
	int FindStringNoCase(LPCTSTR str);
	/**
	 * FindString:
	 *
	 * @param str 
	 * @return int 
	 */
	int FindString(LPCTSTR str);
	/**
	 * getCount:
	 *
	 * @return int virtual 
	 */
	int virtual getCount() = NULL;
	/**
	 * getItem:
	 *
	 * @param index 
	 * @return LPCTSTR virtual 
	 */
	LPCTSTR virtual getItem(int index) = NULL;
};

/**
 * class CStringTableImpl: The class for storing strings. It is used for MS Word styles names and in Filter tabs of Active Element dialog.
 *
 * @author 
 */
class CStringTableImpl : public CStringTable
{
private:
//	CArray<CString *, CString *> data;	// tabulka zdroju
	std::vector <CString *> data;

public:
	/**
	 * Add:
	 *
	 * @param s 
	 * @return void 
	 */
	void Add(LPCTSTR s);
	/**
	 * Clear:
	 *
	 * @return void 
	 */
	void Clear();

	/**
	 * getCount:
	 *
	 * @return int virtual 
	 */
	int virtual getCount();
	/**
	 * getItem:
	 *
	 * @param index 
	 * @return LPCTSTR virtual 
	 */
	LPCTSTR virtual getItem(int index);

	~CStringTableImpl();

public:
	/**
	 * Sort:
	 *
	 * @param ascending 
	 * @return void 
	 */
	void Sort(BOOL ascending = TRUE);
	/**
	 * SortNumeric:
	 *
	 * @param ascending 
	 * @return void 
	 */
	void SortNumeric(BOOL ascending = TRUE);
	// loads items (values) from XML DOM Node - elements with type <item value="(new item)">
	/**
	 * loadItemsFromXML:
	 *
	 * @param pNodeList 
	 * @return BOOL 
	 */
	BOOL loadItemsFromXML(MSXML2::IXMLDOMNodeListPtr & pNodeList);
public:
	// returns a xml string with all items : <item value="(item)"/>
	/**
	 * getItemsInXML:
	 *
	 * @param  
	 * @return CString 
	 */
	CString getItemsInXML(void);
};

/**
 * class CStrCompare: This class encapsulates comparing function for sorting.
 *
 * @author 
 */
class CStrCompare
{
public:
	/**
	 * str_sort_desc: Sorting of strings, descending.
	 *
	 * @param s1 
	 * @param s2 
	 * @return bool static 
	 */
	bool static str_sort_desc(CString * s1,  CString * s2);
	/**
	 * str_sort_asc:Sorting of strings, ascending.
	 *
	 * @param s1 
	 * @param s2 
	 * @return bool static 
	 */
	bool static str_sort_asc(CString * s1,  CString * s2);

	/**
	 * num_sort_desc: Sorting of numbers, descending.
	 *
	 * @param s1 
	 * @param s2 
	 * @return bool static 
	 */
	bool static num_sort_desc(CString * s1,  CString * s2);
	/**
	 * num_sort_asc: Sorting of numbers, ascending.
	 *
	 * @param s1 
	 * @param s2 
	 * @return bool static 
	 */
	bool static num_sort_asc(CString * s1,  CString * s2);
};



/**
 * class CWordManager: This class serves to control the WordLoader module of LM-RA, which serves to generate a skeleton to a MS Word document.
 *
 * @author 
 */
class CWordManager  
{
public:
	/**
	 * getLastElementName:
	 *
	 * @return LPCTSTR 
	 */
	LPCTSTR getLastElementName();

	/**
	 * OpenWordEditor:
	 *
	 * @return void 
	 */
	void OpenWordEditor();
	/**
	 * GenerateXMLString:
	 *
	 * @param XML_str 
	 * @return void 
	 */
	void GenerateXMLString(_bstr_t XML_str);
	/**
	 * InitWordLoader:
	 *
	 * @return BOOL 
	 */
	BOOL InitWordLoader();
	/**
	 * CWordManager:
	 *
	 * @param m 
	 * @return  
	 */
	CWordManager(CDirectoriesManager & m);
	virtual ~CWordManager();

	/**
	 * LoadWordStylesAndTempates:
	 *
	 * @param template_name 
	 * @return void 
	 */
	void LoadWordStylesAndTempates(LPCTSTR template_name = NULL);
protected:
	/**
	 * LoadWordTemplates:
	 *
	 * @return void 
	 */
	void LoadWordTemplates();
	/**
	 * LoadWordStyles:
	 *
	 * @param template_name 
	 * @return void 
	 */
	void LoadWordStyles(LPCTSTR template_name);

	// kody: funkce pro vlakno
	/**
	 * LoadWordStylesThreadFunction:
	 *
	 * @param template_name 
	 * @param pWordManager 
	 * @return void static 
	 */
	void static CWordManager::LoadWordStylesThreadFunction(LPARAM template_name, LPARAM pWordManager);
	
public:
	/**
	 * PrepareParentTaskActivation:
	 *
	 * @return void 
	 */
	void PrepareParentTaskActivation();
	/**
	 * WordEditShowMainWindow:
	 *
	 * @return void 
	 */
	void WordEditShowMainWindow();
	/**
	 * WordEditHideMainWindow:
	 *
	 * @return void 
	 */
	void WordEditHideMainWindow();
	/**
	 * isWordEditorActive:
	 *
	 * @return BOOL 
	 */
	BOOL CWordManager::isWordEditorActive();
	/**
	 * SetWordEditorParentTaskName:
	 *
	 * @return void 
	 */
	void SetWordEditorParentTaskName();
	/**
	 * GenerateXMLStringToWordEditor:
	 *
	 * @param XML_str 
	 * @return void 
	 */
	void GenerateXMLStringToWordEditor(_bstr_t XML_str);
	/**
	 * getWordTemplates:
	 *
	 * @return CStringTable& 
	 */
	CStringTable & getWordTemplates() { return m_WordTemplates; };
	/**
	 * getWordParagraphStyles:
	 *
	 * @return CStringTable& 
	 */
	CStringTable & getWordParagraphStyles() { return m_WordParagraphStyles; };
	/**
	 * getWordCharacterStyles:
	 *
	 * @return CStringTable& 
	 */
	CStringTable & getWordCharacterStyles() { return m_WordCharacterStyles; };

	/**
	 * setWordTemplate:
	 *
	 * @param word_template 
	 * @return void 
	 */
	void setWordTemplate(LPCTSTR word_template) {m_WordTemplate = word_template; };
	/**
	 * getWordTemplate:
	 *
	 * @return LPCTSTR 
	 */
	LPCTSTR getWordTemplate() {return m_WordTemplate; };

private:
	WINDOWPLACEMENT m_origWINDOWPLACEMENT;
	/**
	 * LoadSafeArrayToStringTable:
	 *
	 * @param sarray 
	 * @param st 
	 * @return static int 
	 */
	static int LoadSafeArrayToStringTable(SAFEARRAY * sarray, CStringTableImpl & st);
	/**
	 * CreateVBRAInstance:
	 *
	 * @param refLMRAInterface 
	 * @return static BOOL 
	 */
	static BOOL CreateVBRAInstance(_LMRA_XML_WordLoaderPtr & refLMRAInterface);
	DWORD m_dwEventHandlerCookie;
	CWordEventHandler * m_pEventHandler;
	_LMRA_XML_WordLoaderPtr m_WordLoader;

	CStringTableImpl m_WordTemplates;
	CStringTableImpl m_WordParagraphStyles;
	CStringTableImpl m_WordCharacterStyles;

	CString m_WordTemplate;
protected:
	/**
	 * FillActiveElements:
	 *
	 * @return void 
	 */
	void FillActiveElements();
	/**
	 * DisconnectWordEventHandler:
	 *
	 * @return void 
	 */
	void DisconnectWordEventHandler();
	/**
	 * InitWordEventHandler:
	 *
	 * @return BOOL 
	 */
	BOOL InitWordEventHandler();
	BOOL isInit();
public:
  /**
   * getLastProcessedId:
   *
   * @param  
   * @return CString 
   */
  CString getLastProcessedId(void);
  /**
   * getLastError:
   *
   * @param  
   * @return CString 
   */
  CString getLastError(void);
  
  // loads lists of Word styles from configuration XML file
	/**
	 * WordEditorInsertActiveElement: loads lists of Word styles from configuration XML file
	 *
	 * @param  
	 * @return void 
	 */
	void WordEditorInsertActiveElement(void);

private:
	/**
	 * loadStylesFromXML:
	 *
	 * @param XMLFilePath 
	 * @return BOOL 
	 */
	BOOL loadStylesFromXML(LPCTSTR XMLFilePath);
	/**
	 * saveStylesToXML: saves a list of Word styles to configutation XML file
	 *
	 * @param file_path 
	 * @return BOOL 
	 */
	BOOL saveStylesToXML(LPCTSTR file_path);
};

#endif // !defined(AFX_WORDMANAGER_H__2A5B5F90_FAA9_46F2_BC25_BE144CE6ADF6__INCLUDED_)
