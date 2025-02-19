#include "main.h"
#include <iostream>
#include <string>

using namespace std;

int modify_people(Addressbooks* adbs, string name)
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

		string n_name;
		string n_sex;
		int n_age;
		string n_phone_number;
		string n_Addr;

		cout << "请修改姓名： " << endl;
		cin >> n_name;
		adbs->personArray[flag].name = n_name;

		cout << "请修改性别： " << endl;
		while (1)
		{
			cin >> n_sex;
			if (n_sex == "男" || n_sex == "女")
			{
				adbs->personArray[flag].sex = n_sex;
				break;
			}
			else
			{
				cout << "请重新输入性别" << endl;
				continue;
			}
		}

		cout << "请修改年龄： " << endl;
		while (1)
		{
			cin >> n_age;
			if (n_age >= 1)
			{
				adbs->personArray[flag].age = n_age;
				break;
			}
			else
			{
				cout << "请重新输入年龄" << endl;
				continue;
			}
		}

		cout << "请修改电话： " << endl;
		while (1)
		{
			cin >> n_phone_number;
			if (n_phone_number.length() == 11)
			{
				adbs->personArray[flag].phone_number = n_phone_number;
				break;
			}
			else
			{
				cout << "请重新输入电话号码" << endl;
				continue;
			}
		}

		cout << "请修改住址： " << endl;
		cin >> n_Addr;
		adbs->personArray[flag].Addr = n_Addr;

		cout << "修改成功" << endl;
	}

	system("pause");
	system("cls");
	return 0;
}