#pragma once
#include "afxcmn.h"


// CMeetRoom112 对话框

class CMeetingRoom112Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMeetingRoom112Dlg)

public:
	CMeetingRoom112Dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMeetingRoom112Dlg();

// 对话框数据
	enum { IDD = IDD_MEETINGROOM112_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	// 生成的消息映射函数
	DECLARE_MESSAGE_MAP()

public:
	CListCtrl m_MeetingRoom112InfoList;//存放会议室112列表信息
	virtual BOOL OnInitDialog();         //初始化函数，创建会议室112列表
	void UpdateMeetingRoom112();         //刷新列表信息
};
