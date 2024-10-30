//string 是一个类，类内部封装了char*，并封装了针对char*的很多操作
#include <iostream>

using namespace std;

//string构造
/*
    string();              //创建一个空的字符串对象
    string(const char* s); //用C语言字符串s初始化
    string(const string& str); //拷贝构造函数
    string(int n,char c); //用n个字符c初始化
*/

void test01()
{
    string str1; //默认构造
    const char* c = "hello world";//常字符指针指向常量
    
    string str2(c);
    cout << "str2 = " << str2 << endl;

    string str3(str2);

    string str4(10, 'a');
    cout << "str4 = " << str4 << endl;
}

//string赋值操作
/*
    string& operator=(const char* s); //char*类型字符串赋值给string对象
    string& operator=(const string& s); //把一个string对象赋值给另一个string对象
    string& operator=(char c); //字符赋值给string对象
    string& assign(const char* s); //char*类型字符串赋值给string对象
    string& assign(const char* s,int n); //把C语言字符串s的前n个字符赋值给字符串对象
    string& assign(const string& s); //把一个string对象赋值给另一个string对象
    string& assign(int n,char c); //用n个字符c初始化

*/

void test02()
{
    string str1;
    str1 = "hello world";

    string str2;
    str2 = str1;

    string str3;
    str3 = 'a';

    //成员函数的方法
    string str4;
    str4.assign("hello world");

    string str5;
    str5.assign("hello world", 5);

    string str6;
    str6.assign(str5);

    string str7;
    str7.assign(10, 'a');
}


//string字符串拼接
/*
    string& operator+=(const char* s); //把字符串s连接到当前字符串结尾
    string& operator+=(const char c); //把字符c连接到当前字符串结尾
    string& operator+=(const string& str); //把字符串str连接到当前字符串结尾
    string& append(const char* s); //把字符串s连接到当前字符串结尾
    string& append(const char* s,int n); //把字符串s的前n个字符连接到当前字符串结尾
    string& append(const string& str); //把字符串str连接到当前字符串结尾
    string& append(const string& str,int pos,int n); //把字符串str中从pos开始的n个字符连接到当前字符串结尾
*/

void test03()
{
    string str1 = "hello";
    str1 += " world";
    
    string str2 = "hello";
    str2 += 'a';

    string str3 = "hello";
    str3 += str2;

    string str4 = "hello";
    str4.append(" world");

    string str5 = "hello";
    str5.append(" world", 2);

    string str6 = "hello";
    str6.append(str5);
}

//string查找和替换
/*
    int find(const string& str,int pos = 0) const; //查找str第一次出现的位置，pos为查找的起始位置
    int find(const char* s,int pos = 0) const; //查找s第一次出现的位置，pos为查找的起始位置
    int find(const char* s,int pos,int n) const; //从pos位置查找字符串s的前n个字符第一次出现的位置
    int find(const char c,int pos = 0) const; //查找字符c第一次出现的位置，pos为查找的起始位置
    int rfind(const string& str,int pos = npos) const; //查找str最后一次出现的位置，pos为查找的起始位置
    int rfind(const char* s,int pos = npos) const; //查找s最后一次出现的位置，pos为查找的起始位置
    int rfind(const char* s,int pos,int n) const; //从pos位置查找字符串s的前n个字符最后一次出现的位置
    int rfind(const char c,int pos = npos) const; //查找字符c最后一次出现的位置，pos为查找的起始位置
    string& replace(int pos,int n,const char* s); //用字符串s替换从pos开始的n个字符
*/

void test04()
{
    string str1 = "hello world";
    int pos = str1.find("o");

    cout << "pos = " << pos << endl;//从0开始索引，-1表示无法找到,find从前往后查找,找到一个则停止

    string str2 = "hello world";
    int pos2 = str2.rfind("o");

    cout << "pos2 = " << pos2 << endl;//从0开始索引，-1表示无法找到，rfind从后往前查找，找到一个则停止

    string str3 = "hello world";
    str3.replace(1, 3, "abcd");//从1号索引开始，替换3个字符，用abcd替换，输出为habcdo world
    cout << "str3 = " << str3 << endl;
}


//string字符串比较（ascii码）,相同输出0，大于输出1，小于输出-1
/*
    int compare(const string& s) const; //与字符串s比较
    int compare(const char* s) const; //与C字符串s比较
*/
void test05()
{
    string str1 = "hello";
    string str2 = "hella";
    int ret = str1.compare(str2);
    cout << "ret = " << ret << endl;
}

//string 字符存取
/*
    char& operator[](int n); //通过[]方式获取第n个字符
    char& at(int n); //通过at方法获取第n个字符
*/
void test06()
{
    //读
    string str1 = "hello world";
    cout << "str1[0] = " << str1[0] << endl;
    cout << "str1.at(0) = " << str1.at(0) << endl;

    for (int i = 0; i < str1.size(); i++)
    {
        cout << str1[i] << " ";
        cout << str1.at(i) << " ";
    }
    //写
    str1.at(0) = 'x';
    str1[1] = 'x';
    cout << "str1 = " << str1 << endl;
    
}

//string插入和删除
/*
    string& insert(int pos,const char* s); //在pos位置插入字符串s
    string& insert(int pos,const char* s,int n); //在pos位置插入字符串s的前n个字符
    string& insert(int pos,const string& str); //在pos位置插入字符串str
    string& erase(int pos,int n); //删除从pos开始的n个字符
*/
void test07()
{
    string str1 = "hello world";
    str1.insert(5, "abc");
    str1.insert(5, "xyz", 2);
    cout << "str1 = " << str1 << endl;

    string str2 = "hello world";
    str2.erase(5, 3);
    cout << "str2 = " << str2 << endl;
}

//string子串,截取字符串中的一小段
/*
    string substr(int pos = 0,int n = npos) const; //返回从pos开始的n个字符组成的字符串
*/
void test08()
{
    string str1 = "hello world";
    string subStr = str1.substr(4, 3);
    cout << "subStr = " << subStr << endl;

    string str2 = "颜祺淞，你好";
    int pos = str2.find("淞");
    string subStr2 = str2.substr(0, pos);
    cout << "pos = " << pos << endl;
    cout << "subStr2 = " << subStr2 << endl;
}
int main()
{
    test08();
    return 0;
}