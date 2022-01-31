#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "items.h"

void add_item(Item *head ,Item *item){
    if(head == NULL){
        *head = *item;
        head->nextItem = NULL;
        return;
    }
    Item * temp = head;
    while(temp != NULL){
        if(temp->nextItem == NULL){
            temp->nextItem = (Item *)malloc(sizeof(item));
            temp->nextItem = item;
            break;
        }
        temp = temp->nextItem;
    }
}
void remove_item(Item * head, char * name){
    if(head == NULL){
        return;
    }
    if(head->nextItem == NULL){    // Item list only have one item
        if(strcmp(name,head->name)){
            free(head);
            return;
        }
        return;
    }
    Item * prev = head;
    Item * current = head->nextItem;
    while(current !=  NULL){
        if(!strcmp(name,current->name)){
            prev->nextItem = current->nextItem;
            break;
        }
        prev = current;
        current = current->nextItem;
    }
}