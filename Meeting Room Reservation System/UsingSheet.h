#pragma once

#include "ReservePage.h"
#include "ReserveCancelPage.h"
#include "EntryPage.h"

// CUsingSheet

class CUsingSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CUsingSheet)

public:
	CUsingSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CUsingSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CUsingSheet();

protected:
	DECLARE_MESSAGE_MAP()
private:
	CReservePage m_reservePage;            //添加“预约页”类的变量
	CReserveCancelPage m_reservecancelPage;//添加“取消预约”类的变量
	CEntryPage m_entryPage;                //添加“登录”类的变量
};


