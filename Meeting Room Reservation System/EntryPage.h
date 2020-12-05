#pragma once


// CEntryPage 对话框

class CEntryPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CEntryPage)

public:
	CEntryPage();
	virtual ~CEntryPage();

// 对话框数据
	enum { IDD = IDD_ENTRY_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
};
