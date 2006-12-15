//functions and classes for LM Metabase socket
#ifndef WINVER
#define WINVER 0x0400
#endif
#include "afx.h"
#include "afxtempl.h"
//4ft_hypothese
//CString fLM4fthyp(void* hSource);

/**
 * This structure defines the LM quantifier parameters.
 *
 * @author Martin Chrz
 */
struct quant_item
{
	CString name;/// quantifier parameter name
	CString value;/// quantifier parameter value
};

/**
 * The array of quantifier parameters.
 */
typedef CArray <quant_item, quant_item> Tquant_item_Array;

/**
 * Defines the basic LM quantifier.
 *
 * @author Martin Chrz
 */
class Quantifier_Meta
{
public:
	CString				id;/// item ID
	CString				db_name;/// database name
	CString				matrix_name;/// matrix name
	CString				task_name;/// task name
	CString				task_type;/// type of the task
	CString				name;/// name of the quantifier
	CString				type;/// type of the quantifier
	Tquant_item_Array	items;/// parameters of the quantifier
	CString             xml_convert ();/// Creates the XML representation of the basic quantifier.
};

/**
 * The array of the basic quantifiers.
 */
typedef CArray <Quantifier_Meta *, Quantifier_Meta *> TQuantifier_Meta_Array;

/**
 * Defines the LM task.
 *
 * @author Martin Chrz
 */
class Task_Meta
{
public:
	CString id;/// item id
	CString db_name;/// database name
	CString matrix_name;/// matrix name
	CString task_name;/// task name
	CString task_type;/// type of the task
	CString gen_state;/// task status (generation interrupted, hypothesis generated, ...)
	CString gen_total_time;/// total time of the task evaluation
	CString gen_start_time;/// start time of the generation
	CString num_hyp;/// number of hypothesis generated
	CString num_tests;/// number of verifications
	CString xml_convert ();/// Creates the XML representation of the LM task
};

/**
 * The array of the LM tasks.
 */
typedef CArray <Task_Meta *, Task_Meta *> TTask_Meta_Array;

/**
 * The structure defines the KL literal.
 *
 * @author Martin Chrz
 */
struct KL_Literal_Meta
{
	CString underlying_attribute;/// underlying attribute of the literal
	CString category_cnt;/// number of categories of the underlying attribute
};

/**
 * The array of KL literals.
 */
typedef CArray <KL_Literal_Meta, KL_Literal_Meta> TKL_Literal_Meta_Array;

/**
 * Defines the KL subcedent.
 *
 * @author Martin Chrz
 */
struct Sub_KL_Cedent_Meta
{
	CString					literal_cnt;/// number of literals
	CString					name;/// subcedent name
	CString					length;/// restriction for sub cedent length
	TKL_Literal_Meta_Array	lit_list;/// list of the KL literals
};

/**
 * The array of KL subcedents.
 */
typedef CArray <Sub_KL_Cedent_Meta *, Sub_KL_Cedent_Meta *> TSub_KL_Cedent_Meta_Array;

/**
 * Defines the KL cedent.
 *
 * @author Martin Chrz
 */
class KL_Cedent_Meta
{
public:
	CString						id;/// item id
	CString						db_name;/// database name
    CString						matrix_name;/// matrix name
	CString						task_name;/// task name
	CString						task_type;/// type of the task
	CString						cedent_type;/// type of the cedent
	CString						sub_cedent_cnt;/// number of subcedents
	TSub_KL_Cedent_Meta_Array	sub_cedents_list;/// the list of subcedents
	CString						xml_convert ();/// Creates the XML representation of the KL cedent.
};

/**
 * The array of KL cedents.
 */
typedef CArray <KL_Cedent_Meta *, KL_Cedent_Meta *> TKL_Cedent_Meta_Array;

/**
 * Defines the CF literal.
 *
 * @author Martin Chrz
 */
struct CF_Literal_Meta
{
	CString underlying_attribute;/// the underlying attribute of the CF literal
	CString category_cnt;/// number of categories of the underlying attribute
};

/**
 * The array of CF literals.
 */
typedef CArray <CF_Literal_Meta, CF_Literal_Meta> TCF_Literal_Meta_Array;

/**
 * Defines the CF subcedent.
 *
 * @author Martin Chrz
 */
struct Sub_CF_Cedent_Meta
{
	CString					literal_cnt;/// number of CF literals
	CString					name;/// the name of the subcedent
	CString					length;/// the restriction for the subcedent length
	TCF_Literal_Meta_Array	lit_list;/// the list of the CF literals
};

/**
 * The array of CF subcedents.
 */
typedef CArray <Sub_CF_Cedent_Meta *, Sub_CF_Cedent_Meta *> TSub_CF_Cedent_Meta_Array;

/**
 * Defines the CF cedent.
 *
 * @author Martin Chrz
 */
class CF_Cedent_Meta
{
public:
	CString						id;/// item id
	CString						db_name;/// database name
    CString						matrix_name;/// matrix name
	CString						task_name;/// task name
	CString						task_type;/// the type of the task
	CString						cedent_type;/// the type of the cedents
	CString						sub_cedent_cnt;/// number of subcedents
	TSub_CF_Cedent_Meta_Array	sub_cedents_list;/// the list of subcedents
	CString						xml_convert ();/// Creates the XML representation of the CF cedent.
};

/**
 * The array of CF cedents.
 */
typedef CArray <CF_Cedent_Meta *, CF_Cedent_Meta *> TCF_Cedent_Meta_Array;

/**
 * Defines the literal.
 *
 * @author Martin Chrz
 */
struct Literal_Meta
{
	CString underlying_attribute;/// the underlying attribute of the literal
	CString category_cnt;/// number of categories of the underlying attribute
	CString missing_type;/// marks, if some of the categories are the values for missing information
	CString coefficient_type;/// the type of the literal (subset, interval, ...)
	CString length;/// restriction for the literal length
	CString gace;/// the gace of the literal (positive x negative)
	CString literal_type;/// the type of the literal (basic x remaining)
	CString equivalence_class;/// equivalence class of the literal
};

/**
 * The array of literals.
 */
typedef CArray <Literal_Meta, Literal_Meta> TLiteral_Meta_Array;

/**
 * Defines the bool subcedent.
 *
 * @author Martin Chrz
 */
class Bool_Cedent_Meta
{
public:
	CString						id;/// items id
	CString						db_name;/// database name
    CString						matrix_name;/// matrix name
	CString						task_name;/// task name
	CString						task_type;/// the type of the task
	CString						cedent_type;/// the type of the cedent
	CString						literal_cnt;/// number of literals
	CString						name;/// the name of the cedent
	CString						length;/// restriction for the cedent length
	TLiteral_Meta_Array			lit_list;/// the list of the literals
	CString						xml_convert ();/// Creates the XML representation of the bool cedent.
};

/**
 * The array of bool subcedents.
 */
typedef CArray <Bool_Cedent_Meta *, Bool_Cedent_Meta *> TBool_Cedent_Meta_Array;

/**
 * Defines the category of some attribute.
 *
 * @author Martin Chrz
 */
struct TCtgr
{
	CString name;/// category name
	CString freq;/// category frequency
};

/**
 * The array of attribute categories
 */
typedef CArray <TCtgr, TCtgr> TCtgrArray;

/**
 * The array of categories for missing type.
 */
typedef CArray <CString, CString> TMissingTypeArray;

/**
 * Defines the attribute.
 *
 * @author Martin Chrz
 */
class Attribute_Meta
{
public:
	CString				id;/// item id
	CString				db_name;/// database name
    CString				matrix_name;/// matrix name
    CString				attr_name;/// attribute name
    CString				creation;/// type of the creation of the attribute
    CString				ctgr_count;/// number of categories of the attribute
	TCtgrArray			category_list;/// the list of categories of the attribute
	TMissingTypeArray	missing_type_list;/// the list of categories representing the missing type of the attribute

	CString				xml_convert ();/// Creates the XML representation of the attribute.
};

/**
 * The array of attributes
 */
typedef CArray <Attribute_Meta *, Attribute_Meta *> TAttribute_Meta_Array;

/**
 * The array of the categories definition.
 */
typedef CArray <CString, CString> TCatDefArray;

/**
 * Defines the category.
 *
 * @author Martin Chrz
 */
class Category_Meta
{
public:
	CString			id;/// item id
    CString			db_name;/// database name
    CString			matrix_name;/// matrix name
    CString			attr_name;/// attribute name
    CString			ctgr_name;/// category name
    CString			ctgr_type;/// type of the category (enumeration, interval, ...)
	CString			ctgr_bool_type;/// indicates, whether the category is boolean or not
    CString			ctgr_freq;/// the frequency of the category
	TCatDefArray	ctgr_def;/// the definition of the category
	long			def_length;/// the number of underlying values defining the category

	CString			xml_convert ();/// Creates the XML representation of the category.
};

/**
 * The array of categories.
 */
typedef CArray <Category_Meta *, Category_Meta *> TCategory_Meta_Array;

/**
 * Defines the literal interpretation in the hypothese.
 *
 * @author Martin Chrz
 */
struct Hyp_tiLiteral
{
	CString	id;/// item id
	CString	quant;/// attribute name
	CString	value;/// attribute value
	CString	coef_type;/// coefficient type
};

/**
 * The array of literals interpretations in the hypothese
 */
typedef CArray <Hyp_tiLiteral, Hyp_tiLiteral> TLitArray;

/**
 * Defines the 4ft hypothese.
 *
 * @author Martin Chrz
 */
class Hyp_4ft_Meta
{
public:
	CString		id;/// item id
    CString		db_name;/// database name
    CString		matrix_name;/// matrix name
    CString		task_name;/// task name
    long		a;/// a - frequency in the four fold table
    long		b;/// b - frequency in the four fold table
    long		c;/// c - frequency in the four fold table
    long		d;/// d - frequency in the four fold table
    double		conf;/// 4ft quantifier
    double		d_conf;/// 4ft quantifier
    double		e_conf;/// 4ft quantifier
    double		support;/// 4ft quantifier
    double		completeness;/// 4ft quantifier
    double		avg_diff;/// 4ft quantifier
    CString		low_bnd_imp;/// 4ft quantifier
    CString		up_bnd_imp;/// 4ft quantifier
    CString		low_bnd_dbl_imp;/// 4ft quantifier
    CString		up_bnd_dbl_imp;/// 4ft quantifier
    CString		low_bnd_eq;/// 4ft quantifier
    CString		up_bnd_eq;/// 4ft quantifier
    CString		fisher;/// 4ft quantifier
    double		chi_sq;/// 4ft quantifier
    TLitArray	antecedent;/// antecedent representation
    TLitArray	succedent;/// succedent representation
    TLitArray	condition;/// condition representation
	CString		ant_id;/// antecedent id
	CString		suc_id;/// succedent id
	CString		con_id;/// condition id
	CString		ar2nl_sentences;/// the formulation of the hypothese in the natural language
//	bool		flag_a;
//	bool		flag_s;
//	bool		flag_c;

	CString		xml_convert (bool ar2nl);/// Creates the XML representation of the 4ft hypothese.
	CString		get_fisher ();/// computes the 4ft quantifier
	double		get_chi_sq ();/// computes the 4ft quantifier
	CString		get_low_bnd_imp ();/// computes the 4ft quantifier
	CString		get_up_bnd_imp ();/// computes the 4ft quantifier
	CString		get_low_bnd_dbl_imp ();/// computes the 4ft quantifier
	CString		get_up_bnd_dbl_imp ();/// computes the 4ft quantifier
	CString		get_low_bnd_eq ();/// computes the 4ft quantifier
	CString		get_up_bnd_eq ();/// computes the 4ft quantifier
};

/**
 * The array of 4ft hypothesis.
 */
typedef CArray <Hyp_4ft_Meta *, Hyp_4ft_Meta *> THyp_4ft_Meta_Array;

/**
 * The array of strings.
 */
typedef CArray <CString, CString> CString_Array;

/**
 * The array of integers.
 */
typedef CArray <int, int> Cint_Array;

/**
 * Defines the CF hypothese.
 *
 * @author Martin Chrz
 */
class Hyp_CF_Meta
{
public:
	CString			id;/// item id
    CString			db_name;/// database name
    CString			matrix_name;/// matrix name
    CString			task_name;/// task name

    CString			sum;/// CF quantifier
    CString			min;/// CF quantifier
    CString			max;/// CF quantifier
    CString			v;/// CF quantifier
    CString			nom_var;/// CF quantifier
    CString			dor_var;/// CF quantifier

	CString			avg_a;/// CF quantifier
    CString			avg_g;/// CF quantifier
    CString			var;/// CF quantifier
    CString			st_dev;/// CF quantifier
    CString			skew;/// CF quantifier
    CString			asym;/// CF quantifier
	
	CString			quant;/// attribute name
	CString_Array	attributes;/// categories of the attribute
    TLitArray		condition;/// list of literals interpretation in the condition

	CString			a_id;/// attributes id
    CString			c_id;/// condition id

	Cint_Array		frequencies;/// frequenies of the categories in "attributes"

	CString			xml_convert ();///Creates the XML representation of the CF hypothese.
	int				get_sum ();/// computes the CF quantifier
	CString			get_min ();/// computes the CF quantifier
	int				get_max ();/// computes the CF quantifier
//	CString			get_v ();
	CString			get_nom_var ();/// computes the CF quantifier
	CString			get_dor_var ();/// computes the CF quantifier
private:
	double			GetVariationRatio ();/// computes the temporary value for the CF quantifiers computation
	
};

/**
 * The array of CF hypothesis.
 */
typedef CArray <Hyp_CF_Meta *, Hyp_CF_Meta *> THyp_CF_Meta_Array;

/**
 * Defines the SD4FT hypothese.
 *
 * @author Martin Chrz
 */
class Hyp_SD4ft_Meta
{
public:
	CString		id;/// item id
    CString		db_name;/// database name
    CString		matrix_name;/// matrix name
    CString		task_name;/// task name
    CString		a;/// a - frequency in the four fold table (first set)
    CString		b;/// b - frequency in the four fold table (first set)
    CString		c;/// c - frequency in the four fold table (first set)
    CString		d;/// d - frequency in the four fold table (first set)
	CString		e;/// a - frequency in the four fold table (second set)
    CString		f;/// b - frequency in the four fold table (second set)
    CString		g;/// c - frequency in the four fold table (second set)
    CString		h;/// d - frequency in the four fold table (second set)

	CString conf1;/// sd4ft quantifier
    CString d_conf1;/// sd4ft quantifier
    CString e_conf1;/// sd4ft quantifier
    CString support1;/// sd4ft quantifier
    CString completeness1;/// sd4ft quantifier
    CString avg_diff1;/// sd4ft quantifier
    CString low_bnd_imp1;/// sd4ft quantifier
    CString up_bnd_imp1;/// sd4ft quantifier
    CString low_bnd_dbl_imp1;/// sd4ft quantifier
    CString up_bnd_dbl_imp1;/// sd4ft quantifier
    CString low_bnd_eq1;/// sd4ft quantifier
    CString up_bnd_eq1;/// sd4ft quantifier
    CString fisher1;/// sd4ft quantifier
    CString chi_sq1;/// sd4ft quantifier

	CString conf2;/// sd4ft quantifier
    CString d_conf2;/// sd4ft quantifier
    CString e_conf2;/// sd4ft quantifier
    CString support2;/// sd4ft quantifier
    CString completeness2;/// sd4ft quantifier
    CString avg_diff2;/// sd4ft quantifier
    CString low_bnd_imp2;/// sd4ft quantifier
    CString up_bnd_imp2;/// sd4ft quantifier
    CString low_bnd_dbl_imp2;/// sd4ft quantifier
    CString up_bnd_dbl_imp2;/// sd4ft quantifier
    CString low_bnd_eq2;/// sd4ft quantifier
    CString up_bnd_eq2;/// sd4ft quantifier
    CString fisher2;/// sd4ft quantifier
    CString chi_sq2;/// sd4ft quantifier
	
	CString dr_sum;/// sd4ft quantifier
    CString df_conf;/// sd4ft quantifier
    CString df_dfui;/// sd4ft quantifier
    CString df_fue;/// sd4ft quantifier
    CString df_avg;/// sd4ft quantifier
    
    TLitArray	antecedent;/// antecedent representation
    TLitArray	succedent;/// succedent representation
    TLitArray	condition;/// condition representation
	TLitArray	set1;/// first set representation
    TLitArray	set2;/// second set representation

	CString		ant_id;/// antecedent id
	CString		suc_id;/// succedent id
	CString		con_id;/// condition id
	CString		set1_id;/// first set id
	CString		set2_id;/// second set id

	CString		xml_convert ();/// Creates the XML representation of SD4FT hypothese
	double		get_conf (long _a, long _b);/// computes the SD4FT quantifier
	double		get_d_conf (long _a, long _b, long _c);/// computes the SD4FT quantifier
	double		get_e_conf (long _a, long _b, long _c, long _d);/// computes the SD4FT quantifier
	double		get_support (long _a, long _b, long _c, long _d);/// computes the SD4FT quantifier
	double		get_completeness (long _a, long _c);/// computes the SD4FT quantifier
	double		get_avg_diff (long _a, long _b, long _c, long _d);/// computes the SD4FT quantifier
	CString		get_low_bnd_imp (long _a, long _b);/// computes the SD4FT quantifier
	CString		get_up_bnd_imp (long _a, long _b);/// computes the SD4FT quantifier
	CString		get_low_bnd_dbl_imp (long _a, long _b, long _c);/// computes the SD4FT quantifier
	CString		get_up_bnd_dbl_imp (long _a, long _b, long _c);/// computes the SD4FT quantifier
	CString		get_low_bnd_eq (long _a, long _b, long _c, long _d);/// computes the SD4FT quantifier
	CString		get_up_bnd_eq (long _a, long _b, long _c, long _d);/// computes the SD4FT quantifier
	CString		get_fisher (long _a, long _b, long _c, long _d);/// computes the SD4FT quantifier
	double		get_chi_sq (long _a, long _b, long _c, long _d);/// computes the SD4FT quantifier
	double		get_dr_sum (long _a, long _b, long _c, long _d,
							long _e, long _f, long _g, long _h);/// computes the SD4FT quantifier
};

/**
 * The array of SD4FT hypothesis.
 */
typedef CArray <Hyp_SD4ft_Meta *, Hyp_SD4ft_Meta *> THyp_SD4ft_Meta_Array;

/**
 * Defines the SDCF hypothese.
 *
 * @author Martin Chrz
 */
class Hyp_SDCF_Meta
{
public:
	CString			id;/// item id
    CString			db_name;/// database name
    CString			matrix_name;/// matrix name
    CString			task_name;/// task name

    CString			sum1;/// SDCF quantifier
    CString			min1;/// SDCF quantifier
    CString			max1;/// SDCF quantifier
    CString			v1;/// SDCF quantifier
    CString			nom_var1;/// SDCF quantifier
    CString			dor_var1;/// SDCF quantifier
	CString			avg_a1;/// SDCF quantifier
    CString			avg_g1;/// SDCF quantifier
    CString			var1;/// SDCF quantifier
    CString			st_dev1;/// SDCF quantifier
    CString			skew1;/// SDCF quantifier
    CString			asym1;/// SDCF quantifier

	CString			sum2;/// SDCF quantifier
    CString			min2;/// SDCF quantifier
    CString			max2;/// SDCF quantifier
    CString			v2;/// SDCF quantifier
    CString			nom_var2;/// SDCF quantifier
    CString			dor_var2;/// SDCF quantifier
	CString			avg_a2;/// SDCF quantifier
    CString			avg_g2;/// SDCF quantifier
    CString			var2;/// SDCF quantifier
    CString			st_dev2;/// SDCF quantifier
    CString			skew2;/// SDCF quantifier
    CString			asym2;/// SDCF quantifier

	
    CString         da_sum;/// SDCF quantifier
    CString         da_min;/// SDCF quantifier
    CString         da_max;/// SDCF quantifier
    CString         dr_sum;/// SDCF quantifier
    CString         dr_min;/// SDCF quantifier
    CString         dr_max;/// SDCF quantifier
	
	CString			quant;/// attribute name
	CString_Array	attributes;/// list of categories of the attribute
    TLitArray		condition;/// list of literals interpretation in the condition
	TLitArray		set1;/// list of literals interpretation in the first set
	TLitArray		set2;/// list of literals interpretation in the second set

	CString			a_id;/// antecedent id
    CString			c_id;/// succedent id
	CString			s1_id;/// first set id
    CString			s2_id;/// second set id

	Cint_Array		frequencies1;/// frequenies of the categories in "attributes" on first set
	Cint_Array		frequencies2;/// frequenies of the categories in "attributes" on second set

	CString			xml_convert ();/// Creates the XML representation of SDCF hypothese.
	int				get_sum1 ();/// computes the SDCF quantifier
	CString			get_min1 ();/// computes the SDCF quantifier
	int				get_max1 ();/// computes the SDCF quantifier
	CString			get_nom_var1 ();/// computes the SDCF quantifier
	CString			get_dor_var1 ();/// computes the SDCF quantifier
	int				get_sum2 ();/// computes the SDCF quantifier
	CString			get_min2 ();/// computes the SDCF quantifier
	int				get_max2 ();/// computes the SDCF quantifier
	CString			get_nom_var2 ();/// computes the SDCF quantifier
	CString			get_dor_var2 ();/// computes the SDCF quantifier
	CString			get_da_sum ();/// computes the SDCF quantifier
	CString			get_da_min ();/// computes the SDCF quantifier
	CString			get_da_max ();/// computes the SDCF quantifier
	CString			get_dr_sum ();/// computes the SDCF quantifier
	CString			get_dr_min ();/// computes the SDCF quantifier
	CString			get_dr_max ();/// computes the SDCF quantifier
private:
	double			GetVariationRatio1 ();/// computes the temporary value for the SDCF quantifiers computation
	double			GetVariationRatio2 ();/// computes the temporary value for the SDCF quantifiers computation
};

/**
 * The array of SDCF hypothesis.
 */
typedef CArray <Hyp_SDCF_Meta *, Hyp_SDCF_Meta *> THyp_SDCF_Meta_Array;

/**
 * The table of integers.
 */
typedef CArray <Cint_Array *, Cint_Array *> Tint_Tab;

/**
 * Defines the KL hypothese.
 *
 * @author Martin Chrz
 */
class Hyp_KL_Meta
{
public:
	CString			id;/// item id
    CString			db_name;/// database name
    CString			matrix_name;/// matrix name
    CString			task_name;/// task name

    CString			sum;/// KL quantifier
    CString			min;/// KL quantifier
    CString			max;/// KL quantifier
    CString			chi_sq;/// KL quantifier
    CString			fnc_s;/// KL quantifier
    CString			fnc_r;/// KL quantifier
    CString			h_c;/// KL quantifier
    CString			h_r;/// KL quantifier
    CString			h_c_r;/// KL quantifier
    CString			mi;/// KL quantifier
    CString			aic;/// KL quantifier
    CString			kend;/// KL quantifier

	CString			quant_row;/// row attribute name
	CString			quant_col;/// column attribute name
	
	CString_Array	row_attributes;/// categories of row attribute
	CString_Array	column_attributes;/// categories of column attribute
    TLitArray		condition;/// list of literals interpretation in the condition
	Tint_Tab		table;/// frequencies in the contingency table

	CString			row_id;/// row attributes id
	CString			col_id;/// column attributes id
    CString			c_id;/// condition id

	CString			xml_convert ();/// Creates the XML representation of the KL hypothese.
	int				get_sum ();/// computation of KL quantifier
	CString			get_min ();/// computtion of KL quantifier
	int				get_max ();/// computation of KL quantifier
	CString			get_chi_sq ();/// computation of KL quantifier
	CString			get_fnc_s ();/// computation of KL quantifier
	CString			get_fnc_r ();/// computation of KL quantifier
	double			get_h_c ();/// computation of KL quantifier
	double			get_h_r ();/// computation of KL quantifier
	double			get_h_c_r ();/// computation of KL quantifier
	CString			get_mi ();/// computation of KL quantifier
	CString			get_aic ();/// computation of KL quantifier
	CString			get_kend ();/// computation of KL quantifier
private:
	int				get_row_sum (Tint_Tab * tab, int row);/// computes the temporary value for the KL quantifiers computation
	int				get_col_sum (Tint_Tab * tab, int col);/// computes the temporary value for the KL quantifiers computation
};

/**
 * The array of KL hypothesis.
 */
typedef CArray <Hyp_KL_Meta *, Hyp_KL_Meta *> THyp_KL_Meta_Array;

/**
 * Definition of SDKL hypothese.
 *
 * @author Martin Chrz
 */
class Hyp_SDKL_Meta
{
public:
	CString			id;/// item id
    CString			db_name;/// database name
    CString			matrix_name;///matrix name
    CString			task_name;/// task name

    CString			sum1;/// SDKL quantifier
    CString			min1;/// SDKL quantifier
    CString			max1;/// SDKL quantifier
    CString			chi_sq1;/// SDKL quantifier
    CString			fnc_s1;/// SDKL quantifier
    CString			fnc_r1;/// SDKL quantifier
    CString			h_c1;/// SDKL quantifier
    CString			h_r1;/// SDKL quantifier
    CString			h_c_r1;/// SDKL quantifier
    CString			mi1;/// SDKL quantifier
    CString			aic1;/// SDKL quantifier
    CString			kend1;/// SDKL quantifier

	CString			sum2;/// SDKL quantifier
    CString			min2;/// SDKL quantifier
    CString			max2;/// SDKL quantifier
    CString			chi_sq2;/// SDKL quantifier
    CString			fnc_s2;/// SDKL quantifier
    CString			fnc_r2;/// SDKL quantifier
    CString			h_c2;/// SDKL quantifier
    CString			h_r2;/// SDKL quantifier
    CString			h_c_r2;/// SDKL quantifier
    CString			mi2;/// SDKL quantifier
    CString			aic2;/// SDKL quantifier
    CString			kend2;/// SDKL quantifier

    CString			da_sum;/// SDKL quantifier
    CString			da_min;/// SDKL quantifier
    CString			da_max;/// SDKL quantifier
    CString			dr_sum;/// SDKL quantifier
    CString			dr_min;/// SDKL quantifier
    CString			dr_max;/// SDKL quantifier

	CString			quant_row;/// row attribute name
	CString			quant_col;/// column attribute name
	
	CString_Array	row_attributes;/// categories of row attributes
	CString_Array	column_attributes;/// categories of column attributes
    TLitArray		condition;/// list of literals interpretation in the condition
	TLitArray		set1;/// list of literals interpretation in the first set
	TLitArray		set2;/// list of literals interpretation in the second set
	Tint_Tab		table1;/// frequencies in the first contingency table
	Tint_Tab		table2;/// frequencies in the second contingency table

	CString			row_id;/// row attributes id
	CString			col_id;/// column attributes id
    CString			c_id;/// condition id
	CString			s1_id;/// first set id
	CString			s2_id;/// second set id

	CString			xml_convert ();/// Creates the XML representation of SDKL hypothese.
	
	int				get_sum1 ();/// computes SDKL quantifier
	CString			get_min1 ();/// computes SDKL quantifier
	int				get_max1 ();/// computes SDKL quantifier
	CString			get_chi_sq1 ();/// computes SDKL quantifier
	CString			get_fnc_s1 ();/// computes SDKL quantifier
	CString			get_fnc_r1 ();/// computes SDKL quantifier
	double			get_h_c1 ();/// computes SDKL quantifier
	double			get_h_r1 ();/// computes SDKL quantifier
	double			get_h_c_r1 ();/// computes SDKL quantifier
	CString			get_mi1 ();/// computes SDKL quantifier
	CString			get_aic1 ();/// computes SDKL quantifier
	CString			get_kend1 ();/// computes SDKL quantifier

	int				get_sum2 ();/// computes SDKL quantifier
	CString			get_min2 ();/// computes SDKL quantifier
	int				get_max2 ();/// computes SDKL quantifier
	CString			get_chi_sq2 ();/// computes SDKL quantifier
	CString			get_fnc_s2 ();/// computes SDKL quantifier
	CString			get_fnc_r2 ();/// computes SDKL quantifier
	double			get_h_c2 ();/// computes SDKL quantifier
	double			get_h_r2 ();/// computes SDKL quantifier
	double			get_h_c_r2 ();/// computes SDKL quantifier
	CString			get_mi2 ();/// computes SDKL quantifier
	CString			get_aic2 ();/// computes SDKL quantifier
	CString			get_kend2 ();/// computes SDKL quantifier

	CString			get_da_sum ();/// computes SDKL quantifier
    CString			get_da_min ();/// computes SDKL quantifier
    CString			get_da_max ();/// computes SDKL quantifier
    CString			get_dr_sum ();/// computes SDKL quantifier
    CString			get_dr_min ();/// computes SDKL quantifier
    CString			get_dr_max ();/// computes SDKL quantifier
private:
	int				get_row_sum (Tint_Tab * tab, int row);/// computes the temporary value for the SDKL quantifiers computation
	int				get_col_sum (Tint_Tab * tab, int col);/// computes the temporary value for the SDKL quantifiers computation
};

/**
 * The array of SDKL hypothesis.
 */
typedef CArray <Hyp_SDKL_Meta *, Hyp_SDKL_Meta *> THyp_SDKL_Meta_Array;

/**
 * Defines the data matrix.
 *
 * @author Martin Chrz
 */
class Data_Matrix_Meta
{
public:
	CString id;/// item id
	CString db_name;/// database name
	CString matrix_name;/// matrix name
	long	record_count;/// number of rows in the matrix
	long	integer_count;/// number of integer rows
	long	float_count;/// number of float rows
	long	string_count;/// number of string rows
	long	boolean_count;/// number of boolean rows
	long	date_count;/// number of date rows

	CString	xml_convert ();/// Creates the XML representation of data matrix.
};

/**
 * The array of data matrices.
 */
typedef CArray <Data_Matrix_Meta *, Data_Matrix_Meta *> TData_Matrix_Meta_Array;

/**
 * Defines the column.
 *
 * @author Martin Chrz
 */
class Column_Meta
{
public:
	CString id;/// item id
	CString db_name;/// database name
	CString matrix_name;/// matrix name
    CString column_name;/// column name
    CString value_type;/// data type of the column
    CString primary_key_position;/// column's position in primary key
    CString min;/// minimal value in the column
    CString max;/// maximal value in the column
    CString avg;/// average value in the column

	CString	xml_convert ();/// Creates the XML representation of column.
};

/**
 * The array of columns.
 */
typedef CArray <Column_Meta *, Column_Meta *> TColumn_Meta_Array;