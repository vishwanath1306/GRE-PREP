#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>
#define HOST_PORT 3034
int main(int argc,char *argv[])
{
        struct sockaddr_in ans,rns;
        char host[1024],ip[1024],file[1024];
        int fd,n,n1;
        fd=socket(AF_INET,SOCK_DGRAM,0);
        ans.sin_family=AF_INET;
        ans.sin_port=HOST_PORT;
        ans.sin_addr.s_addr=inet_addr("127.0.0.1");
        /*rns.sin_family=AF_INET;
        rns.sin_port=ROOT_PORT;
        rns.sin_addr.s_addr=inet_addr("127.0.0.1");*/
        bind(fd,(struct sockaddr *)&ans,sizeof ans);
        n=sizeof ans;
        //n1=sizeof ins;
        while(1)
        {
                strcpy(ip,"");
                FILE *fp=fopen("anscache.txt","r+");
                recvfrom(fd,host,sizeof host,0,(struct sockaddr *)&ans,&n);
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
                        strcpy(ip,"ERROR:404 NOT FOUND");
                }
                fclose(fp);
                sendto(fd,ip,sizeof ip,0,(struct sockaddr *)&ans,n);
        }
        return 0;
}
