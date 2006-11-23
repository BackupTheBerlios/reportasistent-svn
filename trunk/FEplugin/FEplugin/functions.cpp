// implementation of functions, which evaluate a queries about active element in FEplugin
// functions.h
#include <stdafx.h>

#include "functions.h"

using namespace FEplugin_cs;


// ========= AP Analyzed data =============

// --- AP Category

CString fFECategory(void* hSource)
{
	int indexSrc = ((int) hSource) - 1; 
	System::String^ CatList = FEplugin_cs::AP_FECategory::getList(indexSrc);
	CString resultStr = (CString) CatList;
	return resultStr;
}


// --- AP Column 

CString fFEColumn(void* hSource)
{
	int indexSrc = ((int) hSource) - 1; 
	System::String^ ColList = FEplugin_cs::AP_FEColumn::getList(indexSrc);
	CString resultStr = (CString) ColList;
	return resultStr;
}


// --- AP Data matrix

CString fFEData_matrix(void* hSource)
{
	int indexSrc = ((int) hSource) - 1; 
	System::String^ MatList = FEplugin_cs::AP_FEData_matrix::getList(indexSrc);
	CString resultStr = (CString) MatList;
	return resultStr;
}

// ========= AP Hypotheses =============

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

// ========= AP Attributes, cedents =============


// --- AP Attribute

CString fFEAttribute(void* hSource)
{
	int indexSrc = ((int) hSource) - 1;
	System::String^ AttrList = FEplugin_cs::AP_FEAttribute::getList(indexSrc);
	CString resultStr = (CString) AttrList;
	return resultStr;
}


// --- AP Boolean cedent

CString fFEBool_cedent(void* hSource)
{
	int indexSrc = ((int) hSource) - 1;
	System::String^ BCList = FEplugin_cs::AP_FEBool_cedent::getList(indexSrc);
	CString resultStr = (CString) BCList;
	return resultStr;
}

// --- AP KL cedent

CString fFEKL_cedent(void* hSource)
{
	int indexSrc = ((int) hSource) - 1;
	System::String^ KLCList = FEplugin_cs::AP_FEKL_cedent::getList(indexSrc);
	CString resultStr = (CString) KLCList;
	return resultStr;
}

// --- AP CF cedent

CString fFECF_cedent(void* hSource)
{
	int indexSrc = ((int) hSource) - 1;
	System::String^ CFCList = FEplugin_cs::AP_FECF_cedent::getList(indexSrc);
	CString resultStr = (CString) CFCList;
	return resultStr;
}

// ========= AP Quantifier =============

// --- AP Quantifier

CString fFEQuantifier(void* hSource)
{
	int indexSrc = ((int) hSource) - 1;
	System::String^ QantList = FEplugin_cs::AP_FEQuantifier::getList(indexSrc);
	CString resultStr = (CString) QantList;
	return resultStr;
}


// ========= AP Task =============

// --- AP Task

CString fFETask(void* hSource)
{
	int indexSrc = ((int) hSource) - 1;
	System::String^ TaskList = FEplugin_cs::AP_FETask::getList(indexSrc);
	CString resultStr = (CString) TaskList;
	return resultStr;
}

// ========= AP Ferda Data Miner box =============

// --- AP Ferda Data Miner box

CString fFEferda_box(void* hSource)
{
	int indexSrc = ((int) hSource) - 1;
	System::String^ BoxList = FEplugin_cs::AP_FEferda_box::getList(indexSrc);
	CString resultStr = (CString) BoxList;
	return resultStr;
}