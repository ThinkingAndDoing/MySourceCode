#include "stdafx.h"
#include "div.h"

/*************************************************************
function:
input:
output:
*************************************************************/
BOOL Divide::Convert(void)
{
	int i;
	BOOL pfinish=FALSE;
	pfin  = fopen(infname,"r");
	if(NULL==pfin)
	{
		MessageBox(NULL,"文件不存在!",NULL,MB_OK);
		return FALSE;
	}
	do{
		//Read a page.
		pfinish=Read(pfin);
		//Get the name of outputed file and open it.
		i=0;
		while(('\0'!=infname[i])&&('.'!=infname[i]))
			outfname[i]=infname[i++];
		outfname[i++]=(pagename%1000)/100+'0';
		outfname[i++]=(pagename%100)/10+'0';
		outfname[i++]=(pagename%10)/1+'0';
		outfname[i++]='.';
		outfname[i++]='t';
		outfname[i++]='x';
		outfname[i++]='t';
		if('\"'==infname[0])
			outfname[i++]='\"';
		outfname[i]='\0';
		pfout = fopen(outfname,"w");
		if(pfout==NULL)
		{
			MessageBox(NULL,"不能新建文件!\n",NULL,MB_OK);
			return FALSE;
		}
		//Format
//		CFormat(apage);
		//Write a page.
		Write(pfout);
		//next page
		pagename++;
	}while(pfinish!=TRUE);
	
	fclose(pfin);
	return TRUE;
}
/*************************************************************
function:
input:
output:
*************************************************************/
BOOL Divide::Read(FILE *fin)
{
	int i=0,bLow=0,nLines=0;
	int ch=fgetc(fin);
	if(EOF==ch)
	{
		apage[i]='\0';
		return TRUE;
	}
	do{	
		if(ch > 127)
		{
			if(bLow)
			{
				nLines+=2;
				bLow=0;
			} 
			else 
			{
				bLow=1;
			} 
		}
		else 
		{ 
			bLow=0;
		}
		apage[i]=ch;
		i++;
		ch=fgetc(fin);
	}while(EOF!=ch&&(i<PageSize-1||bLow==1));
	apage[i]='\0';
	fseek(fin,-1L,1);
	if(EOF!=ch)
		return FALSE;
	else
		return TRUE;
}
/*************************************************************
function:
input:
output:
*************************************************************/
void Divide::CFormat(void)
{
	int i,j;char *temp=(char*)malloc(sizeof(char)*(PageSize+1));
	i=0;j=0;
	do{
		while('\n'!=apage[i]&&'\0'!=apage[i])
		{
			temp[j]=apage[i];
			i++;j++;
		}
		if('\0'!=apage[i])
			break;
		while('\n'==apage[++i]||'\t'==apage[i]);
		temp[j]='\n';j++;
	}while('\0'!=apage[i]);
	temp[j]='\n';
	for(i=0;i<=j;i++)
		apage[i]=temp[i];
	free(temp);
}
/*************************************************************
function:
input:
output:
*************************************************************/
BOOL Divide::Write(FILE *fout)
{
	//write title
	int i,j;char name[FileNameLength];
	i=0;j=0;
	do{
		name[j]=outfname[i];
		if(outfname[i]=='\\')
			j=0;
		else
			j++;
		i++;
	}while(outfname[i]!='.');
	name[j]='\0';
	fputc('\n',fout);
	fputs(name,fout);
	fputc('\n',fout);
	fputc('\n',fout);
	//write content.
	i=0;
	while('\0'!=apage[i])
	{
		fputc(apage[i],fout);
		i++;
	}
	fputc('\n',fout);
	fclose(fout);
	return TRUE;
}