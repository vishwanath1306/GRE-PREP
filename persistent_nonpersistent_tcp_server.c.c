#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<sys/socket.h>
int main()
{
struct sockaddr_in ser,cli;
memset(&ser,0,sizeof(ser));
memset(&cli,0,sizeof(cli));
char buf[100];
int k;
int fd=socket(AF_INET,SOCK_STREAM,0);
ser.sin_family=AF_INET;
ser.sin_addr.s_addr=inet_addr("127.0.0.1");
ser.sin_port=3321;
k=bind(fd,(struct sockaddr *)&ser,sizeof(ser));
if(k<0)
exit(1);
k=listen(fd,5);
if(k<0)
exit(1);
int len=sizeof(cli);
int nd=accept(fd,(struct sockaddr *)&cli,&len);
while(1)
{
k=recv(nd,buf,100,0);
printf("client message:%s\n",buf);
if(strcmp(buf,"bye")==0)
break;
}
close(nd);
nd=accept(fd,(struct sockaddr *)&cli,&len);
printf("server reply:");
scanf("%s",buf);
k=send(nd,buf,100,0);
close(nd);
close(fd);
return 0;
}
