// WordManager.h: interface for the CWordManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORDMANAGER_H__2A5B5F90_FAA9_46F2_BC25_BE144CE6ADF6__INCLUDED_)
#define AFX_WORDMANAGER_H__2A5B5F90_FAA9_46F2_BC25_BE144CE6ADF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CStringTable
{
public:
	int FindString(LPCTSTR str);
	int virtual getCount() = NULL;
	LPCTSTR virtual getItem(int index) = NULL;
};

class CStringTableImpl : public CStringTable
{
private:
	CArray<CString *, CString *> data;	// tabulka zdroju

public:
	void Add(LPCTSTR s);

	int virtual getCount();
	LPCTSTR virtual getItem(int index);

	~CStringTableImpl();
};



class CWordManager  
{
public:
	void GenerateXMLString(_bstr_t XML_str);
	BOOL InitWordLoader();
	CWordManager();
	virtual ~CWordManager();

	void LoadWordTemplates();
	void LoadWordStyles(LPCTSTR template_name = "normal.dot");
	
	CStringTable & getWordTemplates() { return m_WordTemplates; };
	CStringTable & getWordParagraphStyles() { return m_WordParagraphStyles; };
	CStringTable & getWordCharacterStyles() { return m_WordCharacterStyles; };

private:
	_LMRA_XML_WordLoaderPtr m_WordLoader;

	CStringTableImpl m_WordTemplates;
	CStringTableImpl m_WordParagraphStyles;
	CStringTableImpl m_WordCharacterStyles;
protected:
	void LoadParagraphStyles(LPCTSTR template_name);
	void LoadCharacterStyles(LPCTSTR template_name);
	BOOL isInit();
};

#endif // !defined(AFX_WORDMANAGER_H__2A5B5F90_FAA9_46F2_BC25_BE144CE6ADF6__INCLUDED_)
