
// Meeting Room Reservation SystemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Meeting Room Reservation System.h"
#include "Meeting Room Reservation SystemDlg.h"
#include "afxdialogex.h"
#include "AccountNotExist.h"//添加“账号不存在”对话框头文件
#include "ErrorPassword.h"  //添加“密码错误”对话框头文件
#include "ReserveDlg.h"     //添加“预约”对话框头文件
#include "UsingSheet.h"     //添加“使用说明”属性表头文件
#include "MeetingRoom112Dlg.h"//添加112对话框头文件
#include "MeetingRoom408Dlg.h"//添加408对话框头文件
#include "MeetingRoom409Dlg.h"//添加409对话框头文件
#include "MyExcel.h"          //添加Excel类头文件

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//定义三个全局变量
int m_col = 14;                 //行
int m_row = 8;                  //列
int m_i112[14][8];              //二维指针数组存放112会议室信息,值为0，表示无人预约，为1表示***预约，为2表示？？？预约
int m_i408[14][8];              //二维指针数组存放408会议室信息
int m_i409[14][8];              //二维指针数组存放409会议室信息

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

//构造函数
CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{ 
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMeetingRoomReservationSystemDlg 对话框



//构造函数
CMeetingRoomReservationSystemDlg::CMeetingRoomReservationSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMeetingRoomReservationSystemDlg::IDD, pParent)
	, m_strAccount(_T(""))
	, m_strPassword(_T(""))
	//, m_strClass(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	for(int i=0;i<m_col;i++)//在构造函数中初始化数据成员
		for(int j=0;j<m_row;j++)
		{
			m_i112[i][j]=0;//初始化为0，即表格中都没有被预约
			m_i408[i][j]=0;
			m_i409[i][j]=0;
		}
}

void CMeetingRoomReservationSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	//处理MFC默认的数据交换
	CDialogEx::DoDataExchange(pDX);
	//处理控件IDC_ACCOUNT和变量m_strAccount之间的数据交换
	DDX_Text(pDX, IDC_ACCOUNT, m_strAccount);
	//处理控件IDC_PASSWORD和变量m_strPassword之间的数据交换
	DDX_Text(pDX, IDC_PASSWORD, m_strPassword);
	//处理控件IDC_MEETINGROOM_TAB和变量m_tabMeetingRoom之间的数据交换
	DDX_Control(pDX, IDC_MEETINGROOM_TAB, m_tabMeetingRoom);
	//处理日历控件IDC_MONTHCALENDAR与变量m_montCtrl之间的数据交换
	DDX_Control(pDX, IDC_MONTHCALENDAR, m_montCtrl);

}

BEGIN_MESSAGE_MAP(CMeetingRoomReservationSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_WM_MEASUREITEM_REFLECT()//用来调节列表高度用
	//ON_WM_MEASUREITEM()  //用来调节列表高度用
	//ON_WM_DRAWITEM()     //用来调节列表高度用
	ON_BN_CLICKED(ID_LOGIN, &CMeetingRoomReservationSystemDlg::OnBnClickedLogin)
	ON_BN_CLICKED(ID_ENTRY, &CMeetingRoomReservationSystemDlg::OnBnClickedEntry)
	ON_BN_CLICKED(IDC_RESERVE_BUTTON, &CMeetingRoomReservationSystemDlg::OnBnClickedReserveButton)
	ON_BN_CLICKED(IDC_INSTRUCT_BUTTON, &CMeetingRoomReservationSystemDlg::OnBnClickedInstructButton)
	ON_BN_CLICKED(IDC_QUIT_BUTTON, &CMeetingRoomReservationSystemDlg::OnBnClickedQuitButton)
	ON_NOTIFY(TCN_SELCHANGE, IDC_MEETINGROOM_TAB, &CMeetingRoomReservationSystemDlg::OnTcnSelchangeMeetingroomTab)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMeetingRoomReservationSystemDlg 消息处理程序
//CMeetingRoomReservationSystemDlg 初始化函数
BOOL CMeetingRoomReservationSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//初始化显示登录界面
	ShowEntry();

	//启动定时器,参数：定时器编号，间隔时间（ms），
	SetTimer(1,1000,NULL);//定义编号为1，间隔时间1s

	//向工程所在文件写入程序数据库连接ini文件信息，ini文件动态保存近7天的预约数据。默认设置如下  
	CFileFind finder;   
	//查找是否存在ini文件，返回0，不存在，则生成一个新的默认设置的ini文件，这样就保证了我们更改后的设置每次都可用  
	BOOL ifFind = finder.FindFile(_T(".\\MeetingRoomInfo.ini"));
	if( !ifFind )  //如果没找到文件，将三个会议室数组数据加载到文件中，赋初值为0
	{  
		CTime m_CurTime = CTime::GetCurrentTime();  //存放当前时间日期
		CTimeSpan m_TimeSpan = CTimeSpan(1,0,0,0);  //时间间隔1天
		CString strYear,strMonth,strDay;            //存放年，月，日字符串
		CString strTemp_i;                          //定义两个字符串存放转换后的行//strTemp_j,不需要列。列的名字已经有了，用日期代替了
		CString strTemp;                            //存放字符0
		for(int j=1; j<m_row;j++)
		{
			strYear = m_CurTime.Format("_%Y");      //将年转换为字符串
			strMonth = m_CurTime.Format("/%m");     //将月转换为字符串
			strDay = m_CurTime.Format("/%d");       //将天转换为字符串
			for(int i=0; i<m_col; i++)
			{            
				strTemp_i.Format(_T("_%d"),i);//行转换成字符串
				//strTemp_j.Format(_T("_%d"),j);//列转换成字符串
				strTemp.Format(_T("%d"),0);   //将0转化为字符
				//从一个初始化文件的指定部分获取字符串，参数分别为：字段名；变量名；没有前两个参数时此值赋给变量；路径文件名    .\\MeetingRoomInfo.ini表示在程序当前文件夹中
				::WritePrivateProfileString(_T("MeetingRoomInfo112"),_T("i112") + strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
				::WritePrivateProfileString(_T("MeetingRoomInfo408"),_T("i408") + strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
				::WritePrivateProfileString(_T("MeetingRoomInfo409"),_T("i409") + strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
			}
			m_CurTime = m_CurTime + m_TimeSpan;//当前时间加上间隔时间就是列表第二栏 也就是第二天
		}
	}
	else  //文件存在则将文件中变量值加载到三个会议室数组中
	{
		//①将ini中前一天的键值删除,并添加第七天的值为0
		//②由于ini文件中的值改变了，但是三个数组m_i409[][]中的值没有与ini中的值对应，所以要更新数组中的值
		CMeetingRoomReservationSystemDlg::DeleteIni();	
	}

	/*查找当前目录下是否有MeetingRoomInfo.xls文件
	ifFind = finder.FindFile(_T(".\\MeetingRoomInfo.xls"));
	//如果没有就在当前路径下创建一个
	//if(!ifFind) 
	//{
	//	//CFile file;
	//	//CFileException exp;
	//	//CString strFileName = _T(".\\MeetingRoomInfo.xls");
	//	////创建文件,如果已经存在文件则会覆盖之前的内容，成功创建返回非0
	//	//BOOL bCreateFile = file.Open(strFileName,CFile::modeCreate,&exp);
	//	//if(!bCreateFile)  
	//	//{  
	//	//	MessageBox(_T("创建MeetingRoomInfo.xls文件失败！"));  
	//	//}

	//	//打开一个文件保存对话框  
	//	//string filePathStr(".\\MeetingRoomInfo.xls");  
	// //   string comment("");  
	//    CMyExcel Demon;  
	// //   //在用户路径下生成文件  
	// //   //将鼠标形状更改为漏洞状态  
	// //   theApp.BeginWaitCursor();         
	// //   if(!Demon.openfile(filePathStr,2))  
	// //   {  
	// //       MessageBox(_T("创建Excel文件失败！"));  
	// //   }  
	//     //我们往里面写入20列，每列1000行  
	//     //int iCount = 1;   
	//     //for(;iCount<=20;iCount++)  
	//     //{  
	//     //    char  valStr[10];  
	//     //    comment.clear();               //擦除字符串中所有元素
	//     //    sprintf_s(valStr,"%i",iCount); //写格式化数据到字符串，参数：输出存储单元，
	//     //    comment += "第";  
	//     //    comment +=valStr;  
	//     //    comment +="列";        
	//     //    Demon.writeMatrix(comment,mateDataReal,1,1000);  
	//     //}


	//	
	//	COleVariant类为VARIANT数据类型的包装，在自动化程序中，通常都使用 
	//	VARIANT数据类型进行参数传递。故下列程序中，函数参数都是通过COleVariant 
	//	类来转换了的。 
	//	  
	//	//covOptional 可选参数的VARIANT类型  
	//	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);  
	//	if( !Demon.m_app.CreateDispatch(_T("Excel.Application")) )
	//	{  
	//		this->MessageBox(_T("无法创建Excel应用！"));  
	//		return FALSE;  
	//	}


	//}*/
	 

	//初始化标签控件
	CRect tabRect;//标签控件客户区的位置和大小
	m_tabMeetingRoom.InsertItem(0,_T("112"));//插入第一个标签“112”
	m_tabMeetingRoom.InsertItem(1,_T("408"));//插入第二个标签“408”
	m_tabMeetingRoom.InsertItem(2,_T("409"));//插入第三个标签“409”
	m_MeetingRoom112.Create(IDD_MEETINGROOM112_DIALOG, &m_tabMeetingRoom);//创建第一个标签，顺序必须跟插入标签名字的顺序一致。
	m_MeetingRoom408.Create(IDD_MEETINGROOM408_DIALOG, &m_tabMeetingRoom);//创建第二个标签
	m_MeetingRoom409.Create(IDD_MEETINGROOM409_DIALOG, &m_tabMeetingRoom);//创建第三个标签

	m_tabMeetingRoom.GetClientRect(&tabRect);//获取标签控件客户区 Rect//调整 tabRect，使其覆盖范围适合放置标签页
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;
	//根据调整好的tabRect放置三个会议室对话框,放置的顺序必须跟插入标签名字的顺序一致。
	m_MeetingRoom112.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_SHOWWINDOW);
	m_MeetingRoom408.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_HIDEWINDOW);
	m_MeetingRoom409.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_HIDEWINDOW);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMeetingRoomReservationSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMeetingRoomReservationSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMeetingRoomReservationSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//单击“注册”按钮消息处理函数
void CMeetingRoomReservationSystemDlg::OnBnClickedLogin()
{
	// TODO: 在此添加控件通知处理程序代码

}

//单击“登录”按钮消息处理函数
void CMeetingRoomReservationSystemDlg::OnBnClickedEntry()
{
	INT_PTR nRes;                              //用于保存DoModal函数的返回值

	CAccountNotExist accountnotexist;          //构造对话框类CAccountNotExist的实例
	CErrorPassword   errorpassword;            //构造对话框类CErrorPassword的实例
	// 将各控件中的数据保存到相应的变量
	UpdateData(TRUE);

	if(m_strAccount == "***")
	{
		if(m_strPassword == "123456")
		{
			m_strPassword = "Entry successful!";//账号密码一致显示登录成功
			HideEntry();                        //隐藏登录界面
		}
		else
		{
			nRes = errorpassword.DoModal();     //账号一致密码不一致，弹出密码错误对话框
			
		}
	}
	else if(m_strAccount == "???")
	{
		if(m_strPassword == "12345")
		{
			m_strPassword = "Entry successful!";//账号密码一致显示登录成功
			HideEntry();                        //隐藏登录界面
		}
		else
		{
			nRes = errorpassword.DoModal();     //账号一致密码不一致，弹出密码错误对话框	
		}
	}
	else
	{
		nRes = accountnotexist.DoModal();     //账号不一致，弹出账号不存在对话框
	}
	//根据修改的个控件的值，显示出来
	UpdateData(FALSE);
}

//单击“退出登录”按钮消息处理函数
void CMeetingRoomReservationSystemDlg::OnBnClickedQuitButton()
{
	m_strAccount = "";    //账号清空
	m_strPassword = "";   //密码清空
	SetDlgItemText(IDC_ACCOUNT,m_strAccount);   //清空编辑框显示
	SetDlgItemText(IDC_PASSWORD,m_strPassword); //清空编辑框显示
	ShowEntry();          //显示登录界面
}

//单击“预约”按钮消息处理函数
void CMeetingRoomReservationSystemDlg::OnBnClickedReserveButton()
{
	INT_PTR nRes;                              //用于保存DoModal函数和MessageBox函数的返回值
	CReserveDlg reserveDlg;                    //构造对话框CReserveDlg的实例

	// 将各控件中的数据保存到相应的变量
	if(m_strPassword == "Entry successful!")   //如已成功登录，弹出预约对话框
	{
		nRes = reserveDlg.DoModal();           //弹出“预约”对话框

		//不管预约还是取消预约，首先获取预约对话框中选择的教室、时间、日期信息；
		//以及当前时间日期。
		int i = reserveDlg.m_iTime;           //获取列表被修改表格行序号
		int j;                                //获取列表被修改表格列序号
		CTime m_CurTime = CTime::GetCurrentTime();      //获取系统时间
		CTimeSpan m_TimeSpan = CTimeSpan(1,0,0,0);      //时间间隔1天
		CString strYear,strMonth,strDay;                //存放年，月，日字符串
		/*for循环用来判断预约对话框选定的日期，选定的日期跟列表上的日期比较，看是第几列
		  因为列表一共显示七天的信息，而且列表的0序号列存放时间，所以从1序号列开始。
		  跟当天的日期比较是因为列表的序号1列显示的是当天的日期*/
		for(int i = 1;i < m_row; i++)
		{
			if(m_CurTime.Format("%Y/%m/%d") == reserveDlg.m_dateTime.Format("%Y/%m/%d"))//选定的日期跟列表上的日期比较，看是第几列
			{
				j = i;                                  //列表的列序号赋值
				strYear = m_CurTime.Format("_%Y");      //将年转换为字符串
				strMonth = m_CurTime.Format("/%m");     //将月转换为字符串
				strDay = m_CurTime.Format("/%d");       //将天转换为字符串
				break;                                  //一旦找到列序号就退出for循环
			}	
			m_CurTime = m_CurTime + m_TimeSpan;//没找到就加1天，继续寻找
		}
		CString strTemp_i;            //定义两个字符串存放转换后的行列//strTemp_j,不需要列。列的名字已经有了，用日期代替了
		CString strTemp;              //定义中间变量存放整型值转化后的字符串
		strTemp_i.Format(_T("_%d"),i);//行转换成字符串
		if(IDC_RESERVECANCLE_BUTTON == nRes)   //返回取消预约
		{
			//取消预约后将CMeetingRoomReservationSystemDlg对话框右侧的数据更新，对应取消的表格为空
			switch(reserveDlg.m_iMeetingRoom)  //判断选择的会议室索引号
			{
				//判断要取消的表格信息是否与登陆者信息一致，一致才能取消预约，否则弹出警告
				case 0: if(m_strAccount == m_MeetingRoom112.m_MeetingRoom112InfoList.GetItemText(i,j))
						{
							m_i112[i][j] = 0;
							strTemp.Format(_T("%d"),m_i112[i][j]);//将行列号转换为字符串
							//将改变的值保存在.ini文件中，下次开机初始化时使用
							::WritePrivateProfileString(_T("MeetingRoomInfo112"),_T("i112") + strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
						}	
					break;//索引号0表示会议室112
				case 1: if(m_strAccount == m_MeetingRoom408.m_MeetingRoom408InfoList.GetItemText(i,j))
						{
							m_i408[i][j] = 0;
							strTemp.Format(_T("%d"),m_i408[i][j]);//将行列号转换为字符串
							//将改变的值保存在.ini文件中，下次开机初始化时使用
							::WritePrivateProfileString(_T("MeetingRoomInfo408"),_T("i408")+ strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
						}
					break;//索引号1表示会议室408
				case 2: if(m_strAccount == m_MeetingRoom409.m_MeetingRoom409InfoList.GetItemText(i,j))
						{
							m_i409[i][j] = 0;
							strTemp.Format(_T("%d"),m_i409[i][j]);//将行列号转换为字符串
							//将改变的值保存在.ini文件中，下次开机初始化时使用
							::WritePrivateProfileString(_T("MeetingRoomInfo409"),_T("i409")+ strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
						}
					break;//索引号2表示会议室409
				default: //显示提示对话框，只有OK按钮，和提示图标
						nRes = MessageBox(_T("您没有操作权限！无法取消其他用户预约！"), NULL, MB_OK | MB_ICONWARNING);
						break;
			}
			m_MeetingRoom112.UpdateMeetingRoom112();//刷新112列表信息
			m_MeetingRoom408.UpdateMeetingRoom408();//刷新408列表信息
			m_MeetingRoom409.UpdateMeetingRoom409();//刷新409列表信息
		}				
		else if(IDOK == nRes)                  //返回确定预约，更新列表信息
		{
			//确定预约后将CMeetingRoomReservationSystemDlg对话框右侧的数据更新
			if( (m_strAccount == "***"))// 判断当前登录的账户信息
			{	                    
				//若登录名为***，判断选择的会议室，若为空则将之前组合框中选中的对应行列表格赋值1
				switch(reserveDlg.m_iMeetingRoom)  //判断选择的会议室索引号
				{
					case 0: 
						if(m_MeetingRoom112.m_MeetingRoom112InfoList.GetItemText(i,j) == _T(" "))
						{
							m_i112[i][j] = 1;                     //索引号0表示会议室112
							strTemp.Format(_T("%d"),m_i112[i][j]);//将行列号转换为字符串
							//将改变的值保存在.ini文件中，下次开机初始化时使用
							::WritePrivateProfileString(_T("MeetingRoomInfo112"),_T("i112")+ strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
						}
						break;
					case 1: 
						if(m_MeetingRoom408.m_MeetingRoom408InfoList.GetItemText(i,j) == _T(" "))
						{
							m_i408[i][j] = 1;                     //索引号1表示会议室408
							strTemp.Format(_T("%d"),m_i408[i][j]);//将行列号转换为字符串
							//将改变的值保存在.ini文件中，下次开机初始化时使用
							::WritePrivateProfileString(_T("MeetingRoomInfo408"),_T("i408")+ strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
						}
						break;
					case 2: 
						if(m_MeetingRoom409.m_MeetingRoom409InfoList.GetItemText(i,j) == _T(" "))
						{
							m_i409[i][j] = 1;                     //索引号0表示会议室409
							strTemp.Format(_T("%d"),m_i409[i][j]);//将行列号转换为字符串
							//将改变的值保存在.ini文件中，下次开机初始化时使用
							::WritePrivateProfileString(_T("MeetingRoomInfo409"),_T("i409")+ strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
						}
						break;
					default:
						MessageBox(_T("此时间段已被预约！"), NULL, MB_OK | MB_ICONWARNING);//若已被预约弹出提示信息
						break;
				}	
			}
			if( (m_strAccount == "???"))
			{
				//若登录名为???，判断选择的会议室，若为空则将之前组合框中选中的对应行列表格赋值2
				switch(reserveDlg.m_iMeetingRoom)  //判断选择的会议室索引号
				{
					case 0: 
						if(m_MeetingRoom112.m_MeetingRoom112InfoList.GetItemText(i,j) == _T(" "))
						{
							m_i112[i][j] = 2;                     //索引号0表示会议室112
							strTemp.Format(_T("%d"),m_i112[i][j]);//将行列号转换为字符串
							//将改变的值保存在.ini文件中，下次开机初始化时使用
							::WritePrivateProfileString(_T("MeetingRoomInfo112"),_T("i112")+ strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
						}
						break;
					case 1: 
						if(m_MeetingRoom408.m_MeetingRoom408InfoList.GetItemText(i,j) == _T(" "))
						{
							m_i408[i][j] = 2;                     //索引号1表示会议室408
							strTemp.Format(_T("%d"),m_i408[i][j]);//将行列号转换为字符串
							//将改变的值保存在.ini文件中，下次开机初始化时使用
							::WritePrivateProfileString(_T("MeetingRoomInfo408"),_T("i408")+ strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
						}
						break;
					case 2: 
						if(m_MeetingRoom409.m_MeetingRoom409InfoList.GetItemText(i,j) == _T(" "))
						{
							m_i409[i][j] = 2;                     //索引号0表示会议室409
							strTemp.Format(_T("%d"),m_i409[i][j]);//将行列号转换为字符串
							//将改变的值保存在.ini文件中，下次开机初始化时使用
							::WritePrivateProfileString(_T("MeetingRoomInfo409"),_T("i409")+ strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
						}
						break;
					default:
						MessageBox(_T("此时间段已被预约！"), NULL, MB_OK | MB_ICONWARNING);//若已被预约弹出提示信息
						break;
				}
			}
			//此处可添加登录账户信息

			//点击完确定预约按钮后，更新列表信息
			m_MeetingRoom112.UpdateMeetingRoom112();//刷新112列表信息
			m_MeetingRoom408.UpdateMeetingRoom408();//刷新408列表信息
			m_MeetingRoom409.UpdateMeetingRoom409();//刷新409列表信息
		}
		else
		{
			return;
		}
	} 
	else   //如未成功登录，弹出消息对话框，提示请先登录！
	{
		//显示消息对话框，只有OK按钮，和提示图标
		nRes = MessageBox(_T("请先登录！"), NULL, MB_OK | MB_ICONWARNING);	
	} 
}

//单击“使用说明”按钮时消息处理函数
void CMeetingRoomReservationSystemDlg::OnBnClickedInstructButton()
{
	// TODO: 在此添加控件通知处理程序代码
	//创建属性表对象
	CUsingSheet sheet(_T(""));

	//设置属性对话框为向导对话框
	sheet.SetWizardMode();

	//打开模态向导对话框
	sheet.DoModal();
}

//隐藏登录界面
void CMeetingRoomReservationSystemDlg::HideEntry()
{
	GetDlgItem(IDC_QUIT_BUTTON)->ShowWindow(SW_SHOW);     //显示“退出登录”按钮
	GetDlgItem(IDC_ENTRYSUCCESS_TIP_STATIC)->ShowWindow(SW_SHOW);//显示登录成功提示
	GetDlgItem(IDC_PASSWORD_STATIC)->ShowWindow(SW_HIDE); //隐藏下面的信息
	GetDlgItem(IDC_ACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PASSWORD)->ShowWindow(SW_HIDE);
	GetDlgItem(ID_LOGIN)->ShowWindow(SW_HIDE);
    GetDlgItem(ID_ENTRY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ACCOUNT_STATIC)->ShowWindow(SW_HIDE);
}

//显示登录界面
void CMeetingRoomReservationSystemDlg::ShowEntry()
{
	GetDlgItem(IDC_QUIT_BUTTON)->ShowWindow(SW_HIDE);    //隐藏“退出登录”按钮
	GetDlgItem(IDC_ENTRYSUCCESS_TIP_STATIC)->ShowWindow(SW_HIDE);//隐藏登录成功提示
	GetDlgItem(IDC_PASSWORD_STATIC)->ShowWindow(SW_SHOW);//显示下面的信息
	GetDlgItem(IDC_ACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_PASSWORD)->ShowWindow(SW_SHOW);
	GetDlgItem(ID_LOGIN)->ShowWindow(SW_SHOW);
    GetDlgItem(ID_ENTRY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ACCOUNT_STATIC)->ShowWindow(SW_SHOW);
}

//Tab切换页面消息处理函数
void CMeetingRoomReservationSystemDlg::OnTcnSelchangeMeetingroomTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CRect tabRect;               //标签控件客户区的Rect

	//获取标签控件客户区 Rect，调整 tabRect，使其覆盖范围适合放置标签页
	m_tabMeetingRoom.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;

	switch(m_tabMeetingRoom.GetCurSel())//获取当前标签的索引号，一个标签对应一个索引号，参考初始化代码
	{
		//如果标签当前选择为“112”，（112对应索引号是0），则显示m_MeetingRoom112对话框，隐藏其他对话框
		case 0:
			m_MeetingRoom112.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_SHOWWINDOW);
			m_MeetingRoom408.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_HIDEWINDOW);
			m_MeetingRoom409.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_HIDEWINDOW);
			break;
		//如果标签当前选择为“408”，（408对应索引号是1），则显示m_MeetingRoom408对话框，隐藏其他对话框
		case 1:
			m_MeetingRoom112.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_HIDEWINDOW);
			m_MeetingRoom408.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_SHOWWINDOW);
			m_MeetingRoom409.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_HIDEWINDOW);
			break;
		//如果标签当前选择为“409”，（409对应索引号是2），则显示m_MeetingRoom409对话框，隐藏其他对话框
		case 2:
			m_MeetingRoom112.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_HIDEWINDOW);
			m_MeetingRoom408.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_HIDEWINDOW);
			m_MeetingRoom409.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_SHOWWINDOW);
			break;
		default:
			break;
	}
}

//定时器消息处理函数，1s执行一次此函数
void CMeetingRoomReservationSystemDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CTime m_CurTime = CTime::GetCurrentTime();  //获取系统时间
	CString str = m_CurTime.Format("%H:%M:%S"); //将系统时间保存在字符串中，时，分，秒
	switch(nIDEvent)
	{
	case 1:SetDlgItemText(IDC_TIME_EDIT,str);  break;//显示系统时间
	default:break;
	}
	/*零点时刻进行几个操作：
	①将ini中前一天的键值删除,并添加第七天的值为0
	②由于ini文件中的值改变了，但是三个数组m_i409[][]中的值没有与ini中的值对应，所以要更新数组中的值
	③列表重新初始化，显示更新后的值
	*/
	if((m_CurTime.GetHour() == 0) && (m_CurTime.GetMinute() == 0) && (m_CurTime.GetSecond() == 0))
	{	
		CMeetingRoomReservationSystemDlg::DeleteIni();
		//列表重新初始化
		m_MeetingRoom409.OnInitDialog();
		m_MeetingRoom408.OnInitDialog();
		m_MeetingRoom112.OnInitDialog();
	}
	//CDialogEx::OnTimer(nIDEvent);
}


//①将ini中前一天的键值删除,并添加第七天的值为0
//②由于ini文件中的值改变了，但是三个数组m_i409[][]中的值没有与ini中的值对应，所以要更新数组中的值
void CMeetingRoomReservationSystemDlg::DeleteIni()
{
	CTime m_CurTime = CTime::GetCurrentTime();  //获取系统时间
	CTimeSpan m_TimeSpan = CTimeSpan(1,0,0,0);  //时间间隔1天
	CTime m_ProTime = m_CurTime - m_TimeSpan;   //存放之前1天的日期
	m_TimeSpan = CTimeSpan(6,0,0,0);            //重新赋值，时间间隔7天
	m_CurTime = m_CurTime + m_TimeSpan;         //存放之后第七天日期
	CString strYear,strMonth,strDay;            //存放年，月，日字符串
	CString strProYear,strProMonth,strProDay;   //存放之前年，月，日字符串
	CString strTemp_i;                          //定义两个字符串存放转换后的行列//strTemp_j,不需要列。列的名字已经有了，用日期代替了
	CString strTemp;                            //存放字符0
	
	strYear = m_CurTime.Format("_%Y");       //将年转换为字符串
	strMonth = m_CurTime.Format("/%m");      //将月转换为字符串
	strDay = m_CurTime.Format("/%d");        //将天转换为字符串
	strProYear = m_ProTime.Format("_%Y");       //将年转换为字符串
	strProMonth = m_ProTime.Format("/%m");      //将月转换为字符串
	strProDay = m_ProTime.Format("/%d");        //将天转换为字符串
	strTemp.Format(_T("%d"),0);                 //将0转化为字符
	/*零点时刻将ini中前一天的键值删除,并添加第七天的值为0*/
	for(int i = 0;i<m_col;i++)
	{
		strTemp_i.Format(_T("_%d"),i);          //行转换成字符串
		::WritePrivateProfileString(_T("MeetingRoomInfo112"),_T("i112") + strProYear + strProMonth + strProDay + strTemp_i,NULL,_T(".\\MeetingRoomInfo.ini"));
		::WritePrivateProfileString(_T("MeetingRoomInfo408"),_T("i408") + strProYear + strProMonth + strProDay + strTemp_i,NULL,_T(".\\MeetingRoomInfo.ini"));
		::WritePrivateProfileString(_T("MeetingRoomInfo409"),_T("i409") + strProYear + strProMonth + strProDay + strTemp_i,NULL,_T(".\\MeetingRoomInfo.ini"));
	
		::WritePrivateProfileString(_T("MeetingRoomInfo112"),_T("i112") + strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
		::WritePrivateProfileString(_T("MeetingRoomInfo408"),_T("i408") + strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
		::WritePrivateProfileString(_T("MeetingRoomInfo409"),_T("i409") + strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
	}
	//由于ini文件中的值改变了，但是三个数组m_i409[][]中的值没有与ini中的值对应，所以要更新数组中的值。
	m_CurTime = CTime::GetCurrentTime();      //存放当前时间日期
	m_TimeSpan = CTimeSpan(1,0,0,0);          //时间间隔1天
	for(int j=1; j<m_row; j++)
	{
		strYear = m_CurTime.Format("_%Y");    //将年转换为字符串
		strMonth = m_CurTime.Format("/%m");   //将月转换为字符串
		strDay = m_CurTime.Format("/%d");     //将天转换为字符串
		for(int i=0; i<m_col;i++)
		{
			strTemp_i.Format(_T("_%d"),i);    //行转换成字符串
			//从一个初始化文件的指定部分获取字符串，参数分别为：字段名；变量名；没有前两个参数时此值赋给变量；路径文件名.  .\\MeetingRoomInfo.ini表示在程序当前文件夹中    
			//若变量不存在，则默认在ini文件中先创建次变量，并赋值0
			m_i112[i][j] = GetPrivateProfileInt(_T("MeetingRoomInfo112"),_T("i112")+strYear+strMonth+strDay+strTemp_i,0,_T(".\\MeetingRoomInfo.ini"));
			m_i408[i][j] = GetPrivateProfileInt(_T("MeetingRoomInfo408"),_T("i408")+strYear+strMonth+strDay+strTemp_i,0,_T(".\\MeetingRoomInfo.ini"));
			m_i409[i][j] = GetPrivateProfileInt(_T("MeetingRoomInfo409"),_T("i409")+strYear+strMonth+strDay+strTemp_i,0,_T(".\\MeetingRoomInfo.ini"));	
		}
		m_CurTime = m_CurTime + m_TimeSpan;//当前时间加上间隔时间就是列表第二栏 也就是第二天
	}
}
//
//void CMyListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)  
//{  
//    if (m_nRowHeight>0)  
//    {  
//        lpMeasureItemStruct->itemHeight = m_nRowHeight;  
//    }  
//}  
//
////
//void CMyListCtrl::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)  
//{  
//    // TODO: 在此添加消息处理程序代码和/或调用默认值  
//    CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);  
//}
//
////
//void CMyListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)  
//{  
//  CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);      
//  LVITEM lvi = {0};   
//  lvi.mask = LVIF_STATE;//|LVIF_IMAGE;   
//  lvi.stateMask = LVIS_FOCUSED | LVIS_SELECTED ;   
//  lvi.iItem = lpDrawItemStruct->itemID;   
//  BOOL bGet = GetItem(&lvi);   
//    
//  //高亮显示    
//  BOOL bHighlight =((lvi.state & LVIS_DROPHILITED)||((lvi.state & LVIS_SELECTED)   
//  && ((GetFocus() == this)|| (GetStyle() & LVS_SHOWSELALWAYS))));  
//    
//  //画文本背景   
//  CRect rcBack = lpDrawItemStruct->rcItem;   
//  pDC->SetBkMode(TRANSPARENT);   
//    
//  if( bHighlight ) //如果被选中  
//  {   
//    pDC->SetTextColor(RGB(255,255,255));              //文本颜色  
//    pDC->FillRect(rcBack, &CBrush(RGB(90,162,100)));  //行背景色  
//  }   
//  else   
//  {   
//    pDC->SetTextColor(RGB(0,0,0));                    //文本颜色  
//    pDC->FillRect(rcBack, &CBrush(RGB(255,255,255))); //行背景色  
//  }   
//    
//  //绘制文本  
//  if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)   
//  {   
//    //得到列数  
//    int nCollumn = GetHeaderCtrl()->GetItemCount();  
//      
//    //循环处理  
//    CString szText;   
//    for (int i = 0; i < GetHeaderCtrl()->GetItemCount(); i++)   
//    {    
//      CRect rcItem;   
//      if ( !GetSubItemRect(lpDrawItemStruct->itemID, i, LVIR_LABEL, rcItem ))  
//      {   
//        continue;   
//      }  
//        
//      szText = GetItemText( lpDrawItemStruct->itemID, i );  
//        
//      rcItem.left += 5; rcItem.right -= 1;   
//      pDC->DrawText(szText, lstrlen(szText), &rcItem,    
//      DT_LEFT | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);    
//    }   
//  }   
//} 







