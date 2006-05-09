#if !defined(AFX_ELEMENTPARAGRAPHDIALOG_H__BF12F658_F56C_4F06_8464_9C689F26DD93__INCLUDED_)
#define AFX_ELEMENTPARAGRAPHDIALOG_H__BF12F658_F56C_4F06_8464_9C689F26DD93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ElementParagraphDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CElementParagraphDialog dialog

class CElementParagraphDialog : public CDialog
{
// Construction
public:
	IXMLDOMElementPtr m_SelXMLElm;
	void DDV_NonDuplicateID(CDataExchange *pDX, int nId, CString csIDEditValue);
	CElementParagraphDialog(IXMLDOMElementPtr & SelXMLElm,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CElementParagraphDialog)
	enum { IDD = IDD_DIALOG_PARAGRAPH };
	CString	m_DialParagraphIDEditValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CElementParagraphDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_OldID;

	// Generated message map functions
	//{{AFX_MSG(CElementParagraphDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELEMENTPARAGRAPHDIALOG_H__BF12F658_F56C_4F06_8464_9C689F26DD93__INCLUDED_)
