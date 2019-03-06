#pragma once
#include"stdafx.h"
#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<map>
using namespace std;

#ifndef _SAFE_SEQUENCE_PRODUCE_H
#define _SAFE_SEQUENCE_PRODECE_H

class SqeCls {
private:
	vector<int> m_Source;//ϵͳ��Դ
	vector<int> m_Remain_Source;//ϵͳʣ����Դ
	vector<int, vector<int> > m_Allocation;//�ͻ��ѷ�����Դ
	vector<int, vector<int> > m_MAX;//�ͻ���Դ������
	vector<int, vector<int> > m_Request;//�ͻ�����Ҫ����Դ��
	vector<int, int> m_Duration;//�ͻ�����Դ��ռ��ʱ��
	/*
	vector<map<int, string> > m_Release: string���û�����+ʱ��㹹�ɡ�
	���磺m_Release[2]=<5,1_9>; ����2����Դ�ڵ�9ʱ�̱�1�ſͻ��ͷţ��ͷ���Ϊ5
	*/
	vector<map<int, string> >  m_Release;//��Դ�ͷŵ�ʱ������
public:
	void Sqe_Messageinit();//�Ի�����Ϣ���г�ʼ��
	void Sqe_Sourseinit();//��ϵͳ��Դ���г�ʼ��
	void Sqe_Allocationinit();//�ѷ�����Դ��ʼ��
	void Sqe_Remaininit();//ϵͳʣ����Դ��ʼ��
	void Sqe_RequestAndDuration();//�ͻ��������Դ�Ͷ���Դռ��ʱ���ʼ��

};

#endif