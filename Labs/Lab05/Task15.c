#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main() {
    int fd;
    char buffer[BUFFER_SIZE];

    fd = open("input.txt", O_RDWR);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    int bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read == -1) {
        perror("Error reading file");
        close(fd);
        return 1;
    }
    buffer[bytes_read] = '\0';

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        close(fd);
        return 1;
    }

    if (pid == 0) {
        const char *new_content = "Processed by child process\n";
        write(fd, new_content, sizeof("Processed by child process\n") - 1);

        execlp("cat", "cat", "input.txt", NULL);
        perror("execlp failed");
        exit(1);
    } else {
        wait(NULL);
    }

    close(fd);
    return 0;
}
