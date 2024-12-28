#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 80
#define HOST "127.0.0.1"
int main() {
   int self = socket(AF_INET, SOCK_STREAM, 0);
   if (self < 0)
      return 1;
   struct sockaddr_in srv;

   srv.sin_port = htons(PORT);
   srv.sin_family = AF_INET;

   printf("%s\n", HOST);
   if (inet_pton(AF_INET, HOST, &srv.sin_addr) < 0)
      return 2;

   int status = connect(self, (struct sockaddr *)(&srv), sizeof(srv));

   if (status < 0)
      return 3;

   const char *msg = "GET / HTTP1.1";
   send(self, msg, strlen(msg), 0);

   char buff[2048] = {0};
   printf("%lu\n", sizeof(buff));
   unsigned long rea = read(self, buff, sizeof(buff) - 1);
   printf("%s\n|%lu\n", buff, rea);

   close(self);
}
