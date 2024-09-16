/*
 * Complete the 'climbingLeaderboard' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY ranked
 *  2. INTEGER_ARRAY player
 */

int binarySearch(int *arr, int n, int target){
     int l = 0;
     int r = n - 1;
     
     
     while(l <= r){
         int mid = l + (r - l)/2;
         if(arr[mid] == target){
             return mid + 1;
         }else if(arr[mid] > target){
             l = mid + 1;
         }else if(arr[mid < target]){
             r = mid - 1;
         }
     }
     return l + 1;
 }
 
 
int* climbingLeaderboard(int ranked_count, int* ranked, int player_count, int* player, int* result_count) {
    /*
        Problem: find the position of new player after each game
        E.g.1:
            - I/P: arr_rank = [100, 100, 50, 40, 40, 20, 10]
                              [1, 1, 2, 3, 3, 4, 5] // dense ranking
                   arr_player_scores = [5, 25, 50, 120]
            - Expected output: arr_rank_each_game = [6, 4, 3, 1]
        - rank is in descending order
        - player's score is in ascending order
        
        Solution: 
        - map the score with its rank
            - if we have a array as same as the rank array and with no duplicate number
            so the index of the new array will be the rank
            E.g.: [100, 100, 50, 40, 40, 20, 10] -> [100, 50, 40, 20, 10] -> [1, 2, 3, 4, 5]
            - suppose we have score of the first game is 5, so let use the binarySearch for the index 5
            E.g.: [100, 50, 40, 20, 10]
            Target: 5
            - first search: l = 0, r = 4, mid = 2 -> 5 < 40 -> l = 2 + 1
                - l = 3, r = 4, mid = 3
            - second search: mid = 20 > 5 -> l = 3 + 1
                - l = 4, r = 4, mid = 4
            - third search: mid = 10 > 5 -> l = 5
            (l <= r)? -> false
            - return l + 1 -> 6
            
            E.g.: [100, 50, 40, 20, 10]
            Target = 120
            - first search: l = 0, r = 4, mid = 2 -> 120 > 40 -> r = 2 - 1
                - l = 0, r = 1, mid = 0
            - second search: mid = 120 > 100 -> r = 1 - 1
                - l = 0, r = 0, mid = 0
            - third search: mid = 120 > 100 -> r = 0 - 1
            (l <= r)? -> false
            - return l + 1 -> 1
            
    */
    *result_count = player_count;
    int *ranked_no_dup = (int*)calloc(sizeof(int)*ranked_count, sizeof(int));
    int *result = (int*)calloc(sizeof(int)*player_count, sizeof(int));
    if(ranked != NULL){
        
        // find the rank number
        
        int j = 1;
        int consider_number = ranked[0];
        ranked_no_dup[0] = consider_number;
        for(int i = 0; i < ranked_count; i++){
            if(consider_number != ranked[i]){
                // update the result
                ranked_no_dup[j] = ranked[i];
                consider_number = ranked[i];
                j++;
            }
        }
        // check the no dup array
        j = 0;
        while(ranked_no_dup[j] != 0){
            printf("%d ", ranked_no_dup[j]);
            j++;
        }    
        for(int i = 0; i < player_count; i++){
            int ind = binarySearch(ranked_no_dup, j, player[i]);
            result[i] = ind;
        }
        
    }
    
    return result;
}