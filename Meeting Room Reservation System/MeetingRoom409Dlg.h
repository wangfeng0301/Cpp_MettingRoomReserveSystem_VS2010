#pragma once
#include "afxcmn.h"


// CMeetingRoom409 �Ի���

class CMeetingRoom409Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMeetingRoom409Dlg)

public:
	CMeetingRoom409Dlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMeetingRoom409Dlg();              // ��������

// �Ի�������
	enum { IDD = IDD_MEETINGROOM409_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CListCtrl m_MeetingRoom409InfoList;//��Ż�����409�б���Ϣ
	virtual BOOL OnInitDialog();       //��ʼ������
	void UpdateMeetingRoom409();       //ˢ���б���Ϣ����
};
