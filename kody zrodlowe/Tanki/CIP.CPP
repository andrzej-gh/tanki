// CIP.cpp : implementation file
//

#include "stdafx.h"
#include "Tanki.h"
#include "CIP.h"
#include ".\cip.h"


// CCIP dialog

IMPLEMENT_DYNAMIC(CCIP, CDialog)
CCIP::CCIP(CWnd* pParent /*=NULL*/)
	: CDialog(CCIP::IDD, pParent)
	, serv_ip(_T(""))
{
}

CCIP::~CCIP()
{
}

void CCIP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, serv_ip);
}


BEGIN_MESSAGE_MAP(CCIP, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CCIP message handlers
///aktualizuje dane i zamyka okno
void CCIP::OnBnClickedOk()
{
	UpdateData(true);
	OnOK();
}
