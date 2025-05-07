#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>

FILE *file;

char *words[4] = {"Hello", "World", "Goodbye", "727"};

void sig_handler(int sig) {
  if (sig == SIGINT) {
    remove("tmp.txt");
    exit(0);
  }
}

int main() {
  if (signal(SIGINT, sig_handler) == SIG_ERR) {
    perror("failed to create signal");
    exit(1);
  }

  char buffer[BUFSIZ] = {0};
  while (1) {
    file = fopen("tmp.txt", "a+");
    fprintf(file, "%s\n", words[rand() % 4]);
    fclose(file);
    sleep(3);
  }

  return 0;
}
