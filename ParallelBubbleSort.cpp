#include <iostream>
#include <omp.h>
using namespace std;
void parallel_bubble_sort(int *arr, int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        #pragma omp parallel for private(j, temp) shared(arr)
        for (j = i % 2; j < n - 1; j += 2) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
        #pragma omp barrier
    }
}
int main() {
    int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
    int n = sizeof(arr)/sizeof(arr[0]);
    double start_time = omp_get_wtime();
    parallel_bubble_sort(arr, n);
    double end_time = omp_get_wtime();
    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "Time taken: " << end_time - start_time << " seconds" << endl;
    return 0;
}
