// LatticeRelaxationDoc.h : interface of the CLatticeRelaxationDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LATTICERELAXATIONDOC_H__F9B665FC_6BF9_4950_97FF_673F12F28A40__INCLUDED_)
#define AFX_LATTICERELAXATIONDOC_H__F9B665FC_6BF9_4950_97FF_673F12F28A40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Lattice.h"
#include "Potential.h"	// Added by ClassView
#include "ModelingProject.h"
#include "ModelingOptions.h"
#include "MigrationResults.h"

class CLatticeRelaxationDoc : public CDocument
{
protected: // create from serialization only
	CLatticeRelaxationDoc();
	DECLARE_DYNCREATE(CLatticeRelaxationDoc)

// Attributes
public:
	CCriticalSection m_CS;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLatticeRelaxationDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	ModelingProject* modelingProject;
	ModelingOptions modelingOptions;

	MigrationResults migrationResults;
	RelaxationResults relaxationResults;
	bool calculationFinished;

	//Lattice* lattice;
	//Potential potential;
	//bool potentialLoaded;

	enum ModelingThreadState {
		STARTING,
		RESUMING,
		STARTED,
		SUSPENDING,
		SUSPENDED,
		STOPPING,
		STOPPED
	} modelingThreadState;

	virtual ~CLatticeRelaxationDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CWinThread* relaxationThread;
	//{{AFX_MSG(CLatticeRelaxationDoc)
	afx_msg void OnStartRelaxation();
	afx_msg void OnSelectPotential();
	afx_msg void OnRefresh();
	afx_msg void OnAtomTypes();
	afx_msg void OnStopRelaxation();
	afx_msg void OnPauseRelaxation();
	afx_msg void OnUpdateStopRelaxation(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStartRelaxation(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePauseRelaxation(CCmdUI* pCmdUI);
	afx_msg void OnAddAtomButton();
	afx_msg void OnModelingOptions();
	afx_msg void OnMigrateAtomButton();
	afx_msg void OnUpdateMigrateAtomButton(CCmdUI* pCmdUI);
	afx_msg void OnCalculateForces();
	afx_msg void OnModelingResults();
	afx_msg void OnUpdateModelingResults(CCmdUI* pCmdUI);
	afx_msg void OnExportResults();
	afx_msg void OnUpdateExportResults(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LATTICERELAXATIONDOC_H__F9B665FC_6BF9_4950_97FF_673F12F28A40__INCLUDED_)
