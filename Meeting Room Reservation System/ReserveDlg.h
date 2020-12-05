#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CReserveDlg 对话框

class CReserveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReserveDlg)
public:
	CReserveDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReserveDlg();              // 析构函数

// 对话框数据
	enum { IDD = IDD_RESERVE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl m_dateCtrl;    //添加“日期”变量
	CComboBox m_comboTIME;       //添加“时间”组合框变量
	CComboBox m_comboMeetingRoom;//添加“会议室”组合框变量
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedReservecancleButton();
	afx_msg void OnBnClickedOk();
	int m_iTime;                 //存放时间组合框索引号
	CTime m_dateTime;            //存放日期
	int m_iMeetingRoom;          //存放会议室索引号
	
	
};
