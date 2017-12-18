
#ifndef GETTABLE_H
#define GETTABLE_H

#include <stdio.h>
#include <iostream.h>
#include <stdlib.h>
#include <string.h>

//������
#define		MAXTABLENUM		50
//��ǰʵ�ʱ�ĸ���
#define		CURTABLENUM		27
//���item����
#define		MAXITEMS		100
//�����ַ���󳤶�
#define		SINGLSTRLEN		500

class Cell
{
public:
	Cell()
	{
		strcpy(s," ");
	}

	char s[50];//ÿ�����ӵ�����
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
	Cell **ptbl;//�������
	char header[800];//��ͷ�����ֲ�ͬ��Ĺؼ���
	int  row, col;//���ܹ�������������
	int  headlines;//�洢��ͷ������Ҫ������
	int  skipwords;//�ӱ�ؼ��ֵ����������ĵ�����
	int  linemark;//����һ�еı�־
	bool twin;//�������Ƿ����������ݶ�
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