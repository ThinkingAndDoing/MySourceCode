/***********************************************************
main.cpp: Testing warning manager in win32 console
***********************************************************/


/***********************************************************
Include Header
***********************************************************/

#include "MyTimer.hpp"
#include "warninglist.hpp"
#include "warningstrategycm1e.hpp"
#include "telltale.hpp"
#include "warningresourceids.hpp"
#include <windows.h>


/***********************************************************
Function declaration
***********************************************************/
void  init(void);
void  RequestWarning(int id);
void  ReleaseWarning(int id);
void  SetWarningMode(int id);
void  Suspension(void);
void  Resume(void);
uint16  GetWarningIDFromStack(int id);
void  ProcessVirtualKey(int key);

void  RequestTelltale(int id);
void  ReleaseTelltale(int id);

void print_warninglist(void);
void OnWarningStackChanged(uint16 u16StackSize);
void OnWarningChanged(uint16 u16ActiveWrnID);
void OnTelltaleChanged(uint16 u16ActiveTelltaleID);


/***********************************************************
Global variant
***********************************************************/
WarningStrategyCM1E *poWrnStrategy;
TelltaleStrategy *poTTStrategy;
cMyTimer *poMyTimer;

/***********************************************************
Function define
***********************************************************/

void init(void)
{
	poWrnStrategy = new WarningStrategyCM1E();
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
	if (NULL == poMyTimer)
	{
		printf("unable to satisfy request for memory\n");
	}
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

void SetAvailiable(int id)
{
	poWrnStrategy->SetAvailiable((enum Availiable)id);
}

uint16 GetWarningIDFromStack(int id)
{
	return (uint16)poWrnStrategy->m_poWarningList->GetWarningFromStack((uint16)id);
}

void Suspension(void)
{
	poWrnStrategy->Suspension();
}

void Resume(void)
{
	poWrnStrategy->Resume();
}

void ProcessVirtualKey(int key)
{
	poWrnStrategy->ProcessVirtualKey((enum VirtualKey)key);
}

void OnWarningStackChanged(uint16 u16StackSize)
{
	printf("OnWarningStackChanged u16StackSize = %u \n", u16StackSize);
	print_warninglist();
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
	poTTStrategy->RequestTelltale((enum WarningIDs)id);
}

void ReleaseTelltale(int id)
{
	poTTStrategy->ReleaseTelltale((enum WarningIDs)id);
}

void OnTelltaleChanged(uint16 u16ActiveTelltaleID)
{
	printf("OnTelltaleChanged u16ActiveTelltaleID = %u \n", u16ActiveTelltaleID);
}

void verify_immediate(void)
{
	printf("verify_immediate!\n");

	RequestWarning(98);

	Sleep(500);

	RequestWarning(99);

	Sleep(500);

	RequestWarning(241);

	Sleep(4000);
}

void verify_userlocktime(void)
{
	printf("verify_userlocktime!\n");

	RequestWarning(98);
	Sleep(500);
	ProcessVirtualKey(4);
	Sleep(1000);
	ProcessVirtualKey(4);
	Sleep(2000);
	ProcessVirtualKey(4);
	Sleep(1000);
	RequestWarning(98);

	Sleep(4000);
}

void verify_telltale(void)
{
	printf("verify_telltale!\n");

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

	Sleep(4000);
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
	printf("verify_warninglist!\n");

	RequestWarning(99);
	Sleep(3000);
	ProcessVirtualKey(4);
	RequestWarning(98);
	Sleep(3000);
	ProcessVirtualKey(4);
	RequestWarning(241);
	Sleep(3000);
	ProcessVirtualKey(4);

	ReleaseWarning(98);
	Sleep(500);
	ReleaseWarning(99);
	Sleep(500);
	ReleaseWarning(241);

	Sleep(4000);
}

void verify_warningmode(void)
{
	printf("verify_warningmode!\n");

	SetWarningMode(3);

	RequestWarning(98);

	Sleep(500);

	RequestWarning(99);

	Sleep(500);

	RequestWarning(241);

	SetWarningMode(4);

	Sleep(4000);
}

void verify_suspension_resume(void)
{
	printf("verify_suspension_resume!\n");

	Suspension();

	RequestWarning(98);

	Sleep(500);

	RequestWarning(241);

	Suspension();

	Sleep(500);

	Resume();

	Sleep(4000);
}

void verify_triggertime(void)
{
	printf("verify_triggertime!\n");

	RequestWarning(241);

	Sleep(5000);

	RequestWarning(99);

	Sleep(800);

	ReleaseWarning(99);

	Sleep(500);

	RequestWarning(98);

	Sleep(4000);
}

void verify_availiable(void)
{
	printf("verify_availiable!\n");

	SetAvailiable(OFF);

	SetWarningMode(Abandoned);

	RequestWarning(112);

	Sleep(1000);

	SetAvailiable(Mode1);

	SetWarningMode(Driving);

	Sleep(5000);

	SetAvailiable(OFF);

	Sleep(1000);

	SetAvailiable(Mode1);

	Sleep(4000);
}

void test(void)
{
	SetAvailiable(Stale);

	SetWarningMode(Driving);

	RequestWarning(112);

	Sleep(1000);

	RequestWarning(113);

	Sleep(4000);

	ProcessVirtualKey(4);

	Sleep(4000);

	ProcessVirtualKey(4);

}


void main(void)
{
	init();

	//verify_immediate();

	//verify_userlocktime();

	//verify_telltale();

	//verify_warninglist();

	//verify_warningmode();

	//verify_suspension_resume();

	//verify_triggertime();

	//verify_availiable();

	//verify_suspension_resume();

	test();

	//deInit();


	while (true)
	{
		;
	}
}

