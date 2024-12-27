#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
int main() {
   int self = socket(AF_INET, SOCK_STREAM, 0);
   if (self < 0)
      return 1;
   struct sockaddr_in srv;

   srv.sin_port = 80;
   srv.sin_family = AF_INET;

   if (inet_pton(AF_INET, "", &srv.sin_addr) < 0)
      return 2;

   int status = connect(self, (struct sockaddr *)(&srv), sizeof(srv));

   if (status < 0)
      return 3;

   const char *msg = "";
   send(self, msg, strlen(msg), 0);
   close(self);
}
