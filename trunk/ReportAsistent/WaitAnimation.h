#if !defined(AFX_WAITANIMATION_H__069AA26D_A15E_485E_AC8F_1AEEA82F3068__INCLUDED_)
#define AFX_WAITANIMATION_H__069AA26D_A15E_485E_AC8F_1AEEA82F3068__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WaitAnimation.h : header file
//
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

LM Report Asistent is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with LM Report Asistent; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
/////////////////////////////////////////////////////////////////////////////
// CWaitAnimation window

/**
 * class CWaitAnimation:
 *
 * @author 
 */
class CWaitAnimation : public CStatic
{
// Construction
public:
	CWaitAnimation();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaitAnimation)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWaitAnimation();

	// Generated message map functions
protected:
	/**
	 * GetPixelColor:
	 *
	 * @param r 
	 * @param alpha 
	 * @return virtual COLORREF 
	 */
	virtual COLORREF GetPixelColor(double r, double alpha);
	//{{AFX_MSG(CWaitAnimation)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	/**
	 * count_angle:
	 *
	 * @param x 
	 * @param y 
	 * @return static double 
	 */
	static double count_angle(double x, double y);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAITANIMATION_H__069AA26D_A15E_485E_AC8F_1AEEA82F3068__INCLUDED_)
