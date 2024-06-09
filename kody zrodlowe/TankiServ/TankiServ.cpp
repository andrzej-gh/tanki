// TankiServ.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TankiServ.h"
#include "TankiServDlg.h"
#include "serv.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTankiServApp

BEGIN_MESSAGE_MAP(CTankiServApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTankiServApp construction

CTankiServApp::CTankiServApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTankiServApp object

CTankiServApp theApp;


// CTankiServApp initialization

BOOL CTankiServApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	
	CTankiServDlg dlg;///<okienko tworzenia serwera
	INT_PTR nResponse = dlg.DoModal();
	if(dlg.fragi==NULL||dlg.fragi==0)exit(0);
	CSERV okno;///<okno serwera
	okno.map_id=dlg.map_id;
	okno.frag_limit=dlg.fragi;
	m_pMainWnd = &okno;
	okno.DoModal();

	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
