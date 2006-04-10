//functions and classes for LM Metabase socket
#include "afx.h"
#include "afxtempl.h"
//4ft_hypothese
//CString fLM4fthyp(void* hSource);

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