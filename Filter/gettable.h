
#ifndef GETTABLE_H
#define GETTABLE_H

#include <stdio.h>
#include <iostream.h>
#include <stdlib.h>
#include <string.h>

//最大表数
#define		MAXTABLENUM		50
//当前实际表的个数
#define		CURTABLENUM		27
//最大item个数
#define		MAXITEMS		100
//单个字符最大长度
#define		SINGLSTRLEN		500

class Cell
{
public:
	Cell()
	{
		strcpy(s," ");
	}

	char s[50];//每个格子的数据
};

class Item
{
public:
	Item()
	{
		strcpy(s," ");
		show = 0;
	}

	char s[50];//itemname
	int show;//1-show,0-hide
};

class Table
{
public:
	Table()
	{
		strcpy(header,"");
		ptbl = NULL;
		row = 0;
		col = 0;
		headlines =0;
		skipwords = 0;
		twin = false;
	}
	Item items[MAXITEMS];
	Cell **ptbl;//表的内容
	char header[800];//表头，区分不同表的关键词
	int  row, col;//表总共的行数、列数
	int  headlines;//存储表头部所需要的行数
	int  skipwords;//从表关键字到内容跳过的单词数
	int  linemark;//表中一行的标志
	bool twin;//单表中是否有两种数据段
};

class GetTable
{
public:
	GetTable()
	{
		Init();
	}
	~GetTable()
	{
		if(NULL != fin)
			fclose(fin);
		if(NULL != fmaxmin)
			fclose(fmaxmin);
		if(NULL != fespecial)
			fclose(fespecial);
		if(NULL != fmax)
			fclose(fmax);
		if(NULL != ptable)
			free(ptable);
	}

	int  Read(char *pname);
	int  Write(char *pmaxmin, char *pmax, char *especial);
	void GetAllTable(void);
	void GetType1Table(int tblidx);
	void GetType2Table(int tblidx);
	void GetType3Table(int tblidx);
	void PostInit(int tblidx,bool dblcol=false);
	void T1_FillDate(int tblidx);
	void T2_FillDate(int tblidx);
	void T3_FillDate(int tblidx);
	void PrintTable(int tblidx, FILE *fout);

private:
	//function
	void InitTables(void);
	void Init(void);
	//attrib
	FILE  *fin, *fmaxmin, *fespecial, *fmax;
	char  *ptable;//**pbeamtbl,**pfibertbl,**pspringtbl;
	Table tables[MAXTABLENUM];
	char tmpstr[SINGLSTRLEN];
};


#endif