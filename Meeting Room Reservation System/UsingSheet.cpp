// UsingSheet.cpp : 实现文件
//

#include "stdafx.h"
#include "Meeting Room Reservation System.h"
#include "UsingSheet.h"


// CUsingSheet

IMPLEMENT_DYNAMIC(CUsingSheet, CPropertySheet)

CUsingSheet::CUsingSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	//添加三个属性页到属性表,AddPage()函数为属性对话框添加新的属性页
	AddPage(&m_entryPage);
	AddPage(&m_reservePage);
	AddPage(&m_reservecancelPage);

}

CUsingSheet::CUsingSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	//添加三个属性页到属性表,AddPage()函数为属性对话框添加新的属性页
	AddPage(&m_entryPage);
	AddPage(&m_reservePage);
	AddPage(&m_reservecancelPage);
}

CUsingSheet::~CUsingSheet()
{
}


BEGIN_MESSAGE_MAP(CUsingSheet, CPropertySheet)
END_MESSAGE_MAP()


// CUsingSheet 消息处理程序
