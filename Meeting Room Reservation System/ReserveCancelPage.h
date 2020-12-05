#pragma once


// CReserveCancelPage 对话框

class CReserveCancelPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CReserveCancelPage)

public:
	CReserveCancelPage();
	virtual ~CReserveCancelPage();

// 对话框数据
	enum { IDD = IDD_RESERVECANCEL_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
};
