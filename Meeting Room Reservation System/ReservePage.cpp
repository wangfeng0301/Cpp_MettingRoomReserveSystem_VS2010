// ReservePage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Meeting Room Reservation System.h"
#include "ReservePage.h"
#include "afxdialogex.h"


// CReservePage �Ի���

IMPLEMENT_DYNAMIC(CReservePage, CPropertyPage)

CReservePage::CReservePage()
	: CPropertyPage(CReservePage::IDD)
{

}

CReservePage::~CReservePage()
{
}

void CReservePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CReservePage, CPropertyPage)
END_MESSAGE_MAP()


// CReservePage ��Ϣ�������
//��������ҳ���л�����ǰ�ҳ����Ϣ
BOOL CReservePage::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
	//��ø����ڣ������Ա�CPropertySheet��
	CPropertySheet* psheet = (CPropertySheet*) GetParent();

	//�������Ա��С���һ�����͡���һ������ť
	psheet->SetWizardButtons(PSWIZB_NEXT | PSWIZB_BACK);

	return CPropertyPage::OnSetActive();
}
