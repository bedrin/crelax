// AtomTypesDialog.cpp : implementation file
//

#include "stdafx.h"
#include "LatticeRelaxation.h"
#include "AtomTypesDialog.h"

#include <fstream>
#include "RelaxPtPotentialBuilder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AtomTypesDialog dialog


AtomTypesDialog::AtomTypesDialog(CWnd* pParent /*=NULL*/)
	: CDialog(AtomTypesDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(AtomTypesDialog)
	m_elementName = _T("");
	m_atomMass = 0.0;
	//}}AFX_DATA_INIT
}


void AtomTypesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AtomTypesDialog)
	DDX_Control(pDX, IDC_ATOMTYPE_COLOR_STATIC, m_atomTypeColorStatic);
	DDX_Control(pDX, IDC_EDIT2, m_atomMassControl);
	DDX_Control(pDX, IDC_EDIT1, m_elementNameControl);
	DDX_Control(pDX, IDC_LIST1, m_atomTypesListBox);
	DDX_Text(pDX, IDC_EDIT1, m_elementName);
	DDV_MaxChars(pDX, m_elementName, 2);
	DDX_Text(pDX, IDC_EDIT2, m_atomMass);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AtomTypesDialog, CDialog)
	//{{AFX_MSG_MAP(AtomTypesDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeAtomMass)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeElementName)
	ON_BN_CLICKED(IDC_ADD_ATOM_TYPE_BUTTON, OnAddAtomTypeButton)
	ON_BN_CLICKED(IDC_CHANGE_ATOM_TYPE_COLOR_BUTTON, OnChangeAtomTypeColorButton)
	ON_BN_CLICKED(IDC_EMBEDDING_ENERGY_BUTTON, OnEmbeddingEnergyButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AtomTypesDialog message handlers

BOOL AtomTypesDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	std::set<AtomType*>::iterator atomTypesIterator;
	for (atomTypesIterator = atomTypes.begin(); atomTypesIterator != atomTypes.end(); atomTypesIterator++) {
		AtomType* atomType = *atomTypesIterator;
		m_atomTypesListBox.AddString(atomType->name);
		m_atomTypesListBox.SetItemDataPtr(m_atomTypesListBox.GetCount() - 1, atomType);
	}

	if (m_atomTypesListBox.GetCount()) {
		m_atomTypesListBox.SetCurSel(0);
		m_atomMassControl.EnableWindow();
		//m_elementNameControl.EnableWindow();
		OnSelchangeList1();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void AtomTypesDialog::OnSelchangeList1() 
{
	// TODO: Add your control notification handler code here
	int selectedItem = m_atomTypesListBox.GetCurSel();
	AtomType* atomType = (AtomType*)m_atomTypesListBox.GetItemDataPtr(selectedItem);
	
	CString elementName;
	m_atomTypesListBox.GetText(selectedItem, elementName);
		
	m_atomMass = atomType->mass;
	m_elementName = elementName;

	m_atomTypeColorStatic.m_ctrlText = atomType->color;
	m_atomTypeColorStatic.RedrawWindow();
	//DoDataExchange(new CDataExchange(this,false));
	UpdateData(FALSE);
	
}

void AtomTypesDialog::OnChangeAtomMass() 
{
	DoDataExchange(new CDataExchange(this,true));
	int selectedItem = m_atomTypesListBox.GetCurSel();
	//double atomMass = m_atomMass;
	AtomType* atomType = (AtomType*)m_atomTypesListBox.GetItemDataPtr(selectedItem);
	atomType->mass = m_atomMass;
}

void AtomTypesDialog::OnChangeElementName() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	DoDataExchange(new CDataExchange(this,true));
	int selectedItem = m_atomTypesListBox.GetCurSel();
	
	AtomType* atomType = (AtomType*)m_atomTypesListBox.GetItemDataPtr(selectedItem);
	const char* newElementName = (LPCTSTR) m_elementName;
	strcpy(atomType->name, newElementName);

	m_atomTypesListBox.ResetContent();
	std::set<AtomType*>::iterator atomTypesIterator;
	for (atomTypesIterator = atomTypes.begin(); atomTypesIterator != atomTypes.end(); atomTypesIterator++) {
		AtomType* atomType = *atomTypesIterator;
		m_atomTypesListBox.AddString(atomType->name);
		m_atomTypesListBox.SetItemDataPtr(m_atomTypesListBox.GetCount() - 1, atomType);
	}
	m_atomTypesListBox.SetCurSel(selectedItem);
	OnSelchangeList1();
}

void AtomTypesDialog::OnAddAtomTypeButton() 
{
	// TODO: Add your control notification handler code here
	AtomType* newAtomType = new AtomType("",0);
	atomTypes.insert(newAtomType);
	int before = m_atomTypesListBox.GetCount();
	m_atomTypesListBox.AddString(newAtomType->name);
	int after = m_atomTypesListBox.GetCount();
	m_atomTypesListBox.SetItemDataPtr(after - 1, newAtomType);
	m_atomTypesListBox.SetCurSel(after - 1);
	OnSelchangeList1();
}

void AtomTypesDialog::OnChangeAtomTypeColorButton() 
{
	// TODO: Add your control notification handler code here
	CColorDialog colorDialog;
	if (IDOK == colorDialog.DoModal()) {
		m_atomTypeColorStatic.m_ctrlText = colorDialog.GetColor();
		m_atomTypeColorStatic.RedrawWindow();

		int selectedItem = m_atomTypesListBox.GetCurSel();
		AtomType* atomType = (AtomType*)m_atomTypesListBox.GetItemDataPtr(selectedItem);
		atomType->color = colorDialog.GetColor();
		
	}
	
}

void AtomTypesDialog::OnEmbeddingEnergyButton() 
{
	RelaxPtPotentialBuilder potBuilder(2.86);

	CFileDialog fileDialog(TRUE);
	fileDialog.DoModal();
	LPSTR fileName = fileDialog.m_ofn.lpstrFile;
	std::ifstream potfile(fileName,std::ios::in);

	TableSetFunction* embeddingEnergy = potBuilder.loadTableSetFunction(&potfile);
	
	int selectedItem = m_atomTypesListBox.GetCurSel();
	AtomType* atomType = (AtomType*)m_atomTypesListBox.GetItemDataPtr(selectedItem);
	atomType->embeddingEnergy = *embeddingEnergy;
}
