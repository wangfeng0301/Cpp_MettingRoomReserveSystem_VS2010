// ReserveDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Meeting Room Reservation System.h"
#include "Meeting Room Reservation SystemDlg.h"//���������ͷ�ļ�
#include "ReserveDlg.h"
#include "afxdialogex.h"


// CReserveDlg �Ի���

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
	//����ؼ�IDC_TIME_COMBO�ͱ���m_comboTIME֮������ݽ���
	DDX_Control(pDX, IDC_TIME_COMBO, m_comboTIME);
	//����ؼ�IDC_TIME_COMBO�ͱ���m_comboTIME֮������ݽ���
	DDX_Control(pDX, IDC_MEETINGROOM_COMBO, m_comboMeetingRoom);
	//����ؼ�IDC_DATETIMEPICKER�ͱ���m_comboWEEK֮������ݽ���
	DDX_Control(pDX, IDC_DATETIMEPICKER, m_dateCtrl);
}

//CReserveDlg ��ʼ������
BOOL CReserveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//����Date Time Picker�ؼ�����ѡ�������ʱ�䷶Χ
	CTime m_startTime = CTime::GetCurrentTime();
	CTimeSpan m_timeSpan(7, 0, 0, 0); // 70 days, 0 hour, 0 min, o second.
	CTime m_endTime = m_startTime + m_timeSpan;
	m_dateCtrl.SetRange(&m_startTime, &m_endTime);

	m_comboTIME.InsertString(0,_T("8:00-9:00"));//Ϊ��ʱ�䡱��Ͽ�ؼ����б������б���8:00-9:00
	m_comboTIME.InsertString(1,_T("9:00-10:00"));//Ϊ��ʱ�䡱��Ͽ�ؼ����б������б���
	m_comboTIME.InsertString(2,_T("10:00-11:00"));//Ϊ��ʱ�䡱��Ͽ�ؼ����б������б���
	m_comboTIME.InsertString(3,_T("11:00-12:00"));//Ϊ��ʱ�䡱��Ͽ�ؼ����б������б���
	m_comboTIME.InsertString(4,_T("12:00-13:00"));//Ϊ��ʱ�䡱��Ͽ�ؼ����б������б���
	m_comboTIME.InsertString(5,_T("13:00-14:00"));//Ϊ��ʱ�䡱��Ͽ�ؼ����б������б���
	m_comboTIME.InsertString(6,_T("14:00-15:00"));//Ϊ��ʱ�䡱��Ͽ�ؼ����б������б���
	m_comboTIME.InsertString(7,_T("15:00-16:00"));//Ϊ��ʱ�䡱��Ͽ�ؼ����б������б���
	m_comboTIME.InsertString(8,_T("16:00-17:00"));//Ϊ��ʱ�䡱��Ͽ�ؼ����б������б���
	m_comboTIME.InsertString(9,_T("17:00-18:00"));//Ϊ��ʱ�䡱��Ͽ�ؼ����б������б���
	m_comboTIME.InsertString(10,_T("18:00-19:00"));//Ϊ��ʱ�䡱��Ͽ�ؼ����б������б���
	m_comboTIME.InsertString(11,_T("19:00-20:00"));//Ϊ��ʱ�䡱��Ͽ�ؼ����б������б���
	m_comboTIME.InsertString(12,_T("20:00-21:00"));//Ϊ��ʱ�䡱��Ͽ�ؼ����б������б���
	m_comboTIME.InsertString(13,_T("21:00-22:00"));//Ϊ��ʱ�䡱��Ͽ�ؼ����б������б���
	m_comboTIME.SelectString(0,_T("8:00-9:00"));//ѡ���б��ѡ���������ΪĬ����ʾ

	
	m_comboMeetingRoom.InsertString(0,_T("112"));//Ϊ��Ͽ�ؼ����б������б���112
	m_comboMeetingRoom.InsertString(1,_T("408"));//Ϊ��Ͽ�ؼ����б������б���409
	m_comboMeetingRoom.InsertString(2,_T("409"));//Ϊ��Ͽ�ؼ����б������б���408,����ָ��λ�ã�0�ǵ�һ����1�ǵڶ���...
	m_comboMeetingRoom.SelectString(1,_T("408"));//ѡ���б��ѡ���������ΪĬ����ʾ

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

BEGIN_MESSAGE_MAP(CReserveDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CReserveDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RESERVECANCLE_BUTTON, &CReserveDlg::OnBnClickedReservecancleButton)
	ON_BN_CLICKED(IDOK, &CReserveDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CReserveDlg ��Ϣ�������

//������ȡ������ťʱ��Ϣ������
void CReserveDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();//ֱ���˳�
}


//������ȡ��ԤԼ����ťʱ��Ϣ������
void CReserveDlg::OnBnClickedReservecancleButton()
{
	UpdateData(FALSE);
	//����m_comboTIME.GetCurSel()�ɻ�ȡ��Ͽ�ǰѡ�е������ţ���������Ϣ
	m_iTime = m_comboTIME.GetCurSel();              //��������
	m_dateCtrl.GetTime(m_dateTime);                 //��ȡDate Time Picker�ؼ���ѡ�е�����
	m_iMeetingRoom = m_comboMeetingRoom.GetCurSel();//������������
	UpdateData(FALSE);
	EndDialog(IDC_RESERVECANCLE_BUTTON);            //�ر�ԤԼ���ڲ�����ֵIDC_RESERVECANCLE_BUTTON
}

//������ԤԼ��ʱ��Ϣ������
//ʵ�ֽ�֮ǰ����Ͽ���ѡ�е���Ϣ������Ӧ�ı�񣬶�Ӧ�����������ֵ��ֵ
void CReserveDlg::OnBnClickedOk()
{	
	//����m_comboTIME.GetCurSel()�ɻ�ȡ��Ͽ�ǰѡ�е������ţ���������Ϣ
	m_iTime = m_comboTIME.GetCurSel();              //��������
	m_dateCtrl.GetTime(m_dateTime);                 //��ȡDate Time Picker�ؼ���ѡ�е�����
	m_iMeetingRoom = m_comboMeetingRoom.GetCurSel();//������������
	CDialog::OnOK();                                //����IDOK
}
