// TankiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tanki.h"
#include "TankiDlg.h"
#include "Instrukcja.h"
#include "Credits.h"
#include "Gra.h"
#include ".\tankidlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTankiDlg dialog



CTankiDlg::CTankiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTankiDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTankiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTankiDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_INSTRUKCJA, OnBnClickedInstrukcja)
	ON_BN_CLICKED(IDC_CREDITS, OnBnClickedCredits)
	ON_BN_CLICKED(IDC_START, OnBnClickedStart)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CTankiDlg message handlers

BOOL CTankiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	WSADATA wsaData;
	int iResult = WSAStartup( MAKEWORD(2,2), &wsaData );
	if ( iResult != NO_ERROR )AfxMessageBox("Blad biblioteki");
	
///Inicjacja bitmapy ukazujacej tytulowy obrazek
    BITMAP BM_MENT;
	tyt.LoadBitmap(BM_TYTUL);
	tyt_maska.LoadBitmap(BM_TYTUL_MASK);
	tyt.GetObject(sizeof(BM_MENT),&BM_MENT);

    return TRUE;  // return TRUE  unless you set the focus to a control
	
}

void CTankiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

///rysuje tlo
void CTankiDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		///Wyswietlanie tytylowego obrazaka
CDC MemDC;
 CClientDC Kontekst(this);
MemDC.CreateCompatibleDC(&Kontekst);
 MemDC.SelectObject(&tyt_maska);
Kontekst.StretchBlt(0,0,516,344,&MemDC,0,0,516,344,SRCAND);
MemDC.SelectObject(&tyt);
Kontekst.StretchBlt(0,0,516,344,&MemDC,0,0,516,344,SRCINVERT);

		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTankiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


///wyswietla okno instrukcji
void CTankiDlg::OnBnClickedInstrukcja()
{
	CInstrukcja okno;///<okno instrukcji
	okno.DoModal();
}
///wyswietla okno creditsow
void CTankiDlg::OnBnClickedCredits()
{
	CCredits okno;///<okno creditsow
	okno.DoModal();
}

///uruchamia funkcje OnOK()
/**
*po wywolaniu funkcji OnOK() zostaje utworzone i zainicjowane okno gry jednak najpierw wyswietla sie okno wpisywania IP
*/
void CTankiDlg::OnBnClickedStart()
{
OnOK();
}
///zamyka program
void CTankiDlg::OnBnClickedCancel()
{
	exit(0);
}
