//
// DlgIrcInput.cpp
//
// This file is part of PeerProject (peerproject.org) � 2008-2010
// Portions copyright Shareaza Development Team, 2002-2008.
//
// PeerProject is free software; you can redistribute it and/or
// modify it under the terms of the GNU Affero General Public License
// as published by the Free Software Foundation (fsf.org);
// either version 3 of the License, or later version at your option.
//
// PeerProject is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Affero General Public License 3.0 (AGPLv3) for details:
// (http://www.gnu.org/licenses/agpl.html)
//

#include "StdAfx.h"
#include "PeerProject.h"
#include "DlgIrcInput.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif	// Filename

// CIrcInputDlg dialog

CIrcInputDlg::CIrcInputDlg( CWnd* pParent /*=NULL*/, int nCaptionIndex, BOOL bKickOnly ) :
	CSkinDialog( CIrcInputDlg::IDD, pParent )
{
	m_nCaptionIndex = nCaptionIndex;
	if ( m_nCaptionIndex )
		m_bKickOnly = bKickOnly;
	else
		m_bKickOnly = FALSE;
}

CIrcInputDlg::~CIrcInputDlg()
{
}

// CIrcInputDlg message handlers

void CIrcInputDlg::OnOK()
{
	UpdateData( TRUE );

	m_wndAnswer.GetWindowText( m_sAnswer );

	CSkinDialog::OnOK();
}

void CIrcInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CSkinDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnectToDlg)
	DDX_Control(pDX, IDC_IRC_PROMPT, m_wndPrompt);
	DDX_Control(pDX, IDC_IRC_INPUT, m_wndAnswer);
	//}}AFX_DATA_MAP
}

BOOL CIrcInputDlg::OnInitDialog()
{
	CSkinDialog::OnInitDialog();

	SkinMe( _T("CIrcInputDlg"), m_nCaptionIndex == 0 ? ID_IRC_ADD :
		( m_bKickOnly ? ID_IRC_KICKWHY : ID_IRC_BANKICKWHY ) );
	SelectCaption( this, m_nCaptionIndex );
	SelectCaption( &m_wndPrompt, m_nCaptionIndex );

	return TRUE;
}
