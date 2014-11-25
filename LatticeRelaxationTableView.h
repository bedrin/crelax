// LatticeRelaxationTableView.h : interface of the CLatticeRelaxationTableView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LATTICERELAXATIONTABLEVIEW_H__3A9CFA27_E66B_4484_B2AC_FE30FB151F04__INCLUDED_)
#define AFX_LATTICERELAXATIONTABLEVIEW_H__3A9CFA27_E66B_4484_B2AC_FE30FB151F04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLatticeRelaxationTableView : public CListView
{
protected: // create from serialization only
	
	DECLARE_DYNCREATE(CLatticeRelaxationTableView)

// Attributes
public:
	CLatticeRelaxationTableView();
	CLatticeRelaxationDoc* GetDocument();
	Atom* selectedAtom;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLatticeRelaxationTableView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdateTableItems();
	void CreateTableItems();
	virtual ~CLatticeRelaxationTableView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	virtual void editAtom(Atom* atom);
	//{{AFX_MSG(CLatticeRelaxationTableView)
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMigrateAtomButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool initialized;
};

#ifndef _DEBUG  // debug version in LatticeRelaxationView.cpp
inline CLatticeRelaxationDoc* CLatticeRelaxationTableView::GetDocument()
   { return (CLatticeRelaxationDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LATTICERELAXATIONTABLEVIEW_H__3A9CFA27_E66B_4484_B2AC_FE30FB151F04__INCLUDED_)
