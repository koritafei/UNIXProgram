/**
 * @file statdemo.cc
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

#define MAJOR(a) (unsigned short)(a) >> 8
#define LOWER(a) (unsigned short)(a) & 0xFF

int FileType(struct stat *sbuf) {
  int flag = 0;
  printf("file type : ");
  mode_t mode;
  mode = sbuf->st_mode;
  switch (mode & S_IFMT) {
  case S_IFIFO:
    printf("named pipe (fifo)\n");
    break;
  case S_IFCHR:
    printf("character special\n");
    break;
  case S_IFDIR:
    printf("directory\n");
    break;
  case S_IFBLK:
    flag = 1;
    printf("block special\n");
    break;
  case S_IFREG:
    printf("regular\n");
    break;
  case S_IFLNK:
    printf("symbolic link\n");
    break;
  case S_IFSOCK:
    printf("socket\n");
    break;
  default:
    printf("unknown\n");
    break;
  }

  return flag;
}

int main(int argc, char **argv) {
  if (2 < argc) {
    ERR_EXIT("param is lack");
  }
  struct stat sbuf;

  if (-1 == stat(argv[1], &sbuf)) {
    ERR_EXIT("stat");
  }

  printf("file name : %s\n", argv[1]);
  printf("inode %d, major : %d, minor %d\n", sbuf.st_ino, MAJOR(sbuf.st_dev),
         LOWER(sbuf.st_dev));

  if (FileType(&sbuf)) {
    printf("device number major %d, minor %d\n", MAJOR(sbuf.st_rdev),
           LOWER(sbuf.st_rdev));
  }

  printf("file perssion %o\n", sbuf.st_mode & 07777);

  return 0;
}
