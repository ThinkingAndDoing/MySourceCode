#include "stdafx.h"

#include "DoubleList.h"
#include "iostream"


#include "main.h"
#include "windows.h"
#include "process.h"
#include <conio.h>                            //_kbhit()

using namespace std;


Derived::Derived()                          //派生类构造函数
{
}

Derived::~Derived()                         //派生类析构函数
{
}

void Derived::OnTimer(unsigned id, int iParam, string str)//定时器处理
{
    static long num;                        //静态变量
    printf("num=%d\r\n", num++);
}

int main()
{
    WarningStrategy ws;
    ws.RequestWarning(turnleft);
    printf("Current warning id is %d\n", ws.GetActiveWarningID());
    ws.RequestWarning(lowbeam);
    printf("Current warning id is %d\n", ws.GetActiveWarningID());
    ws.RequestWarning(turnright);
    printf("Current warning id is %d\n", ws.GetActiveWarningID());
    ws.RequestWarning(highbeam);
    printf("Current warning id is %d\n", ws.GetActiveWarningID());
    ws.RequestWarning(dooropen);
    printf("Current warning id is %d\n", ws.GetActiveWarningID());
    ws.ReleaseWarning(dooropen);
    printf("Current warning id is %d\n", ws.GetActiveWarningID());
    ws.ReleaseWarning(highbeam);
    printf("Current warning id is %d\n", ws.GetActiveWarningID());


    //Derived Test;                           //派生类实例化
    //Test.CreateTimer(300);                 //增加一个定时器id=0，定时时间，单位ms
    ////Test.OnTimer(0, 0, "");                   //调用定时器0处理函数。
    while (!_kbhit()) //用于非阻塞地响应键盘输入事件，为 “keyboard hit（键盘敲击）”的简写
    {
    }
    //Test.DeleteTimer(0);                    //删除定时0

	return 0;
}


