// monitor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "monitor.h"

#include "MainFrm.h"
#include "monitorDoc.h"
#include "monitorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMonitorApp

BEGIN_MESSAGE_MAP(CMonitorApp, CWinApp)
    //{{AFX_MSG_MAP(CMonitorApp)
    ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
    // Standard file based document commands
    ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonitorApp construction

CMonitorApp::CMonitorApp()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMonitorApp object

CMonitorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMonitorApp initialization

extern "C"  //wdl
{
    bool IsWin7Above()
    {
        OSVERSIONINFOEX osvi;
        BOOL bOsVersionInfoEx;
        
        ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
        bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO*) &osvi);
        
        // win7的系统版本为NT6.1
        if (VER_PLATFORM_WIN32_NT == osvi.dwPlatformId && osvi.dwMajorVersion >= 6) {
            return true;
        }
        else {
            return false;
        }
    }
    
    typedef LANGID (WINAPI *FP_SetThreadUILanguage)(LANGID LangId);
   /* LANGID SetThreadUILanguage(LANGID lcid)
    {
        HMODULE hKernel32 = GetModuleHandle(_T("Kernel32.dll"));
        FARPROC pFn = GetProcAddress(hKernel32, "SetThreadUILanguage");
        
        FP_SetThreadUILanguage pSetThreadUILanguage = (FP_SetThreadUILanguage)pFn;
        if (pSetThreadUILanguage) {
            return pSetThreadUILanguage(lcid);
        }
        return 0;
    }*/
}

BOOL CMonitorApp::InitInstance()
{
    AfxEnableControlContainer();

    // Standard initialization
    // If you are not using these features and wish to reduce the size
    //  of your final executable, you should remove from the following
    //  the specific initialization routines you do not need.

#ifdef _AFXDLL
    Enable3dControls();         // Call this when using MFC in a shared DLL
#else
    Enable3dControlsStatic();   // Call this when linking to MFC statically
#endif

    // Change the registry key under which our settings are stored.
    // TODO: You should modify this string to be something appropriate
    // such as the name of your company or organization.
    //SetRegistryKey(_T("Local AppWizard-Generated Applications"));
    SetRegistryKey(_T("Berry Apps"));

    LoadStdProfileSettings();  // Load standard INI file options (including MRU)

    //wdl, select suitable language
    /*if (LANG_CHINESE == PRIMARYLANGID(LANGIDFROMLCID(GetThreadLocale())))
    {
        if (IsWin7Above())
            SetThreadUILanguage(MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED), SORT_DEFAULT));
        else
            SetThreadLocale(MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED), SORT_DEFAULT));
    }
    else
    {
        if (IsWin7Above())
            SetThreadUILanguage(MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT));
        else
            SetThreadLocale(MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT));
    }*/

    // Register the application's document templates.  Document templates
    //  serve as the connection between documents, frame windows and views.

    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME,
        RUNTIME_CLASS(CMonitorDoc),
        RUNTIME_CLASS(CMainFrame),       // main SDI frame window
        RUNTIME_CLASS(CMonitorView));
    AddDocTemplate(pDocTemplate);

    // Parse command line for standard shell commands, DDE, file open
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

    // Dispatch commands specified on the command line
    if (!ProcessShellCommand(cmdInfo))
        return FALSE;

    // The one and only window has been initialized, so show and update it.
    //m_pMainWnd->ShowWindow(SW_SHOW);
    m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
    m_pMainWnd->UpdateWindow();

    ((CMainFrame *)m_pMainWnd)->OpenPort();

    return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    //{{AFX_DATA(CAboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
    protected:
    //}}AFX_VIRTUAL

// Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
        // No message handlers
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
        // No message handlers
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CMonitorApp::OnAppAbout()
{
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}
