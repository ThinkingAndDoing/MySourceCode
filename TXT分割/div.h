#include <stdio.h>
#include <stdlib.h>

//macro
#define	BOOL	int
#define TRUE	1
#define FALSE	0
#define FileNameLength	1000//�ļ�������

class Divide
{
public:
//function
	Divide(){PageSize=100*1024;apage=(char*)malloc(sizeof(char)*(PageSize+1));}
	Divide(long size){PageSize=size;apage=(char*)malloc(sizeof(char)*(PageSize+1));}
	BOOL	Read(FILE *fin);
	void	CFormat(void);
	BOOL	Write(FILE *fout);
	BOOL	Convert(void);
	void	ReSize(long size)
	{
		PageSize=size;
		if(NULL!=apage)
		{
			free(apage);
			apage =NULL;
		}
		apage=(char*)malloc(sizeof(char)*(PageSize+1));
	}
	void	SetName(char* name){strcpy(infname,name);}
	~Divide()
	{
		free(apage);
	}
//var
	int		pagename;
private:
	FILE	*pfin, *pfout;
	long	PageSize;//ҳ���С
	char	infname[FileNameLength+1], outfname[FileNameLength+1];
	char	*apage;//ĳһҳ������
};