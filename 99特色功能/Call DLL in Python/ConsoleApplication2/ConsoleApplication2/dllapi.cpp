/***********************************************************
Include Header
***********************************************************/
#include "MyTimer.hpp"
#include "warninglist.hpp"
#include "warningstrategycm1e.hpp"
#include "telltale.hpp"
#include "warningresourceids.hpp"


#define INVALID_ID		0xFFFF

/***********************************************************
Macro define & Type define
***********************************************************/
#define API_DLL __declspec(dllexport)
#define CALL_TYPE __cdecl

typedef void(*_callback_python_func)(int iParam);

/***********************************************************
Export API in DLL
***********************************************************/
extern "C"
{
	API_DLL void CALL_TYPE init(void);
	API_DLL void CALL_TYPE deInit(void);
	API_DLL void CALL_TYPE RequestWarning(int id);
	API_DLL void CALL_TYPE ReleaseWarning(int id);
	API_DLL void CALL_TYPE SetWarningMode(int id);
	API_DLL void CALL_TYPE Suspension(void);
	API_DLL void CALL_TYPE Resume(void);
	API_DLL uint16 CALL_TYPE GetWarningIDFromStack(int id);
	API_DLL void CALL_TYPE ProcessVirtualKey(int key);

	API_DLL void CALL_TYPE RequestTelltale(int id);
	API_DLL void CALL_TYPE ReleaseTelltale(int id);

	API_DLL void CALL_TYPE dllRegisterPythonFunc(void *pyWarningStackPtr, void *pyWarningPtr, void *pyTelltalePtr);
}


/***********************************************************
Function declaration
***********************************************************/
void OnWarningStackChanged(uint16 u16StackSize);
void OnWarningChanged(uint16 u16ActiveWrnID);
void OnTelltaleChanged(uint16 u16ActiveTelltaleID);


/***********************************************************
Global variant
***********************************************************/
WarningStrategyCM1E *poWrnStrategy;
TelltaleStrategy *poTTStrategy;
cMyTimer *poMyTimer;
_callback_python_func cbWarningStackChange;
_callback_python_func cbWarningChange;
_callback_python_func cbTelltaleChange;



/***********************************************************
Function define
***********************************************************/


// warning popup
void CALL_TYPE init(void)
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
	poMyTimer->CreateTimer(100);
	poMyTimer->SetWarningStackCallback(OnWarningStackChanged);
	poMyTimer->SetWarningCallback(OnWarningChanged);
	poMyTimer->SetTelltaleCallback(OnTelltaleChanged);
}

void CALL_TYPE deInit(void)
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
void CALL_TYPE RequestWarning(int id)
{
	poWrnStrategy->RequestWarning((enum WarningIDs)id);
}

void CALL_TYPE ReleaseWarning(int id)
{
	poWrnStrategy->ReleaseWarning((enum WarningIDs)id);
}

void CALL_TYPE SetWarningMode(int id)
{
	poWrnStrategy->SetWarningMode((enum WarningMode)id);
}

uint16 CALL_TYPE GetWarningIDFromStack(int id)
{
	uint16 u16WrnID = (uint16)poWrnStrategy->poWarningList->GetWarningFromStack((uint16)id);

	if (NumberOfWarnings == u16WrnID)
	{
		u16WrnID = INVALID_ID;
	}

	return u16WrnID;
}


void CALL_TYPE Suspension(void)
{
	poWrnStrategy->Suspension();
}


void CALL_TYPE Resume(void)
{
	poWrnStrategy->Resume();
}


void CALL_TYPE ProcessVirtualKey(int key)
{
	poWrnStrategy->ProcessVirtualKey((enum VirtualKey)key);
}

void OnWarningStackChanged(uint16 u16StackSize)
{
	cbWarningStackChange(u16StackSize);

}

void OnWarningChanged(uint16 u16ActiveWrnID)
{
	if (NumberOfWarnings != u16ActiveWrnID)
	{
		cbWarningChange(u16ActiveWrnID);
	}
	else{
		cbWarningChange(INVALID_ID);
	}

}

// telltale
void CALL_TYPE RequestTelltale(int id)
{
	poTTStrategy->RequestWarning((enum WarningIDs)id);
}

void CALL_TYPE ReleaseTelltale(int id)
{
	poTTStrategy->ReleaseWarning((enum WarningIDs)id);
}

void OnTelltaleChanged(uint16 u16ActiveTelltaleID)
{
	if (NumberOfWarnings != u16ActiveTelltaleID)
	{
		cbTelltaleChange(u16ActiveTelltaleID);
	}
	else{
		cbTelltaleChange(INVALID_ID);
	}

}


// register call back
void CALL_TYPE dllRegisterPythonFunc(void *pyWarningStackPtr, void *pyWarningPtr, void *pyTelltalePtr)
{
	cbWarningStackChange = (_callback_python_func)pyWarningStackPtr;
	cbWarningChange = (_callback_python_func)pyWarningPtr;
	cbTelltaleChange = (_callback_python_func)pyTelltalePtr;
}

