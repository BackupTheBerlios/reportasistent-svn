#if !defined(AFX_TRANSFORMATIONSDIALOG_H__BE8C8E40_78CC_4E3F_9047_DD5A7E3900BB__INCLUDED_)
#define AFX_TRANSFORMATIONSDIALOG_H__BE8C8E40_78CC_4E3F_9047_DD5A7E3900BB__INCLUDED_

#include "SimpleFilterDialog.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransformationsDialog.h : header file
//

#if !defined MAX_TRANSFORMATION_COUNT
#define MAX_TRANSFORMATION_COUNT  20
#endif

#if !defined MAX_CHOSEN_TRANSFORMATION_COUNT
#define MAX_CHOSEN_TRANSFORMATION_COUNT 20
#endif
#include "PropertyEditor.h"

/////////////////////////////////////////////////////////////////////////////
// CTransformationsDialog dialog

class CTransformationsDialog : public CPropertyPage
{
// Construction
public:
	BOOL SaveAll();
	CTransformationsDialog(MSXML2::IXMLDOMElementPtr & active_element, MSXML2::IXMLDOMElementPtr & cloned_element, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTransformationsDialog)
	enum { IDD = IDD_TRANSFORMATIONS_DIALOG };
	CButton	m_ConfigureButton;
	CListBox	m_SupportedList;
	CListBox	m_SelectedList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransformationsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void RemoveTransf(int selected_item);
	void SelTransformConfigure(int cur_sel);
	BOOL AddTransformation(int selected_item);
	void ConfigureTransformation(int transform_index);
	BOOL IsSelectedTransformationWithOptions(int transform_index);
	BOOL IsSelectedTransformationAttrLinkTable(int transform_index);
	void ConfigureAttrLinkTable(MSXML2::IXMLDOMNodePtr & attr_link_tbl_node);

	// Generated message map functions
	//{{AFX_MSG(CTransformationsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddButton();
	afx_msg void OnRemoveButton();
	afx_msg void OnMoveUpButton();
	afx_msg void OnMoveDownButton();
	afx_msg void OnConfigureButton();
	afx_msg void OnDblclkSupportedTransfList();
	afx_msg void OnDblclkSelectedTransfsList();
	afx_msg void OnSelchangeSelectedTransfsList();
	afx_msg void OnSelcancelSelectedTransfsList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	MSXML2::IXMLDOMElementPtr & m_active_element;
	MSXML2::IXMLDOMElementPtr & m_cloned_active_element;
	MSXML2::IXMLDOMElementPtr m_cloned_output_element;
	//zmeny se provadeji v klonu, pokud uzivatel zmacken OK, puvodni element (m_active_element) se nahradi klonem

private:
	CString static FindOptionEnumItemLabelFromValue(
							MSXML2::IXMLDOMNodePtr & options_node,
							LPCTSTR variable_name,
							LPCTSTR otion_value);

	CString static FindOptionEnumItemValueFromLabel(
							MSXML2::IXMLDOMNodePtr & options_node,
							LPCTSTR variable_name,
							LPCTSTR otion_value);

	static CProperty * CreateEnumProperty(
					MSXML2::IXMLDOMElementPtr & option_element,
					LPCTSTR current_value);

	static CProperty * CreateDoubleProperty(
					MSXML2::IXMLDOMElementPtr & option_element,
					LPCTSTR current_value);

	static CProperty * CreateIntProperty(
					MSXML2::IXMLDOMElementPtr & option_element,
					LPCTSTR current_value);

	static void AddOptionToPropetryEditor(
			MSXML2::IXMLDOMElementPtr & option_element,
			MSXML2::IXMLDOMElementPtr & transformation_element,
			CPropertyEditor & property_editor);



  virtual BOOL OnApply();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSFORMATIONSDIALOG_H__BE8C8E40_78CC_4E3F_9047_DD5A7E3900BB__INCLUDED_)
