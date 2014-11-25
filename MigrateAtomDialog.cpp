// MigrateAtomDialog.cpp : implementation file
//

#include "stdafx.h"
#include "LatticeRelaxation.h"
#include "MigrateAtomDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MigrateAtomDialog dialog


MigrateAtomDialog::MigrateAtomDialog(CWnd* pParent /*=NULL*/)
	: CDialog(MigrateAtomDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(MigrateAtomDialog)
	m_x = 0.0;
	m_y = 0.0;
	m_z = 0.0;
	m_migrationSteps = 0;
	//}}AFX_DATA_INIT
}


void MigrateAtomDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MigrateAtomDialog)
	DDX_Text(pDX, IDC_EDIT_X, m_x);
	DDX_Text(pDX, IDC_EDIT_Y, m_y);
	DDX_Text(pDX, IDC_EDIT_Z, m_z);
	DDX_Text(pDX, IDC_EDIT_MIGRATION_STEPS, m_migrationSteps);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MigrateAtomDialog, CDialog)
	//{{AFX_MSG_MAP(MigrateAtomDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MigrateAtomDialog message handlers
