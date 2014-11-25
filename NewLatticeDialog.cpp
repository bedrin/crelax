// NewLatticeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "LatticeRelaxation.h"
#include "NewLatticeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewLatticeDialog dialog


CNewLatticeDialog::CNewLatticeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CNewLatticeDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewLatticeDialog)
	m_moveableRadius = 2.0;
	m_totalRadius = 4.0;
	m_latticeType = BCC;
	//}}AFX_DATA_INIT
}


void CNewLatticeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewLatticeDialog)
	DDX_Text(pDX, IDC_EDIT_MOVEABLE_RADIUS, m_moveableRadius);
	DDX_Text(pDX, IDC_EDIT_TOTAL_RADIUS, m_totalRadius);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewLatticeDialog, CDialog)
	//{{AFX_MSG_MAP(CNewLatticeDialog)
	ON_BN_CLICKED(IDC_RADIO_BCC, OnRadioBcc)
	ON_BN_CLICKED(IDC_RADIO_FCC, OnRadioFcc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewLatticeDialog message handlers

BOOL CNewLatticeDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if (m_latticeType == BCC) {
		CheckRadioButton(IDC_RADIO_BCC, IDC_RADIO_FCC, IDC_RADIO_BCC);
	} else {
		CheckRadioButton(IDC_RADIO_BCC, IDC_RADIO_FCC, IDC_RADIO_FCC);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewLatticeDialog::OnRadioBcc() 
{
	// TODO: Add your control notification handler code here
	m_latticeType = BCC;
}

void CNewLatticeDialog::OnRadioFcc() 
{
	// TODO: Add your control notification handler code here
	m_latticeType = FCC;
}
