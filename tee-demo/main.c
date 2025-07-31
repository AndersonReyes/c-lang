
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  // Tries to emulate a basic tee command that writes to stdout and file
  // descriptor using system calls

  if (argc < 2 || argc > 3) {
    printf("invalid arguments. Expected: tee-demo {file} with optional -a for "
           "append mode to file");
    exit(1);
  }

  int fd;
  int flags = O_CREAT | O_WRONLY;

  if (argc == 3 && strcmp(argv[2], "-a") == 0) {
    printf("Output to stdout and %s in append mode\n", argv[1]);
    flags |= O_APPEND;
  } else {
    printf("Output to stdout and %s\n", argv[1]);
    flags |= O_TRUNC;
  }

  fd = open(argv[1], flags, S_IRWXU | S_IRGRP | S_IROTH);

  if (fd == -1)
    printf("Failed to open %s: %s", argv[1], strerror(errno));

  int nread;
  int nwritten;
  int bufsize = 1024;

  char buf[bufsize + 1];

  while ((nread = read(STDIN_FILENO, buf, bufsize)) > 0) {
    buf[bufsize] = '\0';

    if (write(STDOUT_FILENO, buf, nread) != nread) {
      printf("Failed to write to stdout: %s", strerror(errno));
      exit(1);
    }

    if (write(fd, buf, nread) != nread) {
      printf("Failed to write to %s: %s", argv[1], strerror(errno));
      exit(1);
    }
  }

  if (close(fd) == -1) {
    printf("Failed to close %s: %s", argv[1], strerror(errno));
    exit(1);
  }

  return 0;
}
