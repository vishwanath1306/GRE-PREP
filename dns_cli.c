#include<stdio.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define PORT 3030
int main(int argc,char *argv[])
{
        struct sockaddr_in server;
        int fd,n;
        char host[1024],ip[1024];
        fd=socket(AF_INET,SOCK_DGRAM,0);
        if(fd<0)
        {
                printf("Socket Error\n");
                return 0;
        }
        server.sin_family=AF_INET;
        server.sin_port=PORT;
        server.sin_addr.s_addr=inet_addr("127.0.0.1");
        n=sizeof server;
        printf("\nEnter the canonical name..");
        scanf("%s",host);
        sendto(fd,host,sizeof(host),0,(struct sockaddr *)&server,n);
        recvfrom(fd,ip,sizeof host,0,(struct sockaddr *)&server,&n);
        printf("\nThe Corresponding IP address is %s\n",ip);
        return 0;
}
