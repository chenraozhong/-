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
	vector<int> m_Source;
	vector<int> m_Remain_Source;
	vector<int, vector<int> > m_Allocation;
//	vector<int, vector<int> > m_MAXRequest;//�ͻ�����Դ��������
//	vector<int, vector<int> > m_Request;
//	vector<int, int> m_Duration;
	/*
	vector<map<int, string> > m_Release: string���û�����+ʱ��㹹�ɡ�
	���磺m_Release[2]=<5,1_9>; ����2����Դ�ڵ�9ʱ�̱�1�ſͻ��ͷţ��ͷ���Ϊ5
	*/
	/*
	vector<map<int, string> >  m_Release;//��Դ�ͷŵ�ʱ������
	*/
public:
	void Sqe_Messageinit();
	void Sqe_Sourseinit();
	void Sqe_Allocationinit();
	void Sqe_RemainSourceinit();
	void Sqe_RequestAndDuration();
};

#endif