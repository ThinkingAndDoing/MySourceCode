/***********************************************************
Include Header
***********************************************************/
#include "MyTimer.hpp"
#include "warningstrategy.hpp"


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
	API_DLL unsigned int CALL_TYPE GetActiveWarningID(void);

	API_DLL void CALL_TYPE dllRegisterPythonFunc(void *pyFuncPtr);
}


/***********************************************************
Function declaration
***********************************************************/
void OnWarningChanged(uint16 u16ActiveWrnID);



/***********************************************************
Global variant
***********************************************************/
WarningStrategy ws;
cMyTimer myTimer(&ws);
_callback_python_func python_functioin;



/***********************************************************
Function define
***********************************************************/

void CALL_TYPE init(void)
{
    myTimer.CreateTimer(100);
	myTimer.SetOnTimerCallback(OnWarningChanged);
}

void CALL_TYPE RequestWarning(int id)
{
    ws.RequestWarning((enum WarningIDs)id);
}


void CALL_TYPE ReleaseWarning(int id)
{
    ws.ReleaseWarning((enum WarningIDs)id);
}


unsigned int CALL_TYPE GetActiveWarningID(void)
{
    return ws.GetActiveWarningID();
}

void CALL_TYPE dllRegisterPythonFunc(void *pyFuncPtr)
{
	python_functioin = (_callback_python_func)pyFuncPtr;
}

void OnWarningChanged(uint16 u16ActiveWrnID)
{
	python_functioin(u16ActiveWrnID);

}

