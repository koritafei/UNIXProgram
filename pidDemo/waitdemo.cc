#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define ERR_EXIT(m)                                                            \
  do {                                                                         \
    perror(m);                                                                 \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

int main(int argc, char **argv) {
  printf("main process pid = %d\n", getpid());
  pid_t pid = fork();
  if (-1 == pid) {
    ERR_EXIT("fork");
  }

  if (0 < pid) {
    printf("this is parent process pid = %d , child pid = %d\n", getpid(), pid);
    int status;
    pid_t p = wait(&status);
    printf("child process exit pid=%d, status = %d\n", p, status);
  } else if (0 == pid) {
    sleep(3);
    printf("this is child process pid = %d\n", getpid());
    exit(100);
  }

  // int status;
  // pid_t p = wait(&status);
  // printf("child process exit pid=%d, status = %d\n", p, status);

  return 0;
}
