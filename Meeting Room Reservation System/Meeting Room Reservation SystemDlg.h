
// Meeting Room Reservation SystemDlg.h : 头文件

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "MeetingRoom112Dlg.h"//添加112对话框头文件
#include "MeetingRoom408Dlg.h"//添加408对话框头文件
#include "MeetingRoom409Dlg.h"//添加409对话框头文件
#include "afxdtctl.h"
#include "atltime.h"

// CMeetingRoomReservationSystemDlg 对话框
class CMeetingRoomReservationSystemDlg : public CDialogEx
{
// 构造
public:
	CMeetingRoomReservationSystemDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MEETINGROOMRESERVATIONSYSTEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strAccount;                    //保存账号编辑框中字符串
	CString m_strPassword;                   //保存密码编辑框中字符串
	CTabCtrl m_tabMeetingRoom;               //会议室选项卡
	CMeetingRoom409Dlg m_MeetingRoom409;     //添加会议室409类的变量
	CMeetingRoom408Dlg m_MeetingRoom408;     //添加会议室408类的变量
	CMeetingRoom112Dlg m_MeetingRoom112;     //添加会议室112类的变量
	CMonthCalCtrl m_montCtrl;                //添加日历变量
	

	afx_msg void OnBnClickedLogin();         //单击“注册”按钮消息处理函数
	afx_msg void OnBnClickedEntry();         //单击“登录”按钮消息处理函数
	afx_msg void OnBnClickedReserveButton(); //单击“预约”按钮消息处理函数
	afx_msg void OnBnClickedInstructButton();//单击“使用说明”按钮时消息处理函数
	afx_msg void OnBnClickedQuitButton();    //单击“退出登录”按钮时消息处理函数
	afx_msg void OnTcnSelchangeMeetingroomTab(NMHDR *pNMHDR, LRESULT *pResult);//切换标签控件选型卡消息处理函数
	afx_msg void OnTimer(UINT_PTR nIDEvent); //定时器消息处理函数
	
	void CMeetingRoomReservationSystemDlg::HideEntry();//隐藏登录界面
	void CMeetingRoomReservationSystemDlg::ShowEntry();//显示登录界面	
	void CMeetingRoomReservationSystemDlg::DeleteIni();//
};
