/**
 * @file readandwritedemo.cc
 * @author koritafei (koritafei@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-08-31
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define ERR_EXIT(m)                                                            \
  do {                                                                         \
    perror(m);                                                                 \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

int main(int argc, char **argv) {

  int infd;
  int outfd;

  if (3 != argc) {
    fprintf(stderr, "Usage %s src dest \n", argv[0]);
    exit(EXIT_FAILURE);
  }

  infd = open(argv[1], O_RDONLY);
  if (-1 == infd) {
    ERR_EXIT("open source error");
  }

  outfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (-1 == outfd) {
    ERR_EXIT("open dest error");
  }

  char buf[1024];
  int nread;
  while (0 < (nread = read(infd, buf, 1024))) {
    write(outfd, buf, nread);
  }

  close(infd);
  close(outfd);
  return 0;
}
