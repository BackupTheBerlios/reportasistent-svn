// WaitAnimation.cpp : implementation file
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

#include "stdafx.h"
#include "ReportAsistent.h"
#include "WaitAnimation.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaitAnimation

CWaitAnimation::CWaitAnimation()
{
}

CWaitAnimation::~CWaitAnimation()
{
}


BEGIN_MESSAGE_MAP(CWaitAnimation, CStatic)
	//{{AFX_MSG_MAP(CWaitAnimation)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaitAnimation message handlers

#define ABS(a) (a >= 0 ? a : -a)
#define PI 3.1415926535897932384626433832795

void CWaitAnimation::OnPaint() 
{
	static double otoc = 0;
	otoc += 0.15;
	CPaintDC dc(this); // device context for painting

	RECT rc;
	GetClientRect(& rc);

	double sx, sy;

	sx = (rc.left + rc.right)/2;
	sy = (rc.bottom + rc.top)/2;

	int x,y;

	double alpha;
	double r;
	

	for (x=rc.left; x<rc.right; x++)
	for (y=rc.top; y<rc.bottom; y++)
	{
		r = sqrt((x-sx)*(x-sx) + (y-sy)*(y-sy));
		alpha = count_angle(x-sx, y-sy);

		alpha += otoc; //pootoceni
//		alpha = otoc; //pootoceni
		int div = (int) (alpha/(2*PI)); 
		alpha -= 2*PI*div;
		
		dc.SetPixel(x, y, GetPixelColor(r, alpha));
		
	}
}



double CWaitAnimation::count_angle(double x, double y)
{
	if (x >= 0)
	{
		if (y > 0)
			return atan(y/x);
		else
			return (2*PI) - atan((-y)/x);
	}
	else
	{
		if (y > 0)
			return PI - atan(y/(-x));
		else
			return PI + atan(y/x);
	}

}

#define DR 30


COLORREF CWaitAnimation::GetPixelColor(double r, double alpha)
{
	alpha = 2*PI-alpha;
	
	int r_div = (int) (r/DR); 
	if ((r - r_div) > (DR/2)) r_div++;
	if (r_div == 0) r_div++;

	return (COLORREF) (255* ABS(((r - (r_div + alpha/(2*PI))*DR))/DR));
}


/*

void CWaitDlg::OnClose() 
{
	int ret = MessageBox("Do you really want to terminate the Application?", "Terminate?", MB_YESNO | MB_ICONSTOP);
	if (ret == IDYES) OnTerminate();
}

void CWaitDlg::OnOK() 
{}

void CWaitDlg::OnCancel() 
{}

void CWaitDlg::OnTerminate() 
{
 	TerminateProcess(GetCurrentProcess(), 0);
}

*/


