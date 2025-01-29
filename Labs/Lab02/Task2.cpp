#include <iostream>

using namespace std;

int main(int argc, char* arg[]) {
        if (argc < 2) return 1;
        int arr[atoi(arg[1])];
        int i = 0;
        for (i = 0; i < atoi(arg[1]); i++) {
                arr[i] = atoi(arg[i+2]);
        }
        int missing_element = atoi(arg[i+2]);
        int first_element = arr[0];
        int difference = arr[1]-arr[0];
        cout << missing_element  <<"th element  is " << first_element + (missin>
        return 0;
}
