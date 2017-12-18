#include "gettable.h"
#include "global.h"
#include <tchar.h>

/***************************************************************************
全局变量。1--9表
旕慄宍俀師尦偼傝梫慺          壸廳僗僥僢僾 =      3001
旕慄宍俁師尦偼傝梫慺          壸廳僗僥僢僾 =       101
俀師尦僼傽僀僶乕梫慺          壸廳僗僥僢僾 =       100
俁師尦僼傽僀僶乕梫慺          壸廳僗僥僢僾 =       101
僩儔僗梫慺                    壸廳僗僥僢僾 =       101
僶僱梫慺                      壸廳僗僥僢僾 =      3001
巜岦惈暲恑僶僱梫慺            壸廳僗僥僢僾 =       101
巜岦惈夞揮僶僱梫慺            壸廳僗僥僢僾 =       101
曄埵       壸廳僗僥僢僾 =      3001
***************************************************************************/

static char strtbl[CURTABLENUM][MAXITEMS][50] =
{
	//1
	{_T("梫慺斣崋"),_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("偣傫抐椡(G1)(kN)"),_T("偣傫抐椡(G2)(kN)"),
_T("嬋偘儌乕儊儞僩(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩(G2)(kN.m)"),_T("幉曄宍検(G2-G1)(m)"),_T("偣傫抐妏(G2-G1)(rad)"),
_T("嬋棪(/m)"),_T("嬋偘儌乕儊儞僩(kN.m)"),_T("偣傫抐崉惈掅壓棪"),_T("嬋偘崉惈掅壓棪")},
	//2
	{_T("梫慺斣崋"),_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("偣傫抐椡Y(G1)(kN)"),_T("偣傫抐椡Z(G1)(kN)")
,_T("偣傫抐椡Y(G2)(kN)"),_T("偣傫抐椡Z(G2)(kN)"),_T("偹偠傝儌乕儊儞僩(G1)(kN.m)"),_T("偹偠傝儌乕儊儞僩(G2)(kN.m)")
,_T("嬋偘儌乕儊儞僩Y(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩Z(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩Y(G2)(kN.m)"),_T("嬋偘儌乕儊儞僩Z(G2)(kN.m)")
,_T("幉曄宍検(G2-G1)(m)"),_T("偣傫抐妏Y(G2-G1)(rad)"),_T("嬋棪Z(/m)"),_T("嬋偘儌乕儊儞僩Z(kN.m)"),_T("偣傫抐崉惈掅壓棪")
,_T("嬋偘崉惈掅壓棪")},
	//3
	{_T("梫慺斣崋"),_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("偣傫抐椡(G1)(kN)"),_T("偣傫抐椡(G2)(kN)"),
_T("嬋偘儌乕儊儞僩(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩(G2)(kN.m)"),_T("幉曄宍検(G2-G1)(m)"),_T("偣傫抐妏(G2-G1)(rad)"),
_T("嬋棪(G2-G1)(/m)"),_T("嬋偘儌乕儊儞僩(拞墰)(kN.m)"),_T("嬋偘崉惈掅壓棪"),_T("(僼傽僀僶乕斣崋)"),_T("傂偢傒")
,_T("墳椡"),_T("崉惈")},
	//4
	{_T("梫慺斣崋"),_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("偣傫抐椡Y(G1)(kN)"),_T("偣傫抐椡Z(G1)(kN)")
,_T("偣傫抐椡Y(G2)(kN)"),_T("偣傫抐椡Z(G2)(kN)"),_T("偹偠傝儌乕儊儞僩(G1)(kN.m)"),_T("偹偠傝儌乕儊儞僩(G2)(kN.m)")
,_T("嬋偘儌乕儊儞僩Y(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩Z(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩Y(G2)(kN.m)"),_T("嬋偘儌乕儊儞僩Z(G2)(kN.m)")
,_T("幉曄宍検(G2-G1)(m)"),_T("偣傫抐妏Y(G2-G1)(rad)"),_T("偣傫抐妏Z(G2-G1)(rad)"),_T("嬋棪Y(G2-G1)(/m)")
,_T("嬋棪Z(G2-G1)(/m)"),_T("嬋偘儌乕儊儞僩Y.拞墰(kN.m)"),_T("嬋偘儌乕儊儞僩Z.拞墰(kN.m)"),_T("嬋偘崉惈Y掅壓棪")
,_T("嬋偘崉惈Z掅壓棪"),_T("(僼傽僀僶乕斣崋)"),_T("傂偢傒"),_T("墳椡"),_T("崉惈")},
	//5
	{_T("梫慺斣崋"),_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("幉曄宍検(m)"),_T("崉惈掅壓棪")},
	//6
	{_T("梫慺斣崋"),_T("僶僱斀椡(G2)"),_T("僶僱曄宍検(G2-G1)"),_T("崉惈掅壓棪")},
	//7
	{_T("梫慺斣崋"),_T("僶僱斀椡(G2)(kN)"),_T("僶僱曄宍検(G2-G1)(m)"),_T("崉惈掅壓棪")},
	//8
	{_T("梫慺斣崋"),_T("僶僱斀椡(G2)(kN)"),_T("僶僱曄宍検(G2-G1)(m)"),_T("崉惈掅壓棪")},
	//9
	{_T("愡揰斣崋"),_T("俿x(m)"),_T("俿y(m)"),_T("俿z(m)"),_T("俼x(rad)"),_T("俼y(rad)"),_T("俼z(rad)")},
	//10
	 {_T("梫慺斣崋")
,_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("偣傫抐椡(G1)(kN)"),_T("偣傫抐椡(G2)(kN)"),_T("嬋偘儌乕儊儞僩(G1)(kN.m)")
,_T("嬋偘儌乕儊儞僩(G2)(kN.m)"),_T("墢墳椡+SY(G1)(kPa)"),_T("墢墳椡-SY(G1)(kPa)"),_T("墢墳椡+SY(G2)(kPa)")
,_T("墢墳椡-SY(G2)(kPa)"),_T("幉曄宍検(G2-G1)(m)"),_T("偣傫抐妏(G2-G1)(rad)"),_T("嬋棪(/m)"),_T("嬋偘儌乕儊儞僩(kN.m)")
,_T("偣傫抐崉惈掅壓棪"),_T("嬋偘崉惈掅壓棪")},
	//11
	{_T("梫慺斣崋"),_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("偣傫抐椡Y(G1)(kN)"),_T("偣傫抐椡Z(G1)(kN)")
,_T("偣傫抐椡Y(G2)(kN)"),_T("偣傫抐椡Z(G2)(kN)"),_T("偹偠傝儌乕儊儞僩(G1)(kN.m)"),_T("偹偠傝儌乕儊儞僩(G2)(kN.m)")
,_T("嬋偘儌乕儊儞僩Y(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩Z(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩Y(G2)(kN.m)"),_T("嬋偘儌乕儊儞僩Z(G2)(kN.m)")
,_T("幉曄宍検(G2-G1)(m)"),_T("偣傫抐妏Y(G2-G1)(rad)"),_T("嬋棪Z(/m)"),_T("嬋偘儌乕儊儞僩Z(kN.m)"),_T("偣傫抐崉惈掅壓棪")
,_T("嬋偘崉惈掅壓棪")},
	//12
	{_T("梫慺斣崋"),_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("偣傫抐椡(G1)(kN)"),_T("偣傫抐椡(G2)(kN)"),
_T("嬋偘儌乕儊儞僩(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩(G2)(kN.m)"),_T("幉曄宍検(G2-G1)(m)"),_T("偣傫抐妏(G2-G1)(rad)"),
_T("嬋棪(G2-G1)(/m)"),_T("嬋偘儌乕儊儞僩(拞墰)(kN.m)"),_T("嬋偘崉惈掅壓棪"),_T("(僼傽僀僶乕斣崋)"),_T("傂偢傒")
,_T("墳椡"),_T("崉惈")},
	//13
	{_T("梫慺斣崋"),_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("偣傫抐椡Y(G1)(kN)"),_T("偣傫抐椡Z(G1)(kN)")
,_T("偣傫抐椡Y(G2)(kN)"),_T("偣傫抐椡Z(G2)(kN)"),_T("偹偠傝儌乕儊儞僩(G1)(kN.m)"),_T("偹偠傝儌乕儊儞僩(G2)(kN.m)")
,_T("嬋偘儌乕儊儞僩Y(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩Z(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩Y(G2)(kN.m)"),_T("嬋偘儌乕儊儞僩Z(G2)(kN.m)")
,_T("幉曄宍検(G2-G1)(m)"),_T("偣傫抐妏Y(G2-G1)(rad)"),_T("偣傫抐妏Z(G2-G1)(rad)"),_T("嬋棪Y(G2-G1)(/m)")
,_T("嬋棪Z(G2-G1)(/m)"),_T("嬋偘儌乕儊儞僩Y.拞墰(kN.m)"),_T("嬋偘儌乕儊儞僩Z.拞墰(kN.m)"),_T("嬋偘崉惈Y掅壓棪")
,_T("嬋偘崉惈Z掅壓棪"),_T("(僼傽僀僶乕斣崋)"),_T("傂偢傒"),_T("墳椡"),_T("崉惈")},
	//14
	{_T("梫慺斣崋"),_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("幉曄宍検(m)"),_T("崉惈掅壓棪")},
	//15
	{_T("梫慺斣崋"),_T("僶僱斀椡(G2)"),_T("僶僱曄宍検(G2-G1)"),_T("崉惈掅壓棪")},
	//16
	{_T("梫慺斣崋"),_T("僶僱斀椡(G2)(kN)"),_T("僶僱曄宍検(G2-G1)(m)"),_T("崉惈掅壓棪")},
	//17
	{_T("梫慺斣崋"),_T("僶僱斀椡(G2)(kN)"),_T("僶僱曄宍検(G2-G1)(m)"),_T("崉惈掅壓棪")},
	//18
	{_T("愡揰斣崋"),_T("俿x(m)"),_T("俿y(m)"),_T("俿z(m)"),_T("俼x(rad)"),_T("俼y(rad)"),_T("俼z(rad)")},
	//19
	 {_T("梫慺斣崋")
,_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("偣傫抐椡(G1)(kN)"),_T("偣傫抐椡(G2)(kN)"),_T("嬋偘儌乕儊儞僩(G1)(kN.m)")
,_T("嬋偘儌乕儊儞僩(G2)(kN.m)"),_T("幉曄宍検(G2-G1)(m)"),_T("偣傫抐妏(G2-G1)(rad)"),_T("嬋棪(/m)"),_T("嬋偘儌乕儊儞僩(kN.m)")
,_T("偣傫抐崉惈掅壓棪"),_T("嬋偘崉惈掅壓棪")},
	//20
	{_T("梫慺斣崋"),_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("偣傫抐椡Y(G1)(kN)"),_T("偣傫抐椡Z(G1)(kN)")
,_T("偣傫抐椡Y(G2)(kN)"),_T("偣傫抐椡Z(G2)(kN)"),_T("偹偠傝儌乕儊儞僩(G1)(kN.m)"),_T("偹偠傝儌乕儊儞僩(G2)(kN.m)")
,_T("嬋偘儌乕儊儞僩Y(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩Z(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩Y(G2)(kN.m)"),_T("嬋偘儌乕儊儞僩Z(G2)(kN.m)")
,_T("幉曄宍検(G2-G1)(m)"),_T("偣傫抐妏Y(G2-G1)(rad)"),_T("嬋棪Z(/m)"),_T("嬋偘儌乕儊儞僩Z(kN.m)"),_T("偣傫抐崉惈掅壓棪")
,_T("嬋偘崉惈掅壓棪")},
	//21
	{_T("梫慺斣崋"),_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("偣傫抐椡(G1)(kN)"),_T("偣傫抐椡(G2)(kN)"),
_T("嬋偘儌乕儊儞僩(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩(G2)(kN.m)"),_T("幉曄宍検(G2-G1)(m)"),_T("偣傫抐妏(G2-G1)(rad)"),
_T("嬋棪(G2-G1)(/m)"),_T("嬋偘儌乕儊儞僩(拞墰)(kN.m)"),_T("嬋偘崉惈掅壓棪"),_T("(僼傽僀僶乕斣崋)"),_T("傂偢傒")
,_T("墳椡"),_T("崉惈")},
	//22
	{_T("梫慺斣崋"),_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("偣傫抐椡Y(G1)(kN)"),_T("偣傫抐椡Z(G1)(kN)")
,_T("偣傫抐椡Y(G2)(kN)"),_T("偣傫抐椡Z(G2)(kN)"),_T("偹偠傝儌乕儊儞僩(G1)(kN.m)"),_T("偹偠傝儌乕儊儞僩(G2)(kN.m)")
,_T("嬋偘儌乕儊儞僩Y(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩Z(G1)(kN.m)"),_T("嬋偘儌乕儊儞僩Y(G2)(kN.m)"),_T("嬋偘儌乕儊儞僩Z(G2)(kN.m)")
,_T("幉曄宍検(G2-G1)(m)"),_T("偣傫抐妏Y(G2-G1)(rad)"),_T("偣傫抐妏Z(G2-G1)(rad)"),_T("嬋棪Y(G2-G1)(/m)")
,_T("嬋棪Z(G2-G1)(/m)"),_T("嬋偘儌乕儊儞僩Y.拞墰(kN.m)"),_T("嬋偘儌乕儊儞僩Z.拞墰(kN.m)"),_T("嬋偘崉惈Y掅壓棪")
,_T("嬋偘崉惈Z掅壓棪"),_T("(僼傽僀僶乕斣崋)"),_T("傂偢傒"),_T("墳椡"),_T("崉惈")},
	//23
	{_T("梫慺斣崋"),_T("幉椡(G1)(kN)"),_T("幉椡(G2)(kN)"),_T("幉曄宍検(m)"),_T("崉惈掅壓棪")},
	//24
	{_T("梫慺斣崋"),_T("僶僱斀椡(G2)"),_T("僶僱曄宍検(G2-G1)"),_T("崉惈掅壓棪")},
	//25
	{_T("梫慺斣崋"),_T("僶僱斀椡(G2)(kN)"),_T("僶僱曄宍検(G2-G1)(m)"),_T("崉惈掅壓棪")},
	//26
	{_T("梫慺斣崋"),_T("僶僱斀椡(G2)(kN)"),_T("僶僱曄宍検(G2-G1)(m)"),_T("崉惈掅壓棪")},
	//27
	{_T("愡揰斣崋"),_T("俿x(m)"),_T("俿y(m)"),_T("俿z(m)"),_T("俼x(rad)"),_T("俼y(rad)"),_T("俼z(rad)")}
};

static int strtblNum[CURTABLENUM];//每个表分别有多少个items

/*******************************************************************
Name:	InitTables
Input:	
Function:	初始化所有表表头
*******************************************************************/
void GetTable::InitTables(void)
{
	int i,j;
	//计算col
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
	//初始化header
	strcat(tables[0].header,"旕慄宍俀師尦偼傝梫慺          壸廳僗僥僢僾 =");
	strcat(tables[1].header,"旕慄宍俁師尦偼傝梫慺          壸廳僗僥僢僾 =");
	strcat(tables[2].header,"俀師尦僼傽僀僶乕梫慺          壸廳僗僥僢僾 =");
	strcat(tables[3].header,"俁師尦僼傽僀僶乕梫慺          壸廳僗僥僢僾 =");
	strcat(tables[4].header,"僩儔僗梫慺                    壸廳僗僥僢僾 =");
	strcat(tables[5].header,"僶僱梫慺                      壸廳僗僥僢僾 =");
	strcat(tables[6].header,"巜岦惈暲恑僶僱梫慺            壸廳僗僥僢僾 =");
	strcat(tables[7].header,"巜岦惈夞揮僶僱梫慺            壸廳僗僥僢僾 =");
	strcat(tables[8].header,"曄埵       壸廳僗僥僢僾 =");
	//another nine tables
	strcat(tables[9].header,"旕慄宍俀師尦偼傝梫慺          嵟戝墳摎抣   \n                               嵟彫墳摎抣   \n ========================================   ");
	strcat(tables[10].header,"旕慄宍俁師尦偼傝梫慺          嵟戝墳摎抣   \n                               嵟彫墳摎抣   \n ========================================   ");
	strcat(tables[11].header,"俀師尦僼傽僀僶乕梫慺          嵟戝墳摎抣   \n                               嵟彫墳摎抣   \n ========================================   ");
	strcat(tables[12].header,"俁師尦僼傽僀僶乕梫慺          嵟戝墳摎抣   \n                               嵟彫墳摎抣   \n ========================================   ");
	strcat(tables[13].header,"僩儔僗梫慺                    嵟戝墳摎抣   \n                               嵟彫墳摎抣   \n ========================================   ");
	strcat(tables[14].header,"僶僱梫慺                      嵟戝墳摎抣   \n                               嵟彫墳摎抣   \n ========================================   ");
	strcat(tables[15].header,"巜岦惈暲恑僶僱梫慺            嵟戝墳摎抣   \n                               嵟彫墳摎抣   \n ========================================   ");
	strcat(tables[16].header,"巜岦惈夞揮僶僱梫慺            嵟戝墳摎抣   \n                               嵟彫墳摎抣   \n ========================================   ");
	strcat(tables[17].header,"墳摎曄埵       嵟戝墳摎抣   \n                嵟彫墳摎抣   \n =========================   ");
	//another nine tables
	strcat(tables[18].header,"旕慄宍俀師尦偼傝梫慺          嵟戝墳摎抣        \n ========================================");
	strcat(tables[19].header,"旕慄宍俁師尦偼傝梫慺          嵟戝墳摎抣        \n ========================================");
	strcat(tables[20].header,"俀師尦僼傽僀僶乕梫慺          嵟戝墳摎抣        \n ========================================");
	strcat(tables[21].header,"俁師尦僼傽僀僶乕梫慺          嵟戝墳摎抣        \n ========================================");
	strcat(tables[22].header,"僩儔僗梫慺                    嵟戝墳摎抣        \n ========================================");
	strcat(tables[23].header,"僶僱梫慺                      嵟戝墳摎抣        \n ========================================");
	strcat(tables[24].header,"巜岦惈暲恑僶僱梫慺            嵟戝墳摎抣        \n ========================================");
	strcat(tables[25].header,"巜岦惈夞揮僶僱梫慺            嵟戝墳摎抣        \n ========================================");
	strcat(tables[26].header,"嵟戝墳摎曄埵                             \n ============");
	//初始化headlines
	for(i=0; i<CURTABLENUM; i++)
	{
		tables[i].headlines = 1;//表头占1行
	}
	//初始化items[]
	for(i=0; i<CURTABLENUM; i++)
	{
		for(j=0; j<tables[i].col; j++)
			strcpy(tables[i].items[j].s,strtbl[i][j]);
	}
	//初始化linemark
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
	//初始化twin
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
Function:	初始化所有表的配置
*******************************************************************/
void GetTable::Init(void)
{
	fin = NULL;
	fmaxmin =NULL;
	fmax = NULL;
	fespecial = NULL;
	strcpy(tmpstr,"");
	ptable = (char*)malloc(sizeof(char)*100*1024*1024);
	InitTables();//初始化所有表的配置
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
	//计算skipwords
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
		{//如前一个是'('，则前一个不算表头部分
			if(strcmp(prestr,"(")==0)
				skip--;
			break;
		}
		skip++;
	}while(1);
	tables[tblidx].skipwords = skip;
	//计算row
	tables[tblidx].row = CountDateLines(ptable,tables[tblidx].header,tables[tblidx].skipwords,tables[tblidx].linemark);
	tables[tblidx].row = tables[tblidx].row + 1;//这一行放表头
	printf("col = %d, row = %d\n",tables[tblidx].col,tables[tblidx].row);
	//申请空间ptbl
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
	{//处理单表双数据段类型
		col = col -8;
	}
	p = ptable;
	row = 1;
	do
	{//每次处理一个表
		p = strstr(p,tables[tblidx].header);
		if(NULL == p)
			return;
		GapN(p,1);
		for(i=0; i<tables[tblidx].skipwords; i++)
		{//过滤表头skip个单词
			GetFirstStr(p,tmpstr,SINGLSTRLEN);
		}
		do
		{//每次处理一行
			pend = p;
			FilterNull(pend,true);
			if(strcmp(pend,"")==0)
			{//判断文件是否处理完
				return;
			}
			if(GetFirstStr(pend,tmpstr,SINGLSTRLEN)<0)
				break;//检测是否该结束，连续3个单词，若有一个是非ASIC串，则退出
			if(GetFirstStr(pend,tmpstr,SINGLSTRLEN)<0)
				break;
			if(GetFirstStr(pend,tmpstr,SINGLSTRLEN)<0)
				break;
			if(tables[tblidx].twin)
			{//处理单表双数据段类型
				pend = p;
				GetFirstStr(pend,tmpstr,SINGLSTRLEN);
				if(strcmp(tmpstr,"(")==0)
				{
					FilterNull(p,true);
					GapN(p,1);//若当前行第一个word是(，则跳过这一行
					continue;
				}
			}
			GetFirstStr(p,tmpstr,SINGLSTRLEN);
			strcpy(tables[tblidx].ptbl[row][0].s,tmpstr);
			j = 1;
			do
			{//每次循环处理一行中的一列
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
	{//处理单表双数据段类型
		col = col -8;
	}
	p = ptable;
	row = 1;
	do
	{//每次处理一个表
		p = strstr(p,tables[tblidx].header);
		if(NULL == p)
			return;
		GapN(p,1);
		for(i=0; i<tables[tblidx].skipwords; i++)
		{//过滤表头skip个单词
			GetFirstStr(p,tmpstr,SINGLSTRLEN);
		}
		do
		{//每次处理一行
			pend = p;
			if(GetFirstStr(pend,tmpstr,SINGLSTRLEN)<0)
				break;//检测是否该结束，连续3个单词，若有一个是非ASIC串，则退出
			if(GetFirstStr(pend,tmpstr,SINGLSTRLEN)<0)
				break;
			if(GetFirstStr(pend,tmpstr,SINGLSTRLEN)<0)
				break;
			if(tables[tblidx].twin)
			{//处理单表双数据段类型
				pend = p;
				GetFirstStr(pend,tmpstr,SINGLSTRLEN);
				if(strcmp(tmpstr,"(")==0)
				{
					FilterNull(p,true);
					GapN(p,2);//若当前行第一个word是(，则跳过这一行
					continue;
				}
			}
			GetFirstStr(p,tmpstr,SINGLSTRLEN);
			strcpy(tables[tblidx].ptbl[row][0].s,tmpstr);
			j = 1;
			pnext = p;
			GapN(pnext,1);
			do
			{//每次循环处理一行中的一列
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
	{//处理单表双数据段类型
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
		{//过滤表头skip个单词
			GetFirstStr(p,tmpstr,SINGLSTRLEN);
		}
		do
		{
			pend = p;
			if(GetFirstStr(pend,tmpstr,SINGLSTRLEN)<0)
				break;//检测是否该结束，连续3个单词，若有一个是非ASIC串，则退出
			if(GetFirstStr(pend,tmpstr,SINGLSTRLEN)<0)
				break;
			if(GetFirstStr(pend,tmpstr,SINGLSTRLEN)<0)
				break;
			if(tables[tblidx].twin)
			{//处理单表双数据段类型
				pend = p;
				GetFirstStr(pend,tmpstr,SINGLSTRLEN);
				if(strcmp(tmpstr,"(")==0)
				{
					GapN(p,1);//若当前行第一个word是(，则跳过这一行
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
	//将输入文件读入一维数组
	int c, i=0;
	while(EOF != (c=fgetc(fin)))
	{
		if(i>=100*1024*1024)
		{
			printf("文件超过100M，不能处理！\n");
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
