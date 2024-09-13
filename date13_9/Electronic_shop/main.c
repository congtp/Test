void swap(int *p, int *p1){
    int temp = *p;
    *p = *p1;
    *p1 = temp;
}
 
void sortArr(int *arr, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(arr[j] > arr[j + 1]){
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}
 
void dispArr(int *arr, int n){
    for(int i= 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}
 
int getMoneySpent(int keyboards_count, int* keyboards, int drives_count, int* drives, int b) {
    /*
     * Write your code here.
        - I think it will do easily when the array is sorted. -> sort first bigO(n2) -> bigO(nlogn)
        - suppose after sorted we have 2 arrays:
            - Budget = 10;
            - Expected O/P -> 10
            - 1 3 8 : arr1
            - 2 5 8 : arr2
            - suppose we have 2 pointer i -> arr1[0], j -> arr2[2]
            - if(arr1[i] + arr2[j] > Budget)  
                //
                because there is no chance that the element 
                at arr2[j] can sum with the element in arr1 to less than the target
                so we will eliminate the arr2[j]
                //
                - j--
            - if(arr1[i] + arr2[j] < Budget)
                - i++
            - else
                - return arr1[i] + arr2[j];
     */
    
     int i = 0;
     int j = drives_count - 1;
     int rtValue = -1;
     sortArr(keyboards, keyboards_count);
     sortArr(drives, drives_count);
     dispArr(keyboards, keyboards_count);
     dispArr(drives, drives_count);
     while(i < keyboards_count && j >= 0){
         int max = keyboards[i] + drives[j];
         if(max < b){
             if(rtValue < max){
                 rtValue = max;
             }
             i++;
         }else if(max > b){
             j--;
         }else{
             return max;
         }
     }
        
        
    return rtValue;
}