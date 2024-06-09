// TankiDlg.h : header file
//

#pragma once
#include "afxwin.h"


///klasa menu glownego
class CTankiDlg : public CDialog
{
// Construction
public:
	CTankiDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TANKI_DIALOG };

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
	afx_msg void OnBnClickedInstrukcja();
	afx_msg void OnBnClickedCredits();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedCancel();
	CBitmap tyt;  ///<Zmienna przypisana bitmapie ukazujacej tytylowy obrazek
    CBitmap tyt_maska;  ///<Zmienna przypisana bitmapie maske ukazujacej tytylowy obrazek
};
