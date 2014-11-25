// LatticeRelaxationDoc.cpp : implementation of the CLatticeRelaxationDoc class
//

#include "stdafx.h"
#include "LatticeRelaxation.h"

#include "LatticeRelaxationDoc.h"

#include <fstream>

#include "RelaxCorLatticeBuilder.h"
#include "RelaxPtPotentialBuilder.h"
#include "Relaxation.h"

#include "AtomTypesDialog.h"
#include "AtomDialog.h"
#include "PotentialDialog.h"
#include "NewLatticeDialog.h"
#include "ModelingOptionsDialog.h"
#include "MigrationResultsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLatticeRelaxationDoc

IMPLEMENT_DYNCREATE(CLatticeRelaxationDoc, CDocument)

BEGIN_MESSAGE_MAP(CLatticeRelaxationDoc, CDocument)
	//{{AFX_MSG_MAP(CLatticeRelaxationDoc)
	ON_COMMAND(ID_START_RELAXATION, OnStartRelaxation)
	ON_COMMAND(ID_SELECT_POTENTIAL, OnSelectPotential)
	ON_COMMAND(ID_REFRESH, OnRefresh)
	ON_COMMAND(ID_ATOM_TYPES, OnAtomTypes)
	ON_COMMAND(ID_STOP_RELAXATION, OnStopRelaxation)
	ON_COMMAND(ID_PAUSE_RELAXATION, OnPauseRelaxation)
	ON_UPDATE_COMMAND_UI(ID_STOP_RELAXATION, OnUpdateStopRelaxation)
	ON_UPDATE_COMMAND_UI(ID_START_RELAXATION, OnUpdateStartRelaxation)
	ON_UPDATE_COMMAND_UI(ID_PAUSE_RELAXATION, OnUpdatePauseRelaxation)
	ON_COMMAND(ID_ADD_ATOM_BUTTON, OnAddAtomButton)
	ON_COMMAND(ID_MODELING_OPTIONS, OnModelingOptions)
	ON_COMMAND(ID_CALCULATE_FORCES, OnCalculateForces)
	ON_COMMAND(ID_MODELING_RESULTS, OnModelingResults)
	ON_UPDATE_COMMAND_UI(ID_MODELING_RESULTS, OnUpdateModelingResults)
	ON_COMMAND(ID_EXPORT_RESULTS, OnExportResults)
	ON_UPDATE_COMMAND_UI(ID_EXPORT_RESULTS, OnUpdateExportResults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLatticeRelaxationDoc construction/destruction

CLatticeRelaxationDoc::CLatticeRelaxationDoc()
	: modelingThreadState (STOPPED), calculationFinished(false)
{
	// TODO: add one-time construction code here
	//potentialLoaded = false;
}

CLatticeRelaxationDoc::~CLatticeRelaxationDoc()
{
}

BOOL CLatticeRelaxationDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	//lattice = new Lattice();
	CNewLatticeDialog dialog;
	if (IDOK == dialog.DoModal()) {
		double moveableRadius = dialog.m_moveableRadius;
		double totalRadius = dialog.m_totalRadius;
		LatticeType latticeType = dialog.m_latticeType;
		Lattice* lattice;
		if (BCC == latticeType) {
			lattice = LatticeBuilder::buildBCCLattice(moveableRadius, totalRadius);
		} else if (FCC == latticeType) {
			lattice = LatticeBuilder::buildFCCLattice(moveableRadius, totalRadius);
		}
		modelingProject = new ModelingProject(lattice);
	} else {
		Lattice* lattice = new Lattice();
		modelingProject = new ModelingProject(lattice);
	}

	UpdateAllViews(NULL);

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLatticeRelaxationDoc serialization

void CLatticeRelaxationDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLatticeRelaxationDoc diagnostics

#ifdef _DEBUG
void CLatticeRelaxationDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLatticeRelaxationDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLatticeRelaxationDoc commands

BOOL CLatticeRelaxationDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	RelaxCorLatticeBuilder latticeBuilder;
	
	std::ifstream corfile(lpszPathName,std::ios::in);

	Lattice* lattice = latticeBuilder.loadLattice(&corfile);
	modelingProject = new ModelingProject(lattice);

	UpdateAllViews(NULL,TRUE);
	
	return TRUE;
}



void CLatticeRelaxationDoc::OnSelectPotential() 
{
	PotentialDialog potentialDialog;

	modelingProject->populatePotentials();
	potentialDialog.potentials = modelingProject->potentials;

	if (IDOK == potentialDialog.DoModal()) {
		modelingProject->potentials = potentialDialog.potentials;
	}
	/*
	RelaxPtPotentialBuilder potBuilder(2.86);

    CFileDialog fileDialog(TRUE);
    fileDialog.DoModal();
    LPSTR fileName = fileDialog.m_ofn.lpstrFile;
    std::ifstream potfile(fileName,std::ios::in);

	potential = *(potBuilder.loadPotential(&potfile));

	modelingProject->populateAtomTypes();
	std::set<AtomType*> atomTypes = modelingProject->atomTypes;
	
	AtomType* feAtomType = *(atomTypes.begin());
	
	modelingProject->potentials[std::pair<AtomType*,AtomType*>(feAtomType,feAtomType)] = &potential;

	potentialLoaded = true;*/
	
}

void CLatticeRelaxationDoc::OnRefresh() 
{
	// TODO: Add your command handler code here
	modelingProject->populateAtomTypes();

	UpdateAllViews(NULL);
}

void CLatticeRelaxationDoc::OnAtomTypes() 
{
	modelingProject->populateAtomTypes();
	//modelingProject->atomTypes.insert(AtomType("C",30));

	AtomTypesDialog atomTypesDialog;
	atomTypesDialog.atomTypes = modelingProject->atomTypes;
	if (IDOK == atomTypesDialog.DoModal()) {
		modelingProject->atomTypes = atomTypesDialog.atomTypes;
	}
}

UINT RelaxationThreadProc( LPVOID pParam ) {
	CLatticeRelaxationDoc* doc = (CLatticeRelaxationDoc*) pParam;

	Relaxation relaxation(doc,doc->modelingOptions);
	
	try {
		if (NULL == doc->modelingProject->migratingAtom) {
			doc->relaxationResults = relaxation.relaxation(NULL);
			AfxMessageBox(doc->relaxationResults.getStringValue());
		} else {
			doc->migrationResults = relaxation.migration(NULL);
			MigrationResultsDialog migrationResultsDialog;
			migrationResultsDialog.migrationResults = doc->migrationResults;
			migrationResultsDialog.DoModal();
			
		}
		doc->calculationFinished = true;
	} catch (PotentialNotLoadedException e) {
		AfxMessageBox("Potential isn't loaded");
	}

	doc->modelingThreadState = CLatticeRelaxationDoc::ModelingThreadState::STOPPED;



	return 0;
}

void CLatticeRelaxationDoc::OnUpdateStartRelaxation(CCmdUI* pCmdUI) 
{
	if (STARTED == modelingThreadState) {
		pCmdUI->Enable(FALSE);
	} else {
		pCmdUI->Enable(TRUE);
	}
}

void CLatticeRelaxationDoc::OnStartRelaxation() 
{
	if (STOPPED == modelingThreadState) {
		modelingThreadState = STARTING;

		relaxationThread = AfxBeginThread(RelaxationThreadProc,this);
		modelingThreadState = STARTED;
	} else if (SUSPENDED == modelingThreadState) {
		modelingThreadState = RESUMING;
		// TODO: implement correct thread resume
		relaxationThread->ResumeThread();
		modelingThreadState = STARTED;
	}

}

void CLatticeRelaxationDoc::OnUpdateStopRelaxation(CCmdUI* pCmdUI) 
{
	if (STARTED == modelingThreadState) {
		pCmdUI->Enable();
	} else {
		pCmdUI->Enable(FALSE);
	}
}

void CLatticeRelaxationDoc::OnStopRelaxation() 
{
	if (STARTED == modelingThreadState) {
		modelingThreadState = STOPPING;
		// TODO: Add thread stopping code now
		relaxationThread->ExitInstance();
		modelingThreadState = STOPPED;
	}
}

void CLatticeRelaxationDoc::OnUpdatePauseRelaxation(CCmdUI* pCmdUI) 
{
	if (STARTED == modelingThreadState) {
		pCmdUI->Enable();
	} else {
		pCmdUI->Enable(FALSE);
	}
}

void CLatticeRelaxationDoc::OnPauseRelaxation() 
{
	modelingThreadState = SUSPENDING;
	// TODO: implement correct thread suspend
	relaxationThread->SuspendThread();

	modelingThreadState = SUSPENDED;
}



void CLatticeRelaxationDoc::OnAddAtomButton() 
{
	// TODO: Add your command handler code here
	AtomDialog atomDialog;
			
	modelingProject->populateAtomTypes();
	atomDialog.atomTypes = modelingProject->atomTypes;

	if (IDOK == atomDialog.DoModal()) {

		Atom* atom = new Atom();

		atom->r.x = atomDialog.m_positionX;
		atom->r.y = atomDialog.m_positionY;
		atom->r.z = atomDialog.m_positionZ;

		atom->v.x = atomDialog.m_forceX;
		atom->v.y = atomDialog.m_forceY;
		atom->v.z = atomDialog.m_forceZ;

		atom->moveable = atomDialog.m_Moveable;
		atom->visible = atomDialog.m_Visible;

		atom->atomType = atomDialog.atomType;

		modelingProject->activeLattice->atoms.push_back(atom);

		UpdateAllViews(NULL,1,NULL);
	}
}

void CLatticeRelaxationDoc::OnModelingOptions() 
{
	// TODO: Add your command handler code here
	ModelingOptionsDialog dialog;
	dialog.m_differentialStep = modelingOptions.diffStep;
	dialog.m_maximumInteractionDistance = modelingOptions.maximumActionDistance;
	dialog.m_maximumNumberOfDemphings = modelingOptions.maximumNumberOfDemphings;
	dialog.m_maximumNumberOfSteps = modelingOptions.maximumNumberOfSteps;
	dialog.m_maximumTimeDelta = modelingOptions.maxdelt;
	dialog.m_mimimumKineticEnergy = modelingOptions.minimumKineticEnergy;
	dialog.m_startTimeDelta = modelingOptions.startDelt;
	dialog.m_timeDeltaIncrement = modelingOptions.ddelt;
	dialog.m_useEmbeddedAtomMethod = modelingOptions.useEmbeddedAtomMethod;
	dialog.m_calculateDilatationVolume = modelingOptions.calculateDilatationVolume;
	dialog.m_bulkModulus = modelingOptions.bulkModulus;
	dialog.m_elasticCorrectionsAmmount = modelingOptions.elasticCorrectionsAmmount;
	dialog.m_dampingEnabled = modelingOptions.dampingEnabled;
	if (IDOK == dialog.DoModal()) {
		modelingOptions.diffStep = dialog.m_differentialStep;
		modelingOptions.maximumActionDistance = dialog.m_maximumInteractionDistance;
		modelingOptions.maximumNumberOfDemphings = dialog.m_maximumNumberOfDemphings;
		modelingOptions.maximumNumberOfSteps = dialog.m_maximumNumberOfSteps;
		modelingOptions.maxdelt = dialog.m_maximumTimeDelta;
		modelingOptions.minimumKineticEnergy = dialog.m_mimimumKineticEnergy;
		modelingOptions.startDelt = dialog.m_startTimeDelta;
		modelingOptions.ddelt = dialog.m_timeDeltaIncrement;
		modelingOptions.useEmbeddedAtomMethod = dialog.m_useEmbeddedAtomMethod;
		modelingOptions.calculateDilatationVolume = dialog.m_calculateDilatationVolume;
		modelingOptions.bulkModulus = dialog.m_bulkModulus;
		modelingOptions.elasticCorrectionsAmmount = dialog.m_elasticCorrectionsAmmount;
		modelingOptions.dampingEnabled = dialog.m_dampingEnabled;
	}
}

void CLatticeRelaxationDoc::OnCalculateForces() 
{
	Relaxation relaxation(this,modelingOptions);
	
	try {
		modelingProject->activeLattice->calculateAtomNeighbours(modelingOptions.maximumActionDistance);
		relaxation.calculateForces(true);
		relaxation.saveForces();
	} catch (PotentialNotLoadedException e) {
		AfxMessageBox("Potential isn't loaded");
	}	
}

BOOL CLatticeRelaxationDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	RelaxCorLatticeBuilder latticeBuilder;

	Lattice* lattice =modelingProject->activeLattice;

	std::ofstream corfile(lpszPathName,std::ios::out);
	latticeBuilder.storeLattice(lattice,&corfile);

	return true;
}

void CLatticeRelaxationDoc::OnModelingResults() 
{
	if (calculationFinished) {
		if (NULL == modelingProject->migratingAtom) {
			AfxMessageBox(relaxationResults.getStringValue());
		} else {
			MigrationResultsDialog migrationResultsDialog;
			migrationResultsDialog.migrationResults = migrationResults;
			migrationResultsDialog.DoModal();
		}
	}
}

void CLatticeRelaxationDoc::OnUpdateModelingResults(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(calculationFinished);
}

void CLatticeRelaxationDoc::OnExportResults() 
{
	// TODO: Add your command handler code here
	static char delimeter = ',';

	CFileDialog exportResultsDialog(FALSE);
	if (IDOK == exportResultsDialog.DoModal()) {
		CString fileName = exportResultsDialog.GetPathName();

		std::ofstream resultsFile(fileName,std::ios::out);

		if (NULL == modelingProject->migratingAtom) {
			
		} else {
			std::vector<MigrationStepResults>::iterator stepsIterator;
			std::vector<MigrationStepResults> steps = migrationResults.migrationStepResults;

			resultsFile << "X" << delimeter << "Y" << delimeter << "Z" << delimeter << "R" << delimeter << "E" << "\n";

			for (stepsIterator = steps.begin(); stepsIterator != steps.end(); stepsIterator++) {
				MigrationStepResults migrationStepResults = *stepsIterator;
				resultsFile << migrationStepResults.migratingAtomCoordinates.x / 2.86 << delimeter;
				resultsFile << migrationStepResults.migratingAtomCoordinates.y / 2.86 << delimeter;
				resultsFile << migrationStepResults.migratingAtomCoordinates.z / 2.86 << delimeter;
				resultsFile << migrationStepResults.migratingAtomCoordinates.getLength() / 10 << delimeter;
				resultsFile.precision(6);
				resultsFile << migrationStepResults.complexEnergyAfterRelaxation << "\n";
				resultsFile.precision(3);
			}
		}

		resultsFile.close();
	}
}

void CLatticeRelaxationDoc::OnUpdateExportResults(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(calculationFinished);
}
