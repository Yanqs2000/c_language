#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
	DIR *d1;					//ָ��Ŀ¼�ļ���ָ��
	struct dirent *dent1;		//���Ŀ¼��Ľṹ�����
	
	d1=opendir(".");			//��Ŀ¼
	if(d1==NULL)    		//�ж�Ŀ¼�Ƿ�ɹ���
	{
		perror("open .");	//��ʧ�ܣ���ʾ��Ӧ������Ϣ
		exit(1);
	}

	//�����Ķ�Ŀ¼��ֱ������NULLΪֹ��
	//����ÿ�ζ�Ŀ¼��֮ǰ�����������������������
	errno=0;
	while( (dent1=readdir(d1))!=NULL)
	{
		printf("inode=%ld name=%s\n", dent1->d_ino, dent1->d_name);
		errno=0;
	}
	
	//���ѭ���˳����Ҵ��������㣬�򱨴�
	if(errno!=0)
		perror("read dir error");


	closedir(d1);
}
