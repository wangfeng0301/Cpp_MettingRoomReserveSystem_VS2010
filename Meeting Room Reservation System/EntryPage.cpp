// EntryPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Meeting Room Reservation System.h"
#include "EntryPage.h"
#include "afxdialogex.h"


// CEntryPage �Ի���

IMPLEMENT_DYNAMIC(CEntryPage, CPropertyPage)

CEntryPage::CEntryPage()
	: CPropertyPage(CEntryPage::IDD)
{

}

CEntryPage::~CEntryPage()
{
}

void CEntryPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEntryPage, CPropertyPage)
END_MESSAGE_MAP()


// CEntryPage ��Ϣ�������

//��������ҳ���л�Ϊ��ǰ�ҳ����Ϣ
BOOL CEntryPage::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
	//��ø����ڣ������Ա�CPropertySheet��
	CPropertySheet* psheet = (CPropertySheet*) GetParent();

	//�������Ա�ֻ�С���һ������ť
	psheet->SetWizardButtons(PSWIZB_NEXT);

	return CPropertyPage::OnSetActive();
}
