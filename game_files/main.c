#include <arpa/inet.h>
#include <bits/pthreadtypes.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#define buffer_size 16
#define PORT 5001

int inp_values[4];
int run = 1;

void *get_inp_value(void *arg) {
  char temp[4];
  int index = 0;
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in serveraddr;
  char *buffer = (char *)malloc(sizeof(char) * buffer_size);
  int si = sizeof(serveraddr);
  memset(&serveraddr, 0, sizeof(serveraddr));

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(PORT);

  bind(sock, (struct sockaddr *)&serveraddr, si);

  while (run) {

    recvfrom(sock, buffer, buffer_size, 0, NULL, 0);
    for (int i = 0; i < 4; i++) {

      for (int j = 0; j < 4; j++) {

        temp[j] = buffer[index++];
      }
      inp_values[i] = atoi(temp);
    }

    index = 0;
    for (int i = 0; i < 4; i++) {
      printf("%d\t", inp_values[i]);
    }
    printf("\n");
  }

  return NULL;
}

int main() {
  pthread_t inp_thread;

  pthread_create(&inp_thread, NULL, get_inp_value, NULL);
  /*
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
  */

  scanf("%d", &run);
  pthread_join(inp_thread, NULL);

  return 0;
}
