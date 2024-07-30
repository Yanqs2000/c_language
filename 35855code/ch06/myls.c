#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <linux/fs.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <grp.h>
#include <pwd.h>
int typeflag;//file type
void print_size(struct stat *statp)
{
    switch (statp->st_mode & S_IFMT) 
   {
    case S_IFCHR:
    case S_IFBLK:
        printf(" %u,%u ", (unsigned)(statp->st_rdev >> 8),
          (unsigned)(statp->st_rdev & 0xFF));
        break;
    default:
        printf(" %u ", (unsigned long)statp->st_size);
    }
}
void print_date(struct stat *statp)
{
    time_t now;
    double diff;
    char buf[100], *fmt;
    if (time(&now) == -1) 
    {
        printf(" ????????????");
        return;
    }
    diff = difftime(now, statp->st_mtime);
    if (diff < 0 || diff > 60 * 60 * 24 * 182.5) /* roughly 6 months */
        fmt = "%b %e  %Y";
    else
        fmt = "%b %e %H:%M";
    strftime(buf, sizeof(buf), fmt, localtime(&statp->st_mtime));
    printf(" %s ", buf);
}
void printlong(char *name)
{
	struct stat buf;
	struct passwd *user;
	struct group *grp;
	char linkname[64];
	char dirfilename[64];
	int rt;
       rt=lstat(name,&buf);
	if(rt==-1)
	{
		perror("in printlong:lstat");
		return;
	}
        switch(buf.st_mode & S_IFMT)
        {
                case S_IFDIR:  printf("d");break;
                case S_IFLNK:  printf("l");break;
                case S_IFREG:  printf("-");break;
                case S_IFBLK:  printf("b");break;
                case S_IFCHR:  printf("c");break;
                case S_IFSOCK:  printf("s");break;
                case S_IFIFO:  printf("p");break;
                default:printf("?");
        }
        putchar((buf.st_mode & S_IRUSR) ? 'r' :'-');
        putchar((buf.st_mode & S_IWUSR) ? 'w' :'-');
	if(buf.st_mode & S_ISUID)
		putchar((buf.st_mode & S_IXUSR) ? 's' :'S');
	else
        	putchar((buf.st_mode & S_IXUSR) ? 'x' :'-');
        putchar((buf.st_mode & S_IRGRP) ? 'r' :'-');
        putchar((buf.st_mode & S_IWGRP) ? 'w' :'-');
	if(buf.st_mode & S_ISGID)
		putchar((buf.st_mode & S_IXGRP) ? 's' :'S');
	else
        	putchar((buf.st_mode & S_IXGRP) ? 'x' :'-');

        putchar((buf.st_mode & S_IROTH) ? 'r' :'-');
        putchar((buf.st_mode & S_IWOTH) ? 'w' :'-');
	if(buf.st_mode & S_ISVTX)
		putchar((buf.st_mode & S_IXOTH) ? 't' :'T');
	else
        	putchar((buf.st_mode & S_IXOTH) ? 'x' :'-');
        printf(" %u ",buf.st_nlink);
	user=getpwuid(buf.st_uid);
	printf(" %s ",user->pw_name);
       	grp=getgrgid(buf.st_gid);
	printf(" %s ",grp->gr_name);
        print_size(&buf);
        print_date(&buf);
	if(typeflag==3)
	{
		rt=readlink(name,linkname,sizeof(linkname));
		linkname[rt]=0;
		printf(" %s->%s ",name,linkname);
	}
	else
		printf("%s",name);

        printf("\n");
}
void lsdir(char *name,int flag)
{
	DIR *d1;
	struct dirent *dent1;
	char namebuf[128];
	char workdir[50];
	d1=opendir(name);
	if(d1==NULL)
	{
		perror("opendir");
		exit(1);
	}
	getcwd(workdir,50);
	chdir(name);
	errno=0;
	dent1=readdir(d1);
	while( dent1!=NULL)
	{
		if(dent1->d_name[0]!='.')
		{
			if(flag==0)
				printf("%s\t",dent1->d_name);
			else
				printlong(dent1->d_name);
		}
		dent1=readdir(d1);
	}
	if(errno!=0)
		perror("readdir");
	if(flag==0)
		printf("\n");
	closedir(d1);
	chdir(workdir);
	
}
void checkfiletype(char *name)
{
	struct stat  buf;
	lstat(name,&buf);
	switch(buf.st_mode & S_IFMT)  
	{
		case S_IFREG:  typeflag=1;break;
		case S_IFDIR:  typeflag=2;break;
		case S_IFLNK:  typeflag=3;break;
		case S_IFCHR:  typeflag=4;break;
		case S_IFBLK:  typeflag=5;break;
		case S_IFSOCK: typeflag=6;break;
		case S_IFIFO:  typeflag=7;break;
		default:typeflag=0;
	}
}
main(int argc, char *argv[])
{
 	int rt=-1;
	if(argc>3)
	{
		printf("Usage:\n%s\n%s  filename\n%s  dirname\n%s  -l\n%s  -l  dirname\n%s  -l  filename\n",argv[0],argv[0],argv[0],argv[0],argv[0],argv[0]);
		exit(1);
	}
	if(argc==1)
		lsdir(".",0);
     else if(argc==2)
	{
		if(strcmp(argv[1],"-l")==0)
			lsdir(".",1);
		else
		{
			checkfiletype(argv[1]);
			if(typeflag==2)
				lsdir(argv[1],0);
			else if(typeflag==1)
				printf("%s\n",argv[1]);
		}
	}
   	else if(argc==3)
	{
		if(strcmp(argv[1],"-l")==0)
		{
			checkfiletype(argv[2]);
			if(typeflag==2)
				lsdir(argv[2],1);
			else if(typeflag==1)
				printlong(argv[2]);
		}
	}
}
