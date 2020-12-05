
// Meeting Room Reservation SystemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Meeting Room Reservation System.h"
#include "Meeting Room Reservation SystemDlg.h"
#include "afxdialogex.h"
#include "AccountNotExist.h"//��ӡ��˺Ų����ڡ��Ի���ͷ�ļ�
#include "ErrorPassword.h"  //��ӡ�������󡱶Ի���ͷ�ļ�
#include "ReserveDlg.h"     //��ӡ�ԤԼ���Ի���ͷ�ļ�
#include "UsingSheet.h"     //��ӡ�ʹ��˵�������Ա�ͷ�ļ�
#include "MeetingRoom112Dlg.h"//���112�Ի���ͷ�ļ�
#include "MeetingRoom408Dlg.h"//���408�Ի���ͷ�ļ�
#include "MeetingRoom409Dlg.h"//���409�Ի���ͷ�ļ�
#include "MyExcel.h"          //���Excel��ͷ�ļ�

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//��������ȫ�ֱ���
int m_col = 14;                 //��
int m_row = 8;                  //��
int m_i112[14][8];              //��άָ��������112��������Ϣ,ֵΪ0����ʾ����ԤԼ��Ϊ1��ʾ***ԤԼ��Ϊ2��ʾ������ԤԼ
int m_i408[14][8];              //��άָ��������408��������Ϣ
int m_i409[14][8];              //��άָ��������409��������Ϣ

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

//���캯��
CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{ 
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMeetingRoomReservationSystemDlg �Ի���



//���캯��
CMeetingRoomReservationSystemDlg::CMeetingRoomReservationSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMeetingRoomReservationSystemDlg::IDD, pParent)
	, m_strAccount(_T(""))
	, m_strPassword(_T(""))
	//, m_strClass(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	for(int i=0;i<m_col;i++)//�ڹ��캯���г�ʼ�����ݳ�Ա
		for(int j=0;j<m_row;j++)
		{
			m_i112[i][j]=0;//��ʼ��Ϊ0��������ж�û�б�ԤԼ
			m_i408[i][j]=0;
			m_i409[i][j]=0;
		}
}

void CMeetingRoomReservationSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	//����MFCĬ�ϵ����ݽ���
	CDialogEx::DoDataExchange(pDX);
	//����ؼ�IDC_ACCOUNT�ͱ���m_strAccount֮������ݽ���
	DDX_Text(pDX, IDC_ACCOUNT, m_strAccount);
	//����ؼ�IDC_PASSWORD�ͱ���m_strPassword֮������ݽ���
	DDX_Text(pDX, IDC_PASSWORD, m_strPassword);
	//����ؼ�IDC_MEETINGROOM_TAB�ͱ���m_tabMeetingRoom֮������ݽ���
	DDX_Control(pDX, IDC_MEETINGROOM_TAB, m_tabMeetingRoom);
	//���������ؼ�IDC_MONTHCALENDAR�����m_montCtrl֮������ݽ���
	DDX_Control(pDX, IDC_MONTHCALENDAR, m_montCtrl);

}

BEGIN_MESSAGE_MAP(CMeetingRoomReservationSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_WM_MEASUREITEM_REFLECT()//���������б�߶���
	//ON_WM_MEASUREITEM()  //���������б�߶���
	//ON_WM_DRAWITEM()     //���������б�߶���
	ON_BN_CLICKED(ID_LOGIN, &CMeetingRoomReservationSystemDlg::OnBnClickedLogin)
	ON_BN_CLICKED(ID_ENTRY, &CMeetingRoomReservationSystemDlg::OnBnClickedEntry)
	ON_BN_CLICKED(IDC_RESERVE_BUTTON, &CMeetingRoomReservationSystemDlg::OnBnClickedReserveButton)
	ON_BN_CLICKED(IDC_INSTRUCT_BUTTON, &CMeetingRoomReservationSystemDlg::OnBnClickedInstructButton)
	ON_BN_CLICKED(IDC_QUIT_BUTTON, &CMeetingRoomReservationSystemDlg::OnBnClickedQuitButton)
	ON_NOTIFY(TCN_SELCHANGE, IDC_MEETINGROOM_TAB, &CMeetingRoomReservationSystemDlg::OnTcnSelchangeMeetingroomTab)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMeetingRoomReservationSystemDlg ��Ϣ�������
//CMeetingRoomReservationSystemDlg ��ʼ������
BOOL CMeetingRoomReservationSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//��ʼ����ʾ��¼����
	ShowEntry();

	//������ʱ��,��������ʱ����ţ����ʱ�䣨ms����
	SetTimer(1,1000,NULL);//������Ϊ1�����ʱ��1s

	//�򹤳������ļ�д��������ݿ�����ini�ļ���Ϣ��ini�ļ���̬�����7���ԤԼ���ݡ�Ĭ����������  
	CFileFind finder;   
	//�����Ƿ����ini�ļ�������0�������ڣ�������һ���µ�Ĭ�����õ�ini�ļ��������ͱ�֤�����Ǹ��ĺ������ÿ�ζ�����  
	BOOL ifFind = finder.FindFile(_T(".\\MeetingRoomInfo.ini"));
	if( !ifFind )  //���û�ҵ��ļ����������������������ݼ��ص��ļ��У�����ֵΪ0
	{  
		CTime m_CurTime = CTime::GetCurrentTime();  //��ŵ�ǰʱ������
		CTimeSpan m_TimeSpan = CTimeSpan(1,0,0,0);  //ʱ����1��
		CString strYear,strMonth,strDay;            //����꣬�£����ַ���
		CString strTemp_i;                          //���������ַ������ת�������//strTemp_j,����Ҫ�С��е������Ѿ����ˣ������ڴ�����
		CString strTemp;                            //����ַ�0
		for(int j=1; j<m_row;j++)
		{
			strYear = m_CurTime.Format("_%Y");      //����ת��Ϊ�ַ���
			strMonth = m_CurTime.Format("/%m");     //����ת��Ϊ�ַ���
			strDay = m_CurTime.Format("/%d");       //����ת��Ϊ�ַ���
			for(int i=0; i<m_col; i++)
			{            
				strTemp_i.Format(_T("_%d"),i);//��ת�����ַ���
				//strTemp_j.Format(_T("_%d"),j);//��ת�����ַ���
				strTemp.Format(_T("%d"),0);   //��0ת��Ϊ�ַ�
				//��һ����ʼ���ļ���ָ�����ֻ�ȡ�ַ����������ֱ�Ϊ���ֶ�������������û��ǰ��������ʱ��ֵ����������·���ļ���    .\\MeetingRoomInfo.ini��ʾ�ڳ���ǰ�ļ�����
				::WritePrivateProfileString(_T("MeetingRoomInfo112"),_T("i112") + strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
				::WritePrivateProfileString(_T("MeetingRoomInfo408"),_T("i408") + strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
				::WritePrivateProfileString(_T("MeetingRoomInfo409"),_T("i409") + strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
			}
			m_CurTime = m_CurTime + m_TimeSpan;//��ǰʱ����ϼ��ʱ������б�ڶ��� Ҳ���ǵڶ���
		}
	}
	else  //�ļ��������ļ��б���ֵ���ص�����������������
	{
		//�ٽ�ini��ǰһ��ļ�ֵɾ��,����ӵ������ֵΪ0
		//������ini�ļ��е�ֵ�ı��ˣ�������������m_i409[][]�е�ֵû����ini�е�ֵ��Ӧ������Ҫ���������е�ֵ
		CMeetingRoomReservationSystemDlg::DeleteIni();	
	}

	/*���ҵ�ǰĿ¼���Ƿ���MeetingRoomInfo.xls�ļ�
	ifFind = finder.FindFile(_T(".\\MeetingRoomInfo.xls"));
	//���û�о��ڵ�ǰ·���´���һ��
	//if(!ifFind) 
	//{
	//	//CFile file;
	//	//CFileException exp;
	//	//CString strFileName = _T(".\\MeetingRoomInfo.xls");
	//	////�����ļ�,����Ѿ������ļ���Ḳ��֮ǰ�����ݣ��ɹ��������ط�0
	//	//BOOL bCreateFile = file.Open(strFileName,CFile::modeCreate,&exp);
	//	//if(!bCreateFile)  
	//	//{  
	//	//	MessageBox(_T("����MeetingRoomInfo.xls�ļ�ʧ�ܣ�"));  
	//	//}

	//	//��һ���ļ�����Ի���  
	//	//string filePathStr(".\\MeetingRoomInfo.xls");  
	// //   string comment("");  
	//    CMyExcel Demon;  
	// //   //���û�·���������ļ�  
	// //   //�������״����Ϊ©��״̬  
	// //   theApp.BeginWaitCursor();         
	// //   if(!Demon.openfile(filePathStr,2))  
	// //   {  
	// //       MessageBox(_T("����Excel�ļ�ʧ�ܣ�"));  
	// //   }  
	//     //����������д��20�У�ÿ��1000��  
	//     //int iCount = 1;   
	//     //for(;iCount<=20;iCount++)  
	//     //{  
	//     //    char  valStr[10];  
	//     //    comment.clear();               //�����ַ���������Ԫ��
	//     //    sprintf_s(valStr,"%i",iCount); //д��ʽ�����ݵ��ַ���������������洢��Ԫ��
	//     //    comment += "��";  
	//     //    comment +=valStr;  
	//     //    comment +="��";        
	//     //    Demon.writeMatrix(comment,mateDataReal,1,1000);  
	//     //}


	//	
	//	COleVariant��ΪVARIANT�������͵İ�װ�����Զ��������У�ͨ����ʹ�� 
	//	VARIANT�������ͽ��в������ݡ������г����У�������������ͨ��COleVariant 
	//	����ת���˵ġ� 
	//	  
	//	//covOptional ��ѡ������VARIANT����  
	//	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);  
	//	if( !Demon.m_app.CreateDispatch(_T("Excel.Application")) )
	//	{  
	//		this->MessageBox(_T("�޷�����ExcelӦ�ã�"));  
	//		return FALSE;  
	//	}


	//}*/
	 

	//��ʼ����ǩ�ؼ�
	CRect tabRect;//��ǩ�ؼ��ͻ�����λ�úʹ�С
	m_tabMeetingRoom.InsertItem(0,_T("112"));//�����һ����ǩ��112��
	m_tabMeetingRoom.InsertItem(1,_T("408"));//����ڶ�����ǩ��408��
	m_tabMeetingRoom.InsertItem(2,_T("409"));//�����������ǩ��409��
	m_MeetingRoom112.Create(IDD_MEETINGROOM112_DIALOG, &m_tabMeetingRoom);//������һ����ǩ��˳�����������ǩ���ֵ�˳��һ�¡�
	m_MeetingRoom408.Create(IDD_MEETINGROOM408_DIALOG, &m_tabMeetingRoom);//�����ڶ�����ǩ
	m_MeetingRoom409.Create(IDD_MEETINGROOM409_DIALOG, &m_tabMeetingRoom);//������������ǩ

	m_tabMeetingRoom.GetClientRect(&tabRect);//��ȡ��ǩ�ؼ��ͻ��� Rect//���� tabRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;
	//���ݵ����õ�tabRect�������������ҶԻ���,���õ�˳�����������ǩ���ֵ�˳��һ�¡�
	m_MeetingRoom112.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_SHOWWINDOW);
	m_MeetingRoom408.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_HIDEWINDOW);
	m_MeetingRoom409.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_HIDEWINDOW);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMeetingRoomReservationSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMeetingRoomReservationSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//������ע�ᡱ��ť��Ϣ������
void CMeetingRoomReservationSystemDlg::OnBnClickedLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}

//��������¼����ť��Ϣ������
void CMeetingRoomReservationSystemDlg::OnBnClickedEntry()
{
	INT_PTR nRes;                              //���ڱ���DoModal�����ķ���ֵ

	CAccountNotExist accountnotexist;          //����Ի�����CAccountNotExist��ʵ��
	CErrorPassword   errorpassword;            //����Ի�����CErrorPassword��ʵ��
	// �����ؼ��е����ݱ��浽��Ӧ�ı���
	UpdateData(TRUE);

	if(m_strAccount == "***")
	{
		if(m_strPassword == "123456")
		{
			m_strPassword = "Entry successful!";//�˺�����һ����ʾ��¼�ɹ�
			HideEntry();                        //���ص�¼����
		}
		else
		{
			nRes = errorpassword.DoModal();     //�˺�һ�����벻һ�£������������Ի���
			
		}
	}
	else if(m_strAccount == "???")
	{
		if(m_strPassword == "12345")
		{
			m_strPassword = "Entry successful!";//�˺�����һ����ʾ��¼�ɹ�
			HideEntry();                        //���ص�¼����
		}
		else
		{
			nRes = errorpassword.DoModal();     //�˺�һ�����벻һ�£������������Ի���	
		}
	}
	else
	{
		nRes = accountnotexist.DoModal();     //�˺Ų�һ�£������˺Ų����ڶԻ���
	}
	//�����޸ĵĸ��ؼ���ֵ����ʾ����
	UpdateData(FALSE);
}

//�������˳���¼����ť��Ϣ������
void CMeetingRoomReservationSystemDlg::OnBnClickedQuitButton()
{
	m_strAccount = "";    //�˺����
	m_strPassword = "";   //�������
	SetDlgItemText(IDC_ACCOUNT,m_strAccount);   //��ձ༭����ʾ
	SetDlgItemText(IDC_PASSWORD,m_strPassword); //��ձ༭����ʾ
	ShowEntry();          //��ʾ��¼����
}

//������ԤԼ����ť��Ϣ������
void CMeetingRoomReservationSystemDlg::OnBnClickedReserveButton()
{
	INT_PTR nRes;                              //���ڱ���DoModal������MessageBox�����ķ���ֵ
	CReserveDlg reserveDlg;                    //����Ի���CReserveDlg��ʵ��

	// �����ؼ��е����ݱ��浽��Ӧ�ı���
	if(m_strPassword == "Entry successful!")   //���ѳɹ���¼������ԤԼ�Ի���
	{
		nRes = reserveDlg.DoModal();           //������ԤԼ���Ի���

		//����ԤԼ����ȡ��ԤԼ�����Ȼ�ȡԤԼ�Ի�����ѡ��Ľ��ҡ�ʱ�䡢������Ϣ��
		//�Լ���ǰʱ�����ڡ�
		int i = reserveDlg.m_iTime;           //��ȡ�б��޸ı�������
		int j;                                //��ȡ�б��޸ı�������
		CTime m_CurTime = CTime::GetCurrentTime();      //��ȡϵͳʱ��
		CTimeSpan m_TimeSpan = CTimeSpan(1,0,0,0);      //ʱ����1��
		CString strYear,strMonth,strDay;                //����꣬�£����ַ���
		/*forѭ�������ж�ԤԼ�Ի���ѡ�������ڣ�ѡ�������ڸ��б��ϵ����ڱȽϣ����ǵڼ���
		  ��Ϊ�б�һ����ʾ�������Ϣ�������б��0����д��ʱ�䣬���Դ�1����п�ʼ��
		  ����������ڱȽ�����Ϊ�б�����1����ʾ���ǵ��������*/
		for(int i = 1;i < m_row; i++)
		{
			if(m_CurTime.Format("%Y/%m/%d") == reserveDlg.m_dateTime.Format("%Y/%m/%d"))//ѡ�������ڸ��б��ϵ����ڱȽϣ����ǵڼ���
			{
				j = i;                                  //�б������Ÿ�ֵ
				strYear = m_CurTime.Format("_%Y");      //����ת��Ϊ�ַ���
				strMonth = m_CurTime.Format("/%m");     //����ת��Ϊ�ַ���
				strDay = m_CurTime.Format("/%d");       //����ת��Ϊ�ַ���
				break;                                  //һ���ҵ�����ž��˳�forѭ��
			}	
			m_CurTime = m_CurTime + m_TimeSpan;//û�ҵ��ͼ�1�죬����Ѱ��
		}
		CString strTemp_i;            //���������ַ������ת���������//strTemp_j,����Ҫ�С��е������Ѿ����ˣ������ڴ�����
		CString strTemp;              //�����м�����������ֵת������ַ���
		strTemp_i.Format(_T("_%d"),i);//��ת�����ַ���
		if(IDC_RESERVECANCLE_BUTTON == nRes)   //����ȡ��ԤԼ
		{
			//ȡ��ԤԼ��CMeetingRoomReservationSystemDlg�Ի����Ҳ�����ݸ��£���Ӧȡ���ı��Ϊ��
			switch(reserveDlg.m_iMeetingRoom)  //�ж�ѡ��Ļ�����������
			{
				//�ж�Ҫȡ���ı����Ϣ�Ƿ����½����Ϣһ�£�һ�²���ȡ��ԤԼ�����򵯳�����
				case 0: if(m_strAccount == m_MeetingRoom112.m_MeetingRoom112InfoList.GetItemText(i,j))
						{
							m_i112[i][j] = 0;
							strTemp.Format(_T("%d"),m_i112[i][j]);//�����к�ת��Ϊ�ַ���
							//���ı��ֵ������.ini�ļ��У��´ο�����ʼ��ʱʹ��
							::WritePrivateProfileString(_T("MeetingRoomInfo112"),_T("i112") + strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
						}	
					break;//������0��ʾ������112
				case 1: if(m_strAccount == m_MeetingRoom408.m_MeetingRoom408InfoList.GetItemText(i,j))
						{
							m_i408[i][j] = 0;
							strTemp.Format(_T("%d"),m_i408[i][j]);//�����к�ת��Ϊ�ַ���
							//���ı��ֵ������.ini�ļ��У��´ο�����ʼ��ʱʹ��
							::WritePrivateProfileString(_T("MeetingRoomInfo408"),_T("i408")+ strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
						}
					break;//������1��ʾ������408
				case 2: if(m_strAccount == m_MeetingRoom409.m_MeetingRoom409InfoList.GetItemText(i,j))
						{
							m_i409[i][j] = 0;
							strTemp.Format(_T("%d"),m_i409[i][j]);//�����к�ת��Ϊ�ַ���
							//���ı��ֵ������.ini�ļ��У��´ο�����ʼ��ʱʹ��
							::WritePrivateProfileString(_T("MeetingRoomInfo409"),_T("i409")+ strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
						}
					break;//������2��ʾ������409
				default: //��ʾ��ʾ�Ի���ֻ��OK��ť������ʾͼ��
						nRes = MessageBox(_T("��û�в���Ȩ�ޣ��޷�ȡ�������û�ԤԼ��"), NULL, MB_OK | MB_ICONWARNING);
						break;
			}
			m_MeetingRoom112.UpdateMeetingRoom112();//ˢ��112�б���Ϣ
			m_MeetingRoom408.UpdateMeetingRoom408();//ˢ��408�б���Ϣ
			m_MeetingRoom409.UpdateMeetingRoom409();//ˢ��409�б���Ϣ
		}				
		else if(IDOK == nRes)                  //����ȷ��ԤԼ�������б���Ϣ
		{
			//ȷ��ԤԼ��CMeetingRoomReservationSystemDlg�Ի����Ҳ�����ݸ���
			if( (m_strAccount == "***"))// �жϵ�ǰ��¼���˻���Ϣ
			{	                    
				//����¼��Ϊ***���ж�ѡ��Ļ����ң���Ϊ����֮ǰ��Ͽ���ѡ�еĶ�Ӧ���б��ֵ1
				switch(reserveDlg.m_iMeetingRoom)  //�ж�ѡ��Ļ�����������
				{
					case 0: 
						if(m_MeetingRoom112.m_MeetingRoom112InfoList.GetItemText(i,j) == _T(" "))
						{
							m_i112[i][j] = 1;                     //������0��ʾ������112
							strTemp.Format(_T("%d"),m_i112[i][j]);//�����к�ת��Ϊ�ַ���
							//���ı��ֵ������.ini�ļ��У��´ο�����ʼ��ʱʹ��
							::WritePrivateProfileString(_T("MeetingRoomInfo112"),_T("i112")+ strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
						}
						break;
					case 1: 
						if(m_MeetingRoom408.m_MeetingRoom408InfoList.GetItemText(i,j) == _T(" "))
						{
							m_i408[i][j] = 1;                     //������1��ʾ������408
							strTemp.Format(_T("%d"),m_i408[i][j]);//�����к�ת��Ϊ�ַ���
							//���ı��ֵ������.ini�ļ��У��´ο�����ʼ��ʱʹ��
							::WritePrivateProfileString(_T("MeetingRoomInfo408"),_T("i408")+ strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
						}
						break;
					case 2: 
						if(m_MeetingRoom409.m_MeetingRoom409InfoList.GetItemText(i,j) == _T(" "))
						{
							m_i409[i][j] = 1;                     //������0��ʾ������409
							strTemp.Format(_T("%d"),m_i409[i][j]);//�����к�ת��Ϊ�ַ���
							//���ı��ֵ������.ini�ļ��У��´ο�����ʼ��ʱʹ��
							::WritePrivateProfileString(_T("MeetingRoomInfo409"),_T("i409")+ strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
						}
						break;
					default:
						MessageBox(_T("��ʱ����ѱ�ԤԼ��"), NULL, MB_OK | MB_ICONWARNING);//���ѱ�ԤԼ������ʾ��Ϣ
						break;
				}	
			}
			if( (m_strAccount == "???"))
			{
				//����¼��Ϊ???���ж�ѡ��Ļ����ң���Ϊ����֮ǰ��Ͽ���ѡ�еĶ�Ӧ���б��ֵ2
				switch(reserveDlg.m_iMeetingRoom)  //�ж�ѡ��Ļ�����������
				{
					case 0: 
						if(m_MeetingRoom112.m_MeetingRoom112InfoList.GetItemText(i,j) == _T(" "))
						{
							m_i112[i][j] = 2;                     //������0��ʾ������112
							strTemp.Format(_T("%d"),m_i112[i][j]);//�����к�ת��Ϊ�ַ���
							//���ı��ֵ������.ini�ļ��У��´ο�����ʼ��ʱʹ��
							::WritePrivateProfileString(_T("MeetingRoomInfo112"),_T("i112")+ strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
						}
						break;
					case 1: 
						if(m_MeetingRoom408.m_MeetingRoom408InfoList.GetItemText(i,j) == _T(" "))
						{
							m_i408[i][j] = 2;                     //������1��ʾ������408
							strTemp.Format(_T("%d"),m_i408[i][j]);//�����к�ת��Ϊ�ַ���
							//���ı��ֵ������.ini�ļ��У��´ο�����ʼ��ʱʹ��
							::WritePrivateProfileString(_T("MeetingRoomInfo408"),_T("i408")+ strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
						}
						break;
					case 2: 
						if(m_MeetingRoom409.m_MeetingRoom409InfoList.GetItemText(i,j) == _T(" "))
						{
							m_i409[i][j] = 2;                     //������0��ʾ������409
							strTemp.Format(_T("%d"),m_i409[i][j]);//�����к�ת��Ϊ�ַ���
							//���ı��ֵ������.ini�ļ��У��´ο�����ʼ��ʱʹ��
							::WritePrivateProfileString(_T("MeetingRoomInfo409"),_T("i409")+ strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
						}
						break;
					default:
						MessageBox(_T("��ʱ����ѱ�ԤԼ��"), NULL, MB_OK | MB_ICONWARNING);//���ѱ�ԤԼ������ʾ��Ϣ
						break;
				}
			}
			//�˴�����ӵ�¼�˻���Ϣ

			//�����ȷ��ԤԼ��ť�󣬸����б���Ϣ
			m_MeetingRoom112.UpdateMeetingRoom112();//ˢ��112�б���Ϣ
			m_MeetingRoom408.UpdateMeetingRoom408();//ˢ��408�б���Ϣ
			m_MeetingRoom409.UpdateMeetingRoom409();//ˢ��409�б���Ϣ
		}
		else
		{
			return;
		}
	} 
	else   //��δ�ɹ���¼��������Ϣ�Ի�����ʾ���ȵ�¼��
	{
		//��ʾ��Ϣ�Ի���ֻ��OK��ť������ʾͼ��
		nRes = MessageBox(_T("���ȵ�¼��"), NULL, MB_OK | MB_ICONWARNING);	
	} 
}

//������ʹ��˵������ťʱ��Ϣ������
void CMeetingRoomReservationSystemDlg::OnBnClickedInstructButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�������Ա����
	CUsingSheet sheet(_T(""));

	//�������ԶԻ���Ϊ�򵼶Ի���
	sheet.SetWizardMode();

	//��ģ̬�򵼶Ի���
	sheet.DoModal();
}

//���ص�¼����
void CMeetingRoomReservationSystemDlg::HideEntry()
{
	GetDlgItem(IDC_QUIT_BUTTON)->ShowWindow(SW_SHOW);     //��ʾ���˳���¼����ť
	GetDlgItem(IDC_ENTRYSUCCESS_TIP_STATIC)->ShowWindow(SW_SHOW);//��ʾ��¼�ɹ���ʾ
	GetDlgItem(IDC_PASSWORD_STATIC)->ShowWindow(SW_HIDE); //�����������Ϣ
	GetDlgItem(IDC_ACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PASSWORD)->ShowWindow(SW_HIDE);
	GetDlgItem(ID_LOGIN)->ShowWindow(SW_HIDE);
    GetDlgItem(ID_ENTRY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ACCOUNT_STATIC)->ShowWindow(SW_HIDE);
}

//��ʾ��¼����
void CMeetingRoomReservationSystemDlg::ShowEntry()
{
	GetDlgItem(IDC_QUIT_BUTTON)->ShowWindow(SW_HIDE);    //���ء��˳���¼����ť
	GetDlgItem(IDC_ENTRYSUCCESS_TIP_STATIC)->ShowWindow(SW_HIDE);//���ص�¼�ɹ���ʾ
	GetDlgItem(IDC_PASSWORD_STATIC)->ShowWindow(SW_SHOW);//��ʾ�������Ϣ
	GetDlgItem(IDC_ACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_PASSWORD)->ShowWindow(SW_SHOW);
	GetDlgItem(ID_LOGIN)->ShowWindow(SW_SHOW);
    GetDlgItem(ID_ENTRY)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ACCOUNT_STATIC)->ShowWindow(SW_SHOW);
}

//Tab�л�ҳ����Ϣ������
void CMeetingRoomReservationSystemDlg::OnTcnSelchangeMeetingroomTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CRect tabRect;               //��ǩ�ؼ��ͻ�����Rect

	//��ȡ��ǩ�ؼ��ͻ��� Rect������ tabRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ
	m_tabMeetingRoom.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;

	switch(m_tabMeetingRoom.GetCurSel())//��ȡ��ǰ��ǩ�������ţ�һ����ǩ��Ӧһ�������ţ��ο���ʼ������
	{
		//�����ǩ��ǰѡ��Ϊ��112������112��Ӧ��������0��������ʾm_MeetingRoom112�Ի������������Ի���
		case 0:
			m_MeetingRoom112.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_SHOWWINDOW);
			m_MeetingRoom408.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_HIDEWINDOW);
			m_MeetingRoom409.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_HIDEWINDOW);
			break;
		//�����ǩ��ǰѡ��Ϊ��408������408��Ӧ��������1��������ʾm_MeetingRoom408�Ի������������Ի���
		case 1:
			m_MeetingRoom112.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_HIDEWINDOW);
			m_MeetingRoom408.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_SHOWWINDOW);
			m_MeetingRoom409.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_HIDEWINDOW);
			break;
		//�����ǩ��ǰѡ��Ϊ��409������409��Ӧ��������2��������ʾm_MeetingRoom409�Ի������������Ի���
		case 2:
			m_MeetingRoom112.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_HIDEWINDOW);
			m_MeetingRoom408.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_HIDEWINDOW);
			m_MeetingRoom409.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(),SWP_SHOWWINDOW);
			break;
		default:
			break;
	}
}

//��ʱ����Ϣ��������1sִ��һ�δ˺���
void CMeetingRoomReservationSystemDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CTime m_CurTime = CTime::GetCurrentTime();  //��ȡϵͳʱ��
	CString str = m_CurTime.Format("%H:%M:%S"); //��ϵͳʱ�䱣�����ַ����У�ʱ���֣���
	switch(nIDEvent)
	{
	case 1:SetDlgItemText(IDC_TIME_EDIT,str);  break;//��ʾϵͳʱ��
	default:break;
	}
	/*���ʱ�̽��м���������
	�ٽ�ini��ǰһ��ļ�ֵɾ��,����ӵ������ֵΪ0
	������ini�ļ��е�ֵ�ı��ˣ�������������m_i409[][]�е�ֵû����ini�е�ֵ��Ӧ������Ҫ���������е�ֵ
	���б����³�ʼ������ʾ���º��ֵ
	*/
	if((m_CurTime.GetHour() == 0) && (m_CurTime.GetMinute() == 0) && (m_CurTime.GetSecond() == 0))
	{	
		CMeetingRoomReservationSystemDlg::DeleteIni();
		//�б����³�ʼ��
		m_MeetingRoom409.OnInitDialog();
		m_MeetingRoom408.OnInitDialog();
		m_MeetingRoom112.OnInitDialog();
	}
	//CDialogEx::OnTimer(nIDEvent);
}


//�ٽ�ini��ǰһ��ļ�ֵɾ��,����ӵ������ֵΪ0
//������ini�ļ��е�ֵ�ı��ˣ�������������m_i409[][]�е�ֵû����ini�е�ֵ��Ӧ������Ҫ���������е�ֵ
void CMeetingRoomReservationSystemDlg::DeleteIni()
{
	CTime m_CurTime = CTime::GetCurrentTime();  //��ȡϵͳʱ��
	CTimeSpan m_TimeSpan = CTimeSpan(1,0,0,0);  //ʱ����1��
	CTime m_ProTime = m_CurTime - m_TimeSpan;   //���֮ǰ1�������
	m_TimeSpan = CTimeSpan(6,0,0,0);            //���¸�ֵ��ʱ����7��
	m_CurTime = m_CurTime + m_TimeSpan;         //���֮�����������
	CString strYear,strMonth,strDay;            //����꣬�£����ַ���
	CString strProYear,strProMonth,strProDay;   //���֮ǰ�꣬�£����ַ���
	CString strTemp_i;                          //���������ַ������ת���������//strTemp_j,����Ҫ�С��е������Ѿ����ˣ������ڴ�����
	CString strTemp;                            //����ַ�0
	
	strYear = m_CurTime.Format("_%Y");       //����ת��Ϊ�ַ���
	strMonth = m_CurTime.Format("/%m");      //����ת��Ϊ�ַ���
	strDay = m_CurTime.Format("/%d");        //����ת��Ϊ�ַ���
	strProYear = m_ProTime.Format("_%Y");       //����ת��Ϊ�ַ���
	strProMonth = m_ProTime.Format("/%m");      //����ת��Ϊ�ַ���
	strProDay = m_ProTime.Format("/%d");        //����ת��Ϊ�ַ���
	strTemp.Format(_T("%d"),0);                 //��0ת��Ϊ�ַ�
	/*���ʱ�̽�ini��ǰһ��ļ�ֵɾ��,����ӵ������ֵΪ0*/
	for(int i = 0;i<m_col;i++)
	{
		strTemp_i.Format(_T("_%d"),i);          //��ת�����ַ���
		::WritePrivateProfileString(_T("MeetingRoomInfo112"),_T("i112") + strProYear + strProMonth + strProDay + strTemp_i,NULL,_T(".\\MeetingRoomInfo.ini"));
		::WritePrivateProfileString(_T("MeetingRoomInfo408"),_T("i408") + strProYear + strProMonth + strProDay + strTemp_i,NULL,_T(".\\MeetingRoomInfo.ini"));
		::WritePrivateProfileString(_T("MeetingRoomInfo409"),_T("i409") + strProYear + strProMonth + strProDay + strTemp_i,NULL,_T(".\\MeetingRoomInfo.ini"));
	
		::WritePrivateProfileString(_T("MeetingRoomInfo112"),_T("i112") + strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
		::WritePrivateProfileString(_T("MeetingRoomInfo408"),_T("i408") + strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
		::WritePrivateProfileString(_T("MeetingRoomInfo409"),_T("i409") + strYear + strMonth + strDay + strTemp_i,strTemp,_T(".\\MeetingRoomInfo.ini"));
	}
	//����ini�ļ��е�ֵ�ı��ˣ�������������m_i409[][]�е�ֵû����ini�е�ֵ��Ӧ������Ҫ���������е�ֵ��
	m_CurTime = CTime::GetCurrentTime();      //��ŵ�ǰʱ������
	m_TimeSpan = CTimeSpan(1,0,0,0);          //ʱ����1��
	for(int j=1; j<m_row; j++)
	{
		strYear = m_CurTime.Format("_%Y");    //����ת��Ϊ�ַ���
		strMonth = m_CurTime.Format("/%m");   //����ת��Ϊ�ַ���
		strDay = m_CurTime.Format("/%d");     //����ת��Ϊ�ַ���
		for(int i=0; i<m_col;i++)
		{
			strTemp_i.Format(_T("_%d"),i);    //��ת�����ַ���
			//��һ����ʼ���ļ���ָ�����ֻ�ȡ�ַ����������ֱ�Ϊ���ֶ�������������û��ǰ��������ʱ��ֵ����������·���ļ���.  .\\MeetingRoomInfo.ini��ʾ�ڳ���ǰ�ļ�����    
			//�����������ڣ���Ĭ����ini�ļ����ȴ����α���������ֵ0
			m_i112[i][j] = GetPrivateProfileInt(_T("MeetingRoomInfo112"),_T("i112")+strYear+strMonth+strDay+strTemp_i,0,_T(".\\MeetingRoomInfo.ini"));
			m_i408[i][j] = GetPrivateProfileInt(_T("MeetingRoomInfo408"),_T("i408")+strYear+strMonth+strDay+strTemp_i,0,_T(".\\MeetingRoomInfo.ini"));
			m_i409[i][j] = GetPrivateProfileInt(_T("MeetingRoomInfo409"),_T("i409")+strYear+strMonth+strDay+strTemp_i,0,_T(".\\MeetingRoomInfo.ini"));	
		}
		m_CurTime = m_CurTime + m_TimeSpan;//��ǰʱ����ϼ��ʱ������б�ڶ��� Ҳ���ǵڶ���
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
//    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ  
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
//  //������ʾ    
//  BOOL bHighlight =((lvi.state & LVIS_DROPHILITED)||((lvi.state & LVIS_SELECTED)   
//  && ((GetFocus() == this)|| (GetStyle() & LVS_SHOWSELALWAYS))));  
//    
//  //���ı�����   
//  CRect rcBack = lpDrawItemStruct->rcItem;   
//  pDC->SetBkMode(TRANSPARENT);   
//    
//  if( bHighlight ) //�����ѡ��  
//  {   
//    pDC->SetTextColor(RGB(255,255,255));              //�ı���ɫ  
//    pDC->FillRect(rcBack, &CBrush(RGB(90,162,100)));  //�б���ɫ  
//  }   
//  else   
//  {   
//    pDC->SetTextColor(RGB(0,0,0));                    //�ı���ɫ  
//    pDC->FillRect(rcBack, &CBrush(RGB(255,255,255))); //�б���ɫ  
//  }   
//    
//  //�����ı�  
//  if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)   
//  {   
//    //�õ�����  
//    int nCollumn = GetHeaderCtrl()->GetItemCount();  
//      
//    //ѭ������  
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







