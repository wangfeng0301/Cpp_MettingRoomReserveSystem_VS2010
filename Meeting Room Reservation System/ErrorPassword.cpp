// ErrorPassword.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Meeting Room Reservation System.h"
#include "ErrorPassword.h"
#include "afxdialogex.h"


// CErrorPassword �Ի���

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


// CErrorPassword ��Ϣ�������


void CErrorPassword::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
