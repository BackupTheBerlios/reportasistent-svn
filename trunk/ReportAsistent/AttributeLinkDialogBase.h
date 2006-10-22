// AttributeLinkDialogBase.h: interface for the CAttributeLinkDialogBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATTRIBUTELINKDIALOGBASE_H__715B070E_2493_4E4D_8E5F_AF11FB8EF94F__INCLUDED_)
#define AFX_ATTRIBUTELINKDIALOGBASE_H__715B070E_2493_4E4D_8E5F_AF11FB8EF94F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ATTRLIST_CL_NAME	0
#define ATTRLIST_CL_VALUE	1


class CAttributeLinkDialogBase  
{
protected:
	MSXML2::IXMLDOMElementPtr & m_SelXMLElm;

public:
	CAttributeLinkDialogBase(MSXML2::IXMLDOMElementPtr & edited_element);   // standard constructor

protected:
	void SaveTarget(CComboBox & target_combo);
	void OnRefresh(CListCtrl & AttributesList, LPCTSTR target_id);
	void FillAttributesList(CListCtrl & AttributesList, LPCTSTR target_id);
	void InitAttributesList(CListCtrl & AttributesList);
	void FillTargets(CComboBox & TargetCombo);
	void InitBaseDialog(CListCtrl & AttributesList, CComboBox & TargetCombo);
};

#endif // !defined(AFX_ATTRIBUTELINKDIALOGBASE_H__715B070E_2493_4E4D_8E5F_AF11FB8EF94F__INCLUDED_)
