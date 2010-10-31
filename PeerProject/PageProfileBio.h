//
// PageProfileBio.h
//
// This file is part of PeerProject (peerproject.org) � 2008-2010
// Portions copyright Shareaza Development Team, 2002-2007.
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

#pragma once

#include "WndSettingsPage.h"


class CBioProfilePage : public CSettingsPage
{
// Construction
public:
	CBioProfilePage();
	virtual ~CBioProfilePage();

	DECLARE_DYNCREATE(CBioProfilePage)

	enum { IDD = IDD_PROFILE_BIO };

// Dialog Data
public:
	//{{AFX_DATA(CBioProfilePage)
	CEdit	m_wndText;
	//}}AFX_DATA

// Overrides
protected:
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CBioProfilePage)
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnOK();
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CBioProfilePage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
