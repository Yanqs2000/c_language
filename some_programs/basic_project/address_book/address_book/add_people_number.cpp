#include "main.h"
#include <iostream>
#include <string>

using namespace std;

void add_people_number(Addressbooks *adbs)
{
	string m_name;
	string m_sex;
	int m_age;
	string m_phone_number;
	string m_Addr;
	
	if (adbs->size == MAX)
	{
		cout << "通讯录已满，无法添加" << endl;
		return;
	}
	else
	{
		cout << "请添加姓名" << endl;
		cin >> m_name;
		adbs->personArray[adbs->size].name = m_name;

		cout << "请添加性别" << endl;
		while (1)
		{
			cin >> m_sex;
			if (m_sex == "男" || m_sex == "女")
			{
				adbs->personArray[adbs->size].sex = m_sex;
				break;
			}
			else
			{
				cout << "请重新输入性别" << endl;
				continue;
			}
		}
		
		cout << "请添加年龄" << endl;
		while (1)
		{
			cin >> m_age;
			if (m_age >= 1)
			{
				adbs->personArray[adbs->size].age = m_age;
				break;
			}
			else
			{
				cout << "请重新输入年龄" << endl;
				continue;
			}
		}

		cout << "请添加电话号码" << endl;
		while (1)
		{
			cin >> m_phone_number;
			if (m_phone_number.length() == 11)
			{
				adbs->personArray[adbs->size].phone_number = m_phone_number;
				break;
			}
			else
			{
				cout << "请重新输入电话号码" << endl;
				continue;
			}
		}

		cout << "请添加家庭地址" << endl;
		cin >> m_Addr;
		adbs->personArray[adbs->size].Addr = m_Addr;

		adbs->size++;
		cout << "添加成功" << endl;
	}

	system("pause");
	system("cls");
	return;
}