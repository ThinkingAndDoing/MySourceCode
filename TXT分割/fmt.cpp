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
		MessageBox(NULL,"输入文件不存在!",NULL,MB_OK);
		return 1; 
	} 
	if( ( out = fopen( outfile, "w" ) ) == NULL ) 
	{ 
		MessageBox(NULL,"输出文件打不开!",NULL,MB_OK);
		return 1; 
	} 
	
	while( !feof(in) ) 
	{ 
		cin = fgetc( in ); 
		if(cin == '\n') 
			cin=' '; 
		
		if(cin < 0) //汉字内码两个字节，共16位二进制数，两个字节的最高位都是1。 
		{//是中文字符 
			if(bLow) //中文字符占两个字节，这是个好解决方法。
			{
				nLines+=2; 
				bLow=0; //中文字符的第二个字节
			} 
			else 
			{ 
				bLow=1; //中文字符的第一个字节
			} 
		} 
		else 
		{ 
			bLow=0; 
			nLines++; //英文字母也算一个字符
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
