// banker_do.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "InitCls.h"
int main()
{
	InitCls my_AvaliableNumber(4, 4);
	my_AvaliableNumber.InitRandomOfAvailable();
	my_AvaliableNumber.InitRandomOfMax();
	my_AvaliableNumber.InitRandomOfAllocationAndTime();
	system("pause");
	return 0;
}