// AttributeLinkDialogBase.h: interface for the CAttributeLinkDialogBase class.
//
//////////////////////////////////////////////////////////////////////
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
#if !defined(AFX_ATTRIBUTELINKDIALOGBASE_H__715B070E_2493_4E4D_8E5F_AF11FB8EF94F__INCLUDED_)
#define AFX_ATTRIBUTELINKDIALOGBASE_H__715B070E_2493_4E4D_8E5F_AF11FB8EF94F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ATTRLIST_CL_NAME	0
#define ATTRLIST_CL_VALUE	1


/**
 * class CAttributeLinkDialogBase:
 *
 * @author 
 */
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
