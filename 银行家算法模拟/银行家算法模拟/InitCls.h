#pragma once
#include "stdafx.h"
#ifndef _INITCLS_H
#define _INTTCLS_H
#include<fstream>
using namespace std;

class InitCls {
public:
	InitCls(int m, int n);//���캯��
	void InitRandomOfAvailable();//����ϵͳ����Դ��
	void InitRandomOfMax();//���ɿͻ������Դ��
	void InitRandomOfAllocationAndTime();//���ɿͻ���ռ��Դ���Լ�ռ��ʱ����
private:
	int m_people;//�ͻ���
	int m_resource;//��Դ��
	ofstream m_Available;//�洢������ɵ�ϵͳ��Դ��
	ofstream m_Max;//�洢�ͻ������Դ��
	ofstream m_AllocationAndTime;//�洢�ͻ���ռ��Դ���Լ�ʱ��ռ����
};

#endif

