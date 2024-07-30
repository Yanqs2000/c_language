#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
	DIR *d1;					//指向目录文件的指针
	struct dirent *dent1;		//存放目录项的结构体变量
	
	d1=opendir(".");			//打开目录
	if(d1==NULL)    		//判断目录是否成功打开
	{
		perror("open .");	//打开失败，显示相应错误信息
		exit(1);
	}

	//反复的读目录，直到读到NULL为止。
	//这里每次读目录项之前都将错误代码置零来检测错误
	errno=0;
	while( (dent1=readdir(d1))!=NULL)
	{
		printf("inode=%ld name=%s\n", dent1->d_ino, dent1->d_name);
		errno=0;
	}
	
	//如果循环退出并且错误代码非零，则报错
	if(errno!=0)
		perror("read dir error");


	closedir(d1);
}
