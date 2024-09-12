void bonAppetit(int bill_count, int* bill, int k, int b) {

    /*
        the index (k) is the index of the item Anna didn't eat
        so we sum the whole bill except for the item of index k
        then we print "bon appetit" if (b_charge/2 = b)
        otherwise print the diff between them
    */


    int b_charged = 0;
    for(int i = 0; i < bill_count; i++){
        if(i != k){
            b_charged += bill[i];
        }
    }
    b_charged = b_charged/2;
    if(b_charged == b){
        printf("Bon Appetit");
    }else{
        printf("%d", b - b_charged);
    }
    
}