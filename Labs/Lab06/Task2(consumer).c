#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_FILE "myfifo"

int main() {
    int fd;
    char buffer[100];

    fd = open(FIFO_FILE, O_RDONLY);
    if (fd == -1) {
        perror("Error opening FIFO for reading");
        return 1;
    }

    int num_bytes = read(fd, buffer, sizeof(buffer));
    if (num_bytes > 0) {
        printf("Consumer: Received message: %s", buffer);
    } else {
        printf("Consumer: No data received\n");
    }

    close(fd);

    return 0;
}
