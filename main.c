#include <stdio.h>
#include "header.h"



int main(){
    
    products productArr[MAX_PRODUCTS];
    int productsC=0;
    loadProductsArray(productArr,&productsC);
    return 0;
}