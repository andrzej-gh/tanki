#pragma once
#include "afxwin.h"


//!struktura sluzaca do wysylania informacji o tankach
struct STank
{
	int bm_id;///<id bitmapy
	int tank_id;///<id czolgu (id koloru)
	float x, y;///<wspolrzedne
 int score;///<ilosc zdobytych fragow
 int HP;///<ilosc zycia
 int armor;///<ilosc pancerza
 int weapon_id;///<id broni
 int iloscM, iloscL;///<ilosc min oraz lasera
 int speed_time;///<czas bonusowego speeda
 float speed;///<zmienna pomocnicza do obliczania speeda
};

class CWYNIKI : public CDialog
{
	DECLARE_DYNAMIC(CWYNIKI)

public:
	CWYNIKI(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWYNIKI();

// Dialog Data
	enum { IDD = IDD_WYNIKI };
	STank player[12];///<tablica graczy

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	CBitmap czolg_id;///<Zmienna przypisana bitmapie czolgu id
    CBitmap czolg_id_maska;///<Zmienna przypisana masce bitmapy czolgu id
	CBitmap miejsce;
   
	void WyswietlKolorCzolguId(int x, int y, int z);
	int player_idx;///<ilosc graczy w grze
};
