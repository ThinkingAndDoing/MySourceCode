/*****************************�㷨����:******************************************/
/*��ʼ�����ļ���û����
1������һ���ַ�ch��
2����Ϊ�����ַ������ж���Ϊ�ڶ����ֽڣ�num+=2��ת4
3����ΪӢ���ַ�����num+=1,ת4
4�����ch,�ж���num>=30,���ҵ�ǰ�ַ�Ϊ��ΪӢ����ĸ�����������,num=0��ת����ʼ��*/
/********************************************************************************/

#include <stdio.h> 
#include <string.h> 

class Format
{
public:
	Format()
	{
		strcpy(infile, "in.txt");
		strcpy(outfile, "out.txt");
	}
	int SetFileName(char *i, char *o)
	{
		strcpy(infile,i);
		strcpy(outfile,o);
		return 0;
	}
	int fRun(unsigned int length);
private:
	char infile[1000],outfile[1000];//���룬����ļ�·��
};
