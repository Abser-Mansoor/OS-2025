#include <iostream>

using namespace std;

void merge(int* arr, int start, int mid, int end) {
    int left_size = mid - start + 1;
    int  right_size = end - mid;
    int left_index = 0;
    int right_index = 0;
    int k = start;
    int *left = new int[left_size];
    int *right = new int[right_size];

    for (int i = 0; i < left_size; i++) {
        left[i] = arr[start + i];
    }

    for (int i = 0; i < right_size; i++) {
        right[i] = arr[mid+i+1];
    }

    while (left_index < left_size && right_index < right_size) {
        if (left[left_index] <= right[right_index]) {
            arr[k] = left[left_index];
            left_index++;
            k++;
        }
        else {
            arr[k] = right[right_index];
            right_index++;
            k++;
        }
    }

    while (left_index < left_size) {
        arr[k] = left[left_index];
        left_index++;
        k++;
    }
    
    while (right_index < right_size) {
        arr[k] = right[right_index];
        right_index++;
        k++;
    }
    delete [] left;
    delete [] right;
}

void mergesort(int* arr, int start, int end) {
    if (start < end) {
        int mid = start+(end-start)/2;
        mergesort(arr,start,mid);
        mergesort(arr,mid+1,end);
        merge(arr,start,mid,end);
    }
}

int main(int argc, char* arg[]) {
        if (argc < 2) return 1;
        int* arr = new int[atoi(arg[1])];
        int sum = 0;
        for (int i = 0; i < atoi(arg[1]); i++) {
                arr[i] = atoi(arg[i+2]);
        }
	mergesort(arr,0,atoi(arg[1])-1);
	for (int i = 0; i < atoi(arg[1]); i++) {
               cout << arr[i] << " ";
        }
        return 0;
}
