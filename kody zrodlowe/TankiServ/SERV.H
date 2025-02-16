#pragma once
#include "afxwin.h"


// CSERV dialog
//! klasa okienka servera
class CSERV : public CDialog
{
	DECLARE_DYNAMIC(CSERV)

public:
	CSERV(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSERV();

// Dialog Data
	enum { IDD = IDD_SERV };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int map_id; ///<zminna przechowuj�ca indeks mapy, na kt�rej odbywa si� rozgrywka
	int frag_limit; ///<zmienna przechowuj�ca liczb� frag�w kt�re trzeba zdoby� aby wygra�
	char up_id; ///<zmienna do kt�rej wczytywana jest odebrany od klij�ta symbol operacji kt�r� chce wykona�
	afx_msg void OnTimer(UINT nIDEvent);
	CListBox gracze; ///<zmienna steruj�ca list� graczy
	CListBox lista_czat; ///<zmienna steruj�ca list� czatu
	virtual BOOL OnInitDialog();
//!funkcja zamykajaca program
	afx_msg void OnBnClickedCancel();
};
