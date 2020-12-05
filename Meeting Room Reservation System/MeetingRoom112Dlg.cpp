// MeetRoom112.cpp : 实现文件
//

#include "stdafx.h"
#include "Meeting Room Reservation System.h"
#include "MeetingRoom112Dlg.h"
#include "afxdialogex.h"

//声明这三个全局变量在外部定义
extern int m_col;
extern int m_row;
extern int m_i112[14][8];              //二维指针数组存放112会议室信息,值为0，表示无人预约，为1表示***预约，为2表示？？？预约
extern int m_i408[14][8];              //二维指针数组存放408会议室信息
extern int m_i409[14][8];              //二维指针数组存放409会议室信息
// CMeetingRoom112Dlg 对话框

IMPLEMENT_DYNAMIC(CMeetingRoom112Dlg, CDialogEx)

CMeetingRoom112Dlg::CMeetingRoom112Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMeetingRoom112Dlg::IDD, pParent)
{	
}

CMeetingRoom112Dlg::~CMeetingRoom112Dlg()
{
}

void CMeetingRoom112Dlg::DoDataExchange(CDataExchange* pDX)
{
	//处理MFC默认的数据交换
	CDialogEx::DoDataExchange(pDX);
	//处理控件IDC_MEETINGROOM112INFO_LIST和变量m_MeetingRoom112InfoList之间的数据交换
	DDX_Control(pDX, IDC_MEETINGROOM112INFO_LIST, m_MeetingRoom112InfoList);
}

//CMeetingRoom112Dlg 初始化函数
BOOL CMeetingRoom112Dlg::OnInitDialog()
{

	CDialogEx::OnInitDialog();

	// TODO: 在此添加额外的初始化代码
	CTime m_CurTime = CTime::GetCurrentTime(); //获取系统时间
	CTimeSpan m_TimeSpan = CTimeSpan(1,0,0,0); //时间间隔1天
	CString strYear,strMonth,strDay;           //存放年，月，日字符串
	CString m_strDayofWeek;                    //保存周一 周二...

	CRect rect;   //实例化列表对象
	//获取列表视图控件的位置和大小
	m_MeetingRoom112InfoList.GetClientRect(&rect);
	//为列表视图控件添加栅格,自动换行
	m_MeetingRoom112InfoList.SetExtendedStyle(m_MeetingRoom112InfoList.GetExtendedStyle()  | LVS_EX_GRIDLINES |LVS_EX_TRACKSELECT);//
	//第一列为“时间”，参数分别为：列索引，列标题，列中文本对齐方式，列宽，插入列对应列表子项的索引
	m_MeetingRoom112InfoList.InsertColumn(0, _T("时间"), LVCFMT_CENTER, 80, 0);
	for(int i = 1;i<m_row;i++)//循环7次给列表每一列的头赋值
	{
		strYear = m_CurTime.Format("%Y");  //将年转换为字符串
		strMonth = m_CurTime.Format("%m"); //将月转换为字符串
		strDay = m_CurTime.Format("%d");   //将天转换为字符串
		switch(m_CurTime.GetDayOfWeek())
		{
			case 1:m_strDayofWeek = _T("周日\r\n")+ strMonth + _T("月") + strDay + _T("日");break;
			case 2:m_strDayofWeek = _T("周一\r\n")+ strMonth + _T("月") + strDay + _T("日");break;
			case 3:m_strDayofWeek = _T("周二\r\n")+ strMonth + _T("月") + strDay + _T("日");break;
			case 4:m_strDayofWeek = _T("周三\r\n")+ strMonth + _T("月") + strDay + _T("日");break;
			case 5:m_strDayofWeek = _T("周四\r\n")+ strMonth + _T("月") + strDay + _T("日");break;
			case 6:m_strDayofWeek = _T("周五\r\n")+ strMonth + _T("月") + strDay + _T("日");break;
			case 7:m_strDayofWeek = _T("周六\r\n")+ strMonth + _T("月") + strDay + _T("日");break;
			default:break;
		}
		m_CurTime = m_CurTime + m_TimeSpan;//当前时间加上间隔时间就是列表第二栏 也就是第二天
		m_MeetingRoom112InfoList.InsertColumn(i, m_strDayofWeek, LVCFMT_CENTER, 90, i);
	}

	//在列表视图控件中插入列表项，即行，并设置列表子项文本
	//行的序列号不算标题行
	CString str;//存放每行第一列名字
	for(int i = 0;i < m_col;i++)
	{
		str.Format(_T("%d:00-%d:00"),i+8,i+9);      //每行第一列名字8:00-9:00,9:00-10:00...
		m_MeetingRoom112InfoList.InsertItem(i, str);//第i行第1列
	}

	UpdateMeetingRoom112();//刷新列表信息
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


BEGIN_MESSAGE_MAP(CMeetingRoom112Dlg, CDialogEx)
END_MESSAGE_MAP()


// CMeetRoom112 消息处理程序
void CMeetingRoom112Dlg::UpdateMeetingRoom112()
{
	CString str;                   //声明一个字符串存放表格中的字符串信息
	for(int i=0; i<m_col;i++)
	{
		for(int j=1; j<m_row; j++)
		{
			//检测每个表格数值是几，为0表示无人预约，为1表示***预约，为2表示？？？预约
			switch(m_i112[i][j])
			{
				case 0:str = _T(" ");break;//数值为0时，表格中显示空格
				case 1:str = _T("***");break;//数值为1时，表格中显示***，表示被***预约
				case 2:str = _T("???");break;//数值为2时，表格中显示？？？，表示被？？？预约
					//此处可添加信息，值为3，4，5，6.。。。
				default:break;
			}					
			m_MeetingRoom112InfoList.SetItemText(i, j, str);//循环给每一个表格赋值,第i行第j列
		}
	}
}