#pragma once
#include "afxcmn.h"
class CMyListCtrl :
	public CListCtrl
{
public:
	CMyListCtrl(void);
	~CMyListCtrl(void);

	afx_msg void OnCustomDraw(NMHDR* pNMHDR,LRESULT* prESULT); //��Ϣ��������

	int m_iRowHeight;  //�����и߱���
};

