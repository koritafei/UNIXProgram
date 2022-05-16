#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
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

  int fd = open(argv[1], O_CREAT | O_WRONLY);

  if (-1 == fd) {
    ERR_EXIT("open");
  }

  if (0 < pid) {
    printf("this is parent process pid = %d , child pid = %d\n", getpid(), pid);
    write(fd, "parent\n", 7);
    sleep(3);
  } else if (0 == pid) {
    printf("this is child process pid = %d\n", getpid());
    write(fd, "child\n", 6);
  }

  // close(fd);

  return 0;
}
