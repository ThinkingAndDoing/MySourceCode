#ifndef WARNINGRESOURCEIDS_H
#define WARNINGRESOURCEIDS_H
#include "iostream"
using namespace std;

enum WarningIDs
{
    turnleft = 0,
    turnright,
    lowbeam,
    highbeam,
    dooropen,
    brakered,
    brakeyellow,
    numberofwarnings,
    invalidwarningid = 0xFFFF
};



#endif
