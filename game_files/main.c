#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define buffer_size 16
#define PORT 5001

int main() {
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in serveraddr;
  char *buffer = (char *)malloc(sizeof(char) * buffer_size);
  int si = sizeof(serveraddr);
  memset(&serveraddr, 0, sizeof(serveraddr));

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(PORT);

  bind(sock, (struct sockaddr *)&serveraddr, si);

  recvfrom(sock, buffer, buffer_size, 0, NULL, 0);
  printf("%s", buffer);

  return 0;
}
