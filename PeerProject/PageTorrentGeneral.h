//
// PageTorrentGeneral.h
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

#include "PagePropertyAdv.h"


class CTorrentGeneralPage : public CPropertyPageAdv
{
public:
	CTorrentGeneralPage();
	virtual ~CTorrentGeneralPage();

	DECLARE_DYNCREATE(CTorrentGeneralPage)

	enum { IDD = IDD_TORRENT_GENERAL };

protected:
	CString			m_sName;
	CString			m_sComment;
	CString			m_sCreatedBy;
	CString			m_sCreationDate;
	CString			m_sTorrentOther;
	CComboBox		m_wndStartDownloads;
	CString			m_sUploadTotal;

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL	OnInitDialog();
	virtual BOOL OnApply();

	DECLARE_MESSAGE_MAP()
};
