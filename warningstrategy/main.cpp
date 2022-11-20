#include "stdafx.h"

#include "DoubleList.h"
#include "iostream"


#include "main.h"
#include "windows.h"
#include "process.h"
#include <conio.h>                            //_kbhit()

using namespace std;


Derived::Derived()                          //�����๹�캯��
{
}

Derived::~Derived()                         //��������������
{
}

void Derived::OnTimer(unsigned id, int iParam, string str)//��ʱ������
{
    static long num;                        //��̬����
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


    //Derived Test;                           //������ʵ����
    //Test.CreateTimer(300);                 //����һ����ʱ��id=0����ʱʱ�䣬��λms
    ////Test.OnTimer(0, 0, "");                   //���ö�ʱ��0��������
    while (!_kbhit()) //���ڷ���������Ӧ���������¼���Ϊ ��keyboard hit�������û������ļ�д
    {
    }
    //Test.DeleteTimer(0);                    //ɾ����ʱ0

	return 0;
}


