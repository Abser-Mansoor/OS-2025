#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

#define lock(mtx) pthread_mutex_lock(&mtx);
#define unlock(mtx) pthread_mutex_unlock(&mtx);

#define BUFFER 10
#define CHEFS 2
#define CUSTOMERS 5

volatile sig_atomic_t flag = 1;
pthread_mutex_t mtx;
sem_t empty, full;

int servings[BUFFER] = {0};

void *chef(void *arg) {
  int idx = (long)arg;

  while (flag) {
    sem_wait(&empty);
    lock(mtx);
    for (int i = 0; i < BUFFER; ++i) {
      if (servings[i])
        continue;
      servings[i] = rand() % 100;
      printf("%d cooked %d\n", idx, servings[i]);
      break;
    }
    unlock(mtx);
    sem_post(&full);
    sleep(rand() % 2);
  }
}

void *customer(void *arg) {
  int idx = (long)arg;

  while (flag) {
    sem_wait(&full);
    lock(mtx);
    for (int i = 0; i < BUFFER; ++i) {
      if (!servings[i])
        continue;
      printf("%d eating %d\n", idx, servings[i]);
      servings[i] = 0;
      break;
    }
    unlock(mtx);
    sem_post(&empty);
    sleep(rand() % 4);
  }
}

void sig_handler(int sig) {
  if (sig == SIGINT)
    flag = 0;
}

int main() {
  pthread_t chefs[CHEFS], customers[CUSTOMERS];

  pthread_mutex_init(&mtx, NULL);
  sem_init(&empty, 0, BUFFER);
  sem_init(&full, 0, 0);

  for (int i = 0; i < CHEFS; ++i)
    pthread_create(&chefs[i], NULL, chef, (void *)i);
  for (int i = 0; i < CUSTOMERS; ++i)
    pthread_create(&customers[i], NULL, customer, (void *)i);

  for (int i = 0; i < CHEFS; ++i)
    pthread_join(chefs[i], NULL);

  for (int i = 0; i < CUSTOMERS; ++i)
    pthread_join(customers[i], NULL);

  pthread_mutex_destroy(&mtx);
  sem_destroy(&empty);
  sem_destroy(&full);

  return 0;
}
