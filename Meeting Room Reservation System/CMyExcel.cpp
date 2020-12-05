
#include "stdafx.h"
#include "CMyExcel.h"

CMyExcel::CMyExcel():m_rowCount(1),m_sheetCount(1),m_totalCol(256),m_totalRow(65536),m_matricImagCount(1),m_comCount(1)
{
	//获取系统的excel句柄
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

	//m_colPst初始化为A-Z，其中下表为0的为一个无意义的占位符
	m_colPst = new char[27];
	m_colPst[0] = '#';
	for(int i = 1;i<27;i++)
	{
		m_colPst[i]=64+i;
	}
}
CMyExcel::~CMyExcel()
{
	//在这里保存生成的excel
	m_book.SaveAs(
		m_filePath,
		_variant_t((long)56),//该参数使得保存的时候使用兼容模式，避免了使用excel2003打开的时候弹出提示框
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
	//释放占用的excel资源
	m_book.ReleaseDispatch();
	m_books.ReleaseDispatch();
	m_app.Quit();
	m_app.DetachDispatch();

	//将一些计数器变量复原
	m_comCount = 1;
	m_matricImagCount = 1;
}
CString CMyExcel::String2CString(const string& inStr)
{
	int nLen = (int)inStr.length()+1;
	int nwLen = MultiByteToWideChar(CP_ACP,0,inStr.c_str(),nLen,NULL,0);
	TCHAR* lpszOut = new TCHAR[nwLen];	//最多1024字节
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
	//获取需要的字节数
	nLength = WideCharToMultiByte(CP_ACP,NULL,inStr,-1,NULL,0,NULL,NULL);
	//申请char存储空间
	char *buffer = (char*)malloc(nLength);

	//转换
	WideCharToMultiByte(CP_ACP,NULL,inStr,-1,buffer,nLength,NULL,NULL);
	string str(buffer);

	//释放缓存区
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

	//用于标记当前写入的是哪一列：A、B、C、......
	long matrixCt = 0;

	//指定当前写入的行：需要先写入一些注释信息（m_comcount计数），然后在写入数据，因此将他们赋值即可
	m_rowCount = m_comCount;

	//标记当前列标题的变量：比如说（A，AX，BX等）
	CString locPst(_T(""));

	//标记保存位置的变量
	CString position0(_T(""));
	CString locPstReal(_T(""));

	//超过列数就不继续
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

	//数据写入文件
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
			//超过行数，就不再写入文件
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

	//用于标记当前写入的是哪一列：A、B、C、......
	long matrixCt = 0;

	//指定当前写入的行：需要先写入一些注释信息（m_comcount计数），然后在写入数据，因此将他们赋值即可
	m_rowCount = m_comCount;

	//标记当前列标题的变量：比如说（A，AX，BX等）
	CString locPstReal(_T(""));
	CString locPstImge(_T(""));

	//标记写入位置的变量：实数部分、虚数部分
	CString colReal(_T(""));
	CString colImge(_T(""));

	//描述信息
	CString mRow(_T("row = "));
	CString mCol(_T("col = "));
	CString temp;
	temp.Format(_T("%ld"),row);
	mRow = mRow + temp;
	temp.Empty();
	temp.Format(_T("%ld"),col);
	mCol = mCol + temp;

	//超过列数就不继续写
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

	//数据写入文件
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
			//写入实数
			m_range = m_sheet.get_Range(COleVariant(colReal),COleVariant(colReal));
			m_range.put_Value2(COleVariant(mateDataReal[idx]));
			//写入虚数
			m_range = m_sheet.get_Range(COleVariant(colImge),COleVariant(colImge));
			m_range.put_Value2(COleVariant(mateDataImag[idx]));

			//超过行数，就不再写入文件
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
	//获取矩形框走上角写入位置:E3
	CString locPst11(_T(""));
	rowName(locPst11,row1);
	CString temp11(_T(""));
	CString position11(_T(""));
	position11= locPst11;
	temp11.Format(_T("%ld"),col1);
	position11 += temp11;

	//获取矩形框走上角写入位置:E8
	CString locPst12(_T(""));
	rowName(locPst12,row1);
	CString temp12(_T(""));
	CString position12(_T(""));
	position12 = locPst12;
	temp12.Format(_T("%ld"),col2);
	position12 += temp12;

	//获取右上角写入位置 :P3
	CString locPst21(_T(""));
	rowName(locPst21,row2);
	CString temp21(_T(""));
	CString position21(_T(""));
	position21 = locPst21;
	temp21.Format(_T("%ld"),col1);
	position21 += temp21;

	//获取右下角写入位置 :P8
	CString locPst22(_T(""));
	rowName(locPst22,row2);
	CString temp22(_T(""));
	CString position22(_T(""));
	position22 = locPst22;
	temp21.Format(_T("%ld"),col2);
	position22 += temp21;
	
	CString myMatName(str.c_str());
	//首先将数据写入E3这一格中
	m_range = m_sheet.get_Range(COleVariant(position11),COleVariant(position11));
	m_range.put_Value2(_variant_t(myMatName));
	//然后合并E3-P8，形成矩形框
	m_range = m_sheet.get_Range(COleVariant(position11),COleVariant(position22));
	//这里就是“m_coverOptional”用到的地方！
	m_range.Merge(m_coverOptional);
	return 1;
}

