// NeptunePublicGotoDlg.h : header file
//

#pragma once
#include "resource.h"


// CNeptunePublicGotoDlg dialog
class CNeptunePublicGotoDlg : public CDialog
{
// Construction
public:
	CNeptunePublicGotoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_NEPTUNEPUBLICGOTO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedButtonGoto();
	afx_msg void OnDestroy();
};
