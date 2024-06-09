#pragma once


// CMeinMenu dialog
///klasa okna menu gry
class CMeinMenu : public CDialog
{
	DECLARE_DYNAMIC(CMeinMenu)

public:
	CMeinMenu(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMeinMenu();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedInstrukcja();
	afx_msg void OnBnClickedCredits();
	afx_msg void OnBnClickedCancel();
};
