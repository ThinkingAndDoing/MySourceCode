#include "stdafx.h"
#include "fmt.h"
/*************************************************************
function:
input:
output:
*************************************************************/
int Format::fRun(unsigned int length)
{
	FILE* in; 
	FILE* out; 
	char cin; 
	int nLines = 0,i=0; 
	int bLow = 0; 
	if( ( in = fopen( infile, "r" ) ) == NULL ) 
	{ 
		MessageBox(NULL,"�����ļ�������!",NULL,MB_OK);
		return 1; 
	} 
	if( ( out = fopen( outfile, "w" ) ) == NULL ) 
	{ 
		MessageBox(NULL,"����ļ��򲻿�!",NULL,MB_OK);
		return 1; 
	} 
	
	while( !feof(in) ) 
	{ 
		cin = fgetc( in ); 
		if(cin == '\n') 
			cin=' '; 
		
		if(cin < 0) //�������������ֽڣ���16λ���������������ֽڵ����λ����1�� 
		{//�������ַ� 
			if(bLow) //�����ַ�ռ�����ֽڣ����Ǹ��ý��������
			{
				nLines+=2; 
				bLow=0; //�����ַ��ĵڶ����ֽ�
			} 
			else 
			{ 
				bLow=1; //�����ַ��ĵ�һ���ֽ�
			} 
		} 
		else 
		{ 
			bLow=0; 
			nLines++; //Ӣ����ĸҲ��һ���ַ�
		}
		fputc( cin, out ); 	
		if(nLines>=length&&(cin<97||cin>122)) 
		{
			fputc( '\n', out ); 
			nLines=0; 
		} 

	} 
	fputc( '\n', out ); 
	fclose( in ); 
	fclose( out ); 
	return 0;
}
