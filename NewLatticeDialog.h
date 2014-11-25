#if !defined(AFX_NEWLATTICEDIALOG_H__1BBB3869_6511_422D_BFF4_93362CF3EC22__INCLUDED_)
#define AFX_NEWLATTICEDIALOG_H__1BBB3869_6511_422D_BFF4_93362CF3EC22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewLatticeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewLatticeDialog dialog

enum LatticeType {
	BCC, FCC
};

class CNewLatticeDialog : public CDialog
{
// Construction
public:
	CNewLatticeDialog(CWnd* pParent = NULL);   // standard constructor
	LatticeType m_latticeType;

// Dialog Data
	//{{AFX_DATA(CNewLatticeDialog)
	enum { IDD = IDD_NEW_LATTICE_DIALOG };
	double	m_moveableRadius;
	double	m_totalRadius;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewLatticeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewLatticeDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioBcc();
	afx_msg void OnRadioFcc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWLATTICEDIALOG_H__1BBB3869_6511_422D_BFF4_93362CF3EC22__INCLUDED_)
