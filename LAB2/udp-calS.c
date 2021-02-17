#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<strings.h>
int main()
{

int s_sock;

char buf[100]="Enter the operator for the operation please enter  + or - or * or /";
char buf1[100]="Please enter the operands a and b";

s_sock=socket(AF_INET,SOCK_DGRAM,0);
struct sockaddr_in server,other;
 server.sin_family=AF_INET;
 server.sin_port=htons(9009);
 server.sin_addr.s_addr=INADDR_ANY;
 bind(s_sock,(struct sockaddr*)&server,sizeof(server));
 int i=1;
 char n[1];
    char c[1];
     int a[2];
          int r[1];
 n[0]='1';
 while(1)
 {
 socklen_t add;
 add=sizeof(other);

 recvfrom(s_sock,n,sizeof(n),0,(struct sockaddr*)&other,&add);
  printf("%c",n[0]);
   if(n[0]=='1')
   {
 
     sendto(s_sock,buf,sizeof(buf),0,(struct sockaddr*)&other,sizeof(other));

      recvfrom(s_sock,c,sizeof(c),0,(struct sockaddr*)&other,&add);
  
   
      sendto(s_sock,buf1,sizeof(buf1),0,(struct sockaddr*)&other,sizeof(other));

     recvfrom(s_sock,a,sizeof(a),0,(struct sockaddr*)&other,&add);

         switch (c[0]) {
    case '+':
       r[0]= (a[0]+a[1]);  
            sendto(s_sock,r,sizeof(r),0,(struct sockaddr*)&other,sizeof(other));
        break;
    case '-':
  r[0]= a[0]-a[1];  
            sendto(s_sock,r,sizeof(r),0,(struct sockaddr*)&other,sizeof(other));
        break;
    case '*':
 r[0]= a[0]*a[1];  
            sendto(s_sock,r,sizeof(r),0,(struct sockaddr*)&other,sizeof(other));
        break;
    case '/':
 r[0]= a[0]/a[1];  
            sendto(s_sock,r,sizeof(r),0,(struct sockaddr*)&other,sizeof(other));
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
