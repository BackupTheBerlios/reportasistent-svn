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

class Bool_Cedent_Meta
{
public:
	CString						id;
	CString						db_name;
    CString						matrix_name;
	CString						task_name;
	CString						task_type;
	CString						cedent_type;
	CString						literal_cnt;
	CString						name;
	CString						length;
	TLiteral_Meta_Array			lit_list;
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
//	bool		flag_a;
//	bool		flag_s;
//	bool		flag_c;

	CString		xml_convert ();
};

typedef CArray <Hyp_4ft_Meta *, Hyp_4ft_Meta *> THyp_4ft_Meta_Array;

typedef CArray <CString, CString> CString_Array;

typedef CArray <int, int> Cint_Array;

class Hyp_CF_Meta
{
public:
	CString			id;
    CString			db_name;
    CString			matrix_name;
    CString			task_name;

    CString			sum;
    CString			min;
    CString			max;
    CString			v;
    CString			nom_var;
    CString			dor_var;

	CString			avg_a;
    CString			avg_g;
    CString			var;
    CString			st_dev;
    CString			skew;
    CString			asym;
	
	CString			quant;
	CString_Array	attributes;
    TLitArray		condition;

	CString			a_id;
    CString			c_id;

	Cint_Array		frequencies;

	CString			xml_convert ();
	int				get_sum ();
	CString			get_min ();
	int				get_max ();
//	CString			get_v ();
	CString			get_nom_var ();
	CString			get_dor_var ();
private:
	double			GetVariationRatio ();
	
};

typedef CArray <Hyp_CF_Meta *, Hyp_CF_Meta *> THyp_CF_Meta_Array;

class Hyp_SD4ft_Meta
{
public:
	CString		id;
    CString		db_name;
    CString		matrix_name;
    CString		task_name;
    CString		a;
    CString		b;
    CString		c;
    CString		d;
	CString		e;
    CString		f;
    CString		g;
    CString		h;

	CString conf1;
    CString d_conf1;
    CString e_conf1;
    CString support1;
    CString completeness1;
    CString avg_diff1;
    CString low_bnd_imp1;
    CString up_bnd_imp1;
    CString low_bnd_dbl_imp1;
    CString up_bnd_dbl_imp1;
    CString low_bnd_eq1;
    CString up_bnd_eq1;
    CString fisher1;
    CString chi_sq1;

	CString conf2;
    CString d_conf2;
    CString e_conf2;
    CString support2;
    CString completeness2;
    CString avg_diff2;
    CString low_bnd_imp2;
    CString up_bnd_imp2;
    CString low_bnd_dbl_imp2;
    CString up_bnd_dbl_imp2;
    CString low_bnd_eq2;
    CString up_bnd_eq2;
    CString fisher2;
    CString chi_sq2;
	
	CString dr_sum;
    CString df_conf;
    CString df_dfui;
    CString df_fue;
    CString df_avg;
    
    TLitArray	antecedent;
    TLitArray	succedent;
    TLitArray	condition;
	TLitArray	set1;
    TLitArray	set2;

	CString		ant_id;
	CString		suc_id;
	CString		con_id;
	CString		set1_id;
	CString		set2_id;

	CString		xml_convert ();
};

typedef CArray <Hyp_SD4ft_Meta *, Hyp_SD4ft_Meta *> THyp_SD4ft_Meta_Array;

class Hyp_SDCF_Meta
{
public:
	CString			id;
    CString			db_name;
    CString			matrix_name;
    CString			task_name;

    CString			sum1;
    CString			min1;
    CString			max1;
    CString			v1;
    CString			nom_var1;
    CString			dor_var1;
	CString			avg_a1;
    CString			avg_g1;
    CString			var1;
    CString			st_dev1;
    CString			skew1;
    CString			asym1;

	CString			sum2;
    CString			min2;
    CString			max2;
    CString			v2;
    CString			nom_var2;
    CString			dor_var2;
	CString			avg_a2;
    CString			avg_g2;
    CString			var2;
    CString			st_dev2;
    CString			skew2;
    CString			asym2;

	
    CString         da_sum;
    CString         da_min;
    CString         da_max;
    CString         dr_sum;
    CString         dr_min;
    CString         dr_max;
	
	CString			quant;
	CString_Array	attributes;
    TLitArray		condition;
	TLitArray		set1;
	TLitArray		set2;

	CString			a_id;
    CString			c_id;
	CString			s1_id;
    CString			s2_id;

	Cint_Array		frequencies1;
	Cint_Array		frequencies2;

	CString			xml_convert ();
	int				get_sum1 ();
	CString			get_min1 ();
	int				get_max1 ();
	CString			get_nom_var1 ();
	CString			get_dor_var1 ();
	int				get_sum2 ();
	CString			get_min2 ();
	int				get_max2 ();
	CString			get_nom_var2 ();
	CString			get_dor_var2 ();
	CString			get_da_sum ();
	CString			get_da_min ();
	CString			get_da_max ();
	CString			get_dr_sum ();
	CString			get_dr_min ();
	CString			get_dr_max ();
private:
	double			GetVariationRatio1 ();
	double			GetVariationRatio2 ();
};

typedef CArray <Hyp_SDCF_Meta *, Hyp_SDCF_Meta *> THyp_SDCF_Meta_Array;

typedef CArray <Cint_Array *, Cint_Array *> Tint_Tab;

class Hyp_KL_Meta
{
public:
	CString			id;
    CString			db_name;
    CString			matrix_name;
    CString			task_name;

    CString			sum;
    CString			min;
    CString			max;
    CString			chi_sq;
    CString			fnc_s;
    CString			fnc_r;
    CString			h_c;
    CString			h_r;
    CString			h_c_r;
    CString			mi;
    CString			aic;
    CString			kend;

	CString			quant_row;
	CString			quant_col;
	
	CString_Array	row_attributes;
	CString_Array	column_attributes;
    TLitArray		condition;
	Tint_Tab		table;

	CString			row_id;
	CString			col_id;
    CString			c_id;

	CString			xml_convert ();
	int				get_sum ();
	CString			get_min ();
	int				get_max ();
};

typedef CArray <Hyp_KL_Meta *, Hyp_KL_Meta *> THyp_KL_Meta_Array;

class Hyp_SDKL_Meta
{
public:
	CString			id;
    CString			db_name;
    CString			matrix_name;
    CString			task_name;

    CString			sum1;
    CString			min1;
    CString			max1;
    CString			chi_sq1;
    CString			fnc_s1;
    CString			fnc_r1;
    CString			h_c1;
    CString			h_r1;
    CString			h_c_r1;
    CString			mi1;
    CString			aic1;
    CString			kend1;

	CString			sum2;
    CString			min2;
    CString			max2;
    CString			chi_sq2;
    CString			fnc_s2;
    CString			fnc_r2;
    CString			h_c2;
    CString			h_r2;
    CString			h_c_r2;
    CString			mi2;
    CString			aic2;
    CString			kend2;

    CString			da_sum;
    CString			da_min;
    CString			da_max;
    CString			dr_sum;
    CString			dr_min;
    CString			dr_max;

	CString			quant_row;
	CString			quant_col;
	
	CString_Array	row_attributes;
	CString_Array	column_attributes;
    TLitArray		condition;
	TLitArray		set1;
	TLitArray		set2;
	Tint_Tab		table1;
	Tint_Tab		table2;

	CString			row_id;
	CString			col_id;
    CString			c_id;
	CString			s1_id;
	CString			s2_id;

	CString			xml_convert ();
};

typedef CArray <Hyp_SDKL_Meta *, Hyp_SDKL_Meta *> THyp_SDKL_Meta_Array;