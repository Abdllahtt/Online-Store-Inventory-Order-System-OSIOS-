#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

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



typedef struct warehouse{
    //might not be used
}warehouse;

typedef struct customer {
    int id;
    char name[MAX_NAME_LENGTH];
    char **products;
    int num_products;
} Customer;

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
typedef struct Node {
    Customer data;
    struct Node* next;
} Node;

// Define the structure for the queue
typedef struct {
    Node* front;
    Node* rear;
    int size;
} CustomerQueue;
//FUNCTIONS

void saveProductsArray(products *productsArr,int productsCount);



void loadProductsArray(products *productsArr,int *productsCount);


//get an array of categories from the products array without occurences 
char **getUniquecategories(products product[],int numproduct,int *uniqueCount);


//displays categories 
void displaycategories(char **categories,int count);


//search a product by name or Id 
void findname(products inventory[], int Numproduct);


//this function let you add product to the array "cart or product " associated to a customers 
int add_product_cart(Customer *customer, const char *product_name);

bool isEmpty(CustomerQueue* queue);

//innit customers queue
CustomerQueue* createCustomerQueue();


//add a customer to the queue 
void enqueueCustomer(CustomerQueue* queue, Customer customer);




//remove a customer from the queue 
Customer dequeueCustomer(CustomerQueue* queue);


//free the memory of a customer including the array of product he wants Id name 
void freeCustomerMemory(Customer customer);

//free the memory allocated for a single customer (for remove eventually)
void freeCustomerQueue(CustomerQueue* queue);







#endif