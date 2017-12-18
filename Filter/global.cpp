#include "global.h"

#include <stdio.h>
#include <iostream.h>
#include <stdlib.h>
#include <string.h>

/*******************************************************************
Name:	GetFirstStr
Input:	
Function:	获得一维字符数组中的首个字符串，同时首字符指往后移动;
若为ASIC串返回1，若不是ASIC串返回-1，失败则返回0；若ASIC串和非ASIC
串连在一起，则会分成两个读取
*******************************************************************/
int GetFirstStr(char *&table, char *s, int length)
{
	if(table==NULL)
	{
		printf("搜索空表的第一个字符串，失败！");
		return 0;
	}
	char *p = table;
	//过滤空格、换行和Tab键
	while((NULL!=p)&&(*p>=0 && *p<=32))
	{
		p++;
	}
	//表中全是空白字符，返回空
	if(NULL==p)
	{
		return 0;
	}
	int i=0;
	if(*p>32)//英文串首个字符大于0
	{
		while(*p>32)//非空白字符
		{
			s[i++]=*p;
			p++;
			if(i>=length)
			{
				printf("GetFirstStr中越界!\n");
				return 0;
			}
		}
		s[i]='\0';
		table = p;
		return 1;
	}
	else//非英文串首个字符小于0
	{
		while(*p<0)
		{
			s[i++] = *(p++);//读两个字节
			s[i++] = *(p++);
			if(i>=length)
			{
				printf("GetFirstStr中越界!\n");
				return 0;
			}
		}
		s[i] = '\0';
		table = p;
		return -1;
	}
}

/*******************************************************************
Name:	GetFirstNStr
Input:	
Function:	获得一维字符数组中的前N个字符串，将N个字符串合并成一个，
同时首字符指往后移动，成功返回1，失败返回0
*******************************************************************/
int  GetFirstNStr(char *&table, char *s, int length, int n)
{
	int i;
	char tmpstr[50];
	strcpy(s,"");
	for(i=0; i<n; i++)
	{
		if(0 == GetFirstStr(table,tmpstr,50))
			return 0;
		strcat(s,tmpstr);
	}
	return 1;
}

/*******************************************************************
Name:GapN
Input:stext--要跳动的指针，n--跳动的行数
Function:从stext开始，往下跳n行
*******************************************************************/
void GapN(char *&stext, int n)//ok
{
	if(NULL==stext || n<=0)
	{
		
		return;
	}
	int i;
	for(i=0 ;i<n ; i++)
	{
		while('\n' != *stext)
		{
			stext++;
		}
		stext++;
	}
}

/*******************************************************************
Name:	FilterNull
Input:	p--要跳动的指针，n--跳动的行数
Function:	过滤从p开始的空白(true)，或非空白(false)
*******************************************************************/
void FilterNull(char *&p, bool b)//ok
{
	if(NULL == p)
	{
		return ;
		
	}
	if(b)
	{	
		while('\0'!=*p && 0<=*p && 32>=*p)
		{
			p++;
		}
	}
	else
	{
		while('\0'!=*p && (0>*p || 32<*p))
		{
			p++;
		}
	}
}

/*******************************************************************
Name:	CountStr
Input:	p--要统计的字符串，n--返回列数
Function:	计算一列中字符串的个数
*******************************************************************/
void CountStr(char *p, int &col)//ok
{
	if(NULL == p)
	{
		col = 0;
		return ;
		
	}
	
	col =0;
	while('\n' != *p)
	{
		while(*p>=0 && *p<=32)
		{
			if('\n' == *p)
				return;
			p++;
		}
		col++ ;
		FilterNull(p,false);
	}
}

/*******************************************************************
Name:	CountDateLines
Input:	linemark--判断行数的标志，skip--跳过表头的单词数，pkey--区分
	各个表的主键
Function:	计算字符串ptable中满足条件的行数
*******************************************************************/
int CountDateLines(char *ptable, char *pkey, int skip, int linemark)
{
	if(NULL==pkey || NULL==ptable || skip<0 || linemark<0)
	{
		return 0;
	}
	//计算表的行数
	int row =0, i, j;
	char *pend, tmpstr[100];
	char *p = ptable;
	do{
		p = strstr(p,pkey);
		if(NULL == p)
			return row;
		GapN(p,1);
		for(i=0; i<skip; i++)
		{//过滤表头skip个单词
			GetFirstStr(p,tmpstr,100);
		}
		do
		{
			if(strcmp(p,"")==0)
				return row;
			pend = p;
			//若连续三个字符串有一个不是ASIC串则结束
			if(GetFirstStr(pend,tmpstr,100)<0)
				break;
			if(GetFirstStr(pend,tmpstr,100)<0)
				break;
			if(GetFirstStr(pend,tmpstr,100)<0)
				break;
			CountStr(p,j);
			if(linemark == j)//每组有一个 13 个字符串的行
			{
				row ++;
			}
			GapN(p,1);
		}while(1);
	}while(1);
}

/*******************************************************************
Name:	DeleteChar
Input:	s--字符数组，不能是字符串常量，ch--要删除的字符
Function:	删除字符数组所有为ch的字符
*******************************************************************/
void DeleteChar(char s[], char ch)
{
	char *p =s, *cur =s;
	while('\0' != *p)
	{
		while('\0'!=*cur)
		{
			if(*cur!=ch)
				break;
			cur++;
		}
		if('\0'==*cur)
		{
			*p = '\0';
			break;
		}
		*p = *cur;
		p++;
		cur++;
	}
}

/*******************************************************************
Name:	IsNumberStr
Input:	s--字符数组或者字符串常量
Function:	判断字符串是否为0-9之间数字组成
空串返回false，任何含有非0-9之间字符的字符串都返回false
*******************************************************************/
bool IsNumberStr(char *s)
{
	if(NULL==s || strcmp(s,"")==0)
		return false;
	char *p=s;
	while('\0'!=*p)
	{
		if((*p>'9'||*p<'0'))
			return false;
		p++;
	}
	return true;
}