// banker_do.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
//#include "Init_Message.h"
//#include"Safe_Sequence_Produce.h"
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
using namespace std;

int main()
{
	/*
	InitCls my_AvaliableNumber(4, 4);
	my_AvaliableNumber.InitRandomOfAvailable();
	my_AvaliableNumber.InitRandomOfMax();
	my_AvaliableNumber.InitRandomOfAllocationAndTime();
	*/
	//SqeCls ss;
	//ss.SqeCls_Messageinit();
	/*
	vector<vector<int> > value;
	vector<int> value1;
	value.push_back(value1);
	value.push_back(value1);
	value.push_back(value1);
	value[1] = value1;
	map<int, int> mymap;
	mymap[2] = 3;
	map<int, int>::iterator item = mymap.find(2);
	if (item!=mymap.end()) cout << "���ҵ�" << endl;
	mymap[2] += 5;
	cout << mymap[2];
	*/
	vector<int> a;
	a.push_back(1);
	vector<int> b;
	b = a;
	a.push_back(2);
	cout << b.size();
	system("pause");
	return 0;
}