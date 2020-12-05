
#include "stdafx.h"
#include "CMyExcel.h"

CMyExcel::CMyExcel():m_rowCount(1),m_sheetCount(1),m_totalCol(256),m_totalRow(65536),m_matricImagCount(1),m_comCount(1)
{
	//��ȡϵͳ��excel���
	if(!m_app.CreateDispatch(TEXT("Excel.Application")))
	{
		AfxMessageBox(_T("Could not start Excel and get Application object !"));
		return;
	}
	m_covTrue = COleVariant((short)TRUE);
	m_covFalse = COleVariant((short)FALSE);
	m_coverOptional = COleVariant((long)DISP_E_PARAMNOTFOUND,VT_ERROR);
	m_books = m_app.get_Workbooks();
	m_book = m_books.Add(m_coverOptional);
	m_sheets = m_book.get_Sheets();

	//m_colPst��ʼ��ΪA-Z�������±�Ϊ0��Ϊһ���������ռλ��
	m_colPst = new char[27];
	m_colPst[0] = '#';
	for(int i = 1;i<27;i++)
	{
		m_colPst[i]=64+i;
	}
}
CMyExcel::~CMyExcel()
{
	//�����ﱣ�����ɵ�excel
	m_book.SaveAs(
		m_filePath,
		_variant_t((long)56),//�ò���ʹ�ñ����ʱ��ʹ�ü���ģʽ��������ʹ��excel2003�򿪵�ʱ�򵯳���ʾ��
		m_coverOptional,
		m_coverOptional,
		m_coverOptional,
		m_coverOptional,
		0,
		m_coverOptional,
		m_coverOptional,
		m_coverOptional,
		m_coverOptional,
		m_coverOptional
		);
	//�ͷ�ռ�õ�excel��Դ
	m_book.ReleaseDispatch();
	m_books.ReleaseDispatch();
	m_app.Quit();
	m_app.DetachDispatch();

	//��һЩ������������ԭ
	m_comCount = 1;
	m_matricImagCount = 1;
}
CString CMyExcel::String2CString(const string& inStr)
{
	int nLen = (int)inStr.length()+1;
	int nwLen = MultiByteToWideChar(CP_ACP,0,inStr.c_str(),nLen,NULL,0);
	TCHAR* lpszOut = new TCHAR[nwLen];	//���1024�ֽ�
	MultiByteToWideChar(CP_ACP,0,inStr.c_str(),nLen,lpszOut,nwLen);
	CString outStr;
	outStr += lpszOut;

	delete []lpszOut;
	lpszOut = NULL;
	return outStr;
}

string CMyExcel::CString2String(const CString & inStr)
{
	int nLength = 0;
	//��ȡ��Ҫ���ֽ���
	nLength = WideCharToMultiByte(CP_ACP,NULL,inStr,-1,NULL,0,NULL,NULL);
	//����char�洢�ռ�
	char *buffer = (char*)malloc(nLength);

	//ת��
	WideCharToMultiByte(CP_ACP,NULL,inStr,-1,buffer,nLength,NULL,NULL);
	string str(buffer);

	//�ͷŻ�����
	free(buffer);
	return str;

}
int CMyExcel::openfile(const string& filepath ,int mode)
{
	if(m_books)
	{
		m_filePath = COleVariant(String2CString(filepath));
		return 1;
	}
	else
		return -1;
}
int CMyExcel::writeMatrix(const string &matName ,double *mateData,long row,long col)
{
	m_sheet = m_sheets.get_Item(COleVariant((short)m_sheetCount));

	//���ڱ�ǵ�ǰд�������һ�У�A��B��C��......
	long matrixCt = 0;

	//ָ����ǰд����У���Ҫ��д��һЩע����Ϣ��m_comcount��������Ȼ����д�����ݣ���˽����Ǹ�ֵ����
	m_rowCount = m_comCount;

	//��ǵ�ǰ�б���ı���������˵��A��AX��BX�ȣ�
	CString locPst(_T(""));

	//��Ǳ���λ�õı���
	CString position0(_T(""));
	CString locPstReal(_T(""));

	//���������Ͳ�����
	if(m_matricImagCount > m_totalCol)
	{
		return -1;
	}

	matrixCt = m_matricImagCount++;
	CString mRow(_T("row="));
	CString mCol(_T("col="));
	CString temp;
	temp.Format(_T("%ld"),row);
	mRow = mRow + temp;
	temp.Empty();
	temp.Format(_T("%ld"),col);
	mCol = mCol + temp;
	rowName(locPst,matrixCt);
	position0 = locPst;
	temp.Empty();
	temp.Format(_T("%ld"),m_rowCount++);
	position0+=temp;
	CString myMatName(matName.c_str());
	m_range = m_sheet.get_Range(COleVariant(position0),COleVariant(position0));
	m_range.put_Value2(_variant_t(myMatName));


	position0 = locPst;
	temp.Empty();
	temp.Format(_T("%ld"),m_rowCount++);
	position0+=temp;
	m_range = m_sheet.get_Range(COleVariant(position0),COleVariant(position0));
	m_range.put_Value2(COleVariant(TEXT("----")));

	//����д���ļ�
	for(long iRow = 0;iRow < row;iRow++)
	{
		locPstReal.Empty();
		long tmpCol = matrixCt++;
		rowName(locPstReal, tmpCol);
		position0 = locPstReal;
		long rowCount = m_rowCount;
		for(long icol = 0;icol<col; icol++)
		{
			long idx = iRow*col + icol;
			position0 = locPst;
			temp.Empty();
			temp.Format(_T("%ld"),rowCount++);
			position0 += temp;
			m_range = m_sheet.get_Range(COleVariant(position0),COleVariant(position0));
			m_range.put_Value2(COleVariant(mateData[idx]));
			//�����������Ͳ���д���ļ�
			if(rowCount > m_totalRow)
			{
				break;
			}
		}
	}
	m_comCount = 1;
	return 1;
}

int CMyExcel::writeMatrix(const string &matName ,double *mateDataReal,
	double *mateDataImag,long row,long col)
{
	m_sheet = m_sheets.get_Item(COleVariant((short)m_sheetCount));

	//���ڱ�ǵ�ǰд�������һ�У�A��B��C��......
	long matrixCt = 0;

	//ָ����ǰд����У���Ҫ��д��һЩע����Ϣ��m_comcount��������Ȼ����д�����ݣ���˽����Ǹ�ֵ����
	m_rowCount = m_comCount;

	//��ǵ�ǰ�б���ı���������˵��A��AX��BX�ȣ�
	CString locPstReal(_T(""));
	CString locPstImge(_T(""));

	//���д��λ�õı�����ʵ�����֡���������
	CString colReal(_T(""));
	CString colImge(_T(""));

	//������Ϣ
	CString mRow(_T("row = "));
	CString mCol(_T("col = "));
	CString temp;
	temp.Format(_T("%ld"),row);
	mRow = mRow + temp;
	temp.Empty();
	temp.Format(_T("%ld"),col);
	mCol = mCol + temp;

	//���������Ͳ�����д
	if(m_matricImagCount > m_totalCol)
	{
		return -1;
	}
	matrixCt = m_matricImagCount;
	m_matricImagCount += (row * 2);
	rowName(locPstReal, matrixCt);
	colReal = locPstReal;
	temp.Empty();
	temp.Format(_T("%ld"),m_rowCount++);
	colReal += temp;

	CString myMatName(matName.c_str());
	m_range = m_sheet.get_Range(COleVariant(colReal),COleVariant(colReal));
	m_range.put_Value2(_variant_t(myMatName));

	colReal = locPstReal;
	temp.Empty();
	temp.Format(_T("%ld"),m_rowCount++);
	colReal+=temp;
	m_range = m_sheet.get_Range(COleVariant(colReal),COleVariant(colReal));
	m_range.put_Value2(COleVariant(TEXT("--------")));

	//����д���ļ�
	for(long iRow = 0;iRow < row;iRow++)
	{
		locPstReal.Empty();
		locPstImge.Empty();
		long tmpCol = matrixCt;
		rowName(locPstReal, tmpCol);
		rowName(locPstImge, tmpCol+1);
		matrixCt += 2;
		colReal = locPstReal;
		colImge = locPstImge;
		long rowCount = m_rowCount;
		for(long icol = 0;icol<col; icol++)
		{
			long idx = iRow*col + icol;
			colReal = locPstReal;
			colImge = locPstImge;
			temp.Empty();
			temp.Format(_T("%ld"),rowCount++);
			colReal += temp;
			colImge += temp;
			//д��ʵ��
			m_range = m_sheet.get_Range(COleVariant(colReal),COleVariant(colReal));
			m_range.put_Value2(COleVariant(mateDataReal[idx]));
			//д������
			m_range = m_sheet.get_Range(COleVariant(colImge),COleVariant(colImge));
			m_range.put_Value2(COleVariant(mateDataImag[idx]));

			//�����������Ͳ���д���ļ�
			if(rowCount > m_totalRow)
			{
				break;
			}
		}
	}
	m_comCount = 1;
	return 1;
}
int CMyExcel::writeString(const string& str,int& col1,int& row1,int& col2,int& row2)
{
	m_sheet = m_sheets.get_Item(COleVariant((short)m_sheetCount));
	//��ȡ���ο����Ͻ�д��λ��:E3
	CString locPst11(_T(""));
	rowName(locPst11,row1);
	CString temp11(_T(""));
	CString position11(_T(""));
	position11= locPst11;
	temp11.Format(_T("%ld"),col1);
	position11 += temp11;

	//��ȡ���ο����Ͻ�д��λ��:E8
	CString locPst12(_T(""));
	rowName(locPst12,row1);
	CString temp12(_T(""));
	CString position12(_T(""));
	position12 = locPst12;
	temp12.Format(_T("%ld"),col2);
	position12 += temp12;

	//��ȡ���Ͻ�д��λ�� :P3
	CString locPst21(_T(""));
	rowName(locPst21,row2);
	CString temp21(_T(""));
	CString position21(_T(""));
	position21 = locPst21;
	temp21.Format(_T("%ld"),col1);
	position21 += temp21;

	//��ȡ���½�д��λ�� :P8
	CString locPst22(_T(""));
	rowName(locPst22,row2);
	CString temp22(_T(""));
	CString position22(_T(""));
	position22 = locPst22;
	temp21.Format(_T("%ld"),col2);
	position22 += temp21;
	
	CString myMatName(str.c_str());
	//���Ƚ�����д��E3��һ����
	m_range = m_sheet.get_Range(COleVariant(position11),COleVariant(position11));
	m_range.put_Value2(_variant_t(myMatName));
	//Ȼ��ϲ�E3-P8���γɾ��ο�
	m_range = m_sheet.get_Range(COleVariant(position11),COleVariant(position22));
	//������ǡ�m_coverOptional���õ��ĵط���
	m_range.Merge(m_coverOptional);
	return 1;
}

