
/**
 * @file signaldemo.cc
 * @author koritafei (koritafei@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-09-01
 *
 * @copyright Copyright (c) 2021
 *
 */

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

void handler(int sig) { printf("recv a sig = %d\n", sig); }

void printsigset(sigset_t *set) {
  int i;
  for (i = 1; i < NSIG; i++) {
    if (sigismember(set, i)) {
      putchar('1');
    } else {
      putchar('0');
    }
  }
  printf("\n");
}

int main(int argc, char **argv) {
  sigset_t pset;
  if (SIG_ERR == signal(SIGINT, handler)) {
    ERR_EXIT("signal error");
  }
  for (;;) {
    sigpending(&pset);
    printsigset(&pset);
    sleep(1);
  }

  return 0;
}
