#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<stdint.h>
#include<math.h>
int main()
{
int s_sock,c_sock;
char buf[100];
int16_t a[1];
s_sock=socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in server,other;
memset(&server,0,sizeof(server));
memset(&other,0,sizeof(other));
server.sin_family=AF_INET;
server.sin_port=htons(9005);
server.sin_addr.s_addr=INADDR_ANY;
socklen_t add;
bind(s_sock,(struct sockaddr*)&server,sizeof(server));
listen(s_sock,10);
add=sizeof(other);
c_sock=accept(s_sock,(struct sockaddr*)&other,&add);
FILE *pipein;

char* extension=".mp3";
int16_t sample;
int count, n=0;
 
while(1)
{
recv(c_sock,buf,sizeof(buf),0);
printf("filename client requested is:%s \n",buf);
char command[100];

 snprintf(command, sizeof(command), "ffmpeg -i %s%s -f s16le -ac 1 -",buf,extension);
 
 pipein  = popen(command, "r");
   while(1)
    {
        count = fread(&sample, 2, 1, pipein); // read one 2-byte sample
        if (count != 1) break;
        ++n;

        sample = sample * sin(n * 5.0 * 2*M_PI / 44100.0);
        a[0]=sample;
        send(c_sock,a,sizeof(a),0);

    }
  pclose(pipein);
}
close(s_sock);
return 0;
}
