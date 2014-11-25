#if !defined(AFX_MIGRATEATOMDIALOG_H__6C41E495_9296_46CA_AF79_DA783E5D600C__INCLUDED_)
#define AFX_MIGRATEATOMDIALOG_H__6C41E495_9296_46CA_AF79_DA783E5D600C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MigrateAtomDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MigrateAtomDialog dialog

class MigrateAtomDialog : public CDialog
{
// Construction
public:
	MigrateAtomDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MigrateAtomDialog)
	enum { IDD = IDD_MIGRATE_ATOM_DIALOG };
	double	m_x;
	double	m_y;
	double	m_z;
	int		m_migrationSteps;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MigrateAtomDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MigrateAtomDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIGRATEATOMDIALOG_H__6C41E495_9296_46CA_AF79_DA783E5D600C__INCLUDED_)
