// MeetingRoom409.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Meeting Room Reservation System.h"
#include "MeetingRoom409Dlg.h"
#include "afxdialogex.h"

//����������ȫ�ֱ������ⲿ����
extern int m_col;
extern int m_row;
extern int m_i112[14][8];              //��άָ��������112��������Ϣ,ֵΪ0����ʾ����ԤԼ��Ϊ1��ʾ***ԤԼ��Ϊ2��ʾ������ԤԼ
extern int m_i408[14][8];              //��άָ��������408��������Ϣ
extern int m_i409[14][8];              //��άָ��������409��������Ϣ
// CMeetingRoom409Dlg �Ի���

IMPLEMENT_DYNAMIC(CMeetingRoom409Dlg, CDialogEx)

CMeetingRoom409Dlg::CMeetingRoom409Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMeetingRoom409Dlg::IDD, pParent)
{

}

CMeetingRoom409Dlg::~CMeetingRoom409Dlg()
{
}

void CMeetingRoom409Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//����ؼ�IDC_MEETINGROOM409INFO_LIST�ͱ���m_MeetingRoom409InfoList֮������ݽ���
	DDX_Control(pDX, IDC_MEETINGROOM409INFO_LIST, m_MeetingRoom409InfoList);
}


BEGIN_MESSAGE_MAP(CMeetingRoom409Dlg, CDialogEx)
END_MESSAGE_MAP()


// CMeetingRoom409 ��Ϣ�������


BOOL CMeetingRoom409Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CTime m_CurTime = CTime::GetCurrentTime(); //��ȡϵͳʱ��
	CTimeSpan m_TimeSpan = CTimeSpan(1,0,0,0); //ʱ����1��
	CString strYear,strMonth,strDay;           //����꣬�£����ַ���
	CString m_strDayofWeek;                    //������һ �ܶ�...

	CRect rect;   //ʵ�����б����
	//��ȡ�б���ͼ�ؼ���λ�úʹ�С
	m_MeetingRoom409InfoList.GetClientRect(&rect);
	//Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����
	m_MeetingRoom409InfoList.SetExtendedStyle(m_MeetingRoom409InfoList.GetExtendedStyle() | LVS_EX_FULLROWSELECT  | LVS_EX_GRIDLINES);//
	//��һ��Ϊ��ʱ�䡱�������ֱ�Ϊ�����������б��⣬�����ı����뷽ʽ���п������ж�Ӧ�б����������
	m_MeetingRoom409InfoList.InsertColumn(0, _T("ʱ��"), LVCFMT_CENTER, 80, 0);
	for(int i = 1;i<m_row;i++)//ѭ��7�θ��б�ÿһ�е�ͷ��ֵ
	{
		strYear = m_CurTime.Format("%Y");  //����ת��Ϊ�ַ���
		strMonth = m_CurTime.Format("%m"); //����ת��Ϊ�ַ���
		strDay = m_CurTime.Format("%d");   //����ת��Ϊ�ַ���
		switch(m_CurTime.GetDayOfWeek())
		{
			case 1:m_strDayofWeek = _T("����")+ strMonth + _T("��") + strDay + _T("��");break;
			case 2:m_strDayofWeek = _T("��һ")+ strMonth + _T("��") + strDay + _T("��");break;
			case 3:m_strDayofWeek = _T("�ܶ�")+ strMonth + _T("��") + strDay + _T("��");break;
			case 4:m_strDayofWeek = _T("����")+ strMonth + _T("��") + strDay + _T("��");break;
			case 5:m_strDayofWeek = _T("����")+ strMonth + _T("��") + strDay + _T("��");break;
			case 6:m_strDayofWeek = _T("����")+ strMonth + _T("��") + strDay + _T("��");break;
			case 7:m_strDayofWeek = _T("����")+ strMonth + _T("��") + strDay + _T("��");break;
			default:break;
		}
		m_CurTime = m_CurTime + m_TimeSpan;//��ǰʱ����ϼ��ʱ������б�ڶ��� Ҳ���ǵڶ���
		m_MeetingRoom409InfoList.InsertColumn(i, m_strDayofWeek, LVCFMT_CENTER, 90, i);
	}
	//���б���ͼ�ؼ��в����б�����У��������б������ı�
	//�е����кŲ��������
	CString str;//���ÿ�е�һ������
	for(int i = 0;i < m_col;i++)
	{
		str.Format(_T("%d:00-%d:00"),i+8,i+9);      //ÿ�е�һ������8:00-9:00,9:00-10:00...
		m_MeetingRoom409InfoList.InsertItem(i, str);//��i�е�1��
	}

	UpdateMeetingRoom409();//ˢ���б���Ϣ
	return TRUE;           // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

//ˢ���б���Ϣ����
void CMeetingRoom409Dlg::UpdateMeetingRoom409()
{
	CString str;                   //����һ���ַ�����ű���е��ַ�����Ϣ
	for(int i=0; i<m_col;i++)
	{
		for(int j=1; j<m_row; j++)
		{
			//���ÿ�������ֵ�Ǽ���Ϊ0��ʾ����ԤԼ��Ϊ1��ʾ***ԤԼ��Ϊ2��ʾ������ԤԼ
			switch(m_i409[i][j])//meetingRoomReservationSystem.m_i112[i][j]
			{
				case 0:str = _T(" ");break;//��ֵΪ0ʱ���������ʾ�ո�
				case 1:str = _T("***");break;//��ֵΪ1ʱ���������ʾ***����ʾ��***ԤԼ
				case 2:str = _T("???");break;//��ֵΪ2ʱ���������ʾ����������ʾ��������ԤԼ
					//�˴��������Ϣ��ֵΪ3��4��5��6.������
				default:break;
			}					
			m_MeetingRoom409InfoList.SetItemText(i, j, str);//ѭ����ÿһ�����ֵ,��i�е�j��
		}
	}
}
