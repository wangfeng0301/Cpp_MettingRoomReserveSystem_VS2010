// ReserveDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Meeting Room Reservation System.h"
#include "Meeting Room Reservation SystemDlg.h"//添加主界面头文件
#include "ReserveDlg.h"
#include "afxdialogex.h"


// CReserveDlg 对话框

IMPLEMENT_DYNAMIC(CReserveDlg, CDialogEx)

CReserveDlg::CReserveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReserveDlg::IDD, pParent)
{

}

CReserveDlg::~CReserveDlg()
{
}

void CReserveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//处理控件IDC_TIME_COMBO和变量m_comboTIME之间的数据交换
	DDX_Control(pDX, IDC_TIME_COMBO, m_comboTIME);
	//处理控件IDC_TIME_COMBO和变量m_comboTIME之间的数据交换
	DDX_Control(pDX, IDC_MEETINGROOM_COMBO, m_comboMeetingRoom);
	//处理控件IDC_DATETIMEPICKER和变量m_comboWEEK之间的数据交换
	DDX_Control(pDX, IDC_DATETIMEPICKER, m_dateCtrl);
}

//CReserveDlg 初始化函数
BOOL CReserveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//设置Date Time Picker控件允许选择的日期时间范围
	CTime m_startTime = CTime::GetCurrentTime();
	CTimeSpan m_timeSpan(7, 0, 0, 0); // 70 days, 0 hour, 0 min, o second.
	CTime m_endTime = m_startTime + m_timeSpan;
	m_dateCtrl.SetRange(&m_startTime, &m_endTime);

	m_comboTIME.InsertString(0,_T("8:00-9:00"));//为“时间”组合框控件的列表框添加列表项8:00-9:00
	m_comboTIME.InsertString(1,_T("9:00-10:00"));//为“时间”组合框控件的列表框添加列表项
	m_comboTIME.InsertString(2,_T("10:00-11:00"));//为“时间”组合框控件的列表框添加列表项
	m_comboTIME.InsertString(3,_T("11:00-12:00"));//为“时间”组合框控件的列表框添加列表项
	m_comboTIME.InsertString(4,_T("12:00-13:00"));//为“时间”组合框控件的列表框添加列表项
	m_comboTIME.InsertString(5,_T("13:00-14:00"));//为“时间”组合框控件的列表框添加列表项
	m_comboTIME.InsertString(6,_T("14:00-15:00"));//为“时间”组合框控件的列表框添加列表项
	m_comboTIME.InsertString(7,_T("15:00-16:00"));//为“时间”组合框控件的列表框添加列表项
	m_comboTIME.InsertString(8,_T("16:00-17:00"));//为“时间”组合框控件的列表框添加列表项
	m_comboTIME.InsertString(9,_T("17:00-18:00"));//为“时间”组合框控件的列表框添加列表项
	m_comboTIME.InsertString(10,_T("18:00-19:00"));//为“时间”组合框控件的列表框添加列表项
	m_comboTIME.InsertString(11,_T("19:00-20:00"));//为“时间”组合框控件的列表框添加列表项
	m_comboTIME.InsertString(12,_T("20:00-21:00"));//为“时间”组合框控件的列表框添加列表项
	m_comboTIME.InsertString(13,_T("21:00-22:00"));//为“时间”组合框控件的列表框添加列表项
	m_comboTIME.SelectString(0,_T("8:00-9:00"));//选择列表框选项，若存在设为默认显示

	
	m_comboMeetingRoom.InsertString(0,_T("112"));//为组合框控件的列表框添加列表项112
	m_comboMeetingRoom.InsertString(1,_T("408"));//为组合框控件的列表框添加列表项409
	m_comboMeetingRoom.InsertString(2,_T("409"));//为组合框控件的列表框添加列表项408,插入指定位置，0是第一个，1是第二个...
	m_comboMeetingRoom.SelectString(1,_T("408"));//选择列表框选项，若存在设为默认显示

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

BEGIN_MESSAGE_MAP(CReserveDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CReserveDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RESERVECANCLE_BUTTON, &CReserveDlg::OnBnClickedReservecancleButton)
	ON_BN_CLICKED(IDOK, &CReserveDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CReserveDlg 消息处理程序

//单击“取消”按钮时消息处理函数
void CReserveDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();//直接退出
}


//单击“取消预约”按钮时消息处理函数
void CReserveDlg::OnBnClickedReservecancleButton()
{
	UpdateData(FALSE);
	//函数m_comboTIME.GetCurSel()可获取组合框当前选中的索引号，即行列信息
	m_iTime = m_comboTIME.GetCurSel();              //行索引号
	m_dateCtrl.GetTime(m_dateTime);                 //获取Date Time Picker控件被选中的日期
	m_iMeetingRoom = m_comboMeetingRoom.GetCurSel();//会议室索引号
	UpdateData(FALSE);
	EndDialog(IDC_RESERVECANCLE_BUTTON);            //关闭预约窗口并返回值IDC_RESERVECANCLE_BUTTON
}

//单击“预约”时消息处理函数
//实现将之前在组合框中选中的信息，即对应的表格，对应的数组进行数值赋值
void CReserveDlg::OnBnClickedOk()
{	
	//函数m_comboTIME.GetCurSel()可获取组合框当前选中的索引号，即行列信息
	m_iTime = m_comboTIME.GetCurSel();              //行索引号
	m_dateCtrl.GetTime(m_dateTime);                 //获取Date Time Picker控件被选中的日期
	m_iMeetingRoom = m_comboMeetingRoom.GetCurSel();//会议室索引号
	CDialog::OnOK();                                //返回IDOK
}
