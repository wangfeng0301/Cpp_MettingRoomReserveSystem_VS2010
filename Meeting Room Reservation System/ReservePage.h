#pragma once


// CReservePage 对话框

class CReservePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CReservePage)

public:
	CReservePage();
	virtual ~CReservePage();

// 对话框数据
	enum { IDD = IDD_RESERVE_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
};
