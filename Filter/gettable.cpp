#include "gettable.h"
#include "global.h"
#include <tchar.h>

/***************************************************************************
ȫ�ֱ�����1--9��
����`�Q�����͂�v�f          �׏d�X�e�b�v =      3001
����`�R�����͂�v�f          �׏d�X�e�b�v =       101
�Q�����t�@�C�o�[�v�f          �׏d�X�e�b�v =       100
�R�����t�@�C�o�[�v�f          �׏d�X�e�b�v =       101
�g���X�v�f                    �׏d�X�e�b�v =       101
�o�l�v�f                      �׏d�X�e�b�v =      3001
�w�������i�o�l�v�f            �׏d�X�e�b�v =       101
�w������]�o�l�v�f            �׏d�X�e�b�v =       101
�ψ�       �׏d�X�e�b�v =      3001
***************************************************************************/

static char strtbl[CURTABLENUM][MAXITEMS][50] =
{
	//1
	{_T("�v�f�ԍ�"),_T("����(G1)(kN)"),_T("����(G2)(kN)"),_T("����f��(G1)(kN)"),_T("����f��(G2)(kN)"),
_T("�Ȃ����[�����g(G1)(kN.m)"),_T("�Ȃ����[�����g(G2)(kN.m)"),_T("���ό`��(G2-G1)(m)"),_T("����f�p(G2-G1)(rad)"),
_T("�ȗ�(/m)"),_T("�Ȃ����[�����g(kN.m)"),_T("����f�����ቺ��"),_T("�Ȃ������ቺ��")},
	//2
	{_T("�v�f�ԍ�"),_T("����(G1)(kN)"),_T("����(G2)(kN)"),_T("����f��Y(G1)(kN)"),_T("����f��Z(G1)(kN)")
,_T("����f��Y(G2)(kN)"),_T("����f��Z(G2)(kN)"),_T("�˂��胂�[�����g(G1)(kN.m)"),_T("�˂��胂�[�����g(G2)(kN.m)")
,_T("�Ȃ����[�����gY(G1)(kN.m)"),_T("�Ȃ����[�����gZ(G1)(kN.m)"),_T("�Ȃ����[�����gY(G2)(kN.m)"),_T("�Ȃ����[�����gZ(G2)(kN.m)")
,_T("���ό`��(G2-G1)(m)"),_T("����f�pY(G2-G1)(rad)"),_T("�ȗ�Z(/m)"),_T("�Ȃ����[�����gZ(kN.m)"),_T("����f�����ቺ��")
,_T("�Ȃ������ቺ��")},
	//3
	{_T("�v�f�ԍ�"),_T("����(G1)(kN)"),_T("����(G2)(kN)"),_T("����f��(G1)(kN)"),_T("����f��(G2)(kN)"),
_T("�Ȃ����[�����g(G1)(kN.m)"),_T("�Ȃ����[�����g(G2)(kN.m)"),_T("���ό`��(G2-G1)(m)"),_T("����f�p(G2-G1)(rad)"),
_T("�ȗ�(G2-G1)(/m)"),_T("�Ȃ����[�����g(����)(kN.m)"),_T("�Ȃ������ቺ��"),_T("(�t�@�C�o�[�ԍ�)"),_T("�Ђ���")
,_T("����"),_T("����")},
	//4
	{_T("�v�f�ԍ�"),_T("����(G1)(kN)"),_T("����(G2)(kN)"),_T("����f��Y(G1)(kN)"),_T("����f��Z(G1)(kN)")
,_T("����f��Y(G2)(kN)"),_T("����f��Z(G2)(kN)"),_T("�˂��胂�[�����g(G1)(kN.m)"),_T("�˂��胂�[�����g(G2)(kN.m)")
,_T("�Ȃ����[�����gY(G1)(kN.m)"),_T("�Ȃ����[�����gZ(G1)(kN.m)"),_T("�Ȃ����[�����gY(G2)(kN.m)"),_T("�Ȃ����[�����gZ(G2)(kN.m)")
,_T("���ό`��(G2-G1)(m)"),_T("����f�pY(G2-G1)(rad)"),_T("����f�pZ(G2-G1)(rad)"),_T("�ȗ�Y(G2-G1)(/m)")
,_T("�ȗ�Z(G2-G1)(/m)"),_T("�Ȃ����[�����gY.����(kN.m)"),_T("�Ȃ����[�����gZ.����(kN.m)"),_T("�Ȃ�����Y�ቺ��")
,_T("�Ȃ�����Z�ቺ��"),_T("(�t�@�C�o�[�ԍ�)"),_T("�Ђ���"),_T("����"),_T("����")},
	//5
	{_T("�v�f�ԍ�"),_T("����(G1)(kN)"),_T("����(G2)(kN)"),_T("���ό`��(m)"),_T("�����ቺ��")},
	//6
	{_T("�v�f�ԍ�"),_T("�o�l����(G2)"),_T("�o�l�ό`��(G2-G1)"),_T("�����ቺ��")},
	//7
	{_T("�v�f�ԍ�"),_T("�o�l����(G2)(kN)"),_T("�o�l�ό`��(G2-G1)(m)"),_T("�����ቺ��")},
	//8
	{_T("�v�f�ԍ�"),_T("�o�l����(G2)(kN)"),_T("�o�l�ό`��(G2-G1)(m)"),_T("�����ቺ��")},
	//9
	{_T("�ߓ_�ԍ�"),_T("�sx(m)"),_T("�sy(m)"),_T("�sz(m)"),_T("�qx(rad)"),_T("�qy(rad)"),_T("�qz(rad)")},
	//10
	 {_T("�v�f�ԍ�")
,_T("����(G1)(kN)"),_T("����(G2)(kN)"),_T("����f��(G1)(kN)"),_T("����f��(G2)(kN)"),_T("�Ȃ����[�����g(G1)(kN.m)")
,_T("�Ȃ����[�����g(G2)(kN.m)"),_T("������+SY(G1)(kPa)"),_T("������-SY(G1)(kPa)"),_T("������+SY(G2)(kPa)")
,_T("������-SY(G2)(kPa)"),_T("���ό`��(G2-G1)(m)"),_T("����f�p(G2-G1)(rad)"),_T("�ȗ�(/m)"),_T("�Ȃ����[�����g(kN.m)")
,_T("����f�����ቺ��"),_T("�Ȃ������ቺ��")},
	//11
	{_T("�v�f�ԍ�"),_T("����(G1)(kN)"),_T("����(G2)(kN)"),_T("����f��Y(G1)(kN)"),_T("����f��Z(G1)(kN)")
,_T("����f��Y(G2)(kN)"),_T("����f��Z(G2)(kN)"),_T("�˂��胂�[�����g(G1)(kN.m)"),_T("�˂��胂�[�����g(G2)(kN.m)")
,_T("�Ȃ����[�����gY(G1)(kN.m)"),_T("�Ȃ����[�����gZ(G1)(kN.m)"),_T("�Ȃ����[�����gY(G2)(kN.m)"),_T("�Ȃ����[�����gZ(G2)(kN.m)")
,_T("���ό`��(G2-G1)(m)"),_T("����f�pY(G2-G1)(rad)"),_T("�ȗ�Z(/m)"),_T("�Ȃ����[�����gZ(kN.m)"),_T("����f�����ቺ��")
,_T("�Ȃ������ቺ��")},
	//12
	{_T("�v�f�ԍ�"),_T("����(G1)(kN)"),_T("����(G2)(kN)"),_T("����f��(G1)(kN)"),_T("����f��(G2)(kN)"),
_T("�Ȃ����[�����g(G1)(kN.m)"),_T("�Ȃ����[�����g(G2)(kN.m)"),_T("���ό`��(G2-G1)(m)"),_T("����f�p(G2-G1)(rad)"),
_T("�ȗ�(G2-G1)(/m)"),_T("�Ȃ����[�����g(����)(kN.m)"),_T("�Ȃ������ቺ��"),_T("(�t�@�C�o�[�ԍ�)"),_T("�Ђ���")
,_T("����"),_T("����")},
	//13
	{_T("�v�f�ԍ�"),_T("����(G1)(kN)"),_T("����(G2)(kN)"),_T("����f��Y(G1)(kN)"),_T("����f��Z(G1)(kN)")
,_T("����f��Y(G2)(kN)"),_T("����f��Z(G2)(kN)"),_T("�˂��胂�[�����g(G1)(kN.m)"),_T("�˂��胂�[�����g(G2)(kN.m)")
,_T("�Ȃ����[�����gY(G1)(kN.m)"),_T("�Ȃ����[�����gZ(G1)(kN.m)"),_T("�Ȃ����[�����gY(G2)(kN.m)"),_T("�Ȃ����[�����gZ(G2)(kN.m)")
,_T("���ό`��(G2-G1)(m)"),_T("����f�pY(G2-G1)(rad)"),_T("����f�pZ(G2-G1)(rad)"),_T("�ȗ�Y(G2-G1)(/m)")
,_T("�ȗ�Z(G2-G1)(/m)"),_T("�Ȃ����[�����gY.����(kN.m)"),_T("�Ȃ����[�����gZ.����(kN.m)"),_T("�Ȃ�����Y�ቺ��")
,_T("�Ȃ�����Z�ቺ��"),_T("(�t�@�C�o�[�ԍ�)"),_T("�Ђ���"),_T("����"),_T("����")},
	//14
	{_T("�v�f�ԍ�"),_T("����(G1)(kN)"),_T("����(G2)(kN)"),_T("���ό`��(m)"),_T("�����ቺ��")},
	//15
	{_T("�v�f�ԍ�"),_T("�o�l����(G2)"),_T("�o�l�ό`��(G2-G1)"),_T("�����ቺ��")},
	//16
	{_T("�v�f�ԍ�"),_T("�o�l����(G2)(kN)"),_T("�o�l�ό`��(G2-G1)(m)"),_T("�����ቺ��")},
	//17
	{_T("�v�f�ԍ�"),_T("�o�l����(G2)(kN)"),_T("�o�l�ό`��(G2-G1)(m)"),_T("�����ቺ��")},
	//18
	{_T("�ߓ_�ԍ�"),_T("�sx(m)"),_T("�sy(m)"),_T("�sz(m)"),_T("�qx(rad)"),_T("�qy(rad)"),_T("�qz(rad)")},
	//19
	 {_T("�v�f�ԍ�")
,_T("����(G1)(kN)"),_T("����(G2)(kN)"),_T("����f��(G1)(kN)"),_T("����f��(G2)(kN)"),_T("�Ȃ����[�����g(G1)(kN.m)")
,_T("�Ȃ����[�����g(G2)(kN.m)"),_T("���ό`��(G2-G1)(m)"),_T("����f�p(G2-G1)(rad)"),_T("�ȗ�(/m)"),_T("�Ȃ����[�����g(kN.m)")
,_T("����f�����ቺ��"),_T("�Ȃ������ቺ��")},
	//20
	{_T("�v�f�ԍ�"),_T("����(G1)(kN)"),_T("����(G2)(kN)"),_T("����f��Y(G1)(kN)"),_T("����f��Z(G1)(kN)")
,_T("����f��Y(G2)(kN)"),_T("����f��Z(G2)(kN)"),_T("�˂��胂�[�����g(G1)(kN.m)"),_T("�˂��胂�[�����g(G2)(kN.m)")
,_T("�Ȃ����[�����gY(G1)(kN.m)"),_T("�Ȃ����[�����gZ(G1)(kN.m)"),_T("�Ȃ����[�����gY(G2)(kN.m)"),_T("�Ȃ����[�����gZ(G2)(kN.m)")
,_T("���ό`��(G2-G1)(m)"),_T("����f�pY(G2-G1)(rad)"),_T("�ȗ�Z(/m)"),_T("�Ȃ����[�����gZ(kN.m)"),_T("����f�����ቺ��")
,_T("�Ȃ������ቺ��")},
	//21
	{_T("�v�f�ԍ�"),_T("����(G1)(kN)"),_T("����(G2)(kN)"),_T("����f��(G1)(kN)"),_T("����f��(G2)(kN)"),
_T("�Ȃ����[�����g(G1)(kN.m)"),_T("�Ȃ����[�����g(G2)(kN.m)"),_T("���ό`��(G2-G1)(m)"),_T("����f�p(G2-G1)(rad)"),
_T("�ȗ�(G2-G1)(/m)"),_T("�Ȃ����[�����g(����)(kN.m)"),_T("�Ȃ������ቺ��"),_T("(�t�@�C�o�[�ԍ�)"),_T("�Ђ���")
,_T("����"),_T("����")},
	//22
	{_T("�v�f�ԍ�"),_T("����(G1)(kN)"),_T("����(G2)(kN)"),_T("����f��Y(G1)(kN)"),_T("����f��Z(G1)(kN)")
,_T("����f��Y(G2)(kN)"),_T("����f��Z(G2)(kN)"),_T("�˂��胂�[�����g(G1)(kN.m)"),_T("�˂��胂�[�����g(G2)(kN.m)")
,_T("�Ȃ����[�����gY(G1)(kN.m)"),_T("�Ȃ����[�����gZ(G1)(kN.m)"),_T("�Ȃ����[�����gY(G2)(kN.m)"),_T("�Ȃ����[�����gZ(G2)(kN.m)")
,_T("���ό`��(G2-G1)(m)"),_T("����f�pY(G2-G1)(rad)"),_T("����f�pZ(G2-G1)(rad)"),_T("�ȗ�Y(G2-G1)(/m)")
,_T("�ȗ�Z(G2-G1)(/m)"),_T("�Ȃ����[�����gY.����(kN.m)"),_T("�Ȃ����[�����gZ.����(kN.m)"),_T("�Ȃ�����Y�ቺ��")
,_T("�Ȃ�����Z�ቺ��"),_T("(�t�@�C�o�[�ԍ�)"),_T("�Ђ���"),_T("����"),_T("����")},
	//23
	{_T("�v�f�ԍ�"),_T("����(G1)(kN)"),_T("����(G2)(kN)"),_T("���ό`��(m)"),_T("�����ቺ��")},
	//24
	{_T("�v�f�ԍ�"),_T("�o�l����(G2)"),_T("�o�l�ό`��(G2-G1)"),_T("�����ቺ��")},
	//25
	{_T("�v�f�ԍ�"),_T("�o�l����(G2)(kN)"),_T("�o�l�ό`��(G2-G1)(m)"),_T("�����ቺ��")},
	//26
	{_T("�v�f�ԍ�"),_T("�o�l����(G2)(kN)"),_T("�o�l�ό`��(G2-G1)(m)"),_T("�����ቺ��")},
	//27
	{_T("�ߓ_�ԍ�"),_T("�sx(m)"),_T("�sy(m)"),_T("�sz(m)"),_T("�qx(rad)"),_T("�qy(rad)"),_T("�qz(rad)")}
};

static int strtblNum[CURTABLENUM];//ÿ����ֱ��ж��ٸ�items

/*******************************************************************
Name:	InitTables
Input:	
Function:	��ʼ�����б��ͷ
*******************************************************************/
void GetTable::InitTables(void)
{
	int i,j;
	//����col
	for(i=0; i<CURTABLENUM; i++)
	{
		strtblNum[i] = 0;
		for(j=0; j<MAXITEMS; j++)
		{
			if(strcmp("",strtbl[i][j]) != 0)
				strtblNum[i]++;
		}
		tables[i].col = strtblNum[i];
	}
	//��ʼ��header
	strcat(tables[0].header,"����`�Q�����͂�v�f          �׏d�X�e�b�v =");
	strcat(tables[1].header,"����`�R�����͂�v�f          �׏d�X�e�b�v =");
	strcat(tables[2].header,"�Q�����t�@�C�o�[�v�f          �׏d�X�e�b�v =");
	strcat(tables[3].header,"�R�����t�@�C�o�[�v�f          �׏d�X�e�b�v =");
	strcat(tables[4].header,"�g���X�v�f                    �׏d�X�e�b�v =");
	strcat(tables[5].header,"�o�l�v�f                      �׏d�X�e�b�v =");
	strcat(tables[6].header,"�w�������i�o�l�v�f            �׏d�X�e�b�v =");
	strcat(tables[7].header,"�w������]�o�l�v�f            �׏d�X�e�b�v =");
	strcat(tables[8].header,"�ψ�       �׏d�X�e�b�v =");
	//another nine tables
	strcat(tables[9].header,"����`�Q�����͂�v�f          �ő剞���l   \n                               �ŏ������l   \n ========================================   ");
	strcat(tables[10].header,"����`�R�����͂�v�f          �ő剞���l   \n                               �ŏ������l   \n ========================================   ");
	strcat(tables[11].header,"�Q�����t�@�C�o�[�v�f          �ő剞���l   \n                               �ŏ������l   \n ========================================   ");
	strcat(tables[12].header,"�R�����t�@�C�o�[�v�f          �ő剞���l   \n                               �ŏ������l   \n ========================================   ");
	strcat(tables[13].header,"�g���X�v�f                    �ő剞���l   \n                               �ŏ������l   \n ========================================   ");
	strcat(tables[14].header,"�o�l�v�f                      �ő剞���l   \n                               �ŏ������l   \n ========================================   ");
	strcat(tables[15].header,"�w�������i�o�l�v�f            �ő剞���l   \n                               �ŏ������l   \n ========================================   ");
	strcat(tables[16].header,"�w������]�o�l�v�f            �ő剞���l   \n                               �ŏ������l   \n ========================================   ");
	strcat(tables[17].header,"�����ψ�       �ő剞���l   \n                �ŏ������l   \n =========================   ");
	//another nine tables
	strcat(tables[18].header,"����`�Q�����͂�v�f          �ő剞���l        \n ========================================");
	strcat(tables[19].header,"����`�R�����͂�v�f          �ő剞���l        \n ========================================");
	strcat(tables[20].header,"�Q�����t�@�C�o�[�v�f          �ő剞���l        \n ========================================");
	strcat(tables[21].header,"�R�����t�@�C�o�[�v�f          �ő剞���l        \n ========================================");
	strcat(tables[22].header,"�g���X�v�f                    �ő剞���l        \n ========================================");
	strcat(tables[23].header,"�o�l�v�f                      �ő剞���l        \n ========================================");
	strcat(tables[24].header,"�w�������i�o�l�v�f            �ő剞���l        \n ========================================");
	strcat(tables[25].header,"�w������]�o�l�v�f            �ő剞���l        \n ========================================");
	strcat(tables[26].header,"�ő剞���ψ�                             \n ============");
	//��ʼ��headlines
	for(i=0; i<CURTABLENUM; i++)
	{
		tables[i].headlines = 1;//��ͷռ1��
	}
	//��ʼ��items[]
	for(i=0; i<CURTABLENUM; i++)
	{
		for(j=0; j<tables[i].col; j++)
			strcpy(tables[i].items[j].s,strtbl[i][j]);
	}
	//��ʼ��linemark
	tables[0].linemark = 7;
	tables[1].linemark = 7;
	tables[2].linemark = 7;
	tables[3].linemark = 7;
	tables[4].linemark = 5;
	tables[5].linemark = 4;
	tables[6].linemark = 4;
	tables[7].linemark = 4;
	tables[8].linemark = 7;

	tables[9].linemark = 13;
	tables[10].linemark = 13;
	tables[11].linemark = 13;
	tables[12].linemark = 13;
	tables[13].linemark = 8;
	tables[14].linemark = 6;
	tables[15].linemark = 6;
	tables[16].linemark = 6;
	tables[17].linemark = 10;

	tables[18].linemark = 13;
	tables[19].linemark = 13;
	tables[20].linemark = 13;
	tables[21].linemark = 13;
	tables[22].linemark = 8;
	tables[23].linemark = 6;
	tables[24].linemark = 6;
	tables[25].linemark = 6;
	tables[26].linemark = 10;
	//��ʼ��twin
	tables[2].twin = true;
	tables[3].twin = true;
	tables[11].twin = true;
	tables[12].twin = true;
	tables[20].twin = true;
	tables[21].twin = true;
	/*for(int i=0; i<18; i++)
	{
		printf("%s\n",tables[i].header);
	}*/
}

/*******************************************************************
Name:	Init
Input:	
Function:	��ʼ�����б������
*******************************************************************/
void GetTable::Init(void)
{
	fin = NULL;
	fmaxmin =NULL;
	fmax = NULL;
	fespecial = NULL;
	strcpy(tmpstr,"");
	ptable = (char*)malloc(sizeof(char)*100*1024*1024);
	InitTables();//��ʼ�����б������
}

void GetTable::GetAllTable(void)
{
	int i;
	for(i=0; i<9; i++)
		GetType1Table(i);
	printf("=========================================================\n");
	for(i=9; i<18; i++)
		GetType2Table(i);
	printf("=========================================================\n");
	for(i=18; i<27; i++)
		GetType3Table(i);
}

void GetTable::GetType1Table(int tblidx)
{
	PostInit(tblidx);
	T1_FillDate(tblidx);
}

void GetTable::GetType2Table(int tblidx)
{
	PostInit(tblidx,true);
	T2_FillDate(tblidx);
}

void GetTable::GetType3Table(int tblidx)
{
	PostInit(tblidx,true);
	T3_FillDate(tblidx);
}

void GetTable::PostInit(int tblidx,bool dblcol)
{
	if(NULL == ptable)
	{
		return;
	}
	int i,j;
	if(dblcol)
	{
		tables[tblidx].col *= 2;
	}
	//����skipwords
	char prestr[1000],pstr[1000]={""};
	int skip=0;
	char *p= strstr(ptable,tables[tblidx].header);
	GapN(p,1);
	do
	{
		strcpy(prestr,pstr);
		GetFirstStr(p,tmpstr,SINGLSTRLEN);
		strcpy(pstr,tmpstr);
		DeleteChar(tmpstr,'(');
		DeleteChar(tmpstr,')');
		if(IsNumberStr(tmpstr))
		{//��ǰһ����'('����ǰһ�������ͷ����
			if(strcmp(prestr,"(")==0)
				skip--;
			break;
		}
		skip++;
	}while(1);
	tables[tblidx].skipwords = skip;
	//����row
	tables[tblidx].row = CountDateLines(ptable,tables[tblidx].header,tables[tblidx].skipwords,tables[tblidx].linemark);
	tables[tblidx].row = tables[tblidx].row + 1;//��һ�зű�ͷ
	printf("col = %d, row = %d\n",tables[tblidx].col,tables[tblidx].row);
	//����ռ�ptbl
	tables[tblidx].ptbl= (Cell**)malloc(sizeof(Cell*)*tables[tblidx].row);
	for(i=0; i<tables[tblidx].row; i++)
	{
		tables[tblidx].ptbl[i] = (Cell*)malloc(sizeof(Cell)*tables[tblidx].col);
	}
	for(i=0; i<tables[tblidx].row; i++)
	{
		for(j=0; j<tables[tblidx].col; j++)
		{
			tables[tblidx].ptbl[i][j].s[0] = '\0';
		}
	}
}
//ok
void GetTable::T3_FillDate(int tblidx)
{
	int i,j,row,col;
	char *p, *pend;

	col = tables[tblidx].col;
	if(tables[tblidx].twin)
	{//������˫���ݶ�����
		col = col -8;
	}
	p = ptable;
	row = 1;
	do
	{//ÿ�δ���һ����
		p = strstr(p,tables[tblidx].header);
		if(NULL == p)
			return;
		GapN(p,1);
		for(i=0; i<tables[tblidx].skipwords; i++)
		{//���˱�ͷskip������
			GetFirstStr(p,tmpstr,SINGLSTRLEN);
		}
		do
		{//ÿ�δ���һ��
			pend = p;
			FilterNull(pend,true);
			if(strcmp(pend,"")==0)
			{//�ж��ļ��Ƿ�����
				return;
			}
			if(GetFirstStr(pend,tmpstr,SINGLSTRLEN)<0)
				break;//����Ƿ�ý���������3�����ʣ�����һ���Ƿ�ASIC�������˳�
			if(GetFirstStr(pend,tmpstr,SINGLSTRLEN)<0)
				break;
			if(GetFirstStr(pend,tmpstr,SINGLSTRLEN)<0)
				break;
			if(tables[tblidx].twin)
			{//������˫���ݶ�����
				pend = p;
				GetFirstStr(pend,tmpstr,SINGLSTRLEN);
				if(strcmp(tmpstr,"(")==0)
				{
					FilterNull(p,true);
					GapN(p,1);//����ǰ�е�һ��word��(����������һ��
					continue;
				}
			}
			GetFirstStr(p,tmpstr,SINGLSTRLEN);
			strcpy(tables[tblidx].ptbl[row][0].s,tmpstr);
			j = 1;
			do
			{//ÿ��ѭ������һ���е�һ��
				GetFirstStr(p,tmpstr,SINGLSTRLEN);
				strcpy(tables[tblidx].ptbl[row][j].s,tmpstr);
				if(strcmp(tmpstr,"---")!=0)
				{
					GetFirstStr(p,tmpstr,SINGLSTRLEN);
				}
				j++;
			}while(j<col/2);
			row ++;
		}while(1);
	}while(1);
}
//ok
void GetTable::T2_FillDate(int tblidx)
{
	int i,j,row,col;
	char *p, *pend, *pnext;

	col = tables[tblidx].col;
	if(tables[tblidx].twin)
	{//������˫���ݶ�����
		col = col -8;
	}
	p = ptable;
	row = 1;
	do
	{//ÿ�δ���һ����
		p = strstr(p,tables[tblidx].header);
		if(NULL == p)
			return;
		GapN(p,1);
		for(i=0; i<tables[tblidx].skipwords; i++)
		{//���˱�ͷskip������
			GetFirstStr(p,tmpstr,SINGLSTRLEN);
		}
		do
		{//ÿ�δ���һ��
			pend = p;
			if(GetFirstStr(pend,tmpstr,SINGLSTRLEN)<0)
				break;//����Ƿ�ý���������3�����ʣ�����һ���Ƿ�ASIC�������˳�
			if(GetFirstStr(pend,tmpstr,SINGLSTRLEN)<0)
				break;
			if(GetFirstStr(pend,tmpstr,SINGLSTRLEN)<0)
				break;
			if(tables[tblidx].twin)
			{//������˫���ݶ�����
				pend = p;
				GetFirstStr(pend,tmpstr,SINGLSTRLEN);
				if(strcmp(tmpstr,"(")==0)
				{
					FilterNull(p,true);
					GapN(p,2);//����ǰ�е�һ��word��(����������һ��
					continue;
				}
			}
			GetFirstStr(p,tmpstr,SINGLSTRLEN);
			strcpy(tables[tblidx].ptbl[row][0].s,tmpstr);
			j = 1;
			pnext = p;
			GapN(pnext,1);
			do
			{//ÿ��ѭ������һ���е�һ��
				GetFirstStr(p,tmpstr,SINGLSTRLEN);
				strcpy(tables[tblidx].ptbl[row][j].s,tmpstr);
				if(strcmp(tmpstr,"---")!=0)
				{
					GetFirstStr(p,tmpstr,SINGLSTRLEN);
				}
				for(i=0; i<50; i++)
				{
					if(*(p+i)>32)
					{
						break;
					}
					if(*(p+i)=='\n')
					{
						GapN(p,2);
						break;
					}
				}
				GetFirstStr(pnext,tmpstr,SINGLSTRLEN);
				strcpy(tables[tblidx].ptbl[row][j+col/2].s,tmpstr);
				if(strcmp(tmpstr,"---")!=0)
				{
					GetFirstStr(pnext,tmpstr,SINGLSTRLEN);
				}
				for(i=0; i<50; i++)
				{
					if(*(pnext+i)>32)
					{
						break;
					}
					if(*(pnext+i)=='\n')
					{
						GapN(pnext,2);
						break;
					}
				}
				j++;
			}while(j<col/2);
			row ++;
		}while(1);
	}while(1);
}
//ok
void GetTable::T1_FillDate(int tblidx)
{
	int i,j,row,col;
	char *p, *pend;

	col = tables[tblidx].col;
	if(tables[tblidx].twin)
	{//������˫���ݶ�����
		col = col -4;
	}
	p = ptable;
	row = 1;
	do
	{
		p = strstr(p,tables[tblidx].header);
		if(NULL == p)
			return;
		GapN(p,1);
		for(i=0; i<tables[tblidx].skipwords; i++)
		{//���˱�ͷskip������
			GetFirstStr(p,tmpstr,SINGLSTRLEN);
		}
		do
		{
			pend = p;
			if(GetFirstStr(pend,tmpstr,SINGLSTRLEN)<0)
				break;//����Ƿ�ý���������3�����ʣ�����һ���Ƿ�ASIC�������˳�
			if(GetFirstStr(pend,tmpstr,SINGLSTRLEN)<0)
				break;
			if(GetFirstStr(pend,tmpstr,SINGLSTRLEN)<0)
				break;
			if(tables[tblidx].twin)
			{//������˫���ݶ�����
				pend = p;
				GetFirstStr(pend,tmpstr,SINGLSTRLEN);
				if(strcmp(tmpstr,"(")==0)
				{
					GapN(p,1);//����ǰ�е�һ��word��(����������һ��
					continue;
				}
			}
			j = 0;
			do
			{
				GetFirstStr(p,tmpstr,SINGLSTRLEN);
				strcpy(tables[tblidx].ptbl[row][j].s,tmpstr);
				j++;
			}while(j<col);
			row ++;
		}while(1);
	}while(1);
}

void GetTable::PrintTable(int tblidx, FILE *fout)
{
	int i,j;
	for(i=0; i<tables[tblidx].col; i++)
	{
		fprintf(fout,"%-20s,",tables[tblidx].items[i].s);
	}
	for(i =0; i<tables[tblidx].row; i++)
	{
		for(j=0; j<tables[tblidx].col; j++)
		{
			fprintf(fout,"%-20s,",tables[tblidx].ptbl[i][j].s);
		}
		fprintf(fout,"\n");
	}
}


int GetTable::Read(char *pname)
{
	fin = fopen(pname, "r");
	if(NULL == fin)
	{
		//MessageBoxA(NULL,"Inputfile not found !",pname,MB_OK);
		return 1;
	}
	//�������ļ�����һά����
	int c, i=0;
	while(EOF != (c=fgetc(fin)))
	{
		if(i>=100*1024*1024)
		{
			printf("�ļ�����100M�����ܴ���\n");
			return 1;
		}
		ptable[i++]=c;
	}
	ptable[i] = '\0';

	GetAllTable();
	return 0;
}

int GetTable::Write(char *pmaxmin, char *pmax, char *especial)
{
	fespecial	= fopen(especial, "w");
	fmaxmin		= fopen(pmaxmin, "w");
	fmax		= fopen(pmax, "w");
	int i;
	for(i=0; i<9; i++)
		PrintTable(i,fespecial);
	for(i=9; i<18; i++)
		PrintTable(i,fmaxmin);
	for(i=18; i<27; i++)
		PrintTable(i,fmax);
	return 0;
}
