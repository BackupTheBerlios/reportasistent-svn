//functions and classes for LM Metabase socket
#include "afx.h"
#include "afxtempl.h"
//4ft_hypothese
//CString fLM4fthyp(void* hSource);

struct Literal_Meta
{
	CString underlying_attribute;
	CString category_cnt;
	CString missing_type;
	CString coefficient_type;
	CString length;
	CString gace;
	CString literal_type;
	CString equivalence_class;
};

typedef CArray <Literal_Meta, Literal_Meta> TLiteral_Meta_Array;

struct Sub_bool_cedent_Meta
{
	CString				literal_cnt;
	CString				name;
	CString				length;
	TLiteral_Meta_Array	lit_list;
};

typedef CArray <Sub_bool_cedent_Meta, Sub_bool_cedent_Meta> TSub_bool_cedent_Meta_Array;

class Bool_Cedent_Meta
{
public:
	CString						id;
	CString						db_name;
    CString						matrix_name;
	CString						task_name;
	CString						task_type;
	CString						cedent_type;
	CString						sub_cedent_cnt;
	TSub_bool_cedent_Meta_Array	sub_cedents_list;
	CString						xml_convert ();
};

typedef CArray <Bool_Cedent_Meta *, Bool_Cedent_Meta *> TBool_Cedent_Meta_Array;

typedef CArray <CString, CString> TCtgrArray;

typedef CArray <CString, CString> TMissingTypeArray;

class Attribute_Meta
{
public:
	CString				id;
	CString				db_name;
    CString				matrix_name;
    CString				attr_name;
    CString				creation;
    CString				ctgr_count;
	TCtgrArray			category_list;
	TMissingTypeArray	missing_type_list;

	CString				xml_convert ();
};

typedef CArray <Attribute_Meta *, Attribute_Meta *> TAttribute_Meta_Array;

typedef CArray <CString, CString> TCatDefArray;

class Category_Meta
{
public:
	CString			id;
    CString			db_name;
    CString			matrix_name;
    CString			attr_name;
    CString			ctgr_name;
    CString			ctgr_type;
	CString			ctgr_bool_type;
    CString			ctgr_freq;
	TCatDefArray	ctgr_def;
	long			def_length;

	CString			xml_convert ();
};

typedef CArray <Category_Meta *, Category_Meta *> TCategory_Meta_Array;

struct Hyp_tiLiteral
{
	CString	id;
	CString	quant;
	CString	value;
};

typedef CArray <Hyp_tiLiteral, Hyp_tiLiteral> TLitArray;

class Hyp_4ft_Meta
{
public:
	CString		id;
    CString		db_name;
    CString		matrix_name;
    CString		task_name;
    long		a;
    long		b;
    long		c;
    long		d;
    double		conf;
    double		d_conf;
    double		e_conf;
    double		support;
    double		completeness;
    double		avg_diff;
    double		low_bnd_imp;
    double		up_bnd_imp;
    double		low_bnd_dbl_imp;
    double		up_bnd_dbl_imp;
    double		low_bnd_eq;
    double		up_bnd_eq;
    double		fisher;
    double		chi_sq;
    TLitArray	antecedent;
    TLitArray	succedent;
    TLitArray	condition;
	CString		ant_id;
	CString		suc_id;
	CString		con_id;
	bool		flag_a;
	bool		flag_s;
	bool		flag_c;

	CString		xml_convert ();
};

typedef CArray <Hyp_4ft_Meta *, Hyp_4ft_Meta *> THyp_4ft_Meta_Array;