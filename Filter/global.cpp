#include "global.h"

#include <stdio.h>
#include <iostream.h>
#include <stdlib.h>
#include <string.h>

/*******************************************************************
Name:	GetFirstStr
Input:	
Function:	���һά�ַ������е��׸��ַ�����ͬʱ���ַ�ָ�����ƶ�;
��ΪASIC������1��������ASIC������-1��ʧ���򷵻�0����ASIC���ͷ�ASIC
������һ�����ֳ�������ȡ
*******************************************************************/
int GetFirstStr(char *&table, char *s, int length)
{
	if(table==NULL)
	{
		printf("�����ձ�ĵ�һ���ַ�����ʧ�ܣ�");
		return 0;
	}
	char *p = table;
	//���˿ո񡢻��к�Tab��
	while((NULL!=p)&&(*p>=0 && *p<=32))
	{
		p++;
	}
	//����ȫ�ǿհ��ַ������ؿ�
	if(NULL==p)
	{
		return 0;
	}
	int i=0;
	if(*p>32)//Ӣ�Ĵ��׸��ַ�����0
	{
		while(*p>32)//�ǿհ��ַ�
		{
			s[i++]=*p;
			p++;
			if(i>=length)
			{
				printf("GetFirstStr��Խ��!\n");
				return 0;
			}
		}
		s[i]='\0';
		table = p;
		return 1;
	}
	else//��Ӣ�Ĵ��׸��ַ�С��0
	{
		while(*p<0)
		{
			s[i++] = *(p++);//�������ֽ�
			s[i++] = *(p++);
			if(i>=length)
			{
				printf("GetFirstStr��Խ��!\n");
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
Function:	���һά�ַ������е�ǰN���ַ�������N���ַ����ϲ���һ����
ͬʱ���ַ�ָ�����ƶ����ɹ�����1��ʧ�ܷ���0
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
Input:stext--Ҫ������ָ�룬n--����������
Function:��stext��ʼ��������n��
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
Input:	p--Ҫ������ָ�룬n--����������
Function:	���˴�p��ʼ�Ŀհ�(true)����ǿհ�(false)
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
Input:	p--Ҫͳ�Ƶ��ַ�����n--��������
Function:	����һ�����ַ����ĸ���
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
Input:	linemark--�ж������ı�־��skip--������ͷ�ĵ�������pkey--����
	�����������
Function:	�����ַ���ptable����������������
*******************************************************************/
int CountDateLines(char *ptable, char *pkey, int skip, int linemark)
{
	if(NULL==pkey || NULL==ptable || skip<0 || linemark<0)
	{
		return 0;
	}
	//����������
	int row =0, i, j;
	char *pend, tmpstr[100];
	char *p = ptable;
	do{
		p = strstr(p,pkey);
		if(NULL == p)
			return row;
		GapN(p,1);
		for(i=0; i<skip; i++)
		{//���˱�ͷskip������
			GetFirstStr(p,tmpstr,100);
		}
		do
		{
			if(strcmp(p,"")==0)
				return row;
			pend = p;
			//�����������ַ�����һ������ASIC�������
			if(GetFirstStr(pend,tmpstr,100)<0)
				break;
			if(GetFirstStr(pend,tmpstr,100)<0)
				break;
			if(GetFirstStr(pend,tmpstr,100)<0)
				break;
			CountStr(p,j);
			if(linemark == j)//ÿ����һ�� 13 ���ַ�������
			{
				row ++;
			}
			GapN(p,1);
		}while(1);
	}while(1);
}

/*******************************************************************
Name:	DeleteChar
Input:	s--�ַ����飬�������ַ���������ch--Ҫɾ�����ַ�
Function:	ɾ���ַ���������Ϊch���ַ�
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
Input:	s--�ַ���������ַ�������
Function:	�ж��ַ����Ƿ�Ϊ0-9֮���������
�մ�����false���κκ��з�0-9֮���ַ����ַ���������false
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