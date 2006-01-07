#if !defined(AFX_XMLTREE_H__A86FA627_A96D_497D_BF96_EE94E54331D1__INCLUDED_)
#define AFX_XMLTREE_H__A86FA627_A96D_497D_BF96_EE94E54331D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XMLTree.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXMLTree window

class CXMLTree : public CTreeCtrl
{
// Construction
public:
	CXMLTree();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMLTree)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL GenerSelectedSubtree();
	BOOL LoadFromFile(CString FileName);
	virtual ~CXMLTree();

	// Generated message map functions
protected:
	void InsetXMLNode(MSXML2::IXMLDOMNodePtr iNode, HTREEITEM hParentItem);
	//{{AFX_MSG(CXMLTree)
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	MSXML2::IXMLDOMDocumentPtr m_XMLDOMDoc;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMLTREE_H__A86FA627_A96D_497D_BF96_EE94E54331D1__INCLUDED_)
