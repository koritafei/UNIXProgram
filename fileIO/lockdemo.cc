#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <stdio.h>

#define ERR_EXIT(m)                                                            \
  do {                                                                         \
    perror(m);                                                                 \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

int main(int argc, char **argv) {
  int fd;
  fd = open(argv[1], O_RDONLY);
  if (-1 == fd) {
    ERR_EXIT("open fail");
  }

  struct flock lock;
  memset(&lock, 0, sizeof(lock));

  lock.l_type = F_WRLCK;
  lock.l_whence = SEEK_SET;
  lock.l_start = 0;
  lock.l_len = 0;

  if (0 == fcntl(fd, F_SETLK, &lock)) {
    printf("lock sucess!");
    printf("press any key to unlock");
    lock.l_type = F_UNLCK;
    if (0 == fcntl(fd, F_SETLK, &lock)) {
      printf("unlock sucess!\n");
    } else {
      ERR_EXIT("unlock");
    }
  } else {
    ERR_EXIT("lock fail");
  }

  return 0;
}
