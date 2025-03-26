#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *runner(void *parameters) {
    int i, upper = *(int *)parameters;
    int *result = malloc(sizeof(int)); // Allocate memory to store the sum
    *result = 0;

    if (upper > 0) {
        for (i = 1; i <= upper; i++) {
            *result += i;
        }
    }

    pthread_exit((void *) result); // Exit thread with result
}

int main(int argc, char *argv[]) {
    pthread_t threadID;
    pthread_attr_t attributes;
    int num = 100;
    void *exit_status;

    pthread_attr_init(&attributes);
    pthread_create(&threadID, &attributes, runner, (void *)&num);
    pthread_join(threadID, &exit_status);

    int sum = *(int *)exit_status; // Retrieve result
    free(exit_status); // Free allocated memory

    printf("sum = %d\n", sum);
    exit(0);
}


