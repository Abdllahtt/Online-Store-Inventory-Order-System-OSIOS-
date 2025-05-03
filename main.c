#include <stdio.h>
#include <stdlib.h>
#include "header.h"



int main(){
    categories *categoryArr=(categories *) malloc(sizeof(categories));
    int categoryCount=0;
    categoryArr->subc=(subCategories *) malloc(sizeof(subCategories));
    products productArr[MAX_PRODUCTS];
    loadArray("categories.dat",categoryArr,sizeof(categories),&categoryCount);
    
    return 0;
}