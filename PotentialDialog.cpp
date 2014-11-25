// PotentialDialog.cpp : implementation file
//

#include "stdafx.h"
#include "LatticeRelaxation.h"
#include "PotentialDialog.h"

#include <fstream>
#include "RelaxPtPotentialBuilder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// PotentialDialog dialog


PotentialDialog::PotentialDialog(CWnd* pParent /*=NULL*/)
	: CDialog(PotentialDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(PotentialDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void PotentialDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PotentialDialog)
	DDX_Control(pDX, IDC_POTENTIAL_LIST, m_potentialsListCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PotentialDialog, CDialog)
	//{{AFX_MSG_MAP(PotentialDialog)
	ON_BN_CLICKED(IDC_LOAD_POTENTIAL_BUTTON, OnLoadPotentialButton)
	ON_BN_CLICKED(IDC_LOAD_ELECTRONIC_DISTRIBUTION_BUTTON, OnLoadElectronicDistributionButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PotentialDialog message handlers

BOOL PotentialDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_potentialsListCtrl.SetExtendedStyle(
		m_potentialsListCtrl.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT );

	m_potentialsListCtrl.InsertColumn(0,"Atom 1");
	m_potentialsListCtrl.SetColumnWidth(0,50);
	m_potentialsListCtrl.InsertColumn(1,"Atom 2");
	m_potentialsListCtrl.SetColumnWidth(1,50);
	m_potentialsListCtrl.InsertColumn(2,"Potential");
	m_potentialsListCtrl.SetColumnWidth(2,110);

	std::map<std::pair<AtomType*,AtomType*>,Potential*>::iterator atomTypePairsIterator;
	int i = 0;
	for (atomTypePairsIterator = potentials.begin(); atomTypePairsIterator != potentials.end(); atomTypePairsIterator++) {
		//std::pair<AtomType*,AtomType*> atomTypePair = atomTypePairsIterator->first;
		const AtomTypesPair& atomTypePair = atomTypePairsIterator->first;
		atomTypePairs.push_back(atomTypePair);
		Potential* potential = (Potential*)atomTypePairsIterator->second;
		m_potentialsListCtrl.InsertItem(i,atomTypePair.first->name);
		m_potentialsListCtrl.SetItemText(i,0,atomTypePair.first->name);
		m_potentialsListCtrl.SetItemText(i,1,atomTypePair.second->name);
		if (potential) {
			m_potentialsListCtrl.SetItemText(i,2,potential->name.c_str());
		}
		//m_potentialsListCtrl.SetItemData(i,(DWORD)(atomTypePair));
				
		i++;
	}

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void PotentialDialog::OnLoadPotentialButton() 
{
	int selMark = m_potentialsListCtrl.GetSelectionMark();
	if (-1 != selMark) {
		RelaxPtPotentialBuilder potBuilder(2.86);

		CFileDialog fileDialog(TRUE);
		fileDialog.DoModal();
		LPSTR fileName = fileDialog.m_ofn.lpstrFile;
		std::ifstream potfile(fileName,std::ios::in);

		Potential* potential = potBuilder.loadPotential(&potfile);
		potential->name = fileDialog.m_ofn.lpstrFileTitle;

		m_potentialsListCtrl.SetItemText(selMark,2,potential->name.c_str());

		AtomTypesPair atomTypesPair = atomTypePairs.at(selMark);

		potentials[atomTypesPair] = potential;
		//potentials->key_type;
		
		/*DWORD itemData = m_potentialsListCtrl.GetItemData(selMark);
		std::pair<AtomType*,AtomType*>* atomTypesPairPt = reinterpret_cast<std::pair<AtomType*,AtomType*>*> (itemData);
		const std::pair<AtomType*,AtomType*>& atomTypesPair = *atomTypesPairPt;

		//potentials[atomTypesPair] = potential;
		potentials[*atomTypesPairPt];

		
		m_potentialsListCtrl.SetItemData(selMark,(DWORD)potential);

		DWORD itemData = m_potentialsListCtrl.GetItemData(selMark);
		Potential* newPotential = reinterpret_cast<Potential*> (itemData);
		AfxMessageBox(newPotential->name.c_str());*/
	}
}

void PotentialDialog::OnLoadElectronicDistributionButton() 
{
	// TODO: Add your control notification handler code here
	int selMark = m_potentialsListCtrl.GetSelectionMark();
	if (-1 != selMark) {
		RelaxPtPotentialBuilder potBuilder(2.86);

		CFileDialog fileDialog(TRUE);
		fileDialog.DoModal();
		LPSTR fileName = fileDialog.m_ofn.lpstrFile;
		std::ifstream potfile(fileName,std::ios::in);

		TableSetFunction* electronicDensityDistribution = potBuilder.loadTableSetFunction(&potfile);
		/*potential->name = fileDialog.m_ofn.lpstrFileTitle;

		m_potentialsListCtrl.SetItemText(selMark,2,potential->name.c_str());*/

		AtomTypesPair atomTypesPair = atomTypePairs.at(selMark);
		Potential* potential = potentials[atomTypesPair];
		potential->electronicDensityDistribution = *electronicDensityDistribution;
	}
}
