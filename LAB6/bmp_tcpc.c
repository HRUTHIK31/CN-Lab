#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<time.h>
void transfer(int);
int main()
{
int c_sock;
time_t start ,end, diff;
c_sock=socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in client;
memset(&client,0,sizeof(client));
client.sin_family=AF_INET;
client.sin_port=htons(10000);
client.sin_addr.s_addr=INADDR_ANY;
if(connect(c_sock,(struct sockaddr*)&client,sizeof(client))==-1)
{
printf("connection failed Sorry!!");
}
char endoffile[1]="0";
char buf[1];
FILE *fp;
fp = fopen("seltos1.bmp","rb");
time(&start);

	while(!feof(fp))
	{
		fscanf(fp,"%c",&buf[0]);
		send(c_sock,endoffile,sizeof(endoffile),0);
		send(c_sock,buf,sizeof(buf),0);
	}
endoffile[0]='1';
send(c_sock,endoffile,sizeof(endoffile),0);
close(c_sock);


time(&end);
printf("Time taken %ld seconds to transfer\n",diff=end-start);

printf("file sent succesfully \n");
fclose(fp);
return 0;
}

