#pragma once


// CEntryPage �Ի���

class CEntryPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CEntryPage)

public:
	CEntryPage();
	virtual ~CEntryPage();

// �Ի�������
	enum { IDD = IDD_ENTRY_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
};
