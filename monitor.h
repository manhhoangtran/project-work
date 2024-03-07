// monitor.h : main header file for the MONITOR application
//

#if !defined(AFX_MONITOR_H__2C16732B_AA32_48CD_9CC2_DA748553A7DB__INCLUDED_)
#define AFX_MONITOR_H__2C16732B_AA32_48CD_9CC2_DA748553A7DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

const CString CONFIG_SECTION = "Serial Port Setting";
const CString CONFIG_INI_FILE = "c:\\windows\\haoyisheng.ini";

/////////////////////////////////////////////////////////////////////////////
// CMonitorApp:
// See monitor.cpp for the implementation of this class
//

class CMonitorApp : public CWinApp
{
public:
    CMonitorApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMonitorApp)
    public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// Implementation
    //{{AFX_MSG(CMonitorApp)
    afx_msg void OnAppAbout();
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

extern CMonitorApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONITOR_H__2C16732B_AA32_48CD_9CC2_DA748553A7DB__INCLUDED_)
