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
		cout << "���޴���" << endl;
	}
	else
	{
		cout << "�ҵ�����" << endl;
		cout << "������ " << adbs->personArray[flag].name << "\t";
		cout << "�Ա� " << adbs->personArray[flag].sex << "\t";
		cout << "���䣺 " << adbs->personArray[flag].age << "\t";
		cout << "�绰�� " << adbs->personArray[flag].phone_number << "\t";
		cout << "סַ�� " << adbs->personArray[flag].Addr << endl;

	}

	system("pause");
	system("cls");
	return 0;
}