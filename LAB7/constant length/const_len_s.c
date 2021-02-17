#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<time.h>
int main()
{
  FILE *fp;
  int s_sock,c_sock;
  char a[100];
  int d,p=0,m=0;
  char c;
  int k,n,flag=0;
  struct sockaddr_in server, other;
  memset(&server, 0, sizeof(server));
  memset(&other, 0, sizeof(other));
  s_sock = socket(AF_INET, SOCK_STREAM, 0);
  server.sin_family = AF_INET;
  server.sin_port = htons(9009);
  server.sin_addr.s_addr = INADDR_ANY;
  if(bind(s_sock, (struct sockaddr*)&server, sizeof(server))==-1)
  {
    printf("Error in binding..\n");
    exit(1);
  }
  listen(s_sock, 10);
  socklen_t add;
  add = sizeof(other); 
  c_sock = accept(s_sock, (struct sockaddr*)&other, &add);
  recv(c_sock,a,sizeof(a),0);
  recv(c_sock,&k,sizeof(k),0);
  recv(c_sock,&n,sizeof(n),0);
  char b[n];
  int code[k][n];
  recv(c_sock,code,sizeof(code),0);
  fp = fopen("decoded.txt","w");
  recv(c_sock, &d, sizeof(d), 0);
  while(d!=2)
  {
    fputc(d,fp);
    recv(c_sock, &d, sizeof(d), 0);
  }
  fclose(fp);
  printf("\nCHARACTER   CODE\n");
  printf("-----------------------\n");
  for(int i=0;i<k;i++)
  {
   printf("%c\t|\t",a[i]);
   for(int j=0;j<n;j++)
    printf("%d",code[i][j]);
   printf("\n");
  }
  printf("\nDECODED TEXT : \n");
  printf("-------------------------\n");
  fp=fopen("decoded.txt","r");
  while((c=fgetc(fp))!=EOF)
  {
    b[p++]=c;
    if(p!=0 && p%n==0)
    {
      for(int i=0;i<k;i++)
      {
         flag=0;
         m=0;
         for(int j=0;j<n;j++)
         {
           if(code[i][j]==b[j]-48)
           {
             flag=1;
             m++;
           }
           else
              flag=0;
           if(flag==1 && m==n)
           {
              printf("%c",a[i]);
              break;
           }
         }
      }
      p=0;
    }
  }
  printf("\n");
  fclose(fp);
  close(s_sock);
  return 0;
}  
