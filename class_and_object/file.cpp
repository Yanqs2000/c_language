#include <iostream>
#include <fstream>

using namespace std;
//ofstream - write操作
//ifstream - read操作
//fstream - read/write操作

//打开方式
//ios::in - 读
//ios::out - 写
//ios::trunc - 清空文件
//ios::app - 追加
//ios::binary - 二进制
//ios::ate - 定位到文件末尾


void write_file()
{
    ofstream ofs;
    ofs.open("F:\\Users\\git_hub\\c++\\hello", ios::app);

    ofs << "\n颜\n" << endl;
    ofs << "world456\n" << endl;

    ofs.close();
}

void read_file()
{
    ifstream ifs;
    ifs.open("F:\\Users\\git_hub\\c++\\hello", ios::in);

    if (!ifs.is_open())
    {
        cout << "文件打开失败" << endl;
    }
    else
    {
        cout << "文件打开成功" << endl;
        // 第一种
        // char buf[1024] = { 0 };
        // while (ifs >> buf)
        // {
        //     cout << buf << endl;
        // }

        // 第二种
        // char buf[1024] = { 0 };
        // while (ifs.getline(buf, sizeof(buf)))
        // {
        //     cout << buf << endl;
        // }

        // 第三种
        string buf;
        while (getline(ifs, buf))
        {
            cout << buf << endl;
        }
    }
    ifs.close();
}

void write_binary_file()
{
    ofstream ofs;
    ofs.open("F:\\Users\\git_hub\\c++\\hello", ios::binary | ios::out);

    char num[10] = "123abcABC";
    ofs.write((char*)&num, sizeof(num));
    ofs.close();
}

void read_binary_file()
{
    ifstream ifs;
    ifs.open("F:\\Users\\git_hub\\c++\\hello", ios::binary | ios::in);

    if (!ifs.is_open())
    {
        cout << "文件打开失败" << endl;
    }
    else
    {
        cout << "文件打开成功" << endl;
        
        string buf;
        while (getline(ifs, buf))
        {
            cout << buf << endl;
        }
    }
    ifs.close();
}

int main()
{
    write_binary_file();
    read_binary_file();
    return 0;
}