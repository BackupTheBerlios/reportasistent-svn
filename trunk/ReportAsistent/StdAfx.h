// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
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
#if !defined(AFX_STDAFX_H__C54A2D30_CB5E_4C5E_92DA_96F4DB9D2EE4__INCLUDED_)
#define AFX_STDAFX_H__C54A2D30_CB5E_4C5E_92DA_96F4DB9D2EE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef WINVER
#define WINVER 0x0400
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcview.h>
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#include <AFXCTL.H>			// dedek: AfxConnectionAdvise()
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT



//Deda: potreba pro MSXML
#import <msxml3.dll>
//using namespace MSXML2; nepouzivat - pak to nejde prelozit ve VS 2005
//vlozi namespace MSXML2; nepouzivat - pak to nejde prelozit ve VS 2005

//potreba pro WordLoader z VisualBasicu
#import "../VB-LMRA_WordLoader/LMRA_WordLoader.exe" named_guids
#include <afxdlgs.h>
using namespace LMRA_WordLoader;
// vlozi namespace LMRA_WordLoader;




//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__C54A2D30_CB5E_4C5E_92DA_96F4DB9D2EE4__INCLUDED_)
