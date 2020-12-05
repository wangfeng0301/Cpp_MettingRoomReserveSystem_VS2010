#pragma once
#include "afxcmn.h"


// CMeetingRoom 对话框

class CMeetingRoom408Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMeetingRoom408Dlg)

public:
	CMeetingRoom408Dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMeetingRoom408Dlg();

// 对话框数据
	enum { IDD = IDD_MEETINGROOM408_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CListCtrl m_MeetingRoom408InfoList;//存放会议室408列表信息
	virtual BOOL OnInitDialog();         //初始化函数
	void UpdateMeetingRoom408();         //刷新列表信息
};
