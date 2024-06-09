// TankiServDlg.h : header file
//

#pragma once
#include "afxwin.h"



//! klasa okienka tworzenia sewera
class CTankiServDlg : public CDialog
{
// Construction
public:
	CTankiServDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TANKISERV_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	///funkcja wyjscia z programu
	afx_msg void OnBnClickedCancel();
	int fragi;///<przechowuje limit fragow
	///funkcja aktualizacji danych
	/**
	*aktualizuje dane i zamyka okno
	*/
	afx_msg void OnBnClickedOk();
	///funkcja wyboru mapy
	/**
	*tworzy okienko wyboru mapy i po jego zamknieciu kopjuje id mapy
	*/
	afx_msg void OnBnClickedMapa();
	int map_id;///<przechowuje id mapy
};
