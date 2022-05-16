/**
 * @file sigqueeudemo_recv.cc
 * @author koritafei (koritafei@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-09-01
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <bits/types/sigset_t.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <csignal>

#define ERR_EXIT(m)                                                            \
  do {                                                                         \
    perror(m);                                                                 \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

void handler(int sig, siginfo_t *info, void *arg) {
  printf("recv sig = %d, data = %d\n", sig, info->si_value.sival_int);
  sleep(4);
}

int main(int argc, char **argv) {
  struct sigaction act;

  act.sa_sigaction = handler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_SIGINFO;
  // sigaddset(&act.sa_mask, SIGQUIT);

  // sigset_t s;
  // sigemptyset(&s);
  // sigaddset(&s, SIGINT);
  // sigprocmask(SIG_BLOCK, &s, NULL);

  if (0 > sigaction(SIGINT, &act, NULL)) {
    ERR_EXIT("signal action");
  }

  for (;;) {
    pause();
  }

  return 0;
}