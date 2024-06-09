#pragma once
#include "afxwin.h"


// CCzat dialog
///klasa okienka czatu
class CCzat : public CDialog
{
	DECLARE_DYNAMIC(CCzat)

public:
	CCzat(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCzat();

// Dialog Data
	enum { IDD = IDD_CZAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString tekst;///<wiadomosc jaka chcemy wyslac
	afx_msg void OnBnClickedOk();
	char serv_ip[20];///<IP serwera
	CListBox lista_czat;///<lista wiadomosci czatu
//	afx_msg void OnTimer(UINT nIDEvent);
	char nick[20];///<nick gracza
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
};
