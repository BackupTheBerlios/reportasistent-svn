#if !defined(AFX_WORDEVENTHANDLER_H__B6271273_95E9_4D53_A29B_41F63F14BB5F__INCLUDED_)
#define AFX_WORDEVENTHANDLER_H__B6271273_95E9_4D53_A29B_41F63F14BB5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WordEventHandler.h : header file
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


/////////////////////////////////////////////////////////////////////////////
// CWordEventHandler command target

/**
 * class CWordEventHandler:
 *
 * @author 
 */
class CWordEventHandler : public CCmdTarget
{
	DECLARE_DYNCREATE(CWordEventHandler)

	CWordEventHandler();           // protected constructor used by dynamic creation

// Attributes
public:
	CString m_strLastElementName;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWordEventHandler)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWordEventHandler();

protected:

	// Generated message map functions
	//{{AFX_MSG(CWordEventHandler)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CWordEventHandler)
	afx_msg void onActiveElementSelected(LPCTSTR strElementName);
	afx_msg void onSetOptions();
	afx_msg void onSetSources();
	afx_msg void onSkeletonEditor();
	afx_msg void onWordQuit();
	afx_msg void onPrepareParentTaskActivation();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORDEVENTHANDLER_H__B6271273_95E9_4D53_A29B_41F63F14BB5F__INCLUDED_)
