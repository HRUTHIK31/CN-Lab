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
	int c_sock, w_size, ws[1];
	char buf[2], text[50], ch, end[2];
	buf[1] = '\0';
	end[0] = '0';
	end[1] = '\0';

	c_sock = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in client;
	memset(&client,0,sizeof(client));
	
	client.sin_family = AF_INET;
	client.sin_port = htons(9009);
	client.sin_addr.s_addr = INADDR_ANY;

	if(connect(c_sock,(struct sockaddr*)&client,sizeof(client))==-1)
	{
		printf("\nConnection failure\n");
		exit(0);
	}
	
	printf("\nEnter window size:\t");
	scanf("%d",&w_size);

	scanf("%c",&ch);

	ws[0] = w_size;
	send(c_sock, ws, sizeof(ws), 0);

	printf("\nEnter text to be sent: ");
	gets(text);

	for(int i = 0;i < strlen(text);i++)
	{
		send(c_sock, end, sizeof(end), 0);
		for(int j = 0;j < w_size;j++)
		{
			printf("Sending --> %c\n", text[i+j]);
			buf[0] = text[i+j];
			send(c_sock, buf, sizeof(buf), 0);
		}
		int ack_check = -1;
		char ack[2];
		for(int j = 0;j < w_size;j++)
		{
			recv(c_sock, ack, sizeof(ack), 0);
			printf("Received Acknowledgment -> %s\n", ack);
			if(ack[0] == '0')
			{
				ack_check = j;
				j = w_size;
			}
		}
		if(ack_check == -1) 
			i = i + w_size-1;
		else 
			i = i + ack_check-1;
	}
	end[0] = '1';
	send(c_sock,end,sizeof(end),0);
	printf("\nText sent\n");

	close(c_sock);

	return 0;
}
