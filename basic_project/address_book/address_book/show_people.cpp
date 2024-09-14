#include "main.h"
#include <iostream>
#include <string>

using namespace std;

int show_people(Addressbooks *adbs)
{
	if (adbs->size == 0)
	{
		cout << "联系人为空" << endl;
	}
	else
	{
		for (int i = 0; i < adbs->size ; i++)
		{
			cout << "姓名： " << adbs->personArray[i].name << "\t";
			cout << "性别： " << adbs->personArray[i].sex << "\t";
			cout << "年龄： " << adbs->personArray[i].age << "\t";
			cout << "电话： " << adbs->personArray[i].phone_number << "\t";
			cout << "住址： " << adbs->personArray[i].Addr << endl;
		}
	}

	system("pause");
	system("cls");
	return 0;
}