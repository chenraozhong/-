// ���м��㷨ģ��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Init_Message.h"
#include "Safe_Sequence_Sort.h"

int main()
{
	InitCls my_AvaliableNumber(4, 4);
	my_AvaliableNumber.InitRandomOfAvailable();
	my_AvaliableNumber.InitRandomOfMax();
	my_AvaliableNumber.InitRandomOfAllocation();
	my_AvaliableNumber.InitRandomOfTime();

	Sort_Sequence_SortCls my_SafeAndWeight;
	my_SafeAndWeight.ReadOfSafeAndWeight();
	my_SafeAndWeight.SortOfWeight();
	my_SafeAndWeight.WriteOfSafeAndWeight();

	system("pause");
	return 0;
}

