// implementace funkci pro vyrizeni pozadavku na AP v zasuvce pro Ferdu
// functions.h
#include <stdafx.h>

#include "functions.h"




/*
#import <msxml3.dll>
using namespace MSXML2;
//vlozi namespace MSXML2;
*/



// --- AP Kategorie

CString fFECategory(void* hSource)
{
	int indexSrc = ((int) hSource) - 1; 
	System::String^ CatList = FEplugin_cs::FEAPFunctions::fFECategory(indexSrc);
	CString resultStr = (CString) CatList;
	return resultStr;
}


// --- AP 4ft-hypoteza

CString fFE4fthyp(void * hSource)
{
	int indexSrc = ((int) hSource) - 1; 
	System::String^ HypList = FEplugin_cs::FEAPFunctions::fFE4fthyp(indexSrc);
	CString resultStr = (CString) HypList;
	return resultStr;
}

// --- AP Atribut

CString fFEAttribute(void* hSource)
{
	int indexSrc = ((int) hSource) - 1;
	System::String^ AttrList = FEplugin_cs::FEAPFunctions::fFEAttribute(indexSrc);
	CString resultStr = (CString) AttrList;
	return resultStr;
}

