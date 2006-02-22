#if !defined(AFX_WORDVIEW_H__FA62FE84_1533_403C_BF14_CBCF7A22D2A4__INCLUDED_)
#define AFX_WORDVIEW_H__FA62FE84_1533_403C_BF14_CBCF7A22D2A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WordView.h : header file
//




/////////////////////////////////////////////////////////////////////////////
// CMyOleClientItem class

class CMyOleClientItem : public COleClientItem
{
protected:
	CWnd * m_wdpParent;

public:
	CMyOleClientItem(CWnd * parent, COleDocument* pContainerDoc = NULL) : COleClientItem(pContainerDoc)
		,m_wdpParent(parent)
	{};

public:
	virtual void OnChange(OLE_NOTIFICATION nCode, DWORD dwParam);
};


/////////////////////////////////////////////////////////////////////////////
// CWordView window

class CWordView : public CButton
{
// Construction
public:
	CWordView();

protected:
	CMyOleClientItem * m_pItem;
	COleDocument * m_pDoc;

// Attributes
public:

// Operations
public:
	LPOLEOBJECT GetWordObject(void);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWordView)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWordView();

	// Generated message map functions
protected:
	CPoint m_ptMove;
	CPoint m_ptStartDrag;
	//{{AFX_MSG(CWordView)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORDVIEW_H__FA62FE84_1533_403C_BF14_CBCF7A22D2A4__INCLUDED_)
