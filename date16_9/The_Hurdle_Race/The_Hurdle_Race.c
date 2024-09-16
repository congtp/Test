
int hurdleRace(int k, int height_count, int* height) {
    /*
        Problem: find the number of potion needed to jump over all the enemy 
        height
        E.g.: height [1, 2, 3, 3, 2]
              k = 1 # k is the natural height the character can jump
            - Expected output = 3 - 1 = 2
        
        
        Solution:
            - Find the max number in the heights
            - if k > max:
                - return 0
            - else 
                - return k - max
        
    */
    int max = INT32_MIN;
    int result = 0;
    
    for(int i = 0; i < height_count; i++){
        if(max < height[i]){
            max = height[i];
        }
    }
    
    if(k <= max){
       result = max - k;
    }
    
    return result;
}