#include <iostream>
#include "main.h"

using namespace std;


int main()
{
	int select = 0;//�û�����ı���
	string name_3;
	string name_4;
	string name_5;

	//��ʼ��
	Addressbooks adbs;
	adbs.size = 0;


	while (1)
	{
		//��ʾ�˵�
		menu();
		cin >> select;
		switch (select)
		{
		case 0:
			cout << "��ӭ�´�ʹ��ͨѶ¼" << endl;
			system("pause");
			return 0;
			break;
		case 1:
			add_people_number(&adbs);
			break;
		case 2:
			show_people(&adbs);
			break;
		case 3:
			cout << "������ɾ���˵�����" << endl;
			cin >> name_3;
			delete_people(&adbs,name_3);
			break;
		case 4:
			cout << "����������˵�����" << endl;
			cin >> name_4;
			find_people(&adbs, name_4);
			break;
		case 5:
			cout << "�������޸��˵�����" << endl;
			cin >> name_5;
			modify_people(&adbs, name_5);
			break;
		case 6:
			cout << "�Ƿ����" << endl;
			system("pause");
			adbs.size = 0;
			cout << "�����" << endl;
			system("cls");
			break;
		default:
			break;
		}
	}


	system("pause");
	return 0;
}