#if !defined(AFX_GENERATEDIALOG_H__B6BE28EE_6665_4B0C_82E9_8F658541580A__INCLUDED_)
#define AFX_GENERATEDIALOG_H__B6BE28EE_6665_4B0C_82E9_8F658541580A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GenerateDialog.h : header file
//

//#include "SkeletonManager.h"

/////////////////////////////////////////////////////////////////////////////
// CGenerateDialog dialog

class CGenerateDialog : public CDialog
{
// Construction
public:
	CGenerateDialog(CSkeletonDoc & DocumentToGenerate, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGenerateDialog)
	enum { IDD = IDD_GENERATE_DIALOG };
	BOOL	m_bNewWordChecked;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGenerateDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGenerateDialog)
	afx_msg void OnGenerateButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CSkeletonDoc & m_SkeletonDocument;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENERATEDIALOG_H__B6BE28EE_6665_4B0C_82E9_8F658541580A__INCLUDED_)
