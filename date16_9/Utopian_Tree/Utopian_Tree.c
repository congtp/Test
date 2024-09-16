/*
 * Complete the 'utopianTree' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER n as parameter.
 */

int utopianTree(int n) {
    /*
        Problem: find the height of tree with given cycle.
        Spring: double size, Summer: size + 1, start with Spring
        Tree start with height = 1
        E.g.: 
        - n = 5 -> 5 cycle
        - n = 0 -> height = 1, n = 1 -> height = 1*2
        - n = 2 -> height = 2 + 1, n = 3 -> height = 3*2
        - n = 4 -> height = 6 + 1, n = 5 -> height = 7 * 2
        
        Solution:
        - we can go through all the cycle
        - if cycle is odd -> double size
        - if cycle is even -> size + 1
        
         
    */
    int result = 1;
    
    for(int i = 1; i <= n; i++){
        if(i % 2 == 0){
            // even
            result += 1;
        }else{
            result *= 2;
        }
        printf("%d ", result);
    }
    return result;
}
