#pragma once
#include "MyTimer.hpp"
using namespace std;

class Derived : public cMyTimer             //������
{
public:                                     //���е�
    Derived();                              //���캯��
    ~Derived();                             //����������������ж�ʱ��

    //��ʱ���ص�����
    virtual void OnTimer(unsigned id, int iParam, string str);
};