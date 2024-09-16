int reverseDay(int n){
    // convert to string
    int result = 0;
    char s[10] = {0};
    int cnt = sprintf(s, "%d", n);
    //printf("%d", cnt);
    // reverse the s
    for(int i = 0; i < cnt/2; i++){
        swap(&s[i], &s[cnt - 1 - i]);
    }
    result = atoi(s);
    printf("%d ", result);
    return result;
}

int beautifulDays(int i, int j, int k) {
    /*
        Problem: find the beautiful day
        - Given the starting, the ending day, and the divisor 
        - if the |day - reverse_day| % divisor == 0 -> beautiful day
        
        Solution:
        - Find the corresponding reverse day
            - E.g.: day = 120
            - 120 % 10 = 0 -> 120 /10 = 12 (store in array)
            - 12 % 10 = 2 -> 12 / 10 = 1 (store in array)
            - 1 % 10 = 1 -> 1 /10 = 0 -> stop (store in array)
            - -> just use atoi() and sprintf
        - if the |day - reverse_day| % divisor == 0 -> beautiful day + 1
        
        
    */
    
    int reverDay = 0;
    int cnt = 0;
    while (i <= j){
        reverDay = reverseDay(i);
        if(abs(i - reverDay) % k == 0){
            cnt++;
        }
        //printf("%d ", abs(i - reverDay) % k);
        i++;
        
        
            
    }
    
    return cnt;
    
}