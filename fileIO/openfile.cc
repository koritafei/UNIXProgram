/**
 * @file openfile.cc
 * @author koritafei (koritafei@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-08-31
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <cstdlib>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define ERR_EXIT(m)                                                            \
  do {                                                                         \
    perror(m);                                                                 \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

int main(int argc, char **argv) {
  int fd;
  fd = open("./filenoandfile.cc", O_RDONLY);
  if (-1 == fd) {
    fprintf(stderr, "open file error whith msg : %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  fputs("open sucess!", stdout);

  return 0;
}
