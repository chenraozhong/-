#pragma once
#pragma once
#include"stdafx.h"
#include<fstream>
#include<vector>
using namespace std;
#ifndef _Message_Init_H
#define _Message_Init_H

class InitCls {
private:
	ofstream m_fSourse;//���ڴ洢ϵͳ��Դ
	ofstream m_fAllocation;//���ڴ洢�û���ռ����Դ���
						   //ofstream m_fRequest;//���ڴ洢�û��������Դ����ռ��ʱ��
	int m;//ϵͳ��Դ������(��Ϊ��û�н��棬���Գ�ʼ��Ϊ3)
		  //int n;//�ͻ���(��Ϊ��û�н��棬���Գ�ʼ��)
	vector<int> m_Sourse;

public:
	void InitSourse();//��ʼ��ϵͳ��Դ
					  //void InitAllocation();//��ʼ���û���ռ����Դ
					  //void InitRequest();//��ʼ���û��������Դ����ռ��ʱ��
};

#endif