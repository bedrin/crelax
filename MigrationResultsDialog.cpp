// MigrationResultsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "LatticeRelaxation.h"
#include "MigrationResultsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MigrationResultsDialog dialog


MigrationResultsDialog::MigrationResultsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(MigrationResultsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(MigrationResultsDialog)
	m_migrationEnergy = 0.0;
	m_numberOfSteps = 0;
	//}}AFX_DATA_INIT
}


void MigrationResultsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MigrationResultsDialog)
	DDX_Control(pDX, IDC_MIGRATION_STEPS_LIST, m_migrationStepsList);
	DDX_Text(pDX, IDC_ENERGY_OF_MIGRATION_EDIT, m_migrationEnergy);
	DDX_Text(pDX, IDC_NUMBER_OF_MIGRATION_STEPS_EDIT, m_numberOfSteps);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MigrationResultsDialog, CDialog)
	//{{AFX_MSG_MAP(MigrationResultsDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MigrationResultsDialog message handlers

BOOL MigrationResultsDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_migrationStepsList.SetExtendedStyle(
		m_migrationStepsList.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT );

	m_migrationStepsList.InsertColumn(0,"Step");
	m_migrationStepsList.SetColumnWidth(0,50);
	m_migrationStepsList.InsertColumn(1,"Migrating atom coordinates, a0");
	m_migrationStepsList.SetColumnWidth(1,190);
	m_migrationStepsList.InsertColumn(2,"Energy after relaxation, eV");
	m_migrationStepsList.SetColumnWidth(2,190);
	m_migrationStepsList.InsertColumn(3,"Delta Energy, eV");
	m_migrationStepsList.SetColumnWidth(3,142);

	std::vector<MigrationStepResults>::iterator stepsIterator;
	std::vector<MigrationStepResults> steps = migrationResults.migrationStepResults;

	int numberOfSteps = 0;
	double minEnergy = 0.0;
	double maxEnergy = 0.0;

	for (stepsIterator = steps.begin(); stepsIterator != steps.end(); stepsIterator++) {
		MigrationStepResults relaxationResults = *stepsIterator;

		CString formatString;

		formatString.Format("%d",numberOfSteps);
		m_migrationStepsList.InsertItem(numberOfSteps,formatString);
		m_migrationStepsList.SetItemText(numberOfSteps,0,formatString);

		formatString.Format("(%f, %f, %f)",relaxationResults.migratingAtomCoordinates.x / 2.86,relaxationResults.migratingAtomCoordinates.y / 2.86,relaxationResults.migratingAtomCoordinates.z / 2.86);
		m_migrationStepsList.SetItemText(numberOfSteps,1,formatString);

		formatString.Format("%f",relaxationResults.complexEnergyAfterRelaxation);
		m_migrationStepsList.SetItemText(numberOfSteps,2,formatString);

		formatString.Format("%f",relaxationResults.relaxationEnergy);
		m_migrationStepsList.SetItemText(numberOfSteps,3,formatString);

		if ((relaxationResults.complexEnergyAfterRelaxation > maxEnergy) || (maxEnergy == 0.0)) {
			maxEnergy = relaxationResults.complexEnergyAfterRelaxation;
		}

		if ((relaxationResults.complexEnergyAfterRelaxation < minEnergy) || (minEnergy == 0.0)) {
			minEnergy = relaxationResults.complexEnergyAfterRelaxation;
		}

		numberOfSteps++;

	}

	numberOfSteps = 0;
	for (stepsIterator = steps.begin(); stepsIterator != steps.end(); stepsIterator++) {
		MigrationStepResults relaxationResults = *stepsIterator;

		CString formatString;

		formatString.Format("%f",relaxationResults.complexEnergyAfterRelaxation - minEnergy);
		m_migrationStepsList.SetItemText(numberOfSteps,3,formatString);

		numberOfSteps++;
	}
	
	m_migrationEnergy = maxEnergy - minEnergy;
    m_numberOfSteps = numberOfSteps; 

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
