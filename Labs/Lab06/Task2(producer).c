#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE "myfifo"

int main() {
    int fd;
    char write_msg[100];

    mkfifo(FIFO_FILE, 0666);

    printf("Producer: Enter a message: ");
    fgets(write_msg, sizeof(write_msg), stdin);

    fd = open(FIFO_FILE, O_WRONLY);
    if (fd == -1) {
        perror("Error opening FIFO for writing");
        return 1;
    }

    write(fd, write_msg, strlen(write_msg) + 1);
    printf("Producer: Message sent!\n");

    close(fd);

    return 0;
}
