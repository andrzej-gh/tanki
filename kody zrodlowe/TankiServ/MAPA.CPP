// MAPA.cpp : implementation file
//

#include "stdafx.h"
#include "TankiServ.h"
#include "MAPA.h"
#include ".\mapa.h"


// CMAPA dialog

IMPLEMENT_DYNAMIC(CMAPA, CDialog)
CMAPA::CMAPA(CWnd* pParent /*=NULL*/)
	: CDialog(CMAPA::IDD, pParent)
	, mapa(FALSE)
{
}

CMAPA::~CMAPA()
{
}

void CMAPA::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_MAP1, mapa);
}


BEGIN_MESSAGE_MAP(CMAPA, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CMAPA message handlers

void CMAPA::OnBnClickedOk()
{
	UpdateData(true);
	OnOK();
}
