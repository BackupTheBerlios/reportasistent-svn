//functions and classes for LM Metabase socket
#ifndef WINVER
#define WINVER 0x0400
#endif
#include "afx.h"
#include "afxtempl.h"
//4ft_hypothese
//CString fLM4fthyp(void* hSource);

struct quant_item
{
	CString name;
	CString value;
};

typedef CArray <quant_item, quant_item> Tquant_item_Array;

class Quantifier_Meta
{
public:
	CString				id;
	CString				db_name;
	CString				matrix_name;
	CString				task_name;
	CString				task_type;
	CString				name;
	CString				type;
	Tquant_item_Array	items;
	CString             xml_convert ();
};

typedef CArray <Quantifier_Meta *, Quantifier_Meta *> TQuantifier_Meta_Array;

class Task_Meta
{
public:
	CString id;
	CString db_name;
	CString matrix_name;
	CString task_name;
	CString task_type;
	CString gen_state;
	CString gen_total_time;
	CString gen_start_time;
	CString num_hyp;
	CString num_tests;
	CString xml_convert ();
};

typedef CArray <Task_Meta *, Task_Meta *> TTask_Meta_Array;

struct KL_Literal_Meta
{
	CString underlying_attribute;
	CString category_cnt;
};

typedef CArray <KL_Literal_Meta, KL_Literal_Meta> TKL_Literal_Meta_Array;

struct Sub_KL_Cedent_Meta
{
	CString					literal_cnt;
	CString					name;
	CString					length;
	TKL_Literal_Meta_Array	lit_list;
};

typedef CArray <Sub_KL_Cedent_Meta *, Sub_KL_Cedent_Meta *> TSub_KL_Cedent_Meta_Array;

class KL_Cedent_Meta
{
public:
	CString						id;
	CString						db_name;
    CString						matrix_name;
	CString						task_name;
	CString						task_type;
	CString						cedent_type;
	CString						sub_cedent_cnt;
	TSub_KL_Cedent_Meta_Array	sub_cedents_list;
	CString						xml_convert ();
};

typedef CArray <KL_Cedent_Meta *, KL_Cedent_Meta *> TKL_Cedent_Meta_Array;

struct CF_Literal_Meta
{
	CString underlying_attribute;
	CString category_cnt;
};

typedef CArray <CF_Literal_Meta, CF_Literal_Meta> TCF_Literal_Meta_Array;

struct Sub_CF_Cedent_Meta
{
	CString					literal_cnt;
	CString					name;
	CString					length;
	TCF_Literal_Meta_Array	lit_list;
};

typedef CArray <Sub_CF_Cedent_Meta *, Sub_CF_Cedent_Meta *> TSub_CF_Cedent_Meta_Array;

class CF_Cedent_Meta
{
public:
	CString						id;
	CString						db_name;
    CString						matrix_name;
	CString						task_name;
	CString						task_type;
	CString						cedent_type;
	CString						sub_cedent_cnt;
	TSub_CF_Cedent_Meta_Array	sub_cedents_list;
	CString						xml_convert ();
};

typedef CArray <CF_Cedent_Meta *, CF_Cedent_Meta *> TCF_Cedent_Meta_Array;

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

struct Sub_Bool_Cedent_Meta
{
	CString				literal_cnt;
	CString				name;
	CString				length;
	TLiteral_Meta_Array	lit_list;
};

typedef CArray <Sub_Bool_Cedent_Meta *, Sub_Bool_Cedent_Meta *> TSub_Bool_Cedent_Meta_Array;

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
	TSub_Bool_Cedent_Meta_Array	sub_cedents_list;
	CString						xml_convert ();
};

typedef CArray <Bool_Cedent_Meta *, Bool_Cedent_Meta *> TBool_Cedent_Meta_Array;

struct TCtgr
{
	CString name;
	CString freq;
};

typedef CArray <TCtgr, TCtgr> TCtgrArray;

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