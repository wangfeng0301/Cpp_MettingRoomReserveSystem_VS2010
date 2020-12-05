//CMyPublicData.h  :头文件

#pragma once
#include "Meeting Room Reservation SystemDlg.h"
#include "MeetingRoom112Dlg.h"
#include "MeetingRoom408Dlg.h"
#include "MeetingRoom409Dlg.h"

//全局类，声明几个全局变量
class CMyPublicData
{
	// 构造
public:
	CMyPublicData();	// 标准构造函数

	int m_i112[14][8];  //二维指针数组存放112会议室信息,值为0，表示无人预约，为1表示***预约，为2表示？？？预约
	int m_i408[14][8];  //二维指针数组存放408会议室信息
	int m_i409[14][8];  //二维指针数组存放409会议室信息

};