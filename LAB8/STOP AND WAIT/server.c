#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main()
{
	int s_sock, c_client, len=0;
	char text[50], end[2], buf[2], ack[2];
	s_sock=socket(AF_INET,SOCK_STREAM,0); 
	struct sockaddr_in server,other;
	memset(&server,0,sizeof(server));
	memset(&other,0,sizeof(other));
	server.sin_family = AF_INET;
	server.sin_port = htons(9009);
	server.sin_addr.s_addr = INADDR_ANY;
	socklen_t addr_size;
	bind(s_sock,(struct sockaddr*)&server,sizeof(server));
	listen(s_sock,5);
	addr_size = sizeof(other);
	c_client = accept(s_sock,(struct sockaddr*)&other,&addr_size);
	recv(c_client,end,sizeof(end),0);
	while(end[0] == '0')
	{
		recv(c_client,buf,sizeof(buf),0);
		printf("Buffer-> %c",buf[0]);
		char ack1[2];
		printf("\nEnter Ack->");
		gets(ack1);
		ack[0] = ack1[0];
		send(c_client,ack,sizeof(ack),0);
		if(ack[0] == '1')
		{
			text[len++] = buf[0];
		}
		recv(c_client,end,sizeof(end),0);
	}
	text[len++] = '\0';
	printf("\nReceived message: ");
	for(int i = 0;i < len;++i)
		printf("%c",text[i]);
	printf("\n");
	close(s_sock);
	close(c_client);
	return 0;
}
