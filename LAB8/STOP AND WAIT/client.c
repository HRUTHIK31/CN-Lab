#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
int main()
{	
	int c_sock;
	char buf[2],text[50],end[2];
	end[1] = '\0';
	buf[1] = '\0';
	c_sock = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in client;
	memset(&client,0,sizeof(client));
	client.sin_family = AF_INET;
	client.sin_port = htons(9009);
	client.sin_addr.s_addr = INADDR_ANY;
	if(connect(c_sock,(struct sockaddr*)&client,sizeof(client))==-1)
	{
		printf("Connection failure\n");
		exit(0);
	}
	printf("Enter text to be sent: ");
	gets(text);	
	for(int i = 0;i < strlen(text);i++)
	{
		buf[0] = text[i];
		char ack[2];
		end[0] = '0';
		send(c_sock,end,sizeof(end),0);
		send(c_sock,buf,sizeof(buf),0);
		recv(c_sock,ack,sizeof(ack),0);
		printf("Ack-> %c \n",ack[0]);
		if(ack[0] == '0')
			i-=1;
	}
	end[0] = '1';
	send(c_sock,end,sizeof(end),0);
	printf("\nMessage sent\n");
	close(c_sock);
	return 0;
}
