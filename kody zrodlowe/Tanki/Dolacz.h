#pragma once
#include "afxwin.h"


// CDolacz dialog
///klasa okna dolaczania do gry
class CDolacz : public CDialog
{
	DECLARE_DYNAMIC(CDolacz)

public:
	CDolacz(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDolacz();

// Dialog Data
	enum { IDD = IDD_DOLACZ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString nick;///<nick gracza
	afx_msg void OnBnClickedOk();
	char serv_ip[20];///<IP serwera
	int map_id;///<identyfikator mapy
	int frag_limit;///<liczba limitu fragow
	virtual BOOL OnInitDialog();
	BOOL kolor;///<kolor gracza
	afx_msg void OnPaint();
	//zmienna do ktorej przypisana jest bitmapa
	
	CBitmap rysuj_kolor; ///<Zmienna przypisana bitmapie wyboru koloru czolgow
	CBitmap rysuj_kolor_maska; ///<Zmienna przypisana bitmapie maski wyboru koloru czolgow
	
	///Rysuje bitmapki kolorow czolgow
	void RysujKoloryCzolgow(int x, int y, int z);
};
