#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../header.h"

//LOADING AND SAVING ARRAY

void loadArray(const char fileName[],void **array,int elementSize,int *count){
    FILE *fp=fopen(fileName,"rb");

    if(fp==NULL) printf("failed to open %s.dat for reading",fileName);

    fread(count,sizeof(int),1,fp);
    if(*count>0){
        *array=realloc(*array,(*count)*elementSize); //p
        fread(*array,elementSize,*count,fp);
    }
    fclose(fp);
}

void saveArray(const char fileName[],const void *array,int elementSize,int count){
    FILE *fp=fopen(fileName,"wb");

    if(fp==NULL) printf("failed to open %s.dat for writing",fileName);

    fwrite(&count,sizeof(int),1,fp);
    fwrite(array,elementSize,count,fp);
    fclose(fp);
}

//LOADING DATA

void saveProducts(int arrNum,subCategories *arr){ 
    char fileName[MAX_NAME_LENGTH];
    for (int i = 0; i < arrNum; i++)
    {
        sprintf(fileName,"products_%d.dat",i);
        saveArray(fileName,arr[i].prod,sizeof(products),(arr[i].prodArrCount));
    }
    
}

void saveSubCategories(int arrNum,categories *arr){
    char fileName[MAX_NAME_LENGTH];
    for (int i = 0; i < arrNum; i++)
    {
        sprintf(fileName,"subCategories_%d.dat",i);
        saveArray(fileName,arr[i].subc,sizeof(subCategories),(arr[i].subCArrCount));
        saveProducts(arr[i].subCArrCount,(arr[i].subc));
    }
}

//LOADING DATA

void loadProducts(int arrNum,subCategories *arr){ //(double pointer problem)
    char fileName[MAX_NAME_LENGTH];
    for (int i = 0; i < arrNum; i++)
    {
        arr[i].prodArrCount=0;
        sprintf(fileName,"products_%d.dat",i);
        loadArray(fileName,&arr[i].prod,sizeof(products),&(arr[i].prodArrCount));
    }
    
}

void loadSubCategories(int arrNum,categories *arr){
    char fileName[MAX_NAME_LENGTH];
    for (int i = 0; i < arrNum; i++)
    {
        arr[i].subCArrCount=0;
        sprintf(fileName,"subCategories_%d.dat",i);
        loadArray(fileName,&arr[i].subc,sizeof(subCategories),&(arr[i].subCArrCount));
        loadProducts(arr[i].subCArrCount,&(arr[i].subc));
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
products* findProduct(products inventory[], int Numproduct) {
    printf("Enter the name or ID of the wanted product: ");
    char input[50];
    scanf("%49s", input);

    int wantedID = atoi(input);

    if (wantedID != 0) {
        for (int i = 0; i < Numproduct; i++) {
            if (wantedID == inventory[i].ID) {
                return &inventory[i]; // Return a pointer to the found struct
            }
        }
    }

    // If not found by ID or if the input was not a valid ID, search by name
    for (int i = 0; i < Numproduct; i++) {
        if (strcmp(input, inventory[i].name) == 0) {
            return &inventory[i]; // Return a pointer to the found struct
        }
    }

    return NULL; // Return NULL if the product is not found
}

// Function to display the details of a product struct
void displayProduct(const products* product) {
    if (product != NULL) {
        printf("Name: %s\n", product->name);
        printf("Category: %s\n", product->category);
        printf("Sub-category: %s\n", product->subCategory);
        printf("ID: %d\n", product->ID);
        printf("Price: %d\n", product->price);
    } else {
        printf("Product not found.\n");
    }
}
void assigne_status(products  *product){
    if(product->stock_value ==0){
        product ->product_status=OUT_OF_STOCK;
    }
    else if(product->stock_value ==-1){
        product->product_status=DISCONTINUED;
        
    }
    else if(product->stock_value >0){
        product ->product_status=AVAILABLE;
        
    }
}


// STILL IN PRODUCTION---------------------------------------------------------------------------------------------------------------------------------------
void addCategory(categories **arr,int *elementCount){
    categories cat;
    categories *temp;
    printf("Enter category name : \n");
    scanf("%s",cat.name);
    cat.subCArrCount=0;
    cat.subc=(subCategories *)malloc(sizeof(subCategories));
    if(cat.subc==NULL) {
        printf("failed to allocate memory");
        return;
    }
    temp=(categories *)realloc(*arr,((*elementCount+1))*sizeof(categories));
    if (temp==NULL)
    {
        printf("failed to allocate memory");
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
    if(strcmp((*arr)[(*elementCount)-1].name,catName)!=0){
        printf("Category not found");
        return;
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
            return;
        }
        
    }
    printf("Category not found");
}

void addSubCategory(char catName[MAX_NAME_LENGTH],categories **catArr,int elementCount){
    int i=0;
    while (strcmp((*catArr)[i].name,catName)!=0 && i!=elementCount)
    {
        i++;
        if (i == elementCount)
        {
            printf("Category not found");
            return;
        }
        
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
            if (i==elementCount)
            {
                printf("Category not found");
                return;
            }
            
        }
        int subCsize=(*catArr)[i].subCArrCount;
        for (int j = 0; j < subCsize; i++)
        {
            if(j+1==subCsize) break;
            if (strcmp((*catArr)[i].subc[j].name,subCatName)==0)
            {
                subCategories temp=(*catArr)[i].subc[j];
                (*catArr)[i].subc[j]=(*catArr)[i].subc[j+1];
                (*catArr)[i].subc[j+1]=temp;
                
            }
            
        }
        if(strcmp((*catArr)[i].subc[subCsize-1].name,subCatName)!=0){
            printf("Sub-Category not found");
            return;
        }
        free((*catArr)[i].subc[subCsize-1].prod);
        (*catArr)[i].subc=(subCategories *) realloc((*catArr)[i].subc,(--(*catArr)[i].subCArrCount)*sizeof(subCategories));
    

}


void editSubCategory(char catName[MAX_NAME_LENGTH],char subCatName[MAX_NAME_LENGTH],categories **catArr,int elementCount){

    int i=0;
    while (strcmp((*catArr)[i].name,catName)!=0 && i!=elementCount)
    {
        i++;
    }
    if (i==elementCount) {
        printf("Category not found");
        return;
    }
    

    for (int j = 0; j < (*catArr)[i].subCArrCount; j++)
    {
        if (strcmp(subCatName,(*catArr)[i].subc[j].name)==0)
        {
            printf("Enter a new name : \n");
            scanf("%s",(*catArr)[i].subc[j].name);
            return;
        }
        
    }
    printf("Sub-Category not found");
}


void addProduct(categories **catArr,char catName[MAX_NAME_LENGTH],char subCatName[MAX_NAME_LENGTH],int elementCount,products **allProducts,int *allProductsCount){
    int i=0;
    while (strcmp((*catArr)[i].name,catName)!=0 && i!=elementCount)
    {
        i++;
    }
    if (i==elementCount) {
        printf("Category not found");
        return;
    }

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
               if(strcmp((*catArr)[i].subc[j].prod[k].name,new.name)) {
                printf("Product already exists, try 'Edit Products'");
                return;
                }
            }

            printf("Enter product's price : \n");
            scanf("%d",&new.price);
            printf("Enter product's status : \n");
            scanf("%d",&new.product_status);
            printf("Enter product's stock value : \n");
            scanf("%d",&new.stock_value);
            printf("Enter product's ID : \n");
            scanf("%d",&new.ID);

            (*catArr)[i].subc[j].prod=(products *) realloc((*catArr)[i].subc[j].prod,(++(*catArr)[i].subc[j].prodArrCount)*sizeof(products));
            (*catArr)[i].subc[j].prod[(*catArr)[i].subc[j].prodArrCount-1]=new;
            *allProducts=(products *) realloc(*allProducts,++*allProductsCount);
            (*allProducts)[*allProductsCount-1]=new;
            return;
        }
        
    }
    printf("Sub-Category not found");


}

void removeProduct(categories **catArr,char prodName[MAX_NAME_LENGTH],int elementCount,products **allProducts,int *allProductsCount){
    char cat[MAX_NAME_LENGTH];
    char subCat[MAX_NAME_LENGTH];
    for (int i = 0; i < *allProductsCount; i++)
    {
        if(strcmp(prodName,(*allProducts)[i].name)==0){
            strcpy(cat,(*allProducts)[i].category);
            strcpy(subCat,(*allProducts)[i].subCategory);
            products temp=(*allProducts)[i];
            (*allProducts)[i]=(*allProducts)[i+1];
            (*allProducts)[i+1]=temp;
        }
        
    }
    if(strcmp(prodName,(*allProducts)[*allProductsCount-1].name)!=0){
        printf("Product not found");
        return;
    }
    *allProducts=(products *) realloc(*allProducts,--*allProductsCount); 
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
          
    int productSize=(*catArr)[i].subc->prodArrCount;
    for (int k = 0; k < productSize; k++)
    {
        if(k+1 == productSize) break;
        if(strcmp((*catArr)[i].subc[j].prod[k].name,prodName)==0){
        products tmp;
        tmp=(*catArr)[i].subc[j].prod[k];
        (*catArr)[i].subc[j].prod[k]=(*catArr)[i].subc[j].prod[k+1];
        (*catArr)[i].subc[j].prod[k+1]=tmp;
        }              
    }
    (*catArr)[i].subc[j].prod=(products *) realloc((*catArr)[i].subc[j].prod,(--(*catArr)[i].subc[j].prodArrCount)*sizeof(products));
    

}
// we have to add product staaaaaaaaaaaaaaatuuuuuuuuuuuus
void editProduct(categories **catArr,char prodName[MAX_NAME_LENGTH],int elementCount,products **allProducts,int allProductsCount){
    char cat[MAX_NAME_LENGTH];
    char subCat[MAX_NAME_LENGTH];
    for (int i = 0; i < allProductsCount; i++)
    {
    
        if(strcmp(prodName,(*allProducts)[i].name)==0){
            strcpy(cat,(*allProducts)[i].category);
            strcpy(subCat,(*allProducts)[i].subCategory);
            printf("1- Edit name.\n");
            printf("2- Edit price.\n");
            printf("3- Edit stock value.\n");
            int edit;
            scanf("%d",&edit);
            switch (edit)
            {
            case 1:
                printf("Enter a new name");
                scanf("%s",(*allProducts)[i].name);
                break;
            case 2:
                printf("Enter a new price");
                scanf("%d",&(*allProducts)[i].price);
                break;
            case 3:
                printf("Enter a new stock value");
                scanf("%d",&(*allProducts)[i].stock_value);
                break;
            
            default:
                break;
            }
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
