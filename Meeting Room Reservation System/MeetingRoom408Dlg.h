#pragma once
#include "afxcmn.h"


// CMeetingRoom �Ի���

class CMeetingRoom408Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMeetingRoom408Dlg)

public:
	CMeetingRoom408Dlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMeetingRoom408Dlg();

// �Ի�������
	enum { IDD = IDD_MEETINGROOM408_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CListCtrl m_MeetingRoom408InfoList;//��Ż�����408�б���Ϣ
	virtual BOOL OnInitDialog();         //��ʼ������
	void UpdateMeetingRoom408();         //ˢ���б���Ϣ
};
