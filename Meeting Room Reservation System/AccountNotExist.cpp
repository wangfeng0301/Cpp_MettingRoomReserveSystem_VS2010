// AccountNotExist.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Meeting Room Reservation System.h"
#include "AccountNotExist.h"
#include "afxdialogex.h"


// CAccountNotExist �Ի���

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


// CAccountNotExist ��Ϣ�������


void CAccountNotExist::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
