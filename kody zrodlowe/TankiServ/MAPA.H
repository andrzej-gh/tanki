#pragma once


// CMAPA dialog

//! klasa okienka wyboru mapy
class CMAPA : public CDialog
{
	DECLARE_DYNAMIC(CMAPA)

public:
	CMAPA(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMAPA();

// Dialog Data
	enum { IDD = IDD_MAPA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL mapa;///<zmienna przechowujaca ktoramapa zostala wybrana
	///funkcja aktualizujaca dane i zamykajaca okienko
	afx_msg void OnBnClickedOk();
};
