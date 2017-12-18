// cccDoc.cpp : implementation of the CCccDoc class
//

#include "stdafx.h"
#include "ccc.h"

#include "cccSet.h"
#include "cccDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCccDoc

IMPLEMENT_DYNCREATE(CCccDoc, CDocument)

BEGIN_MESSAGE_MAP(CCccDoc, CDocument)
	//{{AFX_MSG_MAP(CCccDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCccDoc construction/destruction

CCccDoc::CCccDoc()
{
	// TODO: add one-time construction code here

}

CCccDoc::~CCccDoc()
{
}

BOOL CCccDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCccDoc serialization

void CCccDoc::Serialize(CArchive& ar)
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
// CCccDoc diagnostics

#ifdef _DEBUG
void CCccDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCccDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCccDoc commands
