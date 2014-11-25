#if !defined(AFX_POTENTIALDIALOG_H__2D74E544_1ECF_4FFE_BE6F_8E0CFA77261C__INCLUDED_)
#define AFX_POTENTIALDIALOG_H__2D74E544_1ECF_4FFE_BE6F_8E0CFA77261C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PotentialDialog.h : header file
//

#include <map>
#include <vector>
#include "AtomType.h"
#include "Potential.h"

/////////////////////////////////////////////////////////////////////////////
// PotentialDialog dialog

typedef std::pair<AtomType*,AtomType*> AtomTypesPair;

class PotentialDialog : public CDialog
{
// Construction
public:
	PotentialDialog(CWnd* pParent = NULL);   // standard constructor
	std::map<AtomTypesPair,Potential*> potentials;
	std::vector<AtomTypesPair> atomTypePairs;

// Dialog Data
	//{{AFX_DATA(PotentialDialog)
	enum { IDD = IDD_POTENTIAL_DIALOG };
	CListCtrl	m_potentialsListCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PotentialDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PotentialDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnLoadPotentialButton();
	afx_msg void OnLoadElectronicDistributionButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POTENTIALDIALOG_H__2D74E544_1ECF_4FFE_BE6F_8E0CFA77261C__INCLUDED_)
