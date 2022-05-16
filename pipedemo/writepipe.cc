/**
 * @file writepipe.cc
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
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <csignal>
#include <cstdlib>

#define ERR_EXIT(m)                                                            \
  do {                                                                         \
    perror(m);                                                                 \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

int main(int argc, char **argv) {
  mkfifo("tp", 0644);

  int infd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC);

  if (-1 == infd) {
    ERR_EXIT("open error");
  }

  int outfd = open("tp", O_RDONLY);
  if (-1 == outfd) {
    ERR_EXIT("open error");
  }

  char buf[1024];
  int  n;
  while (0 < (n = read(infd, buf, 1024))) {
    write(outfd, buf, n);
  }

  close(infd);
  close(outfd);
  unlink("tp");
  return 0;
}
