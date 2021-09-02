/**
 * @file pipedemo.cc
 * @author koritafei (koritafei@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-09-02
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

#include <csignal>
#include <cstdlib>

#define ERR_EXIT(m)                                                            \
  do {                                                                         \
    perror(m);                                                                 \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

int main(int argc, char **argv) {
  int pipefd[2];
  if (-1 == pipe(pipefd)) {
    ERR_EXIT("pipe");
  }

  pid_t pid = fork();
  if (-1 == pid) {
    ERR_EXIT("fork");
  }

  if (0 == pid) {
    close(pipefd[0]);
    write(pipefd[1], "hello", 5);
    close(pipefd[1]);
    exit(EXIT_SUCCESS);
  }

  char buf[10] = {0};
  close(pipefd[1]);
  read(pipefd[0], buf, 10);
  printf("buf = %s\n", buf);
  close(pipefd[0]);

  return 0;
}
