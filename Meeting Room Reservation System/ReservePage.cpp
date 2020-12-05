// ReservePage.cpp : 实现文件
//

#include "stdafx.h"
#include "Meeting Room Reservation System.h"
#include "ReservePage.h"
#include "afxdialogex.h"


// CReservePage 对话框

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


// CReservePage 消息处理程序
//处理属性页被切换到当前活动页的消息
BOOL CReservePage::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	//获得父窗口，即属性表CPropertySheet类
	CPropertySheet* psheet = (CPropertySheet*) GetParent();

	//设置属性表有“下一步”和“下一步”按钮
	psheet->SetWizardButtons(PSWIZB_NEXT | PSWIZB_BACK);

	return CPropertyPage::OnSetActive();
}
