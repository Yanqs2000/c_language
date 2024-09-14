#include <stdio.h>
#include <stdlib.h>
const int a = 1;//只读，数据段
static int b = 2;//数据段
int c = 3; //数据段
int d;//bss段
int main(int argc,char * argv[]) 
{
  char *p;//栈
  static int e = 5;//数据段
  static int f;//bss段
  char g[] = "Hello world";//栈
  int h = 6;//栈
  const int i=3;//栈
  p = (char*)malloc(64);//堆
  

  printf("&p:%p\n",&p);
  printf("g:%p\n",&g);
  printf("h:%p\n\n",&h);
  printf("i:%p\n",&i);

  printf("p:%p\n\n",p);

  printf("d:%p\n",&d);
  printf("f:%p\n\n",&f);

  printf("e:%p\n",&e);  
  printf("c:%p\n",&c);
  printf("b:%p\n\n",&b);

  printf("a:%p\n\n",&a);
  return 0;
}
