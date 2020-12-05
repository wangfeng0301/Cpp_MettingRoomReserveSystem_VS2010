// ReserveCancelPage.cpp : 实现文件
//

#include "stdafx.h"
#include "Meeting Room Reservation System.h"
#include "ReserveCancelPage.h"
#include "afxdialogex.h"


// CReserveCancelPage 对话框

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


// CReserveCancelPage 消息处理程序

//处理属性页为当前活动页的消息
BOOL CReserveCancelPage::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	//获得父窗口，即属性表CPropertySheet类
	CPropertySheet* psheet = (CPropertySheet*) GetParent();

	//设置属性表只有“完成”按钮
	psheet->SetFinishText(_T("完成"));

	return CPropertyPage::OnSetActive();
}

//处理属性页的“Finish”按钮被单击的消息，仅在向导对话框中有效
BOOL CReserveCancelPage::OnWizardFinish()
{
	// TODO: 在此添加专用代码和/或调用基类
	//提示向导完成
	MessageBox(_T("使用说明向导已阅读完！"));

	return CPropertyPage::OnWizardFinish();
}
