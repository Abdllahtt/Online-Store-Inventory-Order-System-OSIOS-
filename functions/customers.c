#include <stdio.h>
#include "../header.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Save Data
void saveCustomers(int arrNum,Customer *arr){ 
        saveArray("customers.dat",arr,sizeof(Customer),arrNum);
}
// Load Data
void loadCustomers(int *arrNum,Customer **arr){ //(double pointer problem)
        loadArray("customers.dat",(void **)arr,sizeof(Customer),arrNum);
}
// Add customers

void addCustomer(Customer **customerArr,int *elementCount){
    Customer newCustomer;
    int check=0;
    printf("Enter customer name:\n");
    scanf("%s",newCustomer.name);
    while(1){
        printf("Enter customer ID:\n");
        scanf("%d",&newCustomer.ID);
        for (int i = 0; i < *elementCount; i++)
        {
            if((*customerArr)[i].ID==newCustomer.ID) check=1;
        }
        if(check==1) {printf("ID already exists"); continue;}
        if(newCustomer.ID>9999){
            printf("ID must be four digits");
        }else{
            break;
            }
    }
    *customerArr=(Customer *)realloc(*customerArr,++(*elementCount));
    (*customerArr)[*elementCount-1]=newCustomer;
    
}

void removeCustomer(Customer **customerArr,int *elementCount){
    char cusName[MAX_NAME_LENGTH];
    printf("Enter a customer name: \n");
    scanf("%s",cusName);
    for (int i = 0; i < *elementCount; i++)
    {
        if(i+1==*elementCount) break;
        if (strcmp((*customerArr)[i].name,cusName)==0)
        {
            Customer temp=(*customerArr)[i];
            (*customerArr)[i]=(*customerArr)[i+1];
            (*customerArr)[i+1]=temp;

        }
        
    }
    if(strcmp((*customerArr)[*elementCount-1].name,cusName)!=0){
        printf("Customer not found");
        return;
    }
    *customerArr=(Customer *) realloc(*customerArr,--*elementCount);
    
}

void editCustomer(Customer **customerArr,int *elementCount){
    char cusName[MAX_NAME_LENGTH];
    printf("Enter a customer name: \n");
    scanf("%s",cusName);
    for (int i = 0; i < *elementCount; i++)
    {
        if (strcmp((*customerArr)[i].name,cusName)==0)
        {
            printf("1- Edit name.\n");
            printf("2- Edit ID.\n");
            int edit;
            scanf("%d",edit);
            switch (edit)
            {
            case 1:
                printf("Enter a new name");
                scanf("%s",(*customerArr)[i].name);
                break;
            case 2:
                printf("Enter a new name");
                scanf("%d",(*customerArr)[i].ID);
                break;
            }
            return;       
        }
        
    }
    printf("Customer not found");
    
}

void displayAllCustomers(Customer *customerArr,int elementcount){
    for (int i = 0; i < elementcount; i++)
    {
        printf("- Name: %s | ID: %d \n",customerArr[i].name,customerArr[i].ID);
    }
    
}
//find a customer
Customer* findcustomer(Customer *customerArr, int customerCount) {
    printf("Enter the name or ID of the wanted customer (single word): \n");
    char input[50]; // Ensure this is large enough for your names

    // The space before %49s consumes any leading whitespace, including leftover newlines.
    // %49s reads up to 49 characters, leaving space for the null terminator.
    scanf(" %49s", input);

    // Clear any remaining characters on the line (e.g., if user typed more than one word)
    clearInputBuffer(); // Call the utility function here

    int wantedID = atoi(input);

    // Search by ID first
    // Assuming ID 0 is not a valid customer ID or indicates conversion failure.
    if (wantedID != 0) {
        for (int i = 0; i < customerCount; i++) {
            if (customerArr[i].ID == wantedID) {
                return &customerArr[i];
            }
        }
    }

    // If not found by ID or if the input was not a valid ID, search by name
    for (int i = 0; i < customerCount; i++) {
        // strcmp returns 0 if strings are identical
        if (strcmp(input, customerArr[i].name) == 0) {
            return &customerArr[i];
        }
    }

    return NULL; // Return NULL if no customer is found
}
//display customer informations
void displayCustomer(const Customer* customer) {
    if (customer != NULL) {
        printf("Name: %s\n", customer->name);
        printf("ID: %d\n", customer->ID);
    } else {
        printf("Customer not found.\n");
    }
}