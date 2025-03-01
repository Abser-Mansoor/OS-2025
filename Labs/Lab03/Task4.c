#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s D:/abseruni\n", argv[0]);
        return 1;
    }

    struct stat fileStat;
    if (stat(argv[1], &fileStat) == -1) {
        perror("Error checking status");
        return 1;
    }

    if (S_ISREG(fileStat.st_mode)) {
        printf("%s is a file\n", argv[1]);
    } else if (S_ISDIR(fileStat.st_mode)) {
        printf("%s is a directory\n", argv[1]);
    } else {
        printf("%s is of unknown type\n", argv[1]);
    }

    return 0;
}
