#pragma once
#include "MyTimer.h"
using namespace std;

class Derived : public cMyTimer             //派生类
{
public:                                     //公有的
    Derived();                              //构造函数
    ~Derived();                             //析构函数：清除所有定时器

    //定时器回调函数
    virtual void OnTimer(unsigned id, int iParam, string str);
};