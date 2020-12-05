// AccountNotExist.cpp : 实现文件
//

#include "stdafx.h"
#include "Meeting Room Reservation System.h"
#include "AccountNotExist.h"
#include "afxdialogex.h"


// CAccountNotExist 对话框

IMPLEMENT_DYNAMIC(CAccountNotExist, CDialogEx)

CAccountNotExist::CAccountNotExist(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAccountNotExist::IDD, pParent)
{

}

CAccountNotExist::~CAccountNotExist()
{
}

void CAccountNotExist::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAccountNotExist, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAccountNotExist::OnBnClickedOk)
END_MESSAGE_MAP()


// CAccountNotExist 消息处理程序


void CAccountNotExist::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
