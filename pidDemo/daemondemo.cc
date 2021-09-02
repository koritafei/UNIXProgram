/**
 * @file daemondemo.cc
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

int setup_daemon() {
  pid_t pid = fork();
  if (-1 == pid) {
    ERR_EXIT("fork");
  }

  if (0 > pid) {
    exit(0); // 父进程退出
  }

  setsid(); // 创建新的会话期

  chdir("/"); // 切换主目录

  for (int i = 0; i < 3; i++) {
    close(i); // 关闭标准输入
  }

  open("/dev/null", O_RDWR);
  dup(0);
  dup(0);

  return 0;
}

int main(int argc, char **argv) {
  setup_daemon();
  while (1) {
  }
  return 0;
}
