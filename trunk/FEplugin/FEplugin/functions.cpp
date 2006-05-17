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
	CString buf = "<?xml version=\"1.0\" encoding=\"windows-1250\" ?> <!DOCTYPE active_list[ <!ELEMENT active_list ((hyp_4ft*, category*, ti_cedent*, attribute*)*)> <!ELEMENT attribute (ctgr*, missing_value*)> <!ATTLIST attribute id ID #REQUIRED db_name CDATA #REQUIRED matrix_name CDATA #REQUIRED attr_name CDATA #REQUIRED creation CDATA #REQUIRED ctgr_count CDATA #REQUIRED> <!ELEMENT ctgr EMPTY> <!ATTLIST ctgr name CDATA #REQUIRED> <!ELEMENT missing_value EMPTY> <!ATTLIST missing_value name CDATA #REQUIRED> <!ELEMENT category (ctgr_def*)> <!ATTLIST category id ID #REQUIRED db_name CDATA #REQUIRED matrix_name CDATA #REQUIRED attr_name CDATA #REQUIRED ctgr_name CDATA #REQUIRED ctgr_type CDATA #REQUIRED ctgr_freq CDATA #REQUIRED bool_type CDATA #REQUIRED def_length CDATA #REQUIRED> <!ELEMENT ctgr_def EMPTY> <!ATTLIST ctgr_def definition CDATA #REQUIRED> <!ELEMENT ti_cedent (ti_literal*)> <!ATTLIST ti_cedent id ID #REQUIRED type CDATA #REQUIRED> <!--antecedent, succedent, condition --> <!ELEMENT ti_literal EMPTY> <!ATTLIST ti_literal id ID #REQUIRED quant CDATA #REQUIRED value CDATA #REQUIRED> <!--quant: name of the quantity used in hypothese, e. g. diastolic pressure --> <!--value: value of the quantity used in hypothese, e. g. <50;60) --> <!ELEMENT hyp_4ft EMPTY> <!ATTLIST hyp_4ft id ID #REQUIRED db_name CDATA #REQUIRED matrix_name CDATA #REQUIRED task_name CDATA #REQUIRED a CDATA #REQUIRED b CDATA #REQUIRED c CDATA #REQUIRED d CDATA #REQUIRED conf CDATA #REQUIRED d_conf CDATA #REQUIRED e_conf CDATA #REQUIRED support CDATA #REQUIRED completeness CDATA #REQUIRED avg_diff CDATA #REQUIRED low_bnd_imp CDATA #REQUIRED up_bnd_imp CDATA #REQUIRED low_bnd_dbl_imp CDATA #REQUIRED up_bnd_dbl_imp CDATA #REQUIRED low_bnd_eq CDATA #REQUIRED up_bnd_eq CDATA #REQUIRED fisher CDATA #REQUIRED chi_sq CDATA #REQUIRED antecedent IDREF #IMPLIED succedent IDREF #IMPLIED condition IDREF #IMPLIED> <!--antecedent,succedent,condition: references to ti_cedent --> ]>  <active_list>  <category id=\"cat1\" db_name=\"D:\Projekt\Vyvoj\ReportAsistent\LMMetabase\LMEmpty2\" matrix_name=\"Entry\" attr_name=\"BMI\" ctgr_name=\"podvaha\" ctgr_type=\"Interval\" ctgr_freq=\"N/A\" bool_type=\"No boolean\" def_length=\"1\"> <ctgr_def definition=\"&lt;15;20)\" /> </category> <category id=\"cat2\" db_name=\"D:\Projekt\Vyvoj\ReportAsistent\LMMetabase\LMEmpty2\" matrix_name=\"Entry\" attr_name=\"BMI\" ctgr_name=\"normal\" ctgr_type=\"Interval\" ctgr_freq=\"N/A\" bool_type=\"No boolean\" def_length=\"1\"> <ctgr_def definition=\"&lt;20;25)\" /> </category> </active_list>";
	return buf;
}


// --- AP 4ft-hypoteza

CString fFE4fthyp(void * hSource)
{
	int indexSrc = ((int) hSource) - 1; 
	System::String^ HypList = FEplugin_cs::FEAPFunctions::fFE4fthyp(indexSrc);
	CString resultStr = (CString) HypList;
	return resultStr;
}



