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
	CReservePage m_reservePage;            //��ӡ�ԤԼҳ����ı���
	CReserveCancelPage m_reservecancelPage;//��ӡ�ȡ��ԤԼ����ı���
	CEntryPage m_entryPage;                //��ӡ���¼����ı���
};


