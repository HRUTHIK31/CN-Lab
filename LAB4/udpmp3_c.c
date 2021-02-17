#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<stdint.h>
#include<math.h>
int main()
{
  int c_sock;
  char buf[100],buffe[100];
  int16_t b[1];
  c_sock=socket(AF_INET,SOCK_DGRAM,0);
  struct sockaddr_in client,other;
  client.sin_family=AF_INET;
  client.sin_port=htons(9009);
  client.sin_addr.s_addr=INADDR_ANY;
  socklen_t a;
  a=sizeof(client);
  FILE *pipeout;
  while(1)
  {
printf("Enter the filename of the mp3 file you want as output.mp3 \n");
pipeout = popen("ffmpeg -y -f s16le -ar 44100 -ac 1 -i - output.mp3", "w");
gets(buffe);
    sendto(c_sock,buffe,sizeof(buffe),0,(struct sockaddr*)&client,sizeof(client));
while(1)
{
 recvfrom(c_sock,b,sizeof(b),0,(struct sockaddr*)&client,&a);
 fwrite(&b[0], 2, 1, pipeout);
}
pclose(pipeout);


  }
  close(c_sock);
return 0;
}
