// VersionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "monitor.h"
#include "VersionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVersionDlg dialog


CVersionDlg::CVersionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVersionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVersionDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CVersionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVersionDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVersionDlg, CDialog)
	//{{AFX_MSG_MAP(CVersionDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVersionDlg message handlers
