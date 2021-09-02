/**
 * @file timerdemo.cc
 * @author koritafei (koritafei@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-09-02
 *
 * @copyright Copyright (c) 2021
 *
 */

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
#include <sys/time.h>
#include <unistd.h>

#define ERR_EXIT(m)                                                            \
  do {                                                                         \
    perror(m);                                                                 \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

void handler(int sig) {
  printf("recv a sig = %d\n", sig);
}

int main(int argc, char **argv) {
  if (SIG_ERR == signal(SIGALRM, handler)) {
    ERR_EXIT("signal");
  }

  struct timeval tv_interval = {1, 0};  // 第一次之后间隔时间
  struct timeval tv_val      = {1, 0};  // 第一次间隔时间

  struct itimerval it;
  it.it_interval = tv_interval;
  it.it_value    = tv_val;

  setitimer(ITIMER_REAL, &it, NULL);

  for (int i = 0; i < 1;) {
  }

  struct itimerval oit;
  // setitimer(ITIMER_REAL, &it, &oit);
  getitimer(ITIMER_REAL, &oit);
  printf("%d\t%d\t%d\t%d\n",
         oit.it_interval.tv_sec,
         oit.it_interval.tv_usec,
         oit.it_value.tv_sec,
         oit.it_value.tv_usec);
  return 0;
}
