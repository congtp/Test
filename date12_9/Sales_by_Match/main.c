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

int sockMerchant(int n, int ar_count, int* ar) {
    
    
    sortArr(ar, 0, ar_count - 1);
    int checkPoint = 0;
    int pair = 0;
    int i = 0;
    for(i = 0; i < ar_count; i++){
        printf("%d ", ar[i]);
    }
    for(i = 0; i < ar_count - 1; i++){
        if(ar[checkPoint] != ar[i + 1]){
            pair += (((i + 1) - checkPoint) / 2);
            checkPoint = i + 1;
        }
    }
    if(ar[checkPoint] != ar[i + 1]){
        pair += (((i + 1) - checkPoint) / 2);
        checkPoint = i + 1;
    }
    
    
    return pair;
}