#pragma once


// CCIP dialog
///klasa okna wpisywania IP
class CCIP : public CDialog
{
	DECLARE_DYNAMIC(CCIP)

public:
	CCIP(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCIP();

// Dialog Data
	enum { IDD = IDD_IP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString serv_ip;///<IP sewrera
	afx_msg void OnBnClickedOk();
};
