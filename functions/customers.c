#include <stdio.h>
#include "../header.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Add customers

void addCustomer(Customer *customerArr,int *elementCount){
    Customer newCustomer;
    int check=0;
    printf("Enter customer name:\n");
    scanf("%s",newCustomer.name);
    printf("Enter customer ID:\n");
    while(1){
        scanf("%d",newCustomer.ID);
        for (int i = 0; i < *elementCount; i++)
        {
            if(customerArr[i].ID==newCustomer.ID) check=1;
        }
        if(check==1) {printf("ID already exists"); continue;}
        if(newCustomer.ID>9999) printf("ID must be four digits");
        else{
            break;
        }
    }
    customerArr=(Customer *)realloc(customerArr,*elementCount++);
    customerArr[*elementCount-1]=newCustomer;
    
}

void removeCustomer(Customer *customerArr,int *elementCount,char cusName[MAX_NAME_LENGTH]){
    for (int i = 0; i < *elementCount; i++)
    {
        if(i+1==elementCount) break;
        if (strcmp(customerArr[i].name,cusName)==0)
        {
            Customer temp=customerArr[i];
            customerArr[i]=customerArr[i+1];
            customerArr[i+1]=temp;

        }
        
    }
    if(strcmp(customerArr[*elementCount-1].name,cusName)!=0){
        printf("Customer not found");
        return;
    }
    customerArr=(Customer *) realloc(customerArr,--*elementCount);
    
}

void editCustomer(Customer *customerArr,int *elementCount,char cusName[MAX_NAME_LENGTH]){
    for (int i = 0; i < *elementCount; i++)
    {
        if (strcmp(customerArr[i].name,cusName)==0)
        {
            printf("Enter new customer name:\n");
            scanf("%s",customerArr[i].name);
            printf("Enter new customer ID:\n");
            scanf("%d",customerArr[i].ID);
            return;       
        }
        
    }
    printf("Customer not found");
    
}