
// Meeting Room Reservation SystemDlg.h : ͷ�ļ�

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "MeetingRoom112Dlg.h"//���112�Ի���ͷ�ļ�
#include "MeetingRoom408Dlg.h"//���408�Ի���ͷ�ļ�
#include "MeetingRoom409Dlg.h"//���409�Ի���ͷ�ļ�
#include "afxdtctl.h"
#include "atltime.h"

// CMeetingRoomReservationSystemDlg �Ի���
class CMeetingRoomReservationSystemDlg : public CDialogEx
{
// ����
public:
	CMeetingRoomReservationSystemDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MEETINGROOMRESERVATIONSYSTEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strAccount;                    //�����˺ű༭�����ַ���
	CString m_strPassword;                   //��������༭�����ַ���
	CTabCtrl m_tabMeetingRoom;               //������ѡ�
	CMeetingRoom409Dlg m_MeetingRoom409;     //��ӻ�����409��ı���
	CMeetingRoom408Dlg m_MeetingRoom408;     //��ӻ�����408��ı���
	CMeetingRoom112Dlg m_MeetingRoom112;     //��ӻ�����112��ı���
	CMonthCalCtrl m_montCtrl;                //�����������
	

	afx_msg void OnBnClickedLogin();         //������ע�ᡱ��ť��Ϣ������
	afx_msg void OnBnClickedEntry();         //��������¼����ť��Ϣ������
	afx_msg void OnBnClickedReserveButton(); //������ԤԼ����ť��Ϣ������
	afx_msg void OnBnClickedInstructButton();//������ʹ��˵������ťʱ��Ϣ������
	afx_msg void OnBnClickedQuitButton();    //�������˳���¼����ťʱ��Ϣ������
	afx_msg void OnTcnSelchangeMeetingroomTab(NMHDR *pNMHDR, LRESULT *pResult);//�л���ǩ�ؼ�ѡ�Ϳ���Ϣ������
	afx_msg void OnTimer(UINT_PTR nIDEvent); //��ʱ����Ϣ������
	
	void CMeetingRoomReservationSystemDlg::HideEntry();//���ص�¼����
	void CMeetingRoomReservationSystemDlg::ShowEntry();//��ʾ��¼����	
	void CMeetingRoomReservationSystemDlg::DeleteIni();//
};
