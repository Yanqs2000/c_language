#include "main.h"
#include <iostream>
#include <string>

using namespace std;

int show_people(Addressbooks *adbs)
{
	if (adbs->size == 0)
	{
		cout << "��ϵ��Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < adbs->size ; i++)
		{
			cout << "������ " << adbs->personArray[i].name << "\t";
			cout << "�Ա� " << adbs->personArray[i].sex << "\t";
			cout << "���䣺 " << adbs->personArray[i].age << "\t";
			cout << "�绰�� " << adbs->personArray[i].phone_number << "\t";
			cout << "סַ�� " << adbs->personArray[i].Addr << endl;
		}
	}

	system("pause");
	system("cls");
	return 0;
}