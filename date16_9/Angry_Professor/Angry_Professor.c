char* angryProfessor(int k, int a_count, int* a) {
    /*
        Problem: find if the class is canceled or not
        Given the array of indicate the time go to class
        arr[i] <= 0 -> on time, arr[i] > 0 -> late
        return "YES" or "NO"
        E.g.: Given [-1, -3, 4, 2]
        - k = 3 (cancellation threshold)
        - -> ontime = 2 < 3 -> "YES"
        
        Solution:
        - Go through all the array
        - Count the number that less than 0
        - Compare with k
        - if > k -> return "NO"
        - else -> return "YES"
        
        
    */
    
    int cnt = 0;
    static char result[4] = "";
    for(int i = 0; i < a_count; i++){
        if(a[i] <= 0){
            cnt++;
        }
    }
    if(cnt >= k){
        strcpy(result, "NO");
    }else{
        strcpy(result, "YES");
    }
    return result;
}