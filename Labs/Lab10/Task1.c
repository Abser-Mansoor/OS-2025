#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

sem_t empty, full;
pthread_mutex_t mtx;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

void *producer(void *arg)
{
  int item;
  while (1)
  {
    item = rand() % 100; // Generate a random item to produce
    sem_wait(&empty);
    // sem_wait(&mutex);
    pthread_mutex_lock(&mtx);

    buffer[in] = item;
    printf("Produced: %d\n", item);
    in = (in + 1) % BUFFER_SIZE;

    // sem_post(&mutex);
    pthread_mutex_unlock(&mtx);
    sem_post(&full);
    sleep(rand() % 3); // Simulate some processing time
  }
}

void *consumer(void *arg)
{
  int item;
  while (1)
  {
    sem_wait(&full);
    // sem_wait(&mutex);
    pthread_mutex_lock(&mtx);

    item = buffer[out];
    printf("Consumed: %d\n", item);
    out = (out + 1) % BUFFER_SIZE;

    // sem_post(&mutex);
    pthread_mutex_unlock(&mtx);
    sem_post(&empty);
    sleep(rand() % 3); // Simulate some processing time
  }
}

int main()
{
  pthread_t producer_thread, consumer_thread;

  // Initialize semaphores
  // sem_init(&mutex, 0, 1);
  pthread_mutex_init(&mtx, NULL);
  sem_init(&empty, 0, BUFFER_SIZE);
  sem_init(&full, 0, 0);

  // Create producer and consumer threads
  pthread_create(&producer_thread, NULL, producer, NULL);
  pthread_create(&consumer_thread, NULL, consumer, NULL);

  // Join threads
  pthread_join(producer_thread, NULL);
  pthread_join(consumer_thread, NULL);

  // Destroy semaphores
  // sem_destroy(&mutex);
  pthread_mutex_destroy(&mtx);
  sem_destroy(&empty);
  sem_destroy(&full);

  return 0;
}
