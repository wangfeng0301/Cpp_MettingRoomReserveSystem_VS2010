#pragma once
#include "afxcmn.h"


// CMeetingRoom409 对话框

class CMeetingRoom409Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMeetingRoom409Dlg)

public:
	CMeetingRoom409Dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMeetingRoom409Dlg();              // 析构函数

// 对话框数据
	enum { IDD = IDD_MEETINGROOM409_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CListCtrl m_MeetingRoom409InfoList;//存放会议室409列表信息
	virtual BOOL OnInitDialog();       //初始化函数
	void UpdateMeetingRoom409();       //刷新列表信息函数
};
