
// Meeting Room Reservation System.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Meeting Room Reservation System.h"
#include "Meeting Room Reservation SystemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMeetingRoomReservationSystemApp

BEGIN_MESSAGE_MAP(CMeetingRoomReservationSystemApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMeetingRoomReservationSystemApp ����

CMeetingRoomReservationSystemApp::CMeetingRoomReservationSystemApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMeetingRoomReservationSystemApp ����

CMeetingRoomReservationSystemApp theApp;


// CMeetingRoomReservationSystemApp ��ʼ��

BOOL CMeetingRoomReservationSystemApp::InitInstance()
{
	//AfxOleInit();//��ʼ��COM�ؼ��������޷���COM������������Excelʱ��Ӵ˾䡣
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CMeetingRoomReservationSystemDlg dlg;//����Ի�����CMeetingRoomReservationSystemDlg�Ķ���dlg
	m_pMainWnd = &dlg;                   //��dlg����Ϊ������
	INT_PTR nResponse = dlg.DoModal();   //�����Ի���dlg������DoModal�����ķ���ֵ���˳�ʱ�����ť��ID����ֵ��nResponse
	if (nResponse == ID_ENTRY)           //�жϷ���ֵ�Ƿ�Ϊ��¼��ť
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == ID_LOGIN)      //�жϷ���ֵ�Ƿ�Ϊע�ᰴť
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

