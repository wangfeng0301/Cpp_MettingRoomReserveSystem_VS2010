#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CReserveDlg �Ի���

class CReserveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReserveDlg)
public:
	CReserveDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReserveDlg();              // ��������

// �Ի�������
	enum { IDD = IDD_RESERVE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl m_dateCtrl;    //��ӡ����ڡ�����
	CComboBox m_comboTIME;       //��ӡ�ʱ�䡱��Ͽ����
	CComboBox m_comboMeetingRoom;//��ӡ������ҡ���Ͽ����
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedReservecancleButton();
	afx_msg void OnBnClickedOk();
	int m_iTime;                 //���ʱ����Ͽ�������
	CTime m_dateTime;            //�������
	int m_iMeetingRoom;          //��Ż�����������
	
	
};
