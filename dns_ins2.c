#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>
#define HOST_PORT 3033
#define ROOT_PORT 3034
int main(int argc,char *argv[])
{
        struct sockaddr_in ans,ins;
        char host[1024],ip[1024],file[1024];
        int fd,n,n1;
        fd=socket(AF_INET,SOCK_DGRAM,0);
        ins.sin_family=AF_INET;
        ins.sin_port=HOST_PORT;
        ins.sin_addr.s_addr=inet_addr("127.0.0.1");
        ans.sin_family=AF_INET;
        ans.sin_port=ROOT_PORT;
        ans.sin_addr.s_addr=inet_addr("127.0.0.1");
        bind(fd,(struct sockaddr *)&ins,sizeof ins);
        n=sizeof ins;
        n1=sizeof ans;
        while(1)
        {
                strcpy(ip,"");
                FILE *fp=fopen("ins2cache.txt","r+");
                recvfrom(fd,host,sizeof host,0,(struct sockaddr *)&ins,&n);
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
                        sendto(fd,host,sizeof host,0,(struct sockaddr *)&ans,n1);
                        recvfrom(fd,ip,sizeof ip,0,(struct sockaddr *)&ans,&n1);
                        if(strcmp(ip,"ERROR:404 NOT FOUND")!=0)
                        {
 fclose(fp);
                                FILE *fp1=fopen("ins2cache.txt","a");
                                fputs(host,fp);
                                putc('\n',fp);
                                fputs(ip,fp);
                                putc('\n',fp);
                                fclose(fp1);
                        }
                        else
                                fclose(fp);
                }
                else
                        fclose(fp);
                sendto(fd,ip,sizeof ip,0,(struct sockaddr *)&ins,n);
        }
        return 0;
}
