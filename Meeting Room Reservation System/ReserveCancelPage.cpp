// ReserveCancelPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Meeting Room Reservation System.h"
#include "ReserveCancelPage.h"
#include "afxdialogex.h"


// CReserveCancelPage �Ի���

IMPLEMENT_DYNAMIC(CReserveCancelPage, CPropertyPage)

CReserveCancelPage::CReserveCancelPage()
	: CPropertyPage(CReserveCancelPage::IDD)
{

}

CReserveCancelPage::~CReserveCancelPage()
{
}

void CReserveCancelPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CReserveCancelPage, CPropertyPage)
END_MESSAGE_MAP()


// CReserveCancelPage ��Ϣ�������

//��������ҳΪ��ǰ�ҳ����Ϣ
BOOL CReserveCancelPage::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
	//��ø����ڣ������Ա�CPropertySheet��
	CPropertySheet* psheet = (CPropertySheet*) GetParent();

	//�������Ա�ֻ�С���ɡ���ť
	psheet->SetFinishText(_T("���"));

	return CPropertyPage::OnSetActive();
}

//��������ҳ�ġ�Finish����ť����������Ϣ�������򵼶Ի�������Ч
BOOL CReserveCancelPage::OnWizardFinish()
{
	// TODO: �ڴ����ר�ô����/����û���
	//��ʾ�����
	MessageBox(_T("ʹ��˵�������Ķ��꣡"));

	return CPropertyPage::OnWizardFinish();
}
