#pragma once


// CAccountNotExist �Ի���

class CAccountNotExist : public CDialogEx
{
	DECLARE_DYNAMIC(CAccountNotExist)

public:
	CAccountNotExist(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAccountNotExist();

// �Ի�������
	enum { IDD = IDD_ACCOUNTNOTEXIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
