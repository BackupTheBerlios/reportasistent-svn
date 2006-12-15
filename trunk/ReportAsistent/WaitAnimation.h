#if !defined(AFX_WAITANIMATION_H__069AA26D_A15E_485E_AC8F_1AEEA82F3068__INCLUDED_)
#define AFX_WAITANIMATION_H__069AA26D_A15E_485E_AC8F_1AEEA82F3068__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WaitAnimation.h : header file
//

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
