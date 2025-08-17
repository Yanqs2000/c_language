#include <iostream>
#include <string>

using namespace std;


void writeCode(int a)
{
    static int i = 0;
    i++;
    cout << i << endl;
}


int main()
{
    writeCode(30);
    writeCode(40);
    writeCode(50);
    writeCode(60);

    return 0;
}
