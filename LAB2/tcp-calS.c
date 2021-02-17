#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
int main()
{
int s_sock,c_sock;
char buf[100]="Enter the operator for the operation please enter  + or - or * or /";
char buf1[100]="Please enter the operands a and b";
s_sock=socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in server,other;
memset(&server,0,sizeof(server));
memset(&other,0,sizeof(other));
server.sin_family=AF_INET;
server.sin_port=htons(9000);
server.sin_addr.s_addr=INADDR_ANY;
socklen_t add;
bind(s_sock,(struct sockaddr*)&server,sizeof(server));
listen(s_sock,10);
add=sizeof(other);
c_sock=accept(s_sock,(struct sockaddr*)&other,&add);

int i=1;
 char n[1];
    char c[1];
     int a[2];
          int r[1];
 n[0]='1';
 while(1)
 {


recv(c_sock,n,sizeof(n),0);

   if(n[0]=='1')
   {
 
  send(c_sock,buf,sizeof(buf),0);

recv(c_sock,c,sizeof(c),0);
  
   
  send(c_sock,buf1,sizeof(buf1),0);

recv(c_sock,a,sizeof(a),0);

         switch (c[0]) {
    case '+':
       r[0]= (a[0]+a[1]);  
  send(c_sock,r,sizeof(r),0);
        break;
    case '-':
  r[0]= a[0]-a[1];  
  send(c_sock,r,sizeof(r),0);
        break;
    case '*':
 r[0]= a[0]*a[1];  
  send(c_sock,r,sizeof(r),0);
        break;
    case '/':
 r[0]= a[0]/a[1];  
  send(c_sock,r,sizeof(r),0);
        break;
        // operator doesn't match any case constant
    default:
        printf("Error! operator is not correct");
    };
    }
    else
    {
    break;
    }
    
    


 
 }
 

close(s_sock);
return 0;
}
