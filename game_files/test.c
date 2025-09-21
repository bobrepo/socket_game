#include <pthread.h>
#include <stdio.h>

typedef struct dat {
  int a, b;
  int res;
} dat;

void *foo(void *arg) {
  dat *vv = (dat *)arg;
  vv->res = vv->a + vv->b;
  printf("hello, world!: %d\n", vv->res);
  return NULL;
}

int main() {
  pthread_t thread1;
  dat values;
  values.a = 5;
  values.b = 5;
  pthread_create(&thread1, NULL, foo, &values);
  pthread_join(thread1, NULL);

  printf("%d", values.res);
  return 0;
}
