#include "main.h"
#include <iostream>
#include <string>

using namespace std;

int find_people(Addressbooks* adbs, string name)
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
		cout << "找到此人" << endl;
		cout << "姓名： " << adbs->personArray[flag].name << "\t";
		cout << "性别： " << adbs->personArray[flag].sex << "\t";
		cout << "年龄： " << adbs->personArray[flag].age << "\t";
		cout << "电话： " << adbs->personArray[flag].phone_number << "\t";
		cout << "住址： " << adbs->personArray[flag].Addr << endl;

	}

	system("pause");
	system("cls");
	return 0;
}