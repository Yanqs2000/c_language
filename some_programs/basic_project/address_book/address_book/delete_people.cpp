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
		cout << "���޴���" << endl;
	}
	else
	{
		cout << "�ҵ�����,�Ƿ�ɾ��" << endl;
		system("pause");
		
		//����Ǩ��
		for (int i = flag; i < adbs->size; i++)
		{
			adbs->personArray[i] = adbs->personArray[i + 1];
		}
		adbs->size--;
		cout << "ɾ���ɹ�" << endl;
	}

	system("pause");
	system("cls");
	return 0;
}