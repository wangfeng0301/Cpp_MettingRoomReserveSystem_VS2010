#pragma once


// CReservePage �Ի���

class CReservePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CReservePage)

public:
	CReservePage();
	virtual ~CReservePage();

// �Ի�������
	enum { IDD = IDD_RESERVE_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
};
