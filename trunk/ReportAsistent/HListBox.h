#if !defined(AFX_HLISTBOX_H__346C3917_14BC_11D5_A025_006067718D04__INCLUDED_)
#define AFX_HLISTBOX_H__346C3917_14BC_11D5_A025_006067718D04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HListBox.h : header file
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
// CHListBox window

/**
 * class CHListBox:
 *
 * @author 
 */
class CHListBox : public CListBox
{
// Construction
public:
	CHListBox();

// Attributes
public:

// Operations
public:
    int AddString(LPCTSTR s);
    int InsertString(int i, LPCTSTR s);
    void ResetContent();
    int DeleteString(int i);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHListBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHListBox();

	// Generated message map functions
protected:
        void updateWidth(LPCTSTR s);
	int width;
	//{{AFX_MSG(CHListBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HLISTBOX_H__346C3917_14BC_11D5_A025_006067718D04__INCLUDED_)
