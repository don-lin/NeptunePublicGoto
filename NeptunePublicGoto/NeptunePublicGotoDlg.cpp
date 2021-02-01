// NeptunePublicGotoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NeptunePublicGoto.h"
#include "NeptunePublicGotoDlg.h"
#include "NeptunePublicWrap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNeptunePublicGotoDlg dialog



CNeptunePublicGotoDlg::CNeptunePublicGotoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNeptunePublicGotoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNeptunePublicGotoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNeptunePublicGotoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnBnClickedConnect)
	ON_BN_CLICKED(IDC_BUTTON_GOTO, OnBnClickedButtonGoto)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CNeptunePublicGotoDlg message handlers

BOOL CNeptunePublicGotoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNeptunePublicGotoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNeptunePublicGotoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CNeptunePublicGotoDlg::OnBnClickedConnect()
{
	if(CNeptunePublicWrap::CreateNeptunePublicComPtr())
	{
		SetWindowText(_T("Connect to Neptune public server succeed!"));
		GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_GOTO)->EnableWindow(TRUE);
	}
	else
	{
		SetWindowText(_T("Connect to Neptune public server failed!"));
		GetDlgItem(IDC_BUTTON_GOTO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
	}
}

void CNeptunePublicGotoDlg::OnBnClickedButtonGoto()
{
	CString strX,strY,strZ;
	GetDlgItem(IDC_EDIT_X)->GetWindowText(strX);
	GetDlgItem(IDC_EDIT_Y)->GetWindowText(strY);
	GetDlgItem(IDC_EDIT_Z)->GetWindowText(strZ);

	double x,y,z;
	x = atof(strX);
	y = atof(strY);
	z = atof(strZ);

	if(CNeptunePublicWrap::MachineGoto(x,y,z))
	{
		CString strMsg;
		strMsg.Format(_T("Machine goto (%.6f, %.6f, %.6f) failed!"),x,y,z);
		AfxMessageBox(strMsg);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_GOTO)->EnableWindow(FALSE);

		while(true)
		{
			MSG message;	
			while (PeekMessage(&message,NULL,NULL,NULL,PM_REMOVE))         
			{            
				TranslateMessage(&message);            
				DispatchMessage(&message);         
			}

			Sleep(500);
			if(CNeptunePublicWrap::IsMachineIdle())
				break;
		}

		double x,y,z;
		if(!CNeptunePublicWrap::GetCurrentMachinePosition(x, y, z))
		{
			CString strMsg;
			strMsg.Format(_T("Machine goto ended at (%.6f, %.6f, %.6f)!"),x,y,z);
			AfxMessageBox(strMsg);
		}
		GetDlgItem(IDC_BUTTON_GOTO)->EnableWindow(TRUE);
	}
}

void CNeptunePublicGotoDlg::OnDestroy()
{
	CDialog::OnDestroy();

	if(CNeptunePublicWrap::IsInitSuccessed())
		CNeptunePublicWrap::ReleaseNeptunePublicComPtr();
}
