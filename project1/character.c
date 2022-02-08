#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"

void add_character(Character ** headPointer ,Character character){
    Character * head = *headPointer;
    if(head == NULL){
        *headPointer = (Character * )malloc(sizeof(Character));
        **headPointer = character;
        (*headPointer)->nextCharacter = NULL;
        return;
    }
    Character * temp = head;
    while(temp != NULL){
        if(temp->nextCharacter == NULL){
            temp->nextCharacter = (Character *)malloc(sizeof(character));
            *(temp->nextCharacter) = character;
            break;
        }
        temp = temp->nextCharacter;
    }
}
Character* remove_character(Character ** headPointer, char * name){
    Character * head = *headPointer;
    if(head == NULL){
        return NULL; // removed item not found
    }
     if(!strcmp(name,head->name)){
            Character * removed  = head;
            if(head->nextCharacter != NULL){
               *headPointer = head->nextCharacter;
            }else{
                *headPointer = NULL;
            }
            return removed;   
    }
    Character * prev = head;
    Character * current = head->nextCharacter;
    while(current !=  NULL){
        if(!strcmp(name,current->name)){  // A bit weird but strcmp returns 0, so !0 means name == current->name
            Character * removed = prev->nextCharacter;
            if(removed->nextCharacter != NULL){
                removed->nextCharacter = NULL;
            }
            prev->nextCharacter = current->nextCharacter;
            return removed;
        }
        prev = current;
        current = current->nextCharacter;
    }
    return NULL; // removed item not found
}
