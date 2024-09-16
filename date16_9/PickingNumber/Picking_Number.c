/*
 * Complete the 'pickingNumbers' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY a as parameter.
 */

void swap(int *p1, int *p2){
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void sortArr(int *arr, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - 1 - i; j++){
            if (arr[j] > arr[j + 1]){
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void dispArr(int *arr, int n){
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
}

int pickingNumbers(int a_count, int* a) {
    /*
        Problem: find the longest subarray where difference between any two number
        is less than or equal to 1 (max length is 5)
            E.g.1:
            - I/P: [1, 1, 2, 2, 4, 4, 5, 5, 5]
            - Expected O/P: 5 ([4, 4, 5, 5, 5])
            E.g.2:
            - I/P: [4, 6, 5, 3, 3, 1]
            - Expected O/P: 3 ([4, 3, 3])
        
        
        - i think it will easier if the array is sorted, so let sort the array first.
        - suppose we have a 2 pointer for calculate the window length (l and r)
            - while r < size of array
                - if the |arr[r] - arr[l]| <= 1
                    - increase r by 1
                    - if the result < (r - l)
                        - update result
                - if the |arr[r] - arr[l]| > 1 
                    - increase l
                - if the result >= 5
                    return result
                    
        - E.g. : [1, 3, 3, 4, 5, 6]
            - first: r = 0, l = 0 -> arr[r] - arr[l] <= 1
                - r++ -> r = 1
                - result < r - 1 -> result = 1
            - second: r= 1, l = 0 -> 3 - 1 = 2 > 1
                - l++ -> l = 1
            - third: r = 1, l = 1 -> 3 - 3 = 0 <= 1
                - r++ -> r = 2
            - fourth: r = 2, l = 1 -> 3 - 3 = 0 <= 1
                - r++ -> r = 3
                - result < r - l = 2 -> result = 2
            - fifth: r = 3, l = 1 -> 4 - 3 = 1 <= 1
                - r++ -> r = 4
                - result < r - l = 3 -> result = 3
                    
        - Notice that when the r == l, we have case 1 to handle by increase r 1, so
        there noway l > r 
            
    */
    int result = 0;
    int l = 0; 
    int r = 0;
    // sort Arr
    sortArr(a, a_count);
    dispArr(a, a_count);
    while(r < a_count){
        if(abs(a[r] - a[l] <= 1)){
            r++;
            if(result < (r - l)){
                result = r - l;
            }
        }else if (abs(a[r] - a[l] > 1)){
            l++;
        }
    }
    return result;
}