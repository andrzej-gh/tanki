// Instrukcja.cpp : implementation file
//

#include "stdafx.h"
#include "Tanki.h"
#include "Instrukcja.h"
#include ".\instrukcja.h"


// CInstrukcja dialog

IMPLEMENT_DYNAMIC(CInstrukcja, CDialog)
CInstrukcja::CInstrukcja(CWnd* pParent /*=NULL*/)
	: CDialog(CInstrukcja::IDD, pParent)
{
}

CInstrukcja::~CInstrukcja()
{
}

void CInstrukcja::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInstrukcja, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CInstrukcja message handlers

BOOL CInstrukcja::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
///Inicjacja bitmapy wyswietlajacej instrukcje
	 BITMAP BM_INSTRUKCJA;
	instrukcja.LoadBitmap(BM_INSTRUCT);
	instrukcja_maska.LoadBitmap(BM_INSTRUCT_MASk);
	instrukcja.GetObject(sizeof(BM_INSTRUKCJA),&BM_INSTRUKCJA);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CInstrukcja::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	///Wyswietlanie bitmapy ukazujacej instrukcje gry
	CDC MemDC_INSTRUCT;
    CClientDC Kontekst_Instrukcja(this);
    MemDC_INSTRUCT.CreateCompatibleDC(&Kontekst_Instrukcja);
    MemDC_INSTRUCT.SelectObject(&instrukcja_maska);
    Kontekst_Instrukcja.StretchBlt(0,0,600,399,&MemDC_INSTRUCT,0,0,600,399,SRCAND);
	MemDC_INSTRUCT.SelectObject(&instrukcja);
    Kontekst_Instrukcja.StretchBlt(0,0,600,399,&MemDC_INSTRUCT,0,0,600,399,SRCINVERT);



	// Do not call CDialog::OnPaint() for painting messages
}
