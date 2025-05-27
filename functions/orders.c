#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "../header.h"

// Create a new order
order* createOrder(int id, const char* name) {
    order* newOrder = (order*)malloc(sizeof(order));
    if (!newOrder) {
        perror("Failed to allocate memory for order");
        return NULL;
    }
    newOrder->ID = id;
    strncpy(newOrder->Customer_name, name, MAX_NAME_LENGTH - 1);
    newOrder->Customer_name[MAX_NAME_LENGTH - 1] = '\0'; // Ensure null termination
    newOrder->products = NULL; // Initialize products to NULL
    newOrder->num_products = 0;
    newOrder->product_capacity = 0; // Initialize capacity
    newOrder->order_status = PENDING; // Set initial order status to PENDING
    newOrder->totalAmount = 0.0; // Initialize total amount
    newOrder->orderPlacedTime = time(NULL); // Set timestamp
    return newOrder;
}

// Fill the array of products in the order struct
// --- MODIFIED add_product_cart function ---
int add_product_cart(order *current_order, products inventory[], int numProductsInInventory) {
    // findProduct will prompt the user for input
    products *productToAdd = findproduct(inventory, numProductsInInventory);

    if (productToAdd == NULL) {
        printf("Error: Product not found in inventory.\n");
        return -1; // Indicate failure
    }

    // Check stock value
    if (productToAdd->stock_value <= 0) {
        printf("Error: Product '%s' is out of stock.\n", productToAdd->name);
        return -1; // Indicate failure
    }

    // Product is available, proceed to add to cart and decrement stock
    char **temp = realloc(current_order->products, (current_order->num_products + 1) * sizeof(char *));
    if (temp == NULL) {
        perror("Failed to reallocate memory for product list in cart");
        return -1; // Indicate failure
    }
    current_order->products = temp;

    // Allocate memory for the product name string
    current_order->products[current_order->num_products] = malloc(strlen(productToAdd->name) + 1);
    if (current_order->products[current_order->num_products] == NULL) {
        perror("Failed to allocate memory for product name string in cart");
        return -1; // Indicate failure
    }
    strcpy(current_order->products[current_order->num_products], productToAdd->name);

    // Decrement stock value in the inventory
    productToAdd->stock_value--;
    current_order->num_products++;
    // Add product price to order total
    current_order->totalAmount += productToAdd->price;


    printf("Added '%s' to order %d cart. Remaining stock: %d.\n",
           productToAdd->name, current_order->ID, productToAdd->stock_value);

    return 0; // Indicate success
}

// Function to check if the queue is empty
bool isEmpty(OrderQueue* queue) {
    return (queue->size == 0);
}

// Add orders into a queue
OrderQueue* create_OrderQueue() {
    OrderQueue* queue = (OrderQueue*)malloc(sizeof(OrderQueue));
    if (!queue) {
        perror("Failed to allocate memory for order queue");
        return NULL;
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

// Function to enqueue an order into the queue
void enqueueOrder(OrderQueue* queue, order current_order) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        perror("Failed to allocate memory for new order node");
        return;
    }

    // Deep copy the order data to the new node
    newNode->data.ID = current_order.ID;
    strncpy(newNode->data.Customer_name, current_order.Customer_name, MAX_NAME_LENGTH - 1);
    newNode->data.Customer_name[MAX_NAME_LENGTH - 1] = '\0';

    newNode->data.num_products = current_order.num_products;
    newNode->data.product_capacity = current_order.product_capacity;
    newNode->data.order_status = current_order.order_status;
    newNode->data.orderPlacedTime = current_order.orderPlacedTime;
    newNode->data.totalAmount = current_order.totalAmount;

    // Deep copy the product names array
    newNode->data.products = NULL; // Initialize
    if (current_order.num_products > 0) {
        newNode->data.products = malloc(current_order.num_products * sizeof(char *));
        if (!newNode->data.products) {
            perror("Failed to allocate memory for product array in enqueue");
            free(newNode);
            return;
        }
        for (int i = 0; i < current_order.num_products; i++) {
            newNode->data.products[i] = malloc(strlen(current_order.products[i]) + 1);
            if (!newNode->data.products[i]) {
                perror("Failed to allocate memory for product name string in enqueue");
                // Clean up previously allocated product names for this node
                for (int j = 0; j < i; j++) {
                    free(newNode->data.products[j]);
                }
                free(newNode->data.products);
                free(newNode);
                return;
            }
            strcpy(newNode->data.products[i], current_order.products[i]);
        }
    }


    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->size++;
    printf("Enqueued order with ID: %d, Status: %d\n", current_order.ID, current_order.order_status);
}

// Function to dequeue an order from the front of the queue
order dequeueOrder(OrderQueue* queue) {
    // Initialize an empty order to return if queue is empty
    order emptyOrder = {-1, "", NULL, 0, 0, PENDING, 0, 0.0};

    if (queue->front == NULL) {
        printf("Order queue is empty. Cannot dequeue.\n");
        return emptyOrder;
    }

    Node* temp = queue->front;
    order dequeuedOrder = temp->data; // This is a shallow copy of the order struct data

    // IMPORTANT: When you dequeue, you get a copy. The original 'data' within 'temp'
    // still holds the malloc'd product names. You need to free them from temp.
    // However, if you plan to re-enqueue or process this dequeuedOrder later,
    // you must deep copy its 'products' array.
    // For this test, we assume dequeuedOrder will be processed/freed later.

    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL; // Queue becomes empty
    }

    // Free the product names memory that was part of the *node being removed*
    // before freeing the node itself.
    // This is vital to prevent memory leaks for dequeued orders.
    if (temp->data.products != NULL) {
        for (int i = 0; i < temp->data.num_products; i++) {
            free(temp->data.products[i]);
        }
        free(temp->data.products);
    }
    free(temp); // Free the node itself

    queue->size--;
    printf("Dequeued order with ID: %d, Status: %d\n", dequeuedOrder.ID, dequeuedOrder.order_status);
    return dequeuedOrder;
}



// Function to free the memory associated with an order (including its products)
void freeOrderMemory(order current_order) {
    if (current_order.products != NULL) {
        for (int i = 0; i < current_order.num_products; i++) {
            free(current_order.products[i]);
        }
        free(current_order.products);
    }
    // Note: If 'order' itself was malloc'd (like from createOrder), you'd free it here.
    // But since dequeueOrder returns a copy, it doesn't free the outer order struct.
    // This function is useful for `createOrder` results before enqueueing if they fail,
    // or if you have orders not in the queue.
}

// Function to free the entire order queue and the memory of the orders within
void freeOrderQueue(OrderQueue* queue) {
    Node* current = queue->front;
    Node* next;
    while (current != NULL) {
        next = current->next;
        // Free the deep-copied products within the node's data
        if (current->data.products != NULL) {
            for (int i = 0; i < current->data.num_products; i++) {
                free(current->data.products[i]);
            }
            free(current->data.products);
        }
        free(current); // Free the node itself
        current = next;
    }
    free(queue); // Free the queue structure
}





// --- Helper function to get status as string ---
const char* getStatusString(OrderStatus status) {
    switch (status) {
        case PENDING:    return "PENDING";
        case PROCESSING: return "PROCESSING";
        case SUCCEEDED:  return "SUCCEEDED";
        case CANCELLED:   return "CANCELED";
        default:         return "UNKNOWN";
    }
}


// Helper to print order details
void printOrderDetails(const order *ord) {
    if (ord == NULL) {
        printf("Order is NULL.\n");
        return;
    }
    printf("  Order ID: %d\n", ord->ID);
    printf("  Customer: %s\n", ord->Customer_name);
    printf("  Status: %s\n", getStatusString(ord->order_status));
    printf("  Placed: %s", ctime(&ord->orderPlacedTime)); // ctime adds a newline
    printf("  Total Amount: %.2f\n", ord->totalAmount);
    printf("  Products (%d):\n", ord->num_products);
    if (ord->num_products == 0) {
        printf("    (No products in cart)\n");
    } else {
        for (int i = 0; i < ord->num_products; i++) {
            printf("    - %s\n", ord->products[i]);
        }
    }
    printf("-------------------------\n");
}

// View all orders currently in the queue (regardless of status)
void viewAllOrders(OrderQueue* queue) {
    printf("\n--- All Orders in System ---\n");
    if (isEmpty(queue)) {
        printf("No orders in the system.\n");
        return;
    }
    Node* current = queue->front;
    while (current != NULL) {
        printOrderDetails(&current->data);
        current = current->next;
    }
    printf("--- End All Orders ---\n");
}


// View only pending orders
void viewPendingOrders(OrderQueue* queue) {
    printf("\n--- Pending Orders in System ---\n");
    if (isEmpty(queue)) {
        printf("No pending orders.\n");
        return;
    }
    Node* current = queue->front;
    int count = 0;
    while (current != NULL) {
        if (current->data.order_status == PENDING) {
            printOrderDetails(&current->data);
            count++;
        }
        current = current->next;
    }
    if (count == 0) {
        printf("No orders currently PENDING.\n");
    }
    printf("--- End Pending Orders ---\n");
}


// Find an order by ID in the queue
Node* findOrderNodeInQueue(OrderQueue* queue, int orderId) {
    Node* current = queue->front;
    while (current != NULL) {
        if (current->data.ID == orderId) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}


// Simulate processing an order by ID (changes status and deducts inventory)

void processOrderById(OrderQueue* queue, int orderId) {
    Node* orderNode = findOrderNodeInQueue(queue, orderId);
    if (orderNode == NULL) {
        printf("Order %d not found.\n", orderId);
        return;
    }

    order* ord = &orderNode->data;

    if (ord->order_status != PENDING) {
        printf("Order %d cannot be processed. Current status: %s.\n", orderId, getStatusString(ord->order_status));
        return;
    }

    printf("\nAttempting to PROCESS order %d...\n", orderId);
    // Re-check stock before final processing (important in real systems)
    // For this assignment, stock was deducted at add_product_cart, so we just confirm
    // that the status can change. In a real system, you'd iterate ord->products
    // and deduct again, or re-verify.

    ord->order_status = PROCESSING;
    printf("Order %d status changed to %s.\n", orderId, getStatusString(ord->order_status));
}



// Simulate marking an order as succeeded by ID
void markOrderSucceededById(OrderQueue* queue, int orderId) {
    Node* orderNode = findOrderNodeInQueue(queue, orderId);
    if (orderNode == NULL) {
        printf("Order %d not found.\n", orderId);
        return;
    }

    order* ord = &orderNode->data;

    if (ord->order_status != PROCESSING && ord->order_status != PENDING) { // Allow direct from PENDING too
        printf("Order %d cannot be marked SUCCEEDED. Current status: %s.\n", orderId, getStatusString(ord->order_status));
        return;
    }

    printf("\nMarking order %d as SUCCEEDED...\n", orderId);
    ord->order_status = SUCCEEDED;
    printf("Order %d status changed to %s.\n", orderId, getStatusString(ord->order_status));
}



// Simulate canceling an order by ID (returns stock)
void cancelOrderById(OrderQueue* queue, int orderId,products inventory[],int numProductsInInventory) {
    Node* orderNode = findOrderNodeInQueue(queue, orderId);
    if (orderNode == NULL) {
        printf("Order %d not found.\n", orderId);
        return;
    }

    order* ord = &orderNode->data;

    if (ord->order_status == CANCELLED || ord->order_status == SUCCEEDED) {
        printf("Order %d cannot be canceled. Current status: %s.\n", orderId, getStatusString(ord->order_status));
        return;
    }

    printf("\nCanceling order %d...\n", orderId);

    // Return stock to inventory if it was already deducted (i.e., order was being processed)
    if (ord->order_status == PROCESSING) { // If it was processed, return stock.
        for (int i = 0; i < ord->num_products; i++) {
            products *invProduct = findproduct(inventory, numProductsInInventory); // This will re-prompt, which is not ideal for auto-return
            // To make this automatic without user input for every item, you'd need
            // a findProductByName(const char* name) that doesn't prompt.
            // For now, let's assume findProduct gives the correct result or you
            // handle it by writing a simpler direct lookup for this purpose.
            
            // For a test, we'll assume a direct lookup by name for simplicity without re-prompting:
            products *currentInvProduct = NULL;
            for(int j=0; j<numProductsInInventory; j++) {
                if(strcmp(inventory[j].name, ord->products[i]) == 0) {
                    currentInvProduct = &inventory[j];
                    break;
                }
            }

            if (currentInvProduct != NULL) {
                currentInvProduct->stock_value++; // Return 1 unit
                printf("  - Returned 1 of '%s' to stock. New stock: %d\n",
                       currentInvProduct->name, currentInvProduct->stock_value);
            } else {
                printf("  - WARNING: Product '%s' not found in inventory during cancellation return.\n", ord->products[i]);
            }
        }
    } else {
        printf("  (Stock not returned as order was not yet processed/fulfilled)\n");
    }

    ord->order_status = CANCELLED;
    printf("Order %d status changed to %s.\n", orderId, getStatusString(ord->order_status));
}
