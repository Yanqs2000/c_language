#include <stdio.h>
#include <stdlib.h>
const int a = 1;//ֻ�������ݶ�
static int b = 2;//���ݶ�
int c = 3; //���ݶ�
int d;//bss��
int main(int argc,char * argv[]) 
{
  char *p;//ջ
  static int e = 5;//���ݶ�
  static int f;//bss��
  char g[] = "Hello world";//ջ
  int h = 6;//ջ
  const int i=3;//ջ
  p = (char*)malloc(64);//��
  

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
