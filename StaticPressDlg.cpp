// StaticPressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "monitor.h"
#include "StaticPressDlg.h"
#include "MainFrm.h"
#include "CnComm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticPressDlg dialog


CStaticPressDlg::CStaticPressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStaticPressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStaticPressDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


BEGIN_MESSAGE_MAP(CStaticPressDlg, CDialog)
	//{{AFX_MSG_MAP(CStaticPressDlg)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticPressDlg message handlers

BOOL CStaticPressDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_IsOpen = true;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStaticPressDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	m_IsOpen = false;

	CDialog::OnClose();
}

BOOL CStaticPressDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
        return TRUE;
    }
    
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) {
        m_IsOpen = false;
    }

	return CDialog::PreTranslateMessage(pMsg);
}
