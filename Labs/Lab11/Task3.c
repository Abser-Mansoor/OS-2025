#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#define lock(mtx) pthread_mutex_lock(&mtx);
#define unlock(mtx) pthread_mutex_unlock(&mtx);

int balance = 0;
pthread_mutex_t mtx;
volatile sig_atomic_t flag = 1;

void *teller(void *arg) {
  int i = (long)arg;

  while (flag) {
    lock(mtx);
    int value = rand() % 1000;
    printf("balance: %d\n", balance);
    printf("teller #%d; value = %d\n", i+1, value);

    if (rand() % 2) {
      balance += value;
    } else {
      balance -= value;
      if (balance < 0) {
        printf("Not enough balance to extract: %d\n", value);
        balance = 0;
      }
    }
    printf("balance: %d\n\n", balance);
    unlock(mtx);
    sleep(rand() % 3);
  }
}

void sig_handler(int sig) {
  if (sig == SIGINT)
    flag = 0;
}

int main() {
  pthread_t tellers[3];

  pthread_mutex_init(&mtx, NULL);

  for (int i = 0; i < 3; ++i)
    pthread_create(&tellers[i], NULL, teller, (void *)i);

  for (int i = 0; i < 3; ++i)
    pthread_join(tellers[i], NULL);

  pthread_mutex_destroy(&mtx);

  return 0;
}
