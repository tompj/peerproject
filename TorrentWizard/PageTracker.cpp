//
// PageTracker.cpp
//
// This file is part of PeerProject Torrent Wizard (peerproject.org) � 2008-2012
// Portions Copyright Shareaza Development Team, 2007.
//
// PeerProject Torrent Wizard is free software; you can redistribute it
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or later version (at your option).
//
// Torrent Wizard is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License 3.0
// along with PeerProject; if not, write to Free Software Foundation, Inc.
// 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA  (www.fsf.org)
//

#include "StdAfx.h"
#include "TorrentWizard.h"
#include "PageTracker.h"
#include "PageWelcome.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CTrackerPage, CWizardPage)

BEGIN_MESSAGE_MAP(CTrackerPage, CWizardPage)
	//{{AFX_MSG_MAP(CTrackerPage)
	ON_BN_CLICKED(IDC_CLEAR_TRACKERS, &CTrackerPage::OnClearTrackers)
	ON_WM_XBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTrackerPage property page

CTrackerPage::CTrackerPage() : CWizardPage(CTrackerPage::IDD)
{
}

//CTrackerPage::~CTrackerPage()
//{
//}

void CTrackerPage::DoDataExchange(CDataExchange* pDX)
{
	CWizardPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrackerPage)
	DDX_Control(pDX, IDC_TRACKER, m_wndTracker);
	DDX_CBString(pDX, IDC_TRACKER, m_sTracker);
	DDX_Control(pDX, IDC_TRACKER2, m_wndTracker2);
	DDX_CBString(pDX, IDC_TRACKER2, m_sTracker2);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CTrackerPage message handlers

BOOL CTrackerPage::OnInitDialog()
{
	CWizardPage::OnInitDialog();

	int nCount = theApp.GetProfileInt( _T("Trackers"), _T("Count"), 0 );

	for ( int nItem = 0 ; nItem < nCount ; nItem++ )
	{
		CString strName, strURL;
		strName.Format( _T("%.3i.URL"), nItem + 1 );
		strURL = theApp.GetProfileString( _T("Trackers"), strName );
		if ( strURL.GetLength() )
		{
			m_wndTracker.AddString( strURL );
			m_wndTracker2.AddString( strURL );
		}
	}

	m_sTracker = theApp.GetProfileString( _T("Trackers"), _T("Last") );
	if ( m_sTracker.GetLength() < 14 )
		m_sTracker = _T("udp://tracker.openbittorrent.com:80");
	UpdateData( FALSE );

	return TRUE;
}

BOOL CTrackerPage::OnSetActive()
{
	SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT );

	if ( ! theApp.m_sCommandLineTracker.IsEmpty() )
	{
		m_sTracker = theApp.m_sCommandLineTracker;
		theApp.m_sCommandLineTracker.Empty();

		UpdateData( FALSE );

		Next();
	}

	return CWizardPage::OnSetActive();
}

void CTrackerPage::OnClearTrackers()
{
	theApp.WriteProfileInt( _T("Trackers"), _T("Count"), 0 );
	m_sTracker.Empty();
	UpdateData( FALSE );
	m_wndTracker.ResetContent();
	m_wndTracker2.ResetContent();
	m_wndTracker.SetFocus();
}

LRESULT CTrackerPage::OnWizardBack()
{
	GET_PAGE( CWelcomePage, pWelcome );

	UpdateData( TRUE );

	SaveTrackers();

	return pWelcome->m_nType ? IDD_PACKAGE_PAGE : IDD_SINGLE_PAGE;
}

LRESULT CTrackerPage::OnWizardNext()
{
	UpdateData( TRUE );

	if ( m_sTracker.GetLength() < 16 ||
		( m_sTracker.Find( _T("http:") ) != 0 && m_sTracker.Find( _T("udp:") ) != 0 ) )
	{
		if ( IDYES != AfxMessageBox( IDS_TRACKER_NEED_URL, MB_ICONQUESTION|MB_YESNO ) )
		{
			m_wndTracker.SetFocus();
			return -1;
		}
	}

	SaveTrackers();

	return IDD_COMMENT_PAGE;
}

void CTrackerPage::SaveTrackers()
{
	if ( m_sTracker.GetLength() > 15 && m_wndTracker.FindStringExact( -1, m_sTracker ) < 0 )
	{
		m_wndTracker.AddString( m_sTracker );	// Populate Combo-box
		m_wndTracker2.AddString( m_sTracker );

		CString strName;
		int nCount = theApp.GetProfileInt( _T("Trackers"), _T("Count"), 0 );
		strName.Format( _T("%.3i.URL"), ++nCount );
		theApp.WriteProfileInt( _T("Trackers"), _T("Count"), nCount );
		theApp.WriteProfileString( _T("Trackers"), strName, m_sTracker );
	}

	if ( m_sTracker2.GetLength() > 15 && m_sTracker2.Find( _T("://") ) > 0 && m_wndTracker2.FindStringExact( -1, m_sTracker2 ) < 0 )
	{
		m_wndTracker.AddString( m_sTracker2 );
		m_wndTracker2.AddString( m_sTracker2 );

		CString strName;
		int nCount = theApp.GetProfileInt( _T("Trackers"), _T("Count"), 0 );
		strName.Format( _T("%.3i.URL"), ++nCount );
		theApp.WriteProfileInt( _T("Trackers"), _T("Count"), nCount );
		theApp.WriteProfileString( _T("Trackers"), strName, m_sTracker );
	}

	theApp.WriteProfileString( _T("Trackers"), _T("Last"), m_sTracker );
}

void CTrackerPage::OnXButtonDown(UINT /*nFlags*/, UINT nButton, CPoint /*point*/)
{
	if ( nButton == 1 )
		GetSheet()->PressButton( PSBTN_BACK );
	else if ( nButton == 2 )
		GetSheet()->PressButton( PSBTN_NEXT );
}
