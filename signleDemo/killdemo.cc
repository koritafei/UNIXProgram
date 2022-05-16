/**
 * @file killdemo.cc
 * @author koritafei (koritafei@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-09-01
 *
 * @copyright Copyright (c) 2021
 *
 */

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

void handler(int sig) { printf("recv a sig = %d\n", sig); }

int main(int argc, char **argv) {
  signal(SIGUSR1, handler);
  pid_t pid = fork();

  if (-1 == pid) {
    ERR_EXIT("fork");
  }

  if (0 == pid) {
    pid = getpgrp();
    kill(-pid, SIGUSR1);
    exit(EXIT_SUCCESS);
  }

  int n = 5;
  do {
    sleep(n);
  } while (n--);

  return 0;
}
