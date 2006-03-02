// SkeletonView.h : interface of the CSkeletonView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKELETONVIEW_H__7EE68070_62BF_4C22_A2E1_57F1897D226D__INCLUDED_)
#define AFX_SKELETONVIEW_H__7EE68070_62BF_4C22_A2E1_57F1897D226D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSkeletonView : public CTreeView
{
protected: // create from serialization only
	CSkeletonView();
	DECLARE_DYNCREATE(CSkeletonView)

// Attributes
public:
	CSkeletonDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkeletonView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSkeletonView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSkeletonView)
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SkeletonView.cpp
inline CSkeletonDoc* CSkeletonView::GetDocument()
   { return (CSkeletonDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKELETONVIEW_H__7EE68070_62BF_4C22_A2E1_57F1897D226D__INCLUDED_)
