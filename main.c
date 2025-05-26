#include <stdio.h>
#include <stdlib.h>
#include "header.h"



int main(){
    Customer *customerArr=(Customer *) malloc(sizeof(Customer));
    int customerCount=0;
    products *allProducts=(products *) malloc(sizeof(products));
    int productsCount=0;
    categories *categoryArr=(categories *) malloc(sizeof(categories));
    int categoryCount=0;
    categoryArr->subc=(subCategories *) malloc(sizeof(subCategories));
    
    
    return 0;
}