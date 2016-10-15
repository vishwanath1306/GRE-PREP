#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>
#define HOST_PORT 3030
#define ROOT_PORT 3031
int main(int argc,char *argv[])
{
        struct sockaddr_in lns,ins;
        char host[1024],ip[1024],file[1024];
        int fd,n,n1;
        fd=socket(AF_INET,SOCK_DGRAM,0);
        lns.sin_family=AF_INET;
        lns.sin_port=HOST_PORT;
        lns.sin_addr.s_addr=inet_addr("127.0.0.1");
        ins.sin_family=AF_INET;
        ins.sin_port=ROOT_PORT;
        ins.sin_addr.s_addr=inet_addr("127.0.0.1");
        bind(fd,(struct sockaddr *)&lns,sizeof lns);
        n=sizeof ins;
        n1=sizeof lns;
        while(1)
        {
                strcpy(ip,"");
                FILE *fp=fopen("lnscache.txt","r+");
                recvfrom(fd,host,sizeof host,0,(struct sockaddr *)&lns,&n1);
                while(!feof(fp))
                {
                        fscanf(fp,"%s",file);
                        if(strcmp(file,host)==0)
                        {
                                fscanf(fp,"%s",ip);
                                break;
                        }
                }
                if(strcmp(ip,"")==0)
                {
                        sendto(fd,host,sizeof host,0,(struct sockaddr *)&ins,n);
                        recvfrom(fd,ip,sizeof ip,0,(struct sockaddr *)&ins,&n);
                        if(strcmp(ip,"ERROR:404 NOT FOUND")!=0)
                        {
 fclose(fp);
                                FILE *fp1=fopen("lnscache.txt","a");
                                fputs(host,fp1);
                                putc('\n',fp1);
                                fputs(ip,fp1);
                                putc('\n',fp1);
                                fclose(fp1);
                        }
                }
                else
                        fclose(fp);
                sendto(fd,ip,sizeof ip,0,(struct sockaddr *)&lns,n1);
        }
        return 0;
}
