#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int fd[2];  
    pid_t pid;  
    char write_msg[100];
    char read_msg[100];   

    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) {
        printf("Parent process (PID: %d)\n", getpid());
        printf("Child process (PID: %d)\n", pid);
        close(fd[0]);

        printf("Enter a message to write into the pipe: ");
        fgets(write_msg, sizeof(write_msg), stdin);
        
        write(fd[1], write_msg, strlen(write_msg) + 1);

        close(fd[1]);
    } else {
        printf("Child process running (PID: %d, Parent PID: %d)\n", getpid(), getppid());
        close(fd[1]);

        read(fd[0], read_msg, sizeof(read_msg));

        printf("Child process received: %s\n", read_msg);

        close(fd[0]);
    }

    return 0;
}
