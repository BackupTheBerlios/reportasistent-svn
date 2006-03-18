#define DTD "<?xml version=\"1.0\" encoding=\"windows-1250\" ?> \
<!DOCTYPE active_list[ \
  <!ELEMENT active_list (hyp_4ft*, category*, ti_cedent*)> \
  <!ELEMENT category EMPTY> \
  <!ATTLIST category id ID #REQUIRED \
                     db_name CDATA #REQUIRED \
                     matrix_name CDATA #REQUIRED \
                     attr_name CDATA #REQUIRED \
                     ctgr_name CDATA #REQUIRED \
                     ctgr_type CDATA #REQUIRED \
                     ctgr_def CDATA #REQUIRED \
                     ctgr_freq CDATA #REQUIRED> "
#define DTD1  "<!ELEMENT ti_cedent (ti_literal*)> \
  <!ATTLIST ti_cedent id ID #REQUIRED \
                      type CDATA #REQUIRED>  <!--antecedent, succedent, condition --> \
  <!ELEMENT ti_literal EMPTY> \
  <!ATTLIST ti_literal id ID #REQUIRED \
                       quant CDATA #REQUIRED \
                       value CDATA #REQUIRED> \
                       <!--quant: name of the quantity used in hypothese, e. g. diastolic pressure  --> \
                       <!--value: value of the quantity used in hypothese, e. g. <50;60) --> "
#define DTD2  "<!ELEMENT hyp_4ft EMPTY> \
  <!ATTLIST hyp_4ft id ID #REQUIRED \
                    db_name CDATA #REQUIRED \
                    matrix_name CDATA #REQUIRED \
                    task_name CDATA #REQUIRED \
                    a CDATA #REQUIRED \
                    b CDATA #REQUIRED \
                    c CDATA #REQUIRED \
                    d CDATA #REQUIRED \
                    conf CDATA #REQUIRED \
                    d_conf CDATA #REQUIRED \
                    e_conf CDATA #REQUIRED \
                    support CDATA #REQUIRED \
                    completeness CDATA #REQUIRED \
                    avg_diff CDATA #REQUIRED \
                    low_bnd_imp CDATA #REQUIRED \
                    up_bnd_imp CDATA #REQUIRED \
                    low_bnd_dbl_imp CDATA #REQUIRED \
                    up_bnd_dbl_imp CDATA #REQUIRED \
                    low_bnd_eq CDATA #REQUIRED \
                    up_bnd_eq CDATA #REQUIRED \
                    fisher CDATA #REQUIRED \
                    chi_sq CDATA #REQUIRED \
                    antecedent IDREF #REQUIRED \
                    succedent IDREF #REQUIRED \
                    condition IDREF #REQUIRED>   <!--antecedent,succedent,condition: references to ti_cedent --> \
]> "