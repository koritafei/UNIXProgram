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

void handler(int sig) { printf("recv a sig = %d\n", sig); }

int main(int argc, char **argv) {
  signal(SIGINT, handler);
  for (;;)
    ;
  return 0;
}
