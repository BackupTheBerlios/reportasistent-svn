#if !defined(AFX_TRANSFORMATIONSDIALOG_H__BE8C8E40_78CC_4E3F_9047_DD5A7E3900BB__INCLUDED_)
#define AFX_TRANSFORMATIONSDIALOG_H__BE8C8E40_78CC_4E3F_9047_DD5A7E3900BB__INCLUDED_

#include "SimpleFilterDialog.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransformationsDialog.h : header file
//
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#if !defined MAX_TRANSFORMATION_COUNT
#define MAX_TRANSFORMATION_COUNT  20
#endif

#if !defined MAX_CHOSEN_TRANSFORMATION_COUNT
#define MAX_CHOSEN_TRANSFORMATION_COUNT 20
#endif
#include "PropertyEditor.h"

#include "complexfilterdialog.h"


/////////////////////////////////////////////////////////////////////////////
// CTransformationsDialog dialog

/**
 * class CTransformationsDialog:
 *
 * @author 
 */
class CTransformationsDialog : public CPropertyPage, CAElDataShare
{
// Construction
public:
	CTransformationsDialog(CAElDataShare & data_share, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTransformationsDialog)
	enum { IDD = IDD_TRANSFORMATIONS_DIALOG };
	CButton	m_ConfigureButton;
	CHListBox	m_SupportedList;
	CHListBox	m_SelectedList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransformationsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	/**
	 * RemoveTransf:
	 *
	 * @param selected_item 
	 * @return void 
	 */
	void RemoveTransf(int selected_item);
	/**
	 * SelTransformConfigure:
	 *
	 * @param cur_sel 
	 * @return void 
	 */
	void SelTransformConfigure(int cur_sel);
	/**
	 * AddTransformation:
	 *
	 * @param selected_item 
	 * @return BOOL 
	 */
	BOOL AddTransformation(int selected_item);
	/**
	 * ConfigureTransformation:
	 *
	 * @param transform_index 
	 * @return void 
	 */
	void ConfigureTransformation(int transform_index);
	/**
	 * IsSelectedTransformationWithOptions:
	 *
	 * @param transform_index 
	 * @return BOOL 
	 */
	BOOL IsSelectedTransformationWithOptions(int transform_index);
	/**
	 * IsSelectedTransformationAttrLinkTable:
	 *
	 * @param transform_index 
	 * @return BOOL 
	 */
	BOOL IsSelectedTransformationAttrLinkTable(int transform_index);
	/**
	 * ConfigureAttrLinkTable:
	 *
	 * @param attr_link_tbl_node 
	 * @return void 
	 */
	void ConfigureAttrLinkTable(MSXML2::IXMLDOMNodePtr & attr_link_tbl_node);

	// Generated message map functions
	//{{AFX_MSG(CTransformationsDialog)
	virtual BOOL OnInitDialog();
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
	MSXML2::IXMLDOMElementPtr m_cloned_output_element;
	//zmeny se provadeji v klonu, pokud uzivatel zmacken OK, puvodni element (m_active_element) se nahradi klonem

private:
	/**
	 * FindOptionEnumItemLabelFromValue:
	 *
	 * @param options_node 
	 * @param variable_name 
	 * @param otion_value 
	 * @return CString static 
	 */
	CString static FindOptionEnumItemLabelFromValue(
							MSXML2::IXMLDOMNodePtr & options_node,
							LPCTSTR variable_name,
							LPCTSTR otion_value);

	/**
	 * FindOptionEnumItemValueFromLabel:
	 *
	 * @param options_node 
	 * @param variable_name 
	 * @param otion_value 
	 * @return CString static 
	 */
	CString static FindOptionEnumItemValueFromLabel(
							MSXML2::IXMLDOMNodePtr & options_node,
							LPCTSTR variable_name,
							LPCTSTR otion_value);

	/**
	 * CreateEnumProperty:
	 *
	 * @param option_element 
	 * @param current_value 
	 * @return static CProperty* 
	 */
	static CProperty * CreateEnumProperty(
					MSXML2::IXMLDOMElementPtr & option_element,
					LPCTSTR current_value);

	/**
	 * CreateDoubleProperty:
	 *
	 * @param option_element 
	 * @param current_value 
	 * @return static CProperty* 
	 */
	static CProperty * CreateDoubleProperty(
					MSXML2::IXMLDOMElementPtr & option_element,
					LPCTSTR current_value);

	/**
	 * CreateIntProperty:
	 *
	 * @param option_element 
	 * @param current_value 
	 * @return static CProperty* 
	 */
	static CProperty * CreateIntProperty(
					MSXML2::IXMLDOMElementPtr & option_element,
					LPCTSTR current_value);

	/**
	 * AddOptionToPropetryEditor:
	 *
	 * @param option_element 
	 * @param transformation_element 
	 * @param property_editor 
	 * @return static void 
	 */
	static void AddOptionToPropetryEditor(
			MSXML2::IXMLDOMElementPtr & option_element,
			MSXML2::IXMLDOMElementPtr & transformation_element,
			CPropertyEditor & property_editor);



  /**
   * OnApply:
   *
   * @return virtual BOOL 
   */
  virtual BOOL OnApply();
  /**
   * OnKillActive:
   *
   * @return virtual BOOL 
   */
  virtual BOOL OnKillActive();
  /**
   * OnSetActive:
   *
   * @return virtual BOOL 
   */
  virtual BOOL OnSetActive();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSFORMATIONSDIALOG_H__BE8C8E40_78CC_4E3F_9047_DD5A7E3900BB__INCLUDED_)
