
#include "warningstrategy.hpp"

WarningStrategy ws;
extern "C" __declspec(dllexport) int add(int a, int b);
extern "C" __declspec(dllexport) void RequestWarning(int id);
extern "C" __declspec(dllexport) void ReleaseWarning(int id);
extern "C" __declspec(dllexport) void TimeTick(void);
extern "C" __declspec(dllexport) unsigned int GetActiveWarningID(void);

int add(int a, int b)
{
    return a + b;
}

void RequestWarning(int id)
{
    ws.RequestWarning((enum WarningIDs)id);
}



void ReleaseWarning(int id)
{
    ws.ReleaseWarning((enum WarningIDs)id);
}


void TimeTick(void)
{
    ws.TimeTick();
}

unsigned int GetActiveWarningID(void)
{
    return ws.GetActiveWarningID();
}
