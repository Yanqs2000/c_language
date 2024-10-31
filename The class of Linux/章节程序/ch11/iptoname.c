#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
int main(int argc, const char **argv)
{
     unsigned long addr;
     struct hostent *hp;
     char **p;
     if (argc != 2) 
{
        printf("usage: %s IP-address\n", argv[0]);
        exit (1);
     }
     if ((int)(addr = inet_addr(argv[1])) == -1) 
{
        printf("IP-address must be of the form a.b.c.d\n");
        exit (2);
     }
     hp = gethostbyaddr((char *)&addr, sizeof (addr), AF_INET);
     if (hp == NULL) 
{
        printf("host information for %s not found\n", argv[1]);
        exit (3);
     }
     for (p = hp->h_addr_list; *p != 0; p++) 
{
        struct in_addr in;
        char **q;
        memcpy(&in.s_addr, *p, sizeof (in.s_addr));
        printf("%s\t%s", inet_ntoa(in), hp->h_name);
        for (q = hp->h_aliases; *q != 0; q++)
            printf(" %s", *q);
        putchar('\n');
     }
}
