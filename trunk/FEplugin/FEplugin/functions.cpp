// implementace funkci pro vyrizeni pozadavku na AP v zasuvce pro Ferdu
// functions.h
#include <stdafx.h>

#include "functions.h"

using namespace FEplugin_cs;


/*
#import <msxml3.dll>
using namespace MSXML2;
//vlozi namespace MSXML2;
*/



// --- AP Kategorie

CString fFECategory(void* hSource)
{
	int indexSrc = ((int) hSource) - 1; 
	System::String^ CatList = FEplugin_cs::AP_FECategory::getList(indexSrc);
	CString resultStr = (CString) CatList;
	return resultStr;
}


// --- AP 4ft-hypoteza

CString fFE4fthyp(void * hSource)
{
	int indexSrc = ((int) hSource) - 1; 
	System::String^ HypList = FEplugin_cs::AP_FE4fthyp::getList(indexSrc);
	CString resultStr = (CString) HypList;
	return resultStr;
}

// --- AP Atribut

CString fFEAttribute(void* hSource)
{
	int indexSrc = ((int) hSource) - 1;
	System::String^ AttrList = FEplugin_cs::AP_FEAttribute::getList(indexSrc);
	CString resultStr = (CString) AttrList;
	return resultStr;
}

