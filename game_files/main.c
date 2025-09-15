#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

int main() {
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in serveraddr;
  int si = sizeof(serveraddr);
  memcpy(0, &serveraddr, sizeof(serveraddr));

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(5050);

  bind(sock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

  listen(sock, 3);

  nk = accept(sock, (struct sockaddr *)&serveraddr, &si);

  return 0;
}
