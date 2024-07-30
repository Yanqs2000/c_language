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
		cout << "���޴���" << endl;
	}
	else
	{
		cout << "�ҵ�����" << endl;

		string n_name;
		string n_sex;
		int n_age;
		string n_phone_number;
		string n_Addr;

		cout << "���޸������� " << endl;
		cin >> n_name;
		adbs->personArray[flag].name = n_name;

		cout << "���޸��Ա� " << endl;
		while (1)
		{
			cin >> n_sex;
			if (n_sex == "��" || n_sex == "Ů")
			{
				adbs->personArray[flag].sex = n_sex;
				break;
			}
			else
			{
				cout << "�����������Ա�" << endl;
				continue;
			}
		}

		cout << "���޸����䣺 " << endl;
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
				cout << "��������������" << endl;
				continue;
			}
		}

		cout << "���޸ĵ绰�� " << endl;
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
				cout << "����������绰����" << endl;
				continue;
			}
		}

		cout << "���޸�סַ�� " << endl;
		cin >> n_Addr;
		adbs->personArray[flag].Addr = n_Addr;

		cout << "�޸ĳɹ�" << endl;
	}

	system("pause");
	system("cls");
	return 0;
}