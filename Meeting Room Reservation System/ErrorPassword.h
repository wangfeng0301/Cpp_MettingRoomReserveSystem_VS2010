#pragma once


// CErrorPassword �Ի���

class CErrorPassword : public CDialogEx
{
	DECLARE_DYNAMIC(CErrorPassword)

public:
	CErrorPassword(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CErrorPassword();

// �Ի�������
	enum { IDD = IDD_ERRORPASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
