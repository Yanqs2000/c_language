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
		cout << "ͨѶ¼�������޷����" << endl;
		return;
	}
	else
	{
		cout << "���������" << endl;
		cin >> m_name;
		adbs->personArray[adbs->size].name = m_name;

		cout << "������Ա�" << endl;
		while (1)
		{
			cin >> m_sex;
			if (m_sex == "��" || m_sex == "Ů")
			{
				adbs->personArray[adbs->size].sex = m_sex;
				break;
			}
			else
			{
				cout << "�����������Ա�" << endl;
				continue;
			}
		}
		
		cout << "���������" << endl;
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
				cout << "��������������" << endl;
				continue;
			}
		}

		cout << "����ӵ绰����" << endl;
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
				cout << "����������绰����" << endl;
				continue;
			}
		}

		cout << "����Ӽ�ͥ��ַ" << endl;
		cin >> m_Addr;
		adbs->personArray[adbs->size].Addr = m_Addr;

		adbs->size++;
		cout << "��ӳɹ�" << endl;
	}

	system("pause");
	system("cls");
	return;
}