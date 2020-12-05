#pragma once


// CErrorPassword 对话框

class CErrorPassword : public CDialogEx
{
	DECLARE_DYNAMIC(CErrorPassword)

public:
	CErrorPassword(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CErrorPassword();

// 对话框数据
	enum { IDD = IDD_ERRORPASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
