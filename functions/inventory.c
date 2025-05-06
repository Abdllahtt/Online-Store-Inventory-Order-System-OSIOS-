#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../header.h"

//LOADING AND SAVING ARRAY

/*void loadArray(const char fileName[],void **array,int elementSize,int *count){
    FILE *fp=fopen(fileName,"rb");

    if(fp==NULL) printf("failed to open products.dat for reading");

    fread(count,sizeof(int),1,fp);
    if(*count>0){
        array=realloc(*array,(*count)*elementSize); //p
        fread(*array,elementSize,*count,fp);
    }
    fclose(fp);
}*/

/*void saveArray(const char fileName[],const void *array,int elementSize,int count){
    FILE *fp=fopen(fileName,"wb");

    if(fp==NULL) printf("failed to open products.dat for writing");

    fwrite(&count,sizeof(int),1,fp);
    fwrite(array,elementSize,count,fp);
    fclose(fp);
}*/

//LOADING DATA

/*void loadProducts(int arrNum,subCategories *arr[]){ //(double pointer problem)
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
*/

/*

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


*/

// STILL IN PRODUCTION---------------------------------------------------------------------------------------------------------------------------------------
void addCategory(categories **arr,int *elementCount){
    categories cat;
    categories *temp;
    printf("Enter category name : \n");
    scanf("%s",cat.name);
    cat.subCArrCount=0;
    cat.subc=(subCategories *)malloc(sizeof(subCategories));
    temp=(categories *)realloc(*arr,((*elementCount+1))*sizeof(categories));
    if (temp==NULL)
    {
        printf("realloc fails");
        return;
    }
    (*elementCount)++;
    *arr=temp;
    (*arr)[*elementCount-1]=cat;
}

void removeCategory(categories **arr,int *elementCount,char catName[MAX_NAME_LENGTH]){ //removing sub and prod;
    for (int i = 0; i < *elementCount; i++)
    {
        if(i+1==*elementCount) break;
        if (strcmp((*arr)[i].name,catName)==0)
        {
            
            categories temp=(*arr)[i];
            (*arr)[i]=(*arr)[i+1];
            (*arr)[i+1]=temp;
            
        }
    }
    if((*arr)[(*elementCount)-1].subCArrCount!=0) free((*arr)[(*elementCount)-1].subc);
    *arr=(categories *)realloc(*arr,(--(*elementCount))*sizeof(categories));
    
}

void editCategory(categories **arr,int *elementCount,char catName[MAX_NAME_LENGTH]){
    for (int i = 0; i < *elementCount; i++)
    {
        if (strcmp((*arr)[i].name,catName)==0)
        {
            printf("Enter a new name : ");
            scanf("%s",(*arr)[i].name);
        }
        
    }
    
}

void addSubCategory(char catName[MAX_NAME_LENGTH],categories **catArr,int elementCount){
    int i=0;
    while (strcmp((*catArr)[i].name,catName)!=0 && i!=elementCount)
    {
        i++;
    }
    subCategories new;
    printf("Enter a sub-category name : \n");
    scanf("%s",new.name);
    new.prodArrCount=0;
    new.prod=(products *) malloc(sizeof(products));
    (*catArr)[i].subc=(subCategories *)realloc((*catArr)[i].subc,(++(*catArr)[i].subCArrCount)*sizeof(subCategories));
    (*catArr)[i].subc[(*catArr)[i].subCArrCount-1]=new;

}

void removeSubCategory(char catName[MAX_NAME_LENGTH],char subCatName[MAX_NAME_LENGTH],categories **catArr,int elementCount){
        int i=0;
    
        while(strcmp(catName,(*catArr)[i].name)!=0 && i!=elementCount)
        {
            i++;
        }
        
        for (int j = 0; j < (*catArr)[i].subCArrCount; i++)
        {
            if(j+1==(*catArr)[i].subCArrCount) break;
            if (strcmp((*catArr)[i].subc[j].name,subCatName)==0)
            {
                subCategories temp=(*catArr)[i].subc[j];
                (*catArr)[i].subc[j]=(*catArr)[i].subc[j+1];
                (*catArr)[i].subc[j+1]=temp;
                
            }
            
        }
        
        (*catArr)[i].subc=(subCategories *) realloc((*catArr)[i].subc,(--(*catArr)[i].subCArrCount)*sizeof(subCategories));
    

}


void editSubCategory(char catName[MAX_NAME_LENGTH],char subCatName[MAX_NAME_LENGTH],categories **catArr,int elementCount){

    int i=0;
    while (strcmp((*catArr)[i].name,catName)!=0 && i!=elementCount)
    {
        i++;
    }
    if (i==elementCount) {printf("Category does not exist"); return;}
    

    for (int j = 0; j < (*catArr)[i].subCArrCount; j++)
    {
        if (strcmp(subCatName,(*catArr)[i].subc[j].name)==0)
        {
            printf("Enter a new name : \n");
            scanf("%s",(*catArr)[i].subc[j].name);
            return;
        }
        
    }
    printf("Subcategory does not exist");
}


void addProduct(categories **catArr,char catName[MAX_NAME_LENGTH],char subCatName[MAX_NAME_LENGTH],int elementCount){
    int i=0;
    while (strcmp((*catArr)[i].name,catName)!=0 && i!=elementCount)
    {
        i++;
    }
    if (i==elementCount) {printf("Category does not exist"); return;}
    

    for (int j = 0; j < (*catArr)[i].subCArrCount; j++)
    {
        if (strcmp((*catArr)[i].subc[j].name,subCatName)==0)
        {
            //find product
            
            
            products new;
            strcpy(new.category,catName);
            strcpy(new.subCategory,subCatName);
            printf("Enter product's name : \n");
            scanf("%s",new.name);
            
            for (int k = 0; k < (*catArr)[i].subc[j].prodArrCount; k++)
            {
                if(strcmp((*catArr)[i].subc[j].prod[k].name,new.name)) printf("Product already exists, try 'Edit Products'");
            }

            printf("Enter product's price : \n");
            scanf("%d",&new.price);
            printf("Enter product's status : \n");
            scanf("%d",&new.status);
            printf("Enter product's stock value : \n");
            scanf("%d",&new.stock_value);
            printf("Enter product's ID : \n");
            scanf("%d",&new.ID);

            (*catArr)[i].subc[j].prod=(products *) realloc((*catArr)[i].subc[j].prod,(++(*catArr)[i].subc[j].prodArrCount)*sizeof(products));
            (*catArr)[i].subc[j].prod[(*catArr)[i].subc[j].prodArrCount-1]=new;
            
        }
        
    }
    


}

void removeProduct(categories **catArr,char prodName[MAX_NAME_LENGTH],int elementCount,products **productsArr,int productsArrSize){
    char cat[MAX_NAME_LENGTH];
    char subCat[MAX_NAME_LENGTH];
    for (int i = 0; i < productsArrSize; i++)
    {
        if(strcmp(prodName,(*productsArr)[i].name)==0){
            strcpy(cat,(*productsArr)[i].category);
            strcpy(subCat,(*productsArr)[i].subCategory);
        }else{
            printf("Product does not exist");
            return;
        }
        
    }
    int i=0;
    while (strcmp((*catArr)[i].name,cat)!=0)
    {
        i++;
    }
    int j=0;
    while (strcmp((*catArr)[i].subc[j].name,subCat)!=0)
    {
        j++;
    }
          
    for (int k = 0; k < (*catArr)[i].subc->prodArrCount; k++)
    {
        if(k== (*catArr)[i].subc->prodArrCount) break;
        if(strcmp((*catArr)[i].subc[j].prod[k].name,prodName)==0){
        products tmp;
        tmp=(*catArr)[i].subc[j].prod[k];
        (*catArr)[i].subc[j].prod[k]=(*catArr)[i].subc[j].prod[k+1];
        (*catArr)[i].subc[j].prod[k+1]=tmp;
        }              
    }
    (*catArr)[i].subc[j].prod=(products *) realloc((*catArr)[i].subc[j].prod,(--(*catArr)[i].subc[j].prodArrCount)*sizeof(products));

}

void editProduct(categories **catArr,char prodName[MAX_NAME_LENGTH],int elementCount,products **productsArr,int productsArrSize){
    char cat[MAX_NAME_LENGTH];
    char subCat[MAX_NAME_LENGTH];
    for (int i = 0; i < productsArrSize; i++)
    {
    
        if(strcmp(prodName,(*productsArr)[i].name)==0){
            strcpy(cat,(*productsArr)[i].category);
            strcpy(subCat,(*productsArr)[i].subCategory);
        }else{
            printf("Product does not exist");
            return;
        }
        
    }
    int i=0;
    while (strcmp((*catArr)[i].name,cat)!=0)
    {
        i++;
    }
    int j=0;
    while (strcmp((*catArr)[i].subc[j].name,subCat)!=0)
    {
        j++;
    }
          
    for (int k = 0; k < (*catArr)[i].subc->prodArrCount; k++)
    {
        if(k== (*catArr)[i].subc->prodArrCount) break;
        if(strcmp((*catArr)[i].subc[j].prod[k].name,prodName)==0){
            printf("1- Edit name.\n");
            printf("2- Edit price.\n");
            printf("3- Edit stock value.\n");
            int edit;
            scanf("%d",&edit);
            switch (edit)
            {
            case 1:
                printf("Enter a new name");
                scanf("%s",(*catArr)[i].subc[j].prod[k].name);
                break;
            case 2:
                printf("Enter a new price");
                scanf("%d",&(*catArr)[i].subc[j].prod[k].price);
                break;
            case 3:
                printf("Enter a new stock value");
                scanf("%d",&(*catArr)[i].subc[j].prod[k].stock_value);
                break;
            
            default:
                break;
            }            
            
        }              
    }

}
