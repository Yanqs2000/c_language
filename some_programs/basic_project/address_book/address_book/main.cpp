#include <iostream>
#include "main.h"

using namespace std;


int main()
{
	int select = 0;//用户输入的变量
	string name_3;
	string name_4;
	string name_5;

	//初始化
	Addressbooks adbs;
	adbs.size = 0;


	while (1)
	{
		//显示菜单
		menu();
		cin >> select;
		switch (select)
		{
		case 0:
			cout << "欢迎下次使用通讯录" << endl;
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
			cout << "请输入删除人的姓名" << endl;
			cin >> name_3;
			delete_people(&adbs,name_3);
			break;
		case 4:
			cout << "请输入查找人的姓名" << endl;
			cin >> name_4;
			find_people(&adbs, name_4);
			break;
		case 5:
			cout << "请输入修改人的姓名" << endl;
			cin >> name_5;
			modify_people(&adbs, name_5);
			break;
		case 6:
			cout << "是否清空" << endl;
			system("pause");
			adbs.size = 0;
			cout << "已清空" << endl;
			system("cls");
			break;
		default:
			break;
		}
	}


	system("pause");
	return 0;
}