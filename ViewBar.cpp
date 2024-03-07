// ViewBar.cpp : implementation file
//

#include "stdafx.h"
#include "monitor.h"
#include "ViewBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewBar dialog


CViewBar::CViewBar(CWnd* pParent /*=NULL*/)
{
    //{{AFX_DATA_INIT(CViewBar)
    //}}AFX_DATA_INIT
    m_Brush.CreateSolidBrush(RGB(0x0, 0x0, 0x0));
    m_FontBig.CreatePointFont(200, "Arial Bold");
    m_FontNormal.CreatePointFont(120, "Arial Bold");
    m_FontSmall.CreatePointFont(80, "Arial Bold");
}


BEGIN_MESSAGE_MAP(CViewBar, CDialogBar)
    //{{AFX_MSG_MAP(CViewBar)
    ON_WM_CTLCOLOR()
    //}}AFX_MSG_MAP
    ON_MESSAGE(WM_INITDIALOG, OnInitDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewBar message handlers

HBRUSH CViewBar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
    HBRUSH hbr = CDialogBar::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO: Change any attributes of the DC here
    if (pWnd->m_hWnd == GetDlgItem(IDC_HR)->m_hWnd) {
        pDC->SetBkColor(RGB(0, 0, 0));
        pDC->SetTextColor(RGB(0, 255, 0));
        return m_Brush;
    }
    else if (pWnd->m_hWnd == GetDlgItem(IDC_RESP)->m_hWnd) {
        pDC->SetBkColor(RGB(0, 0, 0));
        pDC->SetTextColor(RGB(0, 255, 0));
        return m_Brush;
    }
    else if (pWnd->m_hWnd == GetDlgItem(IDC_ST)->m_hWnd) {
        pDC->SetBkColor(RGB(0, 0, 0));
        pDC->SetTextColor(RGB(0, 255, 0));
        return m_Brush;
    }
    else if (pWnd->m_hWnd == GetDlgItem(IDC_ARR)->m_hWnd) {
        pDC->SetBkColor(RGB(0, 0, 0));
        pDC->SetTextColor(RGB(0, 255, 0));
        return m_Brush;
    }
    else if (pWnd->m_hWnd == GetDlgItem(IDC_SYS)->m_hWnd) {
        pDC->SetBkColor(RGB(0, 0, 0));
        pDC->SetTextColor(RGB(255, 255, 0));
        return m_Brush;
    }
    else if (pWnd->m_hWnd == GetDlgItem(IDC_DIA)->m_hWnd) {
        pDC->SetBkColor(RGB(0, 0, 0));
        pDC->SetTextColor(RGB(255, 255, 0));
        return m_Brush;
    }
    else if (pWnd->m_hWnd == GetDlgItem(IDC_MEAN)->m_hWnd) {
        pDC->SetBkColor(RGB(0, 0, 0));
        pDC->SetTextColor(RGB(255, 255, 0));
        return m_Brush;
    }
    else if (pWnd->m_hWnd == GetDlgItem(IDC_CUFF)->m_hWnd) {
        pDC->SetBkColor(RGB(0, 0, 0));
        pDC->SetTextColor(RGB(255, 255, 0));
        return m_Brush;
    }
    else if (pWnd->m_hWnd == GetDlgItem(IDC_SPO2)->m_hWnd) {
        pDC->SetBkColor(RGB(0, 0, 0));
        pDC->SetTextColor(RGB(255, 0, 0));
        return m_Brush;
    }
    else if (pWnd->m_hWnd == GetDlgItem(IDC_PR)->m_hWnd) {
        pDC->SetBkColor(RGB(0, 0, 0));
        pDC->SetTextColor(RGB(255, 0, 0));
        return m_Brush;
    }
    else if (pWnd->m_hWnd == GetDlgItem(IDC_TEMP1)->m_hWnd) {
        pDC->SetBkColor(RGB(0, 0, 0));
        pDC->SetTextColor(RGB(0, 255, 255));
        return m_Brush;
    }
    else if (pWnd->m_hWnd == GetDlgItem(IDC_TEMP2)->m_hWnd) {
        pDC->SetBkColor(RGB(0, 0, 0));
        pDC->SetTextColor(RGB(0, 255, 255));
        return m_Brush;
    }
    else if (pWnd->m_hWnd == GetDlgItem(IDC_ECG_LEAD_STATE)->m_hWnd) {
        pDC->SetBkColor(RGB(0, 0, 0));
        pDC->SetTextColor(RGB(0, 255, 0));
        return m_Brush;
    }
    else if (pWnd->m_hWnd == GetDlgItem(IDC_ECG_MODE)->m_hWnd) {
        pDC->SetBkColor(RGB(0, 0, 0));
        pDC->SetTextColor(RGB(0, 255, 0));
        return m_Brush;
    }
    else if (pWnd->m_hWnd == GetDlgItem(IDC_ECG_GAIN)->m_hWnd) {
        pDC->SetBkColor(RGB(0, 0, 0));
        pDC->SetTextColor(RGB(0, 255, 0));
        return m_Brush;
    }
    else if (pWnd->m_hWnd == GetDlgItem(IDC_ECG_SIGNAL)->m_hWnd) {
        pDC->SetBkColor(RGB(0, 0, 0));
        pDC->SetTextColor(RGB(0, 255, 0));
        return m_Brush;
    }
    else if (pWnd->m_hWnd == GetDlgItem(IDC_NIBP_MODE)->m_hWnd) {
        pDC->SetBkColor(RGB(0, 0, 0));
        pDC->SetTextColor(RGB(255, 255, 0));
        return m_Brush;
    }
    else if (pWnd->m_hWnd == GetDlgItem(IDC_NIBP_STATE)->m_hWnd) {
        pDC->SetBkColor(RGB(0, 0, 0));
        pDC->SetTextColor(RGB(255, 255, 0));
        return m_Brush;
    }
    else if (pWnd->m_hWnd == GetDlgItem(IDC_SPO2_STATE)->m_hWnd) {
        pDC->SetBkColor(RGB(0, 0, 0));
        pDC->SetTextColor(RGB(255, 0, 0));
        return m_Brush;
    }
    else if (pWnd->m_hWnd == GetDlgItem(IDC_TEMP_STATE)->m_hWnd) {
        pDC->SetBkColor(RGB(0, 0, 0));
        pDC->SetTextColor(RGB(0, 255, 255));
        return m_Brush;
    }
    // TODO: Return a different brush if the default is not desired
    return hbr;
}

LRESULT CViewBar::OnInitDialog(UINT wParam, LONG lParam)
{
    BOOL bRet = HandleInitDialog(wParam, lParam);

    // TODO: Add extra initialization here
    
    GetDlgItem(IDC_HR)->SetFont(&m_FontBig);
    GetDlgItem(IDC_RESP)->SetFont(&m_FontBig);
    GetDlgItem(IDC_ST)->SetFont(&m_FontBig);
    GetDlgItem(IDC_ARR)->SetFont(&m_FontNormal);
    GetDlgItem(IDC_SYS)->SetFont(&m_FontBig);
    GetDlgItem(IDC_DIA)->SetFont(&m_FontBig);
    GetDlgItem(IDC_MEAN)->SetFont(&m_FontBig);
    GetDlgItem(IDC_CUFF)->SetFont(&m_FontBig);
    GetDlgItem(IDC_SPO2)->SetFont(&m_FontBig);
    GetDlgItem(IDC_PR)->SetFont(&m_FontBig);
    GetDlgItem(IDC_TEMP1)->SetFont(&m_FontBig);
    GetDlgItem(IDC_TEMP2)->SetFont(&m_FontBig);
    GetDlgItem(IDC_ECG_LEAD_STATE)->SetFont(&m_FontNormal);
    GetDlgItem(IDC_ECG_MODE)->SetFont(&m_FontNormal);
    GetDlgItem(IDC_ECG_GAIN)->SetFont(&m_FontNormal);
    GetDlgItem(IDC_ECG_SIGNAL)->SetFont(&m_FontNormal);
    GetDlgItem(IDC_NIBP_MODE)->SetFont(&m_FontNormal);
    GetDlgItem(IDC_NIBP_STATE)->SetFont(&m_FontNormal);
    GetDlgItem(IDC_SPO2_STATE)->SetFont(&m_FontNormal);
    GetDlgItem(IDC_TEMP_STATE)->SetFont(&m_FontNormal);
   
    SetDlgItemText(IDC_HR, "---");
    SetDlgItemText(IDC_RESP, "---");
    SetDlgItemText(IDC_ST, "---");
    SetDlgItemText(IDC_ARR, "---");
    SetDlgItemText(IDC_SYS, "---");
    SetDlgItemText(IDC_DIA, "---");
    SetDlgItemText(IDC_MEAN, "---");
    SetDlgItemText(IDC_CUFF, "---");
    SetDlgItemText(IDC_SPO2, "---");
    SetDlgItemText(IDC_PR, "---");
    SetDlgItemText(IDC_TEMP1, "---");
    SetDlgItemText(IDC_TEMP2, "---");

    SetDlgItemText(IDC_ECG_LEAD_STATE, "");
    SetDlgItemText(IDC_ECG_SIGNAL, "");
    SetDlgItemText(IDC_ECG_MODE, "");
    SetDlgItemText(IDC_ECG_GAIN, "");
    SetDlgItemText(IDC_NIBP_MODE, "");
    SetDlgItemText(IDC_SPO2_STATE, "");
    SetDlgItemText(IDC_TEMP_STATE, "");

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
