#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<strings.h>
int main()
{
int count=1;
int c_sock;
char buf1[20]="Hello server";  //client message
char buff1[20];
c_sock=socket(AF_INET,SOCK_DGRAM,0);
 struct sockaddr_in client; //contains familyname  ,portnum,ip address
 client.sin_family=AF_INET;
 client.sin_port=htons(9009);
 client.sin_addr.s_addr=INADDR_ANY;
 int i=1;
 while(i==1)
 {

   if(i==1)
   {
     
    if((count%2)==1)
    
    {
       printf("Enter 1 to send a message and 0 to exit \n");
     scanf("%d",&i);
    scanf("%s",buf1);
    sendto(c_sock,buf1,sizeof(buf1),0,(struct sockaddr*)&client,sizeof(client));
     printf("client to server msg:%s \n",buf1);
     count=count+1;
   }
   
     
   else{
     printf("Receiving message \n");
     socklen_t add;
 add=sizeof(client);
 recvfrom(c_sock,buff1,sizeof(buff1),0,(struct sock_addr*)&client,&add);
 printf("msg from server:%s \n",buff1);
 count=count+1;
   } 

   }
   
 }
 
 close(c_sock);
 return 0;
 }
