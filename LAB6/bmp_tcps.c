#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>
int main()
{
int s_sock,c_sock,i;
s_sock=socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in server,other;
memset(&server,0,sizeof(server));
memset(&other,0,sizeof(other));
server.sin_family=AF_INET;
server.sin_port=htons(10000);
server.sin_addr.s_addr=INADDR_ANY;
socklen_t add;
bind(s_sock,(struct sockaddr*)&server,sizeof(server));
listen(s_sock,100);
add=sizeof(other);
c_sock=accept(s_sock,(struct sockaddr *)&other,&add);
FILE *fp;
fp = fopen("destination.bmp","w");
int flag = 0;
char buf[1];
char endoffile[1];
while (flag ==0)
{
recv(c_sock,endoffile,sizeof(endoffile),0);
if(endoffile[0]=='1') 
flag =1;
else
{
recv(c_sock,buf,sizeof(buf),0);
fprintf(fp,"%c",buf[0] );
}
}
fclose(fp);
printf("File Received successfully\n");
close(c_sock);
return 0;
}

