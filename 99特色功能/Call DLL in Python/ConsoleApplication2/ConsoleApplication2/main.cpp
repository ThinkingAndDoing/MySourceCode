/***********************************************************
main.cpp: Testing warning manager in win32 console
***********************************************************/


/***********************************************************
Include Header
***********************************************************/
#include "MyTimer.hpp"
#include "warningstrategy.hpp"
#include "telltale.hpp"
#include <windows.h>

/***********************************************************
Function declaration
***********************************************************/
void  init(void);
void  RequestWarning(int id);
void  ReleaseWarning(int id);
void  SetWarningMode(int id);
uint16  GetWarningIDFromStack(int id);
void  ProcessVirtualKey(int key);

void  RequestTelltale(int id);
void  ReleaseTelltale(int id);

void OnWarningChanged(uint16 u16ActiveWrnID);
void OnTelltaleChanged(uint16 u16ActiveTelltaleID);


/***********************************************************
Global variant
***********************************************************/
WarningStrategy oWrnStrategy;
TelltaleStrategy oTTStrategy;
cMyTimer myTimer(&oWrnStrategy, &oTTStrategy);


/***********************************************************
Function define
***********************************************************/

void init(void)
{
    myTimer.CreateTimer(100);
	myTimer.SetWarningCallback(OnWarningChanged);
	myTimer.SetTelltaleCallback(OnTelltaleChanged);
}

void RequestWarning(int id)
{
	oWrnStrategy.RequestWarning((enum WarningIDs)id);
}

void ReleaseWarning(int id)
{
	oWrnStrategy.ReleaseWarning((enum WarningIDs)id);
}

void SetWarningMode(int id)
{
	oWrnStrategy.SetWarningMode((enum WarningMode)id);
}

uint16 GetWarningIDFromStack(int id)
{
	return (uint16)oWrnStrategy.oWarningList.GetWarningFromStack((uint16)id); 
}

void ProcessVirtualKey(int key)
{
	oWrnStrategy.ProcessVirtualKey((enum VirtualKey)key);
}

void OnWarningChanged(uint16 u16ActiveWrnID)
{
	printf("OnWarningChanged u16ActiveWrnID = %d \n", u16ActiveWrnID);
}


void RequestTelltale(int id)
{
	oTTStrategy.RequestWarning((enum TelltaleIDs)id);
}

void ReleaseTelltale(int id)
{
	oTTStrategy.ReleaseWarning((enum TelltaleIDs)id);
}

void OnTelltaleChanged(uint16 u16ActiveTelltaleID)
{
	printf("OnTelltaleChanged u16ActiveTelltaleID = %d \n", u16ActiveTelltaleID);
}

void verify_immediate(void)
{
	RequestWarning(98);

	Sleep(500);

	RequestWarning(99);

	Sleep(500);

	RequestWarning(241);
}

void verify_userlocktime(void)
{
	RequestWarning(98);
	Sleep(500);
	ProcessVirtualKey(4);
	Sleep(1000);
	ProcessVirtualKey(4);
	Sleep(2000);
	ProcessVirtualKey(4);
	Sleep(1000);
	RequestWarning(98);
}

void verify_telltale(void)
{
	RequestTelltale(0);
	Sleep(500);
	RequestTelltale(1);
	Sleep(500);
	RequestTelltale(2);
	Sleep(500);
	ReleaseTelltale(1);
	Sleep(500);
	ReleaseTelltale(2);
	Sleep(500);
	ReleaseTelltale(0);
}

void print_warninglist(void)
{
	printf("++++++++++\n");
	int i = 0;
	while (GetWarningIDFromStack(i) != 245)
	{
		printf("WarningItem = %d\n", GetWarningIDFromStack(i));
		i = i + 1;
	}
	printf("---------\n");
}

void verify_warninglist(void)
{
	RequestWarning(98);
	Sleep(500);
	ProcessVirtualKey(4);
	Sleep(1000);
	ProcessVirtualKey(4);
	Sleep(2000);
	ProcessVirtualKey(4);
	print_warninglist();
	Sleep(1000);
	RequestWarning(192);
	Sleep(7000);
	print_warninglist();
}

void verify_warningmode(void)
{
	SetWarningMode(3);

	RequestWarning(98);

	Sleep(500);

	RequestWarning(99);

	Sleep(500);

	RequestWarning(241);

	SetWarningMode(4);

}

void main(void)
{
	init();

	verify_immediate();

	verify_userlocktime();

	verify_telltale();

	verify_warninglist();

	verify_warningmode();

	while (true)
	{
		;
	}
}

