// UsingSheet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Meeting Room Reservation System.h"
#include "UsingSheet.h"


// CUsingSheet

IMPLEMENT_DYNAMIC(CUsingSheet, CPropertySheet)

CUsingSheet::CUsingSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	//�����������ҳ�����Ա�,AddPage()����Ϊ���ԶԻ�������µ�����ҳ
	AddPage(&m_entryPage);
	AddPage(&m_reservePage);
	AddPage(&m_reservecancelPage);

}

CUsingSheet::CUsingSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	//�����������ҳ�����Ա�,AddPage()����Ϊ���ԶԻ�������µ�����ҳ
	AddPage(&m_entryPage);
	AddPage(&m_reservePage);
	AddPage(&m_reservecancelPage);
}

CUsingSheet::~CUsingSheet()
{
}


BEGIN_MESSAGE_MAP(CUsingSheet, CPropertySheet)
END_MESSAGE_MAP()


// CUsingSheet ��Ϣ�������
