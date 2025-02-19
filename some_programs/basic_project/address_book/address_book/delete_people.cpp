#include "main.h"
#include <iostream>
#include <string>

using namespace std;

int delete_people(Addressbooks *adbs, string name)
{
	int flag = 1000;
	for (int i = 0; i < adbs->size; i++)
	{
		if (adbs->personArray[i].name == name)
		{
			flag = i;
		}
		else
		{
			flag = -1;
		}
	}
	if (flag == -1)
	{
		cout << "查无此人" << endl;
	}
	else
	{
		cout << "找到此人,是否删除" << endl;
		system("pause");
		
		//数组迁移
		for (int i = flag; i < adbs->size; i++)
		{
			adbs->personArray[i] = adbs->personArray[i + 1];
		}
		adbs->size--;
		cout << "删除成功" << endl;
	}

	system("pause");
	system("cls");
	return 0;
}