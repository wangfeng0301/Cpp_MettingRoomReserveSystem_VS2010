//CMyPublicData.h  :ͷ�ļ�

#pragma once
#include "Meeting Room Reservation SystemDlg.h"
#include "MeetingRoom112Dlg.h"
#include "MeetingRoom408Dlg.h"
#include "MeetingRoom409Dlg.h"

//ȫ���࣬��������ȫ�ֱ���
class CMyPublicData
{
	// ����
public:
	CMyPublicData();	// ��׼���캯��

	int m_i112[14][8];  //��άָ��������112��������Ϣ,ֵΪ0����ʾ����ԤԼ��Ϊ1��ʾ***ԤԼ��Ϊ2��ʾ������ԤԼ
	int m_i408[14][8];  //��άָ��������408��������Ϣ
	int m_i409[14][8];  //��άָ��������409��������Ϣ

};