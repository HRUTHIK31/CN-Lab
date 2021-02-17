#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<strings.h>
int main()
{
int s_sock;
int count=1;
char buf[20];
char buff[20];
s_sock=socket(AF_INET,SOCK_DGRAM,0);
struct sockaddr_in server,other;
 server.sin_family=AF_INET;
 server.sin_port=htons(9009);
 server.sin_addr.s_addr=INADDR_ANY;
 bind(s_sock,(struct sockaddr*)&server,sizeof(server));
 int i=1;

 while(i==1)
 {
   
 
   if(i==1)
   {
   if((count%2)==1)
   {
   printf("Receiving message \n");
    socklen_t add;
 add=sizeof(other);
 recvfrom(s_sock,buf,sizeof(buf),0,(struct sock_addr*)&other,&add);
 printf("msg from client:%s \n",buf);
 count=count+1;
   }
   else
   {
    printf("Enter 1 to send a message and 0 to exit \n");
      scanf("%d",&i);
    scanf("%s",buff);
    sendto(s_sock,buff,sizeof(other),0,(struct sockaddr*)&other,sizeof(other));
     printf("server to client msg:%s \n",buff);
     count=count+1;
   }
   }
    
 }
 close(s_sock);
 return 0;
 }
 
