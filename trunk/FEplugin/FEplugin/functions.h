// Functions of FEplugin, which evaluates queries about active elements (AP)
// functions.h

#ifndef _FUNCTIONS_FE
#define _FUNCTIONS_FE

// ===== INCLUDE =======

#include <afx.h>

// ===== FUNCTIONS ========


// --- AP Category

CString fFECategory(void* hSource);  /// Function resolving query of LM-RA kernell about active element "Category" (ID="category")

// --- AP Column

CString fFEColumn(void* hSource); /// Function resolving query of LM-RA kernell about active element "Column of data matrix" (ID="column")

// --- AP Data matrix

CString fFEData_matrix(void* hSource);/// Function resolving query of LM-RA kernell about active element "Data matrix" (ID="data_matrix")


// --- AP "Hypotheses"

CString fFE4fthyp(void* hSource);  /// Function resolving query of LM-RA kernell about active element "4ft-hypothesis" (ID="hyp_4ft") 
CString fFEsd4fthyp(void* hSource);  /// Function resolving query of LM-RA kernell about active element "SD-4ft-hypothesis" (ID="hyp_sd4ft")
CString fFEklhyp(void* hSource);  /// Function resolving query of LM-RA kernell about active element "KL-hypothesis" (ID="hyp_kl")
CString fFEsdklhyp(void* hSource);  /// Function resolving query of LM-RA kernell about active element "SD-KL-hypothesis" (ID="hyp_sdkl")
CString fFEcfhyp(void* hSource);  /// Function resolving query of LM-RA kernell about active element "CF-hypothesis" (ID="hyp_cf")
CString fFEsdcfhyp(void* hSource);  /// Function resolving query of LM-RA kernell about active element "SD-CF-hypothesis" (ID="hyp_sdcf")

// --- AP Attribute

CString fFEAttribute(void* hSource); /// Function resolving query of LM-RA kernell about active element "Attribute" (ID="attribute")

// --- AP Boolean cedent

CString fFEBool_cedent(void* hSource); /// Function resolving query of LM-RA kernell about active element "Boolean cedent" (ID="bool_cedent")

// --- AP KL cedent

CString fFEKL_cedent(void* hSource); /// Function resolving query of LM-RA kernell about active element "KL cedent" (ID="KL_cedent")

// --- AP CF cedent

CString fFECF_cedent(void* hSource); /// Function resolving query of LM-RA kernell about active element "CF cedent" (ID="CF_cedent")

// --- AP Quantifier

CString fFEQuantifier(void* hSource); /// Function resolving query of LM-RA kernell about active element "Quantifier" (ID="quantifier")

// --- AP Task

CString fFETask(void* hSource); /// Function resolving query of LM-RA kernell about active element "Task" (ID="task")

// --- AP Ferda Data Miner box

CString fFEferda_box(void* hSource); /// Function resolving query of LM-RA kernell about active element "Ferda Data Miner box" (ID="ferda_box")


#endif /* _FUNCTIONS*/