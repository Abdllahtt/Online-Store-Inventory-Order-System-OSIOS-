#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


//CONSTANTS

#define MAX_PRODUCTS 999
#define MAX_CUSTOMERS 500
#define MAX_NAME_LENGTH 50


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
    PROCESSING,
    PROCESSED,
    CANCELLED,
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
    char Customer_name[MAX_NAME_LENGTH];
    char **products;// dynamic array product names
    int num_products;
    int product_capacity;
    OrderStatus order_status;
    time_t orderPlacedTime;// added for timestamping
    double totalAmount; // added to calculate the total amount order value
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
    PROCESSED,
    CANCELLED,
    SUCCEEDED
};

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


//get an array of categories from the products array without occurences 
char **getUniquecategories(products product[],int numproduct,int *uniqueCount);


//displays categories 
void displaycategories(char **categories,int count);

// display products
void displayProduct(const products* product);

//search a product by name or Id 
products  *findproduct(products inventory[], int Numproduct);
void assigne_status(products  *product);
void loadArray(const char fileName[],void *array,int elementSize,int *count);
void saveArray(const char fileName[],const void *array,int elementSize,int count);
void loadProducts(int arrNum,subCategories *arr[]);
void loadSubCategories(int arrNum,categories *arr[]);

//CRUD categories 
void addCategory(categories *arr,int *elementCount);
void removeCategory(categories *arr,int *elementCount,char catName[MAX_NAME_LENGTH]);
void editCategory(categories *arr,int *elementCount,char catName[MAX_NAME_LENGTH]);

//CRUD subcategories
void addSubCategory(char catName[MAX_NAME_LENGTH],categories *catArr,int elementCount);
void removeSubCategory(char catName[MAX_NAME_LENGTH],char subCatName[MAX_NAME_LENGTH],categories *catArr,int elementcount);
void editSubCategory(char catName[MAX_NAME_LENGTH],char subCatName[MAX_NAME_LENGTH],categories *catArr,int elementcount);

//    -------------from order.c--------------------------
//create an order node in thr queue 
order* createOrder(int id, const char* name);

//add product to the subarray in the order's node 
int add_product_cart(order *current_order, products inventory[], int numProductsInInventory);

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

// --- Helper function to get status as string ---
const char* getStatusString(OrderStatus status);

// Helper to print order details
void printOrderDetails(const order *ord);

// View all orders currently in the queue (regardless of status)
void viewAllOrders(OrderQueue* queue);

// View only pending orders
void viewPendingOrders(OrderQueue* queue);

// Find an order by ID in the queue
Node* findOrderNodeInQueue(OrderQueue* queue, int orderId);


// Simulate processing an order by ID (changes status and deducts inventory)

void processOrderById(OrderQueue* queue, int orderId);

// Simulate marking an order as succeeded by ID
void markOrderSucceededById(OrderQueue* queue, int orderId);

// Simulate canceling an order by ID (returns stock)
void cancelOrderById(OrderQueue* queue, int orderId,products inventory[],int numProductsInInventory);


#endif