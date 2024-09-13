/*
 * Complete the 'countingValleys' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER steps
 *  2. STRING path
 */

int countingValleys(int steps, char* path) {
    /*
        The valley will be defined as D->U
        There is a chance that 2 hills consecutively then U->D->U->D
        let say we have a sea level = 0
        and each step up or down will change the sea level respectively
        so we have 3 cases:
            - above the sea level:
                - dont do anything
            - below the sea level and we are finding the valley:
                - valley++
                - find sea level = true -> find sea level
            - equal to the sea level and we are finding the sea:
                - find sea level = false -> find valley
    */
    
    bool find_sea_level = false;
    int sea_level = 0;
    int valley = 0;
    for(int i = 0; i < steps; i++){
        if(path[i] == 'U'){
            sea_level++;
        }else{
            sea_level--;
        }
        if(sea_level < 0 && !find_sea_level){
            valley++;
            find_sea_level = true;
        }
        if(sea_level == 0 && find_sea_level){
            find_sea_level = false;
        }
        
        
    }
    return valley;
}