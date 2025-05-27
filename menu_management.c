#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include <time.h>

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
    if (c1==0 || c1>catCount)
    {
        printf("Invalid choice.\n");
        int c5=1;
        printf("Enter 0 to return to the main menu.\n");
        while (c5)
        {
            scanf("%d",&c5);
        }
        return;
    }
    
    clearScreen();
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
    if (c2==0 || c2>categories[c1-1].subCArrCount)
    {
        printf("Invalid choice.\n");
        int c6=1;
        printf("Enter 0 to return to the main menu.\n");
        while (c6)
        {
            scanf("%d",&c6);
        }
        return;
    }
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
    printf("Enter 1 to display more info about a product | 0 to return to the main menu: \n");
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
    newNode->timeStamp= time(NULL);
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
        int i=1;
        printf("Enter 0 to return to the main menu\n");
        while (i)
        {
            scanf("%d",&i);
        }
        return;
    }
    while (top!=NULL)
    {
        printf("- %s | %s.\n",top->element,ctime(&(top->timeStamp)));
        top=top->next;
    }
    int c=1;
    printf("Enter 0 to return to the main menu\n");
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
void loadQueue(OrderQueue **queue){
    FILE *fp=fopen("queue.dat","rb");
    if (fp==NULL) return;
    
    while (1)
    {
        order data;
        if(fread(&data,sizeof(order),1,fp)!=1)return;
        data.products=(char **) malloc(sizeof(char *)*data.num_products);
        for (int i = 0; i < data.num_products; i++)
        {
            int len;
            fread(&len,sizeof(int),1,fp);
            data.products[i]=(char *)malloc(sizeof(char)*len);
            fread(data.products[i],sizeof(char),len,fp);
        }
        
        enqueueOrder(*queue,data);
        
    }
    fclose(fp);
}
void saveQueue(OrderQueue *queue){
    FILE *fp=fopen("queue.dat","wb");
    if(fp==NULL) return;
    while (queue->front!=NULL)
    {
        
        fwrite(&(queue->front->data),sizeof(order),1,fp);
        for (int i = 0; i < queue->front->data.num_products; i++)
        {
            int len=strlen(queue->front->data.products[i])+1;
            fwrite(&len,sizeof(int),1,fp);
            fwrite(&(queue->front->data.products[i]),sizeof(char)*len,1,fp);
        }
        
        queue->front=queue->front->next;
    }
    fclose(fp);
}

int manageOrder(products *allProducts,int productsCount,OrderQueue* myQueue ){
    if (myQueue == NULL) {
        return 1; // Exit if queue creation fails
    }

    int choice;
    int nextOrderId = 1001; // Starting ID for new orders

    do {
        printf("\n--- Online Store Management Menu ---\n");
        printf("1. Create and Place New Order (Customer)\n");
        printf("2. View Pending Orders (Admin)\n");
        printf("3. Process Order by ID (Admin)\n");
        printf("4. Mark Order as Succeeded by ID (Admin)\n");
        printf("5. Cancel Order by ID (Admin)\n");
        printf("6. View All Orders (Admin)\n");
        printf("7. View Current Inventory Stock\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: { // Create and Place New Order
                char customerName[MAX_NAME_LENGTH];
                printf("Enter customer name: ");
                scanf("%s", customerName); // Simplified input, no spaces

                order* newOrder = createOrder(nextOrderId++, customerName);
                if (newOrder == NULL) {
                    break;
                }

                printf("--- Adding products to Order %d (Enter 0 or 'done' to finish cart) ---\n", newOrder->ID);
                int addMore = 1;
                while (addMore) {
                    printf("  Add product (type 'done' or 0 to finish adding): ");
                    // add_product_cart will internally handle the product name/ID input
                    if (add_product_cart(newOrder, allProducts, productsCount) == -1) {
                         // If product not found or out of stock, give option to continue adding others
                         printf("  Continue adding other products to this order? (1 for Yes, 0 for No): ");
                         scanf("%d", &addMore);
                    } else {
                        printf("  Add another product to this order? (1 for Yes, 0 for No): ");
                        scanf("%d", &addMore);
                    }
                }
                
                // Only enqueue if there are products in the cart
                if (newOrder->num_products > 0) {
                    enqueueOrder(myQueue, *newOrder);
                    // After enqueuing, the 'newOrder' struct (local variable) is a shallow copy.
                    // Its internal 'products' array memory needs to be freed from 'newOrder'
                    // because the queue node now has its own deep copy.
                    freeOrderMemory(*newOrder); // Free the temp 'newOrder' local struct's memory
                    free(newOrder); // Free the newOrder pointer itself
                } else {
                    printf("Order %d has no products and will not be placed.\n", newOrder->ID);
                    freeOrderMemory(*newOrder);
                    free(newOrder);
                }
                break;
            }
            case 2: // View Pending Orders
                viewPendingOrders(myQueue);
                break;
            case 3: { // Process Order by ID
                int idToProcess;
                printf("Enter Order ID to PROCESS: ");
                scanf("%d", &idToProcess);
                processOrderById(myQueue, idToProcess);
                break;
            }
            case 4: { // Mark Order as Succeeded by ID
                int idToSucceed;
                printf("Enter Order ID to mark SUCCEEDED: ");
                scanf("%d", &idToSucceed);
                markOrderSucceededById(myQueue, idToSucceed);
                break;
            }
            case 5: { // Cancel Order by ID
                int idToCancel;
                printf("Enter Order ID to CANCEL: ");
                scanf("%d", &idToCancel);
                cancelOrderById(myQueue, idToCancel,allProducts, productsCount);
                break;
            }
            case 6: // View All Orders
                viewAllOrders(myQueue);
                break;
            case 7: { // View Current Inventory Stock
                printf("\n--- Current Inventory Stock ---\n");
                for (int i = 0; i < productsCount; i++) {
                    printf("ID: %d, Name: %s, Stock: %d, Price: %.2f\n",
                           allProducts[i].ID, allProducts[i].name, allProducts[i].stock_value, allProducts[i].price);
                }
                printf("-------------------------------\n");
                break;
            }
            case 8: // Exit
                printf("Exiting program. Freeing all memory...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);

    //freeOrderQueue(myQueue); // Free all allocated memory for the queue and orders
    return 0;
}
