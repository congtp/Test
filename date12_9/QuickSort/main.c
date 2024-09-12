#include <stdio.h>
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *arr, int low, int high){
    int pivot = arr[low];
    int i = low;
    int j = high;
    while(i < j){
        while(arr[i] <= pivot && i <= high - 1) i++; // find the number > pivot
        while(arr[j] > pivot && j >= low + 1) j--;    // find the number < pivot
        if(i < j){
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[low], &arr[j]);
    return j;
}

void sortArr(int *arr, int low, int high){
    //
    if(low < high){ // terminate if low = high
        // find the index
        int par = partition(arr, low, high);

        sortArr(arr, low, par - 1);
        sortArr(arr, par + 1, high);
        
    }
}

int main(){
    int arr[] = {10, 10, 50, 20, 30, 50, 20};

    int size = sizeof(arr)/sizeof(int);
    sortArr(arr, 0, size - 1);

    for (int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }

    return 0;
}