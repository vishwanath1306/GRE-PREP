#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<sys/socket.h>
int main()
{
struct sockaddr_in ser;
memset(&ser,0,sizeof(ser));
char buf[100];
int k;
int fd=socket(AF_INET,SOCK_STREAM,0);
ser.sin_family=AF_INET;
ser.sin_addr.s_addr=inet_addr("127.0.0.1");
ser.sin_port=3321;
int len=sizeof(ser);
k=connect(fd,(struct sockaddr *)&ser,sizeof(ser));
while(1)
{
printf("\nclient message:");
scanf("%s",buf);
send(fd,buf,100,0);
if(strcmp(buf,"bye")==0)
break;
}
close(fd);
fd=socket(AF_INET,SOCK_STREAM,0);
k=connect(fd,(struct sockaddr *)&ser,sizeof(ser));
k=recv(fd,buf,100,0);
printf("\nserver reply:%s",buf);
close(fd);
return 0;
}
