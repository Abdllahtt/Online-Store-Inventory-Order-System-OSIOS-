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

void clearScreen();

//STRUCTS

typedef struct stack
{
    char element[MAX_NAME_LENGTH];
    time_t timeStamp;
    struct stack *next;
}history;

typedef enum {
    PENDING,
    PROCESSING,
    PROCESSED,
    CANCELLED,
    SUCCEEDED
}OrderStatus;


typedef struct customer {
    int ID;
    char name[MAX_NAME_LENGTH];
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


// display products
void displayProduct(const products* product);
//search customers
void displayCustomer(const Customer* customer);
Customer* findcustomer(Customer *customerArr, int customerCount);
void clearInputBuffer();
//search a product by name or Id 
products  *findproduct(products inventory[], int Numproduct);
products *findProductsDelux(products *allProducts,int allProductsCount,history **top);
void assigne_status(products  *product);
void loadArray(const char fileName[],void **array,int elementSize,int *count);
void saveArray(const char fileName[],const void *array,int elementSize,int count);
void loadProducts(int arrNum,subCategories **arr);
void loadSubCategories(int arrNum,categories **arr);
void loadStack(history **top);
void saveStack(history *top);
void loadQueue(OrderQueue **queue);
void saveQueue(OrderQueue *queue);
void saveProducts(int arrNum,subCategories *arr);
void saveSubCategories(int arrNum,categories *arr);
//CRUD categories 
void addCategory(categories **arr,int *elementCount);
void removeCategory(categories **arr,int *elementCount);
void editCategory(categories **arr,int *elementCount);
void displayCategories(categories *categories,int count);
int isEmptyCategories(int count);
//CRUD subcategories
void addSubCategory(categories **catArr,int elementCount);
void removeSubCategory(categories **catArr,int elementcount);
void editSubCategory(categories **catArr,int elementcount);
void displaySubCategories(char catName[MAX_NAME_LENGTH],subCategories *subCat,int count);
int isEmptySubCategories(int count);
//CRUD products
void addProduct(categories **catArr,int elementCount,products **allProducts,int *allProductsCount);
void removeProduct(categories **catArr,int elementCount,products **allProducts,int *allProductsCount);
void editProduct(categories **catArr,int elementCount,products **allProducts,int allProductsCount);
void displayProducts(char subCatName[MAX_NAME_LENGTH],products *prods,int count);
int isEmptyProducts(int count);
//CRUD customer
void addCustomer(Customer **customerArr,int *elementCount);
void removeCustomer(Customer **customerArr,int *elementCount);
void editCustomer(Customer **customerArr,int *elementCount);
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

//menu management functions
int manageOrder(products *allProducts,int productsCount,OrderQueue* myQueue,Customer **customerArr,int *customerCount );
void search_function(products *allproduct,int productsCount,Customer *customerArr, int customerCount);
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
