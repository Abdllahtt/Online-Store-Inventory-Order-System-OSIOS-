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
    loadArray("customers.dat",(void **)&customerArr,sizeof(Customer),&customerCount);
    loadArray("allProducts.dat",(void **)&allProducts,sizeof(products),&productsCount);
    loadArray("categories.dat",(void **)&categoryArr,sizeof(categories),&categoryCount);
    loadSubCategories(categoryCount,&categoryArr);
    history *sTop=NULL;
    loadStack(&sTop);
    int choice;
    int p=1;
    while (p)
    {
        printf("=== Online Store Inventory & Orders System ===\n");
        printf("1 . Manage Products.\n");
        printf("2 . Manage Customers.\n");
        printf("3 . Manage Categories. \n");
        printf("4 . Manage Sub-Categories. \n");
        printf("5 . Browse Categories.\n");
        printf("6 . Search Products/Customers.\n");
        printf("7 . Place Order.\n");
        printf("8 . View Order Queue.\n");
        printf("9 . Display Browsing History.\n");
        printf("10 . Save Data to File.\n");
        printf("11 . Load Data from File.\n");
        printf("0. Exit.\n");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            clearScreen();
            productManagement(&categoryArr,categoryCount,&allProducts,&productsCount,&sTop);
            break;
        case 2:
            clearScreen();
            customerManagement(&customerArr,&customerCount);
            break;
        case 3:
            clearScreen();
            categoriesManagement(&categoryArr,&categoryCount);
            break;
        case 4:
            clearScreen();
            subCategoriesManagement(&categoryArr,categoryCount);
            break;
        case 5:
            clearScreen();
            browseCategories(categoryArr,categoryCount,allProducts,productsCount,&sTop);
            break;
        case 6:
            clearScreen();
            break;
        case 7:
            clearScreen();
            break;
        case 8:
            clearScreen();
            break;
        case 9:
            clearScreen();
            displayHistory(sTop);
            break;
        case 10:
            clearScreen();
            break;
        case 11:
            clearScreen();
            break;
        case 0:
            p=0;
            break;
        default:
            printf("Wrong number.");
            break;
        }
        clearScreen();
    }
    saveStack(sTop);
    saveArray("customers.dat",(void *)customerArr,sizeof(Customer),customerCount);
    saveArray("allProducts.dat",(void *)allProducts,sizeof(products),productsCount);
    saveArray("categories.dat",(void *)categoryArr,sizeof(categories),categoryCount);
    saveSubCategories(categoryCount,categoryArr);
    return 0;
}