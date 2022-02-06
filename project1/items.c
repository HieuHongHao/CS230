#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "items.h"

void add_item(Item *head ,Item item){
    if(head == NULL){
        *head = item;
        head->nextItem = NULL;
        return;
    }
    Item * temp = head;
    while(temp != NULL){
        if(temp->nextItem == NULL){
            temp->nextItem = (Item *)malloc(sizeof(item));
            *(temp->nextItem) = item;
            break;
        }
        temp = temp->nextItem;
    }
}
Item * remove_item(Item * head, char * name){
    if(head == NULL){
        return NULL;
    }
    if(head->nextItem == NULL){    // Item list only have one item
        if(!strcmp(name,head->name)){
            Item * removedItem  = head;
            head =  NULL;
            return removedItem;
        }
        return NULL; // removed item not found
    }
    Item * prev = head;
    Item * current = head->nextItem;
    while(current !=  NULL){
        if(!strcmp(name,current->name)){  // A bit weird but strcmp returns 0, so !0 means name == current->name
            Item * removedItem = prev->nextItem;
            prev->nextItem = current->nextItem;
            return removedItem;
        }
        prev = current;
        current = current->nextItem;
    }
    return NULL; // removed item not found
}
