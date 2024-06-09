// Credits.cpp : implementation file
//

#include "stdafx.h"
#include "Tanki.h"
#include "Credits.h"
#include ".\credits.h"


// CCredits dialog

IMPLEMENT_DYNAMIC(CCredits, CDialog)
CCredits::CCredits(CWnd* pParent /*=NULL*/)
	: CDialog(CCredits::IDD, pParent)
{
}

CCredits::~CCredits()
{
}

void CCredits::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCredits, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CCredits message handlers



BOOL CCredits::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	//Inicjacja bitmapy wyswietlajacej credits
    BITMAP BM_ZASLUGI;
	zaslugi.LoadBitmap(BM_CREDITS);
	zaslugi.GetObject(sizeof(BM_ZASLUGI),&BM_ZASLUGI);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
///wyswietla bitmape creditsow
void CCredits::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
///Wyswietlanie bitmapy creditsow
CDC MemDC_CREDITS;
CClientDC Kontekst_Zaslugi(this);
MemDC_CREDITS.CreateCompatibleDC(&Kontekst_Zaslugi);
MemDC_CREDITS.SelectObject(&zaslugi);
Kontekst_Zaslugi.StretchBlt(0,0,500,318,&MemDC_CREDITS,0,0,500,318,SRCAND);


	// Do not call CDialog::OnPaint() for painting messages
}
