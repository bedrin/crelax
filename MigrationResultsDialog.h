#if !defined(AFX_MIGRATIONRESULTSDIALOG_H__4B24D33C_6047_4561_BEDC_B3F6EF99E24A__INCLUDED_)
#define AFX_MIGRATIONRESULTSDIALOG_H__4B24D33C_6047_4561_BEDC_B3F6EF99E24A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MigrationResultsDialog.h : header file
//

#include "MigrationResults.h"

/////////////////////////////////////////////////////////////////////////////
// MigrationResultsDialog dialog

class MigrationResultsDialog : public CDialog
{
// Construction
public:
	MigrationResultsDialog(CWnd* pParent = NULL);   // standard constructor
	MigrationResults migrationResults;

// Dialog Data
	//{{AFX_DATA(MigrationResultsDialog)
	enum { IDD = IDD_MIGRATION_RESULTS_DIALOG };
	CListCtrl	m_migrationStepsList;
	double	m_migrationEnergy;
	int		m_numberOfSteps;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MigrationResultsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MigrationResultsDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIGRATIONRESULTSDIALOG_H__4B24D33C_6047_4561_BEDC_B3F6EF99E24A__INCLUDED_)
