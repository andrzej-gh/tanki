#pragma once
#include "afxwin.h"


// CGra dialog
///klasa okna gry
class CGra : public CDialog
{
	DECLARE_DYNAMIC(CGra)
friend UINT watek_paint(LPVOID params);
public:
	CGra(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGra();

// Dialog Data
	enum { IDD = IDD_GRA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

//	afx_msg void OnTimer(UINT nIDEvent);
//	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	UINT watek_paint(LPVOID params);
	int tank_id;///<identyfikator czolgu gracza
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();

	  CBitmap trawa;///<Zmienna przypisana bitmapie trawy
	  CBitmap trawa_maska;///<Zmienna przypisana bitmapie maski trawy

	CBitmap czolg;///<Zmienna przypisana bitmapie czolgu
	
	CBitmap czolg_maska;///<Zmienna przypisana bitmapie maski czolgu
	
	CBitmap objekt;///<Zmienna przypisana bitmapie obiektu wody gory drzewa
	
	CBitmap objekt_maska;///<Zmienna przypisana bitmapie maski obiektu wody gory drzewa
	CBitmap premia;///<Zmienna przypisana bitmapie bonusow
	CBitmap premia_maska;///<Zmienna przypisana bitmapie maski bonusow
	CBitmap pociski;///<Zmienna przypisana bitmapie rakiet oraz lasera
	CBitmap pociski_maska;///<Zmienna przypisana bitmapie maski rakiet oraz lasera
	CBitmap menu_dol;///<Zmienna przypisana bitmapie tla menu dolnego
    CBitmap menu_dol_maska; ///<Zmienna przypisana bitmapie maski tla menu dolnego
	CBitmap menu_gora;///<Zmienna przypisana bitmapie tla menu gornego
    CBitmap menu_gora_maska;///<Zmienna przypisana bitmapie maski tla menu gornego
	CBitmap menl;///<Zmienna przypisana bitmapie zmiennych uzywanych w menu cyfry oraz ikony broni
    CBitmap menl_maska;///<Zmienna przypisana bitmapie maski zmiennych uzywanych w menu cyfry oraz ikony broni
	CBitmap czolg_id;///<Zmienna przypisana bitmapie ikonie czolgu id
    CBitmap czolg_id_maska;///<Zmienna przypisana bitmapie maski ikonie czolgu id

	char nick[20];///<przechowuje nick gracza
	void RysujZmienneMen(int x, int y, int z);
	void WyswietlKolorCzolguId(int x, int y, int z);
};