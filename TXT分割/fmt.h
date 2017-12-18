/*****************************算法描述:******************************************/
/*开始：若文件还没结束
1、读入一个字符ch，
2、若为汉字字符，则判断若为第二个字节，num+=2，转4
3、若为英文字符，则num+=1,转4
4、输出ch,判断若num>=30,并且当前字符为不为英文字母，则输出换行,num=0；转到开始。*/
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
	char infile[1000],outfile[1000];//输入，输出文件路径
};
