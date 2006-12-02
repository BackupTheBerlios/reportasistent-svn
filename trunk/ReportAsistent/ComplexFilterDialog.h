#include "afxwin.h"
#include "afxcmn.h"
#include "HListBox.h"
#if !defined(AFX_COMPLEXFILTERDIALOG_H__2CD50BAE_2DA0_4301_AEB9_05756F4ED841__INCLUDED_)
#define AFX_COMPLEXFILTERDIALOG_H__2CD50BAE_2DA0_4301_AEB9_05756F4ED841__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComplexFilterDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComplexFilterDialog dialog

class CAElDataShare
{
protected:
	void ApplyChanges();

	BOOL & m_bApplyButtonUsed;

public:
	BOOL ApplyButtonUsed() {return m_bApplyButtonUsed; };

	CAElDataShare(
		MSXML2::IXMLDOMElementPtr & active_element,
		MSXML2::IXMLDOMElementPtr & cloned_active_element,
   		MSXML2::IXMLDOMElementPtr & filter_DOM,
		BOOL & bApplyButtonUsed);

	CAElDataShare(CAElDataShare & data_share);

	MSXML2::IXMLDOMElementPtr & m_active_element;
	MSXML2::IXMLDOMElementPtr & m_cloned_active_element;
   	MSXML2::IXMLDOMElementPtr & m_filter_DOM;
};

class CFilterResultImpl
{
protected:
	int getAttributesCount();
	CString getAttributeName(int index);
	CString getAttributeLabel(int index);

	CFilterResultImpl(MSXML2::IXMLDOMElementPtr & filter_DOM)  : m_result_filter_DOM(filter_DOM) {};

  	MSXML2::IXMLDOMElementPtr & m_result_filter_DOM;	//data pouzita na naplneni list veiw
	CListCtrl m_ResultList;

	void InitResultView();
	void UpdateResult(MSXML2::IXMLDOMElementPtr & filter_dom);
};


class CComplexFilterDialog : public CDialog, CFilterResultImpl
{
//	DECLARE_DYNCREATE(CComplexFilterDialog)

// Construction
public:
	CComplexFilterDialog(MSXML2::IXMLDOMElementPtr & active_element, MSXML2::IXMLDOMElementPtr & filter_DOM, CWnd* pParent = NULL);	// nestandard constructor :-)
	CComplexFilterDialog(MSXML2::IXMLDOMElementPtr & active_element, MSXML2::IXMLDOMElementPtr & filter_DOM, MSXML2::IXMLDOMElementPtr currnet_attribute_filter, CWnd* pParent = NULL);
	~CComplexFilterDialog();

// Dialog Data
	//{{AFX_DATA(CComplexFilterDialog)
	enum { IDD = IDD_COMPLEX_FILTER_DIALOG };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CComplexFilterDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CComplexFilterDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
private:
	BOOL m_bNumericSort;
	int m_nFilterTypeRadioGroup;
	int m_nSortDirectionRadioGroup;
	BOOL m_bSourceIsInit;
	CComboBox m_SourcesCombo;
	MSXML2::IXMLDOMElementPtr & m_active_element;
 
	MSXML2::IXMLDOMElementPtr m_currnet_attribute_filter;


//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	afx_msg void OnSelchangeDataSourceCombo();
//    BOOL LoadSource(public_source_id_t sId);

    void UpDateDialog();

	CHListBox m_AttributesList;
	CHListBox m_ValuesList;
	afx_msg void OnLbnSelchangeAttributesList();
	afx_msg void OnDestroy();
	void ClearAttributesList(void);
	afx_msg void OnBnClickedAscendingRadio();
	afx_msg void OnBnClickedDescendingRadio();
protected:
	void SetSortButtons(MSXML2::IXMLDOMElementPtr & attr_elem);
	void FillValuesList(LPCTSTR cur_attr_str = NULL);
public:
	afx_msg void OnBnClickedNumericSortCheck();
	CEdit m_TresholdEdeit;
	unsigned int m_nTopNValues;
public:
//	afx_msg void OnDeltaposTopnSpin(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CSpinButtonCtrl m_TopNSpin;
public:
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnLbnSelchangeValuesList();
	
private:
	void InitDialogFromXML(void);
	void AppendFilter(void);
	MSXML2::IXMLDOMElementPtr CreateAttrFilterElement();

	int m_nSlectedAttrIndex;
	CString m_sTresholdOrFixedValue;
	afx_msg void OnBnClickedRefreshResultsButton();
private:
//	void UpdateResult(MSXML2::IXMLDOMElementPtr & filter_dom);
private:
	afx_msg void OnBnClickedFilterTypeRadio();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPLEXFILTERDIALOG_H__2CD50BAE_2DA0_4301_AEB9_05756F4ED841__INCLUDED_)
