// AtomDialog.cpp : implementation file
//

#include "stdafx.h"
#include "LatticeRelaxation.h"
#include "AtomDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AtomDialog dialog


AtomDialog::AtomDialog(CWnd* pParent /*=NULL*/)
	: CDialog(AtomDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(AtomDialog)
	m_Moveable = FALSE;
	m_Visible = FALSE;
	m_forceX = 0.0;
	m_forceY = 0.0;
	m_forceZ = 0.0;
	m_positionX = 0.0;
	m_positionY = 0.0;
	m_positionZ = 0.0;
	//}}AFX_DATA_INIT
}


void AtomDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(AtomDialog)
	DDX_Control(pDX, IDC_ATOMTYPE_COMBO, m_atomTypeCombo);
	DDX_Check(pDX, IDC_CHECK_MOVEABLE, m_Moveable);
	DDX_Check(pDX, IDC_CHECK_VISIBLE, m_Visible);
	DDX_Text(pDX, IDC_EDIT_FORCE_X, m_forceX);
	DDX_Text(pDX, IDC_EDIT_FORCE_Y, m_forceY);
	DDX_Text(pDX, IDC_EDIT_FORCE_Z, m_forceZ);
	DDX_Text(pDX, IDC_EDIT_POSITION_X, m_positionX);
	DDX_Text(pDX, IDC_EDIT_POSITION_Y, m_positionY);
	DDX_Text(pDX, IDC_EDIT_POSITION_Z, m_positionZ);
	//}}AFX_DATA_MAP

	if (pDX->m_bSaveAndValidate) {
		m_positionX *= 2.86;
		m_positionY *= 2.86;
		m_positionZ *= 2.86;
	}

}


BEGIN_MESSAGE_MAP(AtomDialog, CDialog)
	//{{AFX_MSG_MAP(AtomDialog)
	ON_CBN_EDITCHANGE(IDC_ATOMTYPE_COMBO, OnEditchangeAtomtypeCombo)
	ON_CBN_SELENDCANCEL(IDC_ATOMTYPE_COMBO, OnSelendcancelAtomtypeCombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AtomDialog message handlers

BOOL AtomDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	std::set<AtomType*>::iterator atomTypesIterator;
	for (atomTypesIterator = atomTypes.begin(); atomTypesIterator != atomTypes.end(); atomTypesIterator++) {
		AtomType* atomType = *atomTypesIterator;
		m_atomTypeCombo.AddString(atomType->name);
		m_atomTypeCombo.SetItemDataPtr(m_atomTypeCombo.GetCount() - 1, atomType);
		if (this->atomType == atomType) {
			m_atomTypeCombo.SetCurSel(m_atomTypeCombo.GetCount() - 1);
		}
	}

	m_positionX /= 2.86;
	m_positionY /= 2.86;
	m_positionZ /= 2.86;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void AtomDialog::OnEditchangeAtomtypeCombo() 
{
	// TODO: Add your control notification handler code here
	atomType = (AtomType*)m_atomTypeCombo.GetItemDataPtr(m_atomTypeCombo.GetCurSel());
}

void AtomDialog::OnSelendcancelAtomtypeCombo() 
{
	// TODO: Add your control notification handler code here
	atomType = (AtomType*)m_atomTypeCombo.GetItemDataPtr(m_atomTypeCombo.GetCurSel());
}
