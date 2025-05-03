#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../header.h"

//LOADING AND SAVING ARRAY

void loadArray(const char fileName[],void *array,int elementSize,int *count){
    FILE *fp=fopen(fileName,"rb");

    if(fp==NULL) printf("failed to open products.dat for reading");

    fread(count,sizeof(int),1,fp);
    if(*count>0){
        array=realloc(array,(*count)*elementSize); //p
        fread(array,elementSize,*count,fp);
    }
    fclose(fp);
}

void saveArray(const char fileName[],const void *array,int elementSize,int count){
    FILE *fp=fopen(fileName,"wb");

    if(fp==NULL) printf("failed to open products.dat for writing");

    fwrite(&count,sizeof(int),1,fp);
    fwrite(array,elementSize,count,fp);
    fclose(fp);
}

//LOADING DATA

void loadProducts(int arrNum,subCategories *arr[]){ //(double pointer problem)
    for (int i = 0; i < arrNum; i++)
    {
        arr[i]->prodArrCount=0;
        loadArray("products.dat",arr[i]->prod,sizeof(products),&(arr[i]->prodArrCount));
    }
    
}

void loadSubCategories(int arrNum,categories *arr[]){
    for (int i = 0; i < arrNum; i++)
    {
        arr[i]->subCArrCount=0;
        loadArray("subCategories.dat",arr[i]->subc,sizeof(subCategories),&(arr[i]->subCArrCount));
        loadProducts(arr[i]->subCArrCount,&(arr[i]->subc));
    }
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




// STILL IN PRODUCTION---------------------------------------------------------------------------------------------------------------------------------------
void addCategory(categories *arr,int *elementCount){
    categories cat;
    printf("Enter category name : \n");
    scanf("%s",cat.name);
    arr[*elementCount++]=cat;
}

void removeCategory(categories *arr,int *elementCount,char catName[MAX_NAME_LENGTH]){ //removing sub and prod;
    for (int i = 0; i < *elementCount; i++)
    {
        if(i+1==*elementCount) break;
        if (arr[i].name==catName)
        {
            categories temp=arr[i];
            arr[i]=arr[i+1];
            arr[i+1]=temp;
            
        }
    }
    arr=(categories *)realloc(arr,(--(*elementCount))*sizeof(categories));
    
}

void editCategory(categories *arr,int *elementCount,char catName[MAX_NAME_LENGTH]){
    for (int i = 0; i < *elementCount; i++)
    {
        if (arr[i].name==catName)
        {
            printf("Enter a new name : ");
            scanf("%s",&arr[i].name);
        }
        
    }
    
}

