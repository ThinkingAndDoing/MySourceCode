/***********************************************************
Include Header
***********************************************************/
#include "MyTimer.hpp"
#include "warningstrategy.hpp"
#include "telltale.hpp"

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
	API_DLL void CALL_TYPE RequestWarning(int id);
	API_DLL void CALL_TYPE ReleaseWarning(int id);
	API_DLL void CALL_TYPE SetWarningMode(int id);
	API_DLL uint16 CALL_TYPE GetWarningIDFromStack(int id);
	API_DLL void CALL_TYPE ProcessVirtualKey(int key);

	API_DLL void CALL_TYPE RequestTelltale(int id);
	API_DLL void CALL_TYPE ReleaseTelltale(int id);

	API_DLL void CALL_TYPE dllRegisterPythonFunc(void *pyWarningPtr, void *pyTelltalePtr);
}


/***********************************************************
Function declaration
***********************************************************/
void OnWarningChanged(uint16 u16ActiveWrnID);
void OnTelltaleChanged(uint16 u16ActiveTelltaleID);


/***********************************************************
Global variant
***********************************************************/
WarningStrategy oWrnStrategy;
TelltaleStrategy oTTStrategy;
cMyTimer myTimer(&oWrnStrategy, &oTTStrategy);
_callback_python_func cbWarningChange;
_callback_python_func cbTelltaleChange;



/***********************************************************
Function define
***********************************************************/

void CALL_TYPE init(void)
{
    myTimer.CreateTimer(100);
	myTimer.SetWarningCallback(OnWarningChanged);
	myTimer.SetTelltaleCallback(OnTelltaleChanged);
}

void CALL_TYPE RequestWarning(int id)
{
	oWrnStrategy.RequestWarning((enum WarningIDs)id);
}

void CALL_TYPE ReleaseWarning(int id)
{
	oWrnStrategy.ReleaseWarning((enum WarningIDs)id);
}

void CALL_TYPE SetWarningMode(int id)
{
	oWrnStrategy.SetWarningMode((enum WarningMode)id);
}

uint16 CALL_TYPE GetWarningIDFromStack(int id)
{
	return (uint16)oWrnStrategy.oWarningList.GetWarningFromStack((uint16)id); 
}

void CALL_TYPE ProcessVirtualKey(int key)
{
	oWrnStrategy.ProcessVirtualKey((enum VirtualKey)key);
}

void OnWarningChanged(uint16 u16ActiveWrnID)
{
	cbWarningChange(u16ActiveWrnID);

}


void CALL_TYPE RequestTelltale(int id)
{
	oTTStrategy.RequestWarning((enum TelltaleIDs)id);
}

void CALL_TYPE ReleaseTelltale(int id)
{
	oTTStrategy.ReleaseWarning((enum TelltaleIDs)id);
}

void OnTelltaleChanged(uint16 u16ActiveTelltaleID)
{
	cbTelltaleChange(u16ActiveTelltaleID);

}


void CALL_TYPE dllRegisterPythonFunc(void *pyWarningPtr, void *pyTelltalePtr)
{
	cbWarningChange = (_callback_python_func)pyWarningPtr;
	cbTelltaleChange = (_callback_python_func)pyTelltalePtr;
}

