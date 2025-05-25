#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../header.h"

// Create a new order
order* createOrder(int id, const char* name) {
    order* newOrder = (order*)malloc(sizeof(order));
    if (!newOrder) {
        perror("Failed to allocate memory for order");
        return NULL;
    }
    newOrder->ID = id;
    strncpy(newOrder->name, name, MAX_NAME_LENGTH - 1);
    newOrder->name[MAX_NAME_LENGTH - 1] = '\0'; // Ensure null termination
    newOrder->products = NULL; // Initialize products to NULL
    newOrder->num_products = 0;
    newOrder->product_capacity = 0; // Initialize capacity
    newOrder->order_status = PENDING; // Set initial order status to PENDING
    return newOrder;
}

// Fill the array of products in the order struct
int add_product_cart(order *current_order, const char *product_name) {
    char **temp = realloc(current_order->products, (current_order->num_products + 1) * sizeof(char *));
    if (temp == NULL) {
        perror("Failed to reallocate memory");
        return -1; // Indicate failure
    }
    current_order->products = temp;

    current_order->products[current_order->num_products] = malloc(strlen(product_name) + 1);
    if (current_order->products[current_order->num_products] == NULL) {
        perror("Failed to allocate memory for product name");
        return -1; // Indicate failure
    }
    strcpy(current_order->products[current_order->num_products], product_name);
    current_order->num_products++;
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
    strncpy(newNode->data.name, current_order.name, MAX_NAME_LENGTH - 1);
    newNode->data.name[MAX_NAME_LENGTH - 1] = '\0';

    newNode->data.num_products = current_order.num_products;
    newNode->data.product_capacity = current_order.product_capacity;
    newNode->data.products = malloc(current_order.num_products * sizeof(char *));
    if (!newNode->data.products) {
        perror("Failed to allocate memory for product array in enqueue");
        free(newNode);
        return;
    }
    for (int i = 0; i < current_order.num_products; i++) {
        newNode->data.products[i] = malloc(strlen(current_order.products[i]) + 1);
        if (!newNode->data.products[i]) {
            perror("Failed to allocate memory for product name in enqueue");
            // Clean up previously allocated product names
            for (int j = 0; j < i; j++) {
                free(newNode->data.products[j]);
            }
            free(newNode->data.products);
            free(newNode);
            return;
        }
        strcpy(newNode->data.products[i], current_order.products[i]);
    }

    newNode->data.order_status = current_order.order_status;

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
    order emptyOrder = {-1, "", NULL, 0, 0, PENDING}; // Return a dummy order on empty queue

    if (queue->front == NULL) {
        printf("Order queue is empty. Cannot dequeue.\n");
        return emptyOrder;
    }

    Node* temp = queue->front;
    order dequeuedOrder = temp->data;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL; // Queue becomes empty
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
}

// Function to free the entire order queue and the memory of the orders within
void freeOrderQueue(OrderQueue* queue) {
    Node* current = queue->front;
    Node* next;
    while (current != NULL) {
        next = current->next;
        freeOrderMemory(current->data); // Free the order's dynamic memory
        free(current);
        current = next;
    }
    free(queue);
}