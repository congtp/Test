/*
 * Complete the 'designerPdfViewer' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY h
 *  2. STRING word
 */

int designerPdfViewer(int h_count, int* h, char* word) {
    /*
        Problem: find the area of highlight word
        - Give a h which contains the 26 characters height
        - return the are of the given word
        E.g.: 
            - I/P = "torn"
            - Expected O/P = 8
            - Explain: t will be map with height[t] = 2, o = 1, r = 1, n = 1
            - So t is the highest -> area = 2 * 4 = 8 
        
        
        Solution:
            - we just need to find the index of the character by subtract the
            character for 'a'
            - find the height of each character:
            - find the character with heighest
            - return the multiply of heightest and length of words
    */
    
    int heighest_ch = INT32_MIN;
    int word_cnt = 0;
    for(int i = 0; word[i] != '\0'; i++){
        int idx = (int)(word[i] - 'a');
        printf("%d ", idx);
        if(heighest_ch < h[idx]){
            heighest_ch = h[idx];
        }
        word_cnt++;
    }
    
    return heighest_ch * word_cnt;
}