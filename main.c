#include <stdio.h>
#include <stdlib.h>
#include "header.h"



int main(){
    categories *categoryArr=(categories *) malloc(sizeof(categories));
    int categoryCount=0;
    categoryArr->subc=(subCategories *) malloc(sizeof(subCategories));
    addCategory(&categoryArr,&categoryCount);
    printf("%d",categoryCount);
    addCategory(&categoryArr,&categoryCount);
    printf("%d",categoryCount);
    addCategory(&categoryArr,&categoryCount);
    printf("%d",categoryCount);
    

    for (int i = 0; i < categoryCount; i++)
    {
        printf("%d %s \n",categoryCount,categoryArr[i].name);
    }
    char hh[MAX_NAME_LENGTH]="sub";
    char gg[MAX_NAME_LENGTH]="cat";
    addSubCategory(gg,&categoryArr,categoryCount);
    addProduct(&categoryArr,gg,hh,categoryCount);
    //loadArray("categories.dat",(void**)&categoryArr,sizeof(categories),&categoryCount);

    
    
    return 0;
}