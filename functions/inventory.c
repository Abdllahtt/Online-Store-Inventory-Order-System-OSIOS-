#include <stdio.h>
#include "../header.h"

//LOADING AND SAVING PRODUCT'S ARRAY

void loadProductsArray(products *productsArr,int *productsCount){
    FILE *fp=fopen("/data/products.dat","rb");

    if(fp==NULL) printf("failed to open products.dat for reading");

    fread(productsCount,sizeof(int),1,fp);
    fread(productsArr,sizeof(products),*productsCount,fp);
    fclose(fp);
}

void saveProductsArray(products *productsArr,int productsCount){
    FILE *fp=fopen("/data/products.dat","wb");

    if(fp==NULL) printf("failed to open products.dat for writing");

    fwrite(&productsCount,sizeof(int),1,fp);
    fwrite(productsArr,sizeof(products),productsCount,fp);
    fclose(fp);
}

//CRUD



