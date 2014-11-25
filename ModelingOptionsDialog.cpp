// ModelingOptionsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "LatticeRelaxation.h"
#include "ModelingOptionsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ModelingOptionsDialog dialog


ModelingOptionsDialog::ModelingOptionsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(ModelingOptionsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(ModelingOptionsDialog)
	m_useEmbeddedAtomMethod = FALSE;
	m_differentialStep = 0.0;
	m_maximumInteractionDistance = 0.0;
	m_maximumNumberOfDemphings = 0;
	m_maximumNumberOfSteps = 0;
	m_maximumTimeDelta = 0.0;
	m_mimimumKineticEnergy = 0.0;
	m_startTimeDelta = 0.0;
	m_timeDeltaIncrement = 0.0;
	m_calculateDilatationVolume = FALSE;
	m_bulkModulus = 0.0;
	m_elasticCorrectionsAmmount = 0;
	m_dampingEnabled = FALSE;
	//}}AFX_DATA_INIT
}


void ModelingOptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ModelingOptionsDialog)
	DDX_Check(pDX, IDC_CHECK_USE_EMBEDDED_ATOM_METHOD, m_useEmbeddedAtomMethod);
	DDX_Text(pDX, IDC_EDIT_DIFFERENTIAL_STEP, m_differentialStep);
	DDX_Text(pDX, IDC_EDIT_MAXIMUM_INTERACTION_DISTANCE, m_maximumInteractionDistance);
	DDX_Text(pDX, IDC_EDIT_MAXIMUM_NUMBER_OF_DEMPHINGS, m_maximumNumberOfDemphings);
	DDX_Text(pDX, IDC_EDIT_MAXIMUM_NUMBER_OF_STEPS, m_maximumNumberOfSteps);
	DDX_Text(pDX, IDC_EDIT_MAXIMUM_TIME_DELTA, m_maximumTimeDelta);
	DDX_Text(pDX, IDC_EDIT_MIMIMUM_KINETIC_ENERGY, m_mimimumKineticEnergy);
	DDX_Text(pDX, IDC_EDIT_START_TIME_DELTA, m_startTimeDelta);
	DDX_Text(pDX, IDC_EDIT_TIME_DELTA_INCREMENT, m_timeDeltaIncrement);
	DDX_Check(pDX, IDC_CHECK_USE_DILATATION_VOLUME_CORRECTION, m_calculateDilatationVolume);
	DDX_Text(pDX, IDC_EDIT_BULK_MODULUS, m_bulkModulus);
	DDX_Text(pDX, IDC_EDIT_ELASTIC_CORRECTIONS_AMMOUNT, m_elasticCorrectionsAmmount);
	DDX_Check(pDX, IDC_CHECK_DAMPING_ENABLED, m_dampingEnabled);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ModelingOptionsDialog, CDialog)
	//{{AFX_MSG_MAP(ModelingOptionsDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ModelingOptionsDialog message handlers
