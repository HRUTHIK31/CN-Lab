#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
int main()
{
int c_sock;

c_sock=socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in client;
memset(&client,0,sizeof(client));
client.sin_family=AF_INET;
client.sin_port=htons(9000);
client.sin_addr.s_addr=INADDR_ANY;
if(connect(c_sock,(struct sockaddr*)&client,sizeof(client))==-1)
{
printf("server is busy connection failure");
return 0;
}

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

  send(c_sock,n,sizeof(n),0);
     

 
recv(c_sock,buff,sizeof(buff),0);
     printf("SERVER: %s ",buff);
     


scanf("%s",op);
       send(c_sock,op,sizeof(op),0);
 
     recv(c_sock,buff1,sizeof(buff1),0);
     
     printf("SERVER:%s \n",buff1);
     

     
     scanf("%d%d",&oper[0],&oper[1]);
     
            send(c_sock,oper,sizeof(oper),0);
      
      recv(c_sock,result,sizeof(result),0);
     
      
      printf("The final result is %d  \n",result[0]);
     
  }
  else{
  break;
      }
  }



close(c_sock);
return 0;
}
