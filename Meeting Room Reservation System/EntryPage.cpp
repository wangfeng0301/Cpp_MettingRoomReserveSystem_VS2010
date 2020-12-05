// EntryPage.cpp : 实现文件
//

#include "stdafx.h"
#include "Meeting Room Reservation System.h"
#include "EntryPage.h"
#include "afxdialogex.h"


// CEntryPage 对话框

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


// CEntryPage 消息处理程序

//处理属性页被切换为当前活动页的消息
BOOL CEntryPage::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	//获得父窗口，即属性表CPropertySheet类
	CPropertySheet* psheet = (CPropertySheet*) GetParent();

	//设置属性表只有“下一步”按钮
	psheet->SetWizardButtons(PSWIZB_NEXT);

	return CPropertyPage::OnSetActive();
}
