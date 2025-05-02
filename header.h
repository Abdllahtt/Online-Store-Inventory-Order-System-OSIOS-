#ifndef STRUCTURES_H
#define STRUCTURES_H
//CONSTANTS

#define MAX_PRODUCTS 999
#define MAX_CUSTOMERS 500
#define MAX_NAME_LENGTH 50
#define MAX_CATEGORY_LENGTH 50
#define MAX_SUBCATEGORY_LENGTH 50

//STRUCTS

/*typedef struct tree{
    products *product;
    struct tree *left;
    struct tree *right;
}tree;*/


/*typedef struct categoryTree{
    // for store structure tree in modeling section
    //idea is to create a list for main categories ex:electronics,kids section.
    //which will be linked by next ptr
    //down ptr is for the first child and the next of the first child will have his brothers and so on
    char name[MAX_NAME_LENGTH];
    struct categoryTree *next;
    struct categoryTree *down;
}categoryTree;*/

typedef struct sll{
    //might not be used
}sll;

typedef struct warehouse{
    //might not be used
}warehouse;

typedef struct customers{
    char name[MAX_NAME_LENGTH];
    int ID;
}customers;

typedef struct products{
    char category[MAX_CATEGORY_LENGTH];
    char subCategory[MAX_SUBCATEGORY_LENGTH];
    char name[MAX_NAME_LENGTH];
    int ID;
    int price;
    int stock_value;
    int status;
}products;

//ENUMERATORS

enum customerStatus{
    WAITING,
    UNDER_TREATMENT,
    DISCHARGED
};

enum productStatus{
    AVAILABLE,
    OUT_OF_STOCK,
    DISCONTINUED
};

enum orderStatus{
    PENDING,
    PROCESSED,CANCELLED
};

//FUNCTIONS

void saveProductsArray(products *productsArr,int productsCount);
void loadProductsArray(products *productsArr,int *productsCount);
char **getUniquecategories(products product[],int numproduct,int *uniqueCount);
void displaycategories(char **categories,int count);


#endif