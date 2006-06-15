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


// --- AP Hypotezy

	// 4ft

CString fFE4fthyp(void * hSource)
{
	int indexSrc = ((int) hSource) - 1; 
	System::String^ HypList = FEplugin_cs::AP_FE4fthyp::getList(indexSrc);
	CString resultStr = (CString) HypList;
	return resultStr;
}

	// SD-4ft

CString fFEsd4fthyp(void * hSource)
{
	int indexSrc = ((int) hSource) - 1; 
	System::String^ HypList = FEplugin_cs::AP_FEsd4fthyp::getList(indexSrc);
	CString resultStr = (CString) HypList;
	return resultStr;
}

	// KL

CString fFEklhyp(void * hSource)
{
	int indexSrc = ((int) hSource) - 1; 
	System::String^ HypList = FEplugin_cs::AP_FEklhyp::getList(indexSrc);
	CString resultStr = (CString) HypList;
	return resultStr;
}

	// SD-KL

CString fFEsdklhyp(void * hSource)
{
	int indexSrc = ((int) hSource) - 1; 
	System::String^ HypList = FEplugin_cs::AP_FEsdklhyp::getList(indexSrc);
	CString resultStr = (CString) HypList;
	return resultStr;
}

	// CF

CString fFEcfhyp(void * hSource)
{
	int indexSrc = ((int) hSource) - 1; 
	System::String^ HypList = FEplugin_cs::AP_FEcfhyp::getList(indexSrc);
	CString resultStr = (CString) HypList;
	return resultStr;
}

	// SD-CF

CString fFEsdcfhyp(void * hSource)
{
	int indexSrc = ((int) hSource) - 1; 
	System::String^ HypList = FEplugin_cs::AP_FEsdcfhyp::getList(indexSrc);
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


// --- AP Boolsky cedent

CString fFEBool_cedent(void* hSource)
{
	int indexSrc = ((int) hSource) - 1;
	System::String^ AttrList = FEplugin_cs::AP_FEBool_cedent::getList(indexSrc);
	CString resultStr = (CString) AttrList;
	return resultStr;
}

// --- AP KL cedent

CString fFEKL_cedent(void* hSource)
{
	int indexSrc = ((int) hSource) - 1;
	System::String^ AttrList = FEplugin_cs::AP_FEKL_cedent::getList(indexSrc);
	CString resultStr = (CString) AttrList;
	return resultStr;
}

// --- AP CF cedent

CString fFECF_cedent(void* hSource)
{
	int indexSrc = ((int) hSource) - 1;
	System::String^ AttrList = FEplugin_cs::AP_FECF_cedent::getList(indexSrc);
	CString resultStr = (CString) AttrList;
	return resultStr;
}