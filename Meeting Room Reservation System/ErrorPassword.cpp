// ErrorPassword.cpp : 实现文件
//

#include "stdafx.h"
#include "Meeting Room Reservation System.h"
#include "ErrorPassword.h"
#include "afxdialogex.h"


// CErrorPassword 对话框

IMPLEMENT_DYNAMIC(CErrorPassword, CDialogEx)

CErrorPassword::CErrorPassword(CWnd* pParent /*=NULL*/)
	: CDialogEx(CErrorPassword::IDD, pParent)
{

}

CErrorPassword::~CErrorPassword()
{
}

void CErrorPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CErrorPassword, CDialogEx)
	ON_BN_CLICKED(IDOK, &CErrorPassword::OnBnClickedOk)
END_MESSAGE_MAP()


// CErrorPassword 消息处理程序


void CErrorPassword::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
