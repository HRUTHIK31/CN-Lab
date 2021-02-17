#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<strings.h>
int main()
{
int c_sock;
c_sock=socket(AF_INET,SOCK_DGRAM,0);
struct sockaddr_in client;
 client.sin_family=AF_INET;
 client.sin_port=htons(9009);
 client.sin_addr.s_addr=INADDR_ANY;
 char n[1];
 n[0]='1';
 char buff[100];
 char buff1[100];
      int oper[2];
       char op[1];
             int result[1];
   while(1)
   {
 printf("Enter 1 to start and 0 to exit the chat");
 
scanf("%s",n);
 if(n[0]=='1')
 {

     sendto(c_sock,n,sizeof(n),0,(struct sockaddr*)&client,sizeof(client));
     
  socklen_t add;
 add=sizeof(client);
     recvfrom(c_sock,buff,sizeof(buff),0,(struct sockaddr*)&client,&add);
     printf("SERVER: %s ",buff);
     


scanf("%s",op);
      sendto(c_sock,op,sizeof(op),0,(struct sockaddr*)&client,sizeof(client));
 
     recvfrom(c_sock,buff1,sizeof(buff1),0,(struct sockaddr*)&client,&add);
     
     printf("SERVER:%s \n",buff1);
     

     
     scanf("%d%d",&oper[0],&oper[1]);
     
      sendto(c_sock,oper,sizeof(oper),0,(struct sockaddr*)&client,sizeof(client));
      

      recvfrom(c_sock,result,sizeof(result),0,(struct sockaddr*)&client,&add);
      
      printf("The final result is %d  \n",result[0]);
     
  }
  else{
  break;
      }
  }
   close(c_sock);
   return 0;
}
