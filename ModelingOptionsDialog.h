#if !defined(AFX_MODELINGOPTIONSDIALOG_H__847EE960_517E_4B42_9D31_8D5549BF5952__INCLUDED_)
#define AFX_MODELINGOPTIONSDIALOG_H__847EE960_517E_4B42_9D31_8D5549BF5952__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModelingOptionsDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ModelingOptionsDialog dialog

class ModelingOptionsDialog : public CDialog
{
// Construction
public:
	ModelingOptionsDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ModelingOptionsDialog)
	enum { IDD = IDD_MODELING_OPTIONS_DIALOG };
	BOOL	m_useEmbeddedAtomMethod;
	double	m_differentialStep;
	double	m_maximumInteractionDistance;
	int		m_maximumNumberOfDemphings;
	long	m_maximumNumberOfSteps;
	double	m_maximumTimeDelta;
	double	m_mimimumKineticEnergy;
	double	m_startTimeDelta;
	double	m_timeDeltaIncrement;
	BOOL	m_calculateDilatationVolume;
	double	m_bulkModulus;
	int		m_elasticCorrectionsAmmount;
	BOOL	m_dampingEnabled;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ModelingOptionsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ModelingOptionsDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODELINGOPTIONSDIALOG_H__847EE960_517E_4B42_9D31_8D5549BF5952__INCLUDED_)
