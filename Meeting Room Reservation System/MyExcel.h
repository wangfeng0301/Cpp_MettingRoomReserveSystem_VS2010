/*CMyExcel��ͷ�ļ�*/
#include "CApplication.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorksheet.h"
#include "CWorkbooks.h"
#include "CWorksheets.h"
#include <string>
using namespace std;
class CMyExcel
{
//private:
public:
	//���Excel����ı���
	CApplication m_app;	 //ExcelӦ�ó���ӿ�
	CWorkbooks m_books;	 //����������
	CWorkbook m_book;    //����������
	CWorksheets m_sheets;//��������	
	CWorksheet m_sheet;	 //�������������excel�е�ǰд��ı�ǩҳ
	CRange m_range;		 //���д��ķ�Χ��Excel����Ե�Ԫ��Ĳ�����Ӧ�Ȼ�ȡ���Ӧ��Range����

	COleVariant m_covTrue,m_covFalse,m_coverOptional,m_filePath;	 
	long m_rowCount;	//���Excel��ǰд�������
	long m_sheetCount;	//���Excelʹ���˶��ٱ�ǩҳ�ı���
	long m_totalRow;	//���Excel�������ı���
	long m_totalCol;	//���Excel�������ı���
	char *m_colPst;		//һ������A-Z������
	long m_matricImagCount;//�м�����
	long m_comCount;    //ע����Ϣ��������д��ע�ͺ�д������

public:
	CMyExcel();         //���캯��
	virtual ~CMyExcel();//��������

	//string �ַ���ת��ΪCString
	CString String2CString(const string& inStr);
	
	//CString �ַ���ת��Ϊstring
	string CString2String(const CString & inStr);

	//���ļ����ڶ�д
	//���룺�ļ�������ģʽ
	//������ļ���״̬
	int openfile(const string& filepath ,int mode);

	//д��ʵ����
	//���룺�ļ�������д���ļ�������ָ�룬��д����У���д�����
	//������ļ�д��״̬
	int writeMatrix(const string &matName ,double *mateData,long row,long col);

	//д�븴����
	//�����ļ�������д���ļ�������ʵ��ָ�룬��д���ļ��������鲿ָ�룬��д����У���д�����
	//������ļ�д��״̬
	int writeMatrix(const string &matName ,double *mateDataReal,double *mateDataImag,long row,long col);

	//д���ַ���
	//��Excel��ָ����Χ���ɺ���ָ���ַ������ļ�
	int writeString(const string& str,int& col1,int& col2,int& row1,int& row2);

	//һ�����㵱ǰ���������еĺ���(���뵽ָ������Ҫ�õ��еı��⣺A��AX�ȣ�����������26����)
	inline void rowName(CString &mRowName,const long& mCount )
	{
		if(mCount < 27 )
		{
			mRowName += m_colPst[mCount];
		}
		else
		{
			int i = mCount / 26;
			int j = mCount %26;
			mRowName += m_colPst[i];
			mRowName += m_colPst[j];
		}
	}


};