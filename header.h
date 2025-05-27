#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

//CONSTANTS

#define MAX_PRODUCTS 999
#define MAX_CUSTOMERS 500
#define MAX_NAME_LENGTH 50

void clearScreen();
//STRUCTS

typedef struct stack
{
    char element[MAX_NAME_LENGTH];
    struct stack *next;
}history;

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

//ENUMERATORS

typedef enum {
    WAITING,
    UNDER_TREATMENT,
    DISCHARGED
}customerStatus;

 typedef enum {
    AVAILABLE,
    OUT_OF_STOCK,
    DISCONTINUED
}productStatus;

typedef enum {
    PENDING,
    PROCESSED,
    CANCELLED
}OrderStatus;

typedef struct warehouse{
    //might not be used
}warehouse;

typedef struct customer {
    int ID;
    char name[MAX_NAME_LENGTH];
    customerStatus customer_status;
} Customer;
typedef struct orders{
    int ID;
    char name[MAX_NAME_LENGTH];
    char **products;
    int num_products;
    int product_capacity;
    OrderStatus order_status;
}order;

typedef struct products{
    char category[MAX_NAME_LENGTH];
    char subCategory[MAX_NAME_LENGTH];
    char name[MAX_NAME_LENGTH];
    int ID;
    int price;
    int stock_value;
    productStatus product_status;
}products;

typedef struct subCategories{
    char name[MAX_NAME_LENGTH];
    int prodArrCount;
    products *prod;
}subCategories;

typedef struct categories{
    char name[MAX_NAME_LENGTH];
    int subCArrCount;
    struct subCategories *subc;
}categories;
 


typedef struct Node {
    order data;
    struct Node* next;
} Node;

// Define the structure for the queue
typedef struct CustomerQueue { // Renaming to OrderQueue for consistency
    Node* front;
    Node* rear;
    int size;
} OrderQueue;
//FUNCTIONS

void saveProductsArray(products *productsArr,int productsCount);
void loadProductsArray(products *productsArr,int *productsCount);

// display products
void displayProduct(const products* product);

//search a product by name or Id 
products  *findProduct(products inventory[], int Numproduct,history **top);
void assigne_status(products  *product);
void loadArray(const char fileName[],void **array,int elementSize,int *count);
void saveArray(const char fileName[],const void *array,int elementSize,int count);
void loadProducts(int arrNum,subCategories **arr);
void loadSubCategories(int arrNum,categories **arr);

//CRUD categories 
void addCategory(categories **arr,int *elementCount);
void removeCategory(categories **arr,int *elementCount);
void editCategory(categories **arr,int *elementCount);
void displayCategories(categories *categories,int count);
//CRUD subcategories
void addSubCategory(categories **catArr,int elementCount);
void removeSubCategory(categories **catArr,int elementcount);
void editSubCategory(categories **catArr,int elementcount);
void displaySubCategories(char catName[MAX_NAME_LENGTH],subCategories *subCat,int count);
//CRUD products
void addProduct(categories **catArr,int elementCount,products **allProducts,int *allProductsCount);
void removeProduct(categories **catArr,int elementCount,products **allProducts,int *allProductsCount);
void editProduct(categories **catArr,int elementCount,products **allProducts,int allProductsCount);
void displayProducts(char subCatName[MAX_NAME_LENGTH],products *prods,int count);
//CRUD customer
void addCustomer(Customer **customerArr,int *elementCount);
void removeCustomer(Customer **customerArr,int *elementCount);
void editCustomer(Customer **customerArr,int *elementCount);
//create an order node in thr queue 
order* createOrder(int id, const char* name);

//add product to the subarray in the order's node 
int add_product_cart(order *current_order, const char *product_name);

// function to see if a order's queue is empty
bool isEmpty(OrderQueue* queue);

// create the order's queue
 OrderQueue* create_OrderQueue();

// enqueue into the order's queue 
void enqueueOrder(OrderQueue* queue, order current_order);


//dequeue order from the order's queue 
order dequeueOrder(OrderQueue* queue);

// free a queue node (order)
void freeOrderMemory(order current_order);

// free the entire queue 
void freeOrderQueue(OrderQueue* queue);

//menu management functions
void productManagement(categories **catArr,int elementCount,products **allProducts,int *allProductsCount,history **top);
void customerManagement(Customer **customerArr,int *elementCount);
void subCategoriesManagement(categories **catArr,int elementCount);
void categoriesManagement(categories **arr,int *elementCount);
void browseCategories(categories *categories,int catCount,products *allProducts,int allProductsCount,history **top);
void addToHistory(history **top,char elementName[MAX_NAME_LENGTH]);
void deleteFromHistory(history **top);
int isEmptyStack(history *top);
void displayHistory(history *top);
void clearBrowsingHistory(history **top);
void displayAllCustomers(Customer *customerArr,int elementcount);
#endif