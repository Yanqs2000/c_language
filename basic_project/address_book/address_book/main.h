#include <iostream>

#define MAX 1000

using namespace std;

struct person
{
	string name;
	string sex;
	int age;
	string phone_number;
	string Addr;
};

struct Addressbooks
{
	person personArray[MAX];
	int size;
};

int menu();
void add_people_number(Addressbooks *adbs);
int show_people(Addressbooks *adbs);
int delete_people(Addressbooks *adbs,string name);
int find_people(Addressbooks *adbs, string name);
int modify_people(Addressbooks* adbs, string name);

	