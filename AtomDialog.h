#if !defined(AFX_ATOMDIALOG_H__B76352D7_C1D8_4D4D_B45F_47D54234D0FB__INCLUDED_)
#define AFX_ATOMDIALOG_H__B76352D7_C1D8_4D4D_B45F_47D54234D0FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AtomDialog.h : header file
//

#include <set>
#include "AtomType.h"

/////////////////////////////////////////////////////////////////////////////
// AtomDialog dialog

class AtomDialog : public CDialog
{
// Construction
public:
	AtomDialog(CWnd* pParent = NULL);   // standard constructor
	std::set<AtomType*> atomTypes;

	AtomType* atomType;
// Dialog Data
	//{{AFX_DATA(AtomDialog)
	enum { IDD = IDD_ATOM_DIALOG };
	CComboBox	m_atomTypeCombo;
	BOOL	m_Moveable;
	BOOL	m_Visible;
	double	m_forceX;
	double	m_forceY;
	double	m_forceZ;
	double	m_positionX;
	double	m_positionY;
	double	m_positionZ;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AtomDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AtomDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeAtomtypeCombo();
	afx_msg void OnSelendcancelAtomtypeCombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATOMDIALOG_H__B76352D7_C1D8_4D4D_B45F_47D54234D0FB__INCLUDED_)
