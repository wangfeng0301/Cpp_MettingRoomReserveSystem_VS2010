#pragma once


// CAccountNotExist 对话框

class CAccountNotExist : public CDialogEx
{
	DECLARE_DYNAMIC(CAccountNotExist)

public:
	CAccountNotExist(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAccountNotExist();

// 对话框数据
	enum { IDD = IDD_ACCOUNTNOTEXIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
