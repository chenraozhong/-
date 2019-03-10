#include "stdafx.h"
#include "Init_Message.h"
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<string>
#include<vector>
#include<time.h>

InitCls::InitCls(int m, int n) {
	m_client = m;
	m_resource = n;
}
void InitCls::InitRandomOfAvailable() {
	int my_number;
	srand((unsigned)time(NULL));
	m_Available.open("Available.txt");
	if (!m_Available.is_open()) {
		cout << "The m_Available don't open! error1!" << endl;
	}
	for (int i = 0; i < m_resource; i++) {
		my_number = rand() % 50 + 50;  //����������Դ����������ɣ�50~100)
		m_Available << my_number;
		if (i < m_resource - 1) {   //���һ��������ո��
			m_Available << " ";
		}
	}
	m_Available.close();
}
void InitCls::InitRandomOfMax() {
	string c;
	int my_number1;
	vector<int> my_AvailableFinally;//�洢��ȡ������
	ifstream my_readofAvailable("Available.txt");
	if (!my_readofAvailable.is_open()) {
		cout << "The m_Available don't open! error2!" << endl;
	}
	while (getline(my_readofAvailable, c)) {
		int x;
		stringstream s(c);
		while (s >> x) {
			my_AvailableFinally.push_back(x);
		}
	}
	my_readofAvailable.close();
	m_Max.open("Max.txt");
	if (!m_Max.is_open()) {
		cout << "The Max don't open! error2��" << endl;
	}
	srand((unsigned)time(NULL));
	for (int i = 0; i < m_client; i++) {
		for (int j = 0; j < m_resource; j++) {
			my_number1 = rand() % my_AvailableFinally[j];//���ɵ���Դ������Ϊ��
			m_Max << my_number1;
			if (j < m_resource - 1) {
				m_Max << " ";
			}
		}
		m_Max << "\n";
	}
	m_Max.close();
}
void InitCls::InitRandomOfAllocationAndTime() {
	string c1;
	int my_number2, my_time;
	vector<int> my_MaxFinally;//�洢���е�����
	ifstream my_ReadOfMax("Max.txt");
	if (!my_ReadOfMax.is_open()) {
		cout << "The Max don't open! error3!" << endl;
	}
	while (getline(my_ReadOfMax, c1)) {//�����������ֵ���ȡ
		int x1;
		stringstream s1(c1);
		while (s1 >> x1) {
			my_MaxFinally.push_back(x1);
		}
	}
	my_ReadOfMax.close();
	m_AllocationAndTime.open("AllocationAndTime.txt");
	srand((unsigned)time(NULL));
	if (!m_AllocationAndTime.is_open()) {
		cout << "The AllocationAndTime don't open! error4! " << endl;
	}
	for (int i = 0; i < m_client; i++) {
		for (int j = 0; j < m_resource; j++) {//��һ�������������ɵ���Դ������Ϊ�㣬���Խ��д���
			if (my_MaxFinally[i * 4 + j] == 0) {
				my_number2 = 0;
			}
			else {
				my_number2 = rand() % my_MaxFinally[i * 4 + j];
			}
			my_time = rand() % 9 + 1;                 //��ÿ����Դ��ʱ�䲻Ϊ��
			m_AllocationAndTime << my_number2 << " " << my_time;
			if (j < m_resource - 1) {
				m_AllocationAndTime << " ";
			}
		}
		m_AllocationAndTime << "\n";
	}
	m_AllocationAndTime.close();
}