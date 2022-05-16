
#include <csignal>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ERR_EXIT(m)                                                            \
  do {                                                                         \
    perror(m);                                                                 \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

typedef struct {
  int a;
  int b;
} Test;

Test g_data;

void unsafe_func() { printf("%d %d\n", g_data.a, g_data.b); }

void handler(int sig) {
  // printf("recv a sig = %d\n", sig);
  unsafe_func();
  alarm(1);
}

int main(int argc, char **argv) {
  Test zeros = {0, 0};
  Test ones = {1, 1};

  if (signal(SIGALRM, handler) == SIG_ERR) {
    ERR_EXIT("signal");
  }

  g_data = zeros;
  alarm(1);
  for (;;) {
    g_data = zeros;
    g_data = ones;
  }
  return 0;
}
