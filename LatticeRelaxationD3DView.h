#if !defined(AFX_LATTICERELAXATIOND3DVIEW_H__926F2F2C_ED82_4214_8021_6558FC71325D__INCLUDED_)
#define AFX_LATTICERELAXATIOND3DVIEW_H__926F2F2C_ED82_4214_8021_6558FC71325D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LatticeRelaxationD3DView.h : header file
//

#include <map>

#include "Direct3DView.h"
#include "Atom.h"

/////////////////////////////////////////////////////////////////////////////
// CLatticeRelaxationD3DView view

class CLatticeRelaxationD3DView : public CScrollView, public Direct3DView
{
protected:
	DECLARE_DYNCREATE(CLatticeRelaxationD3DView)

// Attributes
public:
	CLatticeRelaxationDoc* GetDocument();

// Operations
public:
	void BuildAtomMeshes();
	CLatticeRelaxationD3DView();

protected:
    void RenderScene();
    std::map<Atom*, LPD3DXMESH> atomMeshes;

    float rotationX;
    float rotationY;
    CPoint clickPoint;
    float cameraX;
    float cameraY;
    float cameraZ;
	bool initialized;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLatticeRelaxationD3DView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnUpdateIndicatorAtomX(CCmdUI* pCmdUI);
	void OnUpdateIndicatorAtomY(CCmdUI* pCmdUI);
	void OnUpdateIndicatorAtomZ(CCmdUI* pCmdUI);
	virtual void editAtom(Atom* atom);
	Atom* mouseDownAtom;
	Atom* mouseUpAtom;
	Atom* selectedAtom;
	virtual Atom* getAtomFromPoint(CPoint point);
	virtual ~CLatticeRelaxationD3DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CLatticeRelaxationD3DView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDeleteAtomButton();
	afx_msg void OnEditButtonAtom();
	afx_msg void OnUpdateDeleteAtomButton(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditButtonAtom(CCmdUI* pCmdUI);
	afx_msg void OnMigrateAtomButton();
	afx_msg void OnUpdateMigrateAtomButton(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LatticeModellingView.cpp
inline CLatticeRelaxationDoc* CLatticeRelaxationD3DView::GetDocument()
   { return (CLatticeRelaxationDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LATTICERELAXATIOND3DVIEW_H__926F2F2C_ED82_4214_8021_6558FC71325D__INCLUDED_)
