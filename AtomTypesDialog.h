#if !defined(AFX_ATOMTYPESDIALOG_H__37E9FA1E_7CE6_4FF0_8083_B55D019FA313__INCLUDED_)
#define AFX_ATOMTYPESDIALOG_H__37E9FA1E_7CE6_4FF0_8083_B55D019FA313__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AtomTypesDialog.h : header file
//

#include <set>
#include "AtomType.h"

#include "ColorStatic.h"

/////////////////////////////////////////////////////////////////////////////
// AtomTypesDialog dialog

class AtomTypesDialog : public CDialog
{
// Construction
public:
	AtomTypesDialog(CWnd* pParent = NULL);   // standard constructor
	std::set<AtomType*> atomTypes;

// Dialog Data
	//{{AFX_DATA(AtomTypesDialog)
	enum { IDD = IDD_ATOMTYPES_DIALOG };
	CColorStatic	m_atomTypeColorStatic;
	CEdit	m_atomMassControl;
	CEdit	m_elementNameControl;
	CListBox	m_atomTypesListBox;
	CString	m_elementName;
	double	m_atomMass;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AtomTypesDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AtomTypesDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeList1();
	afx_msg void OnChangeAtomMass();
	afx_msg void OnChangeElementName();
	afx_msg void OnAddAtomTypeButton();
	afx_msg void OnChangeAtomTypeColorButton();
	afx_msg void OnEmbeddingEnergyButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATOMTYPESDIALOG_H__37E9FA1E_7CE6_4FF0_8083_B55D019FA313__INCLUDED_)
