
// Meeting Room Reservation System.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMeetingRoomReservationSystemApp:
// �йش����ʵ�֣������ Meeting Room Reservation System.cpp
//

class CMeetingRoomReservationSystemApp : public CWinApp
{
public:
	CMeetingRoomReservationSystemApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMeetingRoomReservationSystemApp theApp;