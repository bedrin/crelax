// LatticeRelaxationTableView.cpp : implementation of the CLatticeRelaxationTableView class
//

#include "stdafx.h"
#include "LatticeRelaxation.h"

#include "LatticeRelaxationDoc.h"
#include "LatticeRelaxationTableView.h"

#include "AtomDialog.h"
#include "MigrateAtomDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLatticeRelaxationView

IMPLEMENT_DYNCREATE(CLatticeRelaxationTableView, CListView)

BEGIN_MESSAGE_MAP(CLatticeRelaxationTableView, CListView)
	//{{AFX_MSG_MAP(CLatticeRelaxationTableView)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_COMMAND(ID_MIGRATE_ATOM_BUTTON, OnMigrateAtomButton)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLatticeRelaxationView construction/destruction

CLatticeRelaxationTableView::CLatticeRelaxationTableView()
{
	// TODO: add construction code here
	initialized = false;
}

CLatticeRelaxationTableView::~CLatticeRelaxationTableView()
{
}

BOOL CLatticeRelaxationTableView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLatticeRelaxationTableView drawing

void CLatticeRelaxationTableView::OnDraw(CDC* pDC)
{
	CLatticeRelaxationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CLatticeRelaxationTableView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CListCtrl& refCtrl = GetListCtrl();
    
	long controlStyle = GetWindowLong(refCtrl.m_hWnd, GWL_STYLE);
	controlStyle |= LVS_REPORT;
	SetWindowLong(refCtrl.m_hWnd, GWL_STYLE, controlStyle);

	refCtrl.SetExtendedStyle(refCtrl.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT );

	CreateTableItems();

}

/////////////////////////////////////////////////////////////////////////////
// CLatticeRelaxationTableView printing

BOOL CLatticeRelaxationTableView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLatticeRelaxationTableView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLatticeRelaxationTableView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CLatticeRelaxationView diagnostics

#ifdef _DEBUG
void CLatticeRelaxationTableView::AssertValid() const
{
	//CListView::AssertValid();
}

void CLatticeRelaxationTableView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CLatticeRelaxationDoc* CLatticeRelaxationTableView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLatticeRelaxationDoc)));
	return (CLatticeRelaxationDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLatticeRelaxationTableView message handlers

void CLatticeRelaxationTableView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CLatticeRelaxationApp* app = (CLatticeRelaxationApp*)AfxGetApp();
	if (!app->tableView) return;

	CLatticeRelaxationDoc* doc = GetDocument();

	CSingleLock csl(&(doc->m_CS));
	csl.Lock();

	if (1 == lHint) {
		CreateTableItems();
	} else {
		UpdateTableItems();
	}
	
	csl.Unlock();
		
}

void CLatticeRelaxationTableView::CreateTableItems()
{
	CListCtrl& refCtrl = GetListCtrl();

	refCtrl.DeleteAllItems();
			
	if (!initialized) {
		refCtrl.InsertColumn(0,"Position X");
		refCtrl.SetColumnWidth(0,75);
		refCtrl.InsertColumn(1,"Position Y");
		refCtrl.SetColumnWidth(1,75);
		refCtrl.InsertColumn(2,"Position Z");
		refCtrl.SetColumnWidth(2,75);
		refCtrl.InsertColumn(3,"Force X");
		refCtrl.SetColumnWidth(3,75);
		refCtrl.InsertColumn(4,"Force Y");
		refCtrl.SetColumnWidth(4,75);
		refCtrl.InsertColumn(5,"Force Z");
		refCtrl.SetColumnWidth(5,75);
		refCtrl.InsertColumn(6,"Atom Type");
		refCtrl.SetColumnWidth(6,75);
		refCtrl.InsertColumn(7,"Mobile");
		refCtrl.SetColumnWidth(7,75);
		refCtrl.InsertColumn(8,"Representable");
		refCtrl.SetColumnWidth(8,100);
		initialized = true;
	}
	
	CLatticeRelaxationDoc* doc = GetDocument();
	Lattice* lattice = doc->modelingProject->activeLattice;
	std::deque<Atom*>& atoms = lattice->atoms;

	if (!atoms.empty()) {
		std::deque<Atom*>::iterator atomsIterator;

		int i = 0;

		for (atomsIterator = atoms.begin(); atomsIterator != atoms.end(); atomsIterator++) {
			Atom* atom = *atomsIterator;
			CString str;

			str.Format(TEXT("%f %f %f"),atom->r.x, atom->r.y, atom->r.z);
			refCtrl.InsertItem(i, str);
			refCtrl.SetItemData(i, reinterpret_cast<DWORD>(atom));
			
			str.Format(TEXT("%f"),atom->r.x / 2.86);
			refCtrl.SetItemText(i,0, str);
			
			str.Format(TEXT("%f"),atom->r.y / 2.86);
			refCtrl.SetItemText(i,1, str);

			str.Format(TEXT("%f"),atom->r.z / 2.86);
			refCtrl.SetItemText(i,2, str);

			str.Format(TEXT("%f"),atom->v.x);
			refCtrl.SetItemText(i,3, str);
					
			str.Format(TEXT("%f"),atom->v.y);
			refCtrl.SetItemText(i,4, str);

			str.Format(TEXT("%f"),atom->v.z);
			refCtrl.SetItemText(i,5, str);

			refCtrl.SetItemText(i,6, atom->atomType->name);

			if (atom->moveable) {
				refCtrl.SetItemText(i,7, "Yes");
			} else {
				refCtrl.SetItemText(i,7, "No");
			}

			if (atom->visible) {
				refCtrl.SetItemText(i,8, "Yes");
			} else {
				refCtrl.SetItemText(i,8, "No");
			}

			i++;
		}

	}

}

void CLatticeRelaxationTableView::UpdateTableItems()
{
	CListCtrl& refCtrl = GetListCtrl();

	int itemCount = refCtrl.GetItemCount();

	for (int i = 0; i < itemCount; i++) {
		DWORD itemData = refCtrl.GetItemData(i);
		Atom* atom = reinterpret_cast<Atom*> (itemData);

		CString str;

		str.Format(TEXT("%f"),atom->r.x / 2.86);
		refCtrl.SetItemText(i,0, str);
		
		str.Format(TEXT("%f"),atom->r.y / 2.86);
		refCtrl.SetItemText(i,1, str);

		str.Format(TEXT("%f"),atom->r.z / 2.86);
		refCtrl.SetItemText(i,2, str);

		str.Format(TEXT("%f"),atom->v.x);
		refCtrl.SetItemText(i,3, str);
				
		str.Format(TEXT("%f"),atom->v.y);
		refCtrl.SetItemText(i,4, str);

		str.Format(TEXT("%f"),atom->v.z);
		refCtrl.SetItemText(i,5, str);

		refCtrl.SetItemText(i,6, atom->atomType->name);

		if (atom->moveable) {
			refCtrl.SetItemText(i,7, "Yes");
		} else {
			refCtrl.SetItemText(i,7, "No");
		}

		if (atom->visible) {
			refCtrl.SetItemText(i,8, "Yes");
		} else {
			refCtrl.SetItemText(i,8, "No");
		}

	}

}

void CLatticeRelaxationTableView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CListCtrl& refCtrl = GetListCtrl();

	int selectedAtomIndex = refCtrl.GetSelectionMark();

	DWORD itemData = refCtrl.GetItemData(selectedAtomIndex);
	Atom* atom = reinterpret_cast<Atom*> (itemData);

	editAtom(atom);

	*pResult = 0;
}

void CLatticeRelaxationTableView::editAtom(Atom *atom)
{
	AtomDialog atomDialog;
		
	atomDialog.m_positionX = atom->r.x;
	atomDialog.m_positionY = atom->r.y;
	atomDialog.m_positionZ = atom->r.z;

	atomDialog.m_forceX = atom->v.x;
	atomDialog.m_forceY = atom->v.y;
	atomDialog.m_forceZ = atom->v.z;

	atomDialog.m_Moveable = atom->moveable;
	atomDialog.m_Visible = atom->visible;

	atomDialog.atomType = atom->atomType;

	GetDocument()->modelingProject->populateAtomTypes();
	atomDialog.atomTypes = GetDocument()->modelingProject->atomTypes;

	if (IDOK == atomDialog.DoModal()) {
		atom->r.x = atomDialog.m_positionX;
		atom->r.y = atomDialog.m_positionY;
		atom->r.z = atomDialog.m_positionZ;

		atom->v.x = atomDialog.m_forceX;
		atom->v.y = atomDialog.m_forceY;
		atom->v.z = atomDialog.m_forceZ;

		atom->moveable = atomDialog.m_Moveable;
		atom->visible = atomDialog.m_Visible;

		atom->atomType = atomDialog.atomType;

		//OnUpdate(this,1,NULL);
		GetDocument()->UpdateAllViews(this,1,NULL);

	}
}

void CLatticeRelaxationTableView::OnMigrateAtomButton() 
{
	// TODO: Add your command handler code here
	CLatticeRelaxationDoc* doc = GetDocument();

	if ((NULL != doc->modelingProject->migratingAtom) && (doc->modelingProject->migratingAtom != selectedAtom)) {
		if (!(IDYES == AfxMessageBox("You've already selected an atom to migrate. Are you sure you want to migrate this one instead?",MB_YESNO))) {
			return;
		}
	}
	
	MigrateAtomDialog migrateAtomDialog;
	if (doc->modelingProject->migratingAtom == selectedAtom) {
		migrateAtomDialog.m_x = doc->modelingProject->migratingToPoint.x / 2.86;
		migrateAtomDialog.m_y = doc->modelingProject->migratingToPoint.y / 2.86;
		migrateAtomDialog.m_z = doc->modelingProject->migratingToPoint.z / 2.86;
		migrateAtomDialog.m_migrationSteps = doc->modelingProject->migratingSteps;
	}

	if (IDOK == migrateAtomDialog.DoModal()) {
		doc->modelingProject->migratingToPoint.x = migrateAtomDialog.m_x * 2.86;
		doc->modelingProject->migratingToPoint.y = migrateAtomDialog.m_y * 2.86;
		doc->modelingProject->migratingToPoint.z = migrateAtomDialog.m_z * 2.86;
		doc->modelingProject->migratingSteps = migrateAtomDialog.m_migrationSteps;
		doc->modelingProject->migratingAtom = selectedAtom;
	}	
}
