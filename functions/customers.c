#include <stdio.h>
#include "../header.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



//fill the array of product in the customers struct 
int add_product_cart(Customer *customer, const char *product_name) {
    char **temp = realloc(customer->products, (customer->num_products + 1) * sizeof(char *));
    if (temp == NULL) {
        perror("Failed to reallocate memory");
        return -1; // Indicate failure
    }
    customer->products = temp;

    customer->products[customer->num_products] = malloc(strlen(product_name) + 1);
    if (customer->products[customer->num_products] == NULL) {
        perror("Failed to allocate memory for product name");
        return -1; // Indicate failure
    }
    strcpy(customer->products[customer->num_products], product_name);
    customer->num_products++;
    return 0; // Indicate success
}


// Function to check if the queue is empty
bool isEmpty(CustomerQueue* queue) {
    return (queue->size == 0);
}



//add customers into a queue 
CustomerQueue* createCustomerQueue() {
    CustomerQueue* queue = (CustomerQueue*)malloc(sizeof(CustomerQueue));
    if (!queue) {
        perror("Failed to allocate memory for customer queue");
        return NULL;
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

// Function to enqueue a customer into the queue
void enqueueCustomer(CustomerQueue* queue, Customer customer) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        perror("Failed to allocate memory for new customer node");
        // You might want to handle the customer's product memory here if allocation fails
        // For simplicity in this example, we just return.
        return;
    }

    // Deep copy the customer data to the new node
    newNode->data.id = customer.id;
    strncpy(newNode->data.name, customer.name, MAX_NAME_LENGTH - 1);
    newNode->data.name[MAX_NAME_LENGTH - 1] = '\0'; // Ensure null termination

    newNode->data.num_products = customer.num_products;
    newNode->data.products = malloc(customer.num_products * sizeof(char *));
    if (!newNode->data.products) {
        perror("Failed to allocate memory for product array in enqueue");
        free(newNode);
        return;
    }
    for (int i = 0; i < customer.num_products; i++) {
        newNode->data.products[i] = malloc(strlen(customer.products[i]) + 1);
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
        strcpy(newNode->data.products[i], customer.products[i]);
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
    printf("Enqueued customer with ID: %d\n", customer.id);
}

// Function to dequeue a customer from the front of the queue
Customer dequeueCustomer(CustomerQueue* queue) {
    Customer emptyCustomer = {-1, "", NULL, 0}; // Return a dummy customer on empty queue

    if (queue->front == NULL) {
        printf("Customer queue is empty. Cannot dequeue.\n");
        return emptyCustomer;
    }

    Node* temp = queue->front;
    Customer dequeuedCustomer = temp->data;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL; // Queue becomes empty
    }

    free(temp); // Free the node itself
    queue->size--;
    printf("Dequeued customer with ID: %d\n", dequeuedCustomer.id);
    return dequeuedCustomer;
}

// Function to free the memory associated with a customer (including their products)
void freeCustomerMemory(Customer customer) {
    if (customer.products != NULL) {
        for (int i = 0; i < customer.num_products; i++) {
            free(customer.products[i]);
        }
        free(customer.products);
    }
}

// Function to free the entire customer queue and the memory of the customers within
void freeCustomerQueue(CustomerQueue* queue) {
    Node* current = queue->front;
    Node* next;
    while (current != NULL) {
        next = current->next;
        freeCustomerMemory(current->data); // Free the customer's dynamic memory
        free(current);
        current = next;
    }
    free(queue);
}
