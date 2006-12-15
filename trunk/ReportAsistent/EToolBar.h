#if !defined(AFX_ETOOLBAR_H__77EDAB19_6435_4D1E_A0F5_427A81A13B94__INCLUDED_)
#define AFX_ETOOLBAR_H__77EDAB19_6435_4D1E_A0F5_427A81A13B94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EToolBar.h : header file
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
// CEToolBar window

/**
 * class CEToolBar:
 *
 * @author 
 */
class CEToolBar : public CToolBar
{
// Construction
public:
	CEToolBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEToolBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEToolBar)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ETOOLBAR_H__77EDAB19_6435_4D1E_A0F5_427A81A13B94__INCLUDED_)
