#pragma once
#include "afxcmn.h"


// CMeetRoom112 �Ի���

class CMeetingRoom112Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMeetingRoom112Dlg)

public:
	CMeetingRoom112Dlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMeetingRoom112Dlg();

// �Ի�������
	enum { IDD = IDD_MEETINGROOM112_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	// ���ɵ���Ϣӳ�亯��
	DECLARE_MESSAGE_MAP()

public:
	CListCtrl m_MeetingRoom112InfoList;//��Ż�����112�б���Ϣ
	virtual BOOL OnInitDialog();         //��ʼ������������������112�б�
	void UpdateMeetingRoom112();         //ˢ���б���Ϣ
};
