// LatticeRelaxation.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "LatticeRelaxation.h"

#include <AFXPRIV.H>

#include "MainFrm.h"
#include "LatticeRelaxationDoc.h"
#include "LatticeRelaxationTableView.h"
#include "LatticeRelaxationD3DView.h"

#include "LatticeRelaxationDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLatticeRelaxationApp

BEGIN_MESSAGE_MAP(CLatticeRelaxationApp, CWinApp)
	//{{AFX_MSG_MAP(CLatticeRelaxationApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_3DVIEW, On3dview)
	ON_UPDATE_COMMAND_UI(ID_3DVIEW, OnUpdate3dview)
	ON_COMMAND(ID_TABLEVIEW, OnTableview)
	ON_UPDATE_COMMAND_UI(ID_TABLEVIEW, OnUpdateTableview)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLatticeRelaxationApp construction

CLatticeRelaxationApp::CLatticeRelaxationApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	tableView = false;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CLatticeRelaxationApp object

CLatticeRelaxationApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CLatticeRelaxationApp initialization

BOOL CLatticeRelaxationApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CLatticeRelaxationDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CLatticeRelaxationD3DView));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	
	CView* pActiveView = ((CFrameWnd*) m_pMainWnd)->GetActiveView();
	m_pOldView = pActiveView;
	m_pNewView = (CView*) new CLatticeRelaxationTableView;

	CDocument* pCurrentDoc = ((CFrameWnd*)m_pMainWnd)->GetActiveDocument();

	// Initialize a CCreateContext to point to the active document.
	// With this context, the new view is added to the document
	// when the view is created in CView::OnCreate().
	CCreateContext newContext;
	newContext.m_pCurrentDoc = pCurrentDoc;

	// The ID of the initial active view is AFX_IDW_PANE_FIRST.
	// Incrementing this value by one for additional views works
	// in the standard document/view case but the technique cannot
	// be extended for the CSplitterWnd case.
	UINT viewID = AFX_IDW_PANE_FIRST + 1;
	CRect rect(0, 0, 0, 0); // Gets resized later.

	// Create the new view. In this example, the view persists for
	// the life of the application. The application automatically
	// deletes the view when the application is closed.
	m_pNewView->Create(NULL, "AnyWindowName", WS_CHILD, rect, m_pMainWnd, viewID, &newContext);
		
	// When a document template creates a view, the WM_INITIALUPDATE
	// message is sent automatically. However, this code must
	// explicitly send the message, as follows.
	m_pNewView->SendMessage(WM_INITIALUPDATE, 0, 0);

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	return TRUE;
}

CView* CLatticeRelaxationApp::SwitchView( )
{
   CView* pActiveView =
      ((CFrameWnd*) m_pMainWnd)->GetActiveView();

   CView* pNewView= NULL;
   if(pActiveView == m_pOldView) {
      pNewView= m_pNewView;
	  tableView = true;
	}
   else {
      pNewView= m_pOldView;
	  tableView = false;
	  }

   // Exchange view window IDs so RecalcLayout() works.
   #ifndef _WIN32
   UINT temp = ::GetWindowWord(pActiveView->m_hWnd, GWW_ID);
   ::SetWindowWord(pActiveView->m_hWnd, GWW_ID, ::GetWindowWord(pNewView->m_hWnd, GWW_ID));
   ::SetWindowWord(pNewView->m_hWnd, GWW_ID, temp);
   #else
   UINT temp = ::GetWindowLong(pActiveView->m_hWnd, GWL_ID);
   ::SetWindowLong(pActiveView->m_hWnd, GWL_ID, ::GetWindowLong(pNewView->m_hWnd, GWL_ID));
   ::SetWindowLong(pNewView->m_hWnd, GWL_ID, temp);
   #endif

   pActiveView->ShowWindow(SW_HIDE);
   pNewView->ShowWindow(SW_SHOW);
   ((CFrameWnd*) m_pMainWnd)->SetActiveView(pNewView);
   ((CFrameWnd*) m_pMainWnd)->RecalcLayout();
   pNewView->Invalidate();
   
   return pActiveView;
}



/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CLatticeRelaxationApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CLatticeRelaxationApp message handlers


void CLatticeRelaxationApp::On3dview() 
{
	SwitchView();
}

void CLatticeRelaxationApp::OnUpdate3dview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CView* pActiveView = ((CFrameWnd*) m_pMainWnd)->GetActiveView();

	pCmdUI->Enable(pActiveView != m_pOldView);
}

void CLatticeRelaxationApp::OnTableview() 
{
	// TODO: Add your command handler code here
	SwitchView();

}

void CLatticeRelaxationApp::OnUpdateTableview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CView* pActiveView = ((CFrameWnd*) m_pMainWnd)->GetActiveView();

	pCmdUI->Enable(pActiveView == m_pOldView);
}
