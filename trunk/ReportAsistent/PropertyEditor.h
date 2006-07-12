#if !defined(AFX_PROPERTYEDITOR_H__E2BBA28E_CE60_4DCF_BF22_C3CF4E78ED0E__INCLUDED_)
#define AFX_PROPERTYEDITOR_H__E2BBA28E_CE60_4DCF_BF22_C3CF4E78ED0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropertyEditor.h : header file
//


class CProperty
{
private:
	CString m_label;

public:
	CProperty(LPCTSTR label) : m_label(label) {};
	LPCTSTR virtual GetLabel() {return m_label; };
	LPCTSTR virtual GetValue() = 0;
	void virtual SetValue(LPCTSTR value) = 0;
	BOOL virtual ValidateValue(CString & value, CString & error_message) = 0;
	DWORD virtual GetComboStyle() = 0;
	void virtual InitCombo(CComboBox * combo) {};

	virtual ~CProperty() {};

};

class CIntProperty: public CProperty
{
private:
	int m_value;
	int m_min;
	int m_max;
	CString m_str_val;

public:
	CIntProperty(LPCTSTR label, int default_value, int min = 0x80000000, int max = 0x7FFFFFFF)
		: CProperty(label), m_value(default_value), m_min(min), m_max(max) { ASSERT(min <= max); };
	
	LPCTSTR virtual GetValue() {m_str_val.Format("%d", m_value); return m_str_val; };
	int GetIntValue() {return m_value; };
	
	void virtual SetValue(LPCTSTR value) {m_value = (long) (_variant_t) value; };
	void SetIntValue(int value) {m_value = value; };
	
	BOOL virtual ValidateValue(CString & value, CString & error_message)
	{
		int try_convert=0;

		try
		{
			try_convert = (long) (_variant_t) value;
		}
		catch (_com_error & e)
		{
			error_message = (LPCTSTR) e.ErrorMessage();
			return FALSE;
		}

		if (try_convert < m_min)
		{
			error_message.Format("Value %d is out of range.\n(minimum = %d)", try_convert, m_min);
			return FALSE;
		}

		if (try_convert > m_max)
		{
			error_message.Format("Value %d is out of range.\n(maximum = %d)", try_convert, m_max);
			return FALSE;
		}


		//zapise prectenou hodnotu do edit boxu zmeni napriklad 4,5 na 5
		value.Format("%d", try_convert);
		return TRUE;
	};

	DWORD virtual GetComboStyle() {return CBS_DROPDOWN; };


	
	//nastavuje edit box tak, aby se do nej daly psat jen cislice (ani "-" (minus) nejde))
	void virtual InitCombo(CComboBox * combo)
	{
		if (m_min < 0) return;

/*
// funguje jen ve VS 2005
		COMBOBOXINFO info;
		info.cbSize = sizeof info;
		combo->GetComboBoxInfo(& info);
		combo->GetEditCtrl();
		LONG style = GetWindowLong(info.hwndItem, GWL_STYLE);
		SetWindowLong(info.hwndItem, GWL_STYLE, style | ES_NUMBER);
*/
	};
};

class CDoubleProperty: public CProperty
{
private:
	double m_value;
	double m_min;
	double m_max;
	CString m_str_val;

public:
	CDoubleProperty(LPCTSTR label, double default_value, double min = -1.7E+308 , double max = 1.7E+308 )
		: CProperty(label), m_value(default_value), m_min(min), m_max(max) { ASSERT(min <= max); };

	LPCTSTR virtual GetValue() {m_str_val = (LPCTSTR) (_bstr_t) m_value; return m_str_val; };
	double GetDoubleValue() {return m_value; };
	
	void virtual SetValue(LPCTSTR value) {m_value = (_variant_t) value; };
	void SetDoubleValue(double value) {m_value = value; };

	BOOL virtual ValidateValue(CString & value, CString & error_message)
	{
		double try_convert=0;

		try
		{
			try_convert = (double) (_variant_t) value;
		}
		catch (_com_error & e)
		{
			error_message = (LPCTSTR) e.ErrorMessage();
			return FALSE;
		}

		if (try_convert < m_min)
		{
			error_message.Format("Value %s is out of range.\n(minimum = %s)",
				(LPCTSTR) (_bstr_t) try_convert, (LPCTSTR) (_bstr_t) m_min);
			return FALSE;
		}

		if (try_convert > m_max)
		{
			error_message.Format("Value %s is out of range.\n(maximum = %s)",
				(LPCTSTR) (_bstr_t) try_convert, (LPCTSTR) (_bstr_t) m_max);
			return FALSE;
		}

//		value.Format("%d", try_convert);
		return TRUE;
	};

	DWORD virtual GetComboStyle() {return CBS_DROPDOWN; };
};

class CStringProperty: public CProperty
{
private:
	CString m_value;

public:
	CStringProperty(LPCTSTR label, LPCTSTR default_value): CProperty(label), m_value(default_value) {};
	LPCTSTR virtual GetValue() {return m_value; };
	void virtual SetValue(LPCTSTR value) {m_value = value; };
	BOOL virtual ValidateValue(CString & value, CString & error_message) {return TRUE; };
	DWORD virtual GetComboStyle() {return CBS_DROPDOWN; };
};

class CEnumProperty: public CStringProperty
{
private:
	CArray<CString, CString> m_combo_strings;

public:
	CEnumProperty(LPCTSTR label, LPCTSTR default_value): CStringProperty(label, default_value) {};
	DWORD virtual GetComboStyle() {return CBS_DROPDOWNLIST; };
	void AddCombostr(LPCTSTR str) {m_combo_strings.Add(str); };
	void virtual InitCombo(CComboBox * combo)
	{
		for(int a=0; a<m_combo_strings.GetSize(); a++)
			combo->AddString(m_combo_strings[a]);
	};
};


/////////////////////////////////////////////////////////////////////////////
// CPropertyEditor dialog

class CPropertyEditor : public CDialog
{
// Construction
public:
	CPropertyEditor(LPCTSTR caption, CWnd* pParent = NULL);   // standard constructor
	virtual ~CPropertyEditor();

// Dialog Data
	//{{AFX_DATA(CPropertyEditor)
	enum { IDD = IDD_PROPERTY_EDITOR };
	CStatic	m_err_text;
	CStatic	m_static_border;
	CScrollBar	m_scrollbar;
	CButton	m_ok_button;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertyEditor)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropertyEditor)
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	struct SProperty {CStatic * label; CComboBox * combo; CProperty * prop; };
	CArray<SProperty, SProperty&> m_properties;
	CList<int, int> m_err_props;
	CString m_caption;


protected:
	int GetMaxVisiblePropertiesCount(void);
	int GetFirstVisibleProperty(void);
	int GetLastVisibleProperty(void);
	void CreateProperty(int index);
	void ShowVisibleProperties(void);
	void CountPropertyRects(CRect & label_rect, CRect & combo_rect, int property_index);
	BOOL ValidateProp(int index);


public:
	int GetPropertiesCount(void);
	int AddProperty(CProperty * prop);
	CProperty * GetValueOfProperty(int index);


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYEDITOR_H__E2BBA28E_CE60_4DCF_BF22_C3CF4E78ED0E__INCLUDED_)
