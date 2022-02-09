#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "items.h"

void add_item(Item ** headPointer ,Item item){
    Item * head = *headPointer;
    if(head == NULL){
        *headPointer = (Item * )malloc(sizeof(Item));
        **headPointer = item;
        (*headPointer)->nextItem = NULL;
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
Item * remove_item(Item ** headPointer, char * name){
    Item * head = *headPointer;
    if(head == NULL){
        return NULL;
    }
    if(!strcmp(name,head->name)){
            Item * removed  = head;
            if(head->nextItem != NULL){
               *headPointer = head->nextItem;
            }else{
                *headPointer = NULL;
            }
            return removed;   
    }
    Item * prev = head;
    Item * current = head->nextItem;
    while(current !=  NULL){
        if(!strcmp(name,current->name)){  // A bit weird but strcmp returns 0, so !0 means name == current->name
            Item * removedItem = prev->nextItem;
            if(removedItem->nextItem != NULL){
                removedItem->nextItem = NULL;
            }
            prev->nextItem = current->nextItem;
            return removedItem;
        }
        prev = current;
        current = current->nextItem;
    }
    return NULL; // removed item not found
}
