
// Meeting Room Reservation System.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Meeting Room Reservation System.h"
#include "Meeting Room Reservation SystemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMeetingRoomReservationSystemApp

BEGIN_MESSAGE_MAP(CMeetingRoomReservationSystemApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMeetingRoomReservationSystemApp 构造

CMeetingRoomReservationSystemApp::CMeetingRoomReservationSystemApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CMeetingRoomReservationSystemApp 对象

CMeetingRoomReservationSystemApp theApp;


// CMeetingRoomReservationSystemApp 初始化

BOOL CMeetingRoomReservationSystemApp::InitInstance()
{
	//AfxOleInit();//初始化COM控件，否则无法打开COM服务器。操作Excel时添加此句。
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CMeetingRoomReservationSystemDlg dlg;//定义对话框类CMeetingRoomReservationSystemDlg的对象dlg
	m_pMainWnd = &dlg;                   //将dlg设置为主窗口
	INT_PTR nResponse = dlg.DoModal();   //弹出对话框dlg，并将DoModal函数的返回值（退出时点击按钮的ID）赋值给nResponse
	if (nResponse == ID_ENTRY)           //判断返回值是否为登录按钮
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == ID_LOGIN)      //判断返回值是否为注册按钮
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

