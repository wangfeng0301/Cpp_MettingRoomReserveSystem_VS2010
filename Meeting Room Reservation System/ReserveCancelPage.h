#pragma once


// CReserveCancelPage �Ի���

class CReserveCancelPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CReserveCancelPage)

public:
	CReserveCancelPage();
	virtual ~CReserveCancelPage();

// �Ի�������
	enum { IDD = IDD_RESERVECANCEL_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
};
