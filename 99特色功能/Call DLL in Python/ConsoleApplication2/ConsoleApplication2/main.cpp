/***********************************************************
main.cpp: Testing warning manager in win32 console
***********************************************************/


/***********************************************************
Include Header
***********************************************************/
#include "MyTimer.hpp"
#include "warninglist.hpp"
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

void OnWarningStackChanged(uint16 u16StackSize);
void OnWarningChanged(uint16 u16ActiveWrnID);
void OnTelltaleChanged(uint16 u16ActiveTelltaleID);


/***********************************************************
Global variant
***********************************************************/
WarningStrategy *poWrnStrategy;
TelltaleStrategy *poTTStrategy;
cMyTimer *poMyTimer;

/***********************************************************
Function define
***********************************************************/

void init(void)
{
	poWrnStrategy = new WarningStrategy();
	if (NULL == poWrnStrategy)
	{
		printf("unable to satisfy request for memory\n");
	}
	poTTStrategy = new TelltaleStrategy();
	if (NULL == poTTStrategy)
	{
		printf("unable to satisfy request for memory\n");
	}
	poMyTimer = new cMyTimer(poWrnStrategy, poTTStrategy);
	poMyTimer->CreateTimer(100);
	poMyTimer->SetWarningStackCallback(OnWarningStackChanged);
	poMyTimer->SetWarningCallback(OnWarningChanged);
	poMyTimer->SetTelltaleCallback(OnTelltaleChanged);
}

void deInit(void)
{
	if (NULL != poWrnStrategy)
	{
		delete poWrnStrategy;
		poWrnStrategy = NULL;
	}
	if (NULL != poTTStrategy)
	{
		delete poTTStrategy;
		poTTStrategy = NULL;
	}
	if (NULL != poMyTimer)
	{
		delete poMyTimer;
		poMyTimer = NULL;
	}
}

void RequestWarning(int id)
{
	poWrnStrategy->RequestWarning((enum WarningIDs)id);
}

void ReleaseWarning(int id)
{
	poWrnStrategy->ReleaseWarning((enum WarningIDs)id);
}

void SetWarningMode(int id)
{
	poWrnStrategy->SetWarningMode((enum WarningMode)id);
}

uint16 GetWarningIDFromStack(int id)
{
	return (uint16)poWrnStrategy->poWarningList->GetWarningFromStack((uint16)id);
}

void ProcessVirtualKey(int key)
{
	poWrnStrategy->ProcessVirtualKey((enum VirtualKey)key);
}

void OnWarningStackChanged(uint16 u16StackSize)
{
	printf("OnWarningStackChanged u16StackSize = %u \n", u16StackSize);

}
void OnWarningChanged(uint16 u16ActiveWrnID)
{
	printf("OnWarningChanged u16ActiveWrnID = %u \n", u16ActiveWrnID);
	if (u16ActiveWrnID == 246)
	{
		printf("Invalid WarningID\n");
	}
}


void RequestTelltale(int id)
{
	poTTStrategy->RequestWarning((enum TelltaleIDs)id);
}

void ReleaseTelltale(int id)
{
	poTTStrategy->ReleaseWarning((enum TelltaleIDs)id);
}

void OnTelltaleChanged(uint16 u16ActiveTelltaleID)
{
	printf("OnTelltaleChanged u16ActiveTelltaleID = %u \n", u16ActiveTelltaleID);
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
	Sleep(400);
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
	while (GetWarningIDFromStack(i) != 246)
	{
		printf("WarningItem = %u\n", GetWarningIDFromStack(i));
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

	//verify_warningmode();

	printf("\nOver!\n");

	//deInit();

	while (true)
	{
		;
	}
}

