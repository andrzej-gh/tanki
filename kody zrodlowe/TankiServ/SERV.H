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
	int map_id; ///<zminna przechowuj¹ca indeks mapy, na której odbywa siê rozgrywka
	int frag_limit; ///<zmienna przechowuj¹ca liczbê fragów które trzeba zdobyæ aby wygraæ
	char up_id; ///<zmienna do której wczytywana jest odebrany od klijêta symbol operacji któr¹ chce wykonaæ
	afx_msg void OnTimer(UINT nIDEvent);
	CListBox gracze; ///<zmienna steruj¹ca list¹ graczy
	CListBox lista_czat; ///<zmienna steruj¹ca list¹ czatu
	virtual BOOL OnInitDialog();
//!funkcja zamykajaca program
	afx_msg void OnBnClickedCancel();
};
