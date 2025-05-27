#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

//make new find product function
void productManagement(categories **catArr,int elementCount,products **allProducts,int *allProductsCount,history **top){
    int choice;
    printf("=== Product Management ===\n");
    printf("1 . Add Product.\n");
    printf("2 . Edit Product.\n");
    printf("3 . View Product.\n");
    printf("4 . Delete Product.\n");
    printf("5 . Back.\n");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        addProduct(catArr,elementCount,allProducts,allProductsCount);
        break;
    case 2:
        clearScreen();
        editProduct(catArr,elementCount,allProducts,*allProductsCount);
        break;
    case 3:
        clearScreen();
        char name[50]="All Products.";
        if(*allProductsCount==0){
        printf("There are no products");
        int c=1;
        printf("Enter 0 to go back to the main menu:\n");
        while (c)
        {
            scanf("%d",&c);
        }
        
        return;
    }
        displayProducts(name,*allProducts,*allProductsCount);
        printf("\n");
        int p=1;
        displayProduct(findProductsDelux(*allProducts,*allProductsCount,top));////BIG BLACK cPROBLEM
        printf("Enter 0 to return to the main menu: \n");
        while (p)
        {
            scanf("%d",&p);
        }
        
        break;
    case 4:
        clearScreen();
        removeProduct(catArr,elementCount,allProducts,allProductsCount);
        break;
    case 5:
        return;
        break;
    default:
        printf("Wrong number.\n");
            int c=1;
            printf("Enter 0 to return to the main menu: \n");
            while (c)
            {
                scanf("%d",&c);
            }
            
            break;
    }
    clearScreen();
}
//remove view customer
void customerManagement(Customer **customerArr,int *elementCount){
    int choice;
    printf("=== Customer Management ===\n");
    printf("1 . Add Customer.\n");
    printf("2 . Edit Customer.\n");
    printf("3 . display Customers.\n");
    printf("4 . Delete Customer.\n");
    printf("5 . Back.\n");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        clearScreen();
        addCustomer(customerArr,elementCount);
        break;
    case 2:
        clearScreen();
        if (*elementCount==0)
        {
            printf("There are no customers. \n");
            int j=1;
            printf("Enter 0 to return to the main menu: \n");
            while (j)
            {
                scanf("%d",&j);
            }
            return;
        }
        
        
        displayAllCustomers(*customerArr,*elementCount);
        editCustomer(customerArr,elementCount);
        break;
    case 3:
        int p=1;
        clearScreen();
        displayAllCustomers(*customerArr,*elementCount);
        printf("Enter 0 to go back to the main menu.");
        while (p)
        {
            scanf("%d",&p);
        }
        
        break;
    case 4:
        clearScreen();
        if (*elementCount==0)
        {
            printf("There are no customers. \n");
            int g=1;
            printf("Enter 0 to return to the main menu: \n");
            while (g)
            {
                scanf("%d",&g);
            }
            return;
        }
        displayAllCustomers(*customerArr,*elementCount);
        removeCustomer(customerArr,elementCount);
        break;
    case 5:
        clearScreen();
        int c=1;
        displayAllCustomers(*customerArr,*elementCount);
        printf("Enter 0 to return to the main menu: \n");
        while (c)
        {
            scanf("%d",&c);
        }
        break;
    default:
        printf("Wrong number.\n");
            int l=1;
            printf("Enter 0 to return to the main menu: \n");
            while (l)
            {
                scanf("%d",&l);
            }
            
            break;
    }
    clearScreen();
}

void subCategoriesManagement(categories **catArr,int elementCount){
    int choice;
    printf("=== Sub-Categories Management ===\n");
    printf("1 . Add Sub-Category.\n");
    printf("2 . Remove Sub-Category.\n");
    printf("3 . Edit Sub-Category.\n");
    printf("4 . back.\n");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        clearScreen();
        if(isEmptyCategories(elementCount)==0) return;
        displayCategories(*catArr,elementCount);
        addSubCategory(catArr,elementCount);
        break;
    case 2:
        clearScreen();
        if(isEmptyCategories(elementCount)==0) return;
        displayCategories(*catArr,elementCount);
        removeSubCategory(catArr,elementCount);
        break;
    case 3:
        clearScreen();
        if(isEmptyCategories(elementCount)==0) return;
        displayCategories(*catArr,elementCount);
        editSubCategory(catArr,elementCount);
        break;
    case 4:
        return;
        break;
    default:
        printf("Wrong number.\n");
            int c=1;
            printf("Enter 0 to return to the main menu: \n");
            while (c)
            {
                scanf("%d",&c);
            }
            
            break;
    }
    clearScreen();
}

void categoriesManagement(categories **arr,int *elementCount){
    int choice;
    printf("=== Categories Management ===\n");
    printf("1 . Add Category.\n");
    printf("2 . Remove Category.\n");
    printf("3 . Edit Category.\n");
    printf("4 . back.\n");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        clearScreen();
        addCategory(arr,elementCount);
        break;
    case 2:
        clearScreen();

        removeCategory(arr,elementCount);
        break;
    case 3:
        clearScreen();
        editCategory(arr,elementCount);
        break;
    case 4:
        return;
        break;
    default:
        printf("Wrong number.\n");
            int c=1;
            printf("Enter 0 to return to the main menu: \n");
            while (c)
            {
                scanf("%d",&c);
            }
            
            break;
    }
    clearScreen();
}

void browseCategories(categories *categories,int catCount,products *allProducts,int allProductsCount,history **top){
    int c1;
    int c2;
    int c3;
    if(catCount==0){
        printf("There are no categories. \n");
        int c4=1;
        printf("Enter 0 to return to the main menu.\n");
        while (c4)
        {
            scanf("%d",&c4);
        }
        return;
        
    }
    displayCategories(categories,catCount);
    printf("Enter the number of the category you want to show: \n");
    scanf("%d",&c1);
    clearScreen();
    printf("\n");
    if (categories[c1-1].subCArrCount==0)
    {
        printf("There are no sub-categories\n");
        printf("Enter 0 to return to the main menu\n");
        int op=1;
        while (op)
        {
            scanf("%d",&op);
        }
        return;
    }
    displaySubCategories(categories[c1-1].name,categories[c1-1].subc,categories[c1-1].subCArrCount);
    printf("Enter the number of the sub-category you want to show: \n");
    scanf("%d",&c2);
    clearScreen();
    if (categories[c1-1].subc[c2-1].prodArrCount==0)
    {
        printf("There are no products\n");
        int po=1;
        printf("Enter 0 to return to the main menu\n");
        while (po)
        {
            scanf("%d",&po);
        }
        
        return;
    }
    displayProducts(categories[c1-1].subc[c2-1].name,categories[c1-1].subc[c2-1].prod,categories[c1-1].subc[c2-1].prodArrCount);
    printf("Enter 1 to display more info about a product, any key to go back to the main menu: \n");
    scanf("%d",&c3);
    switch (c3)
    {
    case 1:
        int c=1;
        displayProduct(findProductsDelux(allProducts,allProductsCount,top));
        printf("Enter 0 to go back to the main menu: \n");
        while(c){
            scanf("%d",&c);
        }
        break;
    default:
        return;    
        break;
    }
}


void addToHistory(history **top,char elementName[MAX_NAME_LENGTH]){
    history *newNode=(history *)malloc(sizeof(history));
    if (newNode==NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    strcpy(newNode->element,elementName);
    newNode->next=*top;
    *top=newNode;
    return;
}
void deleteFromHistory(history **top){
    if (isEmptyStack(*top)==1)
    {
        printf("History is empty\n");
        return;
    }else{
        history *tmp=*top;
        *top=(*top)->next;
        free(tmp);
        return;
    }
    
}
int isEmptyStack(history *top){
    if (top==NULL)
    {
        return 1;
    }else{
        return 0;
    }
    
}
void displayHistory(history *top){
    if(isEmptyStack(top)==1){
        printf("History is empty\n");
        return;
    }
    while (top!=NULL)
    {
        printf("- %s .\n",top->element);
        top=top->next;
    }
    int c=1;
    printf("Enter 0 to return to the main menu");
    while (c)
    {
        scanf("%d",&c);
    }
    
    
}
void clearBrowsingHistory(history **top){
    if (isEmptyStack(*top)==1)
    {
        printf("Stack is empty\n");
    }
    
    while (*top!=NULL)
    {
        deleteFromHistory(top);
        *top=(*top)->next;
    }
    
}
void loadStack(history **top){
    FILE *fp=fopen("history.dat","rb");
    if (fp==NULL) return;
    char data[MAX_NAME_LENGTH];
    history *tail=NULL;
    while (fread(&data,sizeof(char)*MAX_NAME_LENGTH,1,fp)==1)
    {
        history *newNode=(history *)malloc(sizeof(history));
        strcpy(newNode->element,data);
        if (*top==NULL)
        {
            *top=newNode;
            tail=newNode;
        }else{
            tail->next=newNode;
            tail=newNode;
        }
        
    }
    fclose(fp);
}
void saveStack(history *top){
    FILE *fp=fopen("history.dat","wb");
    if(fp==NULL) return;
    while (top!=NULL)
    {
        fwrite(&(top->element),sizeof(char)*MAX_NAME_LENGTH,1,fp);
        top=top->next;
    }
    fclose(fp);
}