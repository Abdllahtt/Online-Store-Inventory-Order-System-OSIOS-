#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
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
//filter categories 
char **getUniquecategories(products inventory[],int Numproduct,int *uniqueCount){
    char** uniquecategories = NULL;
    *uniqueCount = 0;
    for (int i = 0; i < Numproduct; i++)
    {
        bool found=false;
        for (int j = 0; j < *uniqueCount; j++)
        {
            if (strcmp(inventory[i].category, uniquecategories[j]) == 0) {
                found = true;
                break;
            }
        }
        if (!found)
        {
            //allocate memory for the new unique category FOUND 
            char *newcategory=(char*)malloc(strlen(inventory[i].category)+1);
            if (newcategory == NULL)
            {
                perror("Memory allocation failed ");
                for (int k;k<*uniqueCount ;k++){
                    free(uniquecategories[k]);
                }
            }
            strcpy(newcategory, inventory[i].category);
            //realocate memory for the "uniquecategories" array ,resizing the array so the new pointer can be added at the end 
            char **temp =(char**)realloc(uniquecategories,(*uniqueCount +1)*sizeof(char*));
            if(temp==NULL){
                perror("memoy allocation failed");
                free(newcategory);
                // clean previously used memory
                for (int k = 0; k < *uniqueCount; k++) {
                    free(uniquecategories[k]);
                }
                free(uniquecategories);
                return NULL;
            }
            uniquecategories =temp;
            uniquecategories[*uniqueCount] = newcategory;
            (*uniqueCount)++;
        }
        
        
    }
    return uniquecategories;

}
//display function 
void displaycategories(char **categories,int count){
    printf("the current categories are : \n");
    for (int i = 0; i < count; i++)
    {
        printf("%d - %s \n",i+1,categories[i]);
    }
    
}
//search by Id or name function and display the wanted product 
void findname(products inventory[], int Numproduct) {
    printf("Enter the name or ID of the wanted product: ");
    char input[50];
    scanf("%49s", input);

    int wantedID = atoi(input);
    bool searched = false;

    if (wantedID != 0) {
        for (int i = 0; i < Numproduct; i++) {
            if (wantedID == inventory[i].ID) {
                printf("Name: %s\n", inventory[i].name);
                printf("Category: %s\n", inventory[i].category);
                printf("Sub-category: %s\n", inventory[i].subCategory);
                printf("ID: %d\n", inventory[i].ID);
                printf("Price: %d\n", inventory[i].price);
                searched = true;
                break;
            }
        }
    }

    // If not found by ID or if the input was not a valid ID, search by name
    if (!searched) {
        for (int i = 0; i < Numproduct; i++) {
            if (strcmp(input, inventory[i].name) == 0) {
                printf("Name: %s\n", inventory[i].name);
                printf("Category: %s\n", inventory[i].category);
                printf("Sub-category: %s\n", inventory[i].subCategory);
                printf("ID: %d\n", inventory[i].ID);
                printf("Price: %d\n", inventory[i].price);
                searched = true;
                break;
            }
        }
    }

    if (!searched) {
        printf("Product not found.\n");
    }
}



