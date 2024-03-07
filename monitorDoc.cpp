// monitorDoc.cpp : implementation of the CMonitorDoc class
//

#include "stdafx.h"
#include "monitor.h"

#include "monitorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMonitorDoc

IMPLEMENT_DYNCREATE(CMonitorDoc, CDocument)

BEGIN_MESSAGE_MAP(CMonitorDoc, CDocument)
    //{{AFX_MSG_MAP(CMonitorDoc)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonitorDoc construction/destruction

CMonitorDoc::CMonitorDoc()
{
    // TODO: add one-time construction code here

}

CMonitorDoc::~CMonitorDoc()
{
}

BOOL CMonitorDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: add reinitialization code here
    // (SDI documents will reuse this document)

    return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMonitorDoc serialization

void CMonitorDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // TODO: add storing code here
    }
    else
    {
        // TODO: add loading code here
    }
}

/////////////////////////////////////////////////////////////////////////////
// CMonitorDoc diagnostics

#ifdef _DEBUG
void CMonitorDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CMonitorDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMonitorDoc commands
