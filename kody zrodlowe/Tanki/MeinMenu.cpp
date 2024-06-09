// MeinMenu.cpp : implementation file
//

#include "stdafx.h"
#include "Tanki.h"
#include "MeinMenu.h"
#include "Instrukcja.h"
#include "Credits.h"
#include ".\meinmenu.h"


// CMeinMenu dialog

IMPLEMENT_DYNAMIC(CMeinMenu, CDialog)
CMeinMenu::CMeinMenu(CWnd* pParent /*=NULL*/)
	: CDialog(CMeinMenu::IDD, pParent)
{
}

CMeinMenu::~CMeinMenu()
{
}

void CMeinMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMeinMenu, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_INSTRUKCJA, OnBnClickedInstrukcja)
	ON_BN_CLICKED(IDC_CREDITS, OnBnClickedCredits)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CMeinMenu message handlers
///powrot do gry
void CMeinMenu::OnBnClickedOk()
{
	OnOK();
}
///wyswietla okno instrukcji
void CMeinMenu::OnBnClickedInstrukcja()
{
	CInstrukcja okno;///<okno instrukcji
	okno.DoModal();
}
///wyswietla okno creditsow
void CMeinMenu::OnBnClickedCredits()
{
	CCredits okno;///<okno creditsow
	okno.DoModal();
}
///zamyka program
void CMeinMenu::OnBnClickedCancel()
{
exit(0);
}
