#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<time.h>
int main()
{
  FILE *fp,*fp1;
  int b[100]={0},k=0,flag=0,index,n,c_sock,flag1=2,c;
  char a[100];
  struct sockaddr_in client;
  memset(&client, 0, sizeof(client));
  c_sock = socket(AF_INET, SOCK_STREAM, 0);
  client.sin_family = AF_INET;
  client.sin_port = htons(9009);
  client.sin_addr.s_addr = INADDR_ANY;
  if(connect(c_sock, (struct sockaddr*)&client, sizeof(client))==-1)
  {
    printf("Connection error");
    exit(1);
  }
  fp=fopen("file2.txt","r");
  printf("INFORMATION IN THE FILE\n");
  while((c=fgetc(fp))!=EOF)
  {
    printf("%c",c);
    for(int i=0;i<k;i++)
    {
      if(a[i]==c)
      {
         index=i;
         flag=1;
         break;
      }
      else
         flag=0;
    }
    if(flag==1)
       b[index]=b[index]+1;
    else
    {
      a[k]=c;
      b[k]=b[k]+1;
      k++;
    } 
  }
  fclose(fp);
  for(int i=0;i<255;i++)
  {
    if(pow(2,i)<=k && pow(2,i+1)>=k)
    {
      n=i+1;
      break;
    }
  }
  printf("\nFIXED LENGTH => %d\n",n);
  send(c_sock,a,sizeof(a),0);
  send(c_sock,&k,sizeof(k),0);
  send(c_sock,&n,sizeof(n),0);
  int code[k][n],val=1;
  for(int i=0;i<n;i++)
  {
    val=1;
    for(int j=0;j<k;j++)
    {
      int p=pow(2,n-i-1);
      if(j%p==0)
      {
          if(val==0)
             val=1;
          else
             val=0;
         code[j][i]=val;
       }
       else
         code[j][i]=val;
    }
  }
  send(c_sock,code,sizeof(code),0);
  int ind;
  fp=fopen("file2.txt","r");
  fp1=fopen("encoded.txt","w");
  while((c=fgetc(fp))!=EOF)
  {
     for(int i=0;i<k;i++)
     {
       if(a[i]==c)
       {
          ind=i;
          break;
       }
     }
     for(int i=0;i<n;i++)
     {
       fprintf(fp1,"%d",code[ind][i]);
     }
  }
  fclose(fp1);
  fclose(fp);
  fp1=fopen("encoded.txt","r");
  printf("\nENCODED DATA :\n-------------------\n");
  while((c=fgetc(fp1))!=EOF)
  {
    printf("%c",c);
    send(c_sock,&c,sizeof(c),0);
  }
  printf("\n");
  send(c_sock,&flag1,sizeof(flag1),0);
  fclose(fp1);
  printf("\nCHARACTER   FREQUENCY    CODE\n");
  printf("------------------------------------\n");
  for(int i=0;i<k;i++)
  {
   printf("%c\t|\t%d\t|",a[i],b[i]);
   for(int j=0;j<n;j++)
    printf("%d",code[i][j]);
   printf("\n");
  }
  close(c_sock);
   return 0;
}
