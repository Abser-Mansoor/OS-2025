#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s task3file.txt\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "a");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    time_t now = time(NULL);
    fprintf(file, "\nUpdated on: %s", ctime(&now));
    
    fclose(file);
    printf("Timestamp appended to %s\n", argv[1]);
    
    return 0;
}
