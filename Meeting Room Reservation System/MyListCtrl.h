#pragma once
#include "afxcmn.h"
class CMyListCtrl :
	public CListCtrl
{
public:
	CMyListCtrl(void);
	~CMyListCtrl(void);

	afx_msg void OnCustomDraw(NMHDR* pNMHDR,LRESULT* prESULT); //消息函数声明

	int m_iRowHeight;  //设置行高变量
};

