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
  int s_sock;
  char buff[100],bufr2[100];
  int16_t a[1];
  s_sock=socket(AF_INET,SOCK_DGRAM,0);
  struct sockaddr_in server,other;
  server.sin_family=AF_INET;
  server.sin_port=htons(9009);
  server.sin_addr.s_addr=INADDR_ANY;
  bind(s_sock,(struct sockaddr *)&server,sizeof(server));
  socklen_t add;
  add=sizeof(other);
FILE *pipein;

char* extension=".mp3";
int16_t sample;
int count, n=0;
  while(1)
  {
    recvfrom(s_sock,buff,sizeof(buff),0,(struct sockaddr *)&other,&add);

printf("filename client requested is:%s \n",buff);
char command[100];

 snprintf(command, sizeof(command), "ffmpeg -i %s%s -f s16le -ac 1 -",buff,extension);
 
 pipein  = popen(command, "r");
   while(1)
    {
        count = fread(&sample, 2, 1, pipein); // read one 2-byte sample
        if (count != 1) break;
        ++n;

        sample = sample * sin(n * 5.0 * 2*M_PI / 44100.0);
        a[0]=sample;
    sendto(s_sock,a,sizeof(a),0,(struct sockaddr *)&other,sizeof(other));

    }
  pclose(pipein);



  }
  close(s_sock);
return 0;
}
