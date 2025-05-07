#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
int n = 10;

void *sort(void *arg) {
  int start = (long)arg * n/2;
  int end = start + n/2;

  for (int i = start; i < end-1; ++i) {
    for (int j = start; j < end-1; ++j) {
      if (arr[j] > arr[j+1]) {
        arr[j] ^= arr[j+1];
        arr[j+1] ^= arr[j];
        arr[j] ^= arr[j+1];
      }
    }
  }
}

void merge() {
  int arr1[n/2], arr2[n/2];
  for (int i = 0; i < n/2; ++i)
    arr1[i] = arr[i];
  for (int i = 0; i < n/2; ++i)
    arr2[i] = arr[i + n/2];
  
  int i = 0, j = 0, k = 0;
  while (i < n/2 && j < n/2) {
    if (arr1[i] < arr2[j]) {
      arr[k++] = arr1[i++];
    } else {
      arr[k++] = arr2[j++];
    }
  }

  while (i < n/2)
    arr[k++] = arr1[i++];
  while (j < n/2)
    arr[k++] = arr2[j++];
}

int main() {
  pthread_t t1, t2;

  pthread_create(&t1, NULL, sort, (void *)0);
  pthread_create(&t2, NULL, sort, (void *)1);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  merge();

  for (int i = 0; i < n; ++i)
    printf("%d ", arr[i]);
  printf("\n");

  return 0;
}
