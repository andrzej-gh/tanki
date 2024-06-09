#pragma once
#include "afxwin.h"


// CInstrukcja dialog
///klasa okna instrukcji
class CInstrukcja : public CDialog
{
	DECLARE_DYNAMIC(CInstrukcja)

public:
	CInstrukcja(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInstrukcja();

// Dialog Data
	enum { IDD = IDD_INSTRUKCJA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	///rysuje bitmape instrukcji
	afx_msg void OnPaint();
	CBitmap instrukcja;///<Zmienna przypisana bitmapie ukazujacej instrukcje gry
	CBitmap instrukcja_maska;///<Zmienna przypisana bitmapie maski ukazujacej instrukcje gry
};
