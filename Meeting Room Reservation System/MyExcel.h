/*CMyExcel类头文件*/
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
	//标记Excel对象的变量
	CApplication m_app;	 //Excel应用程序接口
	CWorkbooks m_books;	 //工作簿集合
	CWorkbook m_book;    //单个工作簿
	CWorksheets m_sheets;//工作表集合	
	CWorksheet m_sheet;	 //单个工作表，标记excel中当前写入的标签页
	CRange m_range;		 //标记写入的范围，Excel中针对单元格的操作都应先获取其对应的Range对象

	COleVariant m_covTrue,m_covFalse,m_coverOptional,m_filePath;	 
	long m_rowCount;	//标记Excel当前写入的列数
	long m_sheetCount;	//标记Excel使用了多少标签页的变量
	long m_totalRow;	//标记Excel总列数的变量
	long m_totalCol;	//标记Excel总行数的变量
	char *m_colPst;		//一个含有A-Z的数组
	long m_matricImagCount;//列计数器
	long m_comCount;    //注释信息计数器，写完注释后写入数据

public:
	CMyExcel();         //构造函数
	virtual ~CMyExcel();//析构函数

	//string 字符串转换为CString
	CString String2CString(const string& inStr);
	
	//CString 字符串转换为string
	string CString2String(const CString & inStr);

	//打开文件用于读写
	//输入：文件名，打开模式
	//输出：文件打开状态
	int openfile(const string& filepath ,int mode);

	//写入实数组
	//输入：文件名，待写入文件的内容指针，待写入的行，待写入的列
	//输出：文件写入状态
	int writeMatrix(const string &matName ,double *mateData,long row,long col);

	//写入复数组
	//输入文件名，待写入文件的内容实部指针，待写入文件的内容虚部指针，待写入的行，待写入的列
	//输出：文件写入状态
	int writeMatrix(const string &matName ,double *mateDataReal,double *mateDataImag,long row,long col);

	//写入字符串
	//在Excel的指定范围生成含有指定字符串的文件
	int writeString(const string& str,int& col1,int& col2,int& row1,int& row2);

	//一个计算当前数据输入列的函数(输入到指定列需要得到列的标题：A，AX等，而他们满足26进制)
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